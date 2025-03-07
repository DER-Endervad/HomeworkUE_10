// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "LevelActors/Pickup/LMAHealthPickup.h"
#include "Components/LMAHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/LMADefaultCharacter.h"

ALMAHealthPickup::ALMAHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereComponent);
	StaticMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	StaticMesh->SetRelativeLocation(FVector(14.0f, 0.0f, -35.0f));
}

void ALMAHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DeletingTimerHandle;
	GetWorldTimerManager().SetTimer(DeletingTimerHandle, this, &ALMAHealthPickup::DeletingPickup, DeletingTime);
}

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Character = Cast<ALMADefaultCharacter>(OtherActor);
	if (!IsValid(Character)) {
		return;
	}
	if (GivePickup(Character))
	{
		PickupWasTaken();
	}
}

void ALMAHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ALMAHealthPickup::GivePickup(ALMADefaultCharacter* Character)
{
	const auto HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent)
		return false;

	return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::PickupWasTaken()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	//FTimerHandle RespawnTimerHandle;
	//GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

//void ALMAHealthPickup::RespawnPickup()
//{
//	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
//	GetRootComponent()->SetVisibility(true, true);
//}

void ALMAHealthPickup::DeletingPickup() {
	StaticMesh->DestroyComponent();
	SphereComponent->DestroyComponent();
}

