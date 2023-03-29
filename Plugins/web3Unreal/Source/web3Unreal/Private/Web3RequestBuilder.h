﻿#pragma once

#include "HTTP/Public/Interfaces/IHttpRequest.h"

class FWeb3BaseRequest
{
public:
	virtual ~FWeb3BaseRequest() = default;
	
	int32 ChainID;
	FString ChainMetadataVar;
	FHttpRequestCompleteDelegate OnCompleteDelegate;

protected:
	void InitializeRequest();
	void FinalizeRequest() const;
	virtual void BuildRequest() = 0;
	
	typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
	typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

	FString RequestUrl;
	TSharedPtr<FJsonObject> RequestObject;
	TSharedPtr<FJsonObject> ChainObject;
	FString HttpContentString;
	FHttpRequestPtr Request;
};

class FWeb3RPCRequest : public FWeb3BaseRequest
{
public:
	FString Request;
	FString ParamsStr;
protected:
	virtual void BuildRequest() override;
};

class FWeb3ExternalRPCRequest : public FWeb3BaseRequest
{
public:
	FString Url;
	FString RequestString;
protected:
	virtual void BuildRequest() override;
};

class FWeb3SendContractRequest : public FWeb3BaseRequest
{
public:
	FString ContractAddressVar;
	FString FunctionNameVar;
	FString ABIVar;
	FString ValueInWeiVar; //int64 is not big enough
	TArray<FString> ParamsVar;
	int32 GasLimitVar;
	
protected:
	virtual void BuildRequest() override;
};

// TODO For when implementing the call contract request 
class FWeb3CallContractRequest : public FWeb3SendContractRequest 
{
protected:
	virtual void BuildRequest() override;

};

template <typename RequestPolicy>
class FWeb3RequestBuilder : public RequestPolicy
{
public:
	void ExecuteRequest()
	{
		RequestPolicy::InitializeRequest();
		RequestPolicy::BuildRequest();
		RequestPolicy::FinalizeRequest();
	};
};

