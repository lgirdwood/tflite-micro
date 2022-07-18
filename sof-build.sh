#!/bin/bash

# Helper To be executed at top level

# Target can be built with XCC or GCC
TF_TARGET=xtensa_gcc
# uncomment for XCC build
#TF_TARGET=xtensa

# Target ARCH
TF_TARGET_ARCH=xtensa-cnl

TF_LIBS=./tensorflow/lite/micro/tools/make/gen/${TF_TARGET}_${TF_TARGET_ARCH}_default/lib/

# Part 1 - Builds microspeech application.
make -j -f tensorflow/lite/micro/tools/make/Makefile \
	TARGET=${TF_TARGET}  \
	TARGET_ARCH=${TF_TARGET_ARCH} \
	APP=sof \
	micro_speech_lib

# part 2 - take output of part 1 copy test.a to SOF and link SOF to it.

echo "now link test.a to SOF as a module"
exit

# Ranjani - best to use XCC as GCC currently has unresolved symbols in test.a
lrg@sif:~/work/tflite-micro-sof$ xtensa-cnl-elf-nm test.a | grep "U "
         U __adddf3
         U __addsf3
         U __ashldi3
         U calloc
         U close
         U __cxa_atexit
         U __divdf3
         U __divdi3
         U __divsf3
         U __eqdf2
         U __eqsf2
         U __errno
         U __extendsfdf2
         U __fixdfdi
         U __fixdfsi
         U __fixsfsi
         U __fixunssfsi
         U __floatdidf
         U __floatsidf
         U __floatsisf
         U __floatunsisf
         U fputs
         U __gedf2
         U __gesf2
         U __gtdf2
         U __gtsf2
         U _impure_ptr
         U __ledf2
         U __lesf2
         U __lshrdi3
         U __ltdf2
         U __ltsf2
         U memchr
         U memcmp
         U memcpy
         U memmove
         U memset
         U __muldf3
         U __mulsf3
         U __nedf2
         U __nesf2
         U rballoc_align
         U rbrealloc_align
         U rfree
         U rstrcmp
         U rstrlen
         U strtoul
         U __subdf3
         U __subsf3
         U __truncdfsf2
         U _Unwind_DeleteException
         U _Unwind_GetDataRelBase
         U _Unwind_GetIPInfo
         U _Unwind_GetLanguageSpecificData
         U _Unwind_GetRegionStart
         U _Unwind_GetTextRelBase
         U _Unwind_RaiseException
         U _Unwind_Resume
         U _Unwind_Resume_or_Rethrow
         U _Unwind_SetGR
         U _Unwind_SetIP
