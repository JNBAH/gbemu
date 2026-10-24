#include <iostream>
#include "bus.h"
#include "cpu.h"

int main(int argc, char* argv[]) {
    Bus bus; //Call bus class
    
    if(argc >= 2){
        if(!bus.loadRom(argv[1])) 
            return 1; //Load ROM file, if it fails return 1
        
        std::cout << "Title: ";
        for (uint16_t a = 0x0134; a <= 0x0143; ++a){
            char c = static_cast<char>(bus.read(a));
            if (c == 0) break; //
            std::cout << c;
        }
        std::cout <<"\nCartridge Type: 0x" << std::hex
        << static_cast<int>(bus.read(0x0147)) << std::dec << "\n";

    }

    bus.write(0xC000, 0x42); //Write to WRAM
    std::cout << std::hex 
    << "WRAM C000: 0x" << static_cast<int>(bus.read(0xC000)) << "\n"
    << "Echo E000: 0x" << static_cast<int>(bus.read(0xE000)) << "\n";

    bus.write(0x8000, 0x11);
    bus.write(0x9FFF, 0x22);

    std::cout << "VRAM 8000: 0x" << static_cast<int>(bus.read(0x8000)) << "\n"
    << "VRAM 9FFF: 0x" << static_cast<int>(bus.read(0x9FFF)) << "\n";

    bus.write(0xFFFF, 0x1F);
    std::cout << "IE FFFF: 0x" << static_cast<int>(bus.read(0xFFFF)) << "\n";


    Cpu cpu(bus);//Create CPU instance with bus
    for(int i = 0; i < 100000; i++){
    int cycles = cpu.step();
        if (cycles < 0) 
        break; // Stop on error
    }


    return 0;
}

