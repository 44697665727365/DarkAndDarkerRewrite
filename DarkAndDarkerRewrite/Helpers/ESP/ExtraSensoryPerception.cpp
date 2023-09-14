#include "pch.h"

void RenderNames(ADCPlayerCharacterBase* adc, ImColor color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	if (!adc)
		return;

	if (!adc->RootComponent)
		return;

	if (!adc->Mesh)
		return;

	if (!adc->PlayerState)
		return;

	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector head_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head)) : adc->RootComponent->RelativeLocation;
	FVector2D head_pos2d, foot_pos2d;

	head_loc.Z += 25.0f;
	foot_loc.Z -= 5.0f;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(head_loc, head_pos2d, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	auto centerTeamNames = ImGui::CalcTextSize(adc->NickNameCached.OriginalNickName.ToString().c_str());
	RenderText({ foot_pos2d.X - (centerTeamNames.x / 2), head_pos2d.Y - 20 }, color, adc->NickNameCached.OriginalNickName.ToString().c_str());
}

void RenderHealthBar(ADCCharacterBase* adc)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	if (!adc->AbilitySystemComponent)
		return;

	if (!adc->AbilitySystemComponent->SpawnedAttributes.Data)
		return;

	UDCAttributeSet* PlayerAttributes = reinterpret_cast<UDCAttributeSet*>(adc->AbilitySystemComponent->SpawnedAttributes[0]);

	float max_health = PlayerAttributes->MaxHealth.CurrentValue;

	ImVec4 color = ImVec4(.2, .96, .32, 1);

	FVector2D max, min;
	auto headOrigin = adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head));
	auto rootOrigin = adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Root));

	headOrigin.Z += 25.f;
	rootOrigin.Z -= 5;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(headOrigin, max, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(rootOrigin, min, false))
		return;

	float flWidth = fabs((max.Y - min.Y) / 4.f);
	float height = min.Y - max.Y;
	height = height + 8;
	float width = height / 2;
	float x = min.X - (width / 2.f);
	float y = max.Y - 4;

	if (PlayerAttributes->Health.CurrentValue <= 75 && PlayerAttributes->Health.CurrentValue > 50)
		color = ImVec4(.96, .77, .25, 1);
	if (PlayerAttributes->Health.CurrentValue < 50)
		color = ImVec4(1, 0, 0, 1);

	auto health_height = (height) * float(PlayerAttributes->Health.CurrentValue / max_health);
	RenderFilledRect({ x - 12, y, 0 }, 3, height, ImVec4(0, 0, 0, .5));
	RenderFilledRect({ x - 12, (y + (height)) - health_height, 0 }, 3, health_height, color);
}

void RenderClass(ADCPlayerCharacterBase* adc, ImColor color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	if (!adc)
		return;

	if (!adc->RootComponent)
		return;

	if (!adc->Mesh)
		return;

	if (!adc->PlayerState)
		return;


	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector head_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head)) : adc->RootComponent->RelativeLocation;


	FVector2D head_pos2d, foot_pos2d;

	head_loc.Z += 25.0f;
	foot_loc.Z -= 5.0f;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(head_loc, head_pos2d, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	auto cname = adc->NickNameCached.StreamingModeNickName;
	auto _name = cname.ToString();

	size_t hash_pos = _name.find('#');
	auto name = _name.substr(0, hash_pos);

	auto centerTeamNames = ImGui::CalcTextSize(name.c_str());
	RenderText({ foot_pos2d.X - (centerTeamNames.x / 2), head_pos2d.Y - 32 }, color, name.c_str());
}

void RenderWeapon(ADCPlayerCharacterBase* adc, ImColor color)
{

} ///TODO

void RenderDistance(ADCPlayerCharacterBase* adc, ImColor color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	if (!adc)
		return;

	if (!adc->RootComponent)
		return;

	if (!adc->Mesh)
		return;

	if (!adc->PlayerState)
		return;

	auto ActorSelf = reinterpret_cast<ADCPlayerCharacterBase*>(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn);

	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector head_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head)) : adc->RootComponent->RelativeLocation;


	FVector2D head_pos2d, foot_pos2d;

	head_loc.Z += 25.0f;
	foot_loc.Z -= 5.0f;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(head_loc, head_pos2d, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	const std::string PlayerDistance = " [" + std::to_string(static_cast<int>(ActorSelf->RootComponent->RelativeLocation.distance(foot_loc)) / 100) + "m]";
	auto Distance = ImGui::CalcTextSize(PlayerDistance.data());
	RenderText({ foot_pos2d.X - (Distance.x / 2), foot_pos2d.Y - 10 }, color, PlayerDistance.data());
}

void RenderSnaplines(ADCPlayerCharacterBase* adc, ImColor color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	if (!adc)
		return;

	if (!adc->RootComponent)
		return;

	if (!adc->Mesh)
		return;

	if (!adc->PlayerState)
		return;

	auto ActorSelf = reinterpret_cast<ADCPlayerCharacterBase*>(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn);

	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector head_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head)) : adc->RootComponent->RelativeLocation;


	FVector2D head_pos2d, foot_pos2d;

	head_loc.Z += 25.0f;
	foot_loc.Z -= 5.0f;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(head_loc, head_pos2d, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	RenderLine(head_pos2d, { ImGui::GetIO().DisplaySize.x / 2, 0 }, color, 1);
}

void RenderPlayerAngles(ADCPlayerCharacterBase* adc, ImColor esp_color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	FVector2D screen[2];
	auto neckOrigin = adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(neck_01));
	auto forward = AnglesToForward(neckOrigin, adc->K2_GetActorRotation(), 90.f);


	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(neckOrigin, screen[0], false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(forward, screen[1], false))
		return;

	RenderLine(screen[0], screen[1], esp_color, 1);
}

