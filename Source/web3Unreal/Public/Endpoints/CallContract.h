// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once

#include "Runtime/Online/HTTP/Public/Http.h"
#include "HyperplayAsyncRequest.h"
#include "Web3RequestBuilder.h"
#include "CallContract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPinCallContract, FString, Response, int32, StatusCode);

/**
* UCallContract is an async blueprint node used to call the HyperPlay /callContract local http server endpoint
*/
UCLASS()
class WEB3UNREAL_API UCallContract : public UHyperplayAsyncRequest
{
	GENERATED_BODY()

public:
	/**
	* CallContract is used to generate the request
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|generic")
	static UCallContract* CallContract(
		const UObject* WorldContextObject,
		FString contractAddress,
		FString functionName,
		FString abi,
		TArray<FString> params,
		int32 gasLimit = -1, //value <=0 will not be added to the request
		FString valueInWei = "0",
		int32 chainId = 1,
		FString chainMetadata = ""
		);

	/**
	* Activate is used to execute the request.
	* Called to trigger the action once the delegates have been bound
	*/
	virtual void Activate() override;
	
protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;

private:
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess=true))
	FTxnReturnOutputPinCallContract OnResponseOutput;
	
	FWeb3CallContractRequest RequestBuilder;
};