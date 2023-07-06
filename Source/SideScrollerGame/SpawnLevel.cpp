#include "SpawnLevel.h"
#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpawnLevel::ASpawnLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnLevel::BeginPlay()
{
	Super::BeginPlay();

	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);
	
}

// Called every frame
void ASpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ASpawnLevel::SpawnLevel(bool isFirst)
{

	SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	SpawnRotation = FRotator(0, 90, 0);

	if (!isFirst)
	{
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(1, 5);
	ABaseLevel* NewLevel = nullptr;

	if (RandomLevel == 1)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1,
			SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 2)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2,
			SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 3)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3,
			SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 4)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4,
			SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 5)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5,
			SpawnLocation, SpawnRotation, SpawnInfo);
	}

	if (NewLevel)
	{
		if (NewLevel->GetTrigger())
		{
			NewLevel->GetTrigger()->OnComponentBeginOverlap.
				AddDynamic(this, &ASpawnLevel::OnOverlapBegin);
		}
	}

	LevelList.Add(NewLevel);
	if (LevelList.Num() > 3)
	{
		LevelList.RemoveAt(0);
	}
}

void ASpawnLevel::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	SpawnLevel(false);
}
