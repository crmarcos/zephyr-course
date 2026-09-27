#include<zephyr/shell/shell.h>
#include<zephyr/drivers/sensor.h>
#include "our_driver.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include<zephyr/logging/log.h>
LOG_MODULE_REGISTER(our_driver_shell, LOG_LEVEL_INF);


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

// Set subcommand for sensor command
static int cmd_set(const struct  shell* sh, size_t  argc, char** argv){
    
    // Variables fo strtol string to long convertion
    char *endptr;
    long value;

    // Gets the device struct
    const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

    // argc and argv info
    LOG_INF("argc: %d", argc);
    for(int i = 0; i<argc; i++){
        LOG_INF("argv[%d]: %s", i, argv[i]);
    }

    // tries to convert argv[1] to integer
    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    // checks for overrange
    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        shell_error(sh, "Number out of range\n");
        return -EINVAL;
    }

    // checks for malforming number
    if (endptr == argv[1] || *endptr != '\0') {
        shell_error(sh, "Invalid value: %s", argv[1]);
        return -EINVAL;
    }

    // Sets new value if everything is ok
    LOG_INF("Sets new value: %d", (int32_t) value);
    set_internal_counter(driver, (int32_t)value);

    return 0; 
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Calls sensor_sample_fetch function", cmd_fetch),
    SHELL_CMD(read, NULL, "Calls sensor_channel_get function", cmd_read),
    SHELL_CMD(info, NULL, "Gets device name and ready state", cmd_info),
    SHELL_CMD_ARG(set, NULL, "Sets data mutable data of driver", cmd_set, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);


