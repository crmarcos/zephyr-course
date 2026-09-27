#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include<zephyr/drivers/sensor.h>

#include "../drivers/our_driver/our_driver.h"


// Get our_driver
const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


int main(void)
{

    // Check for device
    if (!device_is_ready(driver)) {return -ENODEV;}

    // Call device functions
    struct sensor_value val;
    int ret;

    ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
    ret = sensor_sample_fetch(driver);

    // Enter infinite loop
    while (1) {
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
