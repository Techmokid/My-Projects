/**
 @file FaBoOLED_EROLED096.h
 @brief This is a library for the FaBo OLED I2C Brick.

   http://fabo.io/214.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#ifndef FABOOLED_EROLED096_H
#define FABOOLED_EROLED096_H

#include <Arduino.h>
#include <Print.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include "FaBoOLED_font.h"
#include "FaBoOLED_bmp.h"

#define EROLED096_SLAVE_ADDRESS 0x3C ///< ER-OLED0.96 I2C Slave Address

/**
 @class FaBoOLED_EROLED096
 @brief FaBo OLED I2C Controll class
*/
class FaBoOLED_EROLED096 : public Print {
  public:
    FaBoOLED_EROLED096(uint8_t addr = EROLED096_SLAVE_ADDRESS);
    void init(void);
    void begin(void);
    void showBitmap(void);
    void clear(void);
    void home(void);
    void setCursor(uint8_t col, uint8_t row);
    void setCommand(uint8_t value);
    void setAddress(uint8_t row, uint8_t col_s, uint8_t col_e);
    void writeData(uint8_t value);
    virtual size_t write(uint8_t value);
  private:
    uint8_t _i2caddr;
    uint8_t _cur_x;
    uint8_t _cur_y;
    void send(uint8_t value, uint8_t mode);
};

#endif // FABOOLED_EROLED096_H
