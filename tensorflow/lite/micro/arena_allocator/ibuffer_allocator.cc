/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/arena_allocator/ibuffer_allocator.h"

namespace tflite {

static volatile int g_ibuf_alloc_anchor_0 = 0x11112222;
static volatile int g_ibuf_alloc_anchor_1 = 0x33334444;
static volatile int g_ibuf_alloc_anchor_2 = 0x55556666;
static volatile int g_ibuf_alloc_anchor_3 = 0x77778888;
static volatile int g_ibuf_alloc_anchor_4 = 0x9999aaaa;

IBufferAllocator::IBufferAllocator() { g_ibuf_alloc_anchor_0 = 1; }
IBufferAllocator::~IBufferAllocator() { g_ibuf_alloc_anchor_0 = 2; }

uint8_t* IBufferAllocator::AllocatePersistentBuffer(
    size_t size, size_t alignment) {
  g_ibuf_alloc_anchor_1 = (int)size;
  return nullptr;
}

size_t IBufferAllocator::GetPersistentUsedBytes() const {
  return g_ibuf_alloc_anchor_1;
}

uint8_t* IBufferAllocator::AllocateTemp(size_t size,
                                        size_t alignment) {
  g_ibuf_alloc_anchor_2 = (int)size;
  return nullptr;
}

void IBufferAllocator::DeallocateTemp(uint8_t* buf) {
  g_ibuf_alloc_anchor_2 = (int)(uintptr_t)buf;
}

bool IBufferAllocator::IsAllTempDeallocated() {
  return g_ibuf_alloc_anchor_2 == 0;
}

TfLiteStatus IBufferAllocator::ResetTempAllocations() {
  g_ibuf_alloc_anchor_3 = 1;
  return kTfLiteOk;
}

uint8_t* IBufferAllocator::AllocateResizableBuffer(
    size_t size, size_t alignment) {
  g_ibuf_alloc_anchor_3 = (int)size;
  return nullptr;
}

TfLiteStatus IBufferAllocator::ResizeBuffer(
    uint8_t* resizable_buf, size_t size, size_t alignment) {
  g_ibuf_alloc_anchor_4 = (int)size;
  return kTfLiteError;
}

TfLiteStatus IBufferAllocator::DeallocateResizableBuffer(
    uint8_t* resizable_buf) {
  g_ibuf_alloc_anchor_4 = (int)(uintptr_t)resizable_buf;
  return kTfLiteOk;
}

uint8_t* IBufferAllocator::GetOverlayMemoryAddress() const {
  return nullptr;
}

TfLiteStatus IBufferAllocator::ReserveNonPersistentOverlayMemory(
    size_t size, size_t alignment) {
  g_ibuf_alloc_anchor_4 = 5;
  return kTfLiteOk;
}

size_t IBufferAllocator::GetNonPersistentUsedBytes() const {
  return g_ibuf_alloc_anchor_4;
}

size_t IBufferAllocator::GetAvailableMemory(
    size_t alignment) const {
  return g_ibuf_alloc_anchor_0;
}

}  // namespace tflite
