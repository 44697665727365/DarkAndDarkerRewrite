#pragma once

#define TORAD(x) ((x) * (M_PI / 180.f))
#define M_PI 3.14159265358979323846


template<class T>
class TArray
{
	friend class FString;

public:
	constexpr TArray() noexcept
	{
		Data = nullptr;
		Count = Max = 0;
	};

	[[nodiscard]] constexpr auto Num() const noexcept
	{
		return Count;
	};

	[[nodiscard]] constexpr auto& operator[](std::int32_t i) noexcept
	{
		return Data[i];
	};

	[[nodiscard]] constexpr const auto& operator[](std::int32_t i) const noexcept
	{
		return Data[i];
	};

	[[nodiscard]] constexpr auto IsValidIndex(std::int32_t i) const noexcept
	{
		return i < Num();
	}

	T* Data;
	std::int32_t Count;
	std::int32_t Max;
};

class FString : public TArray<wchar_t>
{
public:
	constexpr FString() noexcept
	{
	};

	constexpr FString(const wchar_t* other) noexcept
	{
		Max = Count = *other ? static_cast<std::int32_t>(std::wcslen(other)) + 1 : 0;

		if (Count)
			Data = const_cast<wchar_t*>(other);
	};

	[[nodiscard]] constexpr auto IsValid() const noexcept
	{
		return Data != nullptr;
	}

	[[nodiscard]] constexpr auto c_str() const noexcept
	{
		return Data;
	}

	[[nodiscard]] auto ToString() const noexcept
	{
		const auto length = std::wcslen(Data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
		return str;
	}
};

struct FNameEntryHandle
{
	uint32_t Block = 0;
	uint32_t Offset = 0;

	FNameEntryHandle(uint32_t block, uint32_t offset) : Block(block), Offset(offset) {};
	FNameEntryHandle(uint32_t id) : Block(id >> 16), Offset(id & 65535) {};
	operator uint32_t() const { return (Block << 16 | Offset); }
};

struct FNameEntry
{
	uint16_t bIsWide : 1;
	uint16_t LowercaseProbeHash : 5;
	uint16_t Len : 10;
	union
	{
		char AnsiName[1024];
		wchar_t	WideName[1024];
	};

	std::string String();
};

struct FNamePool
{
	byte Lock[8];
	uint32_t CurrentBlock;
	uint32_t CurrentByteCursor;
	byte* Blocks[8192];

	FNameEntry* GetEntry(FNameEntryHandle handle) const;
};

struct FName
{
	uint32_t Index;
	uint32_t Number;

	std::string GetName();

};

struct TUObjectArray
{
	byte** Objects;
	byte* PreAllocatedObjects;
	uint32_t MaxElements;
	uint32_t NumElements;
	uint32_t MaxChunks;
	uint32_t NumChunks;

	struct UObject* GetObjectPtr(uint32_t id) const;

};


extern TUObjectArray* ObjObjects;
extern FNamePool* NamePoolData;

struct UObject
{
	void** VFTable;
	uint32_t ObjectFlags;
	uint32_t InternalIndex;
	struct UClass* ClassPrivate;
	FName NamePrivate;
	UObject* OuterPrivate;

	std::string GetName();
	std::string GetFullName();
	bool IsA(void* cmp);
	void ProcessEvent(void* fn, void* parms);

	std::string GetObjectName();

	template<typename T>
	static T* FindObject(const std::string& name)
	{
		for (auto i = 0u; i < ObjObjects->NumElements; i++)
		{
			auto object = ObjObjects->GetObjectPtr(i);
			if (object && object->GetFullName() == name)
				return static_cast<T*>(object);
		}

		return nullptr;
	}

	inline std::string FixName(std::string Name)
	{
		std::string sTemp = Name;
		sTemp = sTemp.substr(0, sTemp.rfind('_'));
		return sTemp;
	}
};

// Class CoreUObject.Field
// Size: 0x30 (Inherited: 0x28)
struct UField : UObject
{
	char UnknownData_28[0x8]; // 0x28(0x08)
};

// Class CoreUObject.Struct
// Size: 0xb0 (Inherited: 0x30)
struct UStruct : UField
{
	char UnknownData_30[0x10]; // 0x30(0x10)
	UStruct* SuperStruct; // 0x40(0x8)
	char UnknownData_48[0x68]; // 0x48(0x80)
};

// Class CoreUObject.Class
// Size: 0x230 (Inherited: 0xb0)
struct UClass : UStruct
{
	char UnknownData_B0[0x180]; // 0xb0(0x180)
};

// Class Engine.BlueprintGeneratedClass
// Size: 0x328 (Inherited: 0x230)
struct UBlueprintGeneratedClass : UClass
{
	char Unknown[0xF8];
};

// Class CoreUObject.Function
// Size: 0xe0 (Inherited: 0xb0)
struct UFunction : UStruct {
	int32_t                                            FunctionFlags;                                            // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int8_t                                             NumParms;                                                 // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int16_t                                            RepOffset;                                                // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	char                                               pad_00B7[1];                                              // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int16_t                                            ParmsSize;                                                // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int16_t                                            ReturnValueOffset;                                        // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int16_t                                            RPCId;                                                    // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int16_t                                            RPCResponseId;                                            // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UProperty* FirstPropertyToInit;                                      // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UFunction* EventGraphFunction;                                       // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            EventGraphCallOffset;                                     // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	char                                               pad_00D4[4];                                              // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	void* Func;                                                     // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
};


template<class TEnum>
class TEnumAsByte
{
public:
	inline TEnumAsByte()
	{
	}

