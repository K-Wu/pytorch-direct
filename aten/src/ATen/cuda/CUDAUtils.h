#pragma once

#include <ATen/cuda/CUDAContext.h>

namespace at { namespace cuda {

// Check if every tensor in a list of tensors matches the current
// device.
inline bool check_device(ArrayRef<Tensor> ts) {
  if (ts.empty()) {
    return true;
  }
  Device curDevice = Device(kCUDA, current_device());
  for (const Tensor& t : ts) {
//    std::cout << t.device().str() << std::endl;
//    std::cout << t.device().is_unified() << std::endl;
//    std::cout << t.device().is_cuda() << std::endl;
    if (t.device() != curDevice) {
      if (t.device().is_unified() && curDevice.is_cuda())
        continue;
      else
        return false;
    }
  }
  return true;
}

}} // namespace at::cuda
