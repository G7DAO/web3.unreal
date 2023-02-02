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

## Common Issues
* When switching branches with the FPS_Demo project, be sure to right click the .uproject and ensure the right engine version is selected with "Switch Unreal Engine Version...". 
  * You should also click "Generate Visual Studio Project Files" if they are not automatically generated after the last step. 
  * Then you must build through your editor. We recommend Visual Studio 2022 or JetBrains Rider. We don't recommend Visual Studio 2019 due to its performance, but it will work as well.
* When copying the plugin source files into your plugin folder, you must "Generate Visual Studio Project Files" and build through your editor
  * We will be distributing precompiled plugin files soon so non C++ UE projects can use web3.unreal
* The main branch is intended to be up to date with the latest Unreal Engine 5 version. If you use Unreal Engine 4, try the version/4.27 branch.

## Contributing
Follow these instructions to start contributing to web3.unreal:
* Clone the repo
* Right click `FPS_Demo.uproject`, click `Switch Unreal Engine Version`, and select the engine version you would like to develop with
  * We have tested with UE 4.27 - 5.1
* Right click `FPS_Demo.uproject` and click `Generate Visual Studio Project Files`
* Open FPS_Demo.sln
* Select `Development Editor` as the build configuration
* Right click FPS_Demo in the solution explorer and select `Build`
* Launch `FPS_Demo.uproject`
* If you get a "Fetch is Incompatible" popup, click yes. 
  * We include the [Fetch plugin](https://github.com/GDi4K/unreal-fetch) as a separate option to Web3.Unreal for making 3rd party rpc calls, but it has restrictive commercial licensing (Creative Commons Non-Commercial license), error prone syntax, and lots of boilerplate. 
* In `Content/FirstPersonBP/Blueprints/FirstPersonCharacter`, there are many examples of web3 functionality that can be performed with web3.unreal
  * Check out the `Web3UnrealExamplesGraph` for a list of examples
* Get some goerli eth [here](https://goerlifaucet.com/)
* Play the game. Interacting with the items on the wall will request web3 transactions
  * You will need to have the HyperPlay desktop app running to perform this functionality. Sign up for early access [here](https://docs.google.com/forms/d/e/1FAIpQLSeBWkOkzUZ6K_i8f6181upDcOFPgGv-7A2KxsSgqUQTPz3h4Q/viewform). Otherwise you will only be able to use web3.unreal for 3rd party reads
    * HyperPlay will be fully open sourced in early 2023
  
Feel free to submit an issue or PR to web3.unreal if you cannot find the functionality that you need

## Writes
Sending transactions is made possible through the HyperPlay desktop app. This removes the complexity of Unreal game devs having to integrate complex UI and wallet integration functionality into their game. Through its integration with web2 game stores, in game overlay, and MetaMask, HyperPlay makes this experience seemless for gamers.

Simply drag one of the async write nodes into a Blueprint graph and fill out the input parameters utilizing Unreal's type system. The output pins for common transactions will be available in Unreal types as well. This call should be made client side.

If you cannot find a wrapper node to suit your specific needs, you can use the `rpc` node to perform any JSON-RPC call. The `sendContract` node also allows you to perform any smart contract interaction with a developer friendly syntax.

## Reads
Reads can be performed locally through the HyperPlay desktop app but these are subject to man in the middle (MITM) attacks. Reads can be conducted through third party nodes as well.

### Client Side Only Games 
Reads in these types of games would be similar to how client side only games are easily manipulated today since the entire game is on the user's machine. 

### Client Server Games
It is recommended for client server model games that reads be performed server side. You can use web3.unreal to connect to any third party node provider while still enjoying all the functionality and ease of use the plugin already provides. Third party node providers we recommend are [Infura](https://www.infura.io/), RPCh, [POKT Network](https://www.pokt.network/), or other RPC services.
