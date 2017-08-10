#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

const bool DEBUG = false;
using namespace std;

const char *readableStatus(cl_int status);

void showPlatformAndDeviceInfo(const cl::Platform& platform, int platform_id, const cl::Device& device, int device_id)
{
	std::string platformName, platformVendor, platformProfile, platformVersion, platformExtensions;
	platform.getInfo(CL_PLATFORM_NAME, &platformName);
	platform.getInfo(CL_PLATFORM_VENDOR, &platformVendor);
	platform.getInfo(CL_PLATFORM_PROFILE, &platformProfile);
	platform.getInfo(CL_PLATFORM_VERSION, &platformVersion);
	platform.getInfo(CL_PLATFORM_EXTENSIONS, &platformExtensions);

	std::cout << "Platform " << platform_id << std::endl;
	std::cout << "    Name:       " << platformName << std::endl;
	std::cout << "    Vendor:     " << platformVendor << std::endl;
	std::cout << "    Profile:    " << platformProfile << std::endl;
	std::cout << "    Version:    " << platformVersion << std::endl;
	std::cout << std::endl;

    std::string deviceName, openCLCVersion, openCLExtensions;
    size_t image2dMaxHeight, image2dMaxWidth;
    size_t image3dMaxDepth, image3dMaxHeight, image3dMaxWidth;
    size_t maxWorkGroupSize, timerResolution;
    cl_ulong maxSize, localMemSize;
    cl_uint  nativeVectorWidthFloat, clockFrequency;
    device.getInfo<std::string>(CL_DEVICE_NAME, &deviceName);
    device.getInfo<std::string>(CL_DEVICE_OPENCL_C_VERSION, &openCLCVersion);
    device.getInfo<std::string>(CL_DEVICE_EXTENSIONS, &openCLExtensions);
    device.getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE, &maxSize); 

    //device.getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT, &image2dMaxHeight);
    //device.getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH, &image2dMaxWidth);
    //device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH, &image3dMaxDepth);
    //device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT, &image3dMaxHeight);
    //device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH, &image3dMaxWidth);

    device.getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE, &localMemSize);
    device.getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkGroupSize);
    device.getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, &nativeVectorWidthFloat);
    device.getInfo<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION, &timerResolution);

    device.getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY, &clockFrequency);

    std::cout << "    Device " << device_id << std::endl;
    std::cout << "        Name                    : " << deviceName << std::endl;
    std::cout << "        OpenCL C Version        : " << openCLCVersion << std::endl;
    //std::cout << "        2D Image limits         : " 
    //          << image2dMaxHeight << "x" << image2dMaxWidth << std::endl;
    //std::cout << "        3D Image limits         : " 
    //          << image3dMaxDepth << "x" << image3dMaxHeight << "x" 
    //          << image2dMaxWidth << std::endl;
    std::cout << "        Maximum buffer size [MB]: "
              << maxSize/(1024*1024) << std::endl;
    std::cout << "        Local memory size [KB]  : "
              << localMemSize/1024 << std::endl;
    std::cout << "        Maximum workgroup size  : " << maxWorkGroupSize << std::endl;
    std::cout << "        Native vector width     : " << nativeVectorWidthFloat << std::endl;
    std::cout << "        Timer resolution        : " << timerResolution << std::endl;
    std::cout << "        Clock frequency         : " << clockFrequency << std::endl;
    std::cout << std::endl;
}

