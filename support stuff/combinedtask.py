'''
Created on Jul 11, 2011

@author: WAH WAH
'''
import sys, string

import XenAPI

class commands:
    def vm_start(self,session,vm):
        record=session.xenapi.VM.get_record(vm)
        powerstate=string.upper(record["power_state"])
        try:
            if powerstate=="HALTED" :
                session.xenapi.VM.start(vm,False,True) #start_paused=False, Force=True
                print "VM started successfully......."
            elif powerstate=="SUSPENDED":
                session.xenapi.VM.resume(vm,False,True) #start_paused=False, Force=True
                print "VM started successfully......."
            elif powerstate=="PAUSED":
                session.xenapi.VM.unpause(vm)
                print "VM moved to running state successfully....." 
            else:
                print "VM already in running state....."
        except XenAPI.Failure as err:
                print "Error occurred in starting: %s" % err

            
    def vm_stop(self,session,vm):
        record=session.xenapi.VM.get_record(vm)
        powerstate=string.upper(record["power_state"])
        try:
            if powerstate=="SUSPENDED":
                session.xenapi.VM.resume(vm,False,True) #start_paused=False, Force=True
                session.xenapi.VM.clean_shutdown(vm)
                print "VM stopped successfully......."
            elif powerstate=="PAUSED":
                session.xenapi.VM.unpause(vm)
                session.xenapi.VM.clean_shutdown(vm)
                print "VM stopped successfully......" 
            elif powerstate=="RUNNING":
                session.xenapi.VM.clean_shutdown(vm)
                print "VM stopped successfully......."
            else:
                print "VM already in halted state...."
        except XenAPI.Failure as err:
            print "Error occurred: %s" % err

        
    def vm_suspend(self,session,vm):
        record=session.xenapi.VM.get_record(vm)
        powerstate=string.upper(record["power_state"])
        try:
            if powerstate=="HALTED":
                print "VM in Halted state can't be suspended!!!"
            elif powerstate=="RUNNING":
                session.xenapi.VM.suspend(vm)
                print "VM suspended successfully......."
            elif powerstate=="PAUSED":
                session.xenapi.VM.unpause(vm)
                session.xenapi.VM.suspend(vm)
                print "VM suspended successfully......" 
            else:
                print "VM already in suspended state....."
        except XenAPI.Failure as err:
            print "Error occurred: %s" % err
        
           
    def vm_reboot(self,session,vmname):
        record=session.xenapi.VM.get_record(vm)
        powerstate=string.upper(record["power_state"])
        try:
            if powerstate=="HALTED":
                print "VM in Halted state can't be rebooted!!! It can be started...."
            else:
                if powerstate=="SUSPENDED":
                    session.xenapi.VM.resume(vm,False,True)
                elif powerstate=="PAUSED":
                    session.xenapi.Vm.unpause(vm)
                session.xenapi.VM.clean_shutdown(vm)
                session.xenapi.VM.start(vm,False,True)
                print "VM rebooted successfully......."   

        except XenAPI.Failure as err:
            print "Error occurred: %s" % err
    

    def vm_pause(self,session,vmname):
        record=session.xenapi.VM.get_record(vm)
        powerstate=string.upper(record["power_state"])
        try:
            if powerstate=="HALTED":
                session.xenapi.VM.start(vm,True,True)
                print "VM started and entered into paused state successfully..."
            elif powerstate=="RUNNING":
                session.xenapi.VM.pause(vm)
                print "VM paused successfully...."
            elif powerstate=="SUSPENDED":
                session.xenapi.VM.resume(vm,True,True)
                #session.xenapi.VM.pause(vm)
                print "VM paused successfully...."
            elif powerstate=="PAUSED":
                print "VM already in Paused state.... "
        except XenAPI.Failure as err:
            print "Error occured: %s" % err

    
    def vm_migrate(self,session,vm,destn_server):
        record=session.xenapi.VM.get_record(vm)
        vm_resident_host_opaque_ref=record["resident_on"]
        vm_resident_host_record=session.xenapi.host.get_record(vm_resident_host_opaque_ref)
        vm_resident_host=vm_resident_host_record["name_label"]
        print "%s" % vm_resident_host
        if string.upper(vm_resident_host)==string.upper(destn_server):
            print "VM on same host... No need of migration..."
            exit(1)
        powerstate=string.upper(record["power_state"])
        hosts=session.xenapi.host.get_all()
        for host in hosts:
            host_record=session.xenapi.host.get_record(host)
            host_name=host_record["name_label"]
            #if vm_resident_host==host:
                #print "VM on same host... No need of migration..."
                #exit(1)
            if string.upper(host_name)==string.upper(destn_server):  
                try:
                    if powerstate!="RUNNING":
                        print "A VM can only be migrated if it is in Running state. Check the state of the machine...."
                    else:
                        session.xenapi.VM.pool_migrate(vm,host,{ "live": "true" })
                        #record=session.xenapi.task.get_record(task)
                        #while record["status"]<> "success":
                            #time.sleep(1)
                        print "VM Migrated successfully..."
                except XenAPI.Failure as err:
                    print "Error occured: %s" % err
                
    
if __name__ == "__main__":

    if len(sys.argv) < 6:
        print "Usage:"
        print sys.argv[0], " <url> <username> <password> <operations> <vmname> <list of other parameters which are not mandatory for some functions>"
        sys.exit(1)
    url = sys.argv[1]
    username = sys.argv[2]
    password = sys.argv[3]
    operation=sys.argv[4]
    vmname=sys.argv[5]
    objcommands=commands()
    fxnattr=0
    try:
        fxnattr=getattr(objcommands,operation)
        session=XenAPI.Session("http://172.20.25.172")
        session.xenapi.login_with_password("root","Rackware123")
        vms=session.xenapi.VM.get_all()
        isvmthere=0
        vm=0    
        for vm in vms:
            record=session.xenapi.VM.get_record(vm)
            if not(record["is_a_template"]) and not(record["is_control_domain"]):
                name =record["name_label"]
                if string.upper(name)==string.upper(vmname):
                    xx=session.xenapi.VM.get_by_name_label(name)
                    i=0
                    while i<len(xx):
                        #bb=session.xenapi.VM.get_resident_on(xx[i])
                        #hostrec=session.xenapi.host.get_record(bb)
                        #hostname=hostrec["hostname"]
                        #if string.upper(hostname)==string.upper(servername):
                        if string.upper(operation)!="VM_MIGRATE":
                            fxnattr(session,vm)  #this is to be indented with the above if statements.. now they are disabled, so it is not indented with them....
                            isvmthere=1          #this also needed to be indented....
                            i=i+1
                        else:
                            servername=sys.argv[6]
                            fxnattr(session,vm,servername)
                            isvmthere=1
                            i=i+1
            
        if isvmthere==0:
            print "VM not present!!!! Check whether you provided the correct input...."
        session.xenapi.logout()
    except AttributeError:
        print "Method not present... Please check the method_name" 
    except XenAPI.Failure:
        print "Error occured..... Check the supplied values......"
        