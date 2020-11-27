#ifndef PACKETS_H
#define PACKETS_H

#endif // PACKETS_H

#include <stdint.h>

#pragma pack(push, 1)
struct InputPacket
{
    float yaw = 0;
    float roll = 0;
    float pitch = 0;
    float depth = 0;
//    float temperature = 0;
//    uint8_t core = 0;
};
#pragma pack(pop)

#pragma pack(push,1)
struct OutputPacket
{
//    bool is_settings = true;
    int8_t manipulator_rotate = 0;
    int8_t manipulator_grab = 0;
    int8_t axis_X = 0;
    int8_t axis_Y = 0;
    int8_t axis_Z = 0;
    int8_t axis_W = 0;


    int8_t camera_rotate = 0;
    bool buttons[8] = {0};

    int8_t m_micro_speed = 0;
    int8_t m_micro_led = 0;

    float YawKp = 0;
    float YawKi = 0;
    float YawKd = 0;

    float PitchKp = 0;
    float PitchKi = 0;
    float PitchKd = 0;

    float RollKp = 0;
    float RollKi = 0;
    float RollKd = 0;

    float DepthKp = 0;
    float DepthKi = 0;
    float DepthKd = 0;

    float YawToSet = 0;
    float PitchToSet = 0;
    float RollToSet = 0;
    float DepthToSet = 0;

    bool yaw_reg_enable = false;
    bool depth_reg_enable = false;
    bool roll_reg_enable = false;
    bool pitch_reg_enable = false;

    int8_t smatyvalka = 0;

};
#pragma pack(pop)
