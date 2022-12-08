#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HyperPlayLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HyperPlayLibraryLog, Display, All);

UCLASS()
class UHyperPlayLibrary : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	static UHyperPlayLibrary* PostToRpc(
		const UObject* WorldContextObject, 
		UHyperPlayLibrary* BlueprintNode, 
		FString request, 
		int32 chainId, 
		FString chainMetadata, 
		FString url, 
		FString params
	);
	static UHyperPlayLibrary* PostToSendContract(
		const UObject* WorldContextObject,
		UHyperPlayLibrary* BlueprintNode,
		FString contractAddress,
		FString functionName,
		FString abi,
		TArray<FString> params,
		int32 gasLimit,
		FString valueInWei,
		int32 chainId
	);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface
protected:
	virtual void ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {}

	TSharedPtr<FJsonValue> CreateJsonValue(FString obj);
private:
	UFUNCTION()
		void ExecuteOnResponse();

	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void CallRpcEndpoint();
	void CallSendContractEndpoint();

private:
	void BuildLocalRequest(TSharedPtr<FJsonObject> requestObject);
	const UObject* WorldContextObjectVar;

	//RPC endpoint specific member variables
	FString request;
	FString paramsStrVar;

	//Send Contract endpoint specific member variables
	FString contractAddressVar;
	FString functionNameVar;
	FString abiVar;
	FString valueInWeiVar; //int64 is not big enough
	TArray<FString> paramsVar;
	int32 gasLimitVar;

	//Common member vars
	int32 chainIdVar;
	FString chainMetadataVar;
	FString url;

	//FHttpRequestRef RequestPtr;
	FString endpoint;
};