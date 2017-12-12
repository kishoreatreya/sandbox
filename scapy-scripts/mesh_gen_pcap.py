#!/usr/bin/python

import argparse
import sys
import os
from scapy.all import *

# Parse arguments
def parse_args(argv=None):
    # Build arguments
    arghandle = argparse.ArgumentParser(description="MESH PCAP/hex dump generator")
    arghandle.add_argument('-s', '--srcport', help="source port", default=0, type=int)
    arghandle.add_argument('-d', '--destport', help="destination port", default=1, type=int)
    arghandle.add_argument('-H', '--hexdump', help="Dump the packet in hex", default = True, type=bool)
    arghandle.add_argument('-f', '--file', help="Name of pcap file to write, default=testmesh.pcap", default='testmesh.pcap', type=str)
    
    return arghandle.parse_args()


def run():
    # parse args
    args = parse_args()
    
    #
    # MAC PREFIX: '00:58:50:01:00:XX'
    # 
    # MODIFY THE XX PART FOR YOUR DESIRED SRC AND DEST PORT
    
    prefix = '00:58:50:01:00:'
    
    if args.srcport == args.destport:
        print "Warning source port %d == dest port %d" % (args.srcport, args.dstport)
    
    srcstr = str(hex(args.srcport))
    dststr = str(hex(args.destport))
    
    packet = Ether(dst=prefix+dststr, src=prefix+srcstr) / IP() / TCP()
    wrpcap(args.file, packet)
    packet.show2()
    
    if args.hexdump == True:
        hexdump(packet)

#
# INIT MAIN
#

if __name__ == '__main__':
    run()
