#include "Cartridge.h"

Cartridge::Cartridge(const std::string& sFileName)
{
	struct sHeader
	{
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		
		char unused[5];


	} header;

	std::ifstream file;
	file.open(sFileName, std::ifstream::binary);
	if (file.is_open())
	{
		file.read((char*)& header, sizeof(header));

		if (header.mapper1 & 0x04)
		{
			file.seekg(512, std::ios::cur);
		}

		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		uint8_t nFileType = 1;

		if (nFileType == 0)
		{

		}

		if (nFileType == 1)
		{
			nPRGBanks = header.prg_rom_chunks;
			vPRGmem.resize(nPRGBanks * 16384);
			file.read((char*)vPRGmem.data(), vPRGmem.size());

			nCHRBanks = header.chr_rom_chunks;
			vCHRmem.resize(nCHRBanks * 8192);
			file.read((char*)vCHRmem.data(), vCHRmem.size());


		}

		if (nFileType == 2)
		{

		}

		switch (nMapperID)
		{
		case 0: 
			pMapper = std::make_shared<Mapper_000>(nPRGBanks, nCHRBanks);
			break;
		}

		file.close();
	}

}

Cartridge::~Cartridge()
{

}

bool Cartridge::ImageValid()
{
	return bImageValid;
}

bool Cartridge::cpuRead(uint16_t address, uint8_t& data)
{
	uint32_t mapper_address = 0x00;
	if (pMapper->cpuMapRead(address, mapper_address))
	{
		data = vPRGmem[mapper_address];
		return true;
	}
	else
	{
		return false;
	}
}

bool Cartridge::cpuWrite(uint16_t address, uint8_t data)
{
	uint32_t mapper_address = 0;
	if (pMapper->cpuMapWrite(address, mapper_address))
	{
		vPRGmem[mapper_address] = data;
		return true;
	}
	else
	{
		return false;
	}
}

bool Cartridge::ppuRead(uint16_t address, uint8_t& data)
{
	uint32_t mapper_address = 0;
	if (pMapper->ppuMapRead(address, mapper_address))
	{
		data = vCHRmem[mapper_address];
		return true;
	}
	else
	{
		return false;
	}
}

bool Cartridge::ppuWrite(uint16_t address, uint8_t data)
{
	uint32_t mapper_address = 0;
	if (pMapper->ppuMapRead(address, mapper_address))
	{
		vCHRmem[mapper_address] = data;
		return true;
	}
	else
	{
		return false;
	}
}