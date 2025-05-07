#include <stdio.h>
#include <stdlib.h>
#include "driver/i2s.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "inc/bt_avrc.h"
#include "inc/bt_a2dp.h"
#include "inc/bt_gap.h"
#include "inc/spiffs_wav.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"

#define TAG "FIRMAo.oSPEAKER"
#define bt_device_name "FIRMAo.oSPEAKER"

#define NEXT_BTN 13
#define LAST_BTN 14
#define STOP_BTN 25
#define DIODA  17
#define DIODA_DIS 16
#define GPIO_SD 25

#define I2S_NUM I2S_NUM_0
#define I2S_SAMPLE_RATE 44100
#define I2S_SAMPLE_BITS 16
#define I2S_CHANNEL_NUM 2

void i2s_configuration(void);
void gpio_configuration(void);
void gpio_task(void * pvParameteres);


void app_main(void) {
    esp_err_t err; //handler błędów 
    err = nvs_flash_init();
    if(err != ESP_OK){
        ESP_LOGI(TAG, "NVS INIT PROBLEM");
    }

    // Inicjalizacja GPIO
    gpio_configuration();
    
    // Konfiguracja I2S
    i2s_configuration();

    spiffs_init();

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((err = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(TAG, "%s initialize controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }
    if ((err = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();

    if ((err = esp_bluedroid_init_with_cfg(&bluedroid_cfg)) != ESP_OK) {
        ESP_LOGE(TAG, "%s initialize bluedroid failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    if ((err = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(TAG, "%s enable bluedroid failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    esp_avrc_ct_register_callback(callback_bt_avrc);
    esp_avrc_ct_init();

    esp_a2d_register_callback(callback_bt_a2d);
    esp_a2d_sink_register_data_callback(bt_a2d_data_i2s);
    esp_a2d_sink_init();

    esp_bt_gap_register_callback(bt_gap);
    esp_bt_dev_set_device_name(bt_device_name);
    esp_bt_io_cap_t io_cap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(ESP_BT_SP_IOCAP_MODE, &io_cap, sizeof(io_cap));
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void gpio_configuration(void) {
    // Diody do komunikacji statusu połączenia
    gpio_set_direction(DIODA, GPIO_MODE_OUTPUT);
    gpio_set_direction(DIODA_DIS, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_SD, GPIO_MODE_OUTPUT);
    
    gpio_set_level(GPIO_SD, 1);
    gpio_set_level(DIODA_DIS, 1);
}

void i2s_configuration(void) {
    esp_err_t err;

    i2s_config_t i2sConfiguration = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = 44100,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .intr_alloc_flags = 0,
        .tx_desc_auto_clear = true
    };

    err = i2s_driver_install(I2S_NUM, &i2sConfiguration, 0, NULL);
    if(err != ESP_OK){
        ESP_LOGI(TAG, "I2S failed to start!");
    }

    i2s_pin_config_t i2s_pins_config = {
        .bck_io_num = 32,
        .ws_io_num = 33,
        .data_out_num = 26,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    
    err = i2s_set_pin(I2S_NUM, &i2s_pins_config);
    if(err != ESP_OK){
        ESP_LOGI(TAG, "I2S pin config fail!");
    }

    i2s_set_sample_rates(I2S_NUM, 44100); // Set sample rates
}


