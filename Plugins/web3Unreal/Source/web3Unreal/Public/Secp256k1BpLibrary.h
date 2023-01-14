#include "Kismet/BlueprintFunctionLibrary.h"
#include "Secp256k1BpLibrary.generated.h"

#pragma once

/**
 *
 */
UCLASS()
class USecp256k1BpLibrary : public UBlueprintFunctionLibrary{
 GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable, Category = "Secp256k1")
	  static FString RecoverAddressFromSignature(TArray<uint8> message, FString signature);
};