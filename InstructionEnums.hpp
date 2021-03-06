#pragma once
enum class gte_commands : unsigned char
{
	RTPS = 0x01,
	NCLIP = 0x06,
	OP_sf = 0x0c,
	DPCS = 0x10,
	INTPL = 0x11,
	MVMVA = 0x12,
	NCDS = 0x13,
	CDP = 0x14,
	NCDT = 0x16,
	NCCS = 0x1b,
	NCS = 0x1e,
	NCT = 0x20,
	SQR_sf = 0x28,
	DCPL = 0x29,
	DPCT = 0x2a,
	AVSZ3 = 0x2d,
	AVSZ4 = 0x2e,
	RTPT = 0x30,
	GPF_sf = 0x3d,
	GPL_sf = 0x3e,
	NCCT = 0x3f
};

// note: these values are octals (thats why they start with 0), its how the R3000A opcode encode was defined
// in http://hitmen.c02.at/files/docs/psx/psx.pdf so I just stuck with that to make it easier to compare
enum class copz_instructions : unsigned char
{
	MF = 000,
	CF = 002,
	MT = 004,
	CT = 006,
	BC = 010
};

enum class cop0_instructions : unsigned char
{
	TLBR = 001,
	TLBWI = 002,
	TLBWR = 006,
	TLBP = 010,
	RFE = 020
};

enum class cpu_instructions : unsigned char
{
	SPECIAL = 000,
	BCOND = 001,
	J = 002,
	JAL = 003,
	BEQ = 004,
	BNE = 005,
	BLEZ = 006,
	BGTZ = 007,
	ADDI = 010,
	ADDIU = 011,
	SLTI = 012,
	SLTIU = 013,
	ANDI = 014,
	ORI = 015,
	XORI = 016,
	LUI = 017,
	COP0 = 020,
	COP1 = 021,
	COP2 = 022,
	COP3 = 023,
	LB = 040,
	LH = 041,
	LWL = 042,
	LW = 043,
	LBU = 044,
	LHU = 045,
	LWR = 046,
	SB = 050,
	SH = 051,
	SWL = 052,
	SW = 053,
	SWR = 056,
	LWC0 = 060,
	LWC1 = 061,
	LWC2 = 062,
	LWC3 = 063,
	SWC0 = 070,
	SWC1 = 071,
	SWC2 = 072,
	SWC3 = 073
};

enum class cpu_special_funcs : unsigned char
{
	SLL = 000,
	SRL = 002,
	SRA = 003,
	SLLV = 004,
	SRLV = 006,
	SRAV = 007,
	JR = 010,
	JALR = 011,
	SYSCALL = 014,
	BREAK = 015,
	MFHI = 020,
	MTHI = 021,
	MFLO = 022,
	MTLO = 023,
	MULT = 030,
	MULTU = 031,
	DIV = 032,
	DIVU = 033,
	ADD = 040,
	ADDU = 041,
	SUB = 042,
	SUBU = 043,
	AND = 044,
	OR = 045,
	XOR = 046,
	NOR = 047,
	SLT = 052,
	SLTU = 053
};

enum class cpu_bconds : unsigned char
{
	BLTZ = 000,
	BGEZ = 001,
	BLTZAL = 020,
	BGEZAL = 021
};

enum class gp0_commands : unsigned char
{
	NOP = 0x00,
	
	// Direct VRAM access
	CLEAR_CACHE = 0x01,
	FILL_RECT = 0x02,
	COPY_RECT_VRAM_VRAM = 0x80,
	COPY_RECT_CPU_VRAM = 0xA0,
	COPY_RECT_VRAM_CPU = 0xC0,

	// Unknown
	UNKNOWN = 0x03,

	// Interrupt Request
	IRQ1 = 0x1F,

	// Render Polygons
	MONO_3_PT_OPAQUE = 0x20,
	MONO_3_PT_SEMI_TRANS = 0x22,
	MONO_4_PT_OPAQUE = 0x28,
	MONO_4_PT_SEMI_TRANS = 0x2A,

	TEX_3_OPAQUE_TEX_BLEND = 0x24,
	TEX_3_OPAQUE_RAW_TEX = 0x25,
	TEX_3_SEMI_TRANS_TEX_BLEND = 0x26,
	TEX_3_SEMI_TRANS_RAW_TEX = 0x27,
	TEX_4_OPAQUE_TEX_BLEND = 0x2C,
	TEX_4_OPAQUE_RAW_TEX = 0x2D,
	TEX_4_SEMI_TRANS_TEX_BLEND = 0x2E,
	TEX_4_SEMI_TRANS_RAW_TEX = 0x2F,

