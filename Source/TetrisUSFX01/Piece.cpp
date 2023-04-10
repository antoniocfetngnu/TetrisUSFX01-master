// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include <vector>


// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //posicion = posicion++;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Pieces Scene");
	RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APiece::SpawnBlocks()
{
    std::vector<std::vector<std::pair<float, float>>> Shapes =
    {
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {10.0, 0.0}},  //Pieza I
        {{0.0, 10.0}, {0.0, 0.0}, {10.0, 0.0}, {20.0, 0.0}},    //Pieza J
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}},  //Pieza L
        {{0.0, 0.0}, {10.0, 0.0}, {0.0, -10.0}, {10.0, -10.0}}, //Pieza Cubo
        {{-10.0, -10.0}, {0.0, -10.0}, {0.0, 0.0}, {10.0, 0.0}},//Pieza S
        {{-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}, {10.0, 0.0}},   //Pieza T
        {{-20.0, 10.0}, {-10.0, 10.0}, {-10.0, 0.0}, {0.0, 0.0}},//Pieza Z
        {{-10.0, 0.0}, {0.0, 10.0}, {10.0, 0.0}, {0.0, -10.0},{0.0,0.0}}, //Pieza Cruz
    };
    tipoPieza = { "Pieza I","Pieza J","Pieza L","Pieza Cubo",
        "Pieza S", "Pieza T","Pieza Z","Pieza Cruz" };

    Index = FMath::RandRange(0, Shapes.size() - 1);
    //UE_LOG(LogTemp, Warning, TEXT("index=%d"), Index);
    //UE_LOG(LogTemp, Warning, TEXT("Pieza=%s"), UTF8_TO_TCHAR(tipoPieza[Index].c_str()));
    nombre = tipoPieza[Index];
    const std::vector<std::pair<float, float>>& YZs = Shapes[Index];
    for (auto&& YZ : YZs)
    {
        FRotator Rotation(0.0, 0.0, 0.0);
        ABlock* B = GetWorld()->SpawnActor<ABlock>(this->GetActorLocation(), Rotation);
        //B->Mesh->SetMaterial(1, Colors[Index]);////
        Blocks.Add(B);
        B->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        B->SetActorRelativeLocation(FVector(0.0, YZ.first, YZ.second));
    }
}

void APiece::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Warning, TEXT("Piezas eliminadas"));
}

void APiece::Dismiss()
{
    Blocks.Empty();
}

