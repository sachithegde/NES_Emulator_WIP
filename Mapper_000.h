#ifndef MAPPER_000_H
#define MAPPER_000_H

#include "Mapper.h"

class Mapper_000 : public Mapper
{
public:
	Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_000();

public:
	bool cpuMapRead(uint16_t address, uint32_t& mapped_address) override;
	bool cpuMapWrite(uint16_t address, uint32_t& mapped_address) override;
	bool ppuMapRead(uint16_t address, uint32_t& mapped_address) override;
	bool ppuMapWrite(uint16_t address, uint32_t& mapped_address) override;
};


#endif // !MAPPER_000_H