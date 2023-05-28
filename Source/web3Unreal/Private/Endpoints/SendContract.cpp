#include "Endpoints/SendContract.h"

USendContract* USendContract::SendContract(
	const UObject* WorldContextObject,
	FString contractAddress,
	FString functionName,
	FString abi,
	TArray<FString> params,
	int32 gasLimit,
	FString valueInWei,
	int32 chainId) {
	
	USendContract* SendContractInstance = NewObject<USendContract>();

	SendContractInstance->RequestBuilder.ParamsVar = params;
	SendContractInstance->RequestBuilder.ChainID = chainId;
	SendContractInstance->RequestBuilder.ContractAddressVar = contractAddress;
	SendContractInstance->RequestBuilder.FunctionNameVar = functionName;
	SendContractInstance->RequestBuilder.GasLimitVar = gasLimit;
	SendContractInstance->RequestBuilder.ABIVar = abi;
	SendContractInstance->RequestBuilder.ValueInWeiVar = valueInWei;
	SendContractInstance->RequestBuilder.OnCompleteDelegate.BindUObject(SendContractInstance, &UHyperplayAsyncRequest::OnResponse);
	
	return SendContractInstance;
}

void USendContract::Activate()
{
	RequestBuilder.ExecuteRequest();
}

void USendContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	Super::ProcessResponse(Response, statusCode);
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
	OnCompleted.Broadcast(ResponseText, statusCode);
}
