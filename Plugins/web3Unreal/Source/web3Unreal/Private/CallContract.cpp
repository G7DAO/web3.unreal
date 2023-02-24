#include "CallContract.h"

UCallContract::UCallContract(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UCallContract* UCallContract::CallContract(
	const UObject* WorldContextObject,
	FString contractAddress,
	FString functionName,
	FString abi,
	TArray<FString> params,
	int32 gasLimit, 
	FString valueInWei,
	int32 chainId,
	FString chainMetadata)
{
	UCallContract* BlueprintNode = NewObject<UCallContract>();
	UCallContract* callContractNode = (UCallContract*)PostToCallContract(WorldContextObject,
		BlueprintNode,
		contractAddress,
		functionName,
		abi,
		params,
		gasLimit,
		valueInWei,
		chainId,
		chainMetadata);
	
	return callContractNode;
}

void UCallContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode)
{
	FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}
