Add Token
==========

Request
-------

This method allows developers to add a custom token to the token list of a MetaMask or WalletConnect wallet. This method is important to game developers, because many games have dozens or even hundreds of tokens, spanning beyond the list of tokens that MetaMask or other wallets are able to auto-detect.

Parameters

* type : In the future, other standards will be supported
* address : The address of the token contract
* symbol: A ticker symbol or shorthand, up to 11 characters
* decimals: The number of token decimals
* image: A string url of the token logo

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
                const FString request("{\"method\": \"wallet_watchAsset\",\"params\": {\"type\": \"ERC20\",\"options\": {\"address\": \"0xdAC17F958D2ee523a2206206994597C13D831ec7\",\"symbol\": \"USDT\",\"decimals\": 6,\"image\": \"chrome-extension://nkbihfbeogaeaoehlefnkodbefgpgknn/images/contract/usdt.svg\"}}}")

                URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
                    request,
                    1);
                RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &OnRpcResponse);
                RpcCallInstance->Activate();
            }
    
   .. tab:: Blueprint
        .. code-block:: text

            Begin Object Class=/Script/BlueprintGraph.K2Node_AsyncAction Name="K2Node_AsyncAction_1"
            ProxyFactoryFunctionName="RpcCall"
            ProxyFactoryClass=Class'"/Script/web3Unreal.RpcCall"'
            ProxyClass=Class'"/Script/web3Unreal.RpcCall"'
            NodePosX=96
            NodePosY=1712
            NodeGuid=757636BE43792DFDE3D230911122A5CD
            CustomProperties Pin (PinId=E570FD9442397FDB8F41E4989096DAC4,PinName="execute",PinToolTip="\nExec",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_InputAction_0 904296DF4CA20B81D7E394B69DAFB05F,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=14AD45684BA18F2CE99506832A362B77,PinName="then",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=6D5200514D50BB9D6B8EE1B8E1EFB408,PinName="OnResponseOutput",PinFriendlyName=NSLOCTEXT("", "105D77014E6BC949B5EC1694C40196F8", "On Response Output"),PinToolTip="On Response Output",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CallFunction_12 C6B76BD3405EB33B8FFED1B11E4375F8,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=E31B4CA341126F494737008E2996703F,PinName="Response",PinToolTip="Response",Direction="EGPD_Output",PinType.PinCategory="string",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CommutativeAssociativeBinaryOperator_1 8A7A7DA4457EB0A9AF0EC4813D868185,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=5092D9124B92263A33DC359DCC51C290,PinName="StatusCode",PinToolTip="Status Code",Direction="EGPD_Output",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CallFunction_10 BDD56EFF4EBFC2F721716CB749B253CD,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=14FB5776463E02AC73544EB5A344206F,PinName="WorldContextObject",PinToolTip="World Context Object\nObject Reference",PinType.PinCategory="object",PinType.PinSubCategory="",PinType.PinSubCategoryObject=Class'"/Script/CoreUObject.Object"',PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=True,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=True,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=A49ADCD847E75AB151441CA9A6FEACE4,PinName="request",PinToolTip="Request\nString",PinType.PinCategory="string",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,DefaultValue="{\"method\":\"wallet_watchAsset\",\"params\":{\"type\":\"ERC20\",\"options\":{\"address\":\"0xBA62BCfcAaFc6622853cca2BE6Ac7d845BC0f2Dc\",\"symbol\":\"FAU\",\"decimals\": 18}}}",PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=872315E64070F3126AC484A2219078BD,PinName="chainId",PinToolTip="Chain Id\nInteger",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,DefaultValue="5",AutogeneratedDefaultValue="1",PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            End Object

Response 
------------


.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            true

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }