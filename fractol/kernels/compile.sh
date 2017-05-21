/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -cl-auto-vectorize-disable -emit-gcl mandelbrot.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -Os -arch x86_64 -emit-llvm-bc kernel.cl -o obj/kernel.cl.o

#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -triple x86_64-applecl-darwin -triple gpu_32-applecl-darwin -cl-auto-vectorize-disable -emit-gcl kernel.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -cl-auto-vectorize-enable hello.cl -v

#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple i386-applecl-darwin -emit-llvm-bc -o obj/hello.cl.i386.bc hello.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple x86_64-applecl-darwin -emit-llvm-bc -o obj/hello.cl.x86_64.bc hello.cl
#/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple gpu_32-applecl-darwin -emit-llvm-bc -o obj/hello.cl.gpu_32.bc hello.cl

#clang -S -emit-llvm -o kernel.ll -x cl kernel.cl
