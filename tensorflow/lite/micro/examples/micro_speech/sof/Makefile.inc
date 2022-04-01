# Copyright 2020 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(APP), sof)

CC = ${TARGET_TOOLCHAIN_PREFIX}cc
CXX = ${TARGET_TOOLCHAIN_PREFIX}c++
LD = ${TARGET_TOOLCHAIN_PREFIX}ld
AS = ${TARGET_TOOLCHAIN_PREFIX}as
AR = ${TARGET_TOOLCHAIN_PREFIX}ar

# Adding some esp specific files in the main CMakeLists.txt
SOF_MICRO_SPEECH_SRCS := \
tensorflow/lite/micro/examples/micro_speech/sof/audio_provider.cc \
tensorflow/lite/micro/examples/micro_speech/sof/main.cc

#SOF_MICRO_SPEECH_HDRS := \
#tensorflow/lite/micro/examples/micro_speech/sof/audio_provider.hh

CCFLAGS += -Wno-nonnull
CXXFLAGS += -Wno-return-type -Wno-strict-aliasing -Wno-ignored-qualifiers -D__ZEPHYR__

MICRO_SPEECH_SRCS := $(filter-out tensorflow/lite/micro/examples/micro_speech/main.cc ,$(MICRO_SPEECH_SRCS))

MICRO_SPEECH_SRCS += $(SOF_MICRO_SPEECH_SRCS)
#MICRO_SPEECH_HDRS += $(SOF_MICRO_SPEECH_HDRS)

endif
