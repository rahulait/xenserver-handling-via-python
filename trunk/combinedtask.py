'''
Created on Jul 11, 2011

@author: WAH WAH
'''
import sys, time, string

import XenAPI

class commands:
    def vm_start(self,session,vmname):
        vms=session.xenapi.VM.get_all()
        isvmthere=0
        
        for vm in vms:
            record=session.xenapi.VM.get_record(vm)
            if not(record["is_a_template"]) and not(record["is_control_domain"]):
                name = string.upper(record["name_label"])
                if name==vmname:
                    isvmthere=1
                    try:
                        if record["power_state"]!="Running":
                            session.xenapi.VM.start(vm,False,True)
                            print "VM started successfully......."
                            break
                        else:
                            print "VM already in running state....."
                    except XenAPI.Failure as err:
                        print "Error occurred: %s" % err
        
        if isvmthere==0:
            print "VM not present!!!! Check whether you provided the correct input...."
            
    def vm_stop(self,session,vmname):
        vms=session.xenapi.VM.get_all()
        isvmthere=0
        
        for vm in vms:
            record=session.xenapi.VM.get_record(vm)
            if not(record["is_a_template"]) and not(record["is_control_domain"]):
                name = string.upper(record["name_label"])
                if name==vmname:
                    isvmthere=1
                    try:
                        if record["power_state"]!="Halted":
                            session.xenapi.VM.clean_shutdown(vm)
                            print "VM stopped successfully......."
                            break
                        else:
                            print "VM already in halted state....."
                    except XenAPI.Failure as err:
                        print "Error occurred: %s" % err
        
        if isvmthere==0:
            print "VM not present!!!! Check whether you provided the correct input...."
        
    def vm_suspend(self,session,vmname):
        vms=session.xenapi.VM.get_all()
        isvmthere=0
        
        for vm in vms:
            record=session.xenapi.VM.get_record(vm)
            if not(record["is_a_template"]) and not(record["is_control_domain"]):
                name = string.upper(record["name_label"])
                if name==vmname:
                    isvmthere=1
                    try:
                        if record["power_state"]!="Halted":
                            session.xenapi.VM.halt(vm,False,True)
                            print "VM started successfully......."
                            break
                        else:
                            print "VM already in running state....."
                    except XenAPI.Failure as err:
                        print "Error occurred: %s" % err
        
        if isvmthere==0:
            print "VM not present!!!! Check whether you provided the correct input...."
        
    def vm_reboot(self,session,vmname):
        vms=session.xenapi.VM.get_all()
        
    

if __name__ == "__main__":

    if len(sys.argv) <> 6:
        print "Usage:"
        print sys.argv[0], " <url> <username> <password> <vmname> <operations>"
        sys.exit(1)
    url = sys.argv[1]
    username = sys.argv[2]
    password = sys.argv[3]
    vmname=sys.argv[4]
    operation=sys.argv[5]
    
    objcommands=commands()
    fxnlist=dir(objcommands)
    length=len(fxnlist)
    i=0
    chkflag=0
    while i < length :
        if string.upper(operation)==string.upper(fxnlist[i]):
            chkflag=1
            break
        i=i+1
            
    if chkflag==0:
        print "Function not present!!! Check the function_name....."
        exit(0)
        
    # First acquire a valid session by logging in:
    session = XenAPI.Session(url)
    session.xenapi.login_with_password(username, password)
    objcommands.vm_start(session,string.upper(vmname))    