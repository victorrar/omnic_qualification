#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "receiverTask.h"

#include "main.h"

xTaskHandle receiverTaskHandle;

uint32_t lastTick = 0;

_Noreturn void receiverTask(void *callback) {
    lastTick = xTaskGetTickCount();
    while (true) {
        uint32_t counterValue = 0;
        BaseType_t val = xQueueReceive(queue, &counterValue, portMAX_DELAY);
        if (val == pdTRUE) {
            uint32_t currentTick = xTaskGetTickCount();
            ((receiverCallback_t) callback)(counterValue, pdTICKS_TO_MS(currentTick - lastTick));
            lastTick = currentTick;
        }
    }
}