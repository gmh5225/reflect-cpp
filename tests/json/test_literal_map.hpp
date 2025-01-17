#include <iostream>
#include <map>
#include <memory>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <source_location>
#include <string>
#include <unordered_map>

#include "write_and_read.hpp"

namespace test_literal_map {

using FieldName = rfl::Literal<"firstName", "lastName">;

void test() {
  std::cout << std::source_location::current().function_name() << std::endl;

  std::map<FieldName, std::unique_ptr<std::string>> homer;
  homer.insert(std::make_pair(FieldName::make<"firstName">(),
                              std::make_unique<std::string>("Homer")));
  homer.insert(std::make_pair(FieldName::make<"lastName">(),
                              std::make_unique<std::string>("Simpson")));

  write_and_read(homer, R"({"firstName":"Homer","lastName":"Simpson"})");
}
}  // namespace test_literal_map
