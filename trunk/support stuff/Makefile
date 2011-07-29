libVMController.so: ./XENVMUtil.o ./VMUtilfactory.o
	g++ -shared -Wl,-soname,libVMController.so.1 -o libVMController.so.1.0.1 XENVMUtil.o VMUtilfactory.o
	ln -s libVMController.so.1.0.1 libVMController.so.1
	ln -s libVMController.so.1 libVMController.so

XENVMUtil.o: ./source/XENVMUtil.cpp ./include/XENVMUtil.h ./include/VMUtil.h
	g++ -c -fPIC ./source/XENVMUtil.cpp -I./include -o XENVMUtil.o

VMUtilfactory.o: ./source/VMUtilfactory.cpp ./include/VMUtilfactory.h ./include/VMUtil.h ./include/XENVMUtil.h
	g++ -c -fPIC ./source/VMUtilfactory.cpp -I./include -o VMUtilfactory.o

