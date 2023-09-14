#include "pch.h"
#include "UnrealEngine.h"

TUObjectArray* ObjObjects = nullptr;
FNamePool* NamePoolData = nullptr;
UFont* DefaultMediumFont;

std::string FNameEntry::String()
{
	if (bIsWide) { return std::string(); }
	return { AnsiName, Len };
}

FNameEntry* FNamePool::GetEntry(FNameEntryHandle handle) const
{
	return reinterpret_cast<FNameEntry*>(Blocks[handle.Block] + 2 * static_cast<uint64_t>(handle.Offset));
}

std::string FName::GetName()
{
	auto entry = NamePoolData->GetEntry(Index);
	auto name = entry->String();
	if (Number > 0)
	{
		name += '_' + std::to_string(Number);
	}
	auto pos = name.rfind('/');
	if (pos != std::string::npos)
	{
		name = name.substr(pos + 1);
	}
	return name;
}

std::string UObject::GetName()
{
	return NamePrivate.GetName();
}

std::string UObject::GetFullName()
{
	std::string name;
	for (auto outer = OuterPrivate; outer; outer = outer->OuterPrivate) { name = outer->GetName() + "." + name; }
	name = ClassPrivate->GetName() + " " + name + this->GetName();
	return name;
}

bool UObject::IsA(void* cmp)
{
	for (auto super = ClassPrivate; super; super = static_cast<UClass*>(super->SuperStruct))
	{
		if (super == cmp)
			return true;
	}
	return false;
}

template<typename Fn>
inline Fn GetVFunction(const void* instance, std::size_t index)
{
	auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(instance));
	return reinterpret_cast<Fn>(vtable[index]);
}

void UObject::ProcessEvent(void* fn, void* parms)
{
	spoof_call(GetVFunction<void(*)(UObject*, void*, void*)>(UWorld::Singleton(), 0x4C), this, fn, parms);
}

std::string UObject::GetObjectName()
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.GetObjectName");

	struct {
		struct UObject* Object;
		struct FString return_value;
	} parms;

	parms.Object = this;

	ProcessEvent(fn, &parms);

	return this->FixName(parms.return_value.ToString());
}

UObject* TUObjectArray::GetObjectPtr(uint32_t id) const
{
	if (id >= NumElements) return nullptr;
	uint64_t chunkIndex = id / 65536;
	if (chunkIndex >= NumChunks) return nullptr;
	auto chunk = Objects[chunkIndex];
	if (!chunk) return nullptr;
	uint32_t withinChunkIndex = id % 65536 * 24;
	auto item = *reinterpret_cast<UObject**>(chunk + withinChunkIndex);
	return item;
}


FVector UKismetMathLibrary::Conv_RotatorToVector(struct FRotator InRot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.Conv_RotatorToVector");
	struct {
		FRotator InRot;
		FVector returnValue;
	} parms;

	parms.InRot = InRot;
	ProcessEvent(fn, &parms);
	return parms.returnValue;
}

float UKismetMathLibrary::GetPI()
{
	static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.GetPI");
	struct {
		float returnValue;
	} parms;

	ProcessEvent(fn, &parms);
	return parms.returnValue;
}

FLinearColor UKismetMathLibrary::Conv_ColorToLinearColor(FColor InColor)
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.Conv_ColorToLinearColor");

	struct {
		FColor InColor;
		FLinearColor returnValue;
	} parms;

	parms.InColor = InColor;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	ProcessEvent(fn, &parms);
	fn->FunctionFlags = flags;

	return parms.returnValue;
}

FRotator UKismetMathLibrary::FindLookAtRotation(FVector Start, FVector Target)
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.FindLookAtRotation");


	struct
	{
		FVector Start;
		FVector Target;
		FRotator returnValue;
	}parms;

	parms.Start = Start;
	parms.Target = Target;

	ProcessEvent(fn, &parms);

	return parms.returnValue;
}

void UKismetSystemLibrary::GetComponentBounds(USceneComponent* Component, FVector& Origin, FVector& BoxExtent, float& SphereRadius)
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.GetComponentBounds");

	struct {
		USceneComponent* Component;
		FVector Origin;
		FVector BoxExtent;
		float SphereRadius;
	} parms;

	parms.Component = Component;

	ProcessEvent(fn, &parms);


	Origin = parms.Origin;
	BoxExtent = parms.BoxExtent;
	SphereRadius = parms.SphereRadius;
}

void UGameplayStatics::GetAllActorsOfClass(UObject* WorldContextObject, AActor* ActorClass, TArray<struct AActor*>& OutActors)
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetAllActorsOfClass");

	struct {
		UObject* WorldContextObject;
		AActor* ActorClass;
		TArray<struct AActor*> OutActors;
	} parms;

	parms.WorldContextObject = WorldContextObject;
	parms.ActorClass = ActorClass;
	parms.OutActors = OutActors;

	ProcessEvent(fn, &parms);


	OutActors = parms.OutActors;
}

FString UGameplayStatics::GetCurrentLevelName(UObject* WorldContextObject, bool bRemovePrefixString)
{
	static UFunction* fn;
	if (fn == nullptr)
		fn = (UFunction*)UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetCurrentLevelName");

	struct {
		UObject* WorldContextObject;
		bool bRemovePrefixString;
		FString returnValue;
	} parms;

	parms.WorldContextObject = WorldContextObject;
	parms.bRemovePrefixString = bRemovePrefixString;

	ProcessEvent(fn, &parms);

	return parms.returnValue;
}
