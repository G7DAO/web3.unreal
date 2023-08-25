Get Accounts 
==========================

Request
----------

Get the user's currently selected address

Note that HyperPlay currently supports a single globally selected account during its connection flow. In the future, multiple account addresses will be supported.

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
                UGetAccounts* GetAccountsInstance = UGetAccounts::GetAccounts(nullptr, 1, "");
                GetAccountsInstance->GetOnCompletedDelegate().AddRaw(this, &OnResponse);
                GetAccountsInstance->Activate();
            }
    
   .. tab:: Blueprint
        .. code-block:: text

            Begin Object Class=/Script/BlueprintGraph.K2Node_AsyncAction Name="K2Node_AsyncAction_3"
            ProxyFactoryFunctionName="GetAccounts"
            ProxyFactoryClass=Class'"/Script/web3Unreal.GetAccounts"'
            ProxyClass=Class'"/Script/web3Unreal.GetAccounts"'
            NodePosX=368
            NodePosY=1264
            ErrorType=1
            NodeGuid=A68F54FE46311FC6C1EDD6B935DB9E00
            CustomProperties Pin (PinId=47B93F1E418AA43A3D49B99FBF5B9F5C,PinName="execute",PinToolTip="\nExec",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_InputAction_0 904296DF4CA20B81D7E394B69DAFB05F,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=9D0B0C694BF6FCA99B3C5EA298583CA6,PinName="then",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CallFunction_11 A43DC78948D3E5BC559EAFA820913229,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=4190722C4FC4A0FD0358A9862D84FF46,PinName="OnResponseOutput",PinFriendlyName=NSLOCTEXT("", "611327CF4C4FA8A082EAD58315C83F8A", "On Response Output"),PinToolTip="On Response Output",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CallFunction_12 C6B76BD3405EB33B8FFED1B11E4375F8,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=144510B04CCC3CE5B0520680134728C9,PinName="SelectedAccount",PinToolTip="Selected Account",Direction="EGPD_Output",PinType.PinCategory="string",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CommutativeAssociativeBinaryOperator_1 8A7A7DA4457EB0A9AF0EC4813D868185,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=F7B94F664F81B897BCECA1AA958F49DB,PinName="StatusCode",PinToolTip="Status Code",Direction="EGPD_Output",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,LinkedTo=(K2Node_CallFunction_10 BDD56EFF4EBFC2F721716CB749B253CD,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=1E3FC27C43AF33DEA0B890BE8C26AFC6,PinName="WorldContextObject",PinToolTip="World Context Object\nObject Reference",PinType.PinCategory="object",PinType.PinSubCategory="",PinType.PinSubCategoryObject=Class'"/Script/CoreUObject.Object"',PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=True,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PersistentGuid=00000000000000000000000000000000,bHidden=True,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            CustomProperties Pin (PinId=ED3BF55E43AF6863E23D3D90868DE83B,PinName="chainId",PinToolTip="Chain Id\nInteger",PinType.PinCategory="int",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,DefaultValue="5",AutogeneratedDefaultValue="1",PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
            End Object

Response 
---------

.. tabs::

   .. tab:: Response
        .. code-block:: text
            
            ["0x638105aa1b69406560f6428aeface3db9da83c64"]

    .. tab:: Response Unreal Engine C++
        .. code-block:: text 

            FString("0x638105aa1b69406560f6428aeface3db9da83c64")

   .. tab:: Error
        .. code-block:: JSON

            {
                "message": "error description here"
            }