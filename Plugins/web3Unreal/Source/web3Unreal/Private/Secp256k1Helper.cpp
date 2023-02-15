#include "Secp256k1Helper.h"
#include "Keccak256.h"
#include "Logging/LogMacros.h"
#include "Web3Utils.h"
#include "Random.h"

/*
 * Recovers the public address from a 32 byte message hash and a hex character FString signature    
 */
FString USecp256k1Helper::RecoverAddressFromSignature(TArray<uint8> messageHash, FString signature)
{
	std::vector<uint8> msgHash = UWeb3Utils::ConvertTArrayToVector(messageHash);

	FString prefix = signature.Left(2);
	FString hexPrefix("0x");
	if (prefix.Equals(hexPrefix))
	{
		signature.RightChopInline(2);
	}
	return USecp256k1Helper::RecoverPublicAddressFromSignature(&msgHash[0], signature);
}

/*
 * Calculates the Ethereum public address from a 256 bit private key byte array 
 */
FString USecp256k1Helper::CalcPublicAddressFromPrivateKey(unsigned char seckey[32]){
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	secp256k1_pubkey pubkey;
	int return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);

	FString pubkeyFString = CalcFStringPublicAddress(ctx, pubkey);
	return pubkeyFString;
}

// Implemented according to https://eips.ethereum.org/EIPS/eip-55
std::string USecp256k1Helper::ChecksumEncode(std::string addr)
{
	// address must be lowercase or hashedAddress will be incorrect
	std::transform(addr.begin(), addr.end(), addr.begin(),
	[](unsigned char c){ return std::tolower(c); });
	
	const auto hexAddrCStr = (unsigned char *)addr.c_str();
	uint8_t hashedAddress[32] = { 0 };
	Keccak256::getHash(&hexAddrCStr[0], 40, hashedAddress);
	const std::string hashedPubKeyHexString = UWeb3Utils::hexStr(hashedAddress, 32);

	std::string checksummedPubKeyHexString;
	for (auto nibbleIndex = 0; nibbleIndex < addr.length(); ++nibbleIndex)
	{
		if (std::isdigit(addr[nibbleIndex]))
		{
			checksummedPubKeyHexString.push_back(addr[nibbleIndex]);
		}
		else
		{
			auto nibble = hashedPubKeyHexString[nibbleIndex];
			const char div = '7';
			if (nibble > div)
			{
				checksummedPubKeyHexString.push_back(std::toupper(addr[nibbleIndex]));
			}
			else
			{
				checksummedPubKeyHexString.push_back(std::tolower(addr[nibbleIndex]));
			}
		}
	}
	return checksummedPubKeyHexString;
}

/*
* Converts secp256k1 library public key type to an FString representing the public address
*/
FString USecp256k1Helper::CalcFStringPublicAddress(secp256k1_context* ctx, secp256k1_pubkey pubkey)
{
	//The first byte is an EC public key prefix. 0x04 for uncompressed EC points which is what ethereum uses
	unsigned char pubkeySerialized[65] = {0};
	size_t len = sizeof(pubkeySerialized);
	secp256k1_ec_pubkey_serialize(ctx, pubkeySerialized, &len, &pubkey, SECP256K1_EC_UNCOMPRESSED);
	
	uint8_t hashedPubKeyBytes[32] = { 0 };
	//We have to remove the EC public key byte prefix before hashing the public key
	Keccak256::getHash(&pubkeySerialized[1], 64, hashedPubKeyBytes);
	
	//Convert the byte array to human readable string of the byte array represented by each character in hex
	const std::string hashedPubKeyString = UWeb3Utils::hexStr(hashedPubKeyBytes, 32).substr(24);
	//calc checksum
	const std::string encodedPubKeyHexString = USecp256k1Helper::ChecksumEncode(hashedPubKeyString);

	const FString hashedPubKeyFString(encodedPubKeyHexString.c_str());
	FString publicKeyFinal = FString("0x") + hashedPubKeyFString;
	
	/* This will clear everything from the context and free the memory */
	secp256k1_context_destroy(ctx);
	return publicKeyFinal;
}

