#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <JC/util.hpp>

#include "DeviceQuery.h"

int main(int argc, char *argv[])
{
	try {

		const int PLATFORM_ID = 9, DEVICE_ID = 0; // SELECT HERE YOUR GPU DEVICE!!! Put Nonsense if you want to see the list of all available OpenCL devices

		std::string kernel_file("kernels.ocl");
		std::string kernel_name("floatCopy");
		unsigned int data_count = 1024 * 1000; // array size


		// alternatively, use program arguments
		//if (argc != 4) {
		//	std::ostringstream oss;
		//	oss << "Usage: " << argv[0] << " <kernel_file> <kernel_name> <data_count>";
		//	throw std::runtime_error(oss.str());
		//}
		//std::string kernel_file(argv[1]);
		//std::string kernel_name(argv[2]);
		//unsigned int data_count = atoi(argv[3]);

		// Allocate memory on the host and populate source
		float *source1 = new float[data_count];
		float *source2 = new float[data_count];
		float *dest = new float[data_count];
		for(int i = 0; i < data_count; ++i) {
			source1[i] = i;
			source2[i] = i;
		}

		// OpenCL initialization
		std::vector<cl::Platform> platforms;
		std::vector<cl::Device> devices;
		cl::Platform::get(&platforms);
		if (PLATFORM_ID >= platforms.size()) {
			std::cerr << "Platform " << PLATFORM_ID << " does not exist on this computer" << std::endl;
			std::cerr << "OpenCL platforms & devices on this computer: " << std::endl;
			showAllOpenCLDevices();
			std::cout << std::endl << "Press ENTER to close window...";
			char c = std::cin.get();
			exit(-1);
		}
		platforms[PLATFORM_ID].getDevices(CL_DEVICE_TYPE_ALL, &devices); // or CL_DEVICE_TYPE_GPU
		if (DEVICE_ID >= devices.size()) {
			std::cerr << "Device " << DEVICE_ID
				  << " of platform " << PLATFORM_ID
				  << " does not exist on this computer (#=" << devices.size()<< ")" << std::endl;
			std::cerr << "OpenCL platforms & devices on this computer: " << std::endl;
			showAllOpenCLDevices();
			std::cout << std::endl << "Press ENTER to close window...";
			char c = std::cin.get();
			exit(-1);
		}
		cl::Context context(devices);
		cl::CommandQueue queue(context, devices[DEVICE_ID], CL_QUEUE_PROFILING_ENABLE);

		showPlatformAndDeviceInfo(platforms[PLATFORM_ID], PLATFORM_ID, devices[DEVICE_ID], DEVICE_ID);

		// Allocate memory on the device
		cl::Buffer source_buf1(context, CL_MEM_READ_ONLY, data_count*sizeof(cl_float));
		cl::Buffer source_buf2(context, CL_MEM_READ_ONLY, data_count * sizeof(cl_float));
		cl::Buffer dest_buf(context, CL_MEM_WRITE_ONLY, data_count*sizeof(cl_float));

		// Create the kernel
		cl::Program program = jc::buildProgram(kernel_file, context, devices);
		cl::Kernel kernel(program, kernel_name.c_str());

		// Set the kernel arguments
		kernel.setArg<cl::Memory>(0, source_buf1);
		kernel.setArg<cl::Memory>(1, source_buf2);
		kernel.setArg<cl::Memory>(2, dest_buf);
		kernel.setArg<cl_uint>(3, data_count);

		// Transfer source data from the host to the device
		queue.enqueueWriteBuffer(source_buf1, CL_TRUE, 0, data_count*sizeof(cl_float), source1);
		queue.enqueueWriteBuffer(source_buf2, CL_TRUE, 0, data_count * sizeof(cl_float), source2);

		// Execute the code on the device
		int work_group_size = 256;
		if (data_count % work_group_size != 0) {
			std::cout << "Error: data_count (" << data_count << ") should be a multiple of work_group_size ("<<work_group_size<<")!" << std::endl;

			std::cout << std::endl << "Press ENTER to close window...";
			char c = std::cin.get();
			return -1;
		}

		cl::NDRange global(data_count); // total amoung of work items (threads)
		cl::NDRange local(work_group_size);  // work group size

		cl_ulong t = jc::runAndTimeKernel(kernel, queue, global, local); // time in nanoseconds

		// Transfer destination data from the device to the host
		queue.enqueueReadBuffer(dest_buf, CL_TRUE, 0, data_count*sizeof(cl_float), dest);

		// Check the result, here we copied the data
		for(int i = 0; i < data_count; ++i) {
			if (source1[i] != dest[i]) {
				throw std::runtime_error("Incorrect results\n");
			}
		}
		std::cout << "The output is correct!" << std::endl;

		// Compute the data throughput in GB/s
		int total_nbr_bytes = 2.0*data_count * sizeof(float);
		float throughput = total_nbr_bytes /t; // t is in nano seconds
		std::cout << "Achieved throughput: " << throughput << " GB/s for "<< total_nbr_bytes <<" Bytes" << std::endl;

		// Deallocate memory
		delete[] dest;
		delete[] source1;
		delete[] source2;

		std::cout << std::endl << "Press ENTER to close window...";
		char c = std::cin.get();

		return 0;
	}
	catch (cl::Error& e) {
		std::cerr << e.what() << ": " << jc::readableStatus(e.err());

		std::cout << std::endl << "Press ENTER to close window...";
		char c = std::cin.get();
		return 3;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 2;
	}
	catch (...) {
		std::cerr << "Unexpected error. Aborting!\n" << std::endl;
		return 1;
	}
}
