// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "secp256k1_recovery.h"
#include "Account.h"
#include <string>
#include <algorithm>
#include <vector>
#include "Secp256k1Helper.generated.h"


/**
 * Exposes functionality that utilizes the bitcoin core secp256k1 library to Blueprints/C++ code
 */
UCLASS()
class WEB3UNREAL_API USecp256k1Helper : public UBlueprintFunctionLibrary{
 GENERATED_BODY()
public:

 /**
 * Blueprint node that recovers signing public address given signature and message hash byte array 
 */
 UFUNCTION(BlueprintCallable, Category = "Web3.Unreal|Secp256k1")
	  static FString RecoverAddressFromSignature(TArray<uint8> message, FString signature);

 /**
 * Blueprint node that generates new random public private key 
 */
 UFUNCTION(BlueprintCallable, Category = "Web3.Unreal|Secp256k1")
   static FAccount GenerateNewAccount();

 /**
 * Blueprint node that signs message hash 32 byte array with given private key. 
 */
 UFUNCTION(BlueprintCallable, Category = "Web3.Unreal|Secp256k1")
   static FString SignMessage(TArray<uint8> messageHash, TArray<uint8> privateKey, int chainId = 1);
 
 /**
 * Get the public address from a private key 32 byte array
 */
 static FString CalcPublicAddressFromPrivateKey(unsigned char seckey[32]);

 /**
 * Static C++ function to recover the public address from signature
 */
 static FString RecoverPublicAddressFromSignature(
  unsigned char msg_hash[32],
  FString signatureHexString);

 /**
 * Convert a secp256k1_pubkey to a FString representing the public key in hex
 */
 static FString CalcFStringPublicAddress(secp256k1_context* ctx, secp256k1_pubkey pubkey);

 /**
 * Checksum encode a public key string 
 */
 static std::string ChecksumEncode(std::string hashedPubKeyString);

private:
 static bool GenerateRandomPrivateKey(secp256k1_context* ctx, unsigned char seckey[32]);
};
