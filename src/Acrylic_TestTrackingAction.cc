#include "globals.hh"
#include "G4RunManager.hh"

#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4TrackingManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "Acrylic_TestTrackingAction.hh"
#include "Acrylic_TestAnalysis.hh"

void Acrylic_TestTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    if (aTrack->GetParentID()==0) {
        // particle is a primary
        analysisManager->FillH1(0, 1);
    }
    
    
}


void Acrylic_TestTrackingAction::PostUserTrackingAction(const G4Track * aTrack)
{}
