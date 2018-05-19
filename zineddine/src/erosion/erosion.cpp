#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include <JC/util.hpp>

#undef min // MS defines pesky min and max macros :-(((
#undef max

std::vector<cl_int>
erosion(const std::vector<cl_int>& image, const int m)
{
  assert(m % 2 == 1);
  std::vector<cl_int> result(image.size());

  for (int i = 0; i < image.size(); ++i) {
    cl_int curr_min = std::numeric_limits<cl_int>::max();
    for (int j = i - m / 2; j <= i + m / 2; ++j) {
      if (j >= 0 && j < image.size())
        curr_min = std::min(curr_min, image[j]);
    }
    result[i] = curr_min;
  }

  return result;
}

std::vector<cl_int>
gpu_erosion(const std::vector<cl_int>& image, const int m)
{
  assert(m % 2 == 1);
  std::vector<cl_int> result(image.size());

  cl::Device device = jc::get_device(CL_DEVICE_TYPE_GPU);
  cl::Context context{ device };
  cl::CommandQueue queue{ context, device, CL_QUEUE_PROFILING_ENABLE };

  // TODO
  // (1) In a file called "kernels.ocl" in the appropriate directory,
  //     write the code for a kernel called "erosion".
  cl::Program program =
    jc::build_program_from_file("./kernels.ocl", context, device);
  cl::Kernel kernel{ program, "erosion" };

  // (1) Create buffers
  size_t byte_size = image.size() * sizeof(cl_int);
  cl::Buffer result_buffer{ context, CL_MEM_WRITE_ONLY, byte_size };
  cl::Buffer image_buffer{ context, CL_MEM_READ_ONLY, byte_size };

  // (2) Set arguments
  kernel.setArg(0, result_buffer);
  kernel.setArg(1, image_buffer);
  kernel.setArg(2, m);
  kernel.setArg(3, static_cast<cl_int>(image.size()));

  // (3) Write data to device
  queue.enqueueWriteBuffer(image_buffer, CL_TRUE, 0, byte_size, image.data());

  // (4) Run and time kernel
  cl_ulong nanoseconds =
    jc::run_and_time_kernel(kernel,
                            queue,
                            cl::NDRange(jc::best_fit(image.size(), 256)),
                            cl::NDRange(256));

  // (5) Read data from device
  queue.enqueueReadBuffer(result_buffer, CL_TRUE, 0, byte_size, result.data());

  int bytes_accessed = (image.size() + image.size() * m) * sizeof(cl_int);
  std::cout << "data throughput: ";
  std::cout << static_cast<double>(bytes_accessed) / nanoseconds;
  std::cout << " GB/s\n";

  return result;
}

std::vector<cl_int>
gpu_local_erosion(const std::vector<cl_int>& image, const int m)
{
  assert(m % 2 == 1);
  std::vector<cl_int> result(image.size());

  cl::Device device = jc::get_device(CL_DEVICE_TYPE_GPU);
  cl::Context context{ device };
  cl::CommandQueue queue{ context, device, CL_QUEUE_PROFILING_ENABLE };

  // TODO
  // (1) In a file called "kernels.ocl" in the appropriate directory,
  //     write the code for a kernel called "erosion".
  cl::Program program =
    jc::build_program_from_file("./kernels.ocl", context, device);
  cl::Kernel kernel{ program, "local_erosion" };

  // (1) Create buffers
  size_t byte_size = image.size() * sizeof(cl_int);
  cl::Buffer result_buffer{ context, CL_MEM_WRITE_ONLY, byte_size };
  cl::Buffer image_buffer{ context, CL_MEM_READ_ONLY, byte_size };

  // (2) Set arguments
  kernel.setArg(0, result_buffer);
  kernel.setArg(1, image_buffer);
  kernel.setArg(2, m);
  kernel.setArg(3, static_cast<cl_int>(image.size()));

  size_t local_byte_size = (256 + 2*(m/2)) * sizeof(cl_int);
  kernel.setArg(4, cl::Local(local_byte_size));

  // (3) Write data to device
  queue.enqueueWriteBuffer(image_buffer, CL_TRUE, 0, byte_size, image.data());

  // (4) Run and time kernel
  cl_ulong nanoseconds =
    jc::run_and_time_kernel(kernel,
                            queue,
                            cl::NDRange(jc::best_fit(image.size(), 256)),
                            cl::NDRange(256));

  // (5) Read data from device
  queue.enqueueReadBuffer(result_buffer, CL_TRUE, 0, byte_size, result.data());

  int bytes_accessed = (image.size() + image.size() * m) * sizeof(cl_int);
  std::cout << "data throughput: ";
  std::cout << static_cast<double>(bytes_accessed) / nanoseconds;
  std::cout << " GB/s\n";

  return result;
}

int
main(int argc, char* argv[])
{
  try {

    int m = 9;
    int n = 2<<20;
    std::vector<cl_int> image(n);
    std::iota(image.begin(), image.end(), 0);

    std::vector<cl_int> result1 = erosion(image, m);
    std::cout << "Running GPU global erosion... ";
    std::vector<cl_int> result2 = gpu_erosion(image, m);
    std::cout << "Running GPU local  erosion... ";
    std::vector<cl_int> result3 = gpu_local_erosion(image, m);

    if (!std::equal(result1.begin(), result1.end(), result3.begin())) {
      std::cerr << "Your results are not the same!\n";
      std::cerr << "Sequential result:\n";
      jc::show_matrix(result1, 1, n);
      std::cerr << "OpenCL result:\n";
      jc::show_matrix(result3, 1, n);
      return 4;
    }

    return 0;
  } catch (cl::Error& e) {
    std::cerr << e.what() << ": " << jc::readable_error(e.err());
    return 1;
  } catch (std::exception& e) {
    std::cerr << e.what() << "\n";
    return 2;
  } catch (...) {
    std::cerr << "Unexpected error. Aborting!\n";
    return 3;
  }
}
