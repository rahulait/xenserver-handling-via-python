'''
Created on Jul 11, 2011

@author: WAH WAH
'''
import sys, string, time

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
                    print "Error occurred: %s" % err
                
    def vm_snapshot(self,session,vm,snapshot_name):
        try:
            snapshot_name_with_time=snapshot_name + " " + time.asctime()
            session.xenapi.VM.snapshot(vm,snapshot_name_with_time)
            print "Snapshot \"%s\" generated successfully......" % snapshot_name_with_time
        except XenAPI.Failure as err:
            print "Error occurred in generating snapshot. Error message is:: %s" % err
            
    
    def vm_clone(self,session,vm,newvm_name):
        try:
            record=session.xenapi.VM.get_record(vm)
            powerstate=string.upper(record["power_state"])
            if(powerstate!="HALTED"):
                print "Only VM in Halted state can be cloned.... Check the state of the specified VM....."
            else:
                session.xenapi.VM.clone(vm,newvm_name)
                print "VM cloned successfully....."
        except XenAPI.Failure as err:
            print "Error occurred in cloning the VM. Error message given by XEN is:: %s" % err
            
                    
    def vm_from_template(self,session,vm,newvm_name):
        try:
            new_vm_ref=session.xenapi.VM.clone(vm,newvm_name)
            session.xenapi.VM.provision(new_vm_ref)
            print "VM from Template created successfully......"
        except XenAPI.Failure as err:
            print "Error occurred in creating VM from template. Error message given by XEN is:: %s" % err
            
    
    def vm_to_template(self,session,vm):
        try:
            session.xenapi.VM.set_is_a_template(vm,True)
            print "VM converted to Template successfully......"
        except XenAPI.Failure as err:
            print "Error occurred in converting VM to template. Error message given by XEN is:: %s" % err
    
    
    def vm_create(self,session,destn_server,storage_name,vm_name,memory,CPUs_max,disk_name,disk_size,network_name):
        try:
            hh=session.xenapi.host.get_by_name_label(destn_server)
            record_hh=session.xenapi.host.get_record(hh[0])
            host_pbds=record_hh["PBDs"]
            for p in host_pbds:
                aa=session.xenapi.SR.get_by_name_label(storage_name)
                for a in aa:
                    record=session.xenapi.SR.get_record(a)
                    pp=record["PBDs"]
                    for px in pp:
                        if p==px:
                            platfrm={}
                            vmprop={'name_label':vm_name,
                                    'name_description':"",
                                    'user_version':"1",
                                    'affinity':"",
                                    'is_a_template':False,
                                    'auto_power_on':False,
                                    'memory_static_max':memory,
                                    'memory_static_min':memory,
                                    'memory_dynamic_max':memory,
                                    'memory_dynamic_min':memory,
                                    'VCPUs_max':CPUs_max,
                                    'VCPUs_at_startup':CPUs_max,
                                    'VCPUs_params':{},
                                    'actions_after_shutdown':"destroy",
                                    'actions_after_reboot':"restart",
                                    'actions_after_crash':"restart",
                                    'PV_kernel':"",
                                    'PV_ramdisk':"",
                                    'PV_bootloader':"",
                                    'PV_bootloader_args':"",
                                    'PV_legacy_args':"",
                                    'HVM_boot_policy':"BIOS order",  #to get the boot order for starting the VM. This is important...
                                    'HVM_boot_params':{'order':'dc'},
                                    'platform':platfrm,
                                    'PCI_bus':"",
                                    'other_config':{},
                                    'recommendations':"",
                                    'PV_args':""}
                            VM_ref=session.xenapi.VM.create(vmprop)
                            vdisk={'name_label':disk_name,
                                   'name_description':"",
                                   'SR':a,
                                   'virtual_size':disk_size,
                                   'type':"user",
                                   'sharable':True,
                                   'read_only':True,
                                   'other_config':{}}
                            vdi_ref=session.xenapi.VDI.create(vdisk)
                            vbdconnect={'VDI':vdi_ref,
                                        'VM':VM_ref,
                                        'userdevice':"0",
                                        'mode':"RW",
                                        'type':"Disk",
                                        'bootable':True,
                                        'unpluggable':True,
                                        'empty':False,
                                        'other_config':{},
                                        'qos_algorithm_type':'',
                                        'qos_algorithm_params':{}}
                            vbdref=session.xenapi.VBD.create(vbdconnect)
                            srs=session.xenapi.SR.get_by_name_label("DVD drives")
                            flag_dvd_present=0
                            for sr in srs:
                                record_dvd=session.xenapi.SR.get_record(sr)
                                pbd=record_dvd["PBDs"]
                                for pbd_h in host_pbds:
                                    if pbd[0]==pbd_h:
                                        VDI_dvd=record_dvd["VDIs"]
                                        vbdconnectcd={'VDI':VDI_dvd[0],
                                                      'VM':VM_ref,
                                                      'userdevice':"1",
                                                      'mode':"RO",
                                                      'type':"cd",
                                                      'bootable':True,
                                                      'unpluggable':True,
                                                      'empty':False,
                                                      'other_config':{},
                                                      'qos_algorithm_type':'',
                                                      'qos_algorithm_params':{}}
                                        vbdref1=session.xenapi.VBD.create(vbdconnectcd)
                                        flag_dvd_present=1
                                        break
                                if flag_dvd_present==1:
                                    break
                            if flag_dvd_present==0:
                                print "DVD Drive with specified name not found... So it can't be attached to the VM...."

                            networks=session.xenapi.network.get_all()
                            for NETWORK_ref in session.xenapi.network.get_all():
                                NETWORK_label = session.xenapi.network.get_name_label(NETWORK_ref)
                                if NETWORK_label == network_name:
                                    nic_det={'device':"0",
                                             'network':NETWORK_ref,
                                             'VM':VM_ref,
                                             'MAC':"",
                                             'MTU':'1500',
                                             'other_config':{},
                                             'qos_algorithm_type':"",
                                             'qos_algorithm_params':{}}
                                    vif=session.xenapi.VIF.create(nic_det)
                                    break
            print "VM Created successfully......"
        except XenAPI.Failure as err:
            print "Error occurred in creating VM. Error message given by XEN is:: %s" % err
                    
