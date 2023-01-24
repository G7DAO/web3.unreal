#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include <string>
#include <unordered_map>
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
};