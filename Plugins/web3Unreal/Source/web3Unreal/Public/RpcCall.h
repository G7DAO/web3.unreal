// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "./HyperPlayLibrary.h"
#include "RpcCall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPinRpcCall, FString, Response, int32, StatusCode);

UCLASS()
class URpcCall : public UHyperPlayLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FTxnReturnOutputPinRpcCall OnResponseOutput;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|generic")
		static URpcCall* RpcCall(const UObject* WorldContextObject, FString request, int32 chainId = 1, FString chainMetadata = "", FString url = "http://localhost:9680/rpc", FString params = "");

protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;
};