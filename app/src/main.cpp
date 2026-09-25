#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include<zephyr/drivers/sensor.h>


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

    while (1) {
        ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        
        ret = sensor_sample_fetch(driver);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
