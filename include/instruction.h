#pragma once
#include <cstdint>
#include "fileReader.h"
#include <iostream>
#include <string>

namespace Instruction
{
    enum InstructionType
    {
        UNKNOWN = 0,
        ADD,
        SUB,
        MUL,
        DIV,
        LOAD,
        STORE,
        JMP,
        CMP,
        PRINT
    };

    struct Base
    {
        InstructionType instructType;

        Base(InstructionType instructionType = UNKNOWN) : instructType (instructionType){};

        void read(FileReaderBase* fileReader);
    };

    struct Add : public Base
    {
        std::uint32_t param1;
        std::uint32_t param2;

        Add() : Base(InstructionType::ADD){};
        
        void read(FileReaderBase* fileReader);
    };

};