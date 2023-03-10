
cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)

################################################################
# libpart
################################################################

add_library(part
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc 
  )


add_executable(hw3 main.cc)

find_library (FFTW_LIBRARIES fftw3 libfftw3-dev)
target_link_libraries(hw3 part gtest_main gtest pthread ${FFTW_LIBRARIES})
#target_link_libraries(gtest_main gtest pthread part ${FFTW_LIBRARIES})

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  add_subdirectory(googletest)
  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)
  add_executable(test_temp test_temp.cc)

  target_link_libraries(test_kepler part gtest_main gtest pthread )
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
  target_link_libraries(test_temp part gtest_main gtest pthread ${FFTW_LIBRARIES})

  add_custom_target(test ./test_kepler && ./test_fft && ./test_temp.cc part test_kepler test_fft test_temp)
else()
  message("
*********************************************
google tests is missing. 
Did you forget `git submodule update --init`
*********************************************
")
  message(FATAL_ERROR "exit")
endif()

################################################################
# Version if we want to add FFTW option
################################################################
#option (FFT_OPT "Use FFTW for project" ON)
#if (FFT_OPT)
#  find_library (FFTW_LIBRARIES fftw3 libfftw3-dev)
#  target_link_libraries(hw3 part gtest_main gtest pthread ${FFTW_LIBRARIES})
#else()
#  target_link_libraries(hw3 part gtest_main gtest pthread)
#endif(FFT_OPT)
#
#add_executable(hw3 main.cc)
#
#if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
#  if (FFT_OPT)
#    add_subdirectory(googletest)
#    add_executable(test_kepler test_kepler.cc)
#    add_executable(test_fft test_fft.cc)
#    add_executable(test_temp test_temp.cc)
#
#    target_link_libraries(test_kepler part gtest_main gtest pthread )
#    target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
#    target_link_libraries(test_temp part gtest_main gtest pthread ${FFTW_LIBRARIES})
#
#    add_custom_target(test ./test_kepler && ./test_fft && ./test_temp.cc part test_kepler test_fft test_temp)
#  else()
#    add_executable(test_kepler test_kepler.cc)
#
#    target_link_libraries(test_kepler part gtest_main gtest pthread )
#    add_custom_target(test ./test_kepler part test_kepler )
#else()
#  message("
#*********************************************
#google tests is missing.
#Did you forget `git submodule update --init`
#*********************************************
#")
#  message(FATAL_ERROR "exit")
#endif()


################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

  # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
    )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)
