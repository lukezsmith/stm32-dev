# stm32-dev
A bare metal C project template and development environment for STM32 microcontrollers using Docker and Visual Studio Code. This template includes the GoogleTest testing framework and HAL/CMSIS drivers.

## Getting Started

### Dependencies
- Docker
- Visual Studio Code
- [Visual Studio Code Remote Development Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)

### Installation
To install run `git clone https://github.com/lukezsmith/stm32-dev` to clone the repository.

Following installation, open the directory in Visual Studio Code. 

Once the directory has been opened in Visual Studio Code, re-open the directory using the provided Docker container. It will take a while to install.

### Configuration
There are a number of configurable properties within the template.

#### Project/Executable Name
To rename the project and executable edit the CMakeLists.txt file in the root directory. 

#### Adding Test Modules
To test new modules it is necessary to follow these steps:
1. Copy the `src/modules/simple_module/` folder to `src/modules/<your_module_name>/`.
2. Rename `src/modules/<your_module_name>/simple_module.c` to `src/modules/<your_module_name>/your_module_name.c`
3. Edit `src/modules/<your_module_name>/CMakeLists.txt` so `<your-module-name>` is the `MODULE_NAME` variable.
4. Append `add_subdirectory(<your-module-name>)` to `src/modules/CMakeLists.txt`.
5. Create the file test/test_<your_module_name>.c and add the following lines to `test/CMakeLists.txt`:   
`list(APPEND tests_names "test_<your_module_name>")`
`list(APPEND tests_flags " ")`
#### HAL Drivers
In `CMakeLists.txt` only a subset of HAL drivers have been added to the executable build. It may be necessary to update this list if you use a HAL driver that is not already included in the executable. 
**Note**: To use the HAL driver you will also need to enable it in the `include/stm32f4xx_hal_conf.h` file, also.

### Building
The template uses CMake to build the code. 
To automate the process there is a Makefile in the root directory which can be run to automate the build.

This template has cross-compilation set up. There is a test build which compiles on the host machine. I use this to unit test the code. To run this simply run `make` or `make BUILD_TYPE=test` in the terminal from the root directory of the repository. The build will be saved in `/build/test`.

To build for the STM32 microcontroller run `make BUILD_TYPE=release`. The build will be saved in `/build/release`.

### Testing
This template includes GoogleTest. The process for adding test modules is explained above. Testing runs automatically when the test target is built with `make BUILD_TYPE=test`. There is also a Visual Studio Code Task included with this template that automatically runs the test build (and associated tests) when the task is run. For me the keyboard shortcut to run this task is `CMD+SHIFT+B`. This task can be found in `/.vscode/tasks.json`.

### Flashing 
Included in the Makefile is a flash command to flash the program to the STM32.

To flash the release build to the microcontroller run `make flash`.

**NOTE:** I haven't yet implemented USB pass-through for flashing (or debugging) whilst in the development container so flashing will fail if ran in the container. A workaround is to simply run the flash command from your host machine after building the project in the container.


## References
I used a couple of different repositories to build this template:
- [fcayci/stm32f4-bare-metal](https://github.com/fcayci/stm32f4-bare-metal)
    - I borrowed a lot of the build settings, libraries and helper files from this repo.
- [astroesteban/tiva/dev](https://github.com/astroesteban/tiva-dev)
    - I borrowed the docker containerisation idea from this TM4C dev environment.
- [rgujju/STM32_Base_Project](https://github.com/rgujju/STM32_Base_Project)
    - I borrowed the test module collation idea from this unity-based project template.

