// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Web3RequestBuilder.h"
#include "HyperplayAsyncRequest.h"
#include "SendContract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPinSendContract, FString, Response, int32, StatusCode);

/**
* USendContract is an async blueprint node used to call the HyperPlay /sendContract local http server endpoint
*/
UCLASS()
class WEB3UNREAL_API USendContract : public UHyperplayAsyncRequest
{
	GENERATED_BODY()

public:
	/**
	* SendContract is used to generate the request
	*/
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

	/**
	* Activate is used to execute the request.
	* Called to trigger the action once the delegates have been bound
	*/
	virtual void Activate() override;
	
protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;

private:
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess=true))
	FTxnReturnOutputPinSendContract OnResponseOutput;
	
	FWeb3SendContractRequest RequestBuilder;
};