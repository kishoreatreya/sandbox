#!/usr/bin/python

# Written by Kishore Atreya
#
# Sample code to generate q nums for dest port mode (regular output queuing mode)
#

# get abs q num routing for port/q
# we need to implement with spray_grp size as 1
def get_abs_q_num(p, q, nqs, spray_grp):
    if p == 176:
        # cpu 0
        return 512 * 3 + 384 + q
        
    if p == 240:
        # cpu 1
        return 512 * 7 + 384 + q
    
    if p == 160:
        # lb 0
        return 512 * 2 + 384 + (q * spray_grp)
        
    if p == 224:
        # lb 1
        return 512 * 6 + 384 + (q * spray_grp)
        
    pipe = int(p / 16)
    poff = int(p % 16)
    
    return 512 * pipe + poff * nqs + (q * spray_grp)
    
# is port valid checker
def is_port_vld(p):
    if p >= 128 and ((p != 176) and (p != 240) and (p != 224) and (p != 160)):
        return False;
    
    return True;
        
# if port cpu
def is_port_cpu(p):
    return ((p == 176) or (p == 240))
        
# main routine
def main():
    tc_bits  = 4
    dp_bits  = 8
    mc_bits  = 1
    sel_bits = 2 # least sig bits in qmap idx cfg memory
    entries  = pow(2, tc_bits + dp_bits + mc_bits)

    num_uc_qs_port = 16
    num_mc_qs_port = 8
    spray_grp_size = 1

    # display some info
    print "INFO: SPRAY GROUP SIZE: %d" % spray_grp_size
    print "INFO: NUM_UC_QS_PORT:   %d" % num_uc_qs_port
    print "INFO: NUM_MC_QS_PORT:   %d" % num_mc_qs_port
    
    # For each front panel dest port (cpu ports are different, loopback ports must be accounted for in this loop)
    for mc in range(pow(2, mc_bits)):
        # Determine effective uc tc range based on num_qs_port and spray_grp_size
        if not mc:
            tc_range = int(num_uc_qs_port / spray_grp_size)
        else:
            tc_range = int(num_mc_qs_port / spray_grp_size)
            
        print "INFO: TC RANGE:         %d" % tc_range
        
        for i in range(pow(2, dp_bits)):
        
            # loop through 256 ports
            if not is_port_vld(i):
                continue
        
            # port is valid
            if is_port_cpu(i):
                continue
        
            # port is not a cpu port
    
            # account for traffic class now:            
            for tc in range(pow(2, tc_bits)):
                # we need to repeat our q's in the valid tc_range -> this creates a mapping of higher tc -> lower tc
                # so when iterating through tc's we will mod with tc_range
                if not tc % 4:
                    abs_q = get_abs_q_num(i, tc % tc_range, num_uc_qs_port + num_mc_qs_port, spray_grp_size)
        
                    if mc:
                        abs_q = abs_q + num_uc_qs_port
        
                    # start building entry index
                    # account for mc or no mc
                    ent_idx = mc << 12   # mc bit is bit 14 in index
                    ent_idx |= i << 4    # dest_port is located in bits 6-13
        
                    ent_idx |= tc    # we now have the line
        
                    # Start the spray
                    print "INFO: PORT: %d TC: %d MC: %d ENT-IDX: %d LINE: %d Q0: %d Q1: %d Q2: %d Q3: %d" % (i, tc, mc, ent_idx, ent_idx >> 2, abs_q + 0, abs_q + 1, abs_q + 2, abs_q + 3)

if __name__ == "__main__":
    main()




