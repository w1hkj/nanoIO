//**********************************************************************
//
// Morse, a part of nanoIO
//
// Copyright (C) 2018, David Freese, W1HKJ
//
// nanoIO is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// nanoIO is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with fldigi.  If not, see <http://www.gnu.org/licenses/>.
//
//Revisions:
//
//1.0.0:  Initial release
//
//**********************************************************************


#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
	public:
		Morse(int wpm, float weight);
		void send(char c, byte pin);
		void weight(float wt);
		void wpm(int spd);
	private:
    byte _speed;   // Speed in WPM

    int _dashlen;  // Length of dash
    int _dotlen;   // Length of dot
    int _spacelen; // Length of space
    float _wt;     // weight 2.5 to 3.5; 3.0 nominal

		void dash(byte pin);
		void dit(byte pin);
    void calc_ratio();
};
#endif
