#include "Endpoints/GetAccounts.h"
#include "HyperPlayUtils.h"

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
	const FString ResponseText = Response->GetContentAsString();
	const TArray<TSharedPtr<FJsonValue>> accountsArray = HyperPlayUtils::CreateJsonValue(ResponseText)->AsArray();
	if (accountsArray.Num() > 0) {
		OnResponseOutput.Broadcast(accountsArray[0]->AsString(), statusCode);
		OnCompleted.Broadcast(accountsArray[0]->AsString(), statusCode);
	}
	else {
		const auto errorMsg = TEXT("ERROR: Account array was empty");
		OnResponseOutput.Broadcast(errorMsg, 400);
		OnCompleted.Broadcast(errorMsg, 400);
	}
}
