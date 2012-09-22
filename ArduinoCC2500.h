/*!
 *  \file    ArduinoCC2500.h
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

#ifndef ARDUINOCC2500_H_
#define ARDUINOCC2500_H_

#include "CC2500.h"
#include <inttypes.h>

/*! \brief Class for interfacing with Other CC2500 Module.
 *
 * This class implements basic functions to communicate with Other CC2500 Module */
class ArduinoCC2500
{
protected:
    /*!
     * CC2500 object to communicate with the Other CC2500 Module.
     */
    CC2500 m_cc2500;

    
public:
    /*!
     * Constructor.
     *
     * \param[in] pinCS Pin number of slave select, default is 10.
     * \param[in] pinSCK Pin number of clock, default is 13 (Arduino standard).
     * \param[in] pinMOSI Pin number of master output slave input, default is 11 (Arduino standard).
     * \param[in] pinMISO Pin number of master input slave output, default is 12 (Arduino standard).
     */
    ArduinoCC2500(unsigned char pinCS = 10,
                 unsigned char pinSCK = 13,
                 unsigned char pinMOSI = 11,
                 unsigned char pinMISO = 12);

    /*!
     * Destructor.
     */
    ~ArduinoCC2500();

    /*!
     * Initializes communication with the Other CC2500 Module.
     */
    void init();

    /*!
     * Sends command to Data     
     */
    void sendCommand(unsigned char data);

    /*!
     * Copy constructor, disabled.
     */
    ArduinoCC2500(const ArduinoCC2500& that);

    /*!
     * Assignment operator, disabled.
     */
    ArduinoCC2500& operator=(const ArduinoCC2500& that);
};

#endif
