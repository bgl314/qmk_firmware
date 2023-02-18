// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+
// here you find only RP2040 specific configurations

#pragma once
#include "config_common.h"

// ┌─────────────────────────────────────────────────┐
// │ a u d i o                                       │
// └─────────────────────────────────────────────────┘

#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4

// #ifdef BLOK_MCU
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN 16
#define I2C1_SCL_PIN 17
// #endif
