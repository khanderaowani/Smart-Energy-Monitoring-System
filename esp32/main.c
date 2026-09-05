#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2
#define VOLTAGE 230.0f
#define CURRENT_LIMIT 4.0f

void app_main(void)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    int cycle = 0;

    while (1)
    {
        float current;

        if (cycle < 5)
            current = 2.0f;
        else if (cycle < 10)
            current = 3.5f;
        else
            current = 5.0f;

        float power = VOLTAGE * current;

        printf("\n--- SMART ENERGY MONITOR ---\n");
        printf("Voltage : %.2f V\n", VOLTAGE);
        printf("Current : %.2f A\n", current);
        printf("Power   : %.2f W\n", power);

        if (current > CURRENT_LIMIT)
        {
            gpio_set_level(LED_PIN, 1);
            printf("Status  : OVERCURRENT FAULT\n");
            printf("LED     : ON\n");
        }
        else
        {
            gpio_set_level(LED_PIN, 0);
            printf("Status  : NORMAL\n");
            printf("LED     : OFF\n");
        }

        cycle++;

        if (cycle >= 15)
            cycle = 0;

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