void showDevice(const cl::Device& device, int i)
{
	std::string deviceName, openCLCVersion, openCLExtensions;
	size_t image2dMaxHeight, image2dMaxWidth;
	size_t image3dMaxDepth, image3dMaxHeight, image3dMaxWidth;
	size_t maxWorkGroupSize, timerResolution;
	cl_ulong maxSize, localMemSize;
	cl_uint nbrComputeUnits, nativeVectorWidthFloat, clockFrequency;
	device.getInfo<std::string>(CL_DEVICE_NAME, &deviceName);
	device.getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS, &nbrComputeUnits);
	device.getInfo<std::string>(CL_DEVICE_OPENCL_C_VERSION, &openCLCVersion);
	device.getInfo<std::string>(CL_DEVICE_EXTENSIONS, &openCLExtensions);
	device.getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE, &maxSize);

	device.getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT, &image2dMaxHeight);
	device.getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH, &image2dMaxWidth);
	device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH, &image3dMaxDepth);
	device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT, &image3dMaxHeight);
	device.getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH, &image3dMaxWidth);

	device.getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE, &localMemSize);
	device.getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkGroupSize);
	device.getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, &nativeVectorWidthFloat);
	device.getInfo<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION, &timerResolution);

	device.getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY, &clockFrequency);

	std::cout << "    Device: " << i << std::endl;
	std::cout << "        Name                    : " << deviceName << std::endl;
	std::cout << "        OpenCL C Version        : " << openCLCVersion << std::endl;
	std::cout << "        #Compute Units (cores)  : " << nbrComputeUnits << std::endl;
	std::cout << "        Native vector width     : " << nativeVectorWidthFloat << std::endl;
	std::cout << "        2D Image limits         : " << image2dMaxHeight << "x" << image2dMaxWidth << std::endl;
	std::cout << "        3D Image limits         : " << image3dMaxDepth << "x" << image3dMaxHeight << "x" << image2dMaxWidth << std::endl;
	std::cout << "        Maximum buffer size [MB]: " << maxSize / (1024 * 1024) << std::endl;
	std::cout << "        Local memory size [KB]  : " << localMemSize / 1024 << std::endl;
	std::cout << "        Maximum workgroup size  : " << maxWorkGroupSize << std::endl;
	std::cout << "        Timer resolution        : " << timerResolution << std::endl;
	std::cout << "        Clock frequency         : " << clockFrequency << std::endl;
	std::cout << std::endl;
}

void showPlatform(const cl::Platform& platform, int i)
{
    std::string platformName, platformVendor, platformProfile, platformVersion, platformExtensions;
    platform.getInfo(CL_PLATFORM_NAME, &platformName);
    platform.getInfo(CL_PLATFORM_VENDOR, &platformVendor);
    platform.getInfo(CL_PLATFORM_PROFILE, &platformProfile);
    platform.getInfo(CL_PLATFORM_VERSION, &platformVersion);
    platform.getInfo(CL_PLATFORM_EXTENSIONS, &platformExtensions);

    std::cout << "Platform " << i << std::endl;
    std::cout << "    Name:       " << platformName << std::endl;
    std::cout << "    Vendor:     " << platformVendor << std::endl;
    std::cout << "    Profile:    " << platformProfile << std::endl;
    std::cout << "    Version:    " << platformVersion << std::endl;
    std::cout << std::endl;

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    for (int i = 0; i < devices.size(); ++i) {
        showDevice(devices[i], i);
    }
}

void showAllOpenCLDevices()
{
	try {


		std::vector<cl::Platform> platforms;
		std::vector<cl::Device> devices;
		cl::Platform::get(&platforms);

		for (int i = 0; i < platforms.size(); ++i) {
			showPlatform(platforms[i], i);
		}
	}
	catch (cl::Error &e) {
		std::cerr << e.what() << ":" << readableStatus(e.err());
		return;
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		return;
	}
	catch (...) {
		std::cerr << "Unforeseen error";
		return;
	}

//cout << endl << "Press ENTER to close window...";
//char c = cin.get();
}

