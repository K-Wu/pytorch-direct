#include <ATen/detail/UnifiedGuardImpl.h>

namespace at {
namespace detail {

C10_REGISTER_GUARD_IMPL(Unified, UnifiedGuardImpl);

}} // namespace at::detail
