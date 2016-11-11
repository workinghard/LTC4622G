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

#include "LTC4622G.h"

// 89672345
// Digit2 => A: 10000111
//           B: 10000100
//           C: 10000010
//           D: 01001000
//           E: 01000100
//           F: 01000010
//           G: 01000001
//          DP: 10000001

// Digit3 => A: 00101000
//           B: 00100100
//           C: 00100010
//           D: 00011000
//           E: 00010100
//           F: 00010010
//           G: 00010001
//          DP: 00100001

// 0 => ABCDEF-
// 1 => -BC----
// 2 => AB-DE-G
// 3 => ABCD--G
// 4 => -BC--FG
// 5 => A-CD-FG
// 6 => A-CDEFG
// 7 => ABC----
// 8 => ABCDEFG
// 9 => ABCD-FG

const boolean segment1[8][8] = { {1,0,0,0,0,1,1,1},
                                 {1,0,0,0,1,0,1,1},
                                 {1,0,0,0,1,1,0,1},
                                 {0,1,0,0,0,1,1,1},
                                 {0,1,0,0,1,0,1,1},
                                 {0,1,0,0,1,1,0,1},
                                 {0,1,0,0,1,1,1,0},
                                 {1,0,0,0,1,1,1,0}
};
 
const boolean segment2[8][8] = { {0,0,1,0,0,1,1,1},
                                 {0,0,1,0,1,0,1,1},
                                 {0,0,1,0,1,1,0,1},
                                 {0,0,0,1,0,1,1,1},
                                 {0,0,0,1,1,0,1,1},
                                 {0,0,0,1,1,1,0,1},
                                 {0,0,0,1,1,1,1,0},
                                 {0,0,1,0,1,1,1,0}
};

// Segments that make each number
const boolean numbers[10][7] = { {1,1,1,1,1,1,0},
                                 {0,1,1,0,0,0,0},
                                 {1,1,0,1,1,0,1},
                                 {1,1,1,1,0,0,1},
                                 {0,1,1,0,0,1,1},
                                 {1,0,1,1,0,1,1},
                                 {1,0,1,1,1,1,1},
                                 {1,1,1,0,0,0,0},
                                 {1,1,1,1,1,1,1},
                                 {1,1,1,1,0,1,1}
};

LTC4622G::LTC4622G(){
  P1=2;P2=3;P3=4;P4=5;P5=6;P6=7;P7=8;P8=12;P9=13;
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P8, OUTPUT);
  pinMode(P9, OUTPUT);
}
LTC4622G::LTC4622G(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7, uint8_t p8, uint8_t p9){
  P1=p1;P2=p2;P3=p3;P4=p4;P5=p5;P6=p6;P7=p7;P8=p8;P9=p9;
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P8, OUTPUT);
  pinMode(P9, OUTPUT);
}

void LTC4622G::update() {
  displayNumber(gf_value);
}

void LTC4622G::displayNumber(float number) {
  // Display: 0,1 ... 19,9
  //          20  ... 199
  if ( number < 1 ) { // 0 ... 0,9
    int decimal = number * 10;
    lightDigit1(0,true);
    lightDigit2(decimal, false);
  }else{
    if ( number < 20 ) { // 1 ... 19,9
      if ( number >= 10 ) {
        lightDigit0();
      }
      int decimal1 = (int)number % 10;
      int decimal2 = int(number * 10 ) % 10;
      lightDigit1(decimal1, true);
      lightDigit2(decimal2, false);
    }else{
      if ( number < 200 ) { // 20 ... 199
        if ( number >= 100 ) {
          lightDigit0();
        }
        int decimal1 = (int)(number / 10) % 10;
        int decimal2 = (int)number % 10;
        lightDigit1(decimal1, false);
        lightDigit2(decimal2, false);
      }
    }
  }
}

void LTC4622G::lightDigit1(byte number, boolean dp) {
  for (int i = 0; i < 7; i++) {
    if ( numbers[number][i] == 1 ) {
      lightSegment1(i);
    }
  }
  if ( true == dp ) {
    lightSegment1(7);
  }
}
void LTC4622G::lightDigit2(byte number, boolean dp) {
  for (int i = 0; i < 7; i++) {
    if ( numbers[number][i] == 1 ) {
      lightSegment2(i);
    } 
  }
  if ( true == dp ) {
    lightSegment2(7);
  }
}

void LTC4622G::lightSegment1(byte segment) {
// i == rails to activate
// order == 89672345
  digitalWrite(P8, segment1[segment][0]);
  digitalWrite(P9, segment1[segment][1]);
  digitalWrite(P6, segment1[segment][2]);
  digitalWrite(P7, segment1[segment][3]);
  digitalWrite(P2, segment1[segment][4]);
  digitalWrite(P3, segment1[segment][5]);
  digitalWrite(P4, segment1[segment][6]);
  digitalWrite(P5, segment1[segment][7]);
  digitalWrite(P1, HIGH);
  delay(1);
  //Serial.println(segment);
}
void LTC4622G::lightSegment2(byte segment) {
// i == rails to activate
// order == 89672345
  digitalWrite(P8, segment2[segment][0]);
  digitalWrite(P9, segment2[segment][1]);
  digitalWrite(P6, segment2[segment][2]);
  digitalWrite(P7, segment2[segment][3]);
  digitalWrite(P2, segment2[segment][4]);
  digitalWrite(P3, segment2[segment][5]);
  digitalWrite(P4, segment2[segment][6]);
  digitalWrite(P5, segment2[segment][7]);
  digitalWrite(P1, HIGH);
  delay(1);
}
void LTC4622G::lightDigit0() {
  // We can disply only 1
  // order == 89672345
  digitalWrite(P8, HIGH);
  digitalWrite(P9, LOW);
  digitalWrite(P6, LOW);
  digitalWrite(P7, LOW);
  digitalWrite(P1, LOW);
  digitalWrite(P2, HIGH);
  digitalWrite(P3, HIGH);
  digitalWrite(P4, HIGH);
  digitalWrite(P5, HIGH);   
  delay(3);
}