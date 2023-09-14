#pragma once

void RenderNames(ADCCharacterBase* adc, ImColor color);
void RenderHealthBar(ADCCharacterBase* adc);
void RenderClass(ADCCharacterBase* adc, ImColor color);
void RenderWeapon(ADCCharacterBase* adc, ImColor color);
void RenderDistance(ADCCharacterBase* adc, ImColor color);
void RenderSnaplines(ADCCharacterBase* adc, ImColor color);
void RenderPlayerAngles(ADCCharacterBase* adc, ImColor esp_color);
void Render3DBox(ADCCharacterBase* adc, ImColor color, bool rotation);
void RenderSkeleton(ADCCharacterBase* adc, PlayerBones bone, PlayerBones bone2, ImColor color);
void RenderPlayerBoxs(ADCCharacterBase* adc, ImColor color);
void RenderStepPath(ADCCharacterBase* adc, PlayerBones step, PlayerBones step2, ImColor color);
void RenderItems(AActor* adc);
void RenderMonsters(ADCMonsterBase* adc);
void RenderTraps(AActor* adc);
void ESP();