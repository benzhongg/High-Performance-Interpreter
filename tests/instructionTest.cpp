#include <gtest/gtest.h>
#include "instructionBuilder.h"
#include "injector.h"
#include "interpreter.h"
#include "fileReader.h"

class MockIB
{
private:
    std::shared_ptr<FileReaderBase> m_fileReader { nullptr };
    InstructionBuilder m_instructionBuilder { m_fileReader };
    std::shared_ptr<Instruction::Base> m_resultInstruction { nullptr };

public:
    MockIB(const char* buffer, size_t size)
    {
        m_fileReader = std::make_shared<BufferFileReader>(buffer, size);
        m_instructionBuilder = InstructionBuilder(m_fileReader);
    }

    void createInstruction()
    {
        m_resultInstruction = m_instructionBuilder.get_instruction();
    }

    bool resultCheck(Instruction::InstructionType targetType)
    {
        return m_resultInstruction->instructType == targetType;
    }
};

TEST(CreateAddInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 12);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::ADD), true);
}

TEST(CreateSubInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 12);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::SUB), true);
}

TEST(CreateMulInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 12);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::MUL), true);
}

TEST(CreateDivInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0, 0x01, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 12);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::DIV), true);
}

TEST(CreateStoreInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 8);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::STORE), true);
}

TEST(CreateCompareInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockIB testInstance(buffer, 16);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::CMP), true);
}

TEST(CreatePrintInstruction, SuccessfulConstruction)
{
    char buffer[] = {0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64};
    MockIB testInstance(buffer, 18);
    testInstance.createInstruction();
    ASSERT_EQ(testInstance.resultCheck(Instruction::InstructionType::PRINT), true);
}