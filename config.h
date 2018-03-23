/***********************************************************************

  nanoIO

  CW / FSK interface sketch for use either stand alone or with fldigi.

  It is designed to fit within the RAM and I/O constraints of an Arduino 
  Nano circuit board.  It generates either CW 5 to 100 WPM Morse code, 
  or FSK Baudot hardline signals of 45.45, 50 or 75 Baud.

  Copyright (C) 2018 David Freese W1HKJ
  Derived from tinyFSK by Andrew T. Flowers K0SM

  nanoIO is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with tinyCWFSK.ino.  If not, see <http://www.gnu.org/licenses/>.

  Revisions:

  //1.0.0:  Initial release

***********************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define VERSION "1.0.0"

//----------------------------------------------------------------------
// values which may need to be changed depending on specific hardware
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//Arduino pins for FSK, CW and PTT to control transmitter
// uncomment the desired h/w configuration
// comment the others
#define MORTTY 1
// #define HA2OS  1
// #define OTHER  1
//----------------------------------------------------------------------

#ifdef MORTTY
// Pin designations for MORTTY circuit board
#  define FSK_PIN 11
#  define CW_PIN  11
#  define PTT_PIN 13
//#  define ST_Pin 4      // Sidetone Output Pin on Pin 4
// paddle input pins compatible with MORTTY board
#  define LP_in 2       // Left Paddle Input on Pin 2
#  define RP_in 5       // Right Paddle Input on Pin 5
#  define DEFAULT_MODE CW_MODE
#else
#  ifdef HA2OS
// Pin designations for HA2OS quad opto-isolator circuit board design
#    define FSK_PIN 12
#    define CW_PIN  10
#    define PTT_PIN 11
//#    define ST_Pin 4      // Sidetone Output Pin on Pin 4
//   paddle input pins
#    define LP_in 5       // Left Paddle Input on Pin 2
#    define RP_in 2       // Right Paddle Input on Pin 5
#    define DEFAULT_MODE CW_MODE
#  else
// change these for OTHER h/w design
#    define FSK_PIN 11
#    define CW_PIN  12
#    define PTT_PIN 13
//#    define ST_Pin 4      // Sidetone Output Pin on Pin 4
//   paddle input pins
#    define LP_in 2       // Left Paddle Input on Pin 2
#    define RP_in 5       // Right Paddle Input on Pin 5
#    define DEFAULT_MODE FSK_MODE
#  endif
#endif

#endif // __CONFIG_H_
