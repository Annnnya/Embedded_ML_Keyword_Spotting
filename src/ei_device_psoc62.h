/*
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef EI_DEVICE_PSOC62_H_
#define EI_DEVICE_PSOC62_H_

#include "firmware-sdk/ei_device_info_lib.h"
#include "firmware-sdk/ei_device_memory.h"
#include "cyhal_timer.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/* Defines related to non-fusion sensors
 *
 * Note: Number of fusion sensors can be found in ei_fusion_sensors_config.h
 *
 */
#define EI_STANDALONE_SENSOR_MIC 0
#define EI_STANDALONE_SENSORS_COUNT 1

#define EI_DEVICE_BAUDRATE 115200
#define EI_DEVICE_BAUDRATE_MAX 460800

class EiDevicePSoC62 : public EiDeviceInfo {
private:
    EiDevicePSoC62() = delete;
    static const int sensors_count = EI_STANDALONE_SENSORS_COUNT;
    ei_device_sensor_t sensors[sensors_count];
    EiState state;
    cyhal_timer_t sample_timer;
    cyhal_timer_cfg_t sample_timer_cfg;
    cyhal_timer_t led_timer;
    volatile bool environmental_sampling;

public:
    EiDevicePSoC62(EiDeviceMemory *mem);
    ~EiDevicePSoC62();
    void init_device_id(void);
    void clear_config(void);
    bool get_sensor_list(const ei_device_sensor_t **sensor_list, size_t *sensor_list_size) override;
    uint32_t get_data_output_baudrate(void);
    void set_max_data_output_baudrate(void);
    void set_default_data_output_baudrate(void);
    bool test_flash(void);
    bool start_sample_thread(void (*sample_read_cb)(void), float sample_interval_ms) override;
    bool stop_sample_thread(void) override;
    void set_state(EiState state) override;
    EiState get_state(void);
    void set_environmental_sampling(void);
    void clear_environmental_sampling(void);
    bool is_environmental_sampling(void);
};

#endif /* EI_DEVICE_PSOC62_H_ */
