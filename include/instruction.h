#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include "fileReader.h"

namespace Instruction
{
    enum InstructionType
    {
        UNKNOWN = 0,
        ADD,
        SUB,
        MUL,
        DIV,
        STORE,
        CMP,
        PRINT
    };

    struct Base
    {
        InstructionType instructType;

        Base(InstructionType instructionType = UNKNOWN) : instructType (instructionType){};

        virtual void read(std::shared_ptr<FileReaderBase> fileReader);
    };

    struct Add : public Base
    {
        std::uint32_t param1;
        std::uint32_t param2;

        Add() : Base(InstructionType::ADD){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };
    struct Sub : public Base
    {
        std::uint32_t param1;
        std::uint32_t param2;
        Sub() : Base(InstructionType::SUB){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };
    struct Mul : public Base
    {
        std::uint32_t param1;
        std::uint32_t param2;

        Mul() : Base(InstructionType::MUL){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };
    struct Div : public Base
    {
        std::uint32_t param1;
        std::uint32_t param2;

        Div() : Base(InstructionType::DIV){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };
    struct Store : public Base
    {
        std::uint32_t param1;

        Store() : Base(InstructionType::STORE){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };
    struct Compare : public Base
    
    {
        enum CompareOperand
        {
            Greater = 1,
            Less,
            GreaterEqual,
            LessEqual,
            Equal
        };

        std::uint32_t param1;
        std::uint32_t param2;
        CompareOperand operand;

        Compare() : Base(InstructionType::CMP){};
        
        void read(std::shared_ptr<FileReaderBase> fileReader);
        
    };
    struct Print : public Base
    {
        std::uint32_t size;
        char* printStr;
        
        Print() : Base(InstructionType::PRINT){};
        void read(std::shared_ptr<FileReaderBase> fileReader);
    };

};