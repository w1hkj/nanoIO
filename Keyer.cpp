//======================================================================
//
//  nanoIO paddle keyer (c) 2018, David Freese, W1HKJ
//
//  based on code from Iambic Keyer Code Keyer Sketch
//  Copyright (c) 2009 Steven T. Elliott
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details:
//
//  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//  Boston, MA  02111-1307  USA
//
//======================================================================

#include "Arduino.h"
#include "TimerOne.h"
#include "Keyer.h"

//#define ST_Freq 600   // Set the Sidetone Frequency to 600 Hz

//======================================================================
//  keyerControl bit definitions
//
#define     DIT_L      0x01     // Dit latch
#define     DAH_L      0x02     // Dah latch
#define     DIT_PROC   0x04     // Dit is being processed
#define     PDLSWAP    0x08     // 0 for normal, 1 for swap
//======================================================================
//
//  State Machine Defines

enum KSTYPE {IDLE, CHK_DIT, CHK_DAH, KEYED_PREP, KEYED, INTER_ELEMENT };

Keyer::Keyer(int wpm, float weight)
{
	ptt_pin_ = PTT_PIN;
	cw_pin_ = CW_PIN;
// Setup outputs
	pinMode(LP_in, INPUT);            // sets Left Paddle digital pin as input
	pinMode(RP_in, INPUT);            // sets Right Paddle digital pin as input

//  pinMode(ST_Pin, OUTPUT);          // Sets the Sidetone digital pin as output

	digitalWrite(LP_in, HIGH);        // Enable pullup resistor on Left Paddle Input Pin
	digitalWrite(RP_in, HIGH);        // Enable pullup resistor on Right Paddle Input Pin

	keyerState = IDLE;
	keyerControl = 0;
	key_mode = IAMBICA;
  _weight = weight;

  _speed = wpm;
  calc_ratio();
}

// Calculate the length of dot, dash and silence
void Keyer::calc_ratio()
{
  float w = (1 + _weight) / (_weight -1);
  _space_len = (1200 / _speed);
  _dotlen = _space_len * (w - 1);
  _dashlen =  (1 + w) * _space_len;
}

void Keyer::cw_pin(int pin)
{
	ptt_pin_ = pin;
}

void Keyer::ptt_pin(int pin)
{
	cw_pin_ = pin;
}

void Keyer::set_mode(int md)
{
  key_mode = md;
}

void Keyer::wpm(int wpm)
{
  _speed = wpm;
  calc_ratio();
}
//======================================================================
//    Latch paddle press
//======================================================================

void Keyer::update_PaddleLatch()
{
	if (digitalRead(RP_in) == LOW) {
		keyerControl |= DIT_L;
	}
	if (digitalRead(LP_in) == LOW) {
		keyerControl |= DAH_L;
	}
}

bool Keyer::do_paddles()
{
	if (key_mode == STRAIGHT) { // Straight Key
		if ((digitalRead(LP_in) == LOW) || (digitalRead(RP_in) == LOW)) {
// Key from either paddle
			digitalWrite(ptt_pin_, HIGH);
			digitalWrite(cw_pin_, HIGH);
//      tone(ST_Pin, 600);
			return true;
		} else {
			digitalWrite(ptt_pin_, LOW);
			digitalWrite(cw_pin_, LOW);
//      noTone(ST_Pin);
		}
		return false;
	}

// keyerControl contains processing flags and keyer mode bits
// Supports Iambic A and B
// State machine based, uses calls to millis() for timing.
  switch (keyerState) {
    case IDLE:      // Wait for direct or latched paddle press
      if ((digitalRead(LP_in) == LOW) || (digitalRead(RP_in) == LOW) || (keyerControl & 0x03)) {
        update_PaddleLatch();
        keyerState = CHK_DIT;
        return true;
      }
      return false;
//      break;
    case CHK_DIT:      // See if the dit paddle was pressed
      if (keyerControl & DIT_L) {
        keyerControl |= DIT_PROC;
        ktimer = _dotlen;
        keyerState = KEYED_PREP;
        return true;
      }  // fall through
        keyerState = CHK_DAH;
    case CHK_DAH:      // See if dah paddle was pressed
      if (keyerControl & DAH_L) {
        ktimer = _dashlen;
        keyerState = KEYED_PREP;
        return true;
      } else {
        keyerState = IDLE;
        return false;
      }
//      break;
    case KEYED_PREP:                     // Assert key down, start timing
                                         // state shared for dit or dah
      digitalWrite(ptt_pin_, HIGH);      // Enable PTT
//      tone(ST_Pin, ST_Freq);           // Turn the Sidetone on
      digitalWrite(cw_pin_, HIGH);       // Key the CW line
      ktimer += millis();                // set ktimer to interval end time
      keyerControl &= ~(DIT_L + DAH_L);  // clear both paddle latch bits
      keyerState = KEYED;                // next state
      return true;
//      break;
    case KEYED:                          // Wait for timer to expire
      if (millis() > ktimer) {           // are we at end of key down ?
        digitalWrite(ptt_pin_, LOW);     // Disable PTT 
//        noTone(ST_Pin);                // Turn the Sidetone off
        digitalWrite(cw_pin_, LOW);      // Unkey the CW line
        ktimer = millis() + _space_len;  // inter-element time
        keyerState = INTER_ELEMENT;      // next state
        return true;
      }
      else if (key_mode == IAMBICB)     // Iambic B Mode ?
        update_PaddleLatch();           // yes, early paddle latch in Iambic B mode
      return true;
//      break;

    case INTER_ELEMENT:                 // Insert time between dits/dahs
      update_PaddleLatch();             // latch paddle state
      if (millis() > ktimer) {          // are we at end of inter-space ?
        if (keyerControl & DIT_PROC) {  // was it a dit or dah ?
          keyerControl &= ~(DIT_L + DIT_PROC);   // clear two bits
          keyerState = CHK_DAH;                  // dit done, check for dah
          return true;
        } else {
          keyerControl &= ~(DAH_L);     // clear dah latch
          keyerState = IDLE;            // go idle
          return false;
        }
      }
      return true;
//      break;
  }
}


