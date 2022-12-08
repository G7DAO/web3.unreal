#include "SendContract.h"

USendContract::USendContract(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

USendContract* USendContract::SendContract(
	const UObject* WorldContextObject,
	FString contractAddress,
	FString functionName,
	FString abi,
	TArray<FString> params,
	int32 gasLimit,
	FString valueInWei,
	int32 chainId) {

	USendContract* BlueprintNode = NewObject<USendContract>();
	USendContract* getAcctNode = (USendContract*)PostToSendContract(WorldContextObject,
		BlueprintNode,
		contractAddress,
		functionName,
		abi,
		params,
		gasLimit,
		valueInWei,
		chainId);
	return getAcctNode;
}

void USendContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}