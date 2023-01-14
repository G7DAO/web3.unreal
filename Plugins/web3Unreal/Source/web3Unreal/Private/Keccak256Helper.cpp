#include "Keccak256Helper.h"
#include "Keccak256.h"
#include "Web3Utils.h"

/*
 * Hash text with Keccak256 into a 32 byte array
 */
void UKeccak256Helper::Keccak256FStringToByteArray(FString data, uint8_t *dest)
{
	std::string msg;
	for (auto iter = data.begin(); iter != data.end(); ++iter) {
		TCHAR char_i = (unsigned char) *iter;
		msg.push_back(char_i);
	}
	const uint8_t* msgUint8 = (uint8_t*)msg.c_str();
	Keccak256::getHash(msgUint8, msg.length(), dest);
}

/*
 * Computes the Keccak256 hash of a text string
 */
FString UKeccak256Helper::Keccak256(FString data) {
	uint8_t dest[32] = { 0 };
	Keccak256FStringToByteArray(data, dest);
	std::string retHex = "0x" + UWeb3Utils::hexStr(dest, 32);
	FString ret(retHex.c_str());
	return ret;
}

/*
 * Hash text with Keccak256 and return a 32 byte TArray
 */
TArray<uint8> UKeccak256Helper::Keccak256Bytes(FString data) {
	uint8_t dest[32] = { 0 };
	Keccak256FStringToByteArray(data, dest);
	TArray<uint8_t> ret;
	ret.Append(dest, 32);
	return ret;
}

/*
 * Concatenates an array of byte arrays and then hashes the result
 */
TArray<uint8> UKeccak256Helper::ConcatByteArraysAndKeccak256(TArray<FByte2DArray> byte2DArray)
{
	std::vector<uint8> msg;
	for (auto iter = byte2DArray.begin(); iter != byte2DArray.end(); ++iter)
	{
		auto arr_i = (*iter).data;
		for (auto j = arr_i.begin(); j != arr_i.end(); ++j)
		{
			msg.push_back(*j);
		}
	}
	uint8_t dest[32] = { 0 };
	Keccak256::getHash(&msg[0], msg.size(), dest);
	TArray<uint8_t> ret;
	ret.Append(dest, 32);
	return ret;
}