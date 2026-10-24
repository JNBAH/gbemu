#pragma once
#include <cstdint>
#include "bus.h"

class Cpu{
    public:
        explicit Cpu(Bus& bus);
        int step();


    private:
        Bus& bus;
        //Registers
        uint8_t a = 0;
        uint8_t f = 0;
        uint8_t b = 0;
        uint8_t c = 0;
        uint8_t d = 0;
        uint8_t e = 0;
        uint8_t h = 0;
        uint8_t l = 0;
        uint16_t sp = 0;
        uint16_t pc = 0;

        bool ime = false; // Interrupt Master Enable Flag

        // Fetch functions for reading data from memory
        uint8_t fetch8();
        uint16_t fetch16();

        // Flag manipulation functions
        void setFlag(uint8_t mask, bool on);
        bool getFlag(uint8_t mask) const;
        

        // Getters for paired registers
        uint16_t getBC() const;
        uint16_t getAF() const;
        uint16_t getDE() const;
        uint16_t getHL() const;

        // Setters for paired registers
        void setBC(uint16_t value);
        void setAF(uint16_t value);
        void setDE(uint16_t value);
        void setHL(uint16_t value);

        static constexpr uint8_t FLAG_Z = 0x80; // Zero Flag
        static constexpr uint8_t FLAG_N = 0x40; // Subtract Flag
        static constexpr uint8_t FLAG_H = 0x20; // Half Carry Flag
        static constexpr uint8_t FLAG_C = 0x10; // Carry Flag





};