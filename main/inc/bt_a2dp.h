#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "string.h"
#include "nvs_flash.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "spiffs_wav.h"



void callback_bt_a2d(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
void bt_a2d_data_i2s(const uint8_t *buf, uint32_t len) ;