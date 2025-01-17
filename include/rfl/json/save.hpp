#ifndef RFL_JSON_SAVE_HPP_
#define RFL_JSON_SAVE_HPP_

#include <fstream>
#include <iostream>
#include <string>

#include "rfl/Result.hpp"
#include "rfl/io/save_string.hpp"
#include "rfl/json/write.hpp"

namespace rfl {
namespace json {

template <class T>
Result<Nothing> save(const std::string& _fname, const T& _obj) {
  const auto write_func = [](const auto& _obj, auto& _stream) -> auto& {
    return write(_obj, _stream);
  };
  return rfl::io::save_string(_fname, _obj, write_func);
}

}  // namespace json
}  // namespace rfl

#endif
