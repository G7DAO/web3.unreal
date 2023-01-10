#include "Secp256k1Helper.h"
#include "secp256k1.h"
#include "Keccak256.h"
#include "Keccak256Node.h"
#include "Logging/LogMacros.h"

/*
 * Calculates the Ethereum public address from a 256 bit private key byte array 
 */
FString Secp256k1Helper::CalcPublicAddressFromPrivateKey(unsigned char seckey[32]){
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	secp256k1_pubkey pubkey;
	int return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);
	UE_LOG(LogTemp, Display, TEXT("pubkey create return value = %d"), return_val);

	//The first byte is an EC public key prefix. 0x04 for uncompressed EC points which is what ethereum uses
	unsigned char pubkeySerialized[65] = {0};
	size_t len = sizeof(pubkeySerialized);
	secp256k1_ec_pubkey_serialize(ctx, pubkeySerialized, &len, &pubkey, SECP256K1_EC_UNCOMPRESSED);
	
	uint8_t hashedPubKeyBytes[32] = { 0 };
	//We have to remove the EC public key byte prefix before hashing the public key
	Keccak256::getHash(&pubkeySerialized[1], 64, hashedPubKeyBytes);
	
	//Convert the byte array to human readable string of the byte array represented by each character in hex
	const std::string hashedPubKeyString = UKeccak256Node::hexStr(hashedPubKeyBytes, 32);
	const FString hashedPubKeyFString(hashedPubKeyString.c_str());
	FString publicKeyFinal = FString("0x") + hashedPubKeyFString.RightChop(24);
	return publicKeyFinal;
}