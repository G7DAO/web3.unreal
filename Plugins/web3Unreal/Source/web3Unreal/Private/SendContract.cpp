#include "SendContract.h"

#include "Web3RequestBuilder.h"

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

	FWeb3RequestBuilder<FWeb3SendContractRequest> RequestBuilder;
	RequestBuilder.ParamsVar = params;
	RequestBuilder.ChainID = chainId;
	RequestBuilder.ContractAddressVar = contractAddress;
	RequestBuilder.FunctionNameVar = functionName;
	RequestBuilder.GasLimitVar = gasLimit;
	RequestBuilder.ABIVar = abi;
	RequestBuilder.ValueInWeiVar = valueInWei;
	RequestBuilder.OnCompleteDelegate.BindUObject(SendContractInstance, &UHyperplayAsyncRequest::OnResponse);
	RequestBuilder.ExecuteRequest();
	
	return SendContractInstance;
}

void USendContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}