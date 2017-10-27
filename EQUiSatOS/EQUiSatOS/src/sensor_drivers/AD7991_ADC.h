/*
 * AD7991_ADC.h
 *
 * Created: 2/19/2017 4:22:22 PM
 *  Author: BSE
 */ 


#ifndef AD7991_ADC_H_
#define AD7991_ADC_H_

#include <global.h>
#include "../processor_drivers/I2C_Commands.h"

#define AD7991_ADDR_0 0b0101000 //0x28 battery board
#define AD7991_ADDR_1 0b0101001 //0x29 control board
#define AD7991_SHOULD_STOP false

enum status_code AD7991_init(void);
enum status_code AD7991_read_all(uint16_t *results, uint8_t addr);

#endif /* AD7991_ADC_H_ */