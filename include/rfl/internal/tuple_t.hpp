#ifndef RFL_INTERNAL_TUPLE_T_HPP_
#define RFL_INTERNAL_TUPLE_T_HPP_

#include <functional>
#include <tuple>
#include <type_traits>

#include "rfl/internal/ptr_tuple_t.hpp"
#include "rfl/internal/remove_ptrs_tup.hpp"
#include "rfl/to_named_tuple.hpp"

namespace rfl {
namespace internal {

template <class T>
using tuple_t = typename remove_ptrs_tup<ptr_tuple_t<T>>::TupleType;

}  // namespace internal
}  // namespace rfl

#endif
