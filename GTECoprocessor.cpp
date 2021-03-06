#include <stdexcept>
#include <fstream>

#include "GTECoprocessor.hpp"
#include "InstructionTypes.hpp"
#include "InstructionEnums.hpp"
#include "Cpu.hpp"
#include "Bus.hpp"

static GTECoprocessor * instance = nullptr;

GTECoprocessor * GTECoprocessor::get_instance()
{
	if (instance == nullptr)
	{
		instance = new GTECoprocessor();
	}

	return instance;
}

void GTECoprocessor::save_state(std::stringstream& file)
{
	file.write(reinterpret_cast<char*>(&control_registers[0]), sizeof(unsigned int) * 32);
	file.write(reinterpret_cast<char*>(&data_registers[0]), sizeof(unsigned int) * 32);
}

void GTECoprocessor::load_state(std::stringstream& file)
{
	file.read(reinterpret_cast<char*>(&control_registers[0]), sizeof(unsigned int) * 32);
	file.read(reinterpret_cast<char*>(&data_registers[0]), sizeof(unsigned int) * 32);
}

void GTECoprocessor::execute(const instruction_union& instruction)
{
	switch (static_cast<cpu_instructions>(instruction.immediate_instruction.op))
	{
		case cpu_instructions::LWC2:
		{
			load_word_to_cop(instruction);
		} return;

		case cpu_instructions::SWC2:
		{
			store_word_from_cop(instruction);
		} return;
	}

	
	if (instruction.immediate_instruction.op == 0b0100101)
	{
		move_control_to_cop_fun(instruction);
		return;
	}

	copz_instructions function = static_cast<copz_instructions>(instruction.register_instruction.rs);
	switch (function) {
		case copz_instructions::MF:
		{
			move_from_cop(instruction);
		} break;

		case copz_instructions::CF:
		{
			move_control_from_cop(instruction);
		} break;

		case copz_instructions::MT:
		{
			move_to_cop(instruction);
		} break;

		case copz_instructions::CT:
		{
			move_control_to_cop(instruction);
		} break;
	}
}

unsigned int GTECoprocessor::get_data_register(unsigned int index)
{
	return data_registers[index];
}

void GTECoprocessor::set_data_register(unsigned int index, unsigned int value)
{
	data_registers[index] = value;
}

unsigned int GTECoprocessor::get_control_register(unsigned int index)
{
	return control_registers[index];
}

void GTECoprocessor::set_control_register(unsigned int index, unsigned int value)
{
	control_registers[index] = value;
}

void GTECoprocessor::load_word_to_cop(const instruction_union& instr)
{
	unsigned int addr = (short)instr.immediate_instruction.immediate + (int)Cpu::get_instance()->register_file.get_register(instr.immediate_instruction.rs);
	unsigned int word = Bus::get_instance()->get_word(addr);
	set_data_register(instr.immediate_instruction.rt, word);
}

void GTECoprocessor::store_word_from_cop(const instruction_union& instr)
{
	unsigned int addr = (short)instr.immediate_instruction.immediate + (int)Cpu::get_instance()->register_file.get_register(instr.immediate_instruction.rs);
	Bus::get_instance()->set_word(addr,get_data_register(instr.immediate_instruction.rt));
}

void GTECoprocessor::move_to_cop(const instruction_union& instr)
{
	unsigned int value = Cpu::get_instance()->register_file.get_register(instr.register_instruction.rt);
	set_data_register(instr.register_instruction.rd, value);
}

void GTECoprocessor::move_from_cop(const instruction_union& instr)
{
	unsigned value = get_data_register(instr.register_instruction.rd);
	Cpu::get_instance()->register_file.set_register(instr.register_instruction.rs, value);
}

void GTECoprocessor::move_control_to_cop(const instruction_union& instr)
{
	unsigned int value = Cpu::get_instance()->register_file.get_register(instr.register_instruction.rt);
	set_control_register(instr.register_instruction.rd, value);
}

void GTECoprocessor::move_control_from_cop(const instruction_union& instr)
{
	unsigned int value = get_control_register(instr.register_instruction.rd);
	Cpu::get_instance()->register_file.set_register(instr.register_instruction.rt, value);
}

void GTECoprocessor::move_control_to_cop_fun(const instruction_union& instr)
{
	throw std::logic_error("not implemented");
}