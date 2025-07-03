/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
//      File:        PhysicsList.cc                                 /////
//      Description: An implementation of the Physics List class    /////
//      Modified from Samir Banik's PhysicsList.cc                  /////
// **********************************************************************
// ----------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////




#include "PhysicsList.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"
#include "G4EmParameters.hh" 
#include "G4EmStandardPhysics.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "PhysListMessenger.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

PhysicsList::PhysicsList(G4int ver):
  G4VModularPhysicsList(),
  messenger(new PhysListMessenger(this)),
  verbose(ver)
{
  defaultCutValue = 0.001 * mm;  // Like RMGPhysics: tuned to ~100 keV in Ge
  AddFCPPhysics(0.01, 100 * MeV);  // Default FCP charge and mass
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(lPhys);

  SetVerboseLevel(verbose);

  // EM parameter settings
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetVerbose(verbose);
  param->SetMinEnergy(2e-6 * eV);
  param->SetMaxEnergy(100 * PeV);
}

PhysicsList::~PhysicsList()
{
  delete messenger;
}

void PhysicsList::ConstructParticle()
{
  G4BosonConstructor().ConstructParticle();
  G4LeptonConstructor().ConstructParticle();
  G4MesonConstructor().ConstructParticle();
  G4BaryonConstructor().ConstructParticle();
  G4IonConstructor().ConstructParticle();
  G4ShortLivedConstructor().ConstructParticle();
  lPhys->ConstructParticle();  // FCP
}

void PhysicsList::SetCuts()
{
  if (verboseLevel > 0) {
    G4cout << "PhysicsList::SetCuts:";
    G4cout << " CutLength : " << defaultCutValue / mm << " mm" << G4endl;
  }

  // Default region cuts
  G4ProductionCuts* defaultCuts = new G4ProductionCuts();
  defaultCuts->SetProductionCut(defaultCutValue, "gamma");
  defaultCuts->SetProductionCut(defaultCutValue, "e-");
  defaultCuts->SetProductionCut(defaultCutValue, "e+");
  defaultCuts->SetProductionCut(defaultCutValue, "proton");

  G4Region* defaultRegion = G4RegionStore::GetInstance()->GetRegion("DefaultRegionForTheWorld");
  if (defaultRegion) {
    defaultRegion->SetProductionCuts(defaultCuts);
  }

  // Sensitive region cuts (e.g. for your detector volume, like "ActiveVolume")
  G4Region* sensitiveRegion = G4RegionStore::GetInstance()->GetRegion("SensitiveRegion");
  if (sensitiveRegion) {
    G4ProductionCuts* sensCuts = new G4ProductionCuts();
    sensCuts->SetProductionCut(defaultCutValue, "gamma");
    sensCuts->SetProductionCut(defaultCutValue, "e-");
    sensCuts->SetProductionCut(defaultCutValue, "e+");
    sensCuts->SetProductionCut(defaultCutValue, "proton");
    sensitiveRegion->SetProductionCuts(sensCuts);
  }

  // Optional: globally set energy range for production cuts
  // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(50 * eV, 100 * PeV);
}
