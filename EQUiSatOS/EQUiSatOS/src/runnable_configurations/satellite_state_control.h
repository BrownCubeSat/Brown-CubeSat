/*
 * init_rtos_tasks.h
 *
 * Created: 10/4/2016 8:47:48 PM
 *  Author: mckenna
 */

#ifndef SATELLITE_STATE_CONTROL_H
#define SATELLITE_STATE_CONTROL_H

#include "rtos_tasks/rtos_tasks.h"
#include "data_handling/equistack.h"

#include "testing_tasks.h"
#include "testing_functions/struct_tests.h"
#include "testing_functions/sat_data_tests.h"

/************************************************************************/
/* Satellite state constructs                                           */
/************************************************************************/
// array wrapped in struct to allow easy copying specification in #defines
typedef struct task_states {
	bool states[NUM_TASKS];
} task_states;

/************************************************************************/
/* Defined task state sets - order must match enum in rtos_tasks_config.h: */
/************************************************************************/
//													WDOG,  STATE,	(ant),	BAT,	TRANS,	FLASH,	IDLE,  	LOWP,	ATTI,	PERSIST
#define INITIAL_TASK_STATES			((task_states){{true,	true,	false,	true,	false,	false,	false,	false,	true,   true}})
#define ANTENNA_DEPLOY_TASK_STATES	((task_states){{true,	true,	false,	true,	false,	false,	false,	false,	true,   true}})
#define HELLO_WORLD_TASK_STATES		((task_states){{true,	true,	false,	true,	true,	false,	true,	false,	true,   true}})
#define IDLE_NO_FLASH_TASK_STATES	HELLO_WORLD_TASK_STATES
#define IDLE_FLASH_TASK_STATES 		((task_states){{true,	true,	false,	true,	true,	true,	true,	false,	true,   true}})
#define LOW_POWER_TASK_STATES 		((task_states){{true,	true,	false,	true,	true,	false,	false,	true,	false, 	true}})
// **see .c file for ir power states**

// duration to wait to get each of ALL the mutexes in sequence (LONG because we really need this)
#define TASK_STATE_CHANGE_MUTEX_WAIT_TIME_TICKS		(5000 / portTICK_PERIOD_MS)
#define TASK_STATE_CHANGE_MUTEX_TAKE_RETRIES		5

#if PRINT_DEBUG != 0
	bool rtos_started;
#endif

/************************************************************************/
/* global hardware states												
   (used primarily to know what currents to expect, etc.)		
   		
   This mutex is take briefly by any hardware changing state,
   such that any section of code that must be run with a consistent hardware
   state can take the hardware state mutex and be assured of the state in 
   this struct.
   
   Places where we need to be sure of the state in this struct
   (other places use other methods, namely the lower-level peripheral mutexes):
	   1. Validation of regulator voltages
	   2. Measuring battery currents									*/
/************************************************************************/ 
typedef enum {
	RADIO_OFF = 0,
	RADIO_IDLE = 1,
	RADIO_TRANSMITTING,
} radio_state_t;

struct hw_states {
	/* locked by peripheral mutexes - mainly done to simplify function arguments */
	bool rail_5v_enabled : 1;
	/* locked by hardware state mutex */
	radio_state_t radio_state : 2; // if >0, both 3V6 regulator and radio power pin are on	
	bool antenna_deploying : 1;
	/* note: flashing state is passed down */
};
#define HARDWARE_STATE_MUTEX_WAIT_TIME_TICKS	(500 / portTICK_PERIOD_MS)

/************************************************************************/
/* Mutex for major satellite operations that should be mutually exclusive*/
/************************************************************************/
#define CRITICAL_MUTEX_WAIT_TIME_TICKS			(5000 / portTICK_PERIOD_MS) // these can take quite a while
StaticSemaphore_t _critical_action_mutex_d;
SemaphoreHandle_t critical_action_mutex;

/************************************************************************/
/* State functions                                                      */
/************************************************************************/
sat_state_t get_sat_state(void);
bool set_sat_state(sat_state_t state);
task_states get_sat_task_states(void);
void task_resume_safe(task_type_t task_id);
bool check_task_state_consistency(void);
bool low_power_active(void);

// hardware-specific functions
struct hw_states* get_hw_states(void);
BaseType_t hardware_state_mutex_take(void);
void hardware_state_mutex_give(void);

void run_rtos(void);
void init_task_state(task_type_t task);

/* TEMPORARY GLOBAL SET STATE FUNCTIONS FOR TESTING - DONT YOU DARE USE THESE */
bool set_sat_state_helper(sat_state_t state);
void set_all_task_states(const task_states states, sat_state_t state, sat_state_t prev_sat_state);
void task_suspend(task_type_t task_id);
void task_resume(task_type_t task_id);

#endif
