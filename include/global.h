#pragma once 
#include "instruction.h"
#include "ringBuffer.h"

using InstructionRingBuffer1024 = RingBuffer<std::shared_ptr<Instruction::Base>, 1024>;

using InstructionRingBuffer1KPtr = std::shared_ptr<InstructionRingBuffer1024>;

using IFStreamUPtr = std::unique_ptr<std::ifstream>;