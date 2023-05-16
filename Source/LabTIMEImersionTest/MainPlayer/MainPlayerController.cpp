// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerController.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"
#include "DrawDebugHelpers.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the player "OpenScoreboard" input to show the scoreboard widget
	InputComponent->BindAction("OpenScoreboard", IE_Pressed, 
		this, &AMainPlayerController::RequestOpenScoreBoard);
	InputComponent->BindAction("OpenScoreboard", IE_Released, 
		this, &AMainPlayerController::RequestCloseScoreBoard);

	// Bind the player "Atirar" input to fire raycasts
	check(InputComponent);
	InputComponent->BindAction("Atirar", EInputEvent::IE_Released, this, 
		&AMainPlayerController::AtirarRayCast);
}

void AMainPlayerController::AtirarRayCast()
{
	// Max Distance traveled by the trace
	float RayTraceLenght = 1000.0f;

	// Ponto de Origim do disparo do raycast
	FVector Origin = PlayerCameraManager->GetCameraLocation();

	// Direção do disparo com base na Origem.
	FVector Dir = PlayerCameraManager->GetActorForwardVector();
	
	// Vetor da Tragetória do raycast
	FVector RayTraceLine = Origin + (Dir * RayTraceLenght);

	// Variavel que recebera todos os detalhes da colisao do raio disparado.
	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;

	bool bHitSomething = GetWorld()->LineTraceSingleByChannel(HitResult, 
		Origin, RayTraceLine, ECollisionChannel::ECC_Camera, CollisionParams);

	DrawDebugLine(GetWorld(), Origin, RayTraceLine, 
		FColor::Green, true, 10.0f, (uint8)0, 1.f);
}

void AMainPlayerController::RequestOpenScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(true);
}

void AMainPlayerController::RequestCloseScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(false);
}
