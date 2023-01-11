#pragma once
#include "secp256k1.h"

class Secp256k1Helper final
{
public:
	static FString CalcPublicAddressFromPrivateKey(unsigned char seckey[32]);
	static FString RecoverPublicAddressFromSignature(
		FString message,
		FString signatureHexString,
		int recid);
	static FString CalcFStringPublicAddress(secp256k1_context* ctx, secp256k1_pubkey pubkey);
};
