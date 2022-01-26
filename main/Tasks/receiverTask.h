#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#ifndef OMNIC_QUALIFICATION_RECEIVERTASK_H
#define OMNIC_QUALIFICATION_RECEIVERTASK_H

#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern xTaskHandle receiverTaskHandle;

typedef void (*receiverCallback_t)(uint32_t, uint32_t);

_Noreturn void receiverTask(void *callback);

#endif //OMNIC_QUALIFICATION_RECEIVERTASK_H
