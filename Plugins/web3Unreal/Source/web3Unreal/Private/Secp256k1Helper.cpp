#include "Secp256k1Helper.h"
#include "secp256k1.h"
#include "Keccak256Node.h"
#include "Logging/LogMacros.h"

FString Secp256k1Helper::CalcPublicKeyFromPrivateKey(unsigned char seckey[32]){
	/* Before we can call actual API functions, we need to create a "context". */
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	secp256k1_pubkey pubkey;
	int return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);
	UE_LOG(LogTemp, Display, TEXT("pubkey create return value = %d"), return_val);

	unsigned char pubkeySerialized[65] = {0};
	size_t len = sizeof(pubkeySerialized);
	
	secp256k1_ec_pubkey_serialize(ctx, pubkeySerialized, &len, &pubkey, SECP256K1_EC_UNCOMPRESSED);
	std::string pubkeyRaw = UKeccak256Node::hexStr(pubkeySerialized, len);
	FString pubkeyFString(pubkeyRaw.c_str());
	UE_LOG(LogTemp, Display, TEXT("public key FString not hashed or chopped = %s"), *pubkeyFString);
    FString hashedPubKey = UKeccak256Node::Keccak256(pubkeyFString);
	UE_LOG(LogTemp, Display, TEXT("public key FString hashed not chopped = %s"), *hashedPubKey);
	FString publicKeyFinal = FString("0x") + hashedPubKey.RightChop(26);
	return publicKeyFinal;
}