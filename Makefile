.PHONY: config configure build release clean rebuild run lldb debug doc windows

BUILD_FOLDER = build/bin
BINARY_NAME = sandbox
BINARY_PATH = $(BUILD_FOLDER)/$(BINARY_NAME)

all: build

configure:
	@cmake . -B build -D CMAKE_BUILD_TYPE=Debug

build:
	@cmake --build build

clean:
	@ - rm -rf build

rebuild: clean configure build

run:
	@cd ./$(BUILD_FOLDER) && ./$(BINARY_NAME)

lldb:
	@cd ./$(BUILD_FOLDER) && lldb ./$(BINARY_NAME)

debug: rebuild lldb