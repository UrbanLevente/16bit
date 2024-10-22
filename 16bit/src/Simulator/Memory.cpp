#include "Memory.h"

Memory::Memory(int size) : m_MAR(0) {

	m_Memory.resize(size);

}

Memory::~Memory() {}

int Memory::read() {
	return m_Memory[m_MAR];
}

void Memory::write(int data) {
	m_Memory[m_MAR] = data;
}
