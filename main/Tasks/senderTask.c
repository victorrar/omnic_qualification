#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_log.h>

#include "senderTask.h"

#include "main.h"

xTaskHandle senderTaskHandle;

_Noreturn void senderTask() {
    TickType_t xLastWakeTime;
    uint32_t counter = 0;
    xLastWakeTime = xTaskGetTickCount();
    while(1){

        BaseType_t res = xQueueSend(queue, &counter, 0);

        if(res == pdFALSE){
            ESP_LOGE(CONFIG_LOG_TAG, "Queue overrun!");
        }

        counter++;
        vTaskDelayUntil(&xLastWakeTime, CONFIG_INCREMENT_PERIOD);
    }
}
