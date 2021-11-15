#include"gtest/gtest.h"
#include"../../../src/model/id/IdGenerator.h"

class IdGeneratorTest : public ::testing::Test {};

TEST_F(IdGeneratorTest, shouldGenerateID) {
    IdGenerator generator;
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(0).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(1).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(2).value());
}

