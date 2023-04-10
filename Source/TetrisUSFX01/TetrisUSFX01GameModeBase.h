// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Block.h"
#include "Piece.h"
#include "TimerManager.h"
#include "Containers/Map.h"
#include <string>
#include "TetrisUSFX01GameModeBase.generated.h"


UCLASS()
class TETRISUSFX01_API ATetrisUSFX01GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY();
	FTimerHandle TimerSpawn; 
	FTimerHandle TimerStop;
	float yPos;
	int posicion;
	TMap<FVector, APiece*> infoPiezas;
	UPROPERTY()
		ABlock* SpawnedActor;

	UPROPERTY()
		APiece* NuevaInstanciaPieza;
	UFUNCTION()
		void AparecerPieza();
	UFUNCTION()
		void DetenerSpawn();
protected:
	virtual void BeginPlay() override;

public:
	

	UFUNCTION()
	void DestroyActorFunction();

	

};
