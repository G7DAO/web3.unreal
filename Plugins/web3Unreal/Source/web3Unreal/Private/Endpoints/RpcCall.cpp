#include "Endpoints/RpcCall.h"

URpcCall* URpcCall::RpcCall(const UObject* WorldContextObject, FString request, int32 chainId, FString chainMetadata, FString url) {

	URpcCall* RpcCallInstance = NewObject<URpcCall>();

	if(url == "http://localhost:9680/rpc")
	{
		RpcCallInstance->RequestBuilder.Set<InternalRPC>({});
		RpcCallInstance->RequestBuilder.Get<InternalRPC>().Request = request;
		RpcCallInstance->RequestBuilder.Get<InternalRPC>().ChainID = chainId;
		RpcCallInstance->RequestBuilder.Get<InternalRPC>().ChainMetadataVar = chainMetadata;
		RpcCallInstance->RequestBuilder.Get<InternalRPC>().OnCompleteDelegate.BindUObject(RpcCallInstance, &UHyperplayAsyncRequest::OnResponse);
	
		return RpcCallInstance;
	}

	RpcCallInstance->RequestBuilder.Set<ExternalRPC>({});
	RpcCallInstance->RequestBuilder.Get<ExternalRPC>().Url = url;
	RpcCallInstance->RequestBuilder.Get<ExternalRPC>().ChainID = chainId;
	RpcCallInstance->RequestBuilder.Get<ExternalRPC>().RequestString = request;
	RpcCallInstance->RequestBuilder.Get<ExternalRPC>().ChainMetadataVar = chainMetadata;
	RpcCallInstance->RequestBuilder.Get<ExternalRPC>().OnCompleteDelegate.BindUObject(RpcCallInstance, &UHyperplayAsyncRequest::OnResponse);
	
	return RpcCallInstance;
}

void URpcCall::Activate()
{
	if(RequestBuilder.IsType<InternalRPC>())
	{
		RequestBuilder.Get<InternalRPC>().ExecuteRequest();
	}
	else
	{
		RequestBuilder.Get<ExternalRPC>().ExecuteRequest();
	}
}

void URpcCall::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	Super::ProcessResponse(Response, statusCode);
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
	OnCompleted.Broadcast(ResponseText, statusCode);
}
