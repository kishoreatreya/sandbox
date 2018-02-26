#!/usr/bin/python

from scapy.all import *

eth = Ether(dst="00:11:22:33:44:55", src="00:55:44:33:22:11")
ip = IPv6(src="::1", dst="::2")
ext = IPv6ExtHdrRouting(segleft=2,addresses=["::3", "::4"])
tcp = TCP(sport=1234, dport=4321)

packet = eth / ip / ext / tcp

packet.show2()

wrpcap('v6ext.pcap', packet)

