//======================================
//  Copyright (c) 2013 Xpliant, Inc. All rights reserved. 
//======================================

/// implemenation of the class in the corresponding .h file
/// assuming target is 32 or 64 bits


#ifdef DBG
#include <stdlib.h>
#endif

#ifndef NDEBUG
#include <assert.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include "XpBitVector.h" 


//======================================
// for argument token op
// setup bitwise operator<op> and operator<op>=
// for the class XpBitVector
//
// requirement is that 
// 0 op 0 is 0
//======================================
#define SETUP_BITWISE_OPERATORS(op)		\
XpBitVector XpBitVector::operator op(const XpBitVector& other) const	\
{	\
	/* pointers to data of result and operands*/	\
	unsigned *data, *data1, *data2;		\
		\
	/* return this*/	\
	XpBitVector ret;	\
		\
	/*pointer to last integer of data*/		\
	unsigned *pLastInt = mData + mLastIntIndex;		\
		\
	ret.copyMembers(*this);		\
	for (data = ret.mData, data1 = mData, data2 = other.mData;	\
			data1 <= pLastInt;	\
			data++, data1++, data2++)	\
			*data = *data1 op *data2;	\
				\
	return ret;		\
}	\
		\
XpBitVector XpBitVector::operator op##=(const XpBitVector& other)	\
{	\
	/* pointers to data of result and operand*/		\
	unsigned *data, *data1;		\
		\
	/* pointer to last integer of data*/	\
	unsigned * const pLastInt = mData + mLastIntIndex;		\
		\
	for (data = mData, data1 = other.mData; data <= pLastInt; data++, data1++)	\
		*data op##= *data1;	\
				\
	return *this;	\
}


//======================================
// construct XpBitVector *this from array src
// copy data segment of srcBits into beginning of the bit vector of size destBits
//
// pad remaining bits with 0s
//
// memory after src is unsigned integers little-endian fashion
//======================================
#define CONSTR_FROM_ARR(destBits, src, srcBits) \
{	\
	/* pointer to data, pointer to last unsigned of data */		\
	unsigned *p, *pLast;	\
		\
	init(destBits);	\
	pLast = mData + mLastIntIndex;	\
	for (p = mData + (srcBits >> BIT_INT_SHIFT); p <= pLast; p++)	\
		*p = 0;		\
	(*this)(0, srcBits - 1) = src;	\
}


//======================================
// number of 1's in a uint32_t
//======================================
static unsigned count1s(uint32_t n) {

	// in each step, we divide n into fixed-width blocks and treat each block separately
	// put count of 1's in each block into that block

	// the basic idea is to add together two halves which are assumed to be done already,
	// however, in each step this formula is optimized for that step

	// once we have done 8-bit blocks, there is no more need to proceed with 16-bit blocks
	// because at that point there is a 1-step formula to get the final result

	// do 2-bit blocks
    n -= n >> 1 & 0x55555555U;             
	
	// do 4-bit blocks assuming 2-bit blocks are done
    n = (n & 0x33333333U) + ((n >> 2) & 0x33333333U);

	// do 8-bit blocks assuming 4-bit blocks are done
    n = (n + (n >> 4)) & 0x0F0F0F0FU;

	// final formula
	// add the 4 8-bit block counts together
    return n * 0x01010101U >> 24; 
}


//======================================
// index of the first 1 bit, or 32 if none
// assuming int is at least 32 bits
//======================================
static unsigned find_first(uint32_t x) {

	// accumulation of bit index after all 0 on the right;
	unsigned ret = 0;

	if (x & 1U)
		return 0U;

	// binary search for the first 1

	if (!(x & LOWER_BITS_LOW(16))) {
		x >>= 16; 
		ret |= 16U;
	}

	if (!(x & LOWER_BITS_LOW(8))) {
		x >>= 8;
		ret |= 8U;
	}

	if (!(x & LOWER_BITS_LOW(4))) {
		x >>= 4;
		ret |= 4U;
	}

	if (!(x & LOWER_BITS_LOW(2))) {
		x >>= 2;
		ret |= 2U;
	}

	if (x & 0x1U)
		return ret;
	
	if (x & 0x2U)
		return ret |= 1U;

	return 32;
}


