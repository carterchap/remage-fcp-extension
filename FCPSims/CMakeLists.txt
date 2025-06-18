cmake_minimum_required(VERSION 3.8)

project(FCP_Simulations)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(remage REQUIRED COMPONENTS GDML)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(
  FCP_Simulations
  fcp_main.cc
  src/PhysicsList.cc
  src/PhysListMessenger.cc
  src/G4FCPPlus.cc
  src/G4FCPMinus.cc
  src/FCPPhysics.cc
  src/FCPPairProduction.cc
  src/FCPPairProductionModel.cc
  src/FCPMultipleScattering.cc
  src/FCPIonisation.cc 
  src/FCPBremsstrahlungModel.cc
  src/FCPBremsstrahlung.cc
  src/FCPBetheBlochModel.cc)

target_link_libraries(FCP_Simulations PUBLIC RMG::remage)

target_include_directories(FCP_Simulations PUBLIC ${PROJECT_SOURCE_DIR}/include)
