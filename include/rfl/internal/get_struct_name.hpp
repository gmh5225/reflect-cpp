#ifndef RFL_INTERNAL_GETSTRUCTNAME_HPP_
#define RFL_INTERNAL_GETSTRUCTNAME_HPP_

#include <iostream>
#include <source_location>
#include <string>

namespace rfl {
namespace internal {

std::string remove_namespaces(const std::string& _name) {
  const size_t pos = _name.find_last_of(":");
  if (pos == std::string::npos) {
    return _name;
  }
  return _name.substr(pos + 1);
}

template <class T>
std::string get_struct_name_impl() {
  const std::string func_name = std::source_location::current().function_name();
  const size_t begin = func_name.find("T = ") + 4;
  if (begin == std::string::npos) {
    return "AnonymousStruct";
  }
  const size_t end = func_name.find_first_of("])};", begin);
  if (end == std::string::npos) {
    return "AnonymousStruct";
  }
  return remove_namespaces(func_name.substr(begin, end - begin));
}

template <class T>
std::string get_struct_name() {
  return get_struct_name_impl<std::decay_t<std::remove_pointer_t<T>>>();
}

}  // namespace internal
}  // namespace rfl

#endif
