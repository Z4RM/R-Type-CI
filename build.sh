#!/usr/bin/env bash

conan profile detect

conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install

cmake --preset conan-release

cmake --build --preset conan-release
