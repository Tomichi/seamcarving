#include "gtest/gtest.h"
#include "Graph/SimpleGraph.h"

TEST(getVertices, test1) {
    auto simpleGraph = SimpleGraph(10, 0);

    EXPECT_EQ (simpleGraph.getVertices(),  10);
}
