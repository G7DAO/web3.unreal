Sign-in With Ethereum
=========================

Examples
----------


.. tabs::

   .. tab:: C++
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
            const FString request("{ \"request\":{ \"method\": \"personal_sign\", \"params\": [\"localhost:8080 wants you to sign in with your Ethereum account:\n0x638105AA1B69406560f6428aEFACe3DB9da83c64\n\nSign in with Ethereum to the app.\n\nURI: http://localhost:8080\nVersion: 1\nChain ID: 1\nNonce: BIiotOrXWUldCD6Z5\nIssued At: 2023-05-09T22:09:03.350Z\", \"0x638105AA1B69406560f6428aEFACe3DB9da83c64\"] }, \"chain\":{ \"chainId\":\"1\" } }");

                URpcCall* RpcCallInstance = URpcCall::RpcCall(nullptr,
                    request,
                    5);
                RpcCallInstance->GetOnCompletedDelegate().AddRaw(this, &OnRpcResponse);
                RpcCallInstance->Activate();
            }

Sample Response
-----------------

The following signature will be returned:

``0x85583ed06e09efd25f0f5b9f948e092f70753182ccd36cfcaa5aa6f7dde6916d7a8fbc367180573f32a6f75410ee99ef202300d991cecac53a6a86baa1c2f1251b``

Overview
-----------

Sign-in with Ethereum (SIWE) is a form of authentication that enables users to control their digital identity without relying on a traditional intermediary. Here's how it generally works:

#. Ethereum Account: To use "Sign in with Ethereum," you need an Ethereum account. This typically involves creating a digital wallet that generates a unique address and cryptographic keys. The wallet stores your private key securely and allows you to interact with the Ethereum network.
#. Application Integration: Applications or services that support "Sign in with Ethereum" integrate with the Ethereum blockchain by utilizing the Ethereum Name Service (ENS) or other similar systems. ENS provides human-readable names for Ethereum addresses, making it easier for users to identify and connect their Ethereum accounts.
#. User Authentication: When you choose to sign in with Ethereum on a supported application, it initiates a request to your Ethereum wallet to authenticate your identity. The application generates a unique cryptographic challenge or request message.
#. Wallet Interaction: Your Ethereum wallet receives the authentication request message and prompts you to confirm the action. You typically need to approve the message by providing your wallet's digital signature using your private key to sign in. This signature serves as proof of your ownership of the Ethereum account.
#. Verification and Access: Once you provide the signed message, the application validates the signature using the corresponding public key associated with your Ethereum account. If the verification is successful, the application grants you access to its services, treating your Ethereum account as a form of authentication. It's important to note that while "Sign in with Ethereum" provides benefits in terms of decentralization and security; it's still essential to exercise caution and protect your private key to prevent unauthorized access to your Ethereum account.


Let's review the process within HyperPlay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This will be split into three parts
* Creating the message
* Signing the message
* Verifying the signature


.. tabs::

   .. tab:: Creating the message

        The server will create a message for the client to sign.

        .. code-block:: js

            const siwe = require("siwe");

            const message = new siwe.SiweMessage({
            domain: "localhost:8080",
            address: "0x6Ee9894c677EFa1c56392e5E7533DE76004C8D94", // address of signer
            statement: "This is a test statement",
            uri: "http://localhost:8080",
            version: "1",
            chainId: "1",
            });

            const siweMessage = message.prepareMessage();

            console.log(siweMessage);

        The siweMessage will look something like this:

        .. code-block:: text

            localhost:8080 wants you to sign in with your Ethereum account:
            0x6Ee9894c677EFa1c56392e5E7533DE76004C8D94

            This is a test statement

            URI: http://localhost:8080
            Version: 1
            Chain ID: 1
            Nonce: BIiotOrXWUldCD6Z5
            Issued At: 2023-05-09T22:09:03.350Z

        Or

        .. code-block:: text 

            localhost:8080 wants you to sign in with your Ethereum account:\n0x638105AA1B69406560f6428aEFACe3DB9da83c64\n\nSign in with Ethereum to the app.\n\nURI: http://localhost:8080\nVersion: 1\nChain ID: 1\nNonce: BIiotOrXWUldCD6Z5\nIssued At: 2023-05-09T22:09:03.350Z

Conclusion 
-------------

By leveraging the power of Ethereum's blockchain technology, this decentralized login mechanism offers enhanced security, data privacy, and user control. It streamlines the authentication process, promoting interoperability and convenience across various platforms. Moreover, the trust and transparency inherent in Ethereum's blockchain foster confidence in the authentication process.

Sources
----------

* https://eips.ethereum.org/EIPS/eip-191
* https://github.com/spruceid/siwe-quickstart/blob/main/01_frontend/src/index.js
* https://github.com/spruceid/siwe-quickstart/blob/main/02_backend/src/index.js

