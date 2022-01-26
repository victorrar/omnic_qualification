#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "receiverTask.h"

#include "main.h"

xTaskHandle receiverTaskHandle;

/**
 * Task receives counter values from the queue and sends them to the supplied callback
 * @param callback Must be receiverCallback_t type [void callback(uint32_t counterValue, uint32_t period)]
 */
_Noreturn void receiverTask(void *callback) {
    uint32_t lastTick = xTaskGetTickCount();

    while (true) {
        uint32_t counterValue = 0;  //received counter value
        BaseType_t res = xQueueReceive(queue, &counterValue, portMAX_DELAY);

        if (res == pdTRUE) {
            uint32_t currentTick = xTaskGetTickCount();
            ((receiverCallback_t) callback)(counterValue, pdTICKS_TO_MS(currentTick - lastTick));
            lastTick = currentTick;
        }

    }
}