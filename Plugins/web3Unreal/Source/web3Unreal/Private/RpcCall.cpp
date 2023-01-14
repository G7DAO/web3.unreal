#include "RpcCall.h"

URpcCall::URpcCall(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

URpcCall* URpcCall::RpcCall(const UObject* WorldContextObject, FString request, int32 chainId, FString chainMetadata, FString url, FString params) {

	URpcCall* BlueprintNode = NewObject<URpcCall>();
	URpcCall* getAcctNode = (URpcCall*)PostToRpc(WorldContextObject, BlueprintNode, request, chainId, chainMetadata, url, params);
	return getAcctNode;
}

void URpcCall::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
		UE_LOG(LogTemp, Warning, TEXT("proccessing response in rpc call"));
	FString ResponseText = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("broadcasting"));
	OnResponseOutput.Broadcast(ResponseText, statusCode);
}