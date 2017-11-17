/*
 * IncFile1.h
 *
 * Created: 10/15/2017 3:21:50 PM
 *  Author: rj16
 */ 


#ifndef BATTERY_CHARGING_TASK_H_
#define BATTERY_CHARGING_TASK_H_

#define BATTERY_DEBUG

#include "global.h"
#include "rtos_tasks.h"

// TODO: are there different thresholds for LifePo?
// thresholds for making very critical charging decisions, including when to go into low power mode
// and when to declare end of life
#define critical   40
#define low        70
#define med        85
#define high       90
#define full       95

// difference between battery percentages that's considered significant enough to change the charhing plan
#define difference 10

extern bool batt_charging[4];
extern int batt_strikes[4];

// defines each battery and/or bank
typedef enum
{	
	LION_ONE = 0,
	LION_TWO,
	LIFE_PO_BANK_ONE,
	LIFE_PO_BANK_TWO,
	LIFE_PO_BANK_ONE_BAT_ONE,
	LIFE_PO_BANK_ONE_BAT_TWO,
	LIFE_PO_BANK_TWO_BAT_ONE,
	LIFE_PO_BANK_TWO_BAT_TWO
} battery;

typedef enum
{
	FILL_LION,
	FILL_LIFE_PO
} charge_state;

void battery_logic(int lion_one_percentage, int lion_two_percentage, int life_po_bank_one_percentage, int life_po_bank_two_percentage);
void check_for_end_of_life(int lion_one_percentage, int lion_two_percentage);
void battery_charging_task(void *pvParameters);

#endif /* BATTERY_CHARGING_TASK_H_ */