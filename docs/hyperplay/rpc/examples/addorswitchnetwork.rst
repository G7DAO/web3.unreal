Add or Switch Network
======================

Request
----------

Leveraging EIP-3085, HyperPlay can pass requests to add a custom network, or switch to the appropriate network, for the user's MetaMask or WalletConnect wallet.

Network information, including a directory of public RPC endpoints, can be found here.


.. tabs::

   .. tab:: C++
        .. code-block:: cpp

            #include "Endpoints/GetAccounts.h"
            #include "HyperPlayUtils.h"

            void OnResponse(FString Response, int32 StatusCode)
            {
                const bool bWasSuccessful = HyperPlayUtils::StatusCodeIsSuccess(StatusCode);

                UE_LOG(LogTemp, Display, TEXT("GetAccounts Success: %s"), bWasSuccessful ? "true" : "false");
                UE_LOG(LogTemp, Display, TEXT("GetAccounts Response: %s"), *Response);
            }

            int main(){
            FString chainMetadata("{\"chainId\":\"137\",\"chainMetadata\":{\"chainName\":\"Polygon\",\"nativeCurrency\":{\"name\":\"MATIC\",\"symbol\":\"MATIC\",\"decimals\":18},\"rpcUrls\":[\"https://polygon-rpc.com\"]}}");
            UGetAccounts* GetAccountsInstance = UGetAccounts::GetAccounts(nullptr, 137, chainMetadata);
            GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &OnResponse);
            GetAccountsInstance->Activate();
            }
    
   .. tab:: Blueprint
        .. code-block:: text

            Begin Object Class=/Script/BlueprintGraph.K2Node_AsyncAction Name="K2Node_AsyncAction_8"
            ProxyFactoryFunctionName="GetAccounts"
            ProxyFactoryClass=Class'"/Script/web3Unreal.GetAccounts"'
            ProxyClass=Class'"/Script/web3Unreal.GetAccounts"'
            NodePosX=-192
            NodePosY=1440
            ErrorType=3
            NodeGuid=F50862694C93FD8DA86577BA77C338CC
            CustomProperties Pin (PinId=47B93F1E418AA43A3D49B99FBF5B9F5C,PinName="execute",PinToolTip="\nExec",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=9D0B0C694BF6FCA99B3C5EA298583CA6,PinName="then",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=4190722C4FC4A0FD0358A9862D84FF46,PinName="OnResponseOutput",PinFriendlyName="On Response Output",PinToolTip="On Response Output",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=144510B04CCC3CE5B0520680134728C9,PinName="SelectedAccount",PinToolTip="Selected Account",Direction="EGPD_Output",PinType.PinCategory="string",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=F7B94F664F81B897BCECA1AA958F49DB,PinName="StatusCode",PinToolTip="Status Code",Direction="EGPD_Output",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=1E3FC27C43AF33DEA0B890BE8C26AFC6,PinName="WorldContextObject",PinToolTip="World Context Object\nObject Reference",PinType.PinCategory="object",PinType.PinSubCategory="",PinType.PinSubCategoryObject=Class'"/Script/CoreUObject.Object"',PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=True,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=True,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=ED3BF55E43AF6863E23D3D90868DE83B,PinName="chainId",PinToolTip="Chain Id\nInteger",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,DefaultValue="56",AutogeneratedDefaultValue="1",PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=1A7D552E4D575F299CEFCAB1A21BAC3C,PinName="chainMetadata",PinToolTip="Chain Metadata\nString",PinType.PinCategory="string",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,DefaultValue="{\"chainName\": \"Binance Smart Chain\", \"nativeCurrency\": {\"name\": \"Binance Coin\", \"symbol\": \"BNB\", \"decimals\": 18}, \"rpcUrls\": [\"https://bsc-dataseed4.binance.org\"], \"blockExplorerUrls\": [\"https://bscscan.com\"]}",PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            End Object

Response 
---------


.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            ["0x638105AA1B69406560f6428aEFACe3DB9da83c64"]

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }