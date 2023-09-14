#pragma once

enum PlayerBones {
    Root = 0,
    pelvis = 1,
    spine_01 = 2,
    spine_02 = 3,
    spine_03 = 4,
    clavicle_l = 5,
    upperarm_l = 6,
    lowerarm_l = 7,
    hand_l = 8,
    thumb_01_l = 9,
    thumb_02_l = 10,
    thumb_03_l = 11,
    index_01_l = 12,
    index_02_l = 13,
    index_03_l = 14,
    middle_01_l = 15,
    middle_02_l = 16,
    middle_03_l = 17,
    ring_01_l = 18,
    ring_02_l = 19,
    ring_03_l = 20,
    pinky_01_l = 21,
    pinky_02_l = 22,
    pinky_03_l = 23,
    fk_weapon_l = 24,
    shield_l = 25,
    lowerarm_twist_01_l = 26,
    upperarm_twist_01_l = 27,
    neck_01 = 28,
    Head = 29,
    eyelid_l = 30,
    eyelid_r = 31,
    clavicle_r = 32,
    upperarm_r = 33,
    lowerarm_r = 34,
    lowerarm_twist_01_r = 35,
    shield_r = 36,
    hand_r = 37,
    pinky_01_r = 38,
    pinky_02_r = 39,
    pinky_03_r = 40,
    ring_01_r = 41,
    ring_02_r = 42,
    ring_03_r = 43,
    middle_01_r = 44,
    middle_02_r = 45,
    middle_03_r = 46,
    index_01_r = 47,
    index_02_r = 48,
    index_03_r = 49,
    thumb_01_r = 50,
    thumb_02_r = 51,
    thumb_03_r = 52,
    fk_weapon_r = 53,
    upperarm_twist_01_r = 54,
    thigh_l = 55,
    calf_l = 56,
    foot_l = 57,
    ball_l = 58,
    calf_twist_01_l = 59,
    thigh_twist_01_l = 60,
    thigh_r = 61,
    calf_r = 62,
    foot_r = 63,
    ball_r = 64,
    calf_twist_01_r = 65,
    thigh_twist_01_r = 66,
    ik_foot_root = 67,
    ik_foot_l = 68,
    ik_foot_r = 69,
    ik_hand_root = 70,
    ik_hand_gun = 71,
    ik_hand_l = 72,
    weapon_l = 73,
    ik_hand_r = 74,
    weapon_r = 75,
    camera_root = 76,
    camera_rot_root = 77,
    Camera = 78
};

enum eViewModeIndex {
    VMI_BrushWireframe,
    VMI_Wireframe, //Fullbright
    VMI_Unlit,
    VMI_Lit, //Default
    VMI_Lit_DetailLighting,
    VMI_LightingOnly,
    VMI_LightComplexity,
    VMI_ShaderComplexity,
    VMI_LightmapDensity,
    VMI_LitLightmapDensity,
    VMI_ReflectionOverride,
    VMI_VisualizeBuffer,
    VMI_StationaryLightOverlap,
    VMI_CollisionPawn,
    VMI_CollisionVisibility,
    VMI_LODColoration,
    VMI_QuadOverdraw,
    VMI_PrimitiveDistanceAccuracy,
    VMI_MeshUVDensityAccuracy,
    VMI_ShaderComplexityWithQuadOverdraw,
    VMI_HLODColoration,
    VMI_GroupLODColoration,
    VMI_MaterialTextureScaleAccuracy,
    VMI_RequiredTextureResolution,
    VMI_PathTracing,
    VMI_RayTracingDebug,
    VMI_VisualizeNanite,
    VMI_VirtualTexturePendingMips,
    VMI_VisualizeLumen,
    VMI_VisualizeVirtualShadowMap,
    VMI_VisualizeGPUSkinCache,
    VMI_Max,
    VMI_Unknown
};


#pragma region Misc
struct FNickname
{
    struct FString OriginalNickName;  // 0x0 (0x0)
    struct FString StreamingModeNickName;  // 0x10 (0x10)
};

struct FAccountDataReplication
{
    struct FString AccountId;  // 0x0 (0x0)
    struct FNickname Nickname;  // 0x10 (0x10)
    struct FString PlayerCharacterId;  // 0x38 (0x38)
    struct FString PartyId;  // 0x48 (0x48)
    struct FString CharacterId;  // 0x58 (0x58)
    int32_t Gender;  // 0x68 (0x68)
    int32_t Level;  // 0x6C (0x6C)
    bool bInit;  // 0x70 (0x70)
    bool bExit;  // 0x71 (0x71)
    bool bLogin;  // 0x72 (0x72)
    bool bAlive;  // 0x73 (0x73)
    bool bEscape;  // 0x74 (0x74)
    bool bDown;  // 0x75 (0x75)
};

