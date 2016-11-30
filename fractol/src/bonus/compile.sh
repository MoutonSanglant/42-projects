/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -cl-auto-vectorize-enable -emit-gcl hello.cl

#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple i386-applecl-darwin -emit-llvm-bc -o obj/kernel.cl.i386.bc kernel.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple x86_64-applecl-darwin -emit-llvm-bc -o obj/kernel.cl.x86_64.bc kernel.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple gpu_32-applecl-darwin -emit-llvm-bc -o obj/kernel.cl.gpu_32.bc kernel.cl

clang -c -Os -Wall -arch x86_64 -o obj/hello.cl.o hello.cl.c
clang -c -Os -Wall -arch x86_64 -o obj/hello.o hello.c
clang -framework OpenCL -o hello obj/hello.cl.o obj/hello.o
