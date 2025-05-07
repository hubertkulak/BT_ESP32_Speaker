#include "bt_a2dp.h"
#define DIODA 17
#define DIODA_DIS 16


void callback_bt_a2d(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
    switch(event) {
        case ESP_A2D_CONNECTION_STATE_EVT: //zmiana statusu połączenia
        if (param->conn_stat.state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
            esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
            gpio_set_level(DIODA, 1);
            gpio_set_level(DIODA_DIS, 0);
            read_wav_and_play("/spiffs_image/cone.wav");
        } 
        if (param->conn_stat.state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
            esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
            gpio_set_level(DIODA, 0);
            gpio_set_level(DIODA_DIS, 1);
            read_wav_and_play("/spiffs_image/dis.wav");
        }
        break;

        case ESP_A2D_AUDIO_CFG_EVT:
        if (param->audio_cfg.mcc.type == ESP_A2D_MCT_SBC) {
            int sample_rate = 16000;
            char oct0 = param->audio_cfg.mcc.cie.sbc[0];
            if (oct0 & (0x01 << 6)) {
                sample_rate = 32000;
            } else if (oct0 & (0x01 << 5)) {
                sample_rate = 44100;
            } else if (oct0 & (0x01 << 4)) {
                sample_rate = 48000;
            }
            i2s_set_clk(0, sample_rate, 16, 2);
        }
            
        break;
        case ESP_A2D_MEDIA_CTRL_ACK_EVT:
        break;
        case ESP_A2D_PROF_STATE_EVT:
        break;
        default:
        break;
    }
}

void bt_a2d_data_i2s(const uint8_t *buf, uint32_t len) {
    size_t wb;
    i2s_write(0, buf, len, &wb, portMAX_DELAY);
}

