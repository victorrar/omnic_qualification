#include <stdint.h>
#include <esp_log.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "sdkconfig.h"

#include "senderTask.h"
#include "receiverTask.h"

#include "main.h"


/**
 * Queue for transfering the counter value from the senderTask to the receiverTask
 */
xQueueHandle queue;


void app_main(void) {
    queue = xQueueCreate(CONFIG_QUEUE_LENGTH, 4);   //queue stores only raw uint32_t counter values
    xTaskCreate(senderTask, "sender", 2048, NULL, 1, &senderTaskHandle);
    xTaskCreate(receiverTask, "receiver", 2048, loggerCallback, 1, &receiverTaskHandle);

}

/**
 * Logging callback for the second (receiver) task
 * @param counterValue Counter value to log
 * @param period Milliseconds since receiving previous queue message
 */
void loggerCallback(uint32_t counterValue, uint32_t period) {
    ESP_LOGI(CONFIG_LOG_TAG, "Counter value: %d. Time elapsed from previous reception: %d ms", counterValue, period);
}
