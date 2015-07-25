#include "Acrylic_TestRunActionMessenger.hh"
#include "Acrylic_TestRunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

Acrylic_TestRunActionMessenger::Acrylic_TestRunActionMessenger(Acrylic_TestRunAction* runAction)
 : G4UImessenger(),
   fRunAction(runAction),
   fDirectory(0),
   fSetFileNameCmd(0)
{
  fDirectory = new G4UIdirectory("/Acrylic_Test/run/");
  fDirectory->SetGuidance("run control");
   
  fSetFileNameCmd 
    = new G4UIcmdWithAString("/Acrylic_Test/run/setFileName",this);
  fSetFileNameCmd->SetGuidance("Set the analysis file name (default: Acrylic_Test");
  fSetFileNameCmd->SetParameterName("fileName",false);
  fSetFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

Acrylic_TestRunActionMessenger::~Acrylic_TestRunActionMessenger()
{
  delete fSetFileNameCmd;
  delete fDirectory;   
}

void Acrylic_TestRunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if ( command == fSetFileNameCmd ) {
    fRunAction->SetFileName(newValue);
  }

}
