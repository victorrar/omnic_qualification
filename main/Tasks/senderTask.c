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

/**
 * Task sends counter value every CONFIG_LOG_TAG milliseconds to the queue
 * period can be set via idf.py menuconfig
 */
_Noreturn void senderTask() {
    TickType_t xLastWakeTime;
    uint32_t counter = 0;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        //this will ensure stable tick rate, independent from the task code execution time and preemption
        BaseType_t res;

        res = xTaskDelayUntil(&xLastWakeTime, CONFIG_INCREMENT_PERIOD);
        if (res == pdTRUE) {
            ESP_LOGE(CONFIG_LOG_TAG, "Can't keep senderTask execution rate! Is CPU overloaded?");
        }

        res = xQueueSend(queue, &counter, 0);
        if (res == pdFALSE) {
            ESP_LOGE(CONFIG_LOG_TAG, "senderTask's queue overrun!");
        }

        counter++;
    }
}
