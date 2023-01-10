.PHONY: config configure build release clean rebuild run lldb debug doc windows

BUILD_SYSTEM = Ninja
XCODE_BUILD_SYSTEM = Xcode
BACKUP_BUILD_SYSTEM = 'Unix Makefiles'
WINDOWS_BUILD_SYSTEM = 'MinGW Makefiles'
BUILD_FOLDER = build/bin
BINARY_NAME = sandbox
BINARY_PATH = $(BUILD_FOLDER)/$(BINARY_NAME)

all: build

configure:
	@cmake . -B build -D CMAKE_BUILD_TYPE=Debug -G $(BUILD_SYSTEM)

xconfigure:
	@cmake . -B build -D CMAKE_BUILD_TYPE=Debug -G $(XCODE_BUILD_SYSTEM)

bconfigure:
	@cmake . -B build -D CMAKE_BUILD_TYPE=Debug -G $(BACKUP_BUILD_SYSTEM)

wconfigure:
	@cmake . -B build -D CMAKE_PREFIX_PATH=/c/cmake -G $(WINDOWS_BUILD_SYSTEM)

build:
	@cmake --build build

install:
	@cmake --install build

clean:
	@ - rm -rf build

rebuild: clean configure build install
brebuild: clean bconfigure build install
wrebuild: clean wconfigure build install

run:
	@cd ./$(BUILD_FOLDER) && ./$(BINARY_NAME)

lldb:
	@cd ./$(BUILD_FOLDER) && lldb ./$(BINARY_NAME)

debug: rebuild lldb

doc:
	@cd ./goon/doc/; ./update_doc.sh; cd -

test:
	@cd ./build && ctest --output-on-failure; cd -
vtest:
	@cd ./build && ctest --output-on-failure --verbose; cd -
