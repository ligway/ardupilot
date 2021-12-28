#include "AP_RangeFinder_PYSITL.h"
#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL


extern const AP_HAL::HAL& hal;

// AP_RangeFinder_PYSITL::AP_RangeFinder_PYSITL(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params) :
//     AP_RangeFinder_Backend(_state, _params)
// {
//     init_queue();
// }
AP_RangeFinder_PYSITL::AP_RangeFinder_PYSITL(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params) :
    AP_RangeFinder_Backend(_state, _params)
{
    // init_queue();
    // set_status(RangeFinder::Status::NoData);
}
// bool AP_RangeFinder_PYSITL::detect()
// {
//     // Assume that if the user set the RANGEFINDER_TYPE parameter to MSP,
//     // there is an attached MSP rangefinder
//     // init_queue();
//     return true;
// }

// void AP_RangeFinder_PYSITL::init_queue()
// {
//     _queue.size = 25;
//     if (_queue.size == 0) {
//         return;
//     }
//     _queue.items = new ObjectBuffer<PYSITL>(_queue.size);
// }

bool AP_RangeFinder_PYSITL::get_reading(float &reading_cm)
{
    // if (_queue.items != nullptr) {
    //     // reading_cm = (float)_queue.items->pop();
    //     // distance = reading_cm;
    //     return true;

    // } else {
        //check if reading file exist
        int ret = AP::FS().open("rngfnd_read",O_RDWR);
        if (ret == -1) {
            reading_cm = 0.0f;
            // distance = reading_cm;
            return true;
        }

        char buffer_read[100];
        int reat = AP::FS().read(ret,buffer_read,sizeof(buffer_read)-1);
        if (reat < 0) {
            reading_cm = 0.0f;
            // distance = reading_cm;
            return true;
        } else if (buffer_read == NULL) {
            reading_cm = 0.0f;
            // distance = reading_cm;
            return true;
        } else {
            char reading_get[10] = {0};
            uint8_t reading_get_count = 0;
            uint8_t count = 0;
            for (uint8_t i = 0; (buffer_read[i]!='\0') || (i <= sizeof(buffer_read)-1);i++) {
                if (buffer_read[i]==',') {
                    count++; 
                } else {
                    reading_get[reading_get_count] = buffer_read[i];
                    reading_get_count++; 
                }
                
                if (count > 0) {
                    // PYSITL item = {(uint16_t)atoi(reading_get)};
                    // queue_data[queue_count] = atoi(reading_get);
                    // _queue.items->push(item);
                    count = 0;
                }
            }
            float reading = atof(reading_get)-1;
            reading += 1;
            reading = reading - 1;
            AP::FS().unlink("rngfnd_read");
            // reading_cm = (float)_queue.items->pop();
            // distance = reading_cm;
        }

        return true;
    // }
    // return true;

}

void AP_RangeFinder_PYSITL::update(void)
{
    get_reading(state.distance_m);
    update_status();
}
#endif