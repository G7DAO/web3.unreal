// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
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
		
	/**
	* Blueprint function that converts TArray of bytes to c++ string representing the byte array in hex
	*/
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Utils")
		static FString ByteArrayToFString(TArray<uint8> arr);
	
	/**
	* Blueprint function that converts an FString with hex representation of a private key into a byte TArray
	*/
	UFUNCTION(BlueprintPure, Category = "Web3.Unreal|Types")
		static TArray<uint8> GetPrivateKeyBytes(FString key);

	/**
	* Converts c style char array to c++ string representing the byte array in hex
	*/
	static std::string hexStr(unsigned char* data, int len);

	/**
	* Converts vector char array to c++ string representing the byte array in hex
	*/
	static std::string hexStr(std::vector<unsigned char> data);

	/**
	* Converts a string with hex chars representing a hex value to its corresponding byte array
	*/
	static std::vector<unsigned char> ByteArrayFromHexStr(FString hexString);

	/**
	* Generic static cpp function that converts a vector to a TArray
	*/
	template< typename T>
	static TArray<T> ConvertVectorToTArray(std::vector<T> vec){
		TArray<T> arr;
		arr.SetNumUninitialized(vec.size());

		for(int i=0; i< vec.size(); i++){
			arr[i] = vec[i];
		}
		return arr;
	}
	
	/**
	* Generic static cpp function that converts a TArray to a vector
	*/
	template< typename T>
	static std::vector<T> ConvertTArrayToVector(TArray<T> byteArray){
		std::vector<T> byteVector;
		for (auto iter = byteArray.begin(); iter != byteArray.end(); ++iter)
		{
			T char_i = *iter;
			byteVector.push_back(char_i);
		}
		return byteVector;
	}
private:
	static constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
};