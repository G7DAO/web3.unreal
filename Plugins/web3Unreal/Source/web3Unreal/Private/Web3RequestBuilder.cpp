#include "Web3RequestBuilder.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HyperPlayUtils.h"

void FWeb3BaseRequest::InitializeRequest()
{
	Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	RequestObject = HyperPlayUtils::CreateJsonValue(TEXT("{}"))->AsObject();
	ChainObject = HyperPlayUtils::CreateJsonValue(TEXT("{}"))->AsObject();
	ChainObject->SetField(TEXT("chainId"), MakeShared<FJsonValueString>(FString::FromInt(ChainID)));

	// Can this be present in all requests???
	if(!ChainMetadataVar.IsEmpty())
	{
		const TSharedPtr<FJsonValue> ChainMetaDataValue = HyperPlayUtils::CreateJsonValue(ChainMetadataVar);
		if(!ChainMetaDataValue.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not parse chain metadata"));
			return;
		}
	
		ChainObject->SetField(TEXT("chainMetadata"), ChainMetaDataValue);
	}
	
	RequestObject->SetField(TEXT("chain"), MakeShared<FJsonValueObject>(ChainObject));
}

void FWeb3BaseRequest::FinalizeRequest() const
{
	Request->SetURL(RequestUrl);
	Request->OnProcessRequestComplete() = OnCompleteDelegate;
	Request->SetContentAsString(HttpContentString);
	UE_LOG(LogTemp, Warning, TEXT("Processing request in web3baserequest finalize request for %s"), *HttpContentString)
	Request->ProcessRequest();
}

void FWeb3RPCRequest::BuildRequest()
{
	RequestUrl = "http://localhost:9680/rpc";
	
	if(!Request.IsEmpty())
	{
		const TSharedPtr<FJsonValue> RPCRequestValue = HyperPlayUtils::CreateJsonValue(Request);
		if(!RPCRequestValue.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not parse the rpc request"));
			return;
		}

		RequestObject->SetField(TEXT("request"), RPCRequestValue);
	}
	
	TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&HttpContentString);
	FJsonSerializer::Serialize(RequestObject.ToSharedRef(), Writer);
}

void FWeb3ExternalRPCRequest::BuildRequest()
{
	RequestUrl = Url;
	HttpContentString = RequestString;
}

void FWeb3SendContractRequest::BuildRequest()
{
	if(RequestUrl.IsEmpty())
		RequestUrl = "http://localhost:9680/sendContract";
	
	RequestObject->SetField(TEXT("contractAddress"), MakeShared<FJsonValueString>(ContractAddressVar));
	RequestObject->SetField(TEXT("functionName"), MakeShared<FJsonValueString>(FunctionNameVar));
	RequestObject->SetField(TEXT("valueInWei"), MakeShared<FJsonValueString>(ValueInWeiVar));

	if (this->GasLimitVar > 0) {
		RequestObject->SetField(TEXT("gasLimit"), MakeShared<FJsonValueString>(FString::FromInt(GasLimitVar)));
	}

	if(!ABIVar.IsEmpty())
	{
		const TSharedPtr<FJsonValue> ABI = HyperPlayUtils::CreateJsonValue(ABIVar);
		RequestObject->SetField(TEXT("abi"), ABI);
	}

	if(ParamsVar.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> ParamsValueArray;
		for (const FString& val : ParamsVar) {
			TSharedPtr<FJsonValue> param = MakeShared<FJsonValueString>(val);
			ParamsValueArray.Add(param);
		}
	
		RequestObject->SetField(TEXT("params"), MakeShared<FJsonValueArray>(ParamsValueArray));
	}

	TSharedRef<FCondensedJsonStringWriter> Writer = FCondensedJsonStringWriterFactory::Create(&HttpContentString);
	FJsonSerializer::Serialize(RequestObject.ToSharedRef(), Writer);
}

void FWeb3CallContractRequest::BuildRequest()
{
	RequestUrl = "http://localhost:9680/callContract";
	FWeb3SendContractRequest::BuildRequest();
}
