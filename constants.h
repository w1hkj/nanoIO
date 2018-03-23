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

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//BUFFER SETTINGS
// Allow up to 300 chars in the buffer before overrunning (wrapping around).
// This can be increased on most boards with more RAM.
#define SEND_BUFFER_SIZE 300

#define MIN_CW_WPM 5
#define MAX_CW_WPM 100
///---------------------------------------------------------------------

//EEPROM addresses to persist configuration
#define EE_SPEED_ADDR 0
#define EE_POLARITY_ADDR 1
#define EE_CW_STRUC_ADDR 2

//Special Baudot symbols for shift
#define LTRS_SHIFT 0x1F  //baudot letter shift byte
#define FIGS_SHIFT 0x1B  //baudot figs shift byte

#define SHIFT_UNKNOWN 0  //Undefined shift--used at TX start to force shift state

//Special ASCII SYMBOLS (8 bit)
#define ASCII_NULL 0x00
#define ASCII_LF 0x0A
#define ASCII_CR 0x0D

#define TX_END_FLAG 0xFF      // Used in Baudot stream to indicate EOT

//References used in banging out the bits for 5-bit baudot. These
//are relative to the first data bit in the frame.
#define START_BIT_POS -1
#define STOP_BIT_POS 5

//Commands that control transmitter sequencing
#define TX_ON '['   // TX now => {TX} in N1MM
#define TX_END ']'  // Buffered switch to RX => {END} in N1MM
#define TX_ABORT '\\' // (Backslash) Immediate switch to RX and clear buffer => {ESC} in N1MM

//Configuration commands.  These are also the values saved in the EEPROM.
#define COMMAND_ESCAPE '~'
#define COMMAND_POLARITY_MARK_HIGH '0'
#define COMMAND_POLARITY_MARK_LOW  '1'
#define COMMAND_45BAUD '4'
#define COMMAND_50BAUD '5'
#define COMMAND_75BAUD '7'
#define COMMAND_100BAUD '9'
#define COMMAND_DUMP_CONFIG '?'

// Stop bit settings
#define STOP_BITS_1     1    // 1 stop bit
#define STOP_BITS_1R5   2    // 1.5 stop bits
#define STOP_BITS_2     3    // 2 stop bits

// TX USOS settings
#define USOS_OFF  1       //Assumes that RX will not reset to LTRS shift after space
//All shift symbols are explicit and spaces do not change
//shift state:
//  K0SM 599 05 NY NY
//     --> <LTR>K<FIG>0<LTR>SM <FIG>599 05 <LTR>NY NY

#define USOS_ON 2         //Space is an implicit LTRS shift character.  "Ham standard"
//demodulators operate in this mode.
//  K0SM 599 05 NY NY
//     --> <LTR>K<FIG>0<LTR>SM <FIG>599 <FIG>05 NY NY

#define USOS_MMTTY_HACK 3 //Essentially USOS OFF plus extra FIGS shifts for all words
//starting with numbers.  This is what MMTTY somewhat misleadingly
//calls "USOS transmission."  This settings makes many contest exchanges
//longer (and slightly more prone to bit errors) all to be
//compatible with MMTTY's non-USOS RX default
//  K0SM 599 05 NY NY
//     --> <LTR>K<FIG>0<LTR>SM <FIG>599 <FIG>05 <LTR>NY NY

#define FSK_MODE 0
#define CW_MODE 1

#endif // _CONSTANTS_H_
