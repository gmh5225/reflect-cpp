#include <cassert>
#include <iostream>
#include <rfl.hpp>
#include <rfl/flexbuf.hpp>
#include <source_location>
#include <string>
#include <vector>

#include "write_and_read.hpp"

namespace test_unique_ptr2 {

struct DecisionTree {
  struct Leaf {
    rfl::Field<"value", double> value;
  };

  struct Node {
    rfl::Field<"criticalValue", double> critical_value;
    rfl::Field<"left", std::unique_ptr<DecisionTree>> lesser;
    rfl::Field<"right", std::unique_ptr<DecisionTree>> greater;
  };

  using LeafOrNode = rfl::TaggedUnion<"type", Leaf, Node>;

  rfl::Field<"leafOrNode", LeafOrNode> leaf_or_node;
};

void test() {
  std::cout << std::source_location::current().function_name() << std::endl;

  auto leaf1 = DecisionTree::Leaf{.value = 3.0};

  auto leaf2 = DecisionTree::Leaf{.value = 5.0};

  auto node = DecisionTree::Node{
      .critical_value = 10.0,
      .lesser = std::make_unique<DecisionTree>(DecisionTree{leaf1}),
      .greater = std::make_unique<DecisionTree>(DecisionTree{leaf2})};

  const DecisionTree tree{.leaf_or_node = std::move(node)};

  write_and_read(tree);
}
}  // namespace test_unique_ptr2
