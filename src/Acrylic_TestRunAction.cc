// Make this appear first!
#include "G4Timer.hh"

#include "Acrylic_TestRunAction.hh"
#include "Acrylic_TestAnalysis.hh"
#include "Acrylic_TestRunActionMessenger.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestRunAction::Acrylic_TestRunAction()
 : G4UserRunAction(),
   timer(0)
{
    if (IsMaster()) {
        timer = new G4Timer();
    }
    
    fMessenger = new Acrylic_TestRunActionMessenger(this);
    fileName = "";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Acrylic_TestRunAction::~Acrylic_TestRunAction()
{
  delete timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4int runID = aRun->GetRunID();
    
    if (IsMaster()){
        G4cout << "### Run " << runID << " start." << G4endl;
        timer->Start();
    }
    
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    if(fileName==""){fileName = "output/Acrylic_Test";}
    analysisManager->OpenFile(fileName);
    
    // index 0
    analysisManager->CreateH1("Photons", "Bins: 1=Primaries, 2=Detected, 3=TPB_Inner, 4=TPB_Outer, 5=TPB_All, 6=OtherWLSPhotons", 10, 0., 10.);
    
    // index 1
    analysisManager->CreateH1("PhotonFate", "Bins: 0=Undefined, 1=X-Plate, 2=Y-Plate, 3=Z-Plate, 4=Cell Absorption, 5=TPB Absorption, 8=Trapped", 10, 0., 10.);
    

    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Acrylic_TestRunAction::EndOfRunAction(const G4Run* aRun)
{

    //Acrylic_TestAnalysisManager::GetInstance()->EndOfRun();
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // save histograms
    //
    analysisManager->Write();
    analysisManager->CloseFile();
    
    // complete cleanup
    //
    delete G4AnalysisManager::Instance();

    
    if (IsMaster()){
        timer->Stop();
        G4cout << "*****G4 RUN TIMER*****" << G4endl;
        G4cout << *timer << G4endl;
        
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
