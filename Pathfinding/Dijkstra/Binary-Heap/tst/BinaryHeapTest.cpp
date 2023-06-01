//
// Created by korycki on 27->05->2023->
//
#include "gtest/gtest.h"
#include "BinaryHeap.h"

class BinaryHeapTest : public ::testing::Test {
public:
    BinaryHeap* uut;
    BinaryHeapTest() {
        uut = new BinaryHeap(1024);
    }
};

TEST_F(BinaryHeapTest, BinaryHeap_utils) {
    auto u = new Vertex(2,6);
    uut->insert_key(new Vertex(1,7));
    uut->insert_key(u);
    uut->insert_key(new Vertex(3,12));
    uut->insert_key(new Vertex(4, 100));
    uut->insert_key(new Vertex(5,-100));
    uut->insert_key(new Vertex(6, 18));
    uut->insert_key(new Vertex(7, 13));

    EXPECT_EQ(7, uut->get_size());
    EXPECT_EQ(-100, uut->extract_min()->dist);

    EXPECT_EQ(6, uut->check_min());
    u->dist = 150;
    uut->heapify(0);
    EXPECT_EQ(7, uut->extract_min()->dist);
    delete uut;
}
TEST_F(BinaryHeapTest, sorting) {

    auto source = new Vertex(9,INT_MAX);

    for (int i = 1; i <= 12; i++) {
        if (i != 9) {
            uut->insert_key(new Vertex(i,INT_MAX));
        } else {
            uut->insert_key(source);
        }
    }
    uut->print_heap_unordered();
    uut->decrease_key(source, 0);
    uut->print_heap_unordered();
    EXPECT_EQ(0, uut->extract_min()->dist);
}