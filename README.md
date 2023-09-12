# PiOS

### Getting Started
Ensure that you are using a Linux system (Native or WSL should both work) with
all the specified dev dependencies installed. A setup script is coming in the 
future for Ubuntu and Arch.

After setting up the environment, create a directory `build` then run `make` 
should compile a new PiOS kernel image. Running `make run` should spin up a
Raspberry Pi 1A+ emulator in QEMU and load the PiOS kernel.

To run the PiOS image on hardware, replace the `kernel.img` in the boot sector
of a copy of Rasbian with the `kernel.img` in the `build` directory 
(Not working at the moment).

For more details please read
[Raspberry Pi Bare Bones](https://wiki.osdev.org/Raspberry_Pi_Bare_Bones#Testing_your_operating_system_.28Real_Hardware.29)


### Dev Dependencies
- make (build automation)
- arm-none-eabi-gcc (compilation)
- qemu-system-arm (emulation)
- screen (serial port communication with hardware)

#### Note:
Do not run `replace_img.sh` and `restore_img.sh` if you don't know what exactly 
the scripts do!
