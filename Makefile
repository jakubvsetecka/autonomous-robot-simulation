# Project: ICP Projekt 2023/2024
# Author: Tomáš Hobza (xhobza03), Jakub Všetečka (xvsete00)
# Description: Makefile for building and running the ICP Projekt using CMake and Qt.

# Set the project directory
PROJECT_DIR := $(shell pwd)

# Set the build directory
BUILD_DIR := $(PROJECT_DIR)/build

# Default target
all: build

# Configure the project
configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -D CMAKE_CXX_COMPILER=/usr/bin/g++ $(PROJECT_DIR)

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
