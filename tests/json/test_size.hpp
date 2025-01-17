#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <source_location>
#include <string>
#include <vector>

#include "write_and_read.hpp"

namespace test_size {

struct Person {
  rfl::Rename<"firstName", std::string> first_name;
  rfl::Rename<"lastName", std::string> last_name;
  rfl::Timestamp<"%Y-%m-%d"> birthday;
  rfl::Validator<std::vector<Person>,
                 rfl::Size<rfl::AnyOf<rfl::EqualTo<0>, rfl::EqualTo<3>>>>
      children;
};

void test() {
  std::cout << std::source_location::current().function_name() << std::endl;

  const auto bart = Person{
      .first_name = "Bart", .last_name = "Simpson", .birthday = "1987-04-19"};

  const auto lisa = Person{
      .first_name = "Lisa", .last_name = "Simpson", .birthday = "1987-04-19"};

  const auto maggie = Person{
      .first_name = "Maggie", .last_name = "Simpson", .birthday = "1987-04-19"};

  const auto homer =
      Person{.first_name = "Homer",
             .last_name = "Simpson",
             .birthday = "1987-04-19",
             .children = std::vector<Person>({bart, lisa, maggie})};

  write_and_read(
      homer,
      R"({"firstName":"Homer","lastName":"Simpson","birthday":"1987-04-19","children":[{"firstName":"Bart","lastName":"Simpson","birthday":"1987-04-19","children":[]},{"firstName":"Lisa","lastName":"Simpson","birthday":"1987-04-19","children":[]},{"firstName":"Maggie","lastName":"Simpson","birthday":"1987-04-19","children":[]}]})");
}
}  // namespace test_size
