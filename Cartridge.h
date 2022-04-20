#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "Mapper_000.h"

class Cartridge
{
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();

public:
	bool cpuRead(uint16_t address, uint8_t& data);
	bool cpuWrite(uint16_t address, uint8_t data);

	bool ppuRead(uint16_t address, uint8_t& data);
	bool ppuWrite(uint16_t address, uint8_t data);

public:
	bool ImageValid();
	enum MIRROR {
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI
	} mirror = HORIZONTAL;
private:
	bool bImageValid = false;
	std::vector<uint8_t> vPRGmem;
	std::vector<uint8_t> vCHRmem;
	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::shared_ptr<Mapper> pMapper;
};


#endif // !CARTRIDGE_H