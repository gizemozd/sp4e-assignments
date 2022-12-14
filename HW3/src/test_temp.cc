#include "compute_temperature.hh"
#include "my_types.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include "material_points_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>

/*****************************************************************/
// Fixture class
class RandomParticles : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup initialization
    MaterialPointsFactory::getInstance();
    n_particles = 8;
    lowerLimit = -1.0;
    upperLimit = 1.0;
    gridLength = upperLimit - lowerLimit; //total length of the grid (max-min limits of grid)
    gridResolution = 1.0 * gridLength / (n_particles-1.0);

    //Initialize the points
    for (UInt j = 0; j < n_particles; j++) {
      for (UInt i = 0; i < n_particles; i++) {
        MaterialPoint p;
        p.getPosition()[0] = lowerLimit + i * gridResolution;
        p.getPosition()[1] = lowerLimit + j * gridResolution;

        // Boundary constraints
        if (p.getPosition()[0] == lowerLimit || p.getPosition()[0] == upperLimit
            || p.getPosition()[1] == lowerLimit || p.getPosition()[1] == upperLimit){
          p.isBoundary() = true;
          //std::cout << "true";
        }else{
          p.isBoundary() = false;
        }
        points.push_back(p);
      }
    }

    // Set up the temperature computation
    temperature = std::make_shared<ComputeTemperature>();
    temperature->deltaT = 1e-5;
    temperature->rho = 1.0;
    temperature->heatCapacity = 1.0;
    temperature->heatConductivity = 1.0;

  }

  System system;
  std::vector<MaterialPoint> points;
  std::shared_ptr<ComputeTemperature> temperature;
  UInt n_particles;
  Real gridLength;
  Real gridResolution;
  Real upperLimit;
  Real lowerLimit;
};
/*****************************************************************/
// Ex 4 - 2 test
TEST_F(RandomParticles, Homogeneous) {
  Real initial_temperature=10.;
  UInt time_steps=50;

  // Add particle to system
  for (auto &p : points) {
    p.getTemperature() = initial_temperature;
    p.getHeatRate() = 0.;
    system.addParticle(std::make_shared<MaterialPoint>(p));
  }

  // Temperature is uniform, no heat exchange
  for (UInt i = 0; i < time_steps; ++i) {
    temperature->compute(system);
  }

  // Temperature should remain the same
  for (auto &p : system){
    auto &mPoint = static_cast<MaterialPoint&>(p);
    // Temp should be close to the initial value
    //std::cout << "Location " << mPoint.getPosition();
    //std::cout << "Temperature " << mPoint.getTemperature() << std::endl;

    ASSERT_NEAR(mPoint.getTemperature(), initial_temperature, 1e-10);

    }

  std::cout << "*************************************************" << std::endl;
  std::cout << "EX 4-2 Passed the homogeneous temperature state " << std::endl;
  std::cout << "*************************************************" << std::endl;

}
/*****************************************************************/

//*****************************************************************/
// Ex 4 - 3 test
TEST_F(RandomParticles, VolumetricEx3) {
  UInt time_steps=10;
  // Let's set the properties again
  // Variables
  Real heatRate;
  Real tempValue;
  Real tempEq;
  Real x_coord;
  Real y_coord;

  // Add particle to system
  for (auto &p : points) {
    // Particle location
    x_coord = p.getPosition()[0];
    y_coord = p.getPosition()[1];
    p.getTemperature() = sin(2.0*M_PI*x_coord/gridLength);
    p.getHeatRate() = pow((2.0*M_PI)/gridLength,2.0)*sin(2.0*M_PI*(x_coord/gridLength));


//    // Set temperature field
//    if (x_coord == -1.0 || x_coord == 1.0
//        || y_coord == -1.0 || y_coord == 1.0){
//      tempValue = 0.0;
//    } else if (x_coord > -1.0 && x_coord <= -0.5){
//      tempValue = -1.0 * x_coord - 1.0;
//    } else if (x_coord > -0.5 && x_coord <= 0.5){
//      tempValue = x_coord;
//    } else if (x_coord > 0.5){
//      tempValue = -1.0 * x_coord + 1.0;
//    }
//    p.getTemperature() = tempValue;

    system.addParticle(std::make_shared<MaterialPoint>(p));
  }

  // Temperature is uniform, no heat exchange
  for (UInt i = 0; i < time_steps; ++i) {
    temperature->compute(system);
  }

  // Temperature should remain the same
  for (auto &p : system){
    auto &mPoint = static_cast<MaterialPoint&>(p);

    // Particle location
    x_coord = mPoint.getPosition()[0];
    y_coord = mPoint.getPosition()[1];
    tempEq = sin(2.0*M_PI*x_coord/gridLength);

    ASSERT_NEAR(mPoint.getTemperature(), tempEq, 1e-2);
  }
  std::cout << "*************************************************" << std::endl;
  std::cout << "EX 4-3 Passed the volumetric heat source example " << std::endl;
  std::cout << "*************************************************" << std::endl;

}


