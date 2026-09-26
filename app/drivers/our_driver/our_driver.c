#include<zephyr/drivers/sensor.h>
#include<zephyr/logging/log.h>

#include <zephyr/drivers/gpio.h>

#include "our_driver.h"


/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);


#define DT_DRV_COMPAT our_driver
LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);


void set_internal_counter(const struct device *dev,
				    int32_t new_value){

    LOG_INF("Internal counter change to: %d", new_value);

    struct our_driver_data* data = dev->data;

    data->internal_counter = new_value;

}


int32_t get_internal_counter(const struct device *dev){

    struct our_driver_data* data = dev->data;
    
    LOG_INF("Internal counter read: %d", data->internal_counter);

    return data->internal_counter;

}


static int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val){

    
    LOG_INF("Hello from channel get, channel: %d", chan);
    LOG_INF("Turn ON LED");

    gpio_pin_set_dt(&led, 0);


    return 0;
}

static int sensor_sample_fetch_my_impl(const struct device *dev,
				     enum sensor_channel chan){

    LOG_INF("Hello from sample fetch, channel: %d", chan);
    LOG_INF("Turn OFF LED");

    gpio_pin_set_dt(&led, 1);

    // Increments internal counter each time the LED is Turned ON
    struct our_driver_data* data = dev->data;
    data->internal_counter = data->internal_counter + 1;

    return 0;
}


static DEVICE_API(sensor, api_iomico_lecture) = {
    .sample_fetch = sensor_sample_fetch_my_impl,
    .channel_get = channel_get_my_impl,
};  

static int init(const struct device *dev ){

    // Init the data
    struct our_driver_data* data = dev->data;
    data->internal_counter = 0;

    // Init the LED 

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    LOG_INF("Driver init");
    return 0;
}


#define OUR_DRIVER_DEFINE(inst)                    \
    static struct our_driver_data data_##inst;     \
                                                   \
    DEVICE_DT_INST_DEFINE(inst,                   \
                          init,                    \
                          NULL,                    \
                          &data_##inst,            \
                          NULL,                    \
                          POST_KERNEL,             \
                          80,                      \
                          &api_iomico_lecture);


DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE);