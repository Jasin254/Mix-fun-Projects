#include "stm32f4xx.h"
#include "dht11.h"
#include "ff.h"

int main(void)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    UINT bytes_written;

    // Initialize the SD Card
    res = f_mount(&fs, "", 1);
    if (res != FR_OK) {
        // Handle error
    }

    // Create a file to store the data
    res = f_open(&file, "data.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        // Handle error
    }

    // Initialize the DHT11 sensor
    dht11_init();

    while (1) {
        // Read temperature and humidity data from the sensor
        int temperature, humidity;
        dht11_read(&temperature, &humidity);

        // Write the data to the file on the SD Card
        char data[20];
        sprintf(data, "%d,%d\n", temperature, humidity);
        res = f_write(&file, data, strlen(data), &bytes_written);
        if (res != FR_OK) {
            // Handle error
        }

        // Wait for some time before reading the sensor again
        HAL_Delay(1000);
    }
}
