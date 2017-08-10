#pragma once
#include <string>
#include <CL/cl.hpp>

void showPlatformAndDeviceInfo(const cl::Platform& platform, int platformID, const cl::Device& device, int device_id);
void showDevice(const cl::Device& device, int i);
void showPlatform(const cl::Platform& platform, int i);
void showAllOpenCLDevices();
void showAllGPUs();
int numberPlatforms();
int numberDevices(int platformID);
std::string deviceName(int platformID, int deviceID);