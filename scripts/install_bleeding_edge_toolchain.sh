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

# If toolchain doesn't exist in cache - build it from sources.
if [ ! -e "${HOME}"/cache/arm-none-eabi-gcc-*.tar.xz ]; then
(
	git clone https://github.com/FreddieChopin/bleeding-edge-toolchain
	cd bleeding-edge-toolchain

	{ time='0'; while true; do sleep 60; time="$((${time} + 1))"; echo "${time} minute(s)..."; done } &
	keepAlivePid="${!}"
	timeout -k 1m 50m ./build-bleeding-edge-toolchain.sh --skip-nano-libraries > >(tee /tmp/stdout.log) 2> /tmp/stderr.log | grep '[*-]\{10,10\} '
	kill "${keepAlivePid}"
	wait "${keepAlivePid}" || true
	cp arm-none-eabi-gcc-*.tar.xz "${HOME}/cache"
)
fi
echo 'Extracting arm-none-eabi-gcc-*.tar.xz...'
tar -xf ${HOME}/cache/arm-none-eabi-gcc-*.tar.xz

echo "travis_fold:end:bleeding-edge-toolchain"