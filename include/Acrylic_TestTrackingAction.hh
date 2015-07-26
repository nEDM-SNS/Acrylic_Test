#ifndef Acrylic_TestTrackingAction_h
#define Acrylic_TestTrackingAction_h 1

#include "G4UserTrackingAction.hh"

class Acrylic_TestTrackingAction : public G4UserTrackingAction {
    
public:
    
    Acrylic_TestTrackingAction() { };
    virtual ~Acrylic_TestTrackingAction() { };
    
    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);
    
    
};

#endif
