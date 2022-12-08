#include "GetAccounts.h"

UGetAccounts::UGetAccounts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UGetAccounts* UGetAccounts::GetAccounts(const UObject* WorldContextObject, int32 chainId, FString chainMetadata) {

	UGetAccounts* BlueprintNode = NewObject<UGetAccounts>();
	UGetAccounts* getAcctNode = (UGetAccounts*)PostToRpc(WorldContextObject, BlueprintNode, TEXT("{\"method\":\"eth_accounts\"}"), chainId, chainMetadata, TEXT("http://localhost:9680/rpc"), "");
	return getAcctNode;
}

void UGetAccounts::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	FString ResponseText = Response->GetContentAsString();
	const TArray<TSharedPtr<FJsonValue>> xx = this->CreateJsonValue(ResponseText)->AsArray();
	if (xx.Num() > 0) {
		OnResponseOutput.Broadcast(xx[0]->AsString(), statusCode);
	}
	else {
		OnResponseOutput.Broadcast(TEXT("ERROR: Account array was empty"), 400);
	}
}