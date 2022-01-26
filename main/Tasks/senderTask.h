#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#ifndef OMNIC_QUALIFICATION_SENDERTASK_H
#define OMNIC_QUALIFICATION_SENDERTASK_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern xTaskHandle senderTaskHandle;

_Noreturn void senderTask();

#endif //OMNIC_QUALIFICATION_SENDERTASK_H
