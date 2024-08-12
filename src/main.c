/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void led_test(void)
{
    int ret;

    if (!device_is_ready(led.port)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    printk("Blinking external LED on pin %d\n", led.pin);

    while (1) {
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0) {
            printk("Error %d: failed to toggle LED\n", ret);
            return;
        }
        k_msleep(SLEEP_TIME_MS);
    }
}

int main(void)
{
    led_test();
    return 0;
} 
