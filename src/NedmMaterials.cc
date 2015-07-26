#include "NedmMaterials.hh"

#include "G4SystemOfUnits.hh"

NedmMaterials* NedmMaterials::fInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NedmMaterials::NedmMaterials()
{
    fNistMan = G4NistManager::Instance();
    
    fNistMan->SetVerbose(2);
    
    CreateMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NedmMaterials::~NedmMaterials()
{
    delete    fPMMA;
    delete    fWLSPMMA;
    delete    fPethylene;
    delete    fFPethylene;
    delete    fPolystyrene;
    delete    fTPBDopedPS;
    delete    fSilicone;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NedmMaterials* NedmMaterials::GetInstance()
{
    if (fInstance == 0)
    {
        fInstance = new NedmMaterials();
    }
    return fInstance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* NedmMaterials::GetMaterial(const G4String material)
{
    G4Material* mat =  fNistMan->FindOrBuildMaterial(material);
    
    if (!mat) mat = G4Material::GetMaterial(material);
    if (!mat) {
        std::ostringstream o;
        o << "Material " << material << " not found!";
        G4Exception("NedmMaterials::GetMaterial","",
                    FatalException,o.str().c_str());
    }
    
    return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NedmMaterials::CreateMaterials()
{
    G4double density;
    G4int ncomponents;
    G4double fractionmass;
    std::vector<G4int> natoms;
    std::vector<G4double> fractionMass;
    std::vector<G4String> elements;
    
    // Materials Definitions
    // =====================
    
    //--------------------------------------------------
    // Vacuum
    //--------------------------------------------------
    
    fNistMan->FindOrBuildMaterial("G4_Galactic");
    
    //--------------------------------------------------
    // Air
    //--------------------------------------------------
    
    fAir = fNistMan->FindOrBuildMaterial("G4_AIR");
    
    //--------------------------------------------------
    // PMMA
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(5);
    elements.push_back("H");     natoms.push_back(8);
    elements.push_back("O");     natoms.push_back(2);
    
    density = 1.190*g/cm3;
    
    fPMMA = fNistMan->
    ConstructNewMaterial("PMMA", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // WLSfiber PMMA - PMMA w/ different MPT
    //--------------------------------------------------
    
    fWLSPMMA = new   G4Material("WLSPMMA",density,fPMMA);
    
    //--------------------------------------------------
    // Cladding (polyethylene)
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(2);
    elements.push_back("H");     natoms.push_back(4);
    
    density = 1.200*g/cm3;
    
    fPethylene = fNistMan->
    ConstructNewMaterial("Pethylene", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // Double Cladding (fluorinated polyethylene)
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(2);
    elements.push_back("H");     natoms.push_back(4);
    
    density = 1.400*g/cm3;
    
    fFPethylene = fNistMan->
    ConstructNewMaterial("FPethylene", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // Polystyrene
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(8);
    elements.push_back("H");     natoms.push_back(8);
    
    density = 1.050*g/cm3;
    
    fPolystyrene = fNistMan->
    ConstructNewMaterial("Polystyrene", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // Tetraphenyl butadiene (TPB)
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(28);
    elements.push_back("H");     natoms.push_back(22);
    
    density = 1.079*g/cm3;
    
    G4Material* TPB = fNistMan->
    ConstructNewMaterial("TPB", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // TPB doped PS matrix - 2% TPB and 98% polystyrene by weight.
    //--------------------------------------------------
    
    // Assuming same density as PS?
    density = 1.050*g/cm3;
    
    fTPBDopedPS =
    new G4Material("TPBDopedPS", density, ncomponents=2);
    
    fTPBDopedPS->AddMaterial(TPB,         fractionmass = 2*perCent);
    fTPBDopedPS->AddMaterial(fPolystyrene, fractionmass = 98*perCent);
    
    //--------------------------------------------------
    // Silicone (Template for Optical Grease)
    //--------------------------------------------------
    
    elements.push_back("C");     natoms.push_back(2);
    elements.push_back("H");     natoms.push_back(6);
    
    density = 1.060*g/cm3;
    
    fSilicone = fNistMan->
    ConstructNewMaterial("Silicone", elements, natoms, density);
    
    elements.clear();
    natoms.clear();
    
    //--------------------------------------------------
    // Aluminium
    //--------------------------------------------------
    
    fNistMan->FindOrBuildMaterial("G4_Al");
    
    //
    // ------------ Generate & Add Material Properties Table ------------
    //
    
    G4double photonEnergy[] =
    {2.00*eV,2.03*eV,2.06*eV,2.09*eV,2.12*eV,
        2.15*eV,2.18*eV,2.21*eV,2.24*eV,2.27*eV,
        2.30*eV,2.33*eV,2.36*eV,2.39*eV,2.42*eV,
        2.45*eV,2.48*eV,2.51*eV,2.54*eV,2.57*eV,
        2.60*eV,2.63*eV,2.66*eV,2.69*eV,2.72*eV,
        2.75*eV,2.78*eV,2.81*eV,2.84*eV,2.87*eV,
        2.90*eV,2.93*eV,2.96*eV,2.99*eV,3.02*eV,
        3.05*eV,3.08*eV,3.11*eV,3.14*eV,3.17*eV,
        3.20*eV,3.23*eV,3.26*eV,3.29*eV,3.32*eV,
        3.35*eV,3.38*eV,3.41*eV,3.44*eV,3.47*eV};
   
    // Wavelength conversion (nm)
    // {619.9,  610.8,  601.9,  593.2,  584.8,
    //  576.7,  568.7,  561.0,  553.5,  546.2,
    //  539.1,  532.1,  525.4,  518.7,  512.3,
    //  506.1,  499.9,  494.0,  488.1,  482.4,
    //  476.9,  471.4,  466.1,  460.9,  455.8,
    //  450.9,  446.0,  441.2,  436.6,  432.0,
    //  427.5,  423.2,  418.9,  414.7,  410.5,
    //  406.5,  402.5,  398.7,  394.9,  391.1,
    //  387.5,  383.9,  380.3,  376.9,  373.4,
    //  370.1,  366.8,  363.6,  360.4,  357.3}

    const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);


    G4double acrylicPhotonEnergy[] =
    {1.96*eV,2.02*eV,2.08*eV,2.14*eV,2.20*eV,
        2.26*eV,2.32*eV,2.38*eV,2.44*eV,2.50*eV,
	2.56*eV,2.62*eV,2.68*eV,2.74*eV,2.80*eV,
	2.86*eV,2.92*eV,2.98*eV,3.04*eV,3.10*eV,
	3.16*eV,3.22*eV,3.28*eV,3.34*eV,3.40*eV,
	3.46*eV,3.52*eV,3.58*eV,3.64*eV,3.70*eV,
	3.76*eV,3.82*eV,3.88*eV,3.94*eV,4.00*eV,
	4.06*eV,4.12*eV,4.18*eV,4.24*eV,4.30*eV,
	4.36*eV,4.42*eV,4.48*eV,4.54*eV,4.60*eV,
	4.66*eV,4.72*eV,4.78*eV,4.84*eV,4.90*eV,
	4.96*eV,5.02*eV,5.08*eV,5.14*eV,5.20*eV};

    // Wavelength conversion (nm)
    // {632.6,  613.8,  596.1,  579.4,  563.6,
    //  548.6,  534.4,  520.9,  508.1,  495.9,
    //  484.3,  473.2,  462.6,  452.5,  442.8,
    //  433.5,  424.6,  416.1,  407.8,  399.9,
    //  392.4,  385.0,  378.0,  371.2,  364.7,
    //  358.3,  352.2,  346.2,  340.6,  335.1,
    //  329.7,  324.6,  319.5,  314.7,  310.0,
    //  305.4,  300.9,  296.6,  292.4,  288.3,
    //  284.4,  280.5,  276.8,  273.1,  269.5,
    //  266.1,  262.7,  259.4,  256.2,  253.0,
    //  250.0,  247.0,  244.1,  241.2,  238.4}

    const G4int nEntriesAcr = sizeof(acrylicPhotonEnergy)/sizeof(G4double);
    
    //--------------------------------------------------
    // Air
    //--------------------------------------------------
    
    G4double refractiveIndex[] =
    { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
    
    assert(sizeof(refractiveIndex) == sizeof(photonEnergy));
    
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);
    
    fAir->SetMaterialPropertiesTable(mpt);
    
    //--------------------------------------------------
    //  Regular PMMA properties - used everywhere but fiber
    //--------------------------------------------------
    
    G4double refractiveIndexPMMA[] =
    { 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
	1.60, 1.60, 1.60, 1.60, 1.60};
    
    assert(sizeof(refractiveIndexPMMA) == sizeof(acrylicPhotonEnergy));

    G4double absPMMA[] =
    {10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
        5.*m, 5.*m, 5.*m, 5.*m, 5.*m, 1.*m, 1.*m, 1.*m, 1.*m, 1.*m,
        50.*cm, 50.*cm, 50.*cm, 20.*cm, 20.*cm, 20.*cm, 20.*cm, 20.*cm, 20.*cm, 20.*cm,
        20.*cm, 20.*cm, 20.*cm, 20.*cm, 20.*cm, 10.*cm, 7.5*cm, 4.*cm, 1.*cm, 6.*mm,
        3.*mm, 2.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*nm, 1.*nm, 1.*nm, 1.*nm, 1.*nm,
        1.*nm, 1.*nm, 1.*nm, 1.*nm, 1.*nm};
    
    assert(sizeof(absPMMA) == sizeof(acrylicPhotonEnergy));

    // Add entries into properties table
    G4MaterialPropertiesTable* mptPMMA = new G4MaterialPropertiesTable();
    mptPMMA->
    AddProperty("RINDEX",acrylicPhotonEnergy,refractiveIndexPMMA,nEntriesAcr);
    mptPMMA->AddProperty("ABSLENGTH",acrylicPhotonEnergy,absPMMA,nEntriesAcr);

    fPMMA->SetMaterialPropertiesTable(mptPMMA);

    //--------------------------------------------------
    //  PMMA for WLSfibers properties
    //--------------------------------------------------
    
    G4double refractiveIndexWLSfiber[] =
    { 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
        1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60};
    
    assert(sizeof(refractiveIndexWLSfiber) == sizeof(photonEnergy));

    G4double absfiber[] =
    {7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
        7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m};

    assert(sizeof(absfiber) == sizeof(photonEnergy));
  

    G4double absWLSfiber[] =
    {5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,
        5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,
        5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,1.10*m,
        1.10*m, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm,
        1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm};


    assert(sizeof(absWLSfiber) == sizeof(photonEnergy));
    
    G4double emissionFib[] =
    {0.05, 0.06, 0.13, 0.19, 0.28, 0.37, 0.53, 0.64, 1.00, 1.40,
        1.90, 2.20, 2.30, 2.53, 3.10, 4.30, 5.00, 4.60, 3.00, 1.00,
        0.14, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
    
    assert(sizeof(emissionFib) == sizeof(photonEnergy));
    
    
    // Add entries into properties table
    G4MaterialPropertiesTable* mptWLSfiber = new G4MaterialPropertiesTable();
    mptWLSfiber->
    AddProperty("RINDEX",photonEnergy,refractiveIndexWLSfiber,nEntries);
    mptWLSfiber->AddProperty("ABSLENGTH",photonEnergy,absfiber,nEntries);
    mptWLSfiber->AddProperty("WLSABSLENGTH",photonEnergy,absWLSfiber,nEntries);
    mptWLSfiber->AddProperty("WLSCOMPONENT",photonEnergy,emissionFib,nEntries);
    mptWLSfiber->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
    

    fWLSPMMA->SetMaterialPropertiesTable(mptWLSfiber);
    
    //--------------------------------------------------
    //  Polyethylene
    //--------------------------------------------------
    
    G4double refractiveIndexClad1[] =
    { 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
        1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
        1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
        1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
        1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49};
    
    assert(sizeof(refractiveIndexClad1) == sizeof(photonEnergy));
    
    G4double absClad[] =
    {7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
        7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m,
	7.5*m, 7.5*m,7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m, 7.5*m};
    
    assert(sizeof(absClad) == sizeof(photonEnergy));
    
    // Add entries into properties table
    G4MaterialPropertiesTable* mptClad1 = new G4MaterialPropertiesTable();
    mptClad1->AddProperty("RINDEX",photonEnergy,refractiveIndexClad1,nEntries);
    mptClad1->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);
    
    fPethylene->SetMaterialPropertiesTable(mptClad1);
    
    //--------------------------------------------------
    // Fluorinated Polyethylene
    //--------------------------------------------------
    
    G4double refractiveIndexClad2[] =
    { 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
        1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
        1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
        1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
        1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42};
    
    assert(sizeof(refractiveIndexClad2) == sizeof(photonEnergy));
    
    // Add entries into properties table
    G4MaterialPropertiesTable* mptClad2 = new G4MaterialPropertiesTable();
    mptClad2->AddProperty("RINDEX",photonEnergy,refractiveIndexClad2,nEntries);
    mptClad2->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);
    
    fFPethylene->SetMaterialPropertiesTable(mptClad2);
    
    //--------------------------------------------------
    // Silicone
    //--------------------------------------------------
    
    G4double refractiveIndexSilicone[] =
    { 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
        1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
        1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
        1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
        1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46};
    
    assert(sizeof(refractiveIndexSilicone) == sizeof(photonEnergy));
    
    // Add entries into properties table
    G4MaterialPropertiesTable* mptSilicone = new G4MaterialPropertiesTable();
    mptSilicone->
    AddProperty("RINDEX",photonEnergy,refractiveIndexSilicone,nEntries);
    mptSilicone->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);
    
    fSilicone->SetMaterialPropertiesTable(mptSilicone);
    
    //--------------------------------------------------
    //  Polystyrene
    //--------------------------------------------------
    
    G4double refractiveIndexPS[] =
    { 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50};
    
    assert(sizeof(refractiveIndexPS) == sizeof(photonEnergy));
    
    G4double absPS[] =
    {2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,
        2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,
        2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,
        2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,
        2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm,2.*cm};
    
    assert(sizeof(absPS) == sizeof(photonEnergy));
    
    G4double scintilFast[] =
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    
    assert(sizeof(scintilFast) == sizeof(photonEnergy));
    
    // Add entries into properties table
    G4MaterialPropertiesTable* mptPolystyrene = new G4MaterialPropertiesTable();
    mptPolystyrene->AddProperty("RINDEX",photonEnergy,refractiveIndexPS,nEntries);
    mptPolystyrene->AddProperty("ABSLENGTH",photonEnergy,absPS,nEntries);
    mptPolystyrene->
    AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,nEntries);
    mptPolystyrene->AddConstProperty("SCINTILLATIONYIELD",10./keV);
    mptPolystyrene->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptPolystyrene->AddConstProperty("FASTTIMECONSTANT", 10.*ns);
    
    fPolystyrene->SetMaterialPropertiesTable(mptPolystyrene);
    
    // Set the Birks Constant for the Polystyrene scintillator
    
    fPolystyrene->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
    
    
    //--------------------------------------------------
    // TPB doped PS matrix - 2% TPB and 98% polystyrene by weight.
    //--------------------------------------------------
    
    // Add entries into properties table (same as PS)
    G4MaterialPropertiesTable* mptTPBDopedPS = new G4MaterialPropertiesTable();
    mptTPBDopedPS->AddProperty("RINDEX", photonEnergy, refractiveIndexPS, nEntries);
//    mptTPBDopedPS->AddProperty("RINDEX", photonEnergy, refractiveIndexPMMA, nEntries);
    mptTPBDopedPS->AddProperty("ABSLENGTH",photonEnergy,absPS,nEntries);
//    mptTPBDopedPS->AddProperty("ABSLENGTH",photonEnergy,absPMMA,nEntries);
    
    // This property triggers the TPB process
    mptTPBDopedPS->AddConstProperty("TPBCONVERSIONEFFICIENCY", 0.33);
    
    fTPBDopedPS->SetMaterialPropertiesTable(mptTPBDopedPS);


}
