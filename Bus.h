#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <array>

#include "c6502.h"
#include "c2C02.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();

public: //Devices Connected to Bus
	c6502 cpu; //CPU
	c2C02 ppu; // PPU

	std::array<uint8_t, 2048> cpuRam; //RAM

	std::shared_ptr<Cartridge> cartridge;



public: // Bus Read and Write
	void cpuWrite(uint16_t address, uint8_t data);
	uint8_t cpuRead(uint16_t address, bool bReadOnly = false);

public: // System INterface | System Interactions
	void InsertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();

private:
	uint32_t nSystemClockCounter = 0;

};

#endif // !BUS_H
