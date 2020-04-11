#include "RegisterFile.hpp"

void RegisterFile::save_state(std::ofstream& file)
{
	file.write(reinterpret_cast<char*>(stage_1_registers), sizeof(unsigned int) * 32);
	file.write(reinterpret_cast<char*>(stage_2_registers), sizeof(unsigned int) * 32);
	file.write(reinterpret_cast<char*>(stage_3_registers), sizeof(unsigned int) * 32);
}

void RegisterFile::load_state(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(stage_1_registers), sizeof(unsigned int) * 32);
	file.read(reinterpret_cast<char*>(stage_2_registers), sizeof(unsigned int) * 32);
	file.read(reinterpret_cast<char*>(stage_3_registers), sizeof(unsigned int) * 32);
}

void RegisterFile::reset()
{
	for (int idx = 0; idx < 32; idx++)
	{
		stage_1_registers[idx] = 0;
		stage_2_registers[idx] = 0;
		stage_3_registers[idx] = 0;
	}
}

void RegisterFile::tick()
{
	memcpy(&stage_3_registers, &stage_2_registers, sizeof(unsigned int) * 32);
	memcpy(&stage_2_registers, &stage_1_registers, sizeof(unsigned int) * 32);
}

unsigned int RegisterFile::get_register(unsigned int index)
{
	return stage_3_registers[index];
}

void RegisterFile::set_register(unsigned int index, unsigned int value, bool load_delay)
{
	if (index != 0)
	{
		if (load_delay)
		{
			stage_1_registers[index] = value;
		}
		else
		{
			stage_1_registers[index] = stage_2_registers[index] = stage_3_registers[index] = value;
		}
	}
}