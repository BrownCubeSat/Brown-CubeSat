/*
 * init_rtos_tasks.c
 *
 * Created: 10/4/2016 8:50:22 PM
 *  Author: mckenna
 */

#include "init_rtos_tasks.h"

void runit_2()
{
	//configure_i2c_master(SERCOM4);

	// Initialize EQUiStacks
	idle_readings_equistack = idle_Stack_Init();
	flash_readings_equistack = flash_Stack_Init();

	xTaskCreate(task_radio_transmit,
		"radio transmit action task",
		TASK_RADIO_TRANSMIT_STACK_SIZE,
		NULL,
		TASK_RADIO_TRANSMIT_PRIORITY,
		NULL);

	xTaskCreate(task_data_read_idle,
			"idle data reader",
			TASK_SENS_RD_IDLE_STACK_SIZE,
			NULL,
			TASK_SENS_RD_IDLE_PRIORITY,
			idle_task_handle);

	xTaskCreate(task_data_read_flash,
			"flash data reader",
			TASK_SENS_RD_FLASH_STACK_SIZE,
			NULL,
			TASK_SENS_RD_FLASH_PRIORITY,
			flash_task_handle);

	/*xTaskCreate(task_data_read_boot,
			"boot data reader",
			TASK_SENS_RD_BOOT_STACK_SIZE,
			NULL,
			TASK_SENS_RD_BOOT_PRIORITY,
			boot_task_handle);

	xTaskCreate(task_data_read_low_power,
			"low power data reader",
			TASK_SENS_RD_LOW_POWER_STACK_SIZE,
			NULL,
			TASK_SENS_RD_LOW_POWER_PRIORITY,
			boot_task_handle);*/

  /*xTaskCreate(test_free,
  		"Tests the freeing of structs",
  		TASK_SENS_RD_IDLE_STACK_SIZE,
  		NULL,
  		TASK_SENS_RD_IDLE_PRIORITY,
  		NULL);*/

  	// Make sure we define the first state
  	set_state_idle();

	/* Start the tasks and timer running. */
	vTaskStartScheduler();
}

void set_state_idle()
{
	CurrentState = IDLE;

	taskFrequencies[LED_TASK] =					idle_TASK_LED_FREQ;
	taskFrequencies[RADIO_TRANSMIT_TASK] =		idle_TASK_RADIO_TRANSMIT_FREQ;

	// TODO: we need to suspend the other tasks and somehow immediately add OR delete their interior structs and make a new one
	// Maybe look for changes in state inside the rtos tasks?
	// OR bring their current structs, etc. global so we can manually reset them? -> NOOOOO

	//vTaskSuspendAll(); TODO: Should we?
// 	vTaskSuspend(flash_task_handle);
// 	vTaskSuspend(boot_task_handle);
// 	vTaskSuspend(low_power_task_handle);
// 	vTaskResume(idle_task_handle);
}

void set_state_flash()
{
	CurrentState = FLASH;

	taskFrequencies[LED_TASK] =					flash_TASK_LED_FREQ;
	taskFrequencies[RADIO_TRANSMIT_TASK] =		flash_TASK_RADIO_TRANSMIT_FREQ;

	// TODO: ibid
	//vTaskSuspendAll(); TODO: Should we?
// 	vTaskSuspend(idle_task_handle);
// 	vTaskSuspend(boot_task_handle);
// 	vTaskSuspend(low_power_task_handle);
// 	vTaskResume(flash_task_handle);
}

void set_state_low_power()
{
	CurrentState = LOW_POWER;

	taskFrequencies[LED_TASK] =					low_power_TASK_LED_FREQ;
	taskFrequencies[RADIO_TRANSMIT_TASK] =		low_power_TASK_RADIO_TRANSMIT_FREQ;

	// TODO: ibid
	//vTaskSuspendAll(); TODO: Should we?
// 	vTaskSuspend(idle_task_handle);
// 	vTaskSuspend(flash_task_handle);
// 	vTaskSuspend(boot_task_handle);
// 	vTaskResume(low_power_task_handle);
}
