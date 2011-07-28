libXENVMController.so: ./XENVMUtil.o
	g++ -shared -Wl,-soname,libXENVMController.so.1 -o libXENVMController.so.1.0.1 XENVMUtil.o
	ln -s libXENVMController.so.1.0.1 libXENVMController.so.1
	ln -s libXENVMController.so.1 libXENVMController.so

XENVMUtil.o: ./src/XENVMUtil.cpp ./include/XENVMUtil.h ./include/VMUtil.h
	g++ -c -fPIC ./src/XENVMUtil.cpp -I./include -o XENVMUtil.o


