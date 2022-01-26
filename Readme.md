# TL;DR
```shell
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git

cd ~/esp/esp-idf
./install.sh esp32

. $HOME/esp/esp-idf/export.sh

idf.py build
idf.py flash /dev/ttyusb0 monitor
```
# About
This is an qualification task for the Omnic inc.
Developed for the ESP32 devkit v1 using the esp-idf framework

# How to build

## Clone this project

For example, we would use the home directory.
```shell
cd ~
git clone https://github.com/victorrar/omnic_qualification.git
```

## Install esp-idf framework (if not installed yet)

Detailed installation instructions can be found on the [official wiki](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#get-started-set-up-tools)
There is some snippets for linux from there:

### Clone framework

```shell
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

### Install tools

```shell
cd ~/esp/esp-idf
./install.sh esp32
```

Framework installed and now you're ready to go!

## Build

ESP-IDF is based on Cmake, so the project can be built in any IDE/tool that supports it.
We are recommended to use the bundled idf.py tool

### Prepare environment variables

It will point the system on idf.py and exports some other required variables

```shell
. $HOME/esp/esp-idf/export.sh
```

Also, we need to point on the IDF location

```shell
export IDF_PATH=~/esp/esp-idf
```

### Execution

#### Configuration
To configure appliaction parameters you could run `idf.py menuconfig` and change paremeters under `User configuration` menu. Then save settiong by pressing `s` and leave the configuration menu by pressing `q`.
Just mention, that **Logger tag** can't exceed 16 characters.

#### Build and deploy
To determine the flashing port you could run `ls /dev/tty*`, then plug-in your ESP32, and repeat `ls /dev/tty*` command. Port that just appeared is the port you are looking for.

```shell
idf.py build
idf.py flash -p /dev/ttyUSB0
```

### Execution

After uploading you can watch app execution by the monitor tool
```shell
idf.py monitor -p /dev/ttyUSB0
```




