/*!
 *  \file    CC2500.cpp
 *  \version 1.0
 *  \date    21-09-2012
 *  \author  Yasir Ali, ali.yasir0@gmail.com
 *
 *  Copyright (c) 2012, Yasir Ali
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program;
 *
 *  \internal
 *    Created: 21-09-2012
 */

#include "CC2500.h"
#include "Arduino.h"

CC2500::CC2500(unsigned char pinCS, unsigned char pinSCK, unsigned char pinMOSI,
    unsigned char pinMISO)
    : m_pinCS(pinCS)
    , m_pinSCK(pinSCK)
    , m_pinMOSI(pinMOSI)
    , m_pinMISO(pinMISO)
{
}

CC2500::~CC2500()
{
}

void CC2500::init()
{
    // setup pin mode
    pinMode(m_pinMOSI, OUTPUT);
    pinMode(m_pinMISO, INPUT);
    pinMode(m_pinSCK, OUTPUT);
    pinMode(m_pinCS, OUTPUT);

    // disable device
    digitalWrite(m_pinCS, HIGH);

    // setup SPI control register: SPCR = 01010000
    // interrupt disabled, spi enabled, msb 1st, master, clk low when idle,
    // sample on rising edge of clk, system clock rate fastest
    SPCR = (1<<SPE) | (1<<MSTR);

    // clear data registers
    byte clr = SPSR;
    clr = SPDR;
}

void CC2500::reset()
{
    // enable device
    digitalWrite(m_pinCS, LOW);
    delayMicroseconds(1);

    // disable device and wait at least 40 microseconds
    digitalWrite(m_pinCS, HIGH);
    delayMicroseconds(41);

    // enable device
    digitalWrite(m_pinCS, LOW);

    // wait for device
    while (digitalRead(m_pinMISO) == HIGH) {
    };

    // send reset command (SRES)
    spiTransfer(0x30);

    // disable device
    digitalWrite(m_pinCS, HIGH);
}

unsigned char CC2500::sendByte(unsigned char data)
{
    // enable device
    digitalWrite(m_pinCS, LOW);

    // wait for device
    while (digitalRead(m_pinMISO) == HIGH) {
    };

    // send byte
    unsigned char result = spiTransfer(data);

    // disable device
    digitalWrite(m_pinCS, HIGH);

    // return result
    return result;
}

unsigned char CC2500::sendCommand(unsigned char command, unsigned char data)
{
    // enable device
    digitalWrite(m_pinCS, LOW);

    // wait for device
    while (digitalRead(m_pinMISO) == HIGH) {
    };

    // send command byte
    spiTransfer(command);

    // send data byte
    unsigned char result = spiTransfer(data);

    // disable device
    digitalWrite(m_pinCS, HIGH);

    // return result
    return result;
}

unsigned char CC2500::sendStrobeCommand(unsigned char command)
{
    // send command
    return sendByte(command);
}

unsigned char CC2500::sendBurstCommand(unsigned char command, unsigned char* data,
    unsigned char length)
{
    // enable device
    digitalWrite(m_pinCS, LOW);

    // wait for device
    while (digitalRead(m_pinMISO) == HIGH) {
    };

    // send command byte
    spiTransfer(command);

    unsigned char result = 0;

    // send data bytes
    for (int i=0; i<length; ++i) {
        result = spiTransfer(data[i]);
        data[i] = result;
    }

    // disable device
    digitalWrite(m_pinCS, HIGH);

    // return result
    return result;
}

unsigned char CC2500::spiTransfer(volatile unsigned char data)
{
    // start transmission
    SPDR = data;

    // wait for end of transmission
    while (!(SPSR & (1<<SPIF))) {
    };

    // return received byte
    return SPDR;
}
