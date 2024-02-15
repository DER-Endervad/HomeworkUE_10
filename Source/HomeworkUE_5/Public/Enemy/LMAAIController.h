// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LMAAIController.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORKUE_5_API ALMAAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
