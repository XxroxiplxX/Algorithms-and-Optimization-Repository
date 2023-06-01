//
// Created by korycki on 29.05.2023.
//

#include "gtest/gtest.h"
#include "DirectedGraph.h"
#include "CircularArray.h"

class CircularArrayTest : public ::testing::Test {
public:
    CircularArray<Vertex*> uut;
    List<Vertex*> uut2;
};
TEST_F(CircularArrayTest, CircularArray_utils) {
    uut = CircularArray<Vertex*>(6);
    EXPECT_TRUE(uut.empty(0));
    uut.set_element(new Vertex(3), 5);
    uut.set_element(new Vertex(8), 5);
    uut.set_element(new Vertex(9), 5);
    EXPECT_EQ(9, uut.get_element(5)->id);

EXPECT_EQ(3, uut.get_ful_size());
    EXPECT_FALSE(uut.empty(5));
    uut.delete_element(5);
    uut.delete_element(5);
    uut.delete_element(5);
    EXPECT_TRUE(uut.empty(0));
}
TEST_F(CircularArrayTest, List_utils) {
    uut2.

push_front(new Vertex(5));
    uut2.

push_front(new Vertex(6));

EXPECT_EQ(2, uut2.get_size());
}