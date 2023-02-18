#include "Web3RequestBuilder.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(Web3RPCRequestSpec, "Web3Unreal.Web3RPCRequestSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnRequestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, const FDoneDelegate);
END_DEFINE_SPEC(Web3RPCRequestSpec)

void Web3RPCRequestSpec::Define()
{
	Describe("Execute RPC request tests (make sure to connect to HyperPlay before running test)", [this]()
	{
		LatentIt("GetAccount RPC", EAsyncExecution::TaskGraph, FTimespan(0, 0, 30), [this](const FDoneDelegate TestDone)
		{
			FWeb3RequestBuilder<FWeb3RPCRequest> RequestBuilder;
			RequestBuilder.Url = "http://localhost:9680/rpc";
			RequestBuilder.Request = TEXT("{\"method\":\"eth_accounts\"}");
			RequestBuilder.ChainID = 5;
			RequestBuilder.ChainMetadataVar = "";
			RequestBuilder.ParamsStrVar = "";
			RequestBuilder.OnCompleteDelegate.BindRaw(this, &Web3RPCRequestSpec::OnRequestResponse, TestDone);
			RequestBuilder.ExecuteRequest();
		});
	});
}

void Web3RPCRequestSpec::OnRequestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, const FDoneDelegate TestDone)
{
	FString ResponseText;
	
	if (bWasSuccessful) {
		const int32 statusCode = Response->GetResponseCode();

		if (!(statusCode > 199 && statusCode < 300))
		{
			bWasSuccessful = false;
		}

		if(bWasSuccessful)
		{
			 ResponseText = Response->GetContentAsString();

			// JSON parsing
			TSharedPtr<FJsonValue> ParsedJSON;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseText);
			FJsonSerializer::Deserialize(Reader, ParsedJSON);
		}
	}

	TestTrue("Web3 Request run successfully!", bWasSuccessful && !ResponseText.IsEmpty());
	TestDone.Execute();
}
