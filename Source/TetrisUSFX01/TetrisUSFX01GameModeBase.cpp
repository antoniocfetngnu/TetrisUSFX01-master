// Copyright Epic Games, Inc. All Rights Reserved.


#include "TetrisUSFX01GameModeBase.h"


void ATetrisUSFX01GameModeBase::BeginPlay()
{

    yPos = 0;
    posicion = 0;
    // Call the parent class version of this function
    Super::BeginPlay();
  
    GetWorldTimerManager().SetTimer(TimerSpawn, this, &ATetrisUSFX01GameModeBase::AparecerPieza, 5.f, true);
    GetWorldTimerManager().SetTimer(TimerStop, this, &ATetrisUSFX01GameModeBase::DetenerSpawn, 30.f, false);

}

void ATetrisUSFX01GameModeBase::DestroyActorFunction()
{
	if (SpawnedActor != nullptr)
   {
      // Displays a red message on the screen for 10 seconds
      GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Actor Block destruido"));
      SpawnedActor->Destroy();
   }
}

void ATetrisUSFX01GameModeBase::AparecerPieza()
{   
    FTransform LugarDeSpawn;
    FVector coordenada;
    coordenada.X = 0.0f;
    coordenada.Y = yPos;
    coordenada.Z = 0.0f;
    LugarDeSpawn.SetLocation(coordenada);
    NuevaInstanciaPieza = GetWorld()->SpawnActor<APiece>(APiece::StaticClass(), LugarDeSpawn);
    NuevaInstanciaPieza->SpawnBlocks();
 

    //UE_LOG(LogTemp, Warning, TEXT("Pieza=%s"), UTF8_TO_TCHAR(NuevaInstanciaPieza->nombre.c_str()));

    yPos = yPos + 80;
    posicion++;
    std::string cadena = std::to_string(posicion);
    std::string  prueba1;

    prueba1= NuevaInstanciaPieza->nombre;
   
    std::string concatStrings = prueba1 +"_" + cadena;
    //UE_LOG(LogTemp, Log, TEXT("Cantidad de elementos Totales=%s"), *NuevaInstanciaPieza->GetName());
    NuevaInstanciaPieza->SetActorLabel(UTF8_TO_TCHAR(concatStrings.c_str()));
    infoPiezas.Add(coordenada, NuevaInstanciaPieza);
    
}
void ATetrisUSFX01GameModeBase::DetenerSpawn() {
    GetWorldTimerManager().ClearTimer(TimerSpawn);
    UE_LOG(LogTemp, Log, TEXT("Cantidad de elementos Totales=%d"), posicion);
    // Recorrer el mapa
    for (auto& Elem : infoPiezas)           
    {
        FVector coord = Elem.Key;
        
        AActor* Objeto = Elem.Value;
        UE_LOG(LogTemp, Log, TEXT(" Nombre del Actor: %s"), *Objeto->GetActorLabel());
        UE_LOG(LogTemp, Log, TEXT("Coordenada X: %f,Coordenada Y: %f,Coordenada Z: %f, Nombre de Actor: %s"), coord.X,coord.Y,coord.Z, *Objeto->GetName());
        
    }
    }
