#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t macAddr_t[6];       ///< User define type for Mac Address
typedef uint8_t ipv4Addr_t[4];      ///< User define type for Ipv4 Address
typedef uint8_t ipv6Addr_t[16];     ///< User define type for Ipv6 Address
typedef uint8_t compIpv6Addr_t[6];  ///< User define type for compressed Ipv6 Address
typedef uint8_t macAddrHigh_t[4];      ///< User define type for MAC Address for Higher 32 Bits
typedef uint8_t macAddrLow_t[2];       ///< User define type for MAC Address for Lower 16  Bits


typedef struct xpIaclL2Ipv4KeyMask_t
{
    uint32_t Reserved0 : 6;
    uint32_t iAclId : 8;
    macAddr_t macDA;
    macAddr_t macSA;
    uint32_t etherType : 16;
    uint32_t cTagVid : 12;
    uint32_t cTagDei : 1;
    uint32_t cTagPcp : 3;
    uint32_t sTagVid : 12;
    uint32_t sTagDei : 1;
    uint32_t sTagPcp : 3;
    ipv4Addr_t DIP;
    ipv4Addr_t SIP;
    uint32_t L4DestPort : 16;
    uint32_t L4SourcePort : 16;
    uint32_t bd : 16;
    uint32_t icmpMessageType : 8;
    uint32_t ttl : 8;
    uint32_t protocol : 8;
    uint32_t ipv4FragOffsetIsZero : 1;
    uint32_t ipv4DfSet : 1;
    uint32_t ipv4MfSet : 1;
    uint32_t isIcmp : 1;
    uint32_t isTcp : 1;
    uint32_t isUdp : 1;
    uint32_t tcpFlags : 9;
    uint32_t pktHasCtag : 1;
    uint32_t pktHasStag : 1;
    uint32_t Reserved1 : 32;
    uint32_t Reserved2 : 32;
    uint32_t Reserved3 : 7;
}xpIaclL2Ipv4KeyMask_t;

/**
 *  * \struct xpIaclIpv6KeyMask_t
 *   * \public
 *    * \brief This struct represents the key/mask portion of entry in
 *     * Iacl - Ipv6 Table.
 *      *
 *       */
typedef struct xpIaclIpv6KeyMask_t
{
    uint32_t Reserved0 : 6;
    uint32_t iAclId : 8;
    ipv6Addr_t DIP;
    ipv6Addr_t SIP;
    uint32_t BD : 16;
    uint32_t nextHeader : 8;
    uint32_t L4DestPort : 16;
    uint32_t L4SrcPort : 16;
    uint32_t icmpMessageType : 8;
    uint32_t hopLimit : 8;
    uint32_t etherType : 16;
    uint32_t routerMac : 1;
    uint32_t isTcp : 1;
    uint32_t isUdp : 1;
    uint32_t Reserved1 : 21;
}xpIaclIpv6KeyMask_t;

typedef union _stu {
    xpIaclL2Ipv4KeyMask_t v4;
    xpIaclIpv6KeyMask_t v6;
} stu;


struct foo
{
    uint8_t x;
    uint8_t y;
    stu z;
};


int main()
{

    uint8_t array[17];

    printf("SIZEOF xpIaclL3Ipv4KeyMask_t: %lu in bytes\n", sizeof(xpIaclL2Ipv4KeyMask_t));
    printf("SIZEOF xpIaclIpv6KeyMask_t: %lu in bytes\n", sizeof(xpIaclIpv6KeyMask_t));

    printf("SIZEOF stu: %lu in bytes\n", sizeof(stu));

    printf("SIZEOF foo: %lu in bytes\n", sizeof(struct foo));

    printf("SIZEOF uint8_t: %lu in bytes\n", sizeof(uint8_t));

    printf("SIZEOF array: %lu in bytes\n", sizeof(array));

    struct foo bar;

    memset(&bar, 0, sizeof(struct foo));

    printf("bar.x: %d\n", bar.x);
    printf("bar.y: %d\n", bar.y);

    return 0;
}


