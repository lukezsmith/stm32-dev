# stm32-dev
A bare metal C project template and developer environment for STM32 microcontrollers using Docker and Visual Studio Code.

## Getting Started

### Dependencies
- Docker
- Visual Studio Code
- [Visual Studio Code Remote Development Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)

### Installation
To install run `git clone --recurse-submodules https://github.com/lukezsmith/stm32-dev` to clone the repository.

Following installation, open the directory in Visual Studio Code. 

Once the directory has been opened in Visual Studio Code, re-open the directory using the provided Docker container. It will take a while to install.

After this, the template is ready to use. 

### Building
The template uses CMake to build the code. 
To automate the process there is a Makefile in the root directory which can be run to automate the build.

To build the code run `make build`.

### Flashing 
Included in the Makefile is a flash command to flash the program to the STM32.

To build and flash the code run `make`.
To flash only run `make flash`.

**NOTE:** I haven't yet implemented USB pass-through for flashing (or debugging) whilst in the development container so flashing will fail if ran in the container. A workaround is to simply run the flash command from your host machine after building the project in the container.


## References
I used a couple of different repositories to build this template:
- [fcayci/stm32f4-bare-metal](https://github.com/fcayci/stm32f4-bare-metal)
    - I borrowed a lot of the build settings, libraries and helper files from this repo.
- [astroesteban/tiva/dev](https://github.com/astroesteban/tiva-dev)
    - I borrowed the docker containerisation idea from this TM4C dev environment.