void XpBitVector::init(unsigned bits) {
	assert(bits);

	mBits = bits;
	LAST_INT_BITS(mLastIntBits, mBits);
	mLastIntIndex = (mBits - mLastIntBits) >> BIT_INT_SHIFT;
	mBytes = N_CHAR_COVERS(bits);
	mLastIntMask = LOWER_BITS(mLastIntBits);
	mData = new unsigned [mLastIntIndex + 1];
	assert(mBits == mLastIntIndex * INT_BITS + mLastIntBits);
}


XpBitVector::XpBitVector(unsigned bits) {
	if (!bits) {
		throw std::range_error(_FILE_LINE);
	}

	init(bits);
	reset();
}


XpBitVector::XpBitVector(unsigned destBits, uint8_t *src, unsigned srcBits) {
	CONSTR_FROM_ARR(destBits, src, srcBits);
}

XpBitVector::XpBitVector(unsigned destBits, uint32_t *src, unsigned srcBits) {
	CONSTR_FROM_ARR(destBits, src, srcBits);
}


void XpBitVector::copyMembers(const XpBitVector &other)
{
	mBytes = other.mBytes;
	mLastIntIndex = other.mLastIntIndex;
	mLastIntBits = other.mLastIntBits;
	mData = new unsigned[mLastIntIndex + 1];
	mLastIntMask = other.mLastIntMask;
	mBits = other.mBits;
}

XpBitVector::XpBitVector(const XpBitVector &other) 
{
	copyMembers(other);
	mData[mLastIntIndex] = 0;
	memcpy(mData, other.mData, mBytes);
}

XpBitVector::XpBitVector(const XpBitVectorRangeRef& range) {
	init(range.mBits);
	mData[mLastIntIndex] = 0;
	cpBits(
		mData, 
		0, mBits - 1, 
		range.mpObj->mData + (range.mLo >> BIT_INT_SHIFT), 
		range.mLo & INT_BIT_MASK);
}


XpBitVector& XpBitVector::operator= (const XpBitVector &other)
{
	if (other.mBits != mBits)
			throw std::range_error(_FILE_LINE);

	if (&other != this)
		memcpy(mData, other.mData, mBytes);
	return *this;
}


XpBitVector::XpBitVector() {
	mData = NULL;
}


void XpBitVector::resize(unsigned bits) {
	unsigned * const old = mData;
	const unsigned oldBytes = mBytes;

	init(bits);
	mData[mLastIntIndex] = mLastIntMask;
	memcpy(mData, old, MIN(oldBytes, mBytes));
	delete old;
}


XpBitVector::~XpBitVector() {
	delete mData;
}


template <typename T> XpBitVector XpBitVector::operator= (T val) {
	// number of bits in T
	const unsigned T_BITS = sizeof(T) * CHAR_BIT;

	// number of whole ints in T
	const unsigned T_INTS = T_BITS >> BIT_INT_SHIFT;

	// number of bytes in all our integers in mData
	const unsigned bytesInInts = (mLastIntIndex + 1) * INT_SIZE;

	if (mBits < T_BITS && (val >= ((T)1U << mBits)))
		throw range_error(_FILE_LINE);

	if (bytesInInts > sizeof(T)) {
		memset(mData + T_INTS, 0, bytesInInts - T_INTS * INT_SIZE);
		memcpy(mData, &val, sizeof(T));
	}
	else
		memcpy(mData, &val, bytesInInts);

	return *this;
}

// explicit instantiate 
template XpBitVector XpBitVector::operator=<uint16_t>(uint16_t val);
template XpBitVector XpBitVector::operator=<uint32_t>(uint32_t val);
template XpBitVector XpBitVector::operator=<uint64_t>(uint64_t val);


