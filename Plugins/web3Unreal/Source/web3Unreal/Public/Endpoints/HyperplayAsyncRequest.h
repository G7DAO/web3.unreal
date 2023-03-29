#pragma once
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HyperplayAsyncRequest.generated.h"

// Wider support for c++ bindings
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCompleted, FString, int32);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailedOutputPin);

UCLASS()
class UHyperplayAsyncRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	FOnCompleted& GetOnCompletedDelegate() { return OnCompleted; }
	
protected:
	virtual void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode);
	
private:
	FOnCompleted OnCompleted;
	
	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FFailedOutputPin OnFailure;
};
