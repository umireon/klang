#include "CppUTest/TestHarness.h"

extern "C" int add(int, int);

TEST_GROUP(Add)
{
};

TEST(Add, Simple)
{
    CHECK_EQUAL(5, add(2, 3));
};