XpBitVector XpBitVector::operator= (int val) {
	if (val < 0)
		throw range_error(_FILE_LINE);
	if (mBits < INT_BITS && ((unsigned)val >= (1U << mBits)))
		throw range_error(_FILE_LINE);

	memcpy(mData, &val, INT_SIZE);
	if (mLastIntIndex)
		memset(mData + 1, 0, mLastIntIndex * INT_SIZE);

	return *this;
}


void XpBitVector::flipTo(unsigned *dest) const
{
	// pointer to current integer
	unsigned *p = mData;
	// pointer to last integer
	unsigned * const pLastInt = mData + mLastIntIndex;

	for (; p < pLastInt; p++, dest++)
		*dest = ~*p;
	WRITE_MASK_BITS(dest, ~*p, mLastIntMask);
}


XpBitVector XpBitVector::operator~() const
{
	XpBitVector ret;
	ret.copyMembers(*this);
	ret.mData[mLastIntIndex] = 0;
	flipTo(ret.mData);
	return ret;
}


XpBitVector XpBitVector::operator<<(unsigned shift) const
{
	const int bitsMinus1 = mBits - 1;

	// index of the last shifted bit
	// meaningful only if >=0
	const int lastShiftBit = bitsMinus1 - (int)shift;

	// end of starting integers covered with 0 for sure
	unsigned *endZeroCovers;

	// bit data to copy to
	unsigned *data;

	// return this
	XpBitVector ret;

	ret.copyMembers(*this);

	if (lastShiftBit < 0) 
		ret.reset();
	else {
		data = ret.mData;
		endZeroCovers = data + N_INT_COVERS(shift);
		while (data < endZeroCovers) 
			*data++ = 0;
		ret.mData[mLastIntIndex] = 0;
		ret(shift, bitsMinus1) = (*this)(0, lastShiftBit);
	}

	return ret;
}


XpBitVector XpBitVector::operator>>(unsigned shift) const
{
	const int bitsMinus1 = mBits - 1;

	// lowest bit index from the top cleared to 0 by the shift
	const int lowZeroBit = (int)mBits - (int)shift;

	// bit data to copy to, start and end
	unsigned *data;
	unsigned * last;

	// return this
	XpBitVector ret;

	ret.copyMembers(*this);

	if (lowZeroBit > 0) {
		last = ret.mData + ret.mLastIntIndex;	
		for (data = ret.mData + (lowZeroBit >> BIT_INT_SHIFT); data <= last; )
			*data++ = 0;
		ret(0, lowZeroBit - 1) = (*this)(shift, bitsMinus1);
	}
	else
		ret.reset();

	return ret;
}


XpBitVector XpBitVector::operator>>=(unsigned shift) 
{
	const int bitsMinus1 = mBits - 1;

	// lowest bit index from the top cleared to 0 by the shift
	const int lowZeroBit = (int)mBits - (int)shift;

	// bit data to copy to, start
	unsigned *data;

	// pointer to last integer of data
	unsigned * const pLastInt = mData + mLastIntIndex;

	if (lowZeroBit > 0) {
		// shift by copying range
		(*this)(0, lowZeroBit - 1) = (*this)(shift, bitsMinus1);

		if (shift) {
			// zero above the copied range

			// first zero mask
			data = mData + (lowZeroBit >> BIT_INT_SHIFT);
			KEEP_BITS(data, LOWER_BITS(lowZeroBit & INT_BIT_MASK));

			for (++data; data <= pLastInt; )
				*data++ = 0;
		}
	}
	else
		reset();

	return *this;
}


SETUP_BITWISE_OPERATORS(&)
SETUP_BITWISE_OPERATORS(|)
SETUP_BITWISE_OPERATORS(^)


bool XpBitVector::operator==(const XpBitVector& other) const
{
	// pointers to data of operands
	unsigned *data, *data1;

	// pointer to last integer of data
	unsigned *pLastInt;

	if (other.mBits != mBits)
		return false;

	pLastInt = mData + mLastIntIndex;

	for (data = mData, data1 = other.mData; 
			data < pLastInt; 
			data++, data1++) 
			if (*data != *data1)
				return false;

	if ((*data & mLastIntMask) != (*data1 & mLastIntMask))
		return false;

	return true;
}


