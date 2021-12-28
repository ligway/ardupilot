#pragma once

#include "AP_RangeFinder.h"
#include "AP_RangeFinder_Backend.h"
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL

#include "AP_RangeFinder_Params.h"
#include <AP_HAL/utility/RingBuffer.h>
#include <AP_Filesystem/AP_Filesystem.h>

class AP_RangeFinder_PYSITL : public AP_RangeFinder_Backend
{
public:
    // constructor
    using AP_RangeFinder_Backend::AP_RangeFinder_Backend;
    // AP_RangeFinder_PYSITL(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params);
    // constructor
    AP_RangeFinder_PYSITL(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params);

    // // static detection function
    // static bool detect(AP_RangeFinder_Params &_params);

    // static detection function
    // static bool detect();

    // uint8_t queue_count = 0;
    // struct PYSITL
    // {
    //     uint16_t queue_data;
    // };

    // struct
    // {
    //     ObjectBuffer<PYSITL> *items;
    //     uint16_t        size;
    // } _queue;

    // initialise
    // void init_queue();

    MAV_DISTANCE_SENSOR _get_mav_distance_sensor_type() const override {
        return MAV_DISTANCE_SENSOR_RADAR;
    }

private:
    float distance = 0.0f;

    // update state
    void update(void) override;
    // // start a reading
    // static bool start_reading(void);
    bool get_reading(float &reading_cm);

};
#endif