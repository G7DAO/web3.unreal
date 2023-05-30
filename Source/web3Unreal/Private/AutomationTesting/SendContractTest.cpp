// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#include "Endpoints/GetAccounts.h"
#include "Misc/AutomationTest.h"
#include "HyperPlayUtils.h"
#include "Endpoints/SendContract.h"

BEGIN_DEFINE_SPEC(Web3SendContract, 
	"Web3Unreal.HyperplayRequests.SendContract",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask);
void OnResponse(FString Response, int32 StatusCode);
FDoneDelegate TestDoneDelegate;
END_DEFINE_SPEC(Web3SendContract)

void Web3SendContract::Define()
{
	Describe("Execute SendContract request tests (make sure to connect to HyperPlay before running test)",
		[this]()
	{
		LatentIt("SendContract Async Node", EAsyncExecution::TaskGraph,
			FTimespan(0, 0, 60),
			[this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			const FString address("0x62bb848ec84D08d55Ea70a19118300bae6658F18");
			const FString amount("100000000000000000000");
			TArray<FString> params;
			params.Add(address);
			params.Add(amount);
			USendContract* SendContractInstance = USendContract::SendContract(nullptr,
				"0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc",
				"mint",
				"",
				params,
				-1,
				"",
				5);
			SendContractInstance->GetOnCompletedDelegate().AddRaw(this, &Web3SendContract::OnResponse);
			SendContractInstance->Activate();
		});
			
		LatentIt("SendContract Struct Param Async Node", EAsyncExecution::TaskGraph,
			FTimespan(0, 0, 60),
			[this](const FDoneDelegate TestDone)
		{
			TestDoneDelegate = TestDone;
			const FString weaponid("0");
			const FString weapon("[\"rifle\", \"1\", \"2\", \"3\"]");
			TArray<FString> params;
			params.Add(weaponid);
			params.Add(weapon);
			USendContract* SendContractInstance = USendContract::SendContract(nullptr,
				"0x2e0Cb17ED5F24bfCBB30D61E195D90E06E388E1e",
				"setWeapon",
				"",
				params,
				-1,
				"",
				5);
			SendContractInstance->GetOnCompletedDelegate().AddRaw(this, &Web3SendContract::OnResponse);
			SendContractInstance->Activate();
		});
	});
}

void Web3SendContract::OnResponse(FString Response, int32 StatusCode)
{
	const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

	TestTrue("SendContract Request run successfully!", bWasSuccessful);
	UE_LOG(LogTemp, Display, TEXT("SendContract Response: %s"), *Response);
	TestDoneDelegate.Execute();
}