#include "Secp256k1BpLibrary.h"
#include "Secp256k1Helper.h"


FString USecp256k1BpLibrary::RecoverAddressFromSignature(TArray<uint8> messageHash, FString signature)
{
	/*std::string messageString;
	for (auto iter = message.begin(); iter != message.end(); ++iter)
	{
		messageString.push_back(*iter);
	}*/
	//std::string messageString = std::string(TCHAR_TO_UTF8(*message));

	std::vector<uint8> msgHash;
	for (auto iter = messageHash.begin(); iter != messageHash.end(); ++iter)
	{
		uint8 char_i = *iter;
		msgHash.push_back(char_i);
	}
	return Secp256k1Helper::RecoverPublicAddressFromSignature(&msgHash[0], signature);
}