#include "spiffs_wav.h"

void spiffs_init(){
 esp_err_t err;
 
// Inicjalizacja SPIFFS
    ESP_LOGI(TAG, "Mounting SPIFFS filesystem");
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs_image",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };

 err = esp_vfs_spiffs_register(&conf);
    if (err != ESP_OK) {
        if (err == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (err == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(err));
        }
        return;
    }

    size_t total = 0, used = 0;
    err = esp_spiffs_info(NULL, &total, &used);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    // Odtwarzanie pliku WAV
    read_wav_and_play("/spiffs_image/start.wav");

}

void read_wav_and_play(const char *filename) {
    ESP_LOGI(TAG, "Opening file %s", filename);
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    // Skip WAV header (44 bytes)
    fseek(f, 44, SEEK_SET);

    size_t buffer_size = 2048;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for buffer");
        fclose(f);
        return;
    }

    while (1) {
        size_t bytes_read = fread(buffer, 1, buffer_size, f);
        if (bytes_read == 0) {
            break;
        }

        size_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            size_t written = 0;
            i2s_write(0, buffer + bytes_written, bytes_read - bytes_written, &written, portMAX_DELAY);
            bytes_written += written;
        }
    }

    free(buffer);
    fclose(f);
    ESP_LOGI(TAG, "Done playing file %s", filename);
}