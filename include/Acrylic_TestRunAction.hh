#ifndef Acrylic_TestRunAction_h
#define Acrylic_TestRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;
class Acrylic_TestRunActionMessenger;

class Acrylic_TestRunAction : public G4UserRunAction
{
  public:
    Acrylic_TestRunAction();
    virtual ~Acrylic_TestRunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);
    
    void SetFileName(G4String name);


  private:
    G4Timer* timer;
    G4String fileName;
    
    Acrylic_TestRunActionMessenger*  fMessenger;   // messenger


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void Acrylic_TestRunAction::SetFileName(G4String name)
{
    fileName = name;
}

#endif /*Acrylic_TestRunAction_h*/
