#include"gtest/gtest.h"
#include"Validator.h"

class ValidatorTest : public ::testing::Test {
};

TEST_F(ValidatorTest, shouldConvertStringToTime) {
    EXPECT_EQ(StringToTime("23:00 11/11/2021"), 1636664400);
    EXPECT_EQ(StringToTime("11:00 3/5/2022"), 1651568400);
    EXPECT_EQ(StringToTime("10:12 7/7/2025"), 1751875920);
    EXPECT_EQ(StringToTime("15:15 4/4/1990"), 639231300);
    EXPECT_THROW(StringToTime("25:00 3/5/1970"), std::runtime_error);
    EXPECT_THROW(StringToTime("23:00 40/13/1979"), std::runtime_error);
}
