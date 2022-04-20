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
	bool nmi;

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
	olc::Sprite& GetPatternTable(uint8_t i, uint8_t palette);
	olc::Pixel& GetColorFromPallete(uint8_t palette, uint8_t pixel);
	bool frame_complete = false;


private:
	int16_t scanline = 0;
	int16_t cycle = 0;

	union 
	{
		struct 
		{
			uint8_t unused : 5;
			uint8_t sprite_overflow : 1;
			uint8_t sprite_zero_hit : 1;
			uint8_t vertical_blank : 1;
		};

		uint8_t reg;

	} status;

	union 
	{
		struct 
		{
			uint8_t grayscale : 1;
			uint8_t render_background_left : 1;
			uint8_t render_sprites_left : 1;
			uint8_t render_background : 1;
			uint8_t render_sprites : 1;
			uint8_t enhance_red: 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blue : 1;
		};

		uint8_t reg;

	} mask;

	union PPUCTRL
	{
		struct
		{
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_sprite : 1;
			uint8_t pattern_background : 1;
			uint8_t sprite_size : 1;
			uint8_t slave_mode : 1; //unused
			uint8_t enable_nmi : 1;
		};

		uint8_t reg;

	} control;


	uint8_t address_latch = 0x00; // Indicates Whether the Adress is the Low Byte or the High Byte. 
	uint8_t ppu_data_buffer = 0x00; 
	uint16_t ppu_address = 0x0000;

	

};

#endif // !c2C02_H
