// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Account.generated.h"

/**
 * Secp256k1 curve private and public key
 */
USTRUCT(BlueprintType)
struct WEB3UNREAL_API FAccount
{
	GENERATED_BODY()

public:
	/**
	* Private key as a hex string
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Web3.Unreal|Types")
	FString privateKey;

	/**
	* Public address as a hex string
	*/
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