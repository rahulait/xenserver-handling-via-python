'''
Created on Jul 11, 2011

@author: Rahul Sharma
'''

import sys, string   # sys is used for handling input parameters, and string to format and check the string values.........

import XenAPI        # imports XenAPI which provides various functions which we can use to make calls to XenServer 

class commands:                                                  # class containing all the member functions which will be called to perform particular task....
    
    def vm_start(self,session,vm):                               # function to start the VM......
        vm_record=session.xenapi.VM.get_record(vm)               # getting all the properties of the particular VM passed....           
        vm_power_state=string.upper(vm_record["power_state"])    # retrieving the power_state of the VM.....
        try:
            if vm_power_state=="HALTED" :                        # if VM is halted, then start it.........
                session.xenapi.VM.start(vm,False,True)           # start_paused=False, Force=True
                print "VM started successfully......."
            elif vm_power_state=="SUSPENDED" or vm_power_state=="PAUSED" :  # if VM is suspended or paused, then resume it.....
                session.xenapi.VM.resume(vm,False,True)          # start_paused=False, Force=True
                print "VM started successfully......."
            else:
                print "VM already in running state....."
        except XenAPI.Failure as err:                            # In case of error......
                print "Error occurred in starting: %s" % err

            
    def vm_stop(self,session,vm):                                # function to stop a particular VM......
        vm_record=session.xenapi.VM.get_record(vm)               # retrieving all the properties of a particular VM......
        vm_power_state=string.upper(vm_record["power_state"])    # retrieving the power_state of the VM......
        try:
            if vm_power_state=="PAUSED" or vm_power_state=="SUSPENDED":  # if the power_state is paused or suspended, then resume it and then do shutdown......
                session.xenapi.VM.resume(vm,False,True)          # start_paused=False, Force=True
                session.xenapi.VM.clean_shutdown(vm)
                print "VM stopped successfully......."
            elif vm_power_state=="RUNNING":                      # If the VM is in running state, then shutdown it......
                session.xenapi.VM.clean_shutdown(vm)
                print "VM stopped successfully......."
            else:
                print "VM already in halted state...."
        except XenAPI.Failure as err:                            # In case of error, notify user with the error message.....
            print "Error occurred: %s" % err

        
    def vm_suspend(self,session,vm):                             # function to suspend the VM......
        vm_record=session.xenapi.VM.get_record(vm)               # get the properties of a particular VM.....
        vm_power_state=string.upper(vm_record["power_state"])    # get the power_state of a particular VM......
        try:
            if vm_power_state=="HALTED":                         # If VM is in Halted state, i.e in Stopped state, it can't be brought to Suspended state....
                print "VM in Halted state can't be suspended!!!"
            elif vm_power_state=="PAUSED" or vm_power_state=="RUNNING":  #If VM is Paused or Running, then suspend it......
                session.xenapi.VM.suspend(vm)
                print "VM suspended successfully......."
            else:
                print "VM already in suspended state....."
        except XenAPI.Failure as err:                            # In case of error, display error message......
            print "Error occurred: %s" % err
        
           
    def vm_reboot(self,session,vmname):                          # Function to reboot the VM......
        vm_record=session.xenapi.VM.get_record(vm)               # get the properties of a particular VM......
        vm_power_state=string.upper(vm_record["power_state"])    # getting the power_state of a particular VM......
        try:
            if vm_power_state=="HALTED":                         # a VM in halted(stopped) state can't be rebooted, hence the check here......
                print "VM in Halted state can't be rebooted!!! It can be started...."
            else:
                if vm_power_state=="PAUSED" or vm_power_state=="SUSPENDED":  # if in paused or suspended state, then resume it and then reboot it.......
                    session.xenapi.VM.resume(vm,False,True)
                session.xenapi.VM.clean_shutdown(vm)
                session.xenapi.VM.start(vm,False,True)
                print "VM rebooted successfully......."   
        except XenAPI.Failure as err:                            # In case of any error, perform error handling here.......
            print "Error occurred: %s" % err
    

    def vm_pause(self,session,vmname):                           # function to pause a particular VM......
        vm_record=session.xenapi.VM.get_record(vm)               # get the properties of a particular VM.....
        vm_power_state=string.upper(vm_record["power_state"])    # get the power_state of a particular VM......
        try:
            if vm_power_state=="HALTED":                         # If the VM is in Halted(Shutdown) state, then start it keeping start_paused=true;
                session.xenapi.VM.start(vm,True,True)            # START_PAUSED=TRUE, FORCE=TRUE
                print "VM started and entered into paused state successfully..."
            elif vm_power_state=="RUNNING" or vm_power_state=="SUSPENDED":  # If the VM is in running or suspended state, then simply pause it.....
                session.xenapi.VM.pause(vm)
                print "VM paused successfully...."
            elif vm_power_state=="PAUSED":                       # If VM already in paused state, then display "Already in paused state..."
                print "VM already in Paused state.... "
        except XenAPI.Failure as err:                            # In case of error, print the error message......
            print "Error occured: %s" % err

    
    def vm_migrate(self,session,vm,destn_server_name):
        vm_record=session.xenapi.VM.get_record(vm)
        vm_resident_host_opaque_ref=vm_record["resident_on"]
        vm_resident_host_record=session.xenapi.host.get_record(vm_resident_host_opaque_ref)
        vm_resident_host_name=vm_resident_host_record["name_label"]
        if string.upper(vm_resident_host_name)==string.upper(destn_server_name):
            print "VM on same host... No need of migration..."
            exit(1)
        vm_power_state=string.upper(vm_record["power_state"])
        hosts=session.xenapi.host.get_all()
        for host in hosts:
            host_record=session.xenapi.host.get_record(host)
            host_name=host_record["name_label"]
            if string.upper(host_name)==string.upper(destn_server_name):  
                try:
                    if vm_power_state!="RUNNING":
                        print "A VM can only be migrated if it is in Running state. Check the state of the machine...."
                    else:
                        session.xenapi.VM.pool_migrate(vm,host,{ "live": "true" })
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
    except:
        print "Method not present... Please check the method_name"
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
        