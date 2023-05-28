#include "Misc/AutomationTest.h"
#include "Keccak256Helper.h"
#include "Tests/AutomationCommon.h"

BEGIN_DEFINE_SPEC(Keccak256Spec, "Web3Unreal.KeccackSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
// Global variables that are shared by all tests go here
END_DEFINE_SPEC(Keccak256Spec)

void Keccak256Spec::Define()
{
    Describe("Compute Keccak256 Hash", [this](){
            It("Should compute hello world hash correctly", [this](){
                const FString Data("hello world");
            	const FString Hash = UKeccak256Helper::Keccak256(Data);
            	const FString CorrectHash("0x47173285A8D7341E5E972FC677286384F802F8EF42A5EC5F03BBFA254CB01FAD");
            	UE_LOG(LogTemp, Display, TEXT("hash = %s and correct hash = %s"), *(Hash), *CorrectHash);
                TestTrue("keccak256 hash computed correctly", Hash.Equals(CorrectHash));
            });
    });
}