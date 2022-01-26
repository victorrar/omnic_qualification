#include <sys/cdefs.h>
//
// Created by Victor on 26.01.2022.
//

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "receiverTask.h"

#include "main.h"

xTaskHandle receiverTaskHandle;

_Noreturn void receiverTask(void *callback) {
    callback = (receiverCallback_t) callback;
    while(true){

    }
}