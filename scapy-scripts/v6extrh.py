#!/usr/bin/python

from scapy.all import *

base = IPv6(src='::1', dst='::2')
trans = TCP(sport=1234, dport=4321)
data = Raw(load="helloworld")
extrh = IPv6ExtHdrRouting(addresses=["::1", "::4"])
extdh = IPv6ExtHdrDestOpt()
extfr = IPv6ExtHdrFragment()
packet = Ether(dst='00:11:22:33:44:55',src='aa:bb:22:33:44:11')/base/extrh/trans/data

packet.show2()

wrpcap('v6ext.pcap', packet)

hexdump(packet)
