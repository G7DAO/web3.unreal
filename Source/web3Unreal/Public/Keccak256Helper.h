// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
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
	/**
	* Blueprint function that calculates the keccak256 hash of the data string
	* and returns the result as a hex FString.
	*/
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static FString Keccak256(FString data);
	
	/**
	* Blueprint function that calculates the keccak256 hash of the data string 
	* and returns the result as a 32 byte TArray.
	*/
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static TArray<uint8> Keccak256Bytes(FString data);

	/**
	* Blueprint function that concatenates an array of byte arrays and then calculates the keccak256 hash of the result. 
	* Returns the result in a byte array.
	*/
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Keccak256")
		static TArray<uint8> ConcatByteArraysAndKeccak256(TArray<FByte2DArray> byte2DArray);
	/**
	* Static cpp function that hashes text with Keccak256 into a 32 byte array
	*/
	static void Keccak256FStringToByteArray(FString data, uint8_t *dest);
private:
};