void XpBitVector::XpBitVectorBitRef::operator= (const XpBitVectorBitRef& bit) {

	unsigned *addr = mpObj->mData + (mPosition >> BIT_INT_SHIFT);
	const unsigned mask = 1U << (mPosition & INT_BIT_MASK);

	if (INT_ARR_BOOL_BIT(bit.mpObj->mData, bit.mPosition))
		SET_BITS(addr, mask)
	else
		RESET_BITS(addr, mask)
}


void XpBitVector::XpBitVectorBitRef::operator= (bool bit) {

	unsigned *addr = mpObj->mData + (mPosition >> BIT_INT_SHIFT);
	const unsigned mask = 1U << (mPosition & INT_BIT_MASK);

	if (bit)
		SET_BITS(addr, mask)
	else
		RESET_BITS(addr, mask)
}


XpBitVector::XpBitVectorBitRef::operator bool() const {
	return INT_ARR_BOOL_BIT(mpObj->mData, mPosition);
}


XpBitVector::XpBitVectorRangeRef::XpBitVectorRangeRef(unsigned end0, unsigned end1, XpBitVector* pObj):
  mpObj(pObj) {

	  // assign mLo and mHi correctly regardless of order of ends
	  if (end0 < end1) {
		  mLo = end0;
		  mHi = end1;
	  }
	  else {
		  mLo = end1;
		  mHi = end0;
	  }
	  mBits = mHi - mLo + 1;
}


void XpBitVector::cpBits(unsigned *dest, unsigned destLo, unsigned destHi, unsigned *src, int srcLoIntBit) {

	// location of first of our integers in destination data
	unsigned *destPInt = dest + (destLo >> BIT_INT_SHIFT);

	// location of last of our integers in destination data
	unsigned * const destPLastInt = dest + (destHi >> BIT_INT_SHIFT);

	// temp variable
	unsigned tmp;

	// positions in unsigned integers are arranged in "target-little endian way":
	// position 0 is <unsigned> & 1U

	// position of lowest destination bit, in its integer
	const unsigned destLoIntBit = destLo & INT_BIT_MASK;

	// position of highest destination bit, in its integer
	const unsigned destHiIntBit = destHi & INT_BIT_MASK;

		// integer difference between bit positions in their integers
	// here initialized with difference in lowest bits of ranges
	int intBitShift = (int) destLoIntBit - srcLoIntBit;

	// positive amount of shift down and up of various parts of unsigneds
	unsigned partShiftDown, partShiftUp;

	// value read from src array, and next one
	unsigned val, nextVal;

	assert(destLo <= destHi);
	assert(srcLoIntBit < (int)INT_BITS);

	if (destPLastInt == destPInt) 
		// dest range in one int
		XpBitVector::cpBitsTo1Int(destPInt, destLoIntBit, destHiIntBit, src, intBitShift);

	else {
		//dest range not in one int


		//first we shift into the first dest int

		//mask
		tmp = EQ_HIGHER_BITS(destLoIntBit);

		// shifting down from the bottom source integer
		// to the bottom dest integer, 
		// then the source must be two integers at least, 
		// and we also need to shift from the second (next) integer
		if (intBitShift < 0) {

			// for each destination integer, including this one (the bottom)
			// but also, the middle ones (possibly excluding the top)
			// we always have to shift two adjacent source integers
			// and always by the same amounts

			//shift amout down from the top of the first source integer
			partShiftDown = -intBitShift;

			// shift amount up from the bottom of the second source integer
			partShiftUp = INT_BITS + intBitShift;

			WRITE_MASK_BITS(
				destPInt,
				*src >> partShiftDown | *(src + 1) << partShiftUp ,
				tmp 	);

			//we don't need to shift from bottom source int anymore so increment pointer
			src++;
		}

		// if we are shifting not-down from the bottom source integer
		// then that's the only part that goes into the bottom dest integer
		else {
			WRITE_MASK_BITS(
				destPInt,
				*src << intBitShift ,
				tmp 	);

			// after the bottom destination integer, 
			// the middle ones still get two shifts
			// (unless the shift amount is 0 precisely, in which case
			// one of the shifts is by INT_BITS so it does not matter)
			partShiftDown = INT_BITS - intBitShift;
			partShiftUp = intBitShift;
		}


		// now we shift into the destination integers between the first and last one

		// be careful with 0 shift, in that case shifting down by INT_BITS would bomb
		// so we split off that case

		++destPInt;
		if (intBitShift) {
			val = *src;
			while (destPInt < destPLastInt) {
				tmp = val >> partShiftDown;
				nextVal = *++src;
				*destPInt++ = tmp | nextVal << partShiftUp;
				val = nextVal;
			}
		}
		else {
			// because whole integers are copied on a single machine, no need to 
			// worry about endian
			tmp = destPLastInt - destPInt;
			if (tmp) {
				memcpy(destPInt, src + 1, INT_SIZE * tmp);
				destPInt = destPLastInt; 
				src += tmp;
			}
		}
		
	// finally we shift into the last dest integer
	// similarly to the first one:
	// if shift amount is negative, we only need to shift from one source integer (last one)
	// else, we need to shift part down from the second-last one, and part up from the last one

	intBitShift = (int) destHiIntBit - ((srcLoIntBit + destHi - destLo) & INT_BIT_MASK); 

	// mask
	tmp = EQ_LOWER_BITS(destHiIntBit);

	// again be careful to take care of intBitShift 0 
	// where shift by INT_BITS is invalid

	WRITE_MASK_BITS(
		destPInt,
		intBitShift < 0 ? 
			*src >> (-intBitShift) :
			intBitShift ? 
				*src >> (INT_BITS - intBitShift) | *(src + 1) << intBitShift :
				*(src + 1),
		tmp 	);
	}

}


