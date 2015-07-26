#ifndef Acrylic_TestEventAction_h
#define Acrylic_TestEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class Acrylic_TestEventAction : public G4UserEventAction
{
public:
    Acrylic_TestEventAction();
    virtual ~Acrylic_TestEventAction();
    
    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
private:
    G4int fPrintModulo;
        
};


#endif


