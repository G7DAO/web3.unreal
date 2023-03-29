#include "Endpoints/CallContract.h"
#include "Endpoints/GetAccounts.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(Web3RPCRequestSpec, "Web3Unreal.HyperplayRequests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3RPCRequestSpec)

void Web3RPCRequestSpec::Define()
{
	Describe("Execute RPC request tests (make sure to connect to HyperPlay before running test)", [this]()
	{
		LatentIt("GetAccount RPC", EAsyncExecution::TaskGraph, FTimespan(0, 0, 30), [this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			UGetAccounts* GetAccountsInstance = UGetAccounts::GetAccounts(nullptr, 5, "");
			GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &Web3RPCRequestSpec::OnResponse);
			GetAccountsInstance->Activate();
		});
	});
}

void Web3RPCRequestSpec::OnResponse(FString Response, int32 StatusCode)
{
	bool bWasSuccessful = true;
	if (!(StatusCode > 199 && StatusCode < 300))
	{
		bWasSuccessful = false;
	}

	TestTrue("Web3RPC Request run successfully!", bWasSuccessful);
	TestDoneDelegate.Execute();
}

BEGIN_DEFINE_SPEC(Web3CallContract, "Web3Unreal.HyperplayRequests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3CallContract)

void Web3CallContract::Define()
{
	Describe("Execute CallContract request tests (make sure to connect to HyperPlay before running test)", [this]()
	{
		LatentIt("CallContract Call", EAsyncExecution::TaskGraph, FTimespan(0, 0, 30), [this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			UCallContract* GetAccountsInstance = UCallContract::CallContract(nullptr,
				"0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc",
				"totalSupply",
				"",
				{},
				-1,
				"",
				5);
			GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &Web3CallContract::OnResponse);
			GetAccountsInstance->Activate();
		});
	});
}

void Web3CallContract::OnResponse(FString Response, int32 StatusCode)
{
	bool bWasSuccessful = true;
	if (!(StatusCode > 199 && StatusCode < 300))
	{
		bWasSuccessful = false;
	}

	TestTrue("CallContract Request run successfully!", bWasSuccessful);
	TestDoneDelegate.Execute();
}