struct FMinimalViewInfo
{
    struct FVector Location;  // 0x0 (0x0)
    struct FRotator Rotation;  // 0x18 (0x18)
    float FOV;  // 0x30 (0x30)
};

struct FCameraCacheEntry
{
    char pad0[0x10];
    struct FMinimalViewInfo POV;  // 0x10 (0x10)
};

struct FKey
{
    struct FName KeyName;  // 0x0 (0x0)
    char pad_8[16];  // 0x8 (0x8)
};

struct FGameplayAttributeData
{
    char pad8[0x8];  // 0x0 (0x0)
    float BaseValue;  // 0x8 (0x8)
    float CurrentValue;  // 0xC (0xC)
};

struct UDCAttributeSet
{
    char pad648[0x648];
    struct FGameplayAttributeData Health;  // 0x648 (0x648)
    struct FGameplayAttributeData MaxHealth;  // 0x658 (0x658)
};

struct UAbilitySystemComponent
{
    char pad11f0[0x11F0];
    struct TArray<struct UAttributeSet*> SpawnedAttributes;  // 0x11F0 (0x11F0)
};

struct FPrimaryAssetType
{
    struct FName Name;  // 0x0 (0x0)
};

struct UDCDataAssetBase
{
    char pad0[0x30];
    struct FPrimaryAssetType AssetType;  // 0x30 (0x30)
};

struct FGameplayTag
{
    struct FName TagName;  // 0x0 (0x0)
};

struct FPrimaryAssetId
{
    struct FPrimaryAssetType PrimaryAssetType;  // 0x0 (0x0)
    struct FName PrimaryAssetName;  // 0x8 (0x8)
};

struct ITextData
{
    FString string;
};

struct FText
{
    ITextData TextData;

    uint32_t Flags;
};

struct FDesignDataItem
{
    struct FGameplayTag IdTag;  // 0x0 (0x0)
    struct FPrimaryAssetId OriginId;  // 0x8 (0x8)
    struct FText Name;  // 0x18 (0x18)
    struct FText FlavorText;  // 0x30 (0x30)
    struct FGameplayTag SlotType;  // 0x48 (0x48)
    struct FGameplayTag HandType;  // 0x50 (0x50)
    struct TArray<struct FGameplayTag> WeaponTypes;  // 0x58 (0x58)
    struct FGameplayTag ArmorType;  // 0x68 (0x68)
    struct FGameplayTag UtilityType;  // 0x70 (0x70)
    struct FGameplayTag AccessoryType;  // 0x78 (0x78)
    struct FGameplayTag MiscType;  // 0x80 (0x80)
    struct FGameplayTag RarityType;  // 0x88 (0x88)
};

struct FItemData
{
    int64_t ItemUniqueId;  // 0x0 (0x0)
    struct FPrimaryAssetId ItemId;  // 0x8 (0x8)
    int32_t InventoryId;  // 0x18 (0x18)
    int32_t SlotId;  // 0x1C (0x1C)
    int32_t ItemCount;  // 0x20 (0x20)
    int32_t ItemAmmoCount;  // 0x24 (0x24)
    int32_t ItemContentsCount;  // 0x28 (0x28)
};

struct UArtDataItem
{
    char pad0[0x30];
    struct FPrimaryAssetType AssetType;  // 0x30 (0x30)
};
#pragma endregion

#pragma region Engine
struct USceneComponent
{
    char pad128[0x128];
    struct FVector RelativeLocation; // 0x128;
    struct FRotator RelativeRotation; // 0x140;
    struct FVector RelativeScale3D; //0x158;
    struct FVector ComponentVelocity; //0x170;;

};

struct USkeletalMeshComponent : UObject
{
    char pad28[0x550];
    struct USkeletalMesh* SkeletalMesh; // 0x578

    FVector GetBoneLocation(int32_t BoneIndex);
    int32_t GetBoneIndex(struct FName BoneName); // Function Engine.SkinnedMeshComponent.GetBoneIndex
    struct FName GetBoneName(int32_t BoneIndex); // Function Engine.SkinnedMeshComponent.GetBoneName
    struct FVector GetSocketLocation(struct FName InSocketName); // Function Engine.SceneComponent.GetSocketLocation

};

struct UWorld : UObject
{
    char pad28[0x8];
    struct ULevel* PersistentLevel;  // 0x30 (0x30)
    char pad30[0x120];
    struct AGameStateBase* GameState;  // 0x158 (0x158)
    char pad158[0x10];
    struct TArray<struct ULevel*> Levels;  // 0x170 (0x170)
    char pad170[0x38];
    struct UGameInstance* OwningGameInstance;  // 0x1B8 (0x1B8)