void XpBitVector::XpBitVectorRangeRef::cpFrom(const unsigned *src, unsigned n) {

	//destination data
	unsigned * const data = mpObj->mData;

	// location of first of our integers in destination data
	unsigned *destPInt = data + (mLo >> BIT_INT_SHIFT);

	// location of last of our integers in destination data
	unsigned * const destPLastInt = data + (mHi >> BIT_INT_SHIFT);

	// value read from src array, and next one
	unsigned val, nextVal;

	// positions in unsigned integers are arranged in "target-little endian way":
	// position 0 is <unsigned> & 1U

	// position of lowest destination bit, in its integer
	const unsigned destLoIntBit = mLo & INT_BIT_MASK;

	// we copy to destination in two phases
	// phase 1 is completely determined by src
	// phase 2 then starts at this pointer
	unsigned * destPInt2;

	// position of highest destination bit, in its integer
	const unsigned destHiIntBit = mHi & INT_BIT_MASK;

	// how much we shift down parts of src integers to copy to destination
	unsigned shiftDown;

	unsigned *srcCpEnd;  // limit of copied source (if we copy all of it)

	unsigned mask;

	// integer to write to a destination location
	unsigned destInt;  


	if (destPLastInt == destPInt) {
		// dest range in one int
		// we just need to shift into that integer and mask
		mask = RANGE_BITS(destLoIntBit, destHiIntBit);
		WRITE_MASK_BITS(
			destPInt, 
			*src << destLoIntBit,
			mask);
	 }

	else {
		//dest range not in one int

		// depending on destLoIntBit, we copy to until destPInt2 differently

		// if destLoIntBit then each integer from src has to be split in two
		// and the parts contribute to consecutive integers in destination
		if (destLoIntBit) {		

			srcCpEnd = destPInt + n ;
			destPInt2 = MIN(srcCpEnd , destPLastInt);
			shiftDown = INT_BITS - destLoIntBit;

			// write the first dest integer
			val = *src;
			mask = EQ_HIGHER_BITS(destLoIntBit);
			WRITE_MASK_BITS(
				destPInt,
				val << destLoIntBit,
				mask);

			// finish all that is determined by src, below destPInt2
			while (++destPInt < destPInt2) {
				nextVal = *++src;
				*destPInt = val >> shiftDown | nextVal << destLoIntBit;
				val = nextVal;
			}

			// next copy to destPInt2, if that is the same as the end, finish already
			if (destPInt2 == destPLastInt) {
				mask = EQ_LOWER_BITS(destHiIntBit);
				destInt = val >> shiftDown;
				if (destPInt2 < srcCpEnd)
					destInt |= *(src + 1) << destLoIntBit;
				WRITE_MASK_BITS(
					destPLastInt,
					destInt,
					mask );
				return;
			}

			assert(destPInt2 < destPLastInt);

			// start second phase
			*destPInt2++ = val >> shiftDown;
		}


		else {
			// if not shifting we can just copy mem

			srcCpEnd = destPInt + n - 1;
			destPInt2 = MIN(srcCpEnd, destPLastInt);

			// copy first phase
			memcpy(destPInt, src, (destPInt2 - destPInt) * INT_SIZE);

			val = *(src + n - 1);

			if (destPInt2 == destPLastInt) {
				mask = EQ_LOWER_BITS(destHiIntBit);
				WRITE_MASK_BITS(
					destPLastInt,
					val,
					mask);
				return;
			}

			*destPInt2++ = val;
		}

		// after the start second phase is the same regardless of destLoIntBit
		memset(destPInt2, 0, (destPLastInt - destPInt2) * INT_SIZE);
		RESET_BITS(destPLastInt, EQ_LOWER_BITS(destHiIntBit));

	}
}


