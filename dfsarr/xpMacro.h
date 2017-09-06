#ifndef _XP_MACRO_H
#define _XP_MACRO_H

//==============================================================================
/// common XP macros
//==============================================================================


//==============================================================================
/// STRINGIZE(x) turns x into a string in the proper C syntax
///
/// \param[in]	x	a literal string (without "")
//
/// \return	x with surrounding ""
//==============================================================================
#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

//==============================================================================
/// \return string constant representing current file and line
//==============================================================================
#define _FILE_LINE \
	"file "__FILE__"\tline "STRINGIZE(__LINE__)


#endif