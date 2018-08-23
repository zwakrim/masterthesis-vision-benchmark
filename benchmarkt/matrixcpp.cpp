#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

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

int
main(int argc, char* argv[])
{
  

    int m = atof(argv[1]);
    int n = atof(argv[2]);

	std::vector<float> matrix(m * n);
    std::vector<float> vector(n, 1.0f);
    for (int row = 0; row < m; ++row)
      for (int col = 0; col < n; ++col)
        matrix[row * n + col] = 1.0f;
	std::vector<float> result1 = matrix_vector(matrix, vector, m, n);
    std::cout << "Running GPU matrix vector... \r\n";

}
