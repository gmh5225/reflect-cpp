#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <source_location>
#include <string>
#include <vector>

#include "write_and_read.hpp"

namespace test_custom_constructor {

struct Person {
  static rfl::Result<Person> from_json_obj(
      typename rfl::json::Reader::InputVarType _obj) {
    /// This only exists for the purpose of the test.
    const auto change_first_name = [](auto&& _person) {
      return rfl::replace(std::move(_person),
                          rfl::Field<"firstName", std::string>("Bart"));
    };
    const auto from_nt = [](auto&& _nt) {
      return rfl::from_named_tuple<Person>(std::move(_nt));
    };
    return rfl::json::read<rfl::named_tuple_t<Person>>(_obj)
        .transform(from_nt)
        .transform(change_first_name);
  }

  rfl::Field<"firstName", std::string> first_name;
  rfl::Field<"lastName", std::string> last_name;
  rfl::Field<"birthday", rfl::Timestamp<"%Y-%m-%d">> birthday;
};

void test() {
  std::cout << std::source_location::current().function_name() << std::endl;

  const auto res = rfl::json::read<Person>(
      R"({"firstName":"Homer","lastName":"Simpson","birthday":"1987-04-19"})");

  if (!res) {
    std::cout << "Test failed on read. Error: " << res.error().value().what()
              << std::endl;
    return;
  }

  if (res.value().first_name() != "Bart") {
    std::cout << "Expected 'Bart', got '" << res.value().first_name() << "'"
              << std::endl
              << std::endl;
  } else {
    std::cout << "OK" << std::endl << std::endl;
  }
}
}  // namespace test_custom_constructor