void Render3DBox(ADCPlayerCharacterBase* adc, ImColor color, bool rotation)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	static FVector boxRescaling = { 55.f, 5.f, 5.f };

	auto WHeadPos = adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head));
	auto WFeetPos = adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Root));
	WHeadPos.Z += 25.f;
	WFeetPos.Z -= 5.f;

	FVector b1, b2, b3, b4, t1, t2, t3, t4;
	FVector2D b1Out, b2Out, b3Out, b4Out, t1Out, t2Out, t3Out, t4Out;

	b1.Z = b2.Z = b3.Z = b4.Z = WFeetPos.Z - boxRescaling.Z;
	float yaw = rotation ? adc->K2_GetActorRotation().Yaw : 0;

	b1.X = WFeetPos.X + cosf(TORAD(yaw + 45.f)) * boxRescaling.X;
	b1.Y = WFeetPos.Y + sinf(TORAD(yaw + 45.f)) * boxRescaling.X;

	b2.X = WFeetPos.X + cosf(TORAD(yaw + 135.f)) * boxRescaling.X;
	b2.Y = WFeetPos.Y + sinf(TORAD(yaw + 135.f)) * boxRescaling.X;

	b3.X = WFeetPos.X + cosf(TORAD(yaw + 225.f)) * boxRescaling.X;
	b3.Y = WFeetPos.Y + sinf(TORAD(yaw + 225.f)) * boxRescaling.X;

	b4.X = WFeetPos.X + cosf(TORAD(yaw + 315.f)) * boxRescaling.X;
	b4.Y = WFeetPos.Y + sinf(TORAD(yaw + 315.f)) * boxRescaling.X;

	t1 = b1, t2 = b2, t3 = b3, t4 = b4;
	t1.Z = t2.Z = t3.Z = t4.Z = WHeadPos.Z + boxRescaling.Y;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(b1, b1Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(b2, b2Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(b3, b3Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(b4, b4Out, false) ||

		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(t1, t1Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(t2, t2Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(t3, t3Out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(t4, t4Out, false))
		return;




	RenderLine(b1Out, b2Out, color, 1);
	RenderLine(b2Out, b3Out, color, 1);
	RenderLine(b3Out, b4Out, color, 1);
	RenderLine(b4Out, b1Out, color, 1);

	RenderLine(b1Out, t1Out, color, 1);
	RenderLine(b2Out, t2Out, color, 1);
	RenderLine(b3Out, t3Out, color, 1);
	RenderLine(b4Out, t4Out, color, 1);

	RenderLine(t1Out, t2Out, color, 1);
	RenderLine(t2Out, t3Out, color, 1);
	RenderLine(t3Out, t4Out, color, 1);
	RenderLine(t4Out, t1Out, color, 1);
}

void RenderSkeleton(ADCPlayerCharacterBase* adc, PlayerBones bone, PlayerBones bone2, ImColor color)
{
	if (!UGameInstance::Singleton())
		return;

	if (!ULocalPlayer::Singleton()->PlayerController)
		return;

	FVector2D out[2];
	if (!APlayerController::Singleton()->ProjectWorldLocationToScreen(adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(bone)), out[0], true))
		return;
	if (!APlayerController::Singleton()->ProjectWorldLocationToScreen(adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(bone2)), out[1], true))
		return;

	RenderLine(out[0], out[1], color, 1);
}

void RenderPlayerBoxs(ADCPlayerCharacterBase* adc, ImColor color)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector head_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetSocketLocation(adc->Mesh->GetBoneName(Head)) : adc->RootComponent->RelativeLocation;

	FVector2D head_pos2d, foot_pos2d;

	head_loc.Z += 25.0f;
	foot_loc.Z -= 5.0f;

	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(head_loc, head_pos2d, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	float flWidth = fabs((head_pos2d.Y - foot_pos2d.Y) / 4.f);

	switch (iSelectedTeamBox)
	{
	case 0: //None

		break;
	case 1: //2D Box
		RenderRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, color);
		break;
	case 2: //2D Filled
		RenderFilledRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, { color.Value.x, color.Value.y,color.Value.z, 50.f / 255.f });
		RenderRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, color);
		break;
	case 3: //2D Corners
		RenderCornerBox(foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, 1.0f, color);
		break;
	case 4: //3D
		Render3DBox(adc, color, true);
		break;
	}

	switch (iSelectedEnemyBox)
	{
	case 0: //None

		break;
	case 1: //2D Box
		RenderRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, color);
		break;
	case 2: //2D Filled
		RenderFilledRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, { color.Value.x, color.Value.y,color.Value.z, 50.f / 255.f });
		RenderRect({ foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, 0 }, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, color);
		break;
	case 3: //2D Corners
		RenderCornerBox(foot_pos2d.X - flWidth - 6.f, head_pos2d.Y - 4.f, flWidth * 2.f + 12.f, foot_pos2d.Y - head_pos2d.Y + 8.f, 1.0f, color);
		break;
	case 4: //3D
		Render3DBox(adc, color, true);
		break;
	}
}

void RenderStepPath(ADCPlayerCharacterBase* adc, PlayerBones step, PlayerBones step2, ImColor color)
{

}

void RenderRadarActors(FVector baseActorLocation, AActor* targetActor, APlayerController* playerController, APlayerCameraManager* playerCameraManager)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	auto RadarRotation = playerCameraManager->GetCameraRotation();

	bool isVisible = false;

	auto RotationPoint = RotatePoint(targetActor->K2_GetActorLocation(), baseActorLocation, RadarRotation.Y, &isVisible);



	RenderFilledRect({ RotationPoint.X, RotationPoint.Y, 0.0f }, 3, 3, { 255, 255, 255, 255 });
}

