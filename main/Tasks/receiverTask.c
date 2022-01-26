#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include <driver/gpio.h>
#include <rom/gpio.h>

#include "receiverTask.h"

#include "main.h"

xTaskHandle receiverTaskHandle;

/**
 * Task receives counter values from the queue and sends them to the supplied callback
 * @param callback Must be receiverCallback_t type [void callback(uint32_t counterValue, uint32_t period)]
 */
_Noreturn void receiverTask(void *callback) {
    uint32_t lastTick = xTaskGetTickCount();

    //blink GPIO configuration
#if (CONFIG_DO_BLINK)
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << CONFIG_BLINK_GPIO);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;

    gpio_config(&io_conf);

    bool ledState = 0;
#endif

    while (true) {
        uint32_t counterValue = 0;  //received counter value
        BaseType_t res = xQueueReceive(queue, &counterValue, portMAX_DELAY);

        if (res == pdTRUE) {
            //blink if enabled in config
#if (CONFIG_DO_BLINK)
            ledState = !ledState;
            gpio_set_level(CONFIG_BLINK_GPIO, ledState);  //toggle led
#endif
            uint32_t currentTick = xTaskGetTickCount();
            ((receiverCallback_t) callback)(counterValue, pdTICKS_TO_MS(currentTick - lastTick));
            lastTick = currentTick;
        }

    }
}