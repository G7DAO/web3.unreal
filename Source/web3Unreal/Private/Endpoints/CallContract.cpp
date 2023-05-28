#include "Endpoints/CallContract.h"

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
	CallContractInstance->RequestBuilder.ParamsVar = params;
	CallContractInstance->RequestBuilder.ChainID = chainId;
	CallContractInstance->RequestBuilder.ChainMetadataVar = chainMetadata;
	CallContractInstance->RequestBuilder.ContractAddressVar = contractAddress;
	CallContractInstance->RequestBuilder.FunctionNameVar = functionName;
	CallContractInstance->RequestBuilder.GasLimitVar = gasLimit;
	CallContractInstance->RequestBuilder.ABIVar = abi;
	CallContractInstance->RequestBuilder.ValueInWeiVar = valueInWei;
	CallContractInstance->RequestBuilder.OnCompleteDelegate.BindUObject(CallContractInstance, &UHyperplayAsyncRequest::OnResponse);
	
	return CallContractInstance;
}

void UCallContract::Activate()
{
	RequestBuilder.ExecuteRequest();
}

void UCallContract::ProcessResponse(FHttpResponsePtr Response, int32 statusCode)
{
	Super::ProcessResponse(Response, statusCode);
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
	OnCompleted.Broadcast(ResponseText, statusCode);
}
