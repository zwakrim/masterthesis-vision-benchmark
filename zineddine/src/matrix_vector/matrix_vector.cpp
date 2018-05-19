#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <JC/util.hpp>

std::vector<float>
matrix_vector(const std::vector<float>& matrix,
              const std::vector<float>& vector,
              const int m,
              const int n)
{
  assert(matrix.size() == m * n);
  assert(vector.size() == n);
  std::vector<float> result(m, 0); // initialize result with m 0s

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      result[i] += matrix[n * i + j] * vector[j];

  return result;
}

std::vector<float>
gpu_matrix_vector(const std::vector<float>& matrix,
                  const std::vector<float>& vector,
                  const int m,
                  const int n)
{
  assert(matrix.size() == m * n);
  assert(vector.size() == n);
  std::vector<float> result(m);

  cl::Device device = jc::get_device(CL_DEVICE_TYPE_GPU);
  cl::Context context{ device };
  cl::CommandQueue queue{ context, device, CL_QUEUE_PROFILING_ENABLE };

  // TODO
  // (1) Create a file called "kernels.ocl" in the appropriate directory.
  // (2) Write the code for a kernel called "matrix_vector" in this file.
  cl::Program program =
    jc::build_program_from_file("./kernels.ocl", context, device);
  cl::Kernel kernel{ program, "matrix_vector" };

  // (1) Create buffers
  size_t matrix_byte_size = matrix.size() * sizeof(cl_float);
  size_t result_byte_size = result.size() * sizeof(cl_float);
  size_t vector_byte_size = vector.size() * sizeof(cl_float);
  cl::Buffer result_buffer{ context, CL_MEM_WRITE_ONLY, result_byte_size };
  cl::Buffer matrix_buffer{ context, CL_MEM_READ_ONLY, matrix_byte_size };
  cl::Buffer vector_buffer{ context, CL_MEM_READ_ONLY, vector_byte_size };

  // (2) Set arguments
  kernel.setArg(0, result_buffer);
  kernel.setArg(1, matrix_buffer);
  kernel.setArg(2, vector_buffer);
  kernel.setArg(3, m);
  kernel.setArg(4, n);

  // (3) Write data to device
  queue.enqueueWriteBuffer(
    matrix_buffer, CL_TRUE, 0, matrix_byte_size, matrix.data());
  queue.enqueueWriteBuffer(
    vector_buffer, CL_TRUE, 0, vector_byte_size, vector.data());

  // (4) Run and time kernel
  cl_ulong nanoseconds = jc::run_and_time_kernel(
    kernel, queue, cl::NDRange(jc::best_fit(m, 256)), cl::NDRange(256));

  // (5) Read data from device
  queue.enqueueReadBuffer(
    result_buffer, CL_TRUE, 0, result_byte_size, result.data());

  int bytes_accessed = (2 * n + 1) * m * sizeof(float);
  std::cout << "data throughput: ";
  std::cout << static_cast<double>(bytes_accessed) / nanoseconds;
  std::cout << " GB/s\n";

  return result;
}

std::vector<float>
gpu_efficient_matrix_vector(const std::vector<float>& matrix,
                            const std::vector<float>& vector,
                            const int m,
                            const int n)
{
  assert(matrix.size() == m * n);
  assert(vector.size() == n);
  std::vector<float> result(m);

  cl::Device device = jc::get_device(CL_DEVICE_TYPE_GPU);
  cl::Context context{ device };
  cl::CommandQueue queue{ context, device, CL_QUEUE_PROFILING_ENABLE };

  // TODO
  // (1) Create a file called "kernels.ocl" in the appropriate directory.
  // (2) Write the code for a kernel called "matrix_vector" in this file.
  cl::Program program =
    jc::build_program_from_file("./kernels.ocl", context, device);
  cl::Kernel kernel{ program, "efficient_matrix_vector1" };

  // (1) Create buffers
  size_t matrix_byte_size = matrix.size() * sizeof(cl_float);
  size_t result_byte_size = result.size() * sizeof(cl_float);
  size_t vector_byte_size = vector.size() * sizeof(cl_float);
  cl::Buffer result_buffer{ context, CL_MEM_WRITE_ONLY, result_byte_size };
  cl::Buffer matrix_buffer{ context, CL_MEM_READ_ONLY, matrix_byte_size };
  cl::Buffer vector_buffer{ context, CL_MEM_READ_ONLY, vector_byte_size };

  // (2) Set arguments
  kernel.setArg(0, result_buffer);
  kernel.setArg(1, matrix_buffer);
  kernel.setArg(2, vector_buffer);
  kernel.setArg(3, m);
  kernel.setArg(4, n);

  const size_t work_group_size{ 256 };

  kernel.setArg(5, cl::Local(work_group_size * sizeof(cl_float)));

  // (3) Write data to device
  queue.enqueueWriteBuffer(
    matrix_buffer, CL_TRUE, 0, matrix_byte_size, matrix.data());
  queue.enqueueWriteBuffer(
    vector_buffer, CL_TRUE, 0, vector_byte_size, vector.data());

  // (4) Run and time kernel
  cl_ulong nanoseconds =
    jc::run_and_time_kernel(kernel,
                            queue,
                            cl::NDRange(m * work_group_size),
                            cl::NDRange(work_group_size));

  // (5) Read data from device
  queue.enqueueReadBuffer(
    result_buffer, CL_TRUE, 0, result_byte_size, result.data());

  int bytes_accessed = (2 * n + 1) * m * sizeof(float);
  std::cout << "data throughput: ";
  std::cout << static_cast<double>(bytes_accessed) / nanoseconds;
  std::cout << " GB/s\n";

  return result;
}

int
main(int argc, char* argv[])
{
  try {

    int m = 256;
    int n = 256;

    std::vector<float> matrix(m * n);
    std::vector<float> vector(n, 1.0f);
    for (int row = 0; row < m; ++row)
      for (int col = 0; col < n; ++col)
        matrix[row * n + col] = 1.0f;

    std::vector<float> result1 = matrix_vector(matrix, vector, m, n);
    std::cout << "Running GPU matrix vector... ";
    std::vector<float> result2 = gpu_matrix_vector(matrix, vector, m, n);
    std::cout << "Running GPU efficient matrix vector... ";
    std::vector<float> result3 =
      gpu_efficient_matrix_vector(matrix, vector, m, n);

    auto close_enough = [](float val1, float val2) {
        if (val1 == 0) return std::abs(val2) < 1e-6;
        if (val2 == 0) return std::abs(val1) < 1e-6;
        return std::abs(val1 - val2) < 1e-6;
    };

    if (!std::equal(result1.begin(), result1.end(), result3.begin(), close_enough)) {
      std::cerr << "Your results are not the same!\n";
      std::cerr << "Sequential result:\n";
      jc::show_matrix(result1, 1, m);
      std::cerr << "OpenCL result:\n";
      jc::show_matrix(result2, 1, m);
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
