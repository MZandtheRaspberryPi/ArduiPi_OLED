/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

02/18/2013  Charles-Henri Hallard (http://hallard.me)
            Modified for compiling and use on Raspberry ArduiPi Board
            LCD size and connection are now passed as arguments on
            the command line (no more #define on compilation needed)
            ArduiPi project documentation http://hallard.me/arduipi

07/26/2013  Charles-Henri Hallard (http://hallard.me)
            modified name for generic library using different OLED type

*********************************************************************/

#ifndef _ArduiPi_OLED_H
#define _ArduiPi_OLED_H

#include "./Adafruit_GFX.h"
#include "bcm2835.h"

#include <cerrno>
#include <ctime>
#include <unistd.h>

namespace Arduipi_NS {

#define BLACK 0
#define WHITE 1

#define OLED_ADAFRUIT_SPI_128x32 0
#define OLED_ADAFRUIT_SPI_128x64 1
#define OLED_ADAFRUIT_I2C_128x32 2
#define OLED_ADAFRUIT_I2C_128x64 3
#define OLED_SEEED_I2C_128x64 4
#define OLED_SEEED_I2C_96x96 5
#define OLED_SH1106_I2C_128x64 6

// Configuration Pin for ArduiPi board
#define OLED_SPI_RESET RPI_V2_GPIO_P1_22 /* GPIO 25 pin 22  */
#define OLED_SPI_DC RPI_V2_GPIO_P1_18    /* GPIO 24 pin 18  */
#define OLED_SPI_CS0 BCM2835_SPI_CS0     /* Chip Select CE0 */
#define OLED_SPI_CS1 BCM2835_SPI_CS1     /* Chip Select CE1 */
#define OLED_SPI_CS BCM2835_SPI_CS1      /* Default Chip Select */
#define OLED_I2C_RESET RPI_V2_GPIO_P1_22 /* GPIO 25 pin 12  */

// OLED type I2C Address
#define ADAFRUIT_I2C_ADDRESS 0x3C /* 011110+SA0+RW - 0x3C or 0x3D */
// Address for 128x32 is 0x3C
// Address for 128x32 is 0x3D (default) or 0x3C (if SA0 is grounded)

#define SEEED_I2C_ADDRESS 0x3C /* 011110+SA0+RW - 0x3C or 0x3D */

#define SH1106_I2C_ADDRESS 0x3C

// Arduino Compatible Macro
#define _BV(bit) (1 << (bit))

/*=========================================================================
    SSDxxxx Common Displays
    -----------------------------------------------------------------------
    Common values to all displays
=========================================================================*/

//#define SSD_Command_Mode      0x80  /* DC bit is 0 */ Seeed set C0 to 1 why ?
#define SSD_Command_Mode 0x00 /* C0 and DC bit are 0         */
#define SSD_Data_Mode 0x40    /* C0 bit is 0 and DC bit is 1 */

#define SSD_Set_Segment_Remap 0xA0
#define SSD_Inverse_Display 0xA7
#define SSD_Set_Muliplex_Ratio 0xA8

#define SSD_Display_Off 0xAE
#define SSD_Display_On 0xAF

#define SSD_Set_ContrastLevel 0x81

#define SSD_External_Vcc 0x01
#define SSD_Internal_Vcc 0x02

#define SSD_Set_Column_Address 0x21
#define SSD_Set_Page_Address 0x22

#define SSD_Activate_Scroll 0x2F
#define SSD_Deactivate_Scroll 0x2E

#define SSD_Right_Horizontal_Scroll 0x26
#define SSD_Left_Horizontal_Scroll 0x27

#define Scroll_Left 0x00
#define Scroll_Right 0x01

#define Scroll_2Frames 0x07
#define Scroll_3Frames 0x04
#define Scroll_4Frames 0x05
#define Scroll_5Frames 0x00
#define Scroll_25Frames 0x06
#define Scroll_64Frames 0x01
#define Scroll_128Frames 0x02
#define Scroll_256Frames 0x03

#define VERTICAL_MODE 01
#define PAGE_MODE 01
#define HORIZONTAL_MODE 02

/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/

#define SSD1306_Entire_Display_Resume 0xA4
#define SSD1306_Entire_Display_On 0xA5

#define SSD1306_Normal_Display 0xA6

#define SSD1306_Set_Display_Offset 0xD3
#define SSD1306_Set_Com_Pins 0xDA
#define SSD1306_Set_Vcomh_Deselect_Level 0xDB
#define SSD1306_Set_Display_Clock_Div 0xD5
#define SSD1306_Set_Precharge_Period 0xD9
#define SSD1306_Set_Lower_Column_Start_Address 0x00
#define SSD1306_Set_Higher_Column_Start_Address 0x10
#define SSD1306_Set_Start_Line 0x40
#define SSD1306_Set_Memory_Mode 0x20
#define SSD1306_Set_Com_Output_Scan_Direction_Normal 0xC0
#define SSD1306_Set_Com_Output_Scan_Direction_Remap 0xC8
#define SSD1306_Charge_Pump_Setting 0x8D

// Scrolling #defines
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

/*=========================================================================
    SSD1308 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/
#define SSD1308_Normal_Display 0xA6

/*=========================================================================
    SSD1327 Displays
    -----------------------------------------------------------------------
    The driver is used in Seeed 96x96 display
=========================================================================*/
#define SSD1327_Set_Display_Start_Line 0xA1
#define SSD1327_Set_Display_Offset 0xA2
#define SSD1327_Normal_Display 0xA4
#define SSD1327_Set_Display_Clock_Div 0xB3
#define SSD1327_Set_Command_Lock 0xFD
#define SSD1327_Set_Column_Address 0x15
#define SSD1327_Set_Row_Address 0x75

#define SSD1327_Set_Row_Address 0x75

/*=========================================================================
    SH1106 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
=========================================================================*/
#define SH1106_Set_Page_Address 0xB0

class ArduiPi_OLED : public Adafruit_GFX {
public:
  ArduiPi_OLED();

  // SPI Init
  bool init(int8_t DC, int8_t RST, int8_t CS, uint8_t OLED_TYPE);

  // I2C Init
  bool init(int8_t RST, uint8_t OLED_TYPE);

  bool oled_is_spi_proto(uint8_t OLED_TYPE); /* to know protocol before init */
  bool select_oled(uint8_t OLED_TYPE);

  void begin(void);
  void close(void);

  void sendCommand(uint8_t c);
  void sendCommand(uint8_t c0, uint8_t c1);
  void sendCommand(uint8_t c0, uint8_t c1, uint8_t c2);
  void sendData(uint8_t c);

  void clearDisplay(void);
  void setGrayLevel(uint8_t grayLevel);
  void setBrightness(uint8_t Brightness);
  void invertDisplay(uint8_t i);
  void display();

  void setSeedTextXY(unsigned char Row, unsigned char Column);
  void putSeedChar(char C);
  void putSeedString(const char *String);

  int16_t getOledWidth(void);
  int16_t getOledHeight(void);

  void startscrollright(uint8_t start, uint8_t stop);
  void startscrollleft(uint8_t start, uint8_t stop);

  void startscrolldiagright(uint8_t start, uint8_t stop);
  void startscrolldiagleft(uint8_t start, uint8_t stop);
  void setHorizontalScrollProperties(bool direction, uint8_t startRow,
                                     uint8_t endRow, uint8_t startColumn,
                                     uint8_t endColumn, uint8_t scrollSpeed);
  void stopscroll(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

private:
  uint8_t *poledbuff; // Pointer to OLED data buffer in memory
  int8_t _i2c_addr, dc, rst, cs;
  int16_t oled_width, oled_height;
  int16_t oled_buff_size;
  uint8_t vcc_type;
  uint8_t oled_type;
  uint8_t grayH, grayL;

  inline bool isI2C(void);
  inline bool isSPI(void);
  void fastSPIwrite(uint8_t c);
  void fastSPIwrite(char *tbuf, uint32_t len);
  void fastI2Cwrite(uint8_t c);
  void fastI2Cwrite(char *tbuf, uint32_t len);
  void slowSPIwrite(uint8_t c);

  // volatile uint8_t *dcport;
  // uint8_t dcpinmask;
};
} // namespace Arduipi_NS

#endif
