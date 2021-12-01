#include"gtest/gtest.h"
#include"IdGenerator.h"

class IdGeneratorTest : public ::testing::Test {
};

TEST_F(IdGeneratorTest, shouldGenerateID) {
    IdGenerator generator;
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(0).value().value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(1).value().value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(2).value().value());
}

TEST_F(IdGeneratorTest, shouldCreateGenerator) {
    IdGenerator generator(15);
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(15).value().value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(16).value().value());
    EXPECT_EQ(generator.GenerateId().value(), TaskId::Create(17).value().value());
}

