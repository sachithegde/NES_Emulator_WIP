#ifndef C6502_H
#define C6502_H

#include <iostream>

#include <vector>
#include<cstdint>


// These are required for disassembler. If you dont require disassembly
// then just remove the function.
#include <string>
#include <map>


class Bus;

class c6502
{
public:
	c6502();
	~c6502();

	inline void ConnectBus(Bus* nBus) { bus = nBus; }

	//Addressing Modes
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

	//Opcodes

	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX();

	void clock();
	//async functions. 
	void reset();
	void irq(); // Interupt Request Signal
	void nmi(); // Non Maskable Interupt signal


	uint8_t fetch(); // Fetch Data if a signal requires it
	uint8_t fetched = 0x00; // Data Fetched from function above. 

	uint16_t address_abs = 0x0000;
	uint16_t address_rel = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t cycles = 0x00;

	bool complete();

	// Produces a map of strings, with keys equivalent to instruction start locations
	// in memory, for the specified address range
	std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);



public:
	//Special Register Flags
	enum FLAG6502
	{
		C = (1 << 0),  // Carry Bit
		Z = (1 << 1),  // Zero Bit
		I = (1 << 2),  // Disable Interrupts Bit
		D = (1 << 3),  // Decimal Mode Bit
		B = (1 << 4),  // Break Bit
		U = (1 << 5),  // Unused Bit
		V = (1 << 6),  // Overflow Bit
		N = (1 << 7),  // Negative Bit

	};

	//Registers
	uint8_t a = 0x00;      // Accumulator Register
	uint8_t x = 0x00;      // X Register
	uint8_t y = 0x00;      // Y Register
	uint8_t sp = 0x00;     // Stack Pointer
	uint16_t pc = 0x0000;  // Program Counter
	uint8_t status = 0x00; // Status Register
	


private:
	Bus* bus = nullptr;
	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);

	uint8_t GetFlag(FLAG6502 flag);
	void SetFlag(FLAG6502 flag, bool value);

	struct INSTRUCTION
	{
		std::string name;
		uint8_t(c6502::* operate)(void) = nullptr;
		uint8_t(c6502::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;

	};

	std::vector<INSTRUCTION> lookup;
};

#endif // !C6502_H
