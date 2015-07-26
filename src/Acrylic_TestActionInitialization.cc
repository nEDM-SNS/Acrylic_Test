#include "Acrylic_TestActionInitialization.hh"

#include "GPSPrimaryGeneratorAction.hh"

#include "Acrylic_TestRunAction.hh"
//#include "Acrylic_TestEventAction.hh"
#include "Acrylic_TestSteppingAction.hh"
//#include "Acrylic_TestStackingAction.hh"
#include "Acrylic_TestTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestActionInitialization::Acrylic_TestActionInitialization()
: G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestActionInitialization::~Acrylic_TestActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestActionInitialization::BuildForMaster() const
{
    //SetUserAction(new Acrylic_TestRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestActionInitialization::Build() const
{
    SetUserAction(new Acrylic_TestRunAction());
    
    SetUserAction(new GPSPrimaryGeneratorAction());
    
    //SetUserAction(new Acrylic_TestEventAction());
    
//    SetUserAction(new Acrylic_TestStackingAction());
    
    SetUserAction(new Acrylic_TestTrackingAction());

    SetUserAction(new Acrylic_TestSteppingAction());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......