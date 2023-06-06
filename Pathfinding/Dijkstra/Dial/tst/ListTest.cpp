//
// Created by korycki on 05.06.2023.
//

#include "gtest/gtest.h"
#include "CircularArray.h"
TEST(ListTest, remove_specified_element) {
    List<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_front(i);
    }
    list.remove_element(3);
    for (int i = 0; i < 9; i++) {
        EXPECT_FALSE(list.get_front() == 3);
        list.remove_front();
    }
    list.push_front(11);
}
