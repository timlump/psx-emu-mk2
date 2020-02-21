#pragma once
#include <memory>
#include "InstructionTypes.hpp"

class Ram;
class Cpu;

class Cop
{
public:
	Cop(std::shared_ptr<Ram> _ram, std::shared_ptr<Cpu> _cpu) { 
		ram = _ram;
		cpu = _cpu;
	};

	virtual void save_state(std::ofstream& file) = 0;
	virtual void load_state(std::ifstream& file) = 0;

	virtual void execute(const instruction_union& instruction) = 0;

	virtual void load_word_to_cop(const instruction_union& instr) = 0;
	virtual void store_word_from_cop(const instruction_union& instr) = 0;
	virtual void move_to_cop(const instruction_union& instr) = 0;
	virtual void move_from_cop(const instruction_union& instr) = 0;
	virtual void move_control_to_cop(const instruction_union& instr) = 0;
	virtual void move_control_from_cop(const instruction_union& instr) = 0;
	virtual void move_control_to_cop_fun(const instruction_union& instr) = 0;

	virtual void reset() {};

	std::shared_ptr<Ram> ram = nullptr;
	std::shared_ptr<Cpu> cpu = nullptr;
};