/**
 * Daniel Shchur & Mitch Clark
 * CornHacks 2020
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

// Pins
#define LIGHT_PIN   23  //D_out
#define PUMP_PIN    22  //D_out
#define DHT11_PIN   36  //D_in
#define SOIL_PIN    39  //A_in
#define WATER_PIN   34  //A_in
#define PHOTO_PIN   35  //A_in

void app_main(void)
{   
    // Set all pins for gpio and in/out
    gpio_pad_select_gpio(LIGHT_PIN);
    gpio_set_direction(LIGHT_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(PUMP_PIN);
    gpio_set_direction(PUMP_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(DHT11_PIN);
    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(SOIL_PIN);
    gpio_set_direction(SOIL_PIN, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(WATER_PIN);
    gpio_set_direction(WATER_PIN, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(PHOTO_PIN);
    gpio_set_direction(PHOTO_PIN, GPIO_MODE_INPUT);

    // Main Loop
    while(1) {
        gpio_set_level(LIGHT_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LIGHT_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
