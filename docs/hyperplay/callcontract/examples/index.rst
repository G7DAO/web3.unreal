Examples
========


Request
--------

This curl request reads the total supply of the USDT ERC20 smart contract.

The C++ example reads the name of a contract.


.. tabs::

   .. tab:: C++
        .. code-block:: cpp

            #include "HyperPlayUtils.h"
            #include "Endpoints/SendContract.h"

            void OnResponse(FString Response, int32 StatusCode)
            {
                const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

                UE_LOG(LogTemp, Display, TEXT("CallContract Success: %s"), bWasSuccessful ? "true" : "false");
                UE_LOG(LogTemp, Display, TEXT("CallContract Response: %s"), *Response);
            }

            int main(){
                UCallContract* GetAccountsInstance = UCallContract::CallContract(nullptr,
                    "0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc",
                    "name",
                    "",
                    {},
                    -1,
                    "",
                    5);
                GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &OnResponse);
                GetAccountsInstance->Activate();
            }

Response
--------

The contract name


.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            "FaucetToken"

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }

