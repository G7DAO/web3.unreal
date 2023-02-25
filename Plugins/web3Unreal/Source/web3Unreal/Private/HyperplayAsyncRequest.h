#pragma once
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HyperplayAsyncRequest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailedOutputPin);

UCLASS()
class UHyperplayAsyncRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:
	virtual void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode);

private:
	UPROPERTY(BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FFailedOutputPin OnFailure;
};
