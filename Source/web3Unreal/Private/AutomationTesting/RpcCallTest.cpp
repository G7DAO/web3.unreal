#include "Endpoints/GetAccounts.h"
#include "Misc/AutomationTest.h"
#include "HyperPlayUtils.h"
#include "Endpoints/RpcCall.h"

BEGIN_DEFINE_SPEC(Web3RPCSpec, 
	"Web3Unreal.HyperplayRequests.RpcCall",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnAcctResponse(FString Response, int32 StatusCode);
void OnRpcResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3RPCSpec)

void Web3RPCSpec::Define()
{
	Describe("Execute RPC request tests (make sure to connect to HyperPlay before running test)",
		[this]()
	{
		LatentIt("RPC Async Node", EAsyncExecution::TaskGraph,
			FTimespan(0, 0, 30),
			[this](const FDoneDelegate TestDone)
		{
				TestDoneDelegate = TestDone;
				UGetAccounts* GetAccountsInstance = UGetAccounts::GetAccounts(nullptr, 5, "");
				GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &Web3RPCSpec::OnAcctResponse);
				GetAccountsInstance->Activate();
		});
	});
}

void Web3RPCSpec::OnAcctResponse(FString Response, int32 StatusCode)
{
	const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

	TestTrue("Rpc get accounts Request run successfully!", bWasSuccessful);
	UE_LOG(LogTemp, Display, TEXT("rpc get accounts Response: %s"), *Response);
	
	const FString request("{\"method\":\"eth_signTypedData_v3\",\"params\":[\""
		+ Response
		+ "\",\"{\\\"types\\\": {\\\"EIP712Domain\\\": [{\\\"name\\\": \\\"name\\\",\\\"type\\\": \\\"string\\\"},{\\\"name\\\": \\\"version\\\",\\\"type\\\": \\\"string\\\"}],\\\"LoginData\\\": [{\\\"name\\\": \\\"game\\\",\\\"type\\\": \\\"string\\\"},{\\\"name\\\": \\\"contents\\\",\\\"type\\\": \\\"string\\\"}]},\\\"primaryType\\\": \\\"LoginData\\\",\\\"domain\\\": {\\\"name\\\": \\\"HyperPlay\\\",\\\"version\\\": \\\"1\\\"},\\\"message\\\": {\\\"game\\\": \\\"HyperPlay FPS Demo\\\",\\\"contents\\\": \\\"Sign this message to log in!\\\"}}\"]}");
	
	UE_LOG(LogTemp, Display, TEXT("rpc signed typed data request: %s"), *request);
	
	URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
		request,
		5);
	RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &Web3RPCSpec::OnRpcResponse);
	RpcCallInstance->Activate();
}

void Web3RPCSpec::OnRpcResponse(FString Response, int32 StatusCode)
{
	const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

	TestTrue("Rpc get accounts Request run successfully!", bWasSuccessful);
	UE_LOG(LogTemp, Display, TEXT("rpc sign typed data v3 Response: %s"), *Response);
	TestDoneDelegate.Execute();
}