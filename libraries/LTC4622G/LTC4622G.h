/*
 *  LTC4622G Library for Arduino
 *
 *  Created by Nikolai Rinas on 11/10/2016.
 *  Copyright (c) 2016 Nikolai Rinas. All rights reserved.
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
  
 *   You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef LTC4622G_h
#define LTC4622G_h
#include <Arduino.h>

// 
//   ----A----    
//   |       |    
//   F       B  
//   |---G---|    
//   E       C  
//   |       |    
//   ----D----    
//           | DP

class LTC4622G {
public:
  LTC4622G();
  LTC4622G(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7, uint8_t p8, uint8_t p9);
  void update();
  void setValue(float number){gf_value=number;};
  
private:
  uint8_t P1;
  uint8_t P2;
  uint8_t P3;
  uint8_t P4;
  uint8_t P5;
  uint8_t P6;
  uint8_t P7;
  uint8_t P8;
  uint8_t P9;
  float gf_value = 0.0;
  
  void displayNumber(float number);
  void lightDigit1(byte number, boolean dp);
  void lightDigit2(byte number, boolean dp);
  void lightSegment1(byte segment);
  void lightSegment2(byte segment);
  void lightDigit0();
};

#endif