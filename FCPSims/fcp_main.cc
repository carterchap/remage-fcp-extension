#include "RMGManager.hh"
#include "RMGHardware.hh" 

#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"

#include "G4UImanager.hh"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CLI11.hpp"


int main(int argc, char **argv) {
    CLI::App app{"FCP Simulations"};
    int nthreads = 1;
    std::string macroName;
    std::string filename;
    std::string charge_mass;
    std::string outputfilename = "output.lh5";
  
    app.add_option("-m,--macro", macroName,
                   "<Geant4 macro filename> Default: None");
    app.add_option("-g,--gdml", filename,
                    "<GDML filename> Default: None");
    app.add_option("-t, --nthreads", nthreads,
                   "<number of threads to use> Default: ");

    app.add_option("-p, --particle", charge_mass, "Charge/mass string for /FCP/Physics/ParticleProperties");

    app.add_option("-o, --output", outputfilename, "Output filename");
  
    CLI11_PARSE(app, argc, argv);

    RMGManager manager("FCP_Simulations", argc, argv);

    std::cout << "current gdml file: " << filename << std::endl;
    manager.GetDetectorConstruction()->IncludeGDMLFile(filename);
   
    
    
    auto user_init = manager.GetUserInit();
    auto *RunManager = manager.GetG4RunManager();
    RunManager->SetNumberOfThreads(nthreads);
        
    


    manager.SetUserInit(new PhysicsList());

    if (!charge_mass.empty()) {
        
        G4UImanager::GetUIpointer()->ApplyCommand("/FCP/Physics/ParticleProperties " + charge_mass);
    }


    
    



    manager.SetInteractive(true);
    
    if (!macroName.empty())
        manager.IncludeMacroFile(macroName);
        
    else
        manager.SetInteractive(true);

    manager.SetOutputFileName(outputfilename);
    manager.SetNumberOfThreads(nthreads);
    manager.SetOutputOverwriteFiles(true);
    manager.Initialize();
    manager.Run();

    return 0;

    }
        
