#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

namespace py = pybind11;

#include "csv_writer.hh"

#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

#include "compute.hh"
#include "compute_interaction.hh"
#include "compute_gravity.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"

#include "system.hh"
#include "system_evolution.hh"


PYBIND11_MODULE(pypart, m) {

    m.doc() = "pybind of the Particles project";

    // Particles factory
    py::class_<ParticlesFactoryInterface>(
            m, "ParticlesFactoryInterface",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def("createSimulation", [](
            ParticlesFactoryInterface &self, const std::string &fname, Real timestep
        ) -> SystemEvolution& { // trailing return type, not required
             return self.createSimulation(fname, timestep);
         // we use reference internal to make sure the memory will be handled
         // by the python garbage collector
         }, py::return_value_policy::reference_internal,
         py::arg("fname"), py::arg("timestep")
     )
    .def("createSimulation", py::overload_cast<const std::string &, Real, py::function>(&ParticlesFactoryInterface::createSimulation<py::function>),
         py::return_value_policy::reference_internal,
         py::arg("fname"), py::arg("timestep"), py::arg("func")
     )
    .def("getInstance", &ParticlesFactoryInterface::getInstance, py::return_value_policy::reference)  // getInstance method
    .def_property_readonly("system_evolution", &ParticlesFactoryInterface::getSystemEvolution );  // getSystemEvolution method


    // Ping pong ball factory
    py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
            m, "PingPongBallsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    // other fnx are not exposed to Python, so we dont add them
    .def("getInstance", &PingPongBallsFactory::getInstance, py::return_value_policy::reference); // getInstance method


    // Planet factory
    py::class_<PlanetsFactory, ParticlesFactoryInterface>(
            m, "PlanetsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def("getInstance", &PlanetsFactory::getInstance, py::return_value_policy::reference);  // getInstance method


    // Material point
    py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
            m, "MaterialPointsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def("getInstance", &MaterialPointsFactory::getInstance, py::return_value_policy::reference);// getInstance method


    // Compute
    py::class_<Compute, std::shared_ptr<Compute>>(
            m, "Compute",
            py::dynamic_attr() // to allow new members to be created dynamically
    );


    // Compute interaction
    py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(
            m, "ComputeInteraction",
            py::dynamic_attr() // to allow new members to be created dynamically
    );


    // Compute gravity
    py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(
            m, "ComputeGravity",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<>())
    //setG method with default argument
    .def("setG", &ComputeGravity::setG, py::arg("G"));


    // Compute temperature
    py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(
            m, "ComputeTemperature",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<>())
    //set private members of ComputeTemperature - give read write access through acessors
    .def_property("conductivity",
          &ComputeTemperature::getConductivity,
          [](ComputeTemperature& c, Real val){c.getConductivity() = val; }
          )
    .def_property("L",
          &ComputeTemperature::getL,
          [](ComputeTemperature& c, Real val){c.getL() = val; }
          )
    .def_property("capacity",
          &ComputeTemperature::getCapacity,
          [](ComputeTemperature& c, Real val){c.getCapacity() = val; }
          )
    .def_property("deltat",
          &ComputeTemperature::getDeltat,
          [](ComputeTemperature& c, Real val){c.getDeltat() = val; }
          )
    .def_property("density",
          &ComputeTemperature::getDensity,
          [](ComputeTemperature& c, Real val){c.getDensity() = val; }
    );


    // Compute verlet interaction
    py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(
            m, "ComputeVerletIntegration",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<Real>())
    .def("addInteraction", &ComputeVerletIntegration::addInteraction);


    // CSV writer
    py::class_<CsvWriter>(
            m, "CsvWriter",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<const std::string&>())
    .def("write", &CsvWriter::write, py::arg("system"));


    // System
    py::class_<System>(
            m, "System",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<>());


    // System evolution
    py::class_<SystemEvolution>(
            m, "SystemEvolution",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
//    .def(py::init<std::unique_ptr<System>>()) // FIXME: why unhappy?
    .def("addCompute", &SystemEvolution::addCompute, py::arg("compute"))
    .def("evolve", &SystemEvolution::evolve)
    .def("getSystem", &SystemEvolution::getSystem)
    .def("setNSteps", &SystemEvolution::setNSteps, py::arg("nsteps"))
    .def("setDumpFreq", &SystemEvolution::setDumpFreq, py::arg("freq"));

}

