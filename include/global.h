#pragma once 
#include "instruction.h"
#include "ringBuffer.h"

using InstructionRingBuffer1024 = RingBuffer<std::shared_ptr<Instruction::Base>, 1024>;