#include"gtest/gtest.h"
#include"id/IdGenerator.h"

class IdGeneratorTest : public ::testing::Test {};

TEST_F(IdGeneratorTest, shouldGenerateID) {
    IdGenerator generator;
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(0).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(1).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(2).value());
}

TEST_F(IdGeneratorTest, shouldCreateGenerator) {
    IdGenerator generator(15);
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(15).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(16).value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(17).value());
}

