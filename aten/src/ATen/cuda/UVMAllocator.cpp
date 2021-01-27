#include <ATen/cuda/UVMAllocator.h>
#include <ATen/Context.h>
#include <ATen/Config.h>

#include <THC/THC.h>
#include <THC/THCGeneral.hpp>

#include <stdexcept>

namespace at { namespace cuda {

at::Allocator* getUVMAllocator() {
  auto state = globalContext().lazyInitCUDA();
  return state->cudaUVMAllocator;
}

}} // namespace at::cuda
