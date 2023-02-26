#include "GetAccounts.h"
#include "HyperPlayLibrary.h"

UGetAccounts* UGetAccounts::GetAccounts(const UObject* WorldContextObject, int32 chainId, FString chainMetadata) {
	UGetAccounts* AccountsInstance = NewObject<UGetAccounts>();
	AccountsInstance->RequestBuilder.Request = TEXT("{\"method\":\"eth_accounts\"}");
	AccountsInstance->RequestBuilder.ChainID = chainId;
	AccountsInstance->RequestBuilder.ChainMetadataVar = chainMetadata;
	AccountsInstance->RequestBuilder.OnCompleteDelegate.BindUObject(AccountsInstance, &UHyperplayAsyncRequest::OnResponse);

	return AccountsInstance;
}

void UGetAccounts::Activate()
{
	RequestBuilder.ExecuteRequest();	
}

void UGetAccounts::ProcessResponse(FHttpResponsePtr Response, int32 statusCode) {
	Super::ProcessResponse(Response, statusCode);
	
	const FString ResponseText = Response->GetContentAsString();
	const TArray<TSharedPtr<FJsonValue>> xx = UHyperPlayLibrary::CreateJsonValue(ResponseText)->AsArray();
	if (xx.Num() > 0) {
		OnResponseOutput.Broadcast(xx[0]->AsString(), statusCode);
	}
	else {
		OnResponseOutput.Broadcast(TEXT("ERROR: Account array was empty"), 400);
	}
}
