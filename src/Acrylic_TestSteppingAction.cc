#include "Acrylic_TestSteppingAction.hh"

#include "Acrylic_TestAnalysis.hh"
#include "Acrylic_TestTrackInformation.hh"


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
    
    else if( (thePrePVname == "CellSide" || thePrePVname == "TPBInterface") && thePostPVname == "expHall") {
        
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        
        G4ThreeVector theGlobalPoint = thePostPoint->GetPosition();
        
        G4bool valid;
        //  Use the new method for Exit Normal in global coordinates,
        //    which provides the normal more reliably.
        
        // ID of Navigator which limits step
        
        G4int hNavId = G4ParallelWorldProcess::GetHypNavigatorID();
        std::vector<G4Navigator*>::iterator iNav =
        G4TransportationManager::GetTransportationManager()->
        GetActiveNavigatorsIterator();
        G4ThreeVector theGlobalNormal =
        (iNav[hNavId])->GetGlobalExitNormal(theGlobalPoint,&valid);
        
        if (!valid) {
            G4ExceptionDescription ed;
            ed << " NedmOpTPB/PostStepDoIt(): "
            << " The Navigator reports that it returned an invalid normal"
            << G4endl;
            G4Exception("NedmOpTPB::PostStepDoIt", "NedmOpTPB",
                        EventMustBeAborted,ed,
                        "Invalid Surface Normal - Geometry must return valid surface normal");
        }
        
        G4double ReflectionCheck;
        ReflectionCheck =thePrePoint->GetMomentumDirection()*theGlobalNormal + thePostPoint->GetMomentumDirection()*theGlobalNormal;
        
        if (ReflectionCheck>1.0e-12) {
            
            Acrylic_TestTrackInformation* trackInfo = (Acrylic_TestTrackInformation*)aStep->GetTrack()->GetUserInformation();
            
            
            if (theGlobalNormal == G4ThreeVector(1,0,0) || theGlobalNormal == G4ThreeVector(-1,0,0)) {
                //G4cout << "***X-Plate Exit***" << G4endl;
                //G4cout << "Position: " << thePostPoint->GetPosition() << G4endl;
                trackInfo->SetStatus(1);
            }
            else if (theGlobalNormal == G4ThreeVector(0,1,0) || theGlobalNormal == G4ThreeVector(0,-1,0)) {
                //G4cout << "***Y-Plate Exit***" << G4endl;
                //G4cout << "Position: " << thePostPoint->GetPosition() << G4endl;
                trackInfo->SetStatus(2);
            }
            else if (theGlobalNormal == G4ThreeVector(0,0,1) || theGlobalNormal == G4ThreeVector(0,0,-1)) {
                //G4cout << "***Z-Plate Exit***" << G4endl;
                //G4cout << "Position: " << thePostPoint->GetPosition() << G4endl;
                trackInfo->SetStatus(3);
            }
            
            
            /*
             G4cout << "***GLobal Normal for Plate Exit***" << theGlobalNormal << G4endl;
             G4cout << "Position: " << thePostPoint->GetPosition() << G4endl;
             G4cout << "PreStepMomDir: " <<  thePrePoint->GetMomentumDirection() << G4endl;
             G4cout << "PostStepMomDir: " <<  thePostPoint->GetMomentumDirection() << G4endl;
             G4cout << "Step Process: " << thePostPoint->GetProcessDefinedStep()->GetProcessName() << G4endl;
             G4cout << "Exit Trigger Attempt: " << thePrePoint->GetMomentumDirection()*theGlobalNormal + thePostPoint->GetMomentumDirection()*theGlobalNormal << G4endl;
             G4cout << "TrackStatus: " << aStep->GetTrack()->GetTrackStatus() << G4endl;
             */
        }
        
        
        
        
    }
    
    else if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption")
    {
        
        Acrylic_TestTrackInformation* trackInfo = (Acrylic_TestTrackInformation*)aStep->GetTrack()->GetUserInformation();
        
        
        if( thePrePVname == "CellSide" && thePostPVname == "CellSide")
        {
            //G4cout << "*****Absorption In Cell*****" << G4endl;
            trackInfo->SetStatus(4);
        }
        
        if( thePrePVname == "TPBInterface" && thePostPVname == "TPBInterface")
        {
            //G4cout << "*****Absorption In TPBInterface*****" << G4endl;
            trackInfo->SetStatus(5);
            
        }
        
        
    }

    
}

