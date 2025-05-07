#include "esp_log.h"
#include "esp_spiffs.h"
#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define TAG "FIRMAo.oSPEAKER"

void spiffs_init();
 

void read_wav_and_play(const char *filename);
    