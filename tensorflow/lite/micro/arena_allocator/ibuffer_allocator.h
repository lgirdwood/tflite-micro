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
#ifndef TENSORFLOW_LITE_MICRO_ARENA_ALLOCATOR_IBUFFER_ALLOCATOR_H_
#define TENSORFLOW_LITE_MICRO_ARENA_ALLOCATOR_IBUFFER_ALLOCATOR_H_

#include <cstddef>
#include <cstdint>

#include "tensorflow/lite/c/c_api_types.h"

namespace tflite {
// Interface classes that the TFLM framework relies on to get buffers it needs.
// There are two types of buffers that the TFLM framework requires: persistent
// and non-persistent. Persistent buffers, once allocated, are never freed by
// the TFLM framework. Non-persist buffers can be allocated and deallocated by
// the TFLM framework. This file defines two interfaces classes that TFLM
// framework will rely on to manage these buffers.

// Single interface class for managing persistent and non-persistent buffers.
class IBufferAllocator {
 public:
  IBufferAllocator();
  virtual ~IBufferAllocator();

  // Allocates persistent memory. The persistent buffer is never freed.
  virtual uint8_t* AllocatePersistentBuffer(size_t size, size_t alignment);

  // Returns the size of all persistent allocations in bytes.
  virtual size_t GetPersistentUsedBytes() const;

  // Allocates a temporary buffer. This buffer is not resizable.
  virtual uint8_t* AllocateTemp(size_t size, size_t alignment);

  // Signals that a temporary buffer is no longer needed.
  virtual void DeallocateTemp(uint8_t* buf);

  // Returns true if all temporary buffers are already deallocated.
  virtual bool IsAllTempDeallocated();

  // Signals that all temporary allocations can be reclaimed.
  virtual TfLiteStatus ResetTempAllocations();

  // Returns a buffer that is resizable viable ResizeBuffer().
  virtual uint8_t* AllocateResizableBuffer(size_t size, size_t alignment);

  // Resizes a buffer that is previously returned by AllocateResizableBuffer.
  virtual TfLiteStatus ResizeBuffer(uint8_t* resizable_buf, size_t size,
                                    size_t alignment);

  // Frees up the memory occupied by the resizable buffer.
  virtual TfLiteStatus DeallocateResizableBuffer(uint8_t* resizable_buf);

  // Returns a pointer pointing to the start of the overlay memory.
  virtual uint8_t* GetOverlayMemoryAddress() const;

  // Reserves the size of the overlay memory.
  virtual TfLiteStatus ReserveNonPersistentOverlayMemory(size_t size,
                                                         size_t alignment);

  // Returns the size of non-persistent buffer in use.
  virtual size_t GetNonPersistentUsedBytes() const;

  // Returns the number of bytes available with a given alignment.
  virtual size_t GetAvailableMemory(size_t alignment) const;
};

using IPersistentBufferAllocator = IBufferAllocator;
using INonPersistentBufferAllocator = IBufferAllocator;

}  // namespace tflite

#endif  // TENSORFLOW_LITE_MICRO_ARENA_ALLOCATOR_IBUFFER_ALLOCATOR_H_
