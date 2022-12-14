#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include <iostream>
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
#include <complex>
/* ------------------------------------------------------ */
// Struct is a class where everything is public.
struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* --------------------------FORWARD TRANSFORM---------------------------- */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
    // Forward Fourier Transform
    UInt rows = m_in.rows();
    UInt cols = m_in.cols();
    Matrix<complex> m_out(rows);

    // Create input and output matrices
    fftw_complex *matrix_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);
    fftw_complex *matrix_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);

    // Assign the input values in a FFTW compatible format
    for (UInt i=0; i<rows; i++){
      for (UInt j=0; j<cols; j++){
        matrix_in[i * cols + j][0] = std::real(m_in(i,j));
        matrix_in[i * cols + j][1] = std::imag(m_in(i,j));
      };
    };

    // FFTW plan, using FFTW_FORWARD for forward FFT
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, matrix_in, matrix_out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    // Assign the results in an output matrix that is in Matrix format.
    for (UInt i=0; i<rows; i++){
      for (UInt j=0; j<cols; j++){
        m_out(i,j) = std::complex<Real> {matrix_out[i * cols + j][0], matrix_out[i * cols + j][1]};
      };
    };

    // Clean-up
    fftw_destroy_plan(plan);

    return m_out;

};

/* --------------------------INVERSE---------------------------- */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
    // Inverse Fourier Transform
    UInt rows = m_in.rows();
    UInt cols = m_in.cols();
    Real scale = 1.0 / (rows * cols);

    Matrix<complex> m_out(rows);

    // Create input and output matrices
    fftw_complex *matrix_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);
    fftw_complex *matrix_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);

    // Assign the input values in a FFTW compatible format
    for (UInt i=0; i<rows; i++){
      for (UInt j=0; j<cols; j++){
        matrix_in[i * cols + j][0] = std::real(m_in(i,j));
        matrix_in[i * cols + j][1] = std::imag(m_in(i,j));
      };
    };

    // FFTW plan, using FFTW_BACKWARD for inverse FFT
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, matrix_in, matrix_out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    // Assign the results in an output matrix that is in Matrix format.
    for (UInt i=0; i<rows; i++){
      for (UInt j=0; j<cols; j++){
        m_out(i,j) = std::complex<Real> {matrix_out[i * cols + j][0] * scale, matrix_out[i * cols + j][1] * scale};
      };
    };

    // Clean-up
    fftw_destroy_plan(plan);

    return m_out;

};

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {

    Matrix<std::complex<int>> m_out(size);
    UInt limit;
    int real_num, imag_num;
    // First check if the window size is even or odd.
    if (size % 2 == 0) {limit = (size / 2) - 1;}
    else { limit = (size - 1) / 2;};

    for (auto&& entry : index(m_out)) {
      int i = std::get<0>(entry);
      int j = std::get<1>(entry);
      auto& val = std::get<2>(entry);
      if (i <= limit){
        real_num = i;
        if (j <= limit){
          imag_num = j;
        } else{
          imag_num = j - size;
        }
      } else {
        real_num = i - size;
        if (j <= limit){
          imag_num = j;
        } else{
          imag_num = j - size;
        }
      }

      val = std::complex<int>(real_num, imag_num);
      //std::cout << real_num << "," << imag_num << std::endl;
    }

    return m_out;
};

#endif  // FFT_HH