	inline TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(int32_t _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(uint8_t _value)
		: value(_value)
	{
	}

	inline operator TEnum() const
	{
		return (TEnum)value;
	}

	inline TEnum GetValue() const
	{
		return (TEnum)value;
	}

private:
	uint8_t value;
};

struct UKismetMathLibrary : UObject
{
	struct FVector Conv_RotatorToVector(struct FRotator InRot);
	float GetPI();

	struct FLinearColor Conv_ColorToLinearColor(struct FColor InColor); // Function Engine.KismetMathLibrary.Conv_ColorToLinearColor


	struct FRotator FindLookAtRotation(struct FVector Start, struct FVector Target); // Function Engine.KismetMathLibrary.FindLookAtRotation

	static UClass* StaticClass()
	{
		static UClass* pStaticClass = 0;
		if (!pStaticClass)
			pStaticClass = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
		return pStaticClass;
	}
};

struct UKismetSystemLibrary : UObject
{
	void GetComponentBounds(struct USceneComponent* Component, struct FVector& Origin, struct FVector& BoxExtent, float& SphereRadius); // Function Engine.KismetSystemLibrary.GetComponentBounds


	static UClass* StaticClass()
	{
		static UClass* pStaticClass = 0;
		if (!pStaticClass)
			pStaticClass = UObject::FindObject<UClass>("Class Engine.KismetSystemLibrary");
		return pStaticClass;
	}
};


#pragma region Math

inline double deg2rad(double deg)
{
	return deg * M_PI / 180.f;
}

inline double rad2deg(double radian)
{
	double pi = 3.14159;
	return(radian * (180 / pi));
}

struct FVector2D
{
	union
	{
		struct { double X, Y; };
		struct { double x, y; };
		struct { double pitch, yaw; };
		struct { double value[2]; };
	};

	FVector2D() : x(0), y(0) {}
	FVector2D(double x) : x(x), y(0) {}
	FVector2D(double x, double y) : x(x), y(y) {}
	FVector2D(double value[2]) : x(value[0]), y(value[1]) {}
};

struct FVector
{
	union
	{
		struct { double X, Y, Z; };
		struct { double x, y, z; };
		struct { double pitch, yaw, roll; };
		struct { double value[3]; };
	};

	constexpr FVector(double x = 0.f, double y = 0.f, double z = 0.f) noexcept : X{ x }, Y{ y }, Z{ z } {}

	[[nodiscard]] friend constexpr auto operator-(const FVector& a, const FVector& b) noexcept -> FVector
	{
		return { a.X - b.X, a.Y - b.Y, a.Z - b.Z };
	}

	[[nodiscard]] friend constexpr auto operator+(const FVector& a, const FVector& b) noexcept -> FVector
	{
		return { a.X + b.X, a.Y + b.Y, a.Z + b.Z };
	}

	[[nodiscard]] friend constexpr auto operator*(const FVector& a, const FVector& b) noexcept -> FVector
	{
		return { a.X * b.X, a.Y * b.Y, a.Z * b.Z };
	}

	[[nodiscard]] friend constexpr auto operator*(const FVector& v, double f) noexcept -> FVector
	{
		return { v.X * f, v.Y * f, v.Z * f };
	}

	[[nodiscard]] friend constexpr auto operator/(const FVector& v, double f) noexcept -> FVector
	{
		return { v.X / f, v.Y / f, v.Z / f };
	}

	[[nodiscard]] friend constexpr auto operator-(double f, const FVector& v) noexcept -> FVector
	{
		return{ f - v.X, f - v.Y, f - v.Z };
	}

	constexpr auto& operator+=(const FVector& v) noexcept
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	constexpr auto& operator-=(const FVector& v) noexcept
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	constexpr auto& operator*=(const FVector& v) noexcept
	{
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
		return *this;
	}

	constexpr auto& operator/=(const FVector& v) noexcept
	{
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
		return *this;
	}

	const double DotProduct(FVector coords)
	{
		return (this->X * coords.X) + (this->Y * coords.Y) + (this->Z * coords.Z);
	}