	SHADED_3_PT_OPAQUE = 0x30,
	SHADED_3_PT_SEMI_TRANS = 0x32,
	SHADED_4_PT_OPAQUE = 0x38,
	SHADED_4_PT_SEMI_TRANS = 0x3A,

	SHADED_TEX_3_OPAQUE_TEX_BLEND = 0x34,
	SHADED_TEX_3_SEMI_TRANS_TEX_BLEND = 0x36,
	SHADED_TEX_4_OPAQUE_TEX_BLEND = 0x3C,
	SHADED_TEX_4_SEMI_TRANS_TEX_BLEND = 0x3E,

	// Render Lines
	MONO_LINE_OPAQUE = 0x40,
	MONO_LINE_SEMI_TRANS = 0x42,
	MONO_POLY_LINE_OPAQUE = 0x48,
	MONO_POLY_LINE_SEMI_TRANS = 0x4A,

	SHADED_LINE_OPAQUE = 0x40,
	SHADED_LINE_SEMI_TRANS = 0x42,
	SHADED_POLY_LINE_OPAQUE = 0x48,
	SHADED_POLY_LINE_SEMI_TRANS = 0x4A,

	// Render Rectangles
	MONO_RECT_VAR_OPAQUE = 0x60,
	MONO_RECT_VAR_SEMI_TRANS = 0x62,
	MONO_RECT_DOT_OPAQUE = 0x68,
	MONO_RECT_DOT_SEMI_TRANS = 0x6A,
	MONO_RECT_8X8_OPAQUE = 0x70,
	MONO_RECT_8X8_SEMI_TRANS = 0x72,
	MONO_RECT_16X16_OPAQUE = 0x78,
	MONO_RECT_16X16_SEMI_TRANS = 0x7A,

	TEX_RECT_VAR_OPAQUE_TEX_BLEND = 0x64,
	TEX_RECT_VAR_OPAQUE_RAW_TEX = 0x65,
	TEX_RECT_VAR_SEMI_TRANS_TEX_BLEND = 0x66,
	TEX_RECT_VAR_SEMI_TRANS_RAW_TEX = 0x67,
	TEX_RECT_DOT_OPAQUE_TEX_BLEND = 0x6C,
	TEX_RECT_DOT_OPAQUE_RAW_TEX = 0x6D,
	TEX_RECT_DOT_SEMI_TRANS_TEX_BLEND = 0x6E,
	TEX_RECT_DOT_SEMI_TRANS_RAW_TEX = 0x6F,
	TEX_RECT_8X8_OPAQUE_TEX_BLEND = 0x74,
	TEX_RECT_8X8_OPAQUE_RAW_TEX = 0x75,
	TEX_RECT_8X8_SEMI_TRANS_TEX_BLEND = 0x76,
	TEX_RECT_8X8_SEMI_TRANS_RAW_TEX = 0x77,
	TEX_RECT_16X16_OPAQUE_TEX_BLEND = 0x7C,
	TEX_RECT_16X16_OPAQUE_RAW_TEX = 0x7D,
	TEX_RECT_16X16_SEMI_TRANS_TEX_BLEND = 0x7E,
	TEX_RECT_16X16_SEMI_TRANS_RAW_TEX = 0x7F,

	// Rendering attributes
	DRAW_MODE = 0xE1,
	TEX_WINDOW = 0xE2,
	SET_DRAW_TOP_LEFT = 0xE3,
	SET_DRAW_BOTTOM_RIGHT = 0xE4,
	SET_DRAWING_OFFSET = 0xE5,
	MASK_BIT = 0xE6

	 // TODO add mirrors
};

enum class gp1_commands : unsigned char
{
	RESET_GPU = 0x00,
	RESET_COMMAND_BUFFER = 0x01,
	ACK_IRQ1 = 0x02,
	DISPLAY_ENABLE = 0x03,
	DMA_DIR = 0x04,
	START_OF_DISPLAY = 0x05,
	HOR_DISPLAY_RANGE = 0x06,
	VERT_DISPLAY_RANGE = 0x07,
	DISPLAY_MODE = 0x08,
	GET_GPU_INFO = 0x10,
	// TODO add mirrors
	NEW_TEX_DISABLE = 0x09,
	PROTO_TEX_DISABLE = 0x20
};