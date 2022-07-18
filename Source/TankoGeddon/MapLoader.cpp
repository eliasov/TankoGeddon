#include "MapLoader.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"


AMapLoader::AMapLoader()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AvtivatedLights"));
	ActivatedLight->SetupAttachment(SceneComp);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("DeavtivatedLights"));
	DeactivatedLight->SetupAttachment(SceneComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMapLoader::OnTriggerOverlapBegin);
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	bIsActivated = NewIsActivated;
	SetActivatedLight();

}

void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActivatedLight();
}

void AMapLoader::SetActivatedLight()
{
	ActivatedLight->SetHiddenInGame(!bIsActivated);
	DeactivatedLight->SetHiddenInGame(bIsActivated);
}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated)
	{
		return;
	}
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}

