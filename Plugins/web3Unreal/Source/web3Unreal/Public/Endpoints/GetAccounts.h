#pragma once
#include "HyperplayAsyncRequest.h"
#include "Web3RequestBuilder.h"
#include "GetAccounts.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPin, FString, SelectedAccount, int32, StatusCode);

UCLASS()
class WEB3UNREAL_API UGetAccounts : public UHyperplayAsyncRequest
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|helpers")
	static UGetAccounts* GetAccounts(const UObject* WorldContextObject, int32 chainId = 1, FString chainMetadata = "");

	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess=true))
	FTxnReturnOutputPin OnResponseOutput;

protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;

private:
	FWeb3RPCRequest RequestBuilder;
};