///*****************************************************************/
//// Ex 4 - 4 test
TEST_F(RandomParticles, VolumetricEx4) {
  UInt time_steps=10;
  // Let's set the properties again
  temperature->rho = 1.0;
  temperature->heatCapacity = 1.0;
  temperature->heatConductivity = 1.0;
  // Variables
  Real heatRate;
  Real tempValue;
  Real tempEq;
  Real x_coord;
  Real y_coord;

  // Add particle to system
  for (auto &p : points) {
    // Particle location
    x_coord = p.getPosition()[0];
    y_coord = p.getPosition()[1];
//    std::cout << x_coord << " , " << y_coord << std::endl;

    // Set heat source
    // Since the particle might not be exactly at the heat source, we select the point
    // that is closest to the heat source location
    if (abs(x_coord - 0.5) < gridResolution / 2.0){
      heatRate = 1.0;
      //std::cout << x_coord << " , " << y_coord << std::endl;

    } else if (abs(x_coord + 0.5) < gridResolution / 2.0){
      heatRate = -1.0;
      //std::cout << x_coord << " , " << y_coord << std::endl;

    } else {
      heatRate = 0.0;
    }
    p.getHeatRate() = heatRate;

    // Set temperature field
    if (x_coord == -1.0 || x_coord == 1.0
        || y_coord == -1.0 || y_coord == 1.0){
      tempValue = 0.0;
    } else if (x_coord > -1.0 && x_coord <= -0.5){
      tempValue = -1.0 * x_coord - 1.0;
    } else if (x_coord > -0.5 && x_coord <= 0.5){
      tempValue = x_coord;
    } else if (x_coord > 0.5){
      tempValue = -1.0 * x_coord + 1.0;
    }
    p.getTemperature() = tempValue;

    system.addParticle(std::make_shared<MaterialPoint>(p));
  }

  // Temperature is uniform, no heat exchange
  for (UInt i = 0; i < time_steps; ++i) {
    temperature->compute(system);
  }

  // Temperature should remain the same
  for (auto &p : system){
    auto &mPoint = static_cast<MaterialPoint&>(p);

    // Particle location
    x_coord = mPoint.getPosition()[0];
    y_coord = mPoint.getPosition()[1];
    // Resulting temperature should be equal to the eq. temp
    if (x_coord == -1.0 || x_coord == 1.0
        || y_coord == -1.0 || y_coord == 1.0){
      tempEq = 0.0;
    } else if (x_coord > -1.0 && x_coord <= -0.5){
      tempEq = -1.0 * x_coord - 1.0;
    } else if (x_coord > -0.5 && x_coord <= 0.5){
      tempEq = x_coord;
    } else if (x_coord > 0.5){
      tempEq = -1.0 * x_coord + 1.0;
    }
    // Temp should be close to the equilibrium value
    //std::cout << "Location " << mPoint.getPosition();
    //std::cout << "Temperature " << mPoint.getTemperature() << "Eq " << tempEq << std::endl;

    ASSERT_NEAR(mPoint.getTemperature(), tempEq, 1e-2);
  }
  std::cout << "*************************************************" << std::endl;
  std::cout << "EX 4-4 Passed the volumetric heat source example " << std::endl;
  std::cout << "*************************************************" << std::endl;

}