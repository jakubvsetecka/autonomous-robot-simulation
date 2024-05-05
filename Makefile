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
RUN_EXPORTS=
ifdef MERLIN
	RUN_EXPORTS=@export LD_LIBRARY_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib; export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/plugins/platforms;
	PREFIX_PATH=-D CMAKE_PREFIX_PATH='/usr/local/share/Qt-5.5.1/5.5/gcc_64' executable
endif

# Because macOS uses clang as the default compiler, we need to specify g++ as the compiler
CXX_COMPILER=g++
ifeq ($(shell uname),Darwin)
	CXX_COMPILER=/usr/bin/g++
endif

# Configure the project
configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -D CMAKE_CXX_COMPILER=$(CXX_COMPILER) $(PREFIX_PATH) $(PROJECT_DIR)

# Build the project
build: configure
	@cd $(BUILD_DIR) && make

# Run the application
# /usr/local/share/Qt-5.5.1/5.5/gcc_64/plugins/platforms
run: build
	$(RUN_EXPORTS) $(BUILD_DIR)/icp-projekt
	# @$(BUILD_DIR)/icp-projekt

# Clean the build directory
clean:
	@rm -rf $(BUILD_DIR)

doxygen: clean-doc
	@doxygen Doxyfile
	@cd ./doc/latex && make
	# @pdflatex -output-directory=./doc ./doc/latex/refman.tex
	@mv ./doc/latex/refman.pdf ./doc/documentation.pdf

puml:
	@plantuml -tsvg ./doc/diagrams/*.puml
	@pandoc ./doc/draft.md -o draft.pdf

clean-doc:
	@rm -rf ./doc/latex
	@rm -rf ./doc/documentation.pdf

# Phony targets to handle commands as prerequisites
.PHONY: configure build run clean
