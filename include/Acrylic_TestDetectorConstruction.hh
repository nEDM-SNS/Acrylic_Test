#ifndef Acrylic_TestDetectorConstruction_H
#define Acrylic_TestDetectorConstruction_H 1

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;

class NedmMaterials;
class NedmDetectorParameters;


#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4Cache.hh"

class Acrylic_TestDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    Acrylic_TestDetectorConstruction();
    virtual ~Acrylic_TestDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();



  private:

    NedmMaterials* fMaterials;
    NedmDetectorParameters* fParams;
    
    G4VPhysicalVolume* ConstructDetector();
    void ConstructCellPlates();
    void ConstructSquareTubeReflector();
    void ConstructFullTentReflector();
    
    G4Box* fExperimentalHall_box;
    G4LogicalVolume* fExperimentalHall_log;
    G4VPhysicalVolume* fExperimentalHall_phys;
    

    
};

#endif
