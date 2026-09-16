#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static int my_esp32_board_from_scratch_init(void)
{
    printk("Board Initialized\n");

    return 0;
}

SYS_INIT(my_esp32_board_from_scratch_init, PRE_KERNEL_1, 0);