// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "TankPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
    USceneComponent* AmmoSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = AmmoSceneComponent;

    //3-d model
    AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
    AmmoMesh->SetupAttachment(AmmoSceneComponent);

    //subscribe meshoverlabegin
    AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
    
    //setting collision 
    AmmoMesh->SetCollisionProfileName(FName("OverlapAll"));
    AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //event crossing works
    AmmoMesh->SetGenerateOverlapEvents(true);


}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
    if (TankPawn)
    {
        TankPawn->SetupCannon(CannonClass);
        Destroy();
    }
}

