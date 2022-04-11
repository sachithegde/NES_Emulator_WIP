#ifndef c2C02_H
#define c2C02_H

#include <iostream>
#include <cstdint>
#include "Cartridge.h"

#include "olcPixelGameEngine.h"

class c2C02
{
public:
	c2C02();
	~c2C02();

public:
	uint8_t NameTable[2][1024];
	uint8_t PaletteTable[32];
	uint8_t PatternTable[2][4096]; // Unneccessary

public:
	uint8_t cpuRead(uint16_t address, bool readonly = false);
	void cpuWrite(uint16_t address, uint8_t data);

	uint8_t ppuRead(uint16_t address, bool readonly = false);
	void ppuWrite(uint16_t address, uint8_t data);

public:
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void clock();

private:
	std::shared_ptr<Cartridge> cartridge;

private:
	olc::Pixel  palScreen[0x40];
	olc::Sprite sprScreen = olc::Sprite(256, 240);
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
	// Debugging Utilities
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t i);
	olc::Sprite& GetPatternTable(uint8_t i);
	bool frame_complete = false;

private:
	int16_t scanline = 0;
	int16_t cycle = 0;

};

#endif // !c2C02_H