    static UWorld* Singleton()
    {
        static uint64_t gworld_ptr = 0;
        if (!gworld_ptr)
        {
            auto gworld = signature("48 8B 05 ? ? ? ? EB 05").instruction(3).add(7);
            gworld_ptr = gworld.GetPointer();
        }
        return (*(UWorld**)(gworld_ptr));
    }
};
#pragma endregion

struct ADCGameStateBase
{
    char pad2e0[0x110];
    struct TArray<struct FAccountDataReplication> AccountDataReplicationArray;  // 0x3F0 (0x3F0)
};

struct UGameInstance
{
    char pad38[0x38];
    struct TArray<struct ULocalPlayer*> LocalPlayers; // 0x38

    static UGameInstance* Singleton()
    {
        return UWorld::Singleton()->OwningGameInstance;
    }
};

struct UGameViewportClient
{
    char pad0[0xB0];
    int32_t ViewModeIndex; //0xB0
};

struct ULocalPlayer
{
    char pad[0x30];
    struct APlayerController* PlayerController; // 0x30
    char pad30[0x40];
    struct UGameViewportClient* ViewportClient;  // 0x78 (0x78)

    static ULocalPlayer* Singleton()
    {
        return UWorld::Singleton()->OwningGameInstance->LocalPlayers[0];
    }
};

struct APlayerController : UObject //UObject Size 0x28
{
    char pad28[0x310];
    struct APawn* AcknowledgedPawn;  // 0x338 (0x338)

    char pad338[0x8];
    struct APlayerCameraManager* PlayerCameraManager;  // 0x348 (0x348)


    void SetControlRotation(struct FRotator& NewRotation); // Function Engine.Controller.SetControlRotation
    bool LineOfSightTo(struct AActor* Other, struct FVector ViewPoint, bool bAlternateChecks); // Function Engine.Controller.LineOfSightTo
    bool IsInputKeyDown(struct FKey Key); // Function Engine.PlayerController.IsInputKeyDown

    bool ProjectWorldLocationToScreen(struct FVector WorldLocation, struct FVector2D& ScreenLocation, bool bPlayerViewportRelative); // Function Engine.PlayerController.ProjectWorldLocationToScreen

    static APlayerController* Singleton()
    {
        return UWorld::Singleton()->OwningGameInstance->LocalPlayers[0]->PlayerController;
    }
};

struct AController : UObject
{

};

struct APlayerCameraManager : UObject
{
    char pad290[0x22B0];
    struct FCameraCacheEntry CameraCachePrivate;  // 0x22B0 (0x22B0)

    float GetFOVAngle(); // Function Engine.PlayerCameraManager.GetFOVAngle
    struct FRotator GetCameraRotation(); // Function Engine.PlayerCameraManager.GetCameraRotation
    struct FVector GetCameraLocation(); // Function Engine.PlayerCameraManager.GetCameraLocation
};

struct AActor : UObject
{
    char pad28[0x170];
    struct USceneComponent* RootComponent;  // 0x198 (0x198)
    char pad198[0xF0];

    struct FRotator K2_GetActorRotation(); // Function Engine.Actor.K2_GetActorRotation
    struct FVector K2_GetActorLocation(); // Function Engine.Actor.K2_GetActorLocation
    struct FVector GetVelocity(); // Function Engine.Actor.GetVelocity
    void GetActorBounds(bool bOnlyCollidingComponents, struct FVector& Origin, struct FVector& BoxExtent, bool bIncludeFromChildActors); // Function Engine.Actor.GetActorBounds

};

struct ULevel //DONT INHERITE STAYS SAME
{
    char pad_88[0xA8];
    struct TArray<struct AActor*> Actors;  // 0x28 (0x28)

    static ULevel* Singleton()
    {
        auto world = UWorld::Singleton();
        if (!world)
            return nullptr;
        return world->PersistentLevel;
    }
};

struct APawn : AActor //AActor size 290 APawn 318
{
    char pad290[0x20];
    struct APlayerState* PlayerState;  // 0x2B0 (0x2B0)
    char pad2b0[0x60];

    bool IsPlayerControlled(); // Function Engine.Pawn.IsPlayerControlled
};


struct APlayerState : UObject //Playerstate size 3A8
{

    struct FString GetPlayerName(); // Function Engine.PlayerState.GetPlayerName
};

struct ACharacter : APawn //APawn size 318
{
    struct USkeletalMeshComponent* Mesh;  // 0x318 (0x318)
    char pad0[0x300];
};

