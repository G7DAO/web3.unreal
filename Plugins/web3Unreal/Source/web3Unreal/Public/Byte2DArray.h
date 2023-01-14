#include "Byte2DArray.generated.h"

#pragma once

/**
 * 2D Byte Array for Blueprints
 */
USTRUCT(BlueprintType)
struct FByte2DArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	TArray<uint8> data;

	/**~
	* This UObject pointer is not accessible to Blueprint Graphs, but
	* is visible to UE4's reflection, smart pointer, and garbage collection
	* systems.
	*/
	UPROPERTY()
	UObject* SafeObjectPointer;
};