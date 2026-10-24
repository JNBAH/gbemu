#include "cpu.h"
#include <iostream>

Cpu::Cpu(Bus& bus) : bus(bus){
    //8-bit registers
   a = 0x01; // Initialize register A to 0x01 "for testing"
   b = 0x00; // Initialize register B to 0x00 ""
   c = 0x13; // Initialize register C to 0x13 ""
   d = 0x00; // Initialize register D to 0x00 ""
   e = 0xD8; // Initialize register E to 0xD8 ""
   f = 0xB0; // Initialize register F to 0xB0 (flags) ""
   h = 0x01; // Initialize register H to 0x01 ""
   l = 0x4D; // Initialize register L to 0x4D ""

    //16-bit registers
   sp = 0xFFFE; // Initialize stack pointer to 0xFFFE ""
   pc = 0x0100;// Initialize program counter to 0x0100 ""

};

uint8_t Cpu::fetch8(){
    return bus.read(pc++);
};

uint16_t Cpu::fetch16(){
    uint16_t low = fetch8();
    uint16_t high = fetch8();
    return (high << 8) | low;
};

uint16_t Cpu::getBC() const{
    return (static_cast<uint16_t>(b) << 8) | c;
};

void Cpu::setBC(uint16_t value){
    b = (value >> 8) & 0xFF;
    c = value & 0xFF;
};

void Cpu::setFlag(uint8_t mask, bool on){
    if (on){
        f |= mask;
    } else{
        f &= ~mask;
    }
}

int Cpu::step(){
    uint8_t opcode = fetch8();
    switch (opcode){

        case 0x00:
            return 4; // Return the number of cycles for this instruction (NOP)
        
        
        case 0x01:{
            uint16_t value = fetch16(); //LD, BC, 
            b = (value >> 8) & 0xFF; // Load high byte into B
            c = value & 0xFF; // Load low byte into C
            return 12; // Return the number of cycles for this instruction
        }

        case 0x02:{
            bus.write(getBC(), a); //LD (BC), A
            return 8; // Return the number of cycles for this instruction
        
        }

        case 0x03:{ //INC BC
            setBC(getBC() + 1); // Read the pair, add one, store it back
            return 8; // Return the number of cycles for this instruction
        }

        case 0x3E:{ //LD A, n
            a = fetch8(); // Load the next byte into A
            return 8; // Return the number of cycles for this instruction
        }

        case 0xC3:{ //JP nn
            uint16_t addr = fetch16(); // Fetch the next two bytes as the address
            pc = addr; // Set the program counter to the fetched address
            return 16; // Return the number of cycles for this instruction
        }

        case 0xF3:{ //DI
            ime = false; // Disable interrupts
            return 4; // Return the number of cycles for this instruction
        }
        
        case 0x31: {
            sp = fetch16(); // Load the next two bytes into the stack pointer
            return 12; // Return the number of cycles for this instruction
        }

        case 0xEA: {
            uint16_t addr = fetch16(); // Fetch the next two bytes as the address
            bus.write(addr, a); // Write the value of A to the fetched address
            return 16; // Return the number of cycles for this instruction
        }

        default:
            std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(opcode) << " at address 0x" << (pc - 1) <<std::endl;
            return -1; // Return a default cycle count for unknown instructions
    
    }
};