struct UKismetStringLibrary : UObject
{

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class Engine.KismetStringLibrary");
        return pStaticClass;
    }
};

struct ADCCharacterBase : ACharacter//0x620
{
    char pad620[0x90];
    struct UAbilitySystemComponent* AbilitySystemComponent;  // 0x6B0 (0x6B0);
    char pad6b0[0x108];
    struct FNickname NickNameCached;  // 0x7C0 (0x7C0)
    char pad7c0[0xC8];

    bool IsSameTeam(struct FString PartyId); // Function DungeonCrawler.DCCharacterBase.IsSameTeam
    struct FString GetPartyId(); // Function DungeonCrawler.DCCharacterBase.GetPartyId


    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.DCCharacterBase");
        return pStaticClass;
    }
};

struct ADCPlayerCharacterBase : ADCCharacterBase
{
    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.DCPlayerCharacterBase");
        return pStaticClass;
    }
};

struct UArtDataMonster : UDCDataAssetBase
{

};

// Size: 0xC30(Inherited: 0x8B0)
struct ADCMonsterBase : ADCCharacterBase
{
    char pad8b0[0x120];
    struct UArtDataMonster* ArtDataMonster;  // 0x9D0 (0x9D0)

    struct FPrimaryAssetId GetMonsterId(); // Function DungeonCrawler.DCMonsterBase.GetMonsterId

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.DCMonsterBase");
        return pStaticClass;
    }
};

struct UMovementComponent
{
    char pad0[0xB8];
    struct FVector Velocity;  // 0xB8 (0xB8)
};

struct UProjectileMovementComponent : UMovementComponent
{
    char pad0[0x108];
    float InitialSpeed;  // 0x108 (0x108)
    float MaxSpeed;  // 0x10C (0x10C)
    char pad10c[0x20];
    float ProjectileGravityScale;  // 0x130 (0x130)
};

struct AProjectileActor
{
    struct UProjectileMovementComponent* ProjectileMovement;  // 0x338 (0x338)
    float GravityScale;  // 0x1D0 (0x1D0)
};

struct ADCPlayerState : APlayerState
{

};

struct ABP_FootTrace_C
{

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("BlueprintGeneratedClass BP_FootTrace.BP_FootTrace_C");
        return pStaticClass;
    }
};

#pragma region Items
struct AItemActor
{
    char pad4d0[0x4d0];
    struct FItemData ItemData;  // 0x4D0 (0x4D0)

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.ItemActor");
        return pStaticClass;
    }
};

struct FInteractTargetData
{
    struct FText InteractTargetName;  // 0x0 (0x0)
    struct FGameplayTag RarityType;  // 0x18 (0x18)
};

struct UInteractableTargetComponent : UObject
{
    struct FInteractTargetData GetInteractTargetData(); // Function DungeonCrawler.InteractableTargetComponent.GetInteractTargetData

};

struct ADCInteractableActorBase : UObject
{
    char pad28[0x2D0];
    struct UInteractableTargetComponent* InteractableTargetComponent;  // 0x2F8 (0x2F8)

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.DCInteractableActorBase");
        return pStaticClass;
    }
};

struct UItem : UObject
{
    char pad28[0x110];
    struct FDesignDataItem ItemDesignData;  // 0x138 (0x138)
    struct UArtDataItem* ItemArtData;  // 0x2C0 (0x2C0)

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.Item");
        return pStaticClass;
    }
};

// Size: 0x3D0(Inherited: 0x300)
struct AItemHolderActorBase : ADCInteractableActorBase
{
    char pad300[0x18];
    struct FPrimaryAssetId ItemId;  // 0x318 (0x318)
    char pad318[0x60];
    struct UItem* ItemObject;  // 0x378 (0x378)
    struct UArtDataItem* ArtDataItem;  // 0x380 (0x380)

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("Class DungeonCrawler.ItemHolderActorBase");
        return pStaticClass;
    }
};

struct ABP_StaticMeshItemHolder_C
{

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("BlueprintGeneratedClass BP_StaticMeshItemHolder.BP_StaticMeshItemHolder_C");
        return pStaticClass;
    }
};
#pragma endregion

#pragma region Traps
struct ABP_TrapBase_C
{

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("BlueprintGeneratedClass BP_TrapBase.BP_TrapBase_C");
        return pStaticClass;
    }
};
#pragma endregion

struct ABP_Chest_Base_C
{

    static UClass* StaticClass()
    {
        static UClass* pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindObject<UClass>("BlueprintGeneratedClass BP_Chest_Base.BP_Chest_Base_C");
        return pStaticClass;
    }
};