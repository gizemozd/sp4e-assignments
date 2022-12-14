#include "fft.hh"
#include "my_types.hh"
#include <gtest/gtest.h>
#include <complex>
/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;

  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
    //std::cout << i << j << std::endl;
  }
  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;

  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
    //std::cout << i << j << std::endl;
  }

  Matrix<complex> res = FFT::transform(m);
  Matrix<complex> res_inv = FFT::itransform(res);

  for (UInt i=0; i<N; i++){
    for (UInt j=0; j<N; j++){
      ASSERT_NEAR(std::real(res_inv(i,j)), std::real(m(i,j)), 1e-10);
      ASSERT_NEAR(std::imag(res_inv(i,j)), std::imag(m(i,j)), 1e-10);
    };
  };

};


/*****************************************************************/

TEST(FFT, compute_frequencies) {

  double python_res [] = {
          0.0, 1.0, 2.0, 3.0, 4.0,
          5.0, 6.0, 7.0, 8.0, 9.0,
          10.0, 11.0, 12.0, 13.0,
          14.0, 15.0, 16.0, 17.0,
          18.0, 19.0, 20.0, 21.0,
          22.0, 23.0, 24.0, 25.0,
          26.0, 27.0, 28.0, 29.0,
          30.0, 31.0, -32.0, -31.0,
          -30.0, -29.0, -28.0, -27.0,
          -26.0, -25.0, -24.0, -23.0,
          -22.0, -21.0, -20.0, -19.0,
          -18.0, -17.0, -16.0, -15.0,
          -14.0, -13.0, -12.0, -11.0,
          -10.0, -9.0, -8.0, -7.0,
          -6.0, -5.0, -4.0, -3.0,
          -2.0, -1.0
  };

  UInt N = 64;

  auto cpp_res = FFT::computeFrequencies(N);

  for (auto&& entry : index(cpp_res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    ASSERT_NEAR(val.real(), python_res[i], 1e-10);
    ASSERT_NEAR(val.imag(), python_res[j], 1e-10);

  };

};
