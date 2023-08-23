Quickstart
=======================================

Installation
----------------------------

Compile from source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Close your existing C++ Unreal Engine project.
#. Create a directory in your app root called Plugins.
#. Clone with

```
git clone https://github.com/G7DAO/web3.unreal.git ./Plugins/web3Unreal
```

or if your project uses git, add as a submodule with

```
git submodule add https://github.com/G7DAO/web3.unreal.git ./Plugins/web3Unreal
```

#. Generate Visual Studio project files

#. Build through your editor

Pre-compiled from UE Marketplace
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Coming Soon!

Making your first call
----------------------------------

Get Balance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

First, let's get our rpc endpoint url so we can perform this call on the client or the server.

Head over to https://app.infura.io and create an account.

Once you have your chain specific Https url with api key, copy the following blueprint or c++ example to your project.

Before calling this function:

#. Replace https://mainnet.infura.io/v3/<API_KEY> with your rpc url.

#. Replace 0x638105AA1B69406560f6428aEFACe3DB9da83c64 with the public address whose balance you want to read


.. code-block:: cpp
    
    #include "HyperPlayUtils.h"
    #include "Endpoints/RpcCall.h"

    void OnRpcResponse(FString Response, int32 StatusCode)
    {
        const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

        UE_LOG(LogTemp, Display, TEXT("Rpc Get Balance Success: %s"), bWasSuccessful ? "true" : "false");
        UE_LOG(LogTemp, Display, TEXT("Rpc Get Balance Response: %s"), *Response);
    }

    int main(){
    const FString request("{ \"method\": \"eth_getBalance\", \"params\": [\"0x638105AA1B69406560f6428aEFACe3DB9da83c64\", \"latest\"] }");

        URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
            request,
            5,
            "",
            "https://mainnet.infura.io/v3/<API_KEY>");
        RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &OnRpcResponse);
        RpcCallInstance->Activate();
    }


The balance returned will be in hexadecimal. Once converted to decimal, the unit will be in wei.

For example, hexadecimal 0x236a4c456ef7c0 to base10 is 9968499999832000

Base10 9968499999832000 wei to ETH is 0.009968499999832 ETH

Send Token
^^^^^^^^^^

Now let's request an ERC20 transfer client side from the HyperPlay connected wallet.

Before calling this function:

#. Replace 0x8a9f58dea0cf3d92dd8963f5a0a4c7aa9fa76642 with the contract address of the ERC20 token you wish to transfer
#. Replace 0x638105AA1B69406560f6428aEFACe3DB9da83c64 with the public address you would like the HyperPlay connected wallet to send tokens too
#. Replace 1230000000000000000 with the amount of tokens to send in WEI
#. Replace the chain id (i.e. 1) in "chainId": "1" with the chain id that you would like to send the ERC20 tokens on

.. code-block:: cpp

    #include "HyperPlayUtils.h"
    #include "Endpoints/SendContract.h"

    void OnResponse(FString Response, int32 StatusCode)
    {
        const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

        UE_LOG(LogTemp, Display, TEXT("SendContract Success: %s"), bWasSuccessful ? "true" : "false");
        UE_LOG(LogTemp, Display, TEXT("SendContract Response: %s"), *Response);
    }

    int main(){
        const FString address("0x62bb848ec84D08d55Ea70a19118300bae6658F18");
        const FString amount("100000000000000000000");
        TArray<FString> params;
        params.Add(address);
        params.Add(amount);
        USendContract* SendContractInstance = USendContract::SendContract(nullptr,
            "0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc",
            "transfer",
            "",
            params,
            -1,
            "",
            5);
        SendContractInstance->GetOnCompletedDelegate().AddRaw(this, &OnResponse);
        SendContractInstance->Activate();
    }

After the user confirms this transaction in HyperPlay, this will return a transaction hash similar to 0x1b8368d5b67a914a49c76984776849ee3c56a4ac28c92d98103ef18e7215ae2b 

Finishing Up
--------------

Call the Get Balance function again server side and you should see the new updated on-chain token balance.

Congratulations! You just performed blockchain reads and writes client and server side in Unreal Engine with NO custodial wallets and NO external servers!

Next Steps
-----------
Check out our deep dive API docs or go straight to the examples