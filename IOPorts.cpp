#include "IOPorts.hpp"
#include "Gpu.hpp"
#include "Dma.hpp"
#include "Exceptions.hpp"
#include <typeinfo.h>

constexpr unsigned int IO_START = 0x1F801000;
constexpr unsigned int GP0_Send_GPUREAD_START = 0x1f801810 - IO_START;
constexpr unsigned int GP0_Send_GPUREAD_END = GP0_Send_GPUREAD_START + 4;
constexpr unsigned int GP1_Send_GPUSTAT_START = 0x1f801814 - IO_START;
constexpr unsigned int GP1_Send_GPUSTAT_END = GP1_Send_GPUSTAT_START + 4;

constexpr unsigned int MEMORY_CONTROL_1_START = 0x1F801000 - IO_START;
constexpr unsigned int MEMORY_CONTROL_1_END = MEMORY_CONTROL_1_START + MEMORY_CONTROL_1_SIZE;

constexpr unsigned int MEMORY_CONTROL_2_START = 0x1F801060 - IO_START;
constexpr unsigned int MEMORY_CONTROL_2_END = MEMORY_CONTROL_2_START + MEMORY_CONTROL_2_SIZE;

constexpr unsigned int SPU_CONTROL_START = 0x1F801D80 - IO_START;
constexpr unsigned int SPU_CONTROL_END = SPU_CONTROL_START + SPU_CONTROL_SIZE;

constexpr unsigned int SPU_VOICE_START = 0x1F801C00 - IO_START;
constexpr unsigned int SPU_VOICE_END = SPU_VOICE_START + SPU_VOICE_SIZE;

constexpr unsigned int POST = 0x1F802041 - IO_START;

constexpr unsigned int I_STAT_START = 0x1F801070 - IO_START;
constexpr unsigned int I_STAT_END = I_STAT_START + I_STAT_SIZE;

constexpr unsigned int I_MASK_START = 0x1F801074 - IO_START;
constexpr unsigned int I_MASK_END = I_MASK_START + I_MASK_SIZE;

constexpr unsigned int TIMER_START = 0x1F801100 - IO_START;
constexpr unsigned int TIMER_END = TIMER_START + TIMER_SIZE;

constexpr unsigned int DMA_SIZE = 128;
constexpr unsigned int DMA_START = 0x1F801080 - IO_START;
constexpr unsigned int DMA_END = DMA_START + DMA_SIZE;

void IOPorts::init(std::shared_ptr<Gpu> _gpu, std::shared_ptr<Dma> _dma)
{
	gpu = _gpu;
	dma = _dma;
}

void IOPorts::save_state(std::ofstream& file)
{
	throw std::logic_error("not implemented");
}

void IOPorts::load_state(std::ifstream& file)
{
	throw std::logic_error("not implemented");
}

unsigned char IOPorts::get(unsigned int address)
{
	if (address >= GP0_Send_GPUREAD_START &&
		address < GP0_Send_GPUREAD_END)
	{
		return gpu->get(Gpu::GPUREAD, address - GP0_Send_GPUREAD_START);
	}
	else if (address >= GP1_Send_GPUSTAT_START &&
		address < GP1_Send_GPUSTAT_END)
	{
		return gpu->get(Gpu::GPUSTAT, address - GP1_Send_GPUSTAT_START);
	}
	else if (address >= MEMORY_CONTROL_1_START &&
		address < MEMORY_CONTROL_1_END)
	{
		return memory_control_1[address - MEMORY_CONTROL_1_START];
	}
	else if (address >= MEMORY_CONTROL_2_START &&
		address < MEMORY_CONTROL_2_END)
	{
		return memory_control_2[address - MEMORY_CONTROL_2_START];
	}
	else if (address >= SPU_CONTROL_START &&
		address < SPU_CONTROL_END)
	{
		return spu_control[address - SPU_CONTROL_START];
	}
	else if (address >= SPU_VOICE_START &&
		address < SPU_VOICE_END)
	{
		return spu_voice_registers[address - SPU_VOICE_START];
	}
	else if (address >= I_STAT_START &&
		address < I_STAT_END)
	{
		return i_stat[address - I_STAT_START];
	}
	else if (address >= I_MASK_START &&
		address < I_MASK_END)
	{
		return i_mask[address - I_MASK_START];
	}
	else if (address >= TIMER_START &&
		address < TIMER_END)
	{
		return timers[address - TIMER_START];
	}
	else if (address >= DMA_START &&
		address < DMA_END)
	{
		return dma->get(address - DMA_START);
	}
	else if (address == POST)
	{
		return post;
	}
	else
	{
		throw bus_error();
	}
}

void IOPorts::set(unsigned int address, unsigned char value)
{
	if (address >= GP0_Send_GPUREAD_START &&
		address < GP0_Send_GPUREAD_END)
	{
		gpu->set(Gpu::GP0_SEND, address - GP0_Send_GPUREAD_START, value);
	}
	else if (address >= GP1_Send_GPUSTAT_START &&
		address < GP1_Send_GPUSTAT_END)
	{
		gpu->set(Gpu::GP1_SEND, address - GP1_Send_GPUSTAT_START, value);
	}
	else if (address >= MEMORY_CONTROL_1_START &&
		address < MEMORY_CONTROL_1_END)
	{
		memory_control_1[address - MEMORY_CONTROL_1_START] = value;
	}
	else if (address >= MEMORY_CONTROL_2_START &&
		address < MEMORY_CONTROL_2_END)
	{
		memory_control_2[address - MEMORY_CONTROL_2_START] = value;
	}
	else if (address >= SPU_CONTROL_START &&
		address < SPU_CONTROL_END)
	{
		spu_control[address - SPU_CONTROL_START] = value;
	}
	else if (address >= SPU_VOICE_START &&
		address < SPU_VOICE_END)
	{
		spu_voice_registers[address - SPU_VOICE_START] = value;
	}
	else if (address >= I_STAT_START &&
		address < I_STAT_END)
	{
		i_stat[address - I_STAT_START] = value;
	}
	else if (address >= I_MASK_START &&
		address < I_MASK_END)
	{
		i_mask[address - I_MASK_START] = value;
	}
	else if (address >= TIMER_START &&
		address < TIMER_END)
	{
		timers[address - TIMER_START] = value;
	}
	else if (address >= DMA_START &&
		address < DMA_END)
	{
		return dma->set(address - DMA_START, value);
	}
	else if (address == POST)
	{
		post = value;
	}
	else
	{
		throw bus_error();
	}
}