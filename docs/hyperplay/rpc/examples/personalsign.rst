Get Balance 
==========================

Request
----------

Signs message with wallet

There are two params

* The string to sign
* The address of the signer


.. tabs::

   .. tab:: C++
        .. code-block:: cpp

            #include "HyperPlayUtils.h"
            #include "Endpoints/RpcCall.h"

            void OnRpcResponse(FString Response, int32 StatusCode)
            {
                const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

                UE_LOG(LogTemp, Display, TEXT("Rpc Personal Sign Success: %s"), bWasSuccessful ? "true" : "false");
                UE_LOG(LogTemp, Display, TEXT("Rpc Personal Sign Response: %s"), *Response);
            }

            int main(){
            const FString request("{\"method\": \"personal_sign\",\"params\": [\"helloo!\", \"0x638105aa1b69406560f6428aeface3db9da83c64\"]}")

                URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
                    request,
                    1);
                RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &OnRpcResponse);
                RpcCallInstance->Activate();
            }

Response 
---------


.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            0x248664217cb1dfb3fa5fad290c053c9aaab8812d0fe9d7ad493b5857b4bc43e93efa51c1fdedff937d0b0919f8f6326c511e688a3fce631cd309b524f518bd081c