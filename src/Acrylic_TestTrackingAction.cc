#include "globals.hh"
#include "G4RunManager.hh"

#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4TrackingManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "Acrylic_TestTrackingAction.hh"
#include "Acrylic_TestAnalysis.hh"
#include "Acrylic_TestTrackInformation.hh"

void Acrylic_TestTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    Acrylic_TestTrackInformation* trackInfo = new Acrylic_TestTrackInformation();
    
    fpTrackingManager->SetUserTrackInformation(trackInfo);
    

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    if (aTrack->GetParentID()==0) {
        // particle is a primary
        analysisManager->FillH1(0, 1);
    }
    
    else{
        if (aTrack->GetCreatorProcess()->GetProcessName() == "OpWLS") {
            if (aTrack->GetOriginTouchable()->GetVolume()->GetName()=="TPBInterface") {
                analysisManager->FillH1(0, 3);
                analysisManager->FillH1(0, 5);
            }
            else if (aTrack->GetOriginTouchable()->GetVolume()->GetName()=="TPBInterface_outer")
            {
                analysisManager->FillH1(0, 4);
                analysisManager->FillH1(0, 5);
            }
            else
            {
                analysisManager->FillH1(0, 6);
            }
            
        }
        else{
            G4cout << "Process Name = " << aTrack->GetCreatorProcess()->GetProcessName() << G4endl;
        }
    }
    
    
}


void Acrylic_TestTrackingAction::PostUserTrackingAction(const G4Track * aTrack)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    Acrylic_TestTrackInformation* trackInfo = (Acrylic_TestTrackInformation*)aTrack->GetUserInformation();
    
    G4int status = trackInfo->GetStatus();
    
    analysisManager->FillH1(1, status);
    
    if (status == 1 || status ==3)
    {
        analysisManager->FillH1(1, 8);
    }
}
