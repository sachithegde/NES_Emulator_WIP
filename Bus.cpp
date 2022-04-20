#include "Bus.h"

//Constructor and Destructor
Bus::Bus()
{
	//Clear RAM
	for (auto& i : cpuRam)
	{
		i = 0x00;
	}

	cpu.ConnectBus(this);
}

Bus::~Bus()
{

}


//Read Write Function Basics
void Bus::cpuWrite(uint16_t address, uint8_t data)
{
	if (cartridge->cpuWrite(address, data))
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		cpuRam[address & 0x07FF] = data;
	}
	else if (address >= 0x2000 && address <= 0x3FFF)
	{
		ppu.cpuWrite(address & 0x0007, data);
	}
}

uint8_t Bus::cpuRead(uint16_t address, bool bReadOnly)
{
	uint8_t data = 0x00;
	if (cartridge->cpuRead(address, data))
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		data = cpuRam[address & 0x07FF];
	}
	else if (address >= 0x2000 && address <= 0x3FFF)
	{
		data = ppu.cpuRead(address & 0x0007, bReadOnly);
	}

	return data;
}

void Bus::InsertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cartridge = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
	cpu.reset();
	nSystemClockCounter = 0;
}

void Bus::clock()
{
	ppu.clock();
	if (nSystemClockCounter % 3 == 0)
	{
		cpu.clock();
	}

	if (ppu.nmi)
	{
		ppu.nmi = false;
		cpu.nmi();
	}
	nSystemClockCounter++;
}