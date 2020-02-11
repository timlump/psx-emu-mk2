#include <memory>
#include <vector>
#include <map>

constexpr unsigned int DMA_SIZE = 128;

class Gpu;
class Ram;

class Dma
{
public:
	union DMA_base_address
	{
		unsigned char byte_value[4];
		struct
		{
			unsigned int memory_address : 24;
			unsigned int na : 8;
		};
	};

	union DMA_block_control
	{
		unsigned char byte_value[4];
		struct
		{
			unsigned int BC : 16;
			unsigned int na : 16;
		};
		struct
		{
			unsigned int BS : 16;
			unsigned int BA : 16;
		};
	};

	union DMA_channel_control
	{
		unsigned char byte_value[4];
		struct
		{
			unsigned int transfer_direction : 1;
			unsigned int memory_address_step : 1;
			unsigned int na1 : 6;
			unsigned int chopping_enable : 1;
			unsigned int sync_mode : 2;
			unsigned int na2 : 5;
			unsigned int chopping_dma_window_size : 3;
			unsigned int na3 : 1;
			unsigned int chopping_cpu_window_size : 3;
			unsigned int na4 : 1;
			unsigned int start_busy : 1;
			unsigned int na5 : 3;
			unsigned int start_trigger : 1;
			unsigned int unknown1 : 1;
			unsigned int unknown2 : 1;
			unsigned int na6 : 1;
		};
	};

	union DMA_control_register
	{
		unsigned char byte_value[4];
		struct
		{
			unsigned int MDECin_priority : 3;
			unsigned int MDECin_master_enable : 1;
			unsigned int MDECout_priority : 3;
			unsigned int MDECout_master_enable : 1;
			unsigned int GPU_priority : 3;
			unsigned int GPU_master_enable : 1;
			unsigned int CDROM_priority : 3;
			unsigned int CDROM_master_enable : 1;
			unsigned int SPU_priority : 3;
			unsigned int SPU_master_enable : 1;
			unsigned int PIO_priority : 3;
			unsigned int PIO_master_enable : 1;
			unsigned int OTC_priority : 3;
			unsigned int OTC_master_enable : 1;
			unsigned int unknown_priority : 3;
			unsigned int unknown_master_enable : 1;
		};
	};

	union DMA_interrupt_register
	{
		unsigned char byte_value[4];
		struct
		{
			unsigned int unknown : 6;
			unsigned int na : 9;
			unsigned int force_irq : 1;
			unsigned int irq_enable : 7;
			unsigned int irq_master_enable : 1;
			unsigned int irq_flags : 7;
			unsigned int irq_master_flag : 1;
		};
	};

	void init(std::shared_ptr<Ram> _ram, std::shared_ptr<Gpu> _gpu);
	unsigned char * operator[](unsigned int address);
private:

	std::shared_ptr<Ram> ram = nullptr;
	std::shared_ptr<Gpu> gpu = nullptr;

	std::vector<DMA_base_address> base_addresses;
	std::vector<DMA_block_control> block_controls;
	std::vector<DMA_channel_control> channel_controls;
	DMA_control_register control_register;
	DMA_interrupt_register interrupt_register;
	unsigned char garbage[8] = { 0 };

	std::map<unsigned int, unsigned char*> raw_ref_buffer;
};