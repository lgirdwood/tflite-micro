# Settings for GCC Xtensa toolchain for the standard kernels.

#TARGET_ARCH :=

PLATFORM_FLAGS = \
  -DTF_LITE_MCU_DEBUG_LOG \
  -DTF_LITE_USE_CTIME \
  -DXTENSA \
  -DNDEBUG \
  -DTF_LITE_STRIP_ERROR_STRINGS

#  -DMAX_RFFT_PWR=9
# -DMIN_RFFT_PWR=MAX_RFFT_PWR

TARGET_TOOLCHAIN_PREFIX := $(TARGET_ARCH)-elf-
CXX_TOOL := c++
CC_TOOL := cc

CXXFLAGS = -O2 $(PLATFORM_ARGS) -std=c++11 $(TF_LITE_MICRO_FLAGS)
#TODO: Use -std=c11 ?
CCFLAGS = -O2 $(PLATFORM_ARGS) $(TF_LITE_MICRO_FLAGS)

# TODO(b/150240249): Do not remove -fno-rtti once that works for the Xtensa toolchain.
CXXFLAGS := $(filter-out -fno-rtti, $(CXXFLAGS))

TEST_SCRIPT := tensorflow/lite/micro/testing/test_xtensa_binary.sh

# TODO(b/156962140): This manually maintained list of excluded examples is
# quite error prone.
EXCLUDED_EXAMPLE_TESTS := \
  tensorflow/lite/micro/examples/image_recognition_experimental/Makefile.inc \
  tensorflow/lite/micro/examples/magic_wand/Makefile.inc \
  tensorflow/lite/micro/examples/network_tester/Makefile.inc \
  tensorflow/lite/micro/examples/person_detection/Makefile.inc \
  tensorflow/lite/micro/examples/person_detection_experimental/Makefile.inc
MICRO_LITE_EXAMPLE_TESTS := $(filter-out $(EXCLUDED_EXAMPLE_TESTS), $(MICRO_LITE_EXAMPLE_TESTS))
