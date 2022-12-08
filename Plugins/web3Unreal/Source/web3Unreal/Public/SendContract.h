// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "./HyperPlayLibrary.h"
#include "SendContract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPinSendContract, FString, Response, int32, StatusCode);

UCLASS()
class USendContract : public UHyperPlayLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FTxnReturnOutputPinSendContract OnResponseOutput;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|generic")
		static USendContract* SendContract(
			const UObject* WorldContextObject,
			FString contractAddress,
			FString functionName,
			FString abi,
			TArray<FString> params,
			int32 gasLimit = -1, //value <=0 will not be added to the request
			FString valueInWei = "0",
			int32 chainId = 1
		);

protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;
};