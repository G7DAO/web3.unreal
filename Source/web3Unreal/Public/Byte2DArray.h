// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Byte2DArray.generated.h"

#pragma once

/**
 * Byte Array object used for 2D byte arrays in Blueprints
 */
USTRUCT(BlueprintType)
struct WEB3UNREAL_API FByte2DArray
{
	GENERATED_BODY()

	/**
	* The byte array that this object holds.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Web3.Unreal|Types")
	TArray<uint8> data;

	/**~
	* This UObject pointer is not accessible to Blueprint Graphs, but
	* is visible to UE4's reflection, smart pointer, and garbage collection
	* systems.
	*/
	UPROPERTY()
	UObject* SafeObjectPointer;
};