#include "Misc/AutomationTest.h"
#include "Secp256k1Helper.h"
#include "Tests/AutomationCommon.h"
#include "Keccak256Node.h"

BEGIN_DEFINE_SPEC(Secp256k1HelperTest, "Web3Unreal.Secp256k1HelperSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
// Global variables that are shared by all tests go here
END_DEFINE_SPEC(Secp256k1HelperTest)

void Secp256k1HelperTest::Define()
{
	Describe("Test Secp256k1 Functions", [this](){
			It("Should calculate the correct public key from an ECDSA private key", [this](){
				unsigned char seckey[32] = {
					0x31, 0x5F, 0x5B, 0xDB, 0x76, 0xD0, 0x78, 0xC4,
					0x3B, 0x8A, 0xC0, 0x06, 0x4E, 0x4A, 0x01, 0x64,
					0x61, 0x2B, 0x1F, 0xCE, 0x77, 0xC8, 0x69, 0x34,
					0x5B, 0xFC, 0x94, 0xC7, 0x58, 0x94, 0xED, 0xD3,
				};
				const FString publicKey = Secp256k1Helper::CalcPublicAddressFromPrivateKey(seckey);
            	const FString CorrectPublicKey("0xDB6191D3BFCF5773F91973590BF3F072F48C2DF2");
                TestTrue("public key computed correctly", publicKey.Equals(CorrectPublicKey));
			});

		
		It("Should verify an ECDSA signature", [this](){
			std::string messageString = "\\x19Ethereum Signed Message:\n11Hello World";
			FString msg(messageString.c_str());
			FString signature("50f31864261ed750ed089309ebc8260749b97aaae5738e76f26a93db7d6d5e5f5738bb3b352be93820d5b2c6be379d57b6ebdc2aa4833b2820c042bbb251039c1c");
			int recoveryId = 1;
			FString pubAddressThatSigned = Secp256k1Helper::RecoverPublicAddressFromSignature(msg, signature, recoveryId);
			UE_LOG(LogTemp, Display, TEXT("pub address that signed = %s"), *pubAddressThatSigned);
		});
	});
}