#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <JC/util.hpp>

int
main(int argc, char* argv[])
{
  try {
    if (argc < 3) {
      std::ostringstream oss;
      oss << "Usage: " << argv[0] << " <file_name> <device_name> [options]";
      throw std::runtime_error(oss.str());
    }
    std::string file_name{ argv[1] };
    std::string device_name{ argv[2] };
    const char* options = nullptr;
    if (argc > 3)
      options = argv[3];

    cl::Device device = jc::get_device(device_name);
    cl::Context context{ device };

    cl::Program program =
      jc::build_program_from_file(file_name, context, device, options);

    std::vector<size_t> binary_sizes;
    program.getInfo<std::vector<size_t>>(CL_PROGRAM_BINARY_SIZES,
                                         &binary_sizes);

    std::vector<char*> binaries;
    for (auto binary_size : binary_sizes)
      binaries.push_back(new char[binary_size]);

    program.getInfo<std::vector<char*>>(CL_PROGRAM_BINARIES, &binaries);

    std::cout << "Binaries are: \n";
    for (const auto& binary : binaries)
      std::cout << binary << "\n";

    for (auto& binary : binaries)
      delete[] binary;

    return 0;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what();
    return 2;
  } catch (...) {
    std::cerr << "Something unexpected happened\n";
    return 1;
  }
}
