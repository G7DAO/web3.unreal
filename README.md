# web3.unreal

web3.unreal is the first plugin to bring true web3 functionality to desktop games built with Unreal Engine. Start making reads and writes to any EVM compatible blockchain in minutes with globally available async blueprint nodes.

This project is free and open source. It will continue to evolve to fit your needs.

[<img alt="Discord" src="https://img.shields.io/discord/593655374469660673.svg?style=for-the-badge&label=Discord&logo=discord" height="20">](https://discord.gg/Vx4ky6ZbAK)
[<img alt="Twitter" src="https://img.shields.io/twitter/follow/espadrine.svg?style=for-the-badge&label=Twitter&color=1DA1F2" height="20">](https://twitter.com/HyperPlayGaming)

## Documentation
https://docs.hyperplaygaming.com/

## Installation
Follow these instructions to install the web3.unreal plugin:

* Close your existing Unreal Engine app.
* Create a directory in your app root called `Plugins`.
* Download [this](https://github.com/G7DAO/web3.unreal/archive/main.zip) GitHub repository and unzip.
* Copy `web3.unreal-main/Plugins/web3Unreal` of the repository to above created `Plugins` directory.
* Start your app & it will ask to compile the plugin. Proceed with that.
* You might need to [setup Visual Studio](https://docs.unrealengine.com/en-US/ProductionPipelines/DevelopmentSetup/VisualStudioSetup/index.html) for Unreal Engine.

## Writes
Sending transactions is made possible through the HyperPlay desktop app. This removes the complexity of Unreal game devs having to integrate complex UI and wallet integration functionality into their game. Through its integration with web2 game stores, in game overlay, and MetaMask, HyperPlay makes this experience seemless for gamers.

Simply drag one of the async write nodes into a Blueprint graph and fill out the input parameters utilizing Unreal's type system. The output pins for common transactions will be available in Unreal types as well. This call should be made client side.

If you cannot find a wrapper node to suit your specific needs, you can use the `rpc` node to perform any JSON-RPC call. The `sendContract` node also allows you to perform any smart contract interaction with a developer friendly syntax.

## Reads
Reads can be performed locally through the HyperPlay desktop app but these are subject to man in the middle (MITM) attacks. Reads can be conducted through third party nodes as well.

### Client Side Only Games 
Reads in these types of games would be similar to how client side only games are easily manipulated today since the entire game is on the user's machine. 

### Client Server Games
It is recommended for client server model games that reads be performed server side. You can use web3.unreal to connect to any third party node provider while still enjoying all the functionality and ease of use the plugin already provides. Third party node providers we recommend are [Infura](https://www.infura.io/) RPCh, [POKT Network](https://www.pokt.network/), or other RPC services.
