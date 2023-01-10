#pragma once

class Secp256k1Helper final
{
public:
	static FString CalcPublicKeyFromPrivateKey(unsigned char seckey[32]);
};
