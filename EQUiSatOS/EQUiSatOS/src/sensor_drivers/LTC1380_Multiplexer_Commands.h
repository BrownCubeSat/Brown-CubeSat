/*
 * LTC1380_Multiplexer_Commands.h
 *
 * Created: 2/12/2017 3:51:29 PM
 *  Author: BSE
 */ 


#ifndef LTC1380_MULTIPLEXER_COMMANDS_H_
#define LTC1380_MULTIPLEXER_COMMANDS_H_

#include <global.h>
#include "../processor_drivers/I2C_Commands.h"

#define MULTIPLEXER_I2C 0x48

void LTC1380_init(void);
void LTC1380_channel_select(uint8_t target);
void LTC1380_disable(void);

#endif /* LTC1380_MULTIPLEXER_COMMANDS_H_ */