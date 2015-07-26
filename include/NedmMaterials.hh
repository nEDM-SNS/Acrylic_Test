#ifndef NedmMaterials_h
#define NedmMaterials_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

class NedmMaterials
{
  public:

    virtual ~NedmMaterials();
 
    static NedmMaterials* GetInstance();

    G4Material* GetMaterial(const G4String);
 
  private:
 
    NedmMaterials();

    void CreateMaterials();

  private:

    static NedmMaterials* fInstance;

    G4NistManager*     fNistMan;

    G4Material*        fAir;

    G4Material*        fPMMA;
    G4Material*        fWLSPMMA;
    G4Material*        fPethylene;
    G4Material*        fFPethylene;
    G4Material*        fPolystyrene;
    G4Material*        fTPB_outer;
    G4Material*        fTPB_inner;
    G4Material*        fSilicone;

};

#endif /*NedmMaterials_h*/
