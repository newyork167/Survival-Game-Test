// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGame.h"
#include "SHUD.h"
#include "SCharacter.h"
#include "SUsableActor.h"
#include "SPlayerController.h"


ASHUD::ASHUD(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	/* You can use the FObjectFinder in C++ to reference content directly in code. Although it's advisable to avoid this and instead assign content through Blueprint child classes. */
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDCenterDotObj(TEXT("/Game/UI/HUD/T_CenterDot_M.T_CenterDot_M"));
	CenterDotIcon = UCanvas::MakeIcon(HUDCenterDotObj.Object);
}


void ASHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCenterDot();

	//DrawRandom();
}


void ASHUD::DrawCenterDot()
{
	float CenterX = Canvas->ClipX / 2;
	float CenterY = Canvas->ClipY / 2;
	float CenterDotScale = 0.07f;

	ASCharacter* Pawn = Cast<ASCharacter>(GetOwningPawn());
	if (Pawn && Pawn->IsAlive())
	{
		// Boost size when hovering over a usable object.
		ASUsableActor* Usable = Pawn->GetUsableInView();
		if (Usable)
		{
			CenterDotScale *= 1.5f;
		}

		Canvas->SetDrawColor(255, 255, 255, 255);
		Canvas->DrawIcon(CenterDotIcon,
			CenterX - CenterDotIcon.UL*CenterDotScale / 2.0f,
			CenterY - CenterDotIcon.VL*CenterDotScale / 2.0f, CenterDotScale);
	}
}

void ASHUD::DrawRandom()
{
	float CenterX = Canvas->ClipX / 2;
	float CenterY = Canvas->ClipY / 2;
	float CenterDotScale = 0.07f;

	FVector2D line_x, line_y;
	float low = 0, high_x = Canvas->ClipX, high_y = Canvas->ClipY, x_factor = 0, y_factor = 0;

	for (int i = 0; i < 10; i++) {
		int flip_axis_x = rand() % 2, flip_axis_y = rand() % 2;
		x_factor = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high_x - low))));
		y_factor = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high_x - low))));

		if (flip_axis_x) {
			x_factor = -x_factor;
		}
		if (flip_axis_y) {
			y_factor = -y_factor;
		}

		line_x = FVector2D(CenterX + x_factor, CenterY + y_factor);

		flip_axis_x = rand() % 2, flip_axis_y = rand() % 2;
		x_factor = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high_x - low))));
		y_factor = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high_x - low))));

		if (flip_axis_x) {
			x_factor = -x_factor;
		}
		if (flip_axis_y) {
			y_factor = -y_factor;
		}

		line_y = FVector2D(CenterX + x_factor, CenterY + y_factor);

		ASCharacter* Pawn = Cast<ASCharacter>(GetOwningPawn());
		if (Pawn && Pawn->IsAlive())
		{
			// Boost size when hovering over a usable object.
			ASUsableActor* Usable = Pawn->GetUsableInView();
			if (Usable)
			{
				CenterDotScale *= 1.5f;
			}

			Canvas->SetDrawColor(255, 0, 0, 0);
			Canvas->K2_DrawLine(line_x, line_y);
		}
	}
}



void ASHUD::OnStateChanged_Implementation(EHUDState NewState)
{
	CurrentState = NewState;
}


EHUDState ASHUD::GetCurrentState()
{
	return CurrentState;
}
