// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellBox.h"
#include "TankPawn.h"

// Sets default values
AShellBox::AShellBox()
{
    USceneComponent* ShellSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = ShellSceneComponent;

	ShellBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellBoxMesh"));
	ShellBoxMesh->SetupAttachment(ShellSceneComponent);

	//subscribe meshoverlabegin
	ShellBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AShellBox::OnMeshOverlapBegin);

	//setting collision 
	ShellBoxMesh->SetCollisionProfileName(FName("OverlapAll"));
	ShellBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//event crossing works
	ShellBoxMesh->SetGenerateOverlapEvents(true);

}

void AShellBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn) {
		TankPawn->SetAmount(Amount);
		Destroy();
	}
}

