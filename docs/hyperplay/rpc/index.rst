RPC Endpoint
=======================


.. toctree::
    
   self
   Get Accounts <getaccounts>


POST localhost:9680/rpc
------------------------

Parameters

request - Object used in the JSON-rpc call. See your chain's developer docs for the specific format.

chain - Object used to ensure the user is on the correct chain (follows the MetaMask specification)

* chainId - string Base 10 string matching the chain id on Chainlist
* chainMetadata (Optional) - Object used to add the chain if the user does not have the chain added to their wallet
    * chainName - string 
    * nativeCurrency - Object
    * name - string is the currency's name
    * symbol - string 2-6 characters long symbol for the chain
    * decimals - 18
    * rpcUrls - Array<string> is an array of rpc node urls that can be used to make requests. We recommend selecting a few from the listing on Chainlist
    * blockExplorerUrls (Optional) - Array<string> is an array of block explorers that can be used with the chain
    * iconUrls (Optional) - Array<string> is currently unused by MetaMask

Returns
-------

Object - See your chain's developer documentation for more details