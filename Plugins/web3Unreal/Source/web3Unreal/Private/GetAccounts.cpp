#include "GetAccounts.h"

#include "Web3RequestBuilder.h"

UGetAccounts* UGetAccounts::GetAccounts(const UObject* WorldContextObject, int32 chainId, FString chainMetadata) {
	UGetAccounts* AccountsInstance = NewObject<UGetAccounts>();

	FWeb3RequestBuilder<FWeb3RPCRequest> RequestBuilder;
	RequestBuilder.Request = TEXT("{\"method\":\"eth_accounts\"}");
	RequestBuilder.ChainID = chainId;
	RequestBuilder.ChainMetadataVar = chainMetadata;
	RequestBuilder.OnCompleteDelegate.BindUObject(AccountsInstance, &UHyperplayAsyncRequest::OnResponse);
	RequestBuilder.ExecuteRequest();

	return AccountsInstance;
}

void UGetAccounts::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	const FString ResponseText = Response->GetContentAsString();
	const TArray<TSharedPtr<FJsonValue>> xx = UHyperPlayLibrary::CreateJsonValue(ResponseText)->AsArray();
	if (xx.Num() > 0) {
		OnResponseOutput.Broadcast(xx[0]->AsString(), statusCode);
	}
	else {
		OnResponseOutput.Broadcast(TEXT("ERROR: Account array was empty"), 400);
	}
}