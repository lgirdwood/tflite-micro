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

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/softmax.h"
#include "tensorflow/lite/micro/micro_context.h"

namespace tflite {

namespace {
// Softmax parameter data that persists in user_data
const int kInt16LUTArraySize = LUTSize<int16_t>();

TfLiteStatus InitializeLutForInt16(TfLiteContext* context,
                                   const TfLiteTensor* input,
                                   TfLiteTensor* output,
                                   SoftmaxParams* op_data) {
  // Only allocate LUTs for KTfLiteInt16 data type
  if (input->type == kTfLiteInt16) {
    void* raw_exp_lut = context->AllocatePersistentBuffer(
        context, sizeof(int16_t) * kInt16LUTArraySize);
    TF_LITE_ENSURE(context, raw_exp_lut != nullptr);
    op_data->exp_lut = reinterpret_cast<int16_t*>(raw_exp_lut);
    void* one_over_one_plus_x_lut = context->AllocatePersistentBuffer(
        context, sizeof(int16_t) * kInt16LUTArraySize);
    TF_LITE_ENSURE(context, one_over_one_plus_x_lut != nullptr);
    op_data->one_over_one_plus_x_lut =
        reinterpret_cast<int16_t*>(one_over_one_plus_x_lut);
  }

  if (output->type == kTfLiteInt16) {
    TF_LITE_ENSURE(context,
                   input->type == kTfLiteInt8 || input->type == kTfLiteInt16);
  } else {
    TF_LITE_ENSURE_EQ(context, input->type, output->type);
  }

  // Populate LUT if required
  if (input->type == kTfLiteInt16) {
    TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);
    // exp LUT only used on negative values
    // we consider exp(-10.0) is insignificant to accumulation
    const int32_t range = std::numeric_limits<int16_t>::max() -
                          std::numeric_limits<int16_t>::min();
    LUTPopulate<int16_t>(
        10.0f / range, std::numeric_limits<int16_t>::max(), 2.0f / range, 0,
        [](float value) { return std::exp(value); }, op_data->exp_lut);

    LUTPopulate<int16_t>(
        1.0f / range, std::numeric_limits<int16_t>::min(), 2.0f / range, 0,
        [](float value) { return 1.0f / (1.0f + value); },
        op_data->one_over_one_plus_x_lut);

    op_data->zero_point = output->params.zero_point;
    op_data->scale = output->params.scale;
  }

  return kTfLiteOk;
}

}  // namespace

TfLiteStatus CalculateSoftmaxParams(TfLiteContext* context,
                                    const TfLiteTensor* input,
                                    TfLiteTensor* output,
                                    const TfLiteSoftmaxParams* params,
                                    SoftmaxParams* op_data) {
  op_data->input_multiplier = 1073741824;
  op_data->input_left_shift = 19;
  op_data->diff_min = -128;
  op_data->zero_point = -128;
  op_data->scale = 1.0f / 256.0f;
  return kTfLiteOk;
}

void* SoftmaxInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(SoftmaxParams));
}

TfLiteStatus SoftmaxPrepare(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TF_LITE_ENSURE(context, input != nullptr);
  TF_LITE_ENSURE(context, NumDimensions(input) >= 1);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE(context, node->user_data != nullptr);
  SoftmaxParams* op_data = static_cast<SoftmaxParams*>(node->user_data);

  auto* params = static_cast<TfLiteSoftmaxParams*>(node->builtin_data);
  auto ret_val =
      CalculateSoftmaxParams(context, input, output, params, op_data);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return ret_val;
}

}  // namespace tflite
