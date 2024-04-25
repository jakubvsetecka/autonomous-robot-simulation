# Project: ICP Projekt 2023/2024
# Author: Tomáš Hobza (xhobza03), Jakub Všetečka (xvsete00)
# Description: Makefile for building and running the ICP Projekt using CMake and Qt.

# Set the project directory
PROJECT_DIR := $(shell pwd)

# Set the build directory
BUILD_DIR := $(PROJECT_DIR)/build

# Default target
all: build

# For using Qt version 5.5.1 add MERLIN=1 to the make command
PREFIX_PATH=
ifdef MERLIN
PREFIX_PATH=-D CMAKE_PREFIX_PATH='/usr/local/share/Qt-5.5.1/5.5/gcc_64' executable
endif

# Configure the project
configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -D CMAKE_CXX_COMPILER=g++ $(PREFIX_PATH) $(PROJECT_DIR)

# Build the project
build: configure
	@cd $(BUILD_DIR) && make

# Run the application
run: build
	@$(BUILD_DIR)/icp-projekt

# Clean the build directory
clean:
	@rm -rf $(BUILD_DIR)

# Phony targets to handle commands as prerequisites
.PHONY: configure build run clean
