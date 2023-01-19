#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Byte2DArray.h"
#include "Keccak256Helper.generated.h"

/**
 * Exposes Keccak256.h functionality to Blueprints/C++ code as a Function Library
 */
UCLASS()
class WEB3UNREAL_API UKeccak256Helper : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static FString Keccak256(FString data);
	
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static TArray<uint8> Keccak256Bytes(FString data);

	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static TArray<uint8> ConcatByteArraysAndKeccak256(TArray<FByte2DArray> byte2DArray);
	
	static void Keccak256FStringToByteArray(FString data, uint8_t *dest);
private:
};