#include "UDPConnection.h"
//#include "Config.h"
#include "RovData.h"
//#include <cstddef>
#include <iostream>
#include <string>
#include <cstring>

UDPConnection::UDPConnection()
{
  
}

void UDPConnection::init()
{
    m_UDP = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)(&m_self_addr), sizeof(m_self_addr));
    m_remote_addr.sin_family = AF_INET;
    m_remote_addr.sin_addr.s_addr = inet_addr("169.254.101.40");
    m_remote_addr.sin_port = htons(5115);
    m_self_addr.sin_family = AF_INET;
    m_self_addr.sin_addr.s_addr = inet_addr("169.254.101.39");
    m_self_addr.sin_port = htons(5115);
    std::cout << bind(m_UDP, (struct sockaddr*) (&m_self_addr), sizeof(m_self_addr)) << std::endl;
    m_timer.start();
}

bool UDPConnection::receivePacket(RovData& rov_data)
{
    char packetBuffer[sizeof(InputPacket)] = { 0 };
    int size = recvfrom(m_UDP, packetBuffer, sizeof(packetBuffer), MSG_DONTWAIT, NULL, NULL);
    if (size > 0)
    {
        InputPacket packet;
        memcpy(&packet, packetBuffer, sizeof(packetBuffer));
        parsePayload(packet, rov_data);
        return true;
    }
    else return false;
}

void UDPConnection::sendPacket(const OutputPacket& packet)
{
    if (m_timer.elapsed() > 100)
    {
        sendto(m_UDP, (unsigned char*)&packet, sizeof(packet), 0, (struct sockaddr*) & m_remote_addr, sizeof(m_remote_addr));
        m_timer.start();
    }
}

void UDPConnection::parsePayload(InputPacket& packet, RovData& rov_data)
{
    rov_data.m_axis_x = - packet.axisX_p;
    rov_data.m_axis_y = packet.axisY_p;
    rov_data.m_axis_z = packet.axisZ_p;
    rov_data.m_axis_w = -packet.axisW_p;
    rov_data.m_manipulator_rotate = packet.manipulator_rotate;
    rov_data.m_manipulator_grab = packet.manipulator_grab;
    rov_data.m_rotary_camera = -packet.camera_rotate * 3;
    
    
    rov_data.m_YawKp = packet.m_YawKp;
    rov_data.m_YawKi = packet.m_YawKi;
    rov_data.m_YawKd = packet.m_YawKd;
    
    rov_data.m_PitchKp = packet.m_PitchKp;
    rov_data.m_PitchKi = packet.m_PitchKi;
    rov_data.m_PitchKd = packet.m_PitchKd;
    
    rov_data.m_RollKp = packet.m_RollKp;
    rov_data.m_RollKi = packet.m_RollKi;
    rov_data.m_RollKd = packet.m_RollKd;
    
    rov_data.m_DepthKp = packet.m_DepthKp;
    rov_data.m_DepthKi = packet.m_DepthKi;
    rov_data.m_DepthKd = packet.m_DepthKd;
    
    rov_data.m_yaw_reg_enable = packet.m_yaw_reg_enable;
    rov_data.m_depth_reg_enable = packet.m_depth_reg_enable;
    rov_data.m_roll_reg_enable = packet.m_roll_reg_enable;
    rov_data.m_pitch_reg_enable = packet.m_pitch_reg_enable;
    
    rov_data.m_roll_to_set = packet.m_RollToSet;
    rov_data.m_pitch_to_set = packet.m_PitchToSet;
}

void UDPConnection::write(RovData& rov_data)
{
    OutputPacket packet;
    
    packet.yaw = rov_data.m_yaw;
    packet.depth = rov_data.m_depth;
    packet.roll = rov_data.m_roll;
    packet.pitch = rov_data.m_pitch;
    
    sendPacket(packet);
}

void UDPConnection::read(RovData& rov_data)
{
    receivePacket(rov_data);
}
