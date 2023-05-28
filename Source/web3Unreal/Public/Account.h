#pragma once
#include "Account.generated.h"

/**
 * Eth account with private and public key
 */
USTRUCT(BlueprintType)
struct WEB3UNREAL_API FAccount
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Web3.Unreal|Types")
	FString privateKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Web3.Unreal|Types")
	FString publicAddress;
	
	/**~
	* This UObject pointer is not accessible to Blueprint Graphs, but
	* is visible to UE4's reflection, smart pointer, and garbage collection
	* systems.
	*/
	UPROPERTY()
	UObject* SafeObjectPointer;
};