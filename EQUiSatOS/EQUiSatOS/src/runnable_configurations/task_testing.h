/*
 * task_testing.h
 *
 * Created: 1/30/2017 3:58:20 PM
 *  Author: mckenna
 */ 

#ifndef TASK_TESTING_H_
#define TASK_TESTING_H_

#include <global.h>
#include "task.h"
#include "semphr.h"

TaskHandle_t suicide_test_handle;

void task_suicide_test(void *pvParameters);
void task_stack_size_overflow_test(void *pvParameters);

#endif /* TASK_TESTING_H_ */