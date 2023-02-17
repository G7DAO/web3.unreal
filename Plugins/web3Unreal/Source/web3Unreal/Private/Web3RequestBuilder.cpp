﻿#include "Web3RequestBuilder.h"
#include "Runtime/Online/HTTP/Public/Http.h"

namespace RequestBuilderUtils
{
	TSharedPtr<FJsonValue> CreateJsonValue(FString obj) {
		TSharedPtr<FJsonValue> val;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(obj);
		FJsonSerializer::Deserialize(Reader, val);
		return val;
	}
}

void FWeb3BaseRequest::InitializeRequest()
{
	Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	RequestObject = RequestBuilderUtils::CreateJsonValue(TEXT("{}"))->AsObject();
	ChainObject = RequestBuilderUtils::CreateJsonValue(TEXT("{}"))->AsObject();
	ChainObject->SetField(TEXT("chainId"), MakeShared<FJsonValueString>(FString::FromInt(ChainID)));
}

void FWeb3BaseRequest::FinalizeRequest() const
{
	Request->OnProcessRequestComplete() = OnCompleteDelegate;
	Request->SetContentAsString(HttpContentString);
	Request->ProcessRequest();
}

void FWeb3RPCRequest::BuildRequest()
{
	if(!ChainMetadataVar.IsEmpty())
	{
		const TSharedPtr<FJsonValue> ChainMetaDataValue = RequestBuilderUtils::CreateJsonValue(ChainMetadataVar);
		if(!ChainMetaDataValue.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not parse chain metadata"));
			return;
		}
	
		ChainObject->SetField(TEXT("chainMetadata"), ChainMetaDataValue);
	}

	RequestObject->SetField(TEXT("chain"), MakeShared<FJsonValueObject>(ChainObject));

	if(!Request.IsEmpty())
	{
		const TSharedPtr<FJsonValue> RPCRequestValue = RequestBuilderUtils::CreateJsonValue(Request);
		if(!RPCRequestValue.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not parse the rpc request"));
			return;
		}

		RequestObject->SetField(TEXT("request"), RPCRequestValue);
	}

	if(!ParamsStrVar.IsEmpty())
	{
		const TSharedPtr<FJsonValue> RPCParamsValue = RequestBuilderUtils::CreateJsonValue(ParamsStrVar);
		if(!RPCParamsValue.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not parse the rpc params"));
			return;
		}
	
		RequestObject->SetField(TEXT("params"), RPCParamsValue);
	}

	TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&HttpContentString);
	FJsonSerializer::Serialize(RequestObject.ToSharedRef(), Writer);
}

void FWeb3PExternalRPCRequest::BuildRequest()
{
	HttpContentString = RequestString;
}

void FWeb3SendContractRequest::BuildRequest()
{
	RequestObject->SetField(TEXT("contractAddress"), MakeShared<FJsonValueString>(ContractAddressVar));
	RequestObject->SetField(TEXT("functionName"), MakeShared<FJsonValueString>(FunctionNameVar));
	RequestObject->SetField(TEXT("valueInWei"), MakeShared<FJsonValueString>(ValueInWeiVar));

	if (this->GasLimitVar > 0) {
		RequestObject->SetField(TEXT("gasLimit"), MakeShared<FJsonValueString>(FString::FromInt(GasLimitVar)));
	}

	const TSharedPtr<FJsonValue> ABI = RequestBuilderUtils::CreateJsonValue(ABIVar);
	RequestObject->SetField(TEXT("abi"), ABI);

	TArray<TSharedPtr<FJsonValue>> ParamsValueArray;
	for (const FString& val : ParamsVar) {
		TSharedPtr<FJsonValue> param = MakeShared<FJsonValueString>(val);
		ParamsValueArray.Add(param);
	}
	
	RequestObject->SetField(TEXT("params"), MakeShared<FJsonValueArray>(ParamsValueArray));

	TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&HttpContentString);
	FJsonSerializer::Serialize(RequestObject.ToSharedRef(), Writer);
}