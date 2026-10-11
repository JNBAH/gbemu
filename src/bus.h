#pragma once 
#include <cstdint>
#include <vector>
#include <array>
#include <string>

class Bus {
public:
    bool loadRom(const std::string& path);
    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t value);


private:
    std::vector<uint8_t> rom;  // 0000-7FFF (from rom file)
    std::array<uint8_t, 0x2000> vram{}; // 8000-9FFF
    std::array<uint8_t, 0x2000> extRam{}; // A000-BFFF
    std::array<uint8_t, 0x1000> wram{}; // C000-CFFF
    std::array<uint8_t, 0x1000> wram2{}; // D000-DFFF
    //std::array<uint8_t, 0x2000> echo; E000-FDFF ("prohibited", but still mapped to WRAM)
    std::array<uint8_t, 0xA0> oam{};  // FE00-FE9F
    //std::array<uint8_t, 0x60> unused; FEA0-FEFF ("prohibited")
    std::array<uint8_t, 0x80> io{};   // FF00-FF7F
    std::array<uint8_t, 0x7f> hram{}; // FF80-FFFE
    uint8_t ie = 0;   // FFFF



};