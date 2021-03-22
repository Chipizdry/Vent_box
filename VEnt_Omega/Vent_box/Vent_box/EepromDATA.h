


#ifndef EEPROMDATA_H_
#define EEPROMDATA_H_
#include "main.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData); // Запись в EEPROM

unsigned char EEPROM_read(unsigned int uiAddress); //Чтение из EEPROM

#endif /* EEPROMDATA_H_ */