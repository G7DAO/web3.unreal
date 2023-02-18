#include "HyperPlayLibrary.h"

#include "Web3RequestBuilder.h"

DEFINE_LOG_CATEGORY(HyperPlayLibraryLog);

UHyperPlayLibrary::UHyperPlayLibrary(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), WorldContextObjectVar(nullptr), chainIdVar(int32(1)), request(FString(TEXT("{}")))
{
}

void UHyperPlayLibrary::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	UE_LOG(LogTemp, Warning, TEXT("bWasSuccessful = %hs"), bWasSuccessful ? "true" : "false");
	if (bWasSuccessful) {
		int32 statusCode = Response->GetResponseCode();
		if (!this->StatusCodeIsSuccess(statusCode))
		{
			this->OnFailure.Broadcast();
			return;
		}
		FString ResponseText = Response->GetContentAsString();

		// JSON parsing
		TSharedPtr<FJsonValue> ParsedJSON;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseText);
		FJsonSerializer::Deserialize(Reader, ParsedJSON);
		this->ProcessResponse(Response, statusCode);
		this->ExecuteOnResponse();
		return;
	}
	this->OnFailure.Broadcast();
}

bool UHyperPlayLibrary::StatusCodeIsSuccess(int32 statusCode)
{
	if (statusCode > 199 && statusCode < 300)
	{
		return true;
	}
	return false;
}

TSharedPtr<FJsonValue> UHyperPlayLibrary::CreateJsonValue(FString obj) {
	TSharedPtr<FJsonValue> val;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(obj);
	FJsonSerializer::Deserialize(Reader, val);
	return val;
}

void UHyperPlayLibrary::ExecuteOnResponse(){}

void UHyperPlayLibrary::CallRpcEndpoint() {

	if(url == "http://localhost:9680/rpc")
	{
		FWeb3RequestBuilder<FWeb3RPCRequest> RequestBuilder;
		RequestBuilder.Url = "http://localhost:9680/rpc";
		RequestBuilder.Request = request;
		RequestBuilder.ChainID = chainIdVar;
		RequestBuilder.ChainMetadataVar = chainMetadataVar;
		RequestBuilder.ParamsStrVar = paramsStrVar;
		RequestBuilder.OnCompleteDelegate.BindUObject(this, &UHyperPlayLibrary::OnResponse);
		RequestBuilder.ExecuteRequest();
	
		return;
	}
	
	FWeb3RequestBuilder<FWeb3PExternalRPCRequest> RequestBuilder;
	RequestBuilder.Url = url;
	RequestBuilder.ChainID = chainIdVar;
	RequestBuilder.RequestString = request;
	RequestBuilder.OnCompleteDelegate.BindUObject(this, &UHyperPlayLibrary::OnResponse);
	RequestBuilder.ExecuteRequest();
}

UHyperPlayLibrary* UHyperPlayLibrary::PostToRpc(const UObject* WorldContextObject, UHyperPlayLibrary* BlueprintNode, FString request, int32 chainId, FString chainMetadata, FString url, FString params)
{
	BlueprintNode->WorldContextObjectVar = WorldContextObject;
	BlueprintNode->request = request;
	BlueprintNode->chainIdVar = chainId;
	BlueprintNode->endpoint = TEXT("rpc");
	BlueprintNode->chainMetadataVar = chainMetadata;
	BlueprintNode->url = url;
	BlueprintNode->paramsStrVar = params;
	return BlueprintNode;
}

void UHyperPlayLibrary::CallSendContractEndpoint() {
	FWeb3RequestBuilder<FWeb3SendContractRequest> RequestBuilder;
	RequestBuilder.Url = "http://localhost:9680/sendContract";
	RequestBuilder.ParamsVar = paramsVar;
	RequestBuilder.ChainID = chainIdVar;
	RequestBuilder.ContractAddressVar = contractAddressVar;
	RequestBuilder.FunctionNameVar = functionNameVar;
	RequestBuilder.GasLimitVar = gasLimitVar;
	RequestBuilder.ABIVar = abiVar;
	RequestBuilder.ValueInWeiVar = valueInWeiVar;
	RequestBuilder.OnCompleteDelegate.BindUObject(this, &UHyperPlayLibrary::OnResponse);
	RequestBuilder.ExecuteRequest();
}

UHyperPlayLibrary* UHyperPlayLibrary::PostToSendContract(
	const UObject* WorldContextObject,
	UHyperPlayLibrary* BlueprintNode,
	FString contractAddress,
	FString functionName,
	FString abi,
	TArray<FString> params,
	int32 gasLimit,
	FString valueInWei,
	int32 chainId
) {
	BlueprintNode->WorldContextObjectVar = WorldContextObject;
	BlueprintNode->contractAddressVar = contractAddress;
	BlueprintNode->functionNameVar = functionName;
	BlueprintNode->abiVar = abi;
	BlueprintNode->paramsVar = params;
	BlueprintNode->valueInWeiVar = valueInWei;
	BlueprintNode->gasLimitVar = gasLimit;
	BlueprintNode->chainIdVar = chainId;
	BlueprintNode->endpoint = TEXT("sendContract");
	return BlueprintNode;
}

void UHyperPlayLibrary::Activate()
{
	// Any safety checks should be performed here. Check here validity of all your pointers etc.
	// You can log any errors using FFrame::KismetExecutionMessage, like that:
	// FFrame::KismetExecutionMessage(TEXT("Valid Player Controller reference is needed for ... to start!"), ELogVerbosity::Error);
	// return;

	if (endpoint.Equals(TEXT("rpc"))) {
		this->CallRpcEndpoint();
	}
	else {
		this->CallSendContractEndpoint();
	}
}