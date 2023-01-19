#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Web3Utils.generated.h"

/**
 * Generic utility functions used by other web3 classes
 */
UCLASS()
class WEB3UNREAL_API UWeb3Utils : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
		
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Utils")
		static FString ByteArrayToFString(TArray<uint8> arr);

	static std::string hexStr(unsigned char* data, int len);
	static void ByteArrayFromHexStr(FString hexString, unsigned char* byteArray);
private:
	static constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	inline static const std::unordered_map<wchar_t, unsigned char> hexCharToByteMap = {
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
};