#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */
/*!
 * @brief Compute Temperature class
 */
ComputeTemperature::ComputeTemperature()
{
  //FIXME later setters
  this->rho = 1;
  this->heatCapacity = 1;
  this->heatConductivity = 1;
  this->deltaT = 0.001;
};

/*!
 * @brief a function for computing the heat distribution
 * @param system system input
 */
void ComputeTemperature::compute(System& system) {
  // Initialize the matrices
  UInt noParticles = system.getNbParticles();
  UInt matrixSize = std::sqrt(noParticles);
  Matrix<complex> tempMatrix(matrixSize);
  Matrix<complex> heatMatrix(matrixSize);
  Matrix<complex> tempFourier(matrixSize);
  Matrix<complex> tempFourierDiff(matrixSize);
  Matrix<complex> heatFourier(matrixSize);
  Matrix<complex> tempFourierInv(matrixSize);
  // Construct the coords matrix
  Matrix<std::complex<int>> fourierCoords = FFT::computeFrequencies(matrixSize);

  // Construct the heat and temperature matrices
  for (UInt i = 0; i < matrixSize; i++) {
    for (UInt j = 0; j < matrixSize; j++) {
      auto& particle = system.getParticle(i * matrixSize + j);
      // Static casting to convert particle into material point
      auto& mp = static_cast<MaterialPoint&>(particle);
      tempMatrix(i,j) = mp.getTemperature();
      heatMatrix(i,j) = mp.getHeatRate();
      //std::cout << "Temp" <<  tempMatrix(i,j) <<"," << "Heat" <<  heatMatrix(i,j) << std::endl;

    }
  }

  // STEP 1 - Take the fourier transform of the heat equation
  tempFourier = FFT::transform(tempMatrix);
  heatFourier = FFT::transform(heatMatrix);
  //std::cout << "step 2 "  << std::endl;

  // STEP 2 - Construct the delta heat / delta t matrix
  Real eqConstant = (1.0 / (this->rho * this->heatCapacity));
  for (UInt i = 0; i < matrixSize; i++) {
    for (UInt j = 0; j < matrixSize; j++) {
      // Coordinates - FIXME SOMETHING IS WRONG HERE.
      // Convert frequencies into rad/sec
      Real q_x = std::real(fourierCoords(i,j)) * 2.0 * M_PI;
      Real q_y = std::imag(fourierCoords(i,j)) * 2.0 * M_PI;
      Real coords = q_x * q_x + q_y * q_y;
      tempFourierDiff(i,j) = eqConstant * (heatFourier(i,j) - this->heatConductivity * tempFourier(i,j) * coords);
    }
  }
  //std::cout << "step 3 "  << std::endl;

  // STEP 3 - Take the inverse Fourier Transform
  tempFourierInv = FFT::itransform(tempFourierDiff);

  // STEP 4 - Euler integration
  // Construct the heat and temperature matrices
  for (UInt i = 0; i < matrixSize; i++) {
    for (UInt j = 0; j < matrixSize; j++) {
      auto& particle = system.getParticle(i * matrixSize + j);
      // Static casting to convert particle into material point
      auto& mp = static_cast<MaterialPoint&>(particle);
      // If boundary, then temperature should not evolve with time
      if (mp.isBoundary()== false){
        mp.getTemperature() += this->deltaT * std::real(tempFourierInv(i,j));
      } else {
        mp.getTemperature() += 0.; // Boundary temparture is 0
      }
      //std::cout << "Temperature " << mp.getTemperature() << std::endl;
    }
  }

};

/* -------------------------------------------------------------------------- */
