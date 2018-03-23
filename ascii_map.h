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

#ifndef _ASCIIMAP_H_
#define _ASCIIMAP_H_

/// Mapping of ascii to baudot symbols.  This is the translation table 
/// that maps an incoming ASCII byte on the serial interface to aN
/// equivalent (or reasonable substitute) that exists the ITA2 or 
/// US 5-bit code.
/// In general, any ASCII control character will be mapped to a Baudot 
/// NULL.  Punctuation will be mapped to '?' if there is no equivalent 
/// in the Baudot set.  Note that some punctuation such as '[', ']' and 
/// '\' are used to control the PTT behavior.  Tilda (~) is used to enter 
/// the configuration menu.  You can use your imagination to add other 
/// control functions here.

int asciiToBaudot[127] = {

//         ASCII             ASCII INDEX (decimal)
  0,//  Null character             0
  0,//  Start of Header            1
  0,//  Start of Text              2
  0,//  End of Text                3
  0,//  End of Transmission        4
  0,//  Enquiry                    5
  0,//  Acknowledgment             6
  5,//  Bell                       7
  0,//  Backspace                  8
  0,//  Horizontal Tab             9
  2,//  Line feed                 10
  0,//  Vertical Tab              11
  0,//  Form feed                 12
  8,//  Carriage return           13
  0,//  Shift Out                 14
  0,//  Shift In                  15
  0,//  Data Link Escape          16
  0,//  Device Control 1          17
  0,//  Device Control 2          18
  0,//  Device Control 3          19
  0,//  Device Control 4          20
  0,//  Negative Acknowledgement  21
  0,//  Synchronous idle          22
  0,//  End of Transmission Block 23
  0,//  Cancel                    24
  0,//  End of Medium             25
  0,//  Substitute                26
  0,//  Escape                    27
  0,//  File Separator            28
  0,//  Group Separator           29
  0,//  Record Separator          30
  0,//  Unit Separator            31
  4,//  space                     32
  13,// !                         33
  17,// "                         34
  20,// #                         35
  9,//  $                         36
  25,// %                         37
  26,// &                         38
  11,// '                         39
  15,// (                         40
  18,// )                         41
  25,// *                         42
  17,// +                         43  //ITA2
  12,// ,                         44
  3,//  -                         45
  28,// .                         46
  29,// /                         47
  22,// 0                         48
  23,// 1                         49
  19,// 2                         50
  1,//  3                         51
  10,// 4                         52
  16,// 5                         53
  21,// 6                         54
  7,//  7                         55
  6,//  8                         56
  24,// 9                         57
  14,// :                         58
  30,// ;                         59
  25,// <                         60
  30,// =                         61 //ITA2
  25,// >                         62
  25,// ?                         63
  25,// @                         64
  3,//  A                         65
  25,// B                         66
  14,// C                         67
  9,//  D                         68
  1,//  E                         69
  13,// F                         70
  26,// G                         71
  20,// H                         72
  6,//  I                         73
  11,// J                         74
  15,// K                         75
  18,// L                         76
  28,// M                         77
  12,// N                         78
  24,// O                         79
  22,// P                         80
  23,// Q                         81
  10,// R                         82
  5,//  S                         83
  16,// T                         84
  7,//  U                         85
  30,// V                         86
  19,// W                         87
  29,// X                         88
  21,// Y                         89
  17,// Z                         90
  15,// [ Used to start TX        91
  20,// \ Used to escape TX       92
  18,// ] Buffered end TX         93
  25,// ^                         94
  4,//  _                         95
  25,// `                         96
  3,//  a                         97
  25,// b                         98
  14,// c                         99
  9,//  d                        100
  1,//  e                        101
  13,// f                        102
  26,// g                        103
  20,// h                        104
  6,//  i                        105
  11,// j                        106
  15,// k                        107
  18,// l                        108
  28,// m                        109
  12,// n                        110
  24,// o                        111
  22,// p                        112
  23,// q                        113
  10,// r                        114
  5,//  s                        115
  16,// t                        116
  7,//  u                        117
  30,// v                        118
  19,// w                        119
  29,// x                        120
  21,// y                        121
  17,// z                        122
  15,// {                        123
  20,// |                        124
  18,// }                        125
  25 // ~ Command escape char    126
};

#endif // _ASCIIMAP_H_
