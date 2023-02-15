#include "Web3Utils.h"

/*
 * Converts c style char array to c++ string representing the byte array in hex
 */
std::string UWeb3Utils::hexStr(unsigned char* data, int len)
{
	std::string s(len * 2, ' ');
	for (int i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}

std::string UWeb3Utils::hexStr(std::vector<unsigned char> data)
{
	return UWeb3Utils::hexStr(&data[0], data.size());
}

/*
 * Converts a string with hex chars representing a hex value to its corresponding byte array
 */
std::vector<unsigned char> UWeb3Utils::ByteArrayFromHexStr(FString hexString)
{
	std::unordered_map<wchar_t, unsigned char> hexCharToByteMap = {
		{'0', 0x00},
		{'1', 0x01},
		{'2', 0x02},
		{'3', 0x03},
		{'4', 0x04},
		{'5', 0x05},
		{'6', 0x06},
		{'7', 0x07},
		{'8', 0x08},
		{'9', 0x09},
		{'A', 0x0A},
		{'B', 0x0B},
		{'C', 0x0C},
		{'D', 0x0D},
		{'E', 0x0E},
		{'F', 0x0F}
	};
	FString hexStringUpper = hexString.ToUpper();
	std::vector<unsigned char> byteArray;
	for (auto iter = hexStringUpper.begin(); iter != hexStringUpper.end(); ++iter)
	{
		wchar_t char_i = *iter;
		++iter;
		if (!(iter != hexStringUpper.end()))
		{
			throw "Hex string is not made up of complete bytes!";
		}

		wchar_t char_iPlus1 = *iter;
		//map the character to 0xletter then shift the higher one over and bitwise or them
		auto byte_0 = hexCharToByteMap.at(char_i);
		auto byte_1 = hexCharToByteMap.at(char_iPlus1);
		unsigned char byteToAdd = (byte_0 << 4) | byte_1;
		byteArray.push_back(byteToAdd);
	}
	return byteArray;
}
/*
 * Converts TArray of bytes to c++ string representing the byte array in hex
 */
FString UWeb3Utils::ByteArrayToFString(TArray<uint8> arr)
{
	std::vector<uint8> msg;
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		uint8 char_i = *iter;
		msg.push_back(char_i);
	}
	auto msgStr = hexStr(&msg[0], msg.size());
	return FString(msgStr.c_str());
}

TArray<uint8> UWeb3Utils::GetPrivateKeyBytes(FString key)
{
	FString privateKeyValue = key.RightChop(2);
	auto privKeyVector = UWeb3Utils::ByteArrayFromHexStr(privateKeyValue);
	TArray<uint8> privateKey = UWeb3Utils::ConvertVectorToTArray(privKeyVector);
	return privateKey;
}