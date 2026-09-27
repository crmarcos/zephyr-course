#include<zephyr/shell/shell.h>
#include<zephyr/drivers/sensor.h>

// Static command to get the app version
static int cmd_version(const struct  shell* sh, size_t  argc, char** argv){
    shell_print(sh, "App Version: 1.0.0");
    return 0; 
}
SHELL_CMD_REGISTER(version, NULL, "Show app version", cmd_version);


// Fetch subcommand for sensor command
static int cmd_fetch(const struct  shell* sh, size_t  argc, char** argv){
    
    const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

    sensor_sample_fetch(driver);

    return 0; 
}

// Read subcommand for sensor command
static int cmd_read(const struct  shell* sh, size_t  argc, char** argv){
    
    const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

    struct sensor_value val;

    sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);

    shell_print(sh, "val1: %d, val2: %d", val.val1, val.val2);

    return 0; 
}

// Info subcommand for sensor command
static int cmd_info(const struct  shell* sh, size_t  argc, char** argv){
    
    const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

    shell_print(sh, "name: %s, state: %d", driver->name, driver->state->initialized);

    return 0; 
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Calls sensor_sample_fetch function", cmd_fetch),
    SHELL_CMD(read, NULL, "Calls sensor_channel_get function", cmd_read),
    SHELL_CMD(info, NULL, "Gets device name and ready state", cmd_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);