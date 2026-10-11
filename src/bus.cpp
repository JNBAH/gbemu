#include "bus.h"
#include <fstream>
#include <iostream>

bool Bus::loadRom(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Could not open ROM file: " << path << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    rom.resize(static_cast<size_t>(size));
    if(!file.read(reinterpret_cast<char*>(rom.data()),size)) {
        std::cerr << "Could not read ROM file \n";
        return false;
    }
    return true;
}

// Read function

uint8_t Bus::read(uint16_t addr) const {
    
    // Handle reading memory regions based on the address
    
    if (addr < 0x8000){
        return addr < rom.size() ? rom[addr] : 0xFF; // If/else to handle no ROM loaded, return 0xFF for an unloaded ROM
    }

    if (addr < 0xA000){
        return vram[addr - 0x8000];
    }

    if (addr < 0xC000){
        return extRam[addr - 0xA000];
    }

    if (addr < 0xD000){
        return wram[addr - 0xC000];
    }

    if (addr < 0xE000){
        return wram2[addr - 0xD000];
    }

    if (addr < 0xFE00){
        return read(addr - 0x2000); // Echo RAM, maps to WRAM
    }

    if (addr < 0xFEA0){
        return oam[addr - 0xFE00];
    }

    if (addr < 0xFF00){
        return 0xFF; // Unusable memory region
    }

    if (addr < 0xFF80){
        return io[addr - 0xFF00];
    }

    if (addr < 0xFFFF){
        return hram[addr - 0xFF80];
    }
    
    if (addr == 0xFFFF){
        return ie;
    }

    return 0xFF; // Usual return value for unmapped addresses
}


// Write function
void Bus::write(uint16_t addr, uint8_t value){
    if (addr < 0x8000){ // ROM is read-only
        return;
    }
    
    if (addr < 0xA000){
        vram[addr - 0x8000] = value;
        return;
    }

    if (addr < 0xC000){
        extRam[addr - 0xA000] = value;
        return;
    }

    if (addr < 0xD000){
        wram [addr - 0xC000] = value;
        return;
    }

    if (addr < 0xE000){
        wram2[addr - 0xD000] = value;
        return;
    }

    if (addr < 0xFE00){ //Echo maps to WRAM
        write(addr - 0x2000, value);
        return;
    }

    if (addr < 0xFEA0){
        oam[addr - 0xFE00] = value;
        return;
    }

    if (addr < 0xFF00){
        return; // Unusable memory region
    }

    if (addr < 0xFF80){
        io[addr - 0xFF00] = value;
        return;
    }

    if (addr < 0xFFFF){
        hram[addr - 0xFF80] = value;
        return;
    }

    if (addr == 0xFFFF){
        ie = value;
        return;
    }
}