void RenderItems(AActor* adc)
{
	if (!UWorld::Singleton()) return;
	if (!adc) return;

	auto Controller = UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController;
	if (!Controller) return;

	FVector location = adc->K2_GetActorLocation();
	FVector2D out;
	if (!Controller->ProjectWorldLocationToScreen(location, out, false))
		return;

	if (adc->IsA(ABP_StaticMeshItemHolder_C::StaticClass()))
	{
		ImColor cItems;
		auto ItemNames = reinterpret_cast<AItemHolderActorBase*>(adc);
		if (!ItemNames)
			return;

		auto interact_base = reinterpret_cast<ADCInteractableActorBase*>(adc);
		if (!interact_base)
			return;

		auto component = interact_base->InteractableTargetComponent;
		if (!component)
			return;

		auto data = component->GetInteractTargetData();
		auto rarity = data.RarityType.TagName.GetName();

		if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Junk"))) { cItems = { 210,180,140, 255 }; }			//Brown
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Poor"))) { cItems = { 180, 180, 180, 255 }; }		//Gray
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Common"))) { cItems = { 255, 255, 255, 255 }; }	//White
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Uncommon"))) { cItems = { 0, 255, 0, 255 }; }		//Green
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Rare"))) { cItems = { 0, 0, 255, 255 }; }			//Blue
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Epic"))) { cItems = { 255, 0, 255, 255 }; }		//Purple
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Legend"))) { cItems = { 255, 255, 0, 255 }; }		//Yellow
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.Unique"))) { cItems = { 0, 255, 255, 255 }; }		//Cyan
		else if (!strcmp(rarity.c_str(), Xors("Type.Item.Rarity.SetPiece"))) { cItems = { 255, 0, 0, 255 }; }		//Red

		auto ParsedNames = ItemNames->ItemId.PrimaryAssetName.GetName();

		ParsedNames = ParsedNames.substr(strlen("id_item_"));
		ParsedNames = ParsedNames.substr(0, ParsedNames.rfind('_'));

		RenderText(out, cItems, ParsedNames.c_str());
	}
}

void RenderMonsters(ADCMonsterBase* adc)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	auto ActorSelf = reinterpret_cast<ADCPlayerCharacterBase*>(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn);

	FVector location = adc->K2_GetActorLocation();
	FVector foot_loc = adc->IsA(ADCPlayerCharacterBase::StaticClass()) ? adc->Mesh->GetBoneLocation(0) : adc->RootComponent->RelativeLocation;
	FVector2D out;
	FVector2D foot_pos2d;
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(location, out, false) ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(foot_loc, foot_pos2d, false))
		return;

	float YOffset = 0;
	if (adc->IsA(ADCMonsterBase::StaticClass()))
	{
		if (!adc->ArtDataMonster)
			return;

		auto ParsedMonsters = adc->GetMonsterId().PrimaryAssetName.GetName();

		ParsedMonsters = ParsedMonsters.substr(strlen("id_monster_"));
		ParsedMonsters = ParsedMonsters.substr(0, ParsedMonsters.rfind('_'));

		UDCAttributeSet* Attributes = reinterpret_cast<UDCAttributeSet*>(adc->AbilitySystemComponent->SpawnedAttributes[0]);
		if (Attributes->Health.CurrentValue > 0)
		{
			auto Monsters = ImGui::CalcTextSize(ParsedMonsters.c_str());
			RenderText({ (float)out.x - (Monsters.x / 2), (float)foot_pos2d.y }, cMonsters, ParsedMonsters.c_str());
			if (bMonsterHealth)
			{
				YOffset += 10;
				const std::string MonsterHealth = "Health: " + std::to_string((int)Attributes->Health.CurrentValue) + "/" + std::to_string((int)Attributes->MaxHealth.CurrentValue);
				auto Health = ImGui::CalcTextSize(MonsterHealth.c_str());
				RenderText({ (float)out.x - (Health.x / 2), (float)foot_pos2d.y + YOffset }, cMonsters, MonsterHealth.c_str());
			}

			if (bMonsterDistance)
			{
				YOffset += 10;
				const std::string MonsterDistance = " [" + std::to_string(static_cast<int>(ActorSelf->RootComponent->RelativeLocation.distance(foot_loc)) / 100) + "m]";
				auto Distance = ImGui::CalcTextSize(MonsterDistance.data());
				RenderText({ (float)out.x - (Distance.x / 2), (float)foot_pos2d.y + YOffset }, cMonsters, MonsterDistance.data());
			}
		}
		else
		{
			auto Corpse = ImGui::CalcTextSize("Monster Corpse");
			RenderText({ (float)out.x - (Corpse.x / 2), (float)foot_pos2d.y + YOffset }, (255, 0, 0, 150), "Corpse");
		}
	}
}

