// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Web3RequestBuilder.h"
#include "HyperplayAsyncRequest.h"
#include "Misc/TVariant.h"
#include "RpcCall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTxnReturnOutputPinRpcCall, FString, Response, int32, StatusCode);

/**
* URpcCall is an async blueprint node used to call the HyperPlay /rpc local http server endpoint or another rpc provider
*/
UCLASS()
class WEB3UNREAL_API URpcCall : public UHyperplayAsyncRequest
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FTxnReturnOutputPinRpcCall OnResponseOutput;

	/**
	* RpcCall is used to generate the request
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|generic")
	static URpcCall* RpcCall(
		const UObject* WorldContextObject,
		FString request,
		int32 chainId = 1,
		FString chainMetadata = "",
		FString url = "http://localhost:9680/rpc");

	/**
	* Activate is used to execute the request.
	* Called to trigger the action once the delegates have been bound
	*/
	virtual void Activate() override;
	
protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) override;

private:
	using InternalRPC = FWeb3RPCRequest;
	using ExternalRPC = FWeb3ExternalRPCRequest;
	TVariant<InternalRPC, ExternalRPC> RequestBuilder;
};