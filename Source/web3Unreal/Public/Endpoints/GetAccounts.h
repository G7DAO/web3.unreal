// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "HyperplayAsyncRequest.h"
#include "Web3RequestBuilder.h"
#include "GetAccounts.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPin, FString, SelectedAccount, int32, StatusCode);

/**
* UGetAccounts is an async blueprint node used to get the currently connected HyperPlay account
*/
UCLASS()
class WEB3UNREAL_API UGetAccounts : public UHyperplayAsyncRequest
{
	GENERATED_BODY()

public:
	/**
	* GetAccounts is used to generate the request
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|helpers")
	static UGetAccounts* GetAccounts(const UObject* WorldContextObject, int32 chainId = 1, FString chainMetadata = "");

	/**
	* Activate is used to execute the request.
	* Called to trigger the action once the delegates have been bound
	*/
	virtual void Activate() override;
	
	/**
	* The OnResponseOutput pin returns the account info to the calling code
	*/
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess=true))
	FTxnReturnOutputPin OnResponseOutput;

protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;

private:
	FWeb3RPCRequest RequestBuilder;
};