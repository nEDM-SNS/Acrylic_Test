#ifndef Acrylic_TestRunActionMessenger_h
#define Acrylic_TestRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class Acrylic_TestRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class Acrylic_TestRunActionMessenger: public G4UImessenger
{
  public:
    Acrylic_TestRunActionMessenger(Acrylic_TestRunAction* runAction);
    virtual ~Acrylic_TestRunActionMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Acrylic_TestRunAction* 	 fRunAction;
    G4UIdirectory*           fDirectory;
    G4UIcmdWithAString*      fSetFileNameCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