void XpBitVector::XpBitVectorRangeRef::operator=(const void *src) {

	//destination data
	unsigned * const data = mpObj->mData;

	// location of first of our integers in destination data
	unsigned *destPInt = data + (mLo >> BIT_INT_SHIFT);

	// location of last of our integers in destination data
	unsigned * const destPLastInt = data + (mHi >> BIT_INT_SHIFT);

	// positions in unsigned integers are arranged in "target-little endian way":
	// position 0 is <unsigned> & 1U

	// position of lowest destination bit, in its integer
	const unsigned destLoIntBit = mLo & INT_BIT_MASK;

	// position of highest destination bit, in its integer
	const unsigned destHiIntBit = mHi & INT_BIT_MASK;

	// value to write to any dest integer
	unsigned val;

	// bit index after src from which we start copying
	unsigned lo;

	// src as pointer that we can increment
	uint8_t *src8 = (uint8_t*)src;

	if (destPLastInt == destPInt) {
		// dest range in one int
		// we just need to shift into that integer and mask
		UINT_BITS_ARR_ADVANCE(val, src8, 0, lo, mBits, false);
		WRITE_BITS_IN_MASK(
			destPInt, 
			val << destLoIntBit,
			RANGE_BITS(destLoIntBit, destHiIntBit));
	 }

	else {
		//dest range not in one int

		// write the first dest integer
		UINT_BITS_ARR_ADVANCE(val, src8, 0, lo, INT_BITS - destLoIntBit, true);
		WRITE_BITS_IN_MASK(
			destPInt,
			val << destLoIntBit,
			EQ_HIGHER_BITS(destLoIntBit)); 

		// middle integers

		while (++destPInt < destPLastInt) {
			UINT_BITS_ARR_ADVANCE(val, src8, lo, lo, INT_BITS, true);
			*destPInt = val;
		}
		
		// finally last dest integer
		UINT_BITS_ARR_ADVANCE(val, src8, lo, lo, destHiIntBit + 1, false);
		WRITE_BITS_IN_MASK(
			destPLastInt,
			val,
			EQ_LOWER_BITS(destHiIntBit));
	}
}


