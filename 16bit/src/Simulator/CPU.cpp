#include <pch.h>
#include "CPU.h"
#include "Memory.h"

CPU::CPU()
	: m_opcode(0), m_PC(0), m_registerA(0), m_registerB(0) {

	m_memory = new Memory(100);

}

CPU::~CPU() {
	delete m_memory;
}

void CPU::Step(int amount) {
	if (m_opcode < 101) {
		// Ensure PC is within the bounds of the memory
		if (m_PC >= 0 && m_PC < m_memory->getSize()) {
			m_memory->setMAR(m_PC);
			m_opcode = m_memory->read();

			switch (m_opcode) {
			case 0:
				NOP();
				break;
			default:
				break;
			}
		} else {
			return;
		}
	}
}

void CPU::NOP() {
	std::cout << "Instruction NOP" << std::endl;
	m_PC++;
}