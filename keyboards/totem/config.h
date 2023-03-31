/*
Copyright 2022 GEIST <@geigeigeist>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#include "config_common.h"
//#define MASTER_LEFT
#define MASTER_RIGHT

/* USB Device descriptor parameter */
/*#define VENDOR_ID       0x3A3C
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    GEIST
#define PRODUCT         TOTEM
*/

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5


// wiring of each half
// seeed rp2040
// #define MATRIX_ROW_PINS { GP26, GP27, GP28, GP29 }
// #define MATRIX_COL_PINS { GP6, GP7, GP3, GP4, GP2 }
// rp2040 zero
#define MATRIX_ROW_PINS { GP0, GP1, GP2, GP3 }
#define MATRIX_COL_PINS { GP4, GP5, GP29, GP28, GP27 }
#define DIODE_DIRECTION COL2ROW


//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define DEBOUNCE 5


/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
// rp2040 zero
#define SOFT_SERIAL_PIN GP6
//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_USB_DETECT
#define SERIAL_USE_MULTI_TRANSACTION
/* communication between sides */
#define SERIAL_PIO_USE_PIO1


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Pointing device configuration. */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12
#define SPI_SS_PIN GP13
#define POINTING_DEVICE_CS_PIN GP13
// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

// Adjust trackpad rotation.
#define POINTING_DEVICE_ROTATION_90

//#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// Configure for the Cirque model
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE

