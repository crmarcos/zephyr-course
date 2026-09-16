# Copyright (c) 2026 Iomico
# SPDX-License-Identifier: Apache-2.0

board_runner_args(openocd "--config=interface/esp_usb_jtag.cfg")
board_runner_args(openocd "--target=esp32.cfg")

include(${ZEPHYR_BASE}/boards/common/esp32.board.cmake)