if __name__ == "__main__":

    if len(sys.argv) < 6:
        print "Usage:"
        print sys.argv[0], " <url> <username> <password> <operations> <vmname> <list of other parameters which are not mandatory for some functions>"
        sys.exit(1)
    url = sys.argv[1]
    username = sys.argv[2]
    password = sys.argv[3]
    operation=sys.argv[4]
    objcommands=commands()
    fxnattr=0
    try:
        fxnattr=getattr(objcommands,operation)
        session=XenAPI.Session(url)
        session.xenapi.login_with_password(username,password)
        vms=session.xenapi.VM.get_all()
        isvmthere=0
        vm=0
        if string.upper(operation)!="VM_CREATE":  
            for vm in vms:
                record=session.xenapi.VM.get_record(vm)
                if not(record["is_a_template"]) and not(record["is_control_domain"]):
                    vmname=sys.argv[5]
                    name =record["name_label"]
                    if string.upper(name)==string.upper(vmname):
                        xx=session.xenapi.VM.get_by_name_label(name)
                        i=0
                        while i<len(xx):
                            #bb=session.xenapi.VM.get_resident_on(xx[i])
                            #hostrec=session.xenapi.host.get_record(bb)
                            #hostname=hostrec["hostname"]
                            #if string.upper(hostname)==string.upper(servername):
                            if string.upper(operation)!="VM_MIGRATE" and string.upper(operation)!="VM_SNAPSHOT" and string.upper(operation)!="VM_CLONE":
                                fxnattr(session,vm)  #this is to be indented with the above if statements.. now they are disabled, so it is not indented with them....
                                isvmthere=1          #this also needed to be indented....
                            elif string.upper(operation)=="VM_SNAPSHOT":
                                snapshot_name=sys.argv[6]
                                fxnattr(session,vm,snapshot_name)
                                isvmthere=1
                            elif string.upper(operation)=="VM_CLONE":
                                newvm_name=sys.argv[6]
                                fxnattr(session,vm,newvm_name)
                                isvmthere=1
                            elif string.upper(operation)=="VM_TO_TEMPLATE":
                                fxnattr(session,vm)
                                isvmthere=1
                            else:
                                servername=sys.argv[6]
                                fxnattr(session,vm,servername)
                                isvmthere=1
                            i=i+1
                
                elif (record["is_a_template"]==True):
                    template_name=sys.argv[5]
                    name=record["name_label"]
                    if string.upper(name)==string.upper(template_name):
                        xx=session.xenapi.VM.get_by_name_label(name)
                        i=0
                        while i<len(xx):
                            if string.upper(operation)=="VM_FROM_TEMPLATE":
                                newvm_name=sys.argv[6]
                                fxnattr(session,vm,newvm_name)
                                isvmthere=1
                            i=i+1
                    
            if isvmthere==0:
                print "VM not present!!!! Check whether you provided the correct input...."
        else:
            destn_server=sys.argv[5]
            storage_name=sys.argv[6]
            vm_name=sys.argv[7]
            memory=sys.argv[8]
            CPUs_max=sys.argv[9]
            disk_name=sys.argv[10]
            disk_size=sys.argv[11]
            network_name=sys.argv[12]
            fxnattr(session,destn_server,storage_name,vm_name,memory,CPUs_max,disk_name,disk_size,network_name)
        session.xenapi.logout()
    except AttributeError:
        print "Method not present... Please check the method_name" 
    except XenAPI.Failure:
        print "Error occurred..... Check the supplied values......"
        