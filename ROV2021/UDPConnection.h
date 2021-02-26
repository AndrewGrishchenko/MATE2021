#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H
//UDPconnection.cpp
#include <cstdint>
#include "Timer.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "RovData.h"

struct InputPacket
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

struct OutputPacket
{
  // Äîáàâèòü íåîáõîäèìûå ïîëÿ
    float yaw = 0;
    float roll = 0;
    float pitch = 0;
    float depth = 0;
};

class UDPConnection
{
public:
  UDPConnection();
  void init(); // Èíèöèàëèçàöèÿ ñîåäèíåíèÿ (ip, port è òä)
  void write(RovData& rov_data); // Îòïðàâêà ïàêåòà
  void read(RovData& rov_data); // ×òåíèå ïàêåòà
    bool receivePacket(RovData& rov_data);
    void sendPacket(const OutputPacket& packet);
    void parsePayload(InputPacket& packet, RovData& rov_data);
private:
    int m_UDP;
    sockaddr_in m_self_addr;
    sockaddr_in m_remote_addr;
  Timer m_timer;
    bool is_settings = false;
    bool button_3_release = false;
};

#endif // !UDPCONNECTION_H
