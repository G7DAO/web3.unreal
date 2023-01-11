#include "Keccak256Node.h"
#include "Keccak256.h"

/*
 * Converts c style char array to c++ string representing the byte array in hex
 */
std::string UKeccak256Node::hexStr(unsigned char* data, int len)
{
	std::string s(len * 2, ' ');
	for (int i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}

void UKeccak256Node::ByteArrayFromHexStr(FString hexString, unsigned char byteArray[])
{
	int byteArrayIndex = 0;
	for (auto iter = hexString.begin(); iter != hexString.end(); ++iter)
	{
		wchar_t char_i = *iter;
		++iter;
		if (!(iter != hexString.end()))
		{
			throw "Hex string is not made up of complete bytes!";
		}

		wchar_t char_iPlus1 = *iter;
		//map the character to 0xletter then shift the higher one over and bitwise or them
		auto byte_0 = hexCharToByteMap.at(char_i);
		auto byte_1 = hexCharToByteMap.at(char_iPlus1);
		unsigned char byteToAdd = (byte_0 << 2) | byte_1;
		byteArray[byteArrayIndex];
		++byteArrayIndex;
	}
}

void UKeccak256Node::HashFStringToByteArray(FString data, uint8_t *dest)
{
	auto dataLengthInBytes = data.Len();
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
FString UKeccak256Node::Keccak256(FString data) {
	uint8_t dest[32] = { 0 };
	HashFStringToByteArray(data, dest);
	std::string retHex = "0x" + hexStr(dest, 32);
	FString ret(retHex.c_str());
	return ret;
}