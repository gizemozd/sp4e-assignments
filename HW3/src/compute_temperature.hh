#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "compute_interaction.hh"
#include <functional>
#include "matrix.hh"
#include "my_types.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  ComputeTemperature();

  virtual ~ComputeTemperature() {};
  //! Penalty contact implementation
  void compute(System& system) override;

  Real rho; // Mass density
  Real heatCapacity; // Heat capacity
  Real heatConductivity; // Heat conductivity
  Real deltaT; // Time step for integration
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
