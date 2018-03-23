//**********************************************************************
//
// Keyer, a part of nanoIO
//
//  nanoIO paddle keyer (c) 2018, David Freese, W1HKJ
//
//  based on code from Iambic Keyer Code Keyer Sketch
//  Copyright (c) 2009 Steven T. Elliott
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


#ifndef Keyer_h
#define Keyer_h

#include "Arduino.h"

#include "config.h"

#define IAMBICA 0
#define IAMBICB 1
#define STRAIGHT 2

class Keyer
{
private:
	int  cw_pin_;
	int  ptt_pin_;
  
	long ktimer;

  int _speed;
  int _dashlen;  // Length of dash
  int _dotlen;   // Length of dot
  int _space_len; // Length of space
  float _weight;

	char keyerControl;
	char keyerState;
	int  key_mode;

  void calc_ratio();
	void update_PaddleLatch();

public:
	Keyer(int wpm, float _weight);
	void cw_pin(int pin);
	void ptt_pin(int pin);
	void wpm(int spd);
	void set_mode(int md);
  int  get_mode() { return key_mode; }
  void set__weight();
 
	bool do_paddles();

};

#endif