/*
* Recovers the public address from an ECDSA signed message hash and signature using secp256k1
* signatureHexString should be 65 bytes in length
*/
FString USecp256k1Helper::RecoverPublicAddressFromSignature(
		unsigned char msg_hash[32],
		FString signatureHexString)
{
	unsigned char* serialized_signature;

	std::vector<unsigned char> byteArray = UWeb3Utils::ByteArrayFromHexStr(signatureHexString);
	serialized_signature = &byteArray[0];

	int recId = 1 - serialized_signature[64] % 2;
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

	secp256k1_ecdsa_recoverable_signature sig;
	secp256k1_ecdsa_recoverable_signature_parse_compact(ctx, &sig, serialized_signature, recId);

	secp256k1_pubkey pubkeyThatSigned;
	secp256k1_ecdsa_recover(ctx, &pubkeyThatSigned, &sig, msg_hash);

	//output the public address that signed
	FString pubkeyFString = CalcFStringPublicAddress(ctx, pubkeyThatSigned);

	/* This will clear everything from the context and free the memory */
	//secp256k1_context_destroy(ctx);
	return pubkeyFString;
}

bool USecp256k1Helper::GenerateRandomPrivateKey(secp256k1_context* ctx, unsigned char seckey[32])
{
	unsigned char randomize[32] = {0};
	if (!fill_random(randomize, 32)) {
		printf("Failed to generate randomness\n");
		return false;
	}
	
	secp256k1_context_randomize(ctx, randomize);

	/*** Key Generation ***/

	/* If the secret key is zero or out of range (bigger than secp256k1's
	 * order), we try to sample a new key. Note that the probability of this
	 * happening is negligible. */
	while (1) {
		if (!fill_random(seckey, 32)) {
			printf("Failed to generate randomness\n");
			return false;
		}
		if (secp256k1_ec_seckey_verify(ctx, seckey)) {
			break;
		}
	}
	
	return true;
}

FAccount USecp256k1Helper::GenerateNewAccount()
{
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	unsigned char seckey[32] = {0};
	if (!GenerateRandomPrivateKey(ctx, seckey))
	{
		return FAccount();
	}
	
	const std::string privKeyString = UWeb3Utils::hexStr(seckey, 32);
	const FString privKeyFString(privKeyString.c_str());
	FString privateKeyFinal = FString("0x") + privKeyFString;

	FString pubAddr = CalcPublicAddressFromPrivateKey(seckey);

	FAccount acct;
	acct.privateKey = privateKeyFinal;
	acct.publicAddress = pubAddr;
	return acct;
}

FString USecp256k1Helper::SignMessage(TArray<uint8> messageHash, TArray<uint8> privateKey, int chainId)
{
	//Before we can call actual API functions, we need to create a "context".
	secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
	
	std::vector<uint8> msgHashByteVector = UWeb3Utils::ConvertTArrayToVector(messageHash);
	unsigned char *msg_hash = &msgHashByteVector[0];
	std::vector<uint8> privateKeyByteVector = UWeb3Utils::ConvertTArrayToVector(privateKey);
	unsigned char *seckey = &privateKeyByteVector[0];

	secp256k1_ecdsa_recoverable_signature sig;
	secp256k1_ecdsa_sign_recoverable(ctx, &sig, msg_hash, seckey, NULL, NULL);

	unsigned char serialized_signature[65] = {0};
	int recoveryId = 0;
	secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx, serialized_signature, &recoveryId, &sig);

	serialized_signature[64] = (uint8)(35 + chainId * 2 + recoveryId);
	std::string hexString = UWeb3Utils::hexStr(serialized_signature, 65);
	FString ret(hexString.c_str());
	return ret;
}
