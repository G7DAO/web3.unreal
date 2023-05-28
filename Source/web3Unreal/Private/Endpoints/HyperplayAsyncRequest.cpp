#include "Endpoints/HyperplayAsyncRequest.h"
#include "HyperPlayUtils.h"


void UHyperplayAsyncRequest::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		const int32 statusCode = Response->GetResponseCode();
		if (!HyperPlayUtils::StatusCodeIsSuccess(statusCode))
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

