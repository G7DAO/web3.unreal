Send Transaction
==================

Request
--------

Sends coin.

Parameters

* from : Account to send from
* to: Account to send to
* value: Amount in smallest unit such as wei
* data : (optional)



.. tabs::

   .. tab:: C++
        .. code-block:: cpp

            #include "HyperPlayUtils.h"
            #include "Endpoints/RpcCall.h"

            void OnRpcResponse(FString Response, int32 StatusCode)
            {
                const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

                UE_LOG(LogTemp, Display, TEXT("Rpc eth_sendTransaction Success: %s"), bWasSuccessful ? "true" : "false");
                UE_LOG(LogTemp, Display, TEXT("Rpc eth_sendTransaction Response: %s"), *Response);
            }

            int main(){
            const FString request("{\"method\": \"eth_sendTransaction\",\"params\": [{\"from\": \"0x638105AA1B69406560f6428aEFACe3DB9da83c64\",\"to\": \"0x638105AA1B69406560f6428aEFACe3DB9da83c64\",\"value\": \"123000000000000\",\"data\": \"\"}]}")

                URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
                    request,
                    1);
                RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &OnRpcResponse);
                RpcCallInstance->Activate();
            }

Response 
------------

The transaction hash 

.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            0xa27e68e665f4bafe045dacdf2d0ace14617c02f20325d081e98dd5e3413ecece

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }