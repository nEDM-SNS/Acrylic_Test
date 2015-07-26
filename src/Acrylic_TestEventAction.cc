#include "Acrylic_TestEventAction.hh"
#include "Acrylic_TestAnalysis.hh"

#include "G4Event.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestEventAction::Acrylic_TestEventAction()
: G4UserEventAction(),
fPrintModulo(1000)
{
}

Acrylic_TestEventAction::~Acrylic_TestEventAction()
{
}

void Acrylic_TestEventAction::BeginOfEventAction(const G4Event* evt)
{
    
    G4int eventID = evt->GetEventID();
    if ( eventID % fPrintModulo == 0 )  {
        G4cout << "\n---> Begin of event: " << eventID << G4endl;
        //CLHEP::HepRandom::showEngineStatus();
    }
        
    
    
}

void Acrylic_TestEventAction::EndOfEventAction(const G4Event* evt)
{

}

