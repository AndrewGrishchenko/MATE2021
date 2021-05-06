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
    int8_t manipulator_rotate = 0;
    int8_t manipulator_grab = 0;

    int8_t axisX_p = 0;
    int8_t axisY_p = 0;
    int8_t axisZ_p = 0;
    int8_t axisW_p = 0;
    int8_t camera_rotate = 0;
    bool buttons[8] = {0};

    int8_t m_micro_speed = 0;
    int8_t m_smatyvalka_value = 0;

    float m_YawKp = 2.5;
    float m_YawKi = 0;
    float m_YawKd = 1;

    float m_PitchKp = 2.3;
    float m_PitchKi = 0;
    float m_PitchKd = 0.5;

    float m_RollKp = 2.3;
    float m_RollKi = 0;
    float m_RollKd = 0.5;

    float m_DepthKp = 5;
    float m_DepthKi = 0;
    float m_DepthKd = 0.5;

    float m_YawToSet = 0;
    float m_PitchToSet = 0;
    float m_RollToSet = 0;
    float m_DepthToSet = 0;

    bool m_yaw_reg_enable = false;
    bool m_depth_reg_enable = false;
    bool m_roll_reg_enable = false;
    bool m_pitch_reg_enable = false;

};
#pragma pack(pop)
