// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HyperplayAsyncRequest.generated.h"

// Wider support for c++ bindings since c++ fxns cannot bind to dynamic delegates
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCompleted, FString, int32);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailedOutputPin);

/**
* UHyperplayAsyncRequest is an abstract parent class to the async blueprint nodes used to make rpc and local HyperPlay calls
*/
UCLASS()
class UHyperplayAsyncRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	* Public getter for completed delegate that has FString and int32 params
	*/
	FOnCompleted& GetOnCompletedDelegate() { return OnCompleted; }

	/**
	* Utility function 
	*/
	virtual void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
protected:
	/**
	* Abstract function called with the http response parsed by OnResponse
	*/
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode);
	
	/**
	* Completed output node that has FString and int32 params.
	* Called from child class when it has finished ProcessResponse.
	*/
	FOnCompleted OnCompleted;
	
private:
	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FFailedOutputPin OnFailure;
};
