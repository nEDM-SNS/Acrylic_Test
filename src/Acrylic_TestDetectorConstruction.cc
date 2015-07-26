#include "Acrylic_TestDetectorConstruction.hh"
#include "NedmDetectorParameters.hh"
#include "NedmMaterials.hh"
#include "NedmCellSide.hh"

#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4UImanager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Acrylic_TestDetectorConstruction::Acrylic_TestDetectorConstruction()
:
fMaterials(NULL)
{
    fExperimentalHall_box = NULL;
    fExperimentalHall_log = NULL;
    fExperimentalHall_phys = NULL;
    
    fParams = NedmDetectorParameters::instance();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestDetectorConstruction::~Acrylic_TestDetectorConstruction() {
    if (fMaterials)         delete fMaterials;
    if (fParams)            delete fParams;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* Acrylic_TestDetectorConstruction::Construct(){
    
    if (fExperimentalHall_phys) {
        G4GeometryManager::GetInstance()->OpenGeometry();
        G4PhysicalVolumeStore::GetInstance()->Clean();
        G4LogicalVolumeStore::GetInstance()->Clean();
        G4SolidStore::GetInstance()->Clean();
        G4LogicalSkinSurface::CleanSurfaceTable();
        G4LogicalBorderSurface::CleanSurfaceTable();
    }
    

    fMaterials = NedmMaterials::GetInstance();


    return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* Acrylic_TestDetectorConstruction::ConstructDetector()
{
    //The experimental hall walls are all 1m away from housing walls
    G4double expHall_x = 10.*m;
    G4double expHall_y = 10.*m;
    G4double expHall_z = 10.*m;
    
    //Create experimental hall
    fExperimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
    fExperimentalHall_log = new G4LogicalVolume(fExperimentalHall_box,
                                                G4Material::GetMaterial("G4_AIR"),
                                            //G4Material::GetMaterial("Vacuum"),
                                                "expHall_log",0,0,0);
    fExperimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),fExperimentalHall_log,"expHall",0,false,0);
    
    fExperimentalHall_log->SetVisAttributes(G4VisAttributes::Invisible);
    
    
    new NedmCellSide(0,G4ThreeVector(0.,0.,0.),fExperimentalHall_log,0);
    ConstructPhotonDet();
    
    return fExperimentalHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestDetectorConstruction::ConstructPhotonDet()
{
    G4Box* photDet_Solid = new G4Box("photDet",
                                      2*fParams->cell_size().x(),
                                      .1*mm,
                                      2*fParams->cell_size().z());
    
    G4LogicalVolume* photonDet_log = new G4LogicalVolume(photDet_Solid,G4Material::GetMaterial("PMMA"),"photDet");
    
    new G4PVPlacement(0,G4ThreeVector(0,-4*fParams->cell_size().y(),0),photonDet_log,"photonDet",fExperimentalHall_log,false,0);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestDetectorConstruction::ConstructSDandField() {}

