#include "Misc/AutomationTest.h"
#include "Secp256k1Helper.h"
#include "Tests/AutomationCommon.h"
#include "Keccak256Helper.h"
#include "Web3Utils.h"

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
				const FString publicKey = USecp256k1Helper::CalcPublicAddressFromPrivateKey(seckey);
            	const FString CorrectPublicKey("0xdb6191d3bFcf5773F91973590bF3F072F48c2df2");
                TestTrue("public key computed correctly", publicKey.Equals(CorrectPublicKey));
			});

		

		It("Should verify an ECDSA signature", [this](){
			std::string msgPrefix = "\x19";
			std::string messageString = msgPrefix + "Ethereum Signed Message:\n11Hello World";
			FString msg(messageString.c_str());
			TArray<uint8> msgBytesHash = UKeccak256Helper::Keccak256Bytes(msg);
			FString signature("50f31864261ed750ed089309ebc8260749b97aaae5738e76f26a93db7d6d5e5f5738bb3b352be93820d5b2c6be379d57b6ebdc2aa4833b2820c042bbb251039c1c");
			FString pubAddressThatSigned = USecp256k1Helper::RecoverAddressFromSignature(msgBytesHash, signature);
			UE_LOG(LogTemp, Display, TEXT("pub address that signed = %s"), *pubAddressThatSigned);
			const FString CorrectPublicKey("0xdb6191d3bFcf5773F91973590bF3F072F48c2df2");
			TestTrue("public key computed correctly", pubAddressThatSigned.Equals(CorrectPublicKey));
		});
		
		It("Should generate an ECDSA signature and recover the signing public address", [this](){
			auto Acct = USecp256k1Helper::GenerateNewAccount();

			std::string msgPrefix = "\x19";
			std::string messageString = msgPrefix + "Ethereum Signed Message:\n11Hello World";
			FString msg(messageString.c_str());
			TArray<uint8> msgBytesHash = UKeccak256Helper::Keccak256Bytes(msg);

			TArray<uint8> privateKey = UWeb3Utils::GetPrivateKeyBytes(Acct.privateKey);
			FString signature = USecp256k1Helper::SignMessage(msgBytesHash, privateKey, 1);

			FString pubAddressThatSigned = USecp256k1Helper::RecoverAddressFromSignature(msgBytesHash, signature);
			UE_LOG(LogTemp, Display, TEXT("pub address that signed = %s"), *pubAddressThatSigned);

			UE_LOG(LogTemp, Display, TEXT("correct pub address = %s"), *(Acct.publicAddress));
			TestTrue("public key computed correctly", pubAddressThatSigned.Equals(Acct.publicAddress));
		});

		It("Should checksum encode an address", [this]()
		{
			std::string addr = "28A826A70DFCBBA87621251DE22A055DA015C407";
			std::string encodedAddr = USecp256k1Helper::ChecksumEncode(addr);
			FString encodedAddrFString(encodedAddr.c_str());
			UE_LOG(LogTemp, Display, TEXT("encoded address = %s"), *(encodedAddrFString));
			std::string correctAddr = "28A826A70dfcBBa87621251DE22a055DA015C407";
			TestTrue("address encoded correctly", encodedAddr._Equal(correctAddr));
		});
	});
}