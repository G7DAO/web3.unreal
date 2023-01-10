#include "Kismet/BlueprintFunctionLibrary.h"
#include "Keccak256Node.generated.h"

#pragma once

/**
 *
 */
UCLASS()
class UKeccak256Node : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Web3.Unreal")
		static FString Keccak256(FString data);

	static std::string hexStr(unsigned char* data, int len);
private:
	static constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
};