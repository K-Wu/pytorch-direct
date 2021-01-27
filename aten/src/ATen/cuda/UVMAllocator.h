#pragma once

#include <c10/core/Allocator.h>

namespace at { namespace cuda {

TORCH_CUDA_CPP_API at::Allocator* getUVMAllocator();
}} // namespace at::cuda
