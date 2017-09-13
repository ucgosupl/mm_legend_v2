#!/bin/bash

################################################################################
# File:     install_bleeding_edge_toolchain.sh
# Author:   GAndaLF
# Brief:    Script for installing bleeding edge toolchain used by Travis-CI.
################################################################################

#-e  Exit immediately if a command exits with a non-zero status.
#-u  Treat unset variables as an error when substituting.
set -e
set -u

echo "travis_fold:start:bleeding-edge-toolchain"
echo "Bleeding edge toolchain"
mkdir -p "${HOME}/cache"
mkdir -p "${HOME}/toolchains"

cd "${HOME}/toolchains"

# If toolchain doesn't exist in cache - download it
if [ ! -e "${HOME}"/cache/arm-none-eabi-gcc-*.tar.xz ]; then
	mkdir bleeding-edge-toolchain
	cd bleeding-edge-toolchain
	echo 'Downloading arm-none-eabi-gcc-5_3-160412-linux-x64.tar.xz...'
	wget http://www.freddiechopin.info/en/download/category/11-bleeding-edge-toolchain?download=143%3Ableeding-edge-toolchain-160412-64-bit-linux -O arm-none-eabi-gcc-5_3-160412-linux-x64.tar.xz
	cp arm-none-eabi-gcc-*.tar.xz "${HOME}/cache"
	cd ../
fi

# build it from sources - deprecated since travis max build time is too low
# if [ ! -e "${HOME}"/cache/arm-none-eabi-gcc-*.tar.xz ]; then
# (
	# git clone https://github.com/FreddieChopin/bleeding-edge-toolchain
	# cd bleeding-edge-toolchain

	# { time='0'; while true; do sleep 60; time="$((${time} + 1))"; echo "${time} minute(s)..."; done } &
	# keepAlivePid="${!}"
	# timeout -k 1m 50m ./build-bleeding-edge-toolchain.sh --skip-nano-libraries > >(tee /tmp/stdout.log) 2> /tmp/stderr.log | grep '[*-]\{10,10\} '
	# kill "${keepAlivePid}"
	# wait "${keepAlivePid}" || true
	# cp arm-none-eabi-gcc-*.tar.xz "${HOME}/cache"
# )
# fi

pwd
echo 'Extracting arm-none-eabi-gcc-*.tar.xz...'
tar -xf ${HOME}/cache/arm-none-eabi-gcc-*.tar.xz
mv gcc-arm-none-eabi-* arm-none-eabi-gcc

echo "travis_fold:end:bleeding-edge-toolchain"