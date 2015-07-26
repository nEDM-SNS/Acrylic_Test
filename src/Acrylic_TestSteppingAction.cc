#include "Acrylic_TestSteppingAction.hh"

#include "Acrylic_TestAnalysis.hh"

#include "G4Step.hh"
#include "G4StepStatus.hh"
#include "G4VProcess.hh"

#include "G4ParallelWorldProcess.hh"
#include "G4TransportationManager.hh"



void Acrylic_TestSteppingAction::UserSteppingAction(const G4Step* aStep)
{
    
    
    // Kill tracks at first step for analyzing input
#if 0
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    return;
#endif
    
    
    G4StepPoint* thePrePoint  = aStep->GetPreStepPoint();
    G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
    
    G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
    G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
    
    G4String thePrePVname  = " ";
    G4String thePostPVname = " ";
    
    if (thePostPV) {
        thePrePVname  = thePrePV->GetName();
        thePostPVname = thePostPV->GetName();
    }
    
    if (thePostPVname=="photDet")
    {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        
        analysisManager->FillH1(0, 2);
        
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
        return;
        
    }
    
}

