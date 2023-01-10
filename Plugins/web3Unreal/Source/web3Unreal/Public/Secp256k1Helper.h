#pragma once

class Secp256k1Helper final
{
public:
	static FString CalcPublicAddressFromPrivateKey(unsigned char seckey[32]);
};
