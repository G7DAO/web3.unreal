#include "RpcCall.h"

#include "Web3RequestBuilder.h"

URpcCall* URpcCall::RpcCall(const UObject* WorldContextObject, FString request, int32 chainId, FString chainMetadata, FString url, FString Params) {

	URpcCall* RpcCallInstance = NewObject<URpcCall>();

	if(url == "http://localhost:9680/rpc")
	{
		FWeb3RequestBuilder<FWeb3RPCRequest> RequestBuilder;
		RequestBuilder.Request = request;
		RequestBuilder.ChainID = chainId;
		RequestBuilder.ChainMetadataVar = chainMetadata;
		RequestBuilder.ParamsStr = Params;
		RequestBuilder.OnCompleteDelegate.BindUObject(RpcCallInstance, &UHyperplayAsyncRequest::OnResponse);
		RequestBuilder.ExecuteRequest();
	
		return RpcCallInstance;
	}
	
	FWeb3RequestBuilder<FWeb3ExternalRPCRequest> RequestBuilder;
	RequestBuilder.Url = url;
	RequestBuilder.ChainID = chainId;
	RequestBuilder.RequestString = request;
	RequestBuilder.ChainMetadataVar = chainMetadata;
	RequestBuilder.OnCompleteDelegate.BindUObject(RpcCallInstance, &UHyperplayAsyncRequest::OnResponse);
	RequestBuilder.ExecuteRequest();
	
	return RpcCallInstance;
}

void URpcCall::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	const FString ResponseText = Response->GetContentAsString();
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}