template <typename T> XpBitVector* XpBitVector::create(unsigned bits, T arr)
	{
		XpBitVector *result = new XpBitVector(bits);
		unsigned *data;
		unsigned * const pLastInt = result->mData + result->mLastIntIndex;	

		for (data = result->mData; data < pLastInt; data++) 
			CP_ADVANCE_ARR_BOOL_TO_BITS(T, arr, INT_BITS, data)

		CP_ADVANCE_ARR_BOOL_TO_BITS(T, arr, result->mLastIntBits, data)

		return result;
	}


// explicit instantiate for unsigned*
template XpBitVector* XpBitVector::create<unsigned*>(unsigned, unsigned*);


uint32_t XpBitVector::toUint32 (unsigned hi, unsigned lo) const {

	// this we return
	unsigned ret = 0;

	cpBitsTo1Int(&ret, 0, hi - lo, mData + (lo >> BIT_INT_SHIFT), -(int)(lo & INT_BIT_MASK));
	return ret;
}


uint64_t XpBitVector::toUint64 (unsigned hi, unsigned lo) const {

	// this we return
	uint64_t ret = 0;

	cpBits((unsigned *)&ret, 0, hi - lo, mData + (lo >> BIT_INT_SHIFT), lo & INT_BIT_MASK);
	return ret;
}


unsigned XpBitVector::count1s() const {

	// pointer to data
	uint32_t *data = mData;

	// return this
	unsigned ret = 0;

	// pointer to next integer past the ones we use
	uint32_t * const pOver = mData + mLastIntIndex + 1;

	do 
		ret += ::count1s(*data++);
	while (data < pOver);

	return ret;
}


unsigned XpBitVector::find_first () const {

	// pointer to data
	uint32_t *data = mData;

	// return this
	unsigned ret = 0;

	// single step find_first
	unsigned ret1;

	// pointer to next integer past the ones we use
	uint32_t * const pOver = mData + mLastIntIndex + 1;

	for (; data < pOver; data++) {
		ret += ret1 = ::find_first(*data);
		if (ret1 < 32)
			break;
	}

	return ret;
}


void XpBitVector::set() {
	memset(mData, -1, mBytes);
	mData[mLastIntIndex] = mLastIntMask;
}


