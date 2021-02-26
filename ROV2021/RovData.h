#ifndef ROVDATA_H
#define ROVDATA_H
#include "stdint.h"

struct RovData
{
  int8_t m_axis_x = 0;
  int8_t m_axis_y = 0;
  int8_t m_axis_z = 0;
  int8_t m_axis_w = 0;

  float m_YawKp = 2.5;
  float m_YawKi = 0;
  float m_YawKd = 1;

  float m_PitchKp = 2.3;
  float m_PitchKi = 0;
  float m_PitchKd = 0.5;

  float m_RollKp = 2.3;//Ð¿Ñ€Ð¾Ð¿Ð¾Ñ€Ñ†Ð¸Ð¾Ð½Ð°Ð»ÑŒÐ½Ñ‹Ð¹
  float m_RollKi = 0;// Ð¸Ð½Ñ‚ÐµÐ³Ñ€Ð°Ð»ÑŒÐ½Ñ‹Ð¹ 
  float m_RollKd = 0.5;// Ð´Ð¸Ñ„Ñ„Ð¸Ñ€Ð¸Ñ†Ð¸Ð°Ð»ÑŒÐ½Ñ‹Ð¹;

  float m_DepthKp = 5;
  float m_DepthKi = 0;
  float m_DepthKd = 0.5;

  int8_t m_manipulator_grab = 0;
  int8_t m_manipulator_rotate = 0;
  int8_t m_rotary_camera = 0;

  bool m_yaw_reg_enable = false;
  bool m_depth_reg_enable = false;
  bool m_roll_reg_enable = false;
  bool m_pitch_reg_enable = false;

  float m_yaw = 0.0f;
  float m_roll = 0.0f;
  float m_pitch = 0.0f;
  float m_depth = 0.0f;
  float m_temperature = -1.0f;

  float m_yaw_to_set = 0.0f;
  float m_roll_to_set = 0.27f;
  float m_pitch_to_set = 149.0f;
  float m_depth_to_set = 0.0f;

  int8_t m_micro_speed = 0;

  bool m_manipulator_release_inverse = false;
  bool m_manipulator_rotate_inverse = false;
  int8_t MAX_HORIZONTAL_POWER = 85;
  int8_t MAX_VERTICAL_POWER = 85;

};

#endif // !ROVDATA_H
