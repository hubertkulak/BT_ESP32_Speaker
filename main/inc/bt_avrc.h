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
#include "esp_avrc_api.h"

#define TAG "FIRMAo.oSPEAKER"

extern volatile bool avrc_conn;

void callback_bt_avrc(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param);
