#include "Endpoints/CallContract.h"
#include "Endpoints/GetAccounts.h"
#include "Misc/AutomationTest.h"
#include "HyperPlayUtils.h"

BEGIN_DEFINE_SPEC(Web3CallContract, 
	"Web3Unreal.HyperplayRequests.CallContract",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3CallContract)

void Web3CallContract::Define()
{
	Describe("Execute CallContract request tests (make sure to connect to HyperPlay before running test)",
		[this]()
	{
		LatentIt("CallContract Async Node",
			EAsyncExecution::TaskGraph, FTimespan(0, 0, 30),
			[this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			UCallContract* GetAccountsInstance = UCallContract::CallContract(nullptr,
				"0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc",
				"name",
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
	const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

	TestTrue("CallContract Request run successfully!", bWasSuccessful);
	UE_LOG(LogTemp, Display, TEXT("CallContract Response: %s"), *Response);
	const FString CorrectName("FaucetToken");
	TestTrue("Total supply read correctly ", Response.Equals(CorrectName));
	TestDoneDelegate.Execute();
}