ostream&
operator<<(ostream& os, const XpBitVector& b) 
{
	// we print BITS_IN_ROW consecutive bits in one row
	// starting from low bits
	// in each row, low bit is on the right
	// in each row, there are blocks of BITS_IN_BLOCK bits printed consecutively, separated by space
	// under each row, there is an "index row" 
	// where indices of low and high bits of blocks are shown under their bits
	// if indices are more than 3 digits (>= 1000) there will not be enough space under a block to print them
	// so they will be shifted

	// some unsigned quantities are signed so we can go into invalid neg values
	
	// bit index
	int bit;

	// last bit
	const unsigned last = b.size() - 1;

	const unsigned BITS_IN_BLOCK = 8;  // should be at least 8
	const unsigned BITS_IN_ROW = 64;  // should be multiple of BITS_IN_BLOCK

	// left bit in a row
	// this may be higher than last, in which case not printed
	unsigned lBitInRow = BITS_IN_ROW - 1;

	// right bit in row
	unsigned rBitInRow;

	// left bit in row really printed
	unsigned lPrintedBitInRow;  

	// as above but for blocks
	int lBitInBlock;
	unsigned rBitInBlock, lPrintedBitInBlock;  

	const char SPACE = ' ';

	char row[BITS_IN_ROW << 2];
	char *p;  // pointer to place in the row

	char indexRow[BITS_IN_ROW << 2];
	char *pI ; // pointer to place in the index row

	// left block index string
	char lI[BITS_IN_BLOCK << 1];
	unsigned lLength; // its length

	// right block index string
	char rI[BITS_IN_BLOCK << 1];
	unsigned rLength; // its length

	// total of the lengths above left and right
	unsigned lrLength;  

	// in between the left and right printed indexes is the middle padding
	// to the left of the left index there may be left padding
	// whose lengths are 
	unsigned midPadLength, leftPadLength;


	// loop over rows
	while(1) {
		lPrintedBitInRow = MIN(lBitInRow, last);
		rBitInRow = lBitInRow - (BITS_IN_ROW - 1);

		bit = lBitInRow;
		p = row;
		pI = indexRow;

		// loop over blocks
		lBitInBlock = lBitInRow;
		while (1) {
			lBitInBlock = bit;
			if (lBitInBlock < (int)rBitInRow) {
				*p = 0;
				*pI = 0;
				break;
			}
			rBitInBlock = lBitInBlock - (BITS_IN_BLOCK - 1);

			// fill up the block of bits to be printed
			for (; bit >= (int)rBitInBlock; bit--) {
				*p++ = bit > (int)lPrintedBitInRow ? SPACE : b[bit] + '0';
			}

			// separate blocks
			*p++ = SPACE;

			// now fill up the part of the index row that corresponds to this block

			*lI = 0;
			*rI = 0;

			// print right index if needed
			if (last >= rBitInBlock)
				sprintf(rI, "%d", rBitInBlock);

			rLength = strlen(rI);

			// print left index if needed and different than right index
			if (last > rBitInBlock) {

				lPrintedBitInBlock = MIN((int)last, lBitInBlock);
				sprintf(lI, "%d",  lPrintedBitInBlock );
				lLength = strlen(lI);
				rLength = strlen(rI);
				lrLength = lLength + rLength;

				// length of pad between left and right index
				// at least 1, but may be more if needed to push the left index
				// to align with the left end of the bit block
				midPadLength = MAX((int)lPrintedBitInBlock - (int)rBitInBlock - (int)lrLength, 0) + 1;

				// if the block is not of maximal length, we need left pad as well
				leftPadLength = MAX((int)BITS_IN_BLOCK - (int)lrLength - (int)midPadLength, 0);
			}
			else {
				lLength = 0;
				leftPadLength = MAX(BITS_IN_BLOCK - rLength, 0);
				midPadLength = 0;
			}

			memset(pI, SPACE, leftPadLength);
			pI += leftPadLength;
			memcpy(pI, lI, lLength);
			pI += lLength;
			memset(pI, SPACE, midPadLength);
			pI += midPadLength;
			memcpy(pI, rI, rLength);
			pI += rLength;
			*pI++ = SPACE;

		}

			os << endl << "val:  " << row << endl << "pos:  " << indexRow << endl << endl;

			if (lBitInRow < last) 
				lBitInRow += BITS_IN_ROW;
			else
				break;
	}

	return os;
}


#ifdef DBG
	void XpBitVector::dump(unsigned lineNum) const {

		// indices of ints and bits in int
		unsigned i = 0, j;

		// index of bit in the vector
		unsigned bit = 0; 

		cout << dec;
		cout << "line " << lineNum << endl;
		cout << "XpBitVector:" << endl;
		cout << "mData " << mData << endl;
#if 0
		DBGX(*mData);
#endif
		for (; i <= mLastIntIndex; i++) {
			for (j = 0; j < INT_BITS; j++, bit++) {
				if (bit == mBits)
					break;
				cout << "bit " << dec << bit << " :\t" << ((mData[i] & (1U << j)) != 0) << endl;
			}
			if (bit == mBits)
				break;
		}
		cout << dec;
		cout << "mLastIntIndex " << mLastIntIndex << endl;
		cout << "mLastIntBits " << mLastIntBits << endl;
		cout << "mLastIntMask 0x" << hex << mLastIntMask << endl;
		assert(!(mData[mLastIntIndex] & ~mLastIntMask));
		cout << "mBits " << dec << mBits << endl;
		cout << "mBytes " << mBytes << endl;
	}


	void XpBitVector::rand() {
		for (unsigned i = 0; i < mBits; i++) 
			(*this)[i] = ::rand() & 1U ? true : false;
	}	

#endif
