#pragma once
#include <pch.h>

class Memory {
public:
	Memory(int size);
	~Memory();

	int read();
	void write(int data);

	inline int getMAR() { return m_MAR; }
	inline void setMAR(int data) { m_MAR = data; }
	inline int getSize() const { return m_Memory.size(); }

private:
	std::vector<int> m_Memory;
	int m_MAR;
};