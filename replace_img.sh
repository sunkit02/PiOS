#!/usr/bin/sh

if [ -z $1 ]; then
  echo "Please specify path to boot sector."
  exit 1
fi

make

echo Mounting specified boot sector at $1
sudo mount $1 /mnt

echo Copying PiOS kernel image to boot sector
sudo cp build/kernel.img /mnt

echo Unmounting boot sector
sudo umount /mnt

echo Unmounted boot sector