void showAllGPUs() {
	try {

		std::vector<cl::Platform> platforms;
		std::vector<cl::Device> devices;
		cl::Platform::get(&platforms);

		for (int i = 0; i < platforms.size(); ++i) {
			cl::Platform platform = platforms[i];
			std::string platformName, platformVendor;
			platform.getInfo(CL_PLATFORM_NAME, &platformName);
			platform.getInfo(CL_PLATFORM_VENDOR, &platformVendor);

			std::vector<cl::Device> devices;
			platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
			for (int j = 0; j < devices.size(); ++j) {
				cl::Device device = devices[j];
				std::string deviceName, openCLCVersion, openCLExtensions;
				
				size_t maxWorkGroupSize, timerResolution;
				cl_ulong maxSize, localMemSize;
				cl_uint nativeVectorWidthFloat, clockFrequency, nbrComputeUnits;
				device.getInfo<std::string>(CL_DEVICE_NAME, &deviceName);
				device.getInfo<std::string>(CL_DEVICE_OPENCL_C_VERSION, &openCLCVersion);
				device.getInfo<std::string>(CL_DEVICE_EXTENSIONS, &openCLExtensions);
				device.getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE, &maxSize);
				device.getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS, &nbrComputeUnits);
				device.getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkGroupSize);
				device.getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, &nativeVectorWidthFloat);
				device.getInfo<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION, &timerResolution);

				device.getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY, &clockFrequency);

				std::cout << " - " << deviceName << " on " << platformName<<": " << nbrComputeUnits <<" cores " << clockFrequency <<
					"MHz " << " vector width="<< nativeVectorWidthFloat <<std::endl;
				//std::cout << "        OpenCL C Version        :" << openCLCVersion << std::endl;
				//std::cout << "        Maximum workgroup size  :" << maxWorkGroupSize << std::endl;
				//std::cout << "        Native vector width     :" << nativeVectorWidthFloat << std::endl;
				//std::cout << "        Timer resolution        :" << timerResolution << std::endl;
				//std::cout << "        Clock frequency         :" << clockFrequency << std::endl;
				//std::cout << std::endl;
			}
		}
	}
	catch (cl::Error &e) {
		std::cerr << e.what() << ":" << readableStatus(e.err());
		return;
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		return;
	}
	catch (...) {
		std::cerr << "Unforeseen error";
		return;
	}

}
int numberPlatforms() {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	return platforms.size();
}
int numberDevices(int platformID) {
	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	cl::Platform::get(&platforms);
	if (platformID >= platforms.size() || platformID < 0)
		return 0;
	platforms[platformID].getDevices(CL_DEVICE_TYPE_ALL, &devices);
	return devices.size();
}
string deviceName(int platformID, int deviceID) {
	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	cl::Platform::get(&platforms);
	if (platformID >= platforms.size() || platformID < 0)
		return string("");
	platforms[platformID].getDevices(CL_DEVICE_TYPE_ALL, &devices);
	if (deviceID >= devices.size() || deviceID < 0)
		return string("");
	cl::Device device = devices[deviceID];
	std::string deviceName;
	device.getInfo<std::string>(CL_DEVICE_NAME, &deviceName);
	return deviceName;
}
const char *readableStatus(cl_int status)
{
	switch (status) {
	case CL_SUCCESS:
		return "CL_SUCCESS";
	case CL_DEVICE_NOT_FOUND:
		return "CL_DEVICE_NOT_FOUND";
	case CL_DEVICE_NOT_AVAILABLE:
		return "CL_DEVICE_NOT_AVAILABLE";
	case CL_COMPILER_NOT_AVAILABLE:
		return "CL_COMPILER_NOT_AVAILABLE";
	case CL_MEM_OBJECT_ALLOCATION_FAILURE:
		return "CL_COMPILER_NOT_AVAILABLE";
	case CL_OUT_OF_RESOURCES:
		return "CL_OUT_OF_RESOURCES";
	case CL_OUT_OF_HOST_MEMORY:
		return "CL_OUT_OF_HOST_MEMORY";
	case CL_PROFILING_INFO_NOT_AVAILABLE:
		return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case CL_MEM_COPY_OVERLAP:
		return "CL_MEM_COPY_OVERLAP";
	case CL_IMAGE_FORMAT_MISMATCH:
		return "CL_IMAGE_FORMAT_MISMATCH";
	case CL_IMAGE_FORMAT_NOT_SUPPORTED:
		return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case CL_BUILD_PROGRAM_FAILURE:
		return "CL_BUILD_PROGRAM_FAILURE";
	case CL_MAP_FAILURE:
		return "CL_MAP_FAILURE";
#ifndef CL_VERSION_1_0
	case CL_MISALIGNED_SUB_BUFFER_OFFSET:
		return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
		return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
#endif
	case CL_INVALID_VALUE:
		return "CL_INVALID_VALUE";
	case CL_INVALID_DEVICE_TYPE:
		return "CL_INVALID_DEVICE_TYPE";
	case CL_INVALID_PLATFORM:
		return "CL_INVALID_PLATFORM";
	case CL_INVALID_DEVICE:
		return "CL_INVALID_DEVICE";
	case CL_INVALID_CONTEXT:
		return "CL_INVALID_CONTEXT";
	case CL_INVALID_QUEUE_PROPERTIES:
		return "CL_INVALID_QUEUE_PROPERTIES";
	case CL_INVALID_COMMAND_QUEUE:
		return "CL_INVALID_COMMAND_QUEUE";
	case CL_INVALID_HOST_PTR:
		return "CL_INVALID_HOST_PTR";
	case CL_INVALID_MEM_OBJECT:
		return "CL_INVALID_MEM_OBJECT";
	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
		return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case CL_INVALID_IMAGE_SIZE:
		return "CL_INVALID_IMAGE_SIZE";
	case CL_INVALID_SAMPLER:
		return "CL_INVALID_SAMPLER";
	case CL_INVALID_BINARY:
		return "CL_INVALID_BINARY";
	case CL_INVALID_BUILD_OPTIONS:
		return "CL_INVALID_BUILD_OPTIONS";
	case CL_INVALID_PROGRAM:
		return "CL_INVALID_PROGRAM";
	case CL_INVALID_PROGRAM_EXECUTABLE:
		return "CL_INVALID_PROGRAM_EXECUTABLE";
	case CL_INVALID_KERNEL_NAME:
		return "CL_INVALID_KERNEL_NAME";
	case CL_INVALID_KERNEL_DEFINITION:
		return "CL_INVALID_KERNEL_DEFINITION";
	case CL_INVALID_KERNEL:
		return "CL_INVALID_KERNEL";
	case CL_INVALID_ARG_INDEX:
		return "CL_INVALID_ARG_INDEX";
	case CL_INVALID_ARG_VALUE:
		return "CL_INVALID_ARG_VALUE";
	case CL_INVALID_ARG_SIZE:
		return "CL_INVALID_ARG_SIZE";
	case CL_INVALID_KERNEL_ARGS:
		return "CL_INVALID_KERNEL_ARGS";
	case CL_INVALID_WORK_DIMENSION:
		return "CL_INVALID_WORK_DIMENSION";
	case CL_INVALID_WORK_GROUP_SIZE:
		return "CL_INVALID_WORK_GROUP_SIZE";
	case CL_INVALID_WORK_ITEM_SIZE:
		return "CL_INVALID_WORK_ITEM_SIZE";
	case CL_INVALID_GLOBAL_OFFSET:
		return "CL_INVALID_GLOBAL_OFFSET";
	case CL_INVALID_EVENT_WAIT_LIST:
		return "CL_INVALID_EVENT_WAIT_LIST";
	case CL_INVALID_EVENT:
		return "CL_INVALID_EVENT";
	case CL_INVALID_OPERATION:
		return "CL_INVALID_OPERATION";
	case CL_INVALID_GL_OBJECT:
		return "CL_INVALID_GL_OBJECT";
	case CL_INVALID_BUFFER_SIZE:
		return "CL_INVALID_BUFFER_SIZE";
	case CL_INVALID_MIP_LEVEL:
		return "CL_INVALID_MIP_LEVEL";
	case CL_INVALID_GLOBAL_WORK_SIZE:
		return "CL_INVALID_GLOBAL_WORK_SIZE";
#ifndef CL_VERSION_1_0
	case CL_INVALID_PROPERTY:
		return "CL_INVALID_PROPERTY";
#endif
	default:
		return "CL_UNKNOWN_CODE";
	}
}

