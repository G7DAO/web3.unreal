#include "Secp256k1Helper.h"
#include "Keccak256.h"
#include "Logging/LogMacros.h"
#include "Web3Utils.h"

/*
 * Recovers the public address from a 32 byte message hash and a hex character FString signature    
 */
FString USecp256k1Helper::RecoverAddressFromSignature(TArray<uint8> messageHash, FString signature)
{
	std::vector<uint8> msgHash;
	for (auto iter = messageHash.begin(); iter != messageHash.end(); ++iter)
	{
		uint8 char_i = *iter;
		msgHash.push_back(char_i);
	}

	FString prefix = signature.Left(2);
	FString hexPrefix("0x");
	if (prefix.Equals(hexPrefix))
	{
		signature.RightChopInline(2);
	}
	return USecp256k1Helper::RecoverPublicAddressFromSignature(&msgHash[0], signature);
}

/*
 * Calculates the Ethereum public address from a 256 bit private key byte array 
 */
FString USecp256k1Helper::CalcPublicAddressFromPrivateKey(unsigned char seckey[32]){
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	secp256k1_pubkey pubkey;
	int return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);

	FString pubkeyFString = CalcFStringPublicAddress(ctx, pubkey);
	return pubkeyFString;
}

/*
* Converts secp256k1 library public key type to an FString representing the public address
*/
FString USecp256k1Helper::CalcFStringPublicAddress(secp256k1_context* ctx, secp256k1_pubkey pubkey)
{
	//The first byte is an EC public key prefix. 0x04 for uncompressed EC points which is what ethereum uses
	unsigned char pubkeySerialized[65] = {0};
	size_t len = sizeof(pubkeySerialized);
	secp256k1_ec_pubkey_serialize(ctx, pubkeySerialized, &len, &pubkey, SECP256K1_EC_UNCOMPRESSED);
	
	uint8_t hashedPubKeyBytes[32] = { 0 };
	//We have to remove the EC public key byte prefix before hashing the public key
	Keccak256::getHash(&pubkeySerialized[1], 64, hashedPubKeyBytes);
	
	//Convert the byte array to human readable string of the byte array represented by each character in hex
	const std::string hashedPubKeyString = UWeb3Utils::hexStr(hashedPubKeyBytes, 32);
	const FString hashedPubKeyFString(hashedPubKeyString.c_str());
	FString publicKeyFinal = FString("0x") + hashedPubKeyFString.RightChop(24);
	
	/* This will clear everything from the context and free the memory */
	secp256k1_context_destroy(ctx);
	return publicKeyFinal;
}

/*
* Recovers the public address from an ECDSA signed message hash and signature using secp256k1
*/
FString USecp256k1Helper::RecoverPublicAddressFromSignature(
		unsigned char msg_hash[32],
		FString signatureHexString)
{
	unsigned char serialized_signature[65] = {0};

	UWeb3Utils::ByteArrayFromHexStr(signatureHexString, serialized_signature);

	int recId = 1 - serialized_signature[64] % 2;
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

	secp256k1_ecdsa_recoverable_signature sig;
	secp256k1_ecdsa_recoverable_signature_parse_compact(ctx, &sig, serialized_signature, recId);

	secp256k1_pubkey pubkeyThatSigned;
	secp256k1_ecdsa_recover(ctx, &pubkeyThatSigned, &sig, msg_hash);

	//output the public address that signed
	FString pubkeyFString = CalcFStringPublicAddress(ctx, pubkeyThatSigned);

	/* This will clear everything from the context and free the memory */
	//secp256k1_context_destroy(ctx);
	return pubkeyFString;
}