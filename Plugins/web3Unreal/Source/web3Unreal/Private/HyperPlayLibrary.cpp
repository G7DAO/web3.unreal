#include "HyperPlayLibrary.h"

DEFINE_LOG_CATEGORY(HyperPlayLibraryLog);

UHyperPlayLibrary::UHyperPlayLibrary(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), WorldContextObjectVar(nullptr), chainIdVar(int32(1)), request(FString(TEXT("{}")))
{
}

void UHyperPlayLibrary::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		int32 statusCode = Response->GetResponseCode();
		FString ResponseText = Response->GetContentAsString();

		// JSON parsing
		TSharedPtr<FJsonValue> ParsedJSON;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseText);
		FJsonSerializer::Deserialize(Reader, ParsedJSON);
		this->ProcessResponse(Response, statusCode);
		this->ExecuteOnResponse();
		return;
	}
	this->ProcessResponse(Response, 404);
	this->ExecuteOnResponse();
}

TSharedPtr<FJsonValue> UHyperPlayLibrary::CreateJsonValue(FString obj) {
	TSharedPtr<FJsonValue> val;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(obj);
	FJsonSerializer::Deserialize(Reader, val);
	return val;
}

void UHyperPlayLibrary::ExecuteOnResponse(){}

typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

void UHyperPlayLibrary::BuildLocalRequest(TSharedPtr<FJsonObject> requestObject) {
	//chain
	TSharedPtr<FJsonValue> emptyChainValue = this->CreateJsonValue(TEXT("{}"));
	TSharedPtr<FJsonObject> chainObject = emptyChainValue->AsObject();
	chainObject->SetField(TEXT("chainId"), MakeShared<FJsonValueString>(FString::FromInt(this->chainIdVar)));

	if (!this->chainMetadataVar.Equals(TEXT(""))) {
		TSharedPtr<FJsonValue> chainMetadataObject = this->CreateJsonValue(this->chainMetadataVar);
		if (!chainMetadataObject.IsValid()) {
			UE_LOG(HyperPlayLibraryLog, Error, TEXT("Could not parse chain metadata"));
			return;
		}
		chainObject->SetField(TEXT("chainMetadata"), chainMetadataObject);
	}

	requestObject->SetField(TEXT("chain"), MakeShared<FJsonValueObject>(chainObject));

	//request
	TSharedPtr<FJsonValue> rpcRequestObject = this->CreateJsonValue(this->request);
	if (!rpcRequestObject.IsValid()) {
		UE_LOG(HyperPlayLibraryLog, Error, TEXT("Could not parse the rpc request"));
		return;
	}
	requestObject->SetField(TEXT("request"), rpcRequestObject);

	//params
	if (!this->paramsStrVar.Equals(TEXT(""))) {
		TSharedPtr<FJsonValue> rpcParamsObject = this->CreateJsonValue(this->paramsStrVar);
		if (!rpcParamsObject.IsValid()) {
			UE_LOG(HyperPlayLibraryLog, Error, TEXT("Could not parse the rpc params"));
			return;
		}
		requestObject->SetField(TEXT("params"), rpcParamsObject);
	}
}

void UHyperPlayLibrary::CallRpcEndpoint() {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(this->url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	TSharedPtr<FJsonValue> emptyRequestValue = this->CreateJsonValue(TEXT("{}"));
	TSharedPtr<FJsonObject> requestObject = emptyRequestValue->AsObject();

	FString OutputString;
	if (this->url.Equals(TEXT("http://localhost:9680/rpc"))) {
		this->BuildLocalRequest(requestObject);
		TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
		FJsonSerializer::Serialize(requestObject.ToSharedRef(), Writer);
	}
	else {
		OutputString = this->request;
	}

	Request->SetContentAsString(OutputString);
	Request->OnProcessRequestComplete().BindUObject(this, &UHyperPlayLibrary::OnResponse);
	Request->ProcessRequest();
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
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(TEXT("http://localhost:9680/sendContract"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	TSharedPtr<FJsonValue> emptyRequestValue = this->CreateJsonValue(TEXT("{}"));
	TSharedPtr<FJsonObject> requestObject = emptyRequestValue->AsObject();

	TSharedPtr<FJsonValue> emptyChainValue = this->CreateJsonValue(TEXT("{}"));

	TSharedPtr<FJsonObject> chainObject = emptyChainValue->AsObject();
	chainObject->SetField(TEXT("chainId"), MakeShared<FJsonValueString>(FString::FromInt(this->chainIdVar)));
	requestObject->SetField(TEXT("chain"), MakeShared<FJsonValueObject>(chainObject));
	// above is same as rpc. consider refactoring into separate method

	requestObject->SetField(TEXT("contractAddress"), MakeShared<FJsonValueString>(this->contractAddressVar));
	requestObject->SetField(TEXT("functionName"), MakeShared<FJsonValueString>(this->functionNameVar));
	requestObject->SetField(TEXT("valueInWei"), MakeShared<FJsonValueString>(this->valueInWeiVar));
	if (this->gasLimitVar > 0) {
		requestObject->SetField(TEXT("gasLimit"), MakeShared<FJsonValueString>(FString::FromInt(this->gasLimitVar)));
	}

	//passed as an FString but should call the endpoint with Array<AbiItem>
	TSharedPtr<FJsonValue> abiItems = this->CreateJsonValue(this->abiVar);
	requestObject->SetField(TEXT("abi"), abiItems);

	TArray<TSharedPtr<FJsonValue>> paramsValueArray;
	for (const FString val : this->paramsVar) {
		TSharedPtr<FJsonValue> param = MakeShared<FJsonValueString>(val);
		paramsValueArray.Add(param);
	}
	requestObject->SetField(TEXT("params"), MakeShared<FJsonValueArray>(paramsValueArray));
	

	// below is same as rpc. consider refactoring into separate method
	FString OutputString;
	TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
	FJsonSerializer::Serialize(requestObject.ToSharedRef(), Writer);
	Request->SetContentAsString(OutputString);
	Request->OnProcessRequestComplete().BindUObject(this, &UHyperPlayLibrary::OnResponse);
	Request->ProcessRequest();
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