#include "HyperplayAsyncRequest.h"

namespace
{
	bool StatusCodeIsSuccess(int32 statusCode)
	{
		if (statusCode > 199 && statusCode < 300)
		{
			return true;
		}
		return false;
	}
}

void UHyperplayAsyncRequest::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("bWasSuccessful = %hs"), bWasSuccessful ? "true" : "false");
	
	if (bWasSuccessful) {
		const int32 statusCode = Response->GetResponseCode();
		if (!StatusCodeIsSuccess(statusCode))
		{
			this->OnFailure.Broadcast();
			return;
		}
		
		const FString ResponseText = Response->GetContentAsString();

		// JSON parsing
		TSharedPtr<FJsonValue> ParsedJSON;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseText);
		FJsonSerializer::Deserialize(Reader, ParsedJSON);
		this->ProcessResponse(Response, statusCode);

		return;
	}
	
	this->OnFailure.Broadcast();
}

void UHyperplayAsyncRequest::ProcessResponse(FHttpResponsePtr Response, int32 statusCode)
{
}

