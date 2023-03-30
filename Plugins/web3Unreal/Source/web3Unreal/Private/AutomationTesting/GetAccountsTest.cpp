#include "Endpoints/GetAccounts.h"
#include "Misc/AutomationTest.h"
#include "HyperPlayUtils.h"

BEGIN_DEFINE_SPEC(Web3GetAccountsSpec,
				  "Web3Unreal.HyperplayRequests.GetAccounts",
				  EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3GetAccountsSpec)

void Web3GetAccountsSpec::Define()
{
	Describe("Execute GetAccounts tests (make sure to connect to HyperPlay before running test)",
		[this]()
	{
		LatentIt("GetAccounts Async Node",
			EAsyncExecution::TaskGraph, FTimespan(0, 0, 30),
			[this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			UGetAccounts* GetAccountsInstance = UGetAccounts::GetAccounts(nullptr, 5, "");
			GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &Web3GetAccountsSpec::OnResponse);
			GetAccountsInstance->Activate();
		});
	});
}

void Web3GetAccountsSpec::OnResponse(FString Response, int32 StatusCode)
{
	const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);
	
	TestTrue("Web3RPC Request run successfully!", bWasSuccessful);
	UE_LOG(LogTemp, Display, TEXT("GetAccount Response: %s"), *Response);
	TestDoneDelegate.Execute();
}