// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Serialization/JsonWriter.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"

/**
 * This class is an abstract base class meant to be inherited by different types of external calls and its abstract BuildRequest member function overridden. 
 */
class FWeb3BaseRequest
{
public:
	virtual ~FWeb3BaseRequest() = default;
	
	/**
	* The chain id to send with the HyperPlay http request, if applicable
	*/
	int32 ChainID;
	/**
	* The chain metadata so the chain can be added to the users wallet if it is not already added. Only applicable for HyperPlay http request calls.
	*/
	FString ChainMetadataVar;
	/**
	* The callback to be called after the http request completes
	*/
	FHttpRequestCompleteDelegate OnCompleteDelegate;
	
	/**
	* Makes the external call to HyperPlay's http server or another rpc provider.
	*/
	void ExecuteRequest()
	{
		InitializeRequest();
		BuildRequest();
		FinalizeRequest();
	};

protected:
	void InitializeRequest();
	/**
	* Override BuildRequest function in child class to create custom external http calls
	*/
	virtual void BuildRequest() = 0;
	void FinalizeRequest() const;
	
	typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
	typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

	FString RequestUrl;
	TSharedPtr<FJsonObject> RequestObject;
	TSharedPtr<FJsonObject> ChainObject;
	FString HttpContentString;
	FHttpRequestPtr Request;
};

/**
* This is a child class of FWeb3BaseRequest that overrides BuildRequest to make calls to the /rpc endpoint of the local HyperPlay http server
*/
class FWeb3RPCRequest : public FWeb3BaseRequest
{
public:
	/**
	* The json rpc request to make, as a string
	*/
	FString Request;
protected:
	virtual void BuildRequest() override;
};

/**
* This is a child class of FWeb3BaseRequest that overrides BuildRequest to make json-rpc calls to an external rpc provider
*/
class FWeb3ExternalRPCRequest : public FWeb3BaseRequest
{
public:
	/**
	* The url of the external rpc provider
	*/
	FString Url;
	/**
	* The json rpc request to make, as a string
	*/
	FString RequestString;
protected:
	virtual void BuildRequest() override;
};

class FWeb3SendContractRequest : public FWeb3BaseRequest
{
public:
	/**
	* Contract address
	*/
	FString ContractAddressVar;
	/**
	* Function name to call send on
	*/
	FString FunctionNameVar;
	/**
	* Contract ABI, as a string
	*/
	FString ABIVar;
	/**
	* Value in wei to send with the request. int64 is not big enough so we store it as FString
	*/
	FString ValueInWeiVar;
	/**
	* Array of string params. uint32 and struct params are parsed from their string values on the http server
	*/
	TArray<FString> ParamsVar;
	/**
	* Gas limit for the transaction
	*/
	int32 GasLimitVar;
	
protected:
	virtual void BuildRequest() override;
};

/**
* FWeb3CallContractRequest is a child class of FWeb3SendContractRequest that overrides BuildRequest to make calls to the /callContract endpoint of the local HyperPlay http server. It has the same interface as FWeb3SendContractRequest.
*/
class FWeb3CallContractRequest : public FWeb3SendContractRequest 
{
protected:
	virtual void BuildRequest() override;
};

