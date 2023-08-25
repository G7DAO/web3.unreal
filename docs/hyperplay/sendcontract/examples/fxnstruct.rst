Function with Struct Param
===========================

Request
---------

This request calls /sendContract with function setWeapon on goerli contract 0x2e0Cb17ED5F24bfCBB30D61E195D90E06E388E1e, passing a struct as a param


.. tabs::

   .. tab:: C++
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
                const FString weaponid("0");
                const FString weapon("[\"rifle\", \"1\", \"2\", \"3\"]");
                TArray<FString> params;
                params.Add(weaponid);
                params.Add(weapon);
                USendContract* SendContractInstance = USendContract::SendContract(nullptr,
                    "0x2e0Cb17ED5F24bfCBB30D61E195D90E06E388E1e",
                    "setWeapon",
                    "",
                    params,
                    -1,
                    "",
                    5);
                SendContractInstance->GetOnCompletedDelegate().AddRaw(this, &Web3SendContract::OnResponse);
                SendContractInstance->Activate();
            };

Response
----------

The transaction hash

.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            {"blockHash":"0x1fbbd38dddfe8e59b00e083d64f3a1b53affee8ae7ab9e01751fbdb84791dd79","blockNumber":8938760,"contractAddress":null,"cumulativeGasUsed":502701,"effectiveGasPrice":115487007638,"from":"0xc1267ce68a966482e742eeba62f58402243a5767","gasUsed":113404,"logsBloom":"0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000","status":true,"to":"0x2e0cb17ed5f24bfcbb30d61e195d90e06e388e1e","transactionHash":"0x06dc5d62f923131ad4e0c0d9926c8fba6377d7cf7e385ff2bef45cfd17468b8d","transactionIndex":10,"type":"0x2","events":{}}

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }