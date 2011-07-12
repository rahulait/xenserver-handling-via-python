'''
Created on Jul 12, 2011

@author: Rahul Sharma
'''
import sys, time, string

import XenAPI


def main(session,vm_name):
    # Find a non-template VM object
    #vms_all=session.xenapi.VM.get_all()
    #print "XenServer has %d VMs which also includes templates....." % len(vms_all)
    
    vms = session.xenapi.VM.get_all()
    print "Server has %d VM objects (this includes templates):" % (len(vms))  
      
    for vm in vms:
        record = session.xenapi.VM.get_record(vm)
        
        # We cannot power-cycle templates and we should avoid touching control domains
        # unless we are really sure of what we are doing...
        if not(record["is_a_template"]) and not(record["is_control_domain"]):
            name = record["name_label"]
            flag=cmp(vm_name,name)
            if not flag:
                powerstate=record["power_state"]
                print "VM %s is in power state '%s'" % (name,powerstate)
                chkpowstate=cmp(string.upper(powerstate),"HALTED")
                if not(chkpowstate) :
                    print "Found VM uuid", record["uuid"], "called: ", name
                    try:
                        session.xenapi.VM.start(vm,False,False)
                    except XenAPI.Failure as err :
                        print "%s" % err
                else:
                    print "VM with uuid %s not in halted state, so no change to it" % record["uuid"]
    print "Program Ended....."

                
if __name__ == "__main__":
    if len(sys.argv) <> 5:
        print "Usage:"
        print sys.argv[0], " <url> <username> <password> <Name of VM to start>"
        sys.exit(1)
    url = sys.argv[1]
    username = sys.argv[2]
    password = sys.argv[3]
    vm_name=sys.argv[4]
    # First acquire a valid session by logging in:
    session = XenAPI.Session(url)
    session.xenapi.login_with_password(username, password)
    main(session,vm_name)