void RenderTraps(AActor* adc)
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	FVector location = adc->K2_GetActorLocation();
	FVector2D out;
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->OwningGameInstance ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(location, out, false))
		return;

	if (adc->IsA(ABP_TrapBase_C::StaticClass()))
	{
		if (!adc)
			return;

		auto ParsedTraps = adc->GetName();

		ParsedTraps = ParsedTraps.substr(strlen("BP_"));
		ParsedTraps = ParsedTraps.substr(0, ParsedTraps.rfind('_'));
		ParsedTraps = ParsedTraps.substr(0, ParsedTraps.rfind('_'));

		RenderText(out, cMonsters, ParsedTraps.c_str());
	}
}

void ESP()
{
	if (!UWorld::Singleton() ||
		!UWorld::Singleton()->PersistentLevel ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn ||
		!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn->RootComponent)
		return;

	auto Levels = UWorld::Singleton()->Levels;

	auto Controller = ULocalPlayer::Singleton()->PlayerController;
	if (!Controller)
		return;

	auto Camera = APlayerController::Singleton()->PlayerCameraManager;
	if (!Camera)
		return;

	auto Pawn = ULocalPlayer::Singleton()->PlayerController->AcknowledgedPawn;
	if (!Pawn)
		return;

	int NearbyPlayers = 0;
	for (auto levelIndex = 0; levelIndex < Levels.Num(); levelIndex++)
	{
		auto level = Levels[levelIndex];

		if (!level)
			continue;

		for (int index = 0; index < level->Actors.Num(); index++)
		{
			auto Actor = reinterpret_cast<ADCPlayerCharacterBase*>(level->Actors[index]);
			auto ActorMonster = reinterpret_cast<ADCMonsterBase*>(level->Actors[index]);
			auto ActorChar = reinterpret_cast<ADCPlayerState*>(Actor->PlayerState);
			auto ActorSelf = reinterpret_cast<ADCPlayerCharacterBase*>(UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->AcknowledgedPawn);

			if (!Actor)
				continue;

			if (!Actor->RootComponent)
				continue;

			FVector location = Actor->K2_GetActorLocation();
			FVector2D out;

			if (Actor->IsA(ADCPlayerCharacterBase::StaticClass()))
			{
				if (!ActorChar)
					continue;

				if (Actor->IsPlayerControlled())
				{
					if (Actor == ActorSelf) //Self Check
						continue;

					NearbyPlayers++;
					if (Actor->IsSameTeam(ActorSelf->GetPartyId()))
					{
						if (bTeamNames)
						{
							RenderNames(Actor, cTeamNames);

							if (bTeamHealth)
							{
								RenderHealthBar(Actor);
							}

							if (bTeamClass)
							{
								RenderClass(Actor, cTeamClass);
							}

							if (bTeamWeapon)
							{

							}

							if (bTeamDistance)
							{
								RenderDistance(Actor, cTeamDistance);
							}

							if (bTeamSnaplines)
							{
								RenderSnaplines(Actor, cTeamSnaplines);
							}

							if (bTeamSkeleton)
							{
								RenderSkeleton(Actor, Head, neck_01, cTeamSkeleton);
								RenderSkeleton(Actor, spine_03, neck_01, cTeamSkeleton);
								RenderSkeleton(Actor, spine_03, spine_02, cTeamSkeleton);
								RenderSkeleton(Actor, spine_01, spine_02, cTeamSkeleton);
								RenderSkeleton(Actor, spine_01, pelvis, cTeamSkeleton);

								RenderSkeleton(Actor, upperarm_l, neck_01, cTeamSkeleton);
								RenderSkeleton(Actor, upperarm_l, lowerarm_l, cTeamSkeleton);
								RenderSkeleton(Actor, lowerarm_l, hand_l, cTeamSkeleton);

								RenderSkeleton(Actor, upperarm_r, neck_01, cTeamSkeleton);
								RenderSkeleton(Actor, upperarm_r, lowerarm_r, cTeamSkeleton);
								RenderSkeleton(Actor, lowerarm_r, hand_r, cTeamSkeleton);

								RenderSkeleton(Actor, thigh_l, pelvis, cTeamSkeleton);
								RenderSkeleton(Actor, calf_l, thigh_l, cTeamSkeleton);
								RenderSkeleton(Actor, calf_l, foot_l, cTeamSkeleton);

								RenderSkeleton(Actor, thigh_r, pelvis, cTeamSkeleton);
								RenderSkeleton(Actor, calf_r, thigh_r, cTeamSkeleton);
								RenderSkeleton(Actor, calf_r, foot_r, cTeamSkeleton);
							}

							if (bTeamViewAngle)
							{
								RenderPlayerAngles(Actor, cTeamViewAngles);
							}

							if (bTeamBoxs)
							{
								RenderPlayerBoxs(Actor, cTeamBoxs);
							}
						}
					}

					else if (!Actor->IsSameTeam(ActorSelf->GetPartyId()))
					{
						if (bEnemyNames)
						{
							RenderNames(Actor, cEnemyNames);

							if (bEnemyHealth)
							{
								RenderHealthBar(Actor);
							}

							if (bEnemyClass)
							{
								RenderClass(Actor, cEnemyClass);
							}

							if (bEnemyWeapon)
							{

							}

							if (bEnemyDistance)
							{
								RenderDistance(Actor, cEnemyDistance);
							}

							if (bEnemySnaplines)
							{
								RenderSnaplines(Actor, cEnemySnaplines);
							}

							if (bEnemySkeleton)
							{
								RenderSkeleton(Actor, Head, neck_01, cEnemySkeleton);
								RenderSkeleton(Actor, spine_03, neck_01, cEnemySkeleton);
								RenderSkeleton(Actor, spine_03, spine_02, cEnemySkeleton);
								RenderSkeleton(Actor, spine_01, spine_02, cEnemySkeleton);
								RenderSkeleton(Actor, spine_01, pelvis, cEnemySkeleton);

								RenderSkeleton(Actor, upperarm_l, neck_01, cEnemySkeleton);
								RenderSkeleton(Actor, upperarm_l, lowerarm_l, cEnemySkeleton);
								RenderSkeleton(Actor, lowerarm_l, hand_l, cEnemySkeleton);

								RenderSkeleton(Actor, upperarm_r, neck_01, cEnemySkeleton);
								RenderSkeleton(Actor, upperarm_r, lowerarm_r, cEnemySkeleton);
								RenderSkeleton(Actor, lowerarm_r, hand_r, cEnemySkeleton);

								RenderSkeleton(Actor, thigh_l, pelvis, cEnemySkeleton);
								RenderSkeleton(Actor, calf_l, thigh_l, cEnemySkeleton);
								RenderSkeleton(Actor, calf_l, foot_l, cEnemySkeleton);

								RenderSkeleton(Actor, thigh_r, pelvis, cEnemySkeleton);
								RenderSkeleton(Actor, calf_r, thigh_r, cEnemySkeleton);
								RenderSkeleton(Actor, calf_r, foot_r, cEnemySkeleton);
							}

							if (bEnemyViewAngle)
							{
								RenderPlayerAngles(Actor, cEnemyViewAngles);
							}

							if (bEnemyBoxs)
							{
								RenderPlayerBoxs(Actor, cEnemyBoxs);
							}
						}
					}
				}
			}

			FVector2D radarResult;
			if (bRadar)
			{
				if (Controller->ProjectWorldLocationToScreen(location, radarResult, false))
				{
					RenderRadarActors(location, Actor, Controller, Camera);
				}
			}

			auto distanceCheck = location.distance(APlayerController::Singleton()->AcknowledgedPawn->K2_GetActorLocation()) / 100;
			if (distanceCheck < iDistanceCheckSlider)
			{
				if (!UWorld::Singleton() ||
					!UWorld::Singleton()->OwningGameInstance ||
					!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0] ||
					!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController ||
					!UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(location, out, false))
					continue;

				if (Actor->IsA(ABP_Chest_Base_C::StaticClass()))
				{
					////Small
					//if (bSimpleChestSmall) {
					//	if (Actor->GetName().find(Xors("BP_SimpleChestSmall")) != std::string::npos) { RenderText(out, cSimpleChestSmall, Xors("[S] Simple Chest")); continue; }
					//}
					//if (bWoodChestSmall) {
					//	if (Actor->GetName().find(Xors("BP_WoodChestSmall")) != std::string::npos) { RenderText(out, cWoodChestSmall, Xors("[S] Wood Chest")); continue; }
					//}
					//if (bBronzeChestSmall) {
					//	if (Actor->GetName().find(Xors("BP_OrnateChestSmall")) != std::string::npos) { RenderText(out, cBronzeChestSmall, Xors("[S] Bronze Chest")); continue; }
					//}

					////Medium
					//if (bSimpleChestMedium) {
					//	if (Actor->GetName().find(Xors("BP_SimpleChestMedium")) != std::string::npos) { RenderText(out, cSimpleChestMedium, Xors("[M] Simple Chest")); continue; }
					//}
					//if (bWoodChestMedium) {
					//	if (Actor->GetName().find(Xors("BP_WoodChestMedium")) != std::string::npos) { RenderText(out, cWoodChestMedium, Xors("[M] Wood Chest")); continue; }
					//}
					//if (bBronzeChestMedium) {
					//	if (Actor->GetName().find(Xors("BP_OrnateChestMedium")) != std::string::npos) { RenderText(out, cBronzeChestMedium, Xors("[M] Bronze Chest")); continue; }
					//}

					////Large
					//if (bSimpleChestLarge) {
					//	if (Actor->GetName().find(Xors("BP_SimpleChestLarge")) != std::string::npos) { RenderText(out, cSimpleChestLarge, Xors("[L] Simple Chest")); continue; }
					//}
					//if (bWoodChestLarge) {
					//	if (Actor->GetName().find(Xors("BP_WoodChestLarge")) != std::string::npos) { RenderText(out, cWoodChestLarge, Xors("[L] Wood Chest")); continue; }
					//}
					//if (bBronzeChestLarge) {
					//	if (Actor->GetName().find(Xors("BP_OrnateChestLarge")) != std::string::npos) { RenderText(out, cBronzeChestLarge, Xors("[L] Bronze Chest")); continue; }
					//}

					//if (bGoldChest) {
					//	if (Actor->GetName().find(Xors("BP_GoldChest")) != std::string::npos) { RenderText(out, cGoldChest, Xors("Gold Chest")); continue; }
					//}
				}
			}

			auto itemDistanceCheck = location.distance(APlayerController::Singleton()->AcknowledgedPawn->K2_GetActorLocation()) / 100;
			if (itemDistanceCheck < iItemDistance)
			{
				if (bRenderItems)
				{
					RenderItems(Actor);
				}
			}

			if (bTraps)
			{
				RenderTraps(Actor);
			}

			if (bMonsters)
			{
				RenderMonsters(ActorMonster);
			}

			if (bMonsterHealth)
			{

			}

			if (bFloorPortal)
			{

			}

			if (bAlter)
			{

			}
		}
	}
	RenderText({ 10, 25 }, { 255, 255, 255,255 }, (std::string(Xors("\t[*]Nearby Players: ")) + std::to_string((int)NearbyPlayers)).c_str());
}
