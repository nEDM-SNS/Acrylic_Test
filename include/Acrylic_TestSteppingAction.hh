#ifndef Acrylic_TestSteppingAction_h
#define Acrylic_TestSteppingAction_h 1

#include "G4UserSteppingAction.hh"

//! User defined actions to be taken for each simulation step.
class Acrylic_TestSteppingAction : public G4UserSteppingAction
{
  public:
    void UserSteppingAction(const G4Step*);
    
  private:


};

#endif
