#include "Secp256k1BpLibrary.h"
#include "Secp256k1Helper.h"


FString USecp256k1BpLibrary::RecoverAddressFromSignature(FString message, FString signature)
{
	std::string messageString = std::string(TCHAR_TO_UTF8(*message));
	return Secp256k1Helper::RecoverPublicAddressFromSignature(messageString, signature);
}