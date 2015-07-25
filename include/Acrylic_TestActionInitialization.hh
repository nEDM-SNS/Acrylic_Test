#ifndef Acrylic_TestActionInitialization_h
#define Acrylic_TestActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class Acrylic_TestActionInitialization : public G4VUserActionInitialization
{
  public:
    Acrylic_TestActionInitialization();
    virtual ~Acrylic_TestActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif
