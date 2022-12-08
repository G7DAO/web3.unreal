// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "./HyperPlayLibrary.h"
#include "GetAccounts.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPin, FString, SelectedAccount, int32, StatusCode);

UCLASS()
class UGetAccounts : public UHyperPlayLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FTxnReturnOutputPin OnResponseOutput;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|helpers")
		static UGetAccounts* GetAccounts(const UObject* WorldContextObject, int32 chainId = 1, FString chainMetadata = "");

protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;
};