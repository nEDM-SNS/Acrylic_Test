#ifndef Acrylic_TestTrackInformation_h
#define Acrylic_TestTrackInformation_h

#include "G4VUserTrackInformation.hh"


class Acrylic_TestTrackInformation : public G4VUserTrackInformation{
    
public:
    Acrylic_TestTrackInformation();
    virtual ~Acrylic_TestTrackInformation();
    
    void SetStatus(G4int newStatus) {fStatus = newStatus;}
    G4int GetStatus() {return fStatus;}

private:
    G4int fStatus;
    
};

#endif
