# fcp-simulations

Code allows REMAGE to simulate Fractionally Charged Particles, or Lightly Ionzing Particles with custom mass and charge as inputs 
credit: https://github.com/SamirBanik/FCP_Simulation, for FCP Code, and https://github.com/legend-exp/remage

---

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Folder Structure](#folder-structure)


---

## Installation

Instructions on how to set up the project:

Assumes remage has been installed using docker. This example works locally, for LONGLEAF or NERSC, it works the same just open a shell inside of the remage container or .sif file

```bash
#Pulls the remage container, open a terminal session inside of the container

docker pull legendexp/remage

docker run -it --rm \
  --entrypoint /bin/bash \
  -v ~/Downloads:/mnt/Downloads \
  -e DISPLAY=host.docker.internal:0 \
  legendexp/remage

#navigate to your folder where you have the FCP code from this repository, in my exmaple it is in my Downloads folder.
#go to the empty build folder

cd /mnt/Downloads/fcp-simulations/build

#Compile

cmake ..
make -j$(nproc)

#Now check your build folder and there should be an executable called 'FCP_Simulations'

---

## Usage

See fcp_main.cc for details on commands
FCP Physics is already included. You can choose to simulate FCPs through the same methodology as standard Geant4 particles

```bash
/RMG/Generator/Select GPS
/gps/particle FCP+

# To run a simulation, open a terminal session inside of the container

docker run -it --rm \
  --entrypoint /bin/bash \
  -v ~/Downloads:/mnt/Downloads \
  -e DISPLAY=host.docker.internal:0 \
  legendexp/remage
#Navigate to the Executable 
cd /mnt/downloads/build

#Run the simulation, -g is how you select a gdml file to use for geometry, -p is how you choose the charge of the particle, the mass of the particle. -m is how you pick the macro file to run. If you want to use the GUI, then then do not enter in a macro file and you can manually input commands that way


./FCP_Simulations -g geometry.gdml -p "0.05 100 MeV" -m macro.txt



