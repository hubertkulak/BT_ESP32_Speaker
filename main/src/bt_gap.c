#include "bt_gap.h"

void bt_gap(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {  //controlls connections - generic access profille
    switch (event) {
        case ESP_BT_GAP_DISC_RES_EVT:
        break;
        case ESP_BT_GAP_DISC_STATE_CHANGED_EVT:
        break;
        case ESP_BT_GAP_RMT_SRVCS_EVT:
        break;
        case ESP_BT_GAP_RMT_SRVC_REC_EVT:
        break;
        case ESP_BT_GAP_AUTH_CMPL_EVT:
            ESP_LOGI(TAG,"auth: state:%d, remote_name:%s", param->auth_cmpl.stat, param->auth_cmpl.device_name);
        break;
        case ESP_BT_GAP_PIN_REQ_EVT:
        break;
        case ESP_BT_GAP_CFM_REQ_EVT:
            esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
        case ESP_BT_GAP_KEY_NOTIF_EVT:
        break;
        case ESP_BT_GAP_MODE_CHG_EVT:
        break;
        default: 
            ESP_LOGI(TAG, "GAP EVENT ID:%d",event);
        break;
    }
}