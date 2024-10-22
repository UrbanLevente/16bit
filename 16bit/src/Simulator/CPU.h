#pragma once
#include  "Memory.h"

class CPU {
public:	
	CPU();
	~CPU();

	void Step(int amount);

	inline int getPC() { return m_PC; }

private:
	int m_opcode;

	int m_PC;

	Memory* m_memory = nullptr;

	int m_registerA;
	int m_registerB;


	void NOP();

};