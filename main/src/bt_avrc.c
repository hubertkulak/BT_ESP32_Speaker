#include "bt_avrc.h"

volatile bool avrc_conn=false;

uint8_t bt_speaker_state=ESP_AVRC_PLAYBACK_STOPPED;

esp_avrc_rn_evt_cap_mask_t rn_cap_mask={0};

void callback_bt_avrc(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param) {
   
    char *text;

    switch(event) {
        case ESP_AVRC_CT_CONNECTION_STATE_EVT: //zmiana stanu połączenia 
        if (param->conn_stat.connected) {
            esp_avrc_ct_send_get_rn_capabilities_cmd(1); //wysłanie powiadomienia do urządenia bt o pobranie event_id powiadomień, które może obsłużyć
            avrc_conn=1;
            esp_avrc_ct_send_register_notification_cmd(1, ESP_AVRC_RN_PLAY_STATUS_CHANGE, 0);//wysłanie komendy do urządzenia bt
        } else {
            rn_cap_mask.bits=0;
             avrc_conn=0;
        }
        break;
      
        case ESP_AVRC_CT_CHANGE_NOTIFY_EVT:   
            switch(param->change_ntf.event_id) {
                case ESP_AVRC_RN_VOLUME_CHANGE:
                break;
                case ESP_AVRC_RN_PLAY_STATUS_CHANGE:
                    bt_speaker_state = param->change_ntf.event_parameter.playback;
                break;
                default:
                break;
            }
        break;
        case ESP_AVRC_CT_GET_RN_CAPABILITIES_RSP_EVT:
            rn_cap_mask.bits = param->get_rn_caps_rsp.evt_set.bits;
            break;
        case ESP_AVRC_CT_SET_ABSOLUTE_VOLUME_RSP_EVT:
        break;
        case ESP_AVRC_CT_METADATA_RSP_EVT:

        break;
        default:
        break;
    }
}