	bool isValid()
	{
		return (this->X != 0 && this->Y != 0 && this->Z != 0);
	}

	double length()
	{
		return (double)sqrt(X * X + Y * Y + Z * Z);
	}

	std::string ToString()
	{
		return va("%.3f %.3f %.3f", this->x, this->y, this->z);
	}

	double distance(FVector vec)
	{
		double _x = this->X - vec.X;
		double _y = this->Y - vec.Y;
		double _z = this->Z - vec.Z;
		return sqrt((_x * _x) + (_y * _y) + (_z * _z));
	}

	FVector normalize()
	{
		FVector newvec;
		newvec.X = this->X / length();
		newvec.Y = this->Y / length();
		newvec.Z = this->Z / length();
		return newvec;
	}
};

struct FRotator
{
	union
	{
		struct { double X, Y, Z; };
		struct { double x, y, z; };
		struct { double pitch, yaw, roll; };
		struct { double Pitch, Yaw, Roll; };
		struct { double value[3]; };
	};

	[[nodiscard]] friend constexpr auto operator-(const FRotator& a, const FRotator& b) noexcept -> FRotator
	{
		return { a.Pitch - b.Pitch, a.Yaw - b.Yaw, a.Roll - b.Roll };
	}

	[[nodiscard]] friend constexpr auto operator+(const FRotator& a, const FRotator& b) noexcept -> FRotator
	{
		return { a.Pitch + b.Pitch, a.Yaw + b.Yaw, a.Roll + b.Roll };
	}

	[[nodiscard]] friend constexpr auto operator*(const FRotator& a, const FRotator& b) noexcept -> FRotator
	{
		return { a.Pitch * b.Pitch, a.Yaw * b.Yaw, a.Roll * b.Roll };
	}

	[[nodiscard]] friend constexpr auto operator*(const FRotator& a, double b) noexcept -> FRotator
	{
		return { a.Pitch * b, a.Yaw * b, a.Roll * b };
	}

	[[nodiscard]] friend constexpr auto operator/(const FRotator& a, double b) noexcept -> FRotator
	{
		return { a.Pitch / b, a.Yaw / b, a.Roll / b };
	}

	double* fromAngle() const
	{
		double temp[3] = {
			std::cos(deg2rad(Pitch)) * std::cos(deg2rad(Yaw)),
			std::cos(deg2rad(Pitch)) * std::sin(deg2rad(Yaw)),
			std::sin(deg2rad(Pitch))
		};

		return temp;
	}

	constexpr auto& operator+=(const FRotator& o) noexcept
	{
		Pitch += o.Pitch;
		Yaw += o.Yaw;
		Roll += o.Roll;
		return *this;
	}



	constexpr auto& normalize() noexcept
	{
		Pitch = std::isfinite(Pitch) ? std::remainder(Pitch, 360.f) : 0.f;
		Yaw = std::isfinite(Yaw) ? std::remainder(Yaw, 360.f) : 0.f;
		Roll = 0.f;
		return *this;
	}

	struct FVector ToVector()
	{
		struct UKismetMathLibrary* math = (struct UKismetMathLibrary*)UKismetMathLibrary::StaticClass();

		FRotator val{ this->pitch, this->yaw, this->roll };

		auto vec = math->Conv_RotatorToVector(val);
		return vec;
	}
};


#pragma endregion

struct FColor
{
	char B;  // 0x0(0x1)
	char G;  // 0x1(0x1)
	char R;  // 0x2(0x1)
	char A;  // 0x3(0x1)

	FColor() { R = G = B = A = 0; };
	FColor(int r, int g, int b)
	{
		R = r;
		G = g;
		B = b;
		A = 255;
	}

};

struct FPlane : public FVector
{
	double W;  // 0x18(0x8)

};

struct FLinearColor
{
	float R;  // 0x0(0x4)
	float G;  // 0x4(0x4)
	float B;  // 0x8(0x4)
	float A;  // 0xC(0x4)

	/*FLinearColor() {}

	FLinearColor(float r) : R(r), G(0), B(0), A(0) {};
	FLinearColor(float r, float g) : R(r / 255), G(g / 255), B(0), A(0) {};
	FLinearColor(float r, float g, float b) : R(r/255.f), G(g / 255.f), B(b / 255.f), A(255) {};
	FLinearColor(float r, float g, float b, float a) : R(r / 255), G(g / 255), B(b / 255), A(a / 255) {};*/
};

struct FCanvasUVTri
{
	struct FVector2D V0_Pos;  // 0x0(0x10)
	struct FVector2D V0_UV;  // 0x10(0x10)
	struct FLinearColor V0_Color;  // 0x20(0x10)
	struct FVector2D V1_Pos;  // 0x30(0x10)
	struct FVector2D V1_UV;  // 0x40(0x10)
	struct FLinearColor V1_Color;  // 0x50(0x10)
	struct FVector2D V2_Pos;  // 0x60(0x10)
	struct FVector2D V2_UV;  // 0x70(0x10)
	struct FLinearColor V2_Color;  // 0x80(0x10)
};

struct FFontImportOptionsData
{
	struct FString FontName;  // 0x0(0x10)
	float Height;  // 0x10(0x4)
	char bEnableAntialiasing : 1;  // 0x14(0x1)
	char bEnableBold : 1;  // 0x14(0x1)
	char bEnableItalic : 1;  // 0x14(0x1)
	char bEnableUnderline : 1;  // 0x14(0x1)
	char bAlphaOnly : 1;  // 0x14(0x1)
	char pad_20_1 : 3;  // 0x14(0x1)
	char pad_21[4];  // 0x15(0x4)
	char CharacterSet;  // 0x18(0x1)
	char pad_25[7];  // 0x19(0x7)
	struct FString Chars;  // 0x20(0x10)
	struct FString UnicodeRange;  // 0x30(0x10)
	struct FString CharsFilePath;  // 0x40(0x10)
	struct FString CharsFileWildcard;  // 0x50(0x10)
	char bCreatePrintableOnly : 1;  // 0x60(0x1)
	char bIncludeASCIIRange : 1;  // 0x60(0x1)
	char pad_96_1 : 6;  // 0x60(0x1)
	char pad_97[4];  // 0x61(0x4)
	struct FLinearColor ForegroundColor;  // 0x64(0x10)
	char bEnableDropShadow : 1;  // 0x74(0x1)
	char pad_116_1 : 7;  // 0x74(0x1)
	char pad_117[4];  // 0x75(0x4)
	int32_t TexturePageWidth;  // 0x78(0x4)
	int32_t TexturePageMaxHeight;  // 0x7C(0x4)
	int32_t XPadding;  // 0x80(0x4)
	int32_t YPadding;  // 0x84(0x4)
	int32_t ExtendBoxTop;  // 0x88(0x4)
	int32_t ExtendBoxBottom;  // 0x8C(0x4)
	int32_t ExtendBoxRight;  // 0x90(0x4)
	int32_t ExtendBoxLeft;  // 0x94(0x4)
	char bEnableLegacyMode : 1;  // 0x98(0x1)
	char pad_152_1 : 7;  // 0x98(0x1)
	char pad_153[4];  // 0x99(0x4)
	int32_t Kerning;  // 0x9C(0x4)
	char bUseDistanceFieldAlpha : 1;  // 0xA0(0x1)
	char pad_160_1 : 7;  // 0xA0(0x1)
	char pad_161[4];  // 0xA1(0x4)
	int32_t DistanceFieldScaleFactor;  // 0xA4(0x4)
	float DistanceFieldScanRadiusScale;  // 0xA8(0x4)
	char pad_172[4];  // 0xAC(0x4)

};
struct UFont : public UObject
{
	char pad_40[8];  // 0x28(0x8)
	uint8_t  FontCacheType;  // 0x30(0x1)
	char pad_49[7];  // 0x31(0x7)
	struct TArray<struct FFontCharacter> Characters;  // 0x38(0x10)
	struct TArray<struct UTexture2D*> Textures;  // 0x48(0x10)
	int32_t IsRemapped;  // 0x58(0x4)
	float EmScale;  // 0x5C(0x4)
	float Ascent;  // 0x60(0x4)
	float Descent;  // 0x64(0x4)
	float Leading;  // 0x68(0x4)
	int32_t Kerning;  // 0x6C(0x4)
	struct FFontImportOptionsData ImportOptions;  // 0x70(0xB0)
	int32_t NumCharacters;  // 0x120(0x4)
	char pad_292[4];  // 0x124(0x4)
	struct TArray<int32_t> MaxCharHeight;  // 0x128(0x10)
	float ScalingFactor;  // 0x138(0x4)
	int32_t LegacyFontSize;  // 0x13C(0x4)
	struct FName LegacyFontName;  // 0x140(0x8)
};

extern UFont* DefaultMediumFont;

struct UGameplayStatics : UObject
{

	void GetAllActorsOfClass(struct UObject* WorldContextObject, struct AActor* ActorClass, struct TArray<struct AActor*>& OutActors); // Function Engine.GameplayStatics.GetAllActorsOfClass
	struct FString GetCurrentLevelName(struct UObject* WorldContextObject, bool bRemovePrefixString); // Function Engine.GameplayStatics.GetCurrentLevelName


	static UClass* StaticClass()
	{
		static UClass* ptr = NULL;
		if (!ptr)
			ptr = UObject::FindObject<UClass>("Class Engine.GameplayStatics");

		return ptr;
	}
};
