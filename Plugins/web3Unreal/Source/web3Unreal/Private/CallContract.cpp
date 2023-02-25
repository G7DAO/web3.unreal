#include "CallContract.h"

#include "Web3RequestBuilder.h"

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
	UCallContract* CallContractInstance = NewObject<UCallContract>();

	FWeb3RequestBuilder<FWeb3CallContractRequest> RequestBuilder;
	RequestBuilder.ParamsVar = params;
	RequestBuilder.ChainID = chainId;
	RequestBuilder.ChainMetadataVar = chainMetadata;
	RequestBuilder.ContractAddressVar = contractAddress;
	RequestBuilder.FunctionNameVar = functionName;
	RequestBuilder.GasLimitVar = gasLimit;
	RequestBuilder.ABIVar = abi;
	RequestBuilder.ValueInWeiVar = valueInWei;
	RequestBuilder.OnCompleteDelegate.BindUObject(CallContractInstance, &UHyperplayAsyncRequest::OnResponse);
	RequestBuilder.ExecuteRequest();
	
	return CallContractInstance;
}

void UCallContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode)
{
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}
