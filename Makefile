.DEFAULT_GOAL := help
.PHONY: help build run clean clean-all all

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Werror -g
LDFLAGS  ?=

# Detect executable suffix for Windows (Git Bash/MSYS) vs Linux
ifeq ($(OS),Windows_NT)
	EXE := .exe
else ifneq (,$(findstring MINGW,$(shell uname -s 2>/dev/null)))
	EXE := .exe
else ifneq (,$(findstring MSYS,$(shell uname -s 2>/dev/null)))
	EXE := .exe
else ifneq (,$(findstring CYGWIN,$(shell uname -s 2>/dev/null)))
	EXE := .exe
else
	EXE :=
endif

# Project layout
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj
TMP_DIR := $(BUILD_DIR)/tmp

# Ensure compiler temporary files are created in a writable directory
export TMPDIR := $(abspath $(TMP_DIR))
export TMP    := $(abspath $(TMP_DIR))
export TEMP   := $(abspath $(TMP_DIR))

# ----------------- USER CONFIG (edit manually) ----------------
# Program name and its source files (basenames in $(SRC_DIR))
NAME := main_program
SRCS := main.cpp Field.cpp Cell.cpp Player.cpp

# Derived values for this program
SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN  := $(BIN_DIR)/$(NAME)$(EXE)

# ----------------- PHONY & HELP ----------------
help:
	@echo "Manual Makefile (simple)"
	@echo
	@echo "Edit NAME and SRCS above to configure your program."
	@echo
	@echo "Commands:"
	@echo "  make build   # compile $(NAME) into $(BIN_DIR)/$(NAME)$(EXE)"
	@echo "  make run     # build and run the program (ARGS=... to pass args)"
	@echo "  make clean   # remove objects and binary"
	@echo "  make         # show this help"

all: help

# Ensure bin dir exists
$(BIN_DIR):
	@mkdir -p "$(BIN_DIR)"

# Ensure obj dir exists (shared for all targets)
$(OBJ_DIR):
	@mkdir -p "$(OBJ_DIR)"

# Ensure tmp dir exists (for compiler temps)
$(TMP_DIR):
	@mkdir -p "$(TMP_DIR)"

# Build program (single)
build: $(BIN)

# Run the program (build first)
run: $(BIN)
	@echo Running: $(BIN) $(ARGS)
	@"$(BIN)" $(ARGS)

# Clean objects and binary
clean:
	@echo Cleaning $(NAME)
	@rm -f $(OBJS) "$(BIN)"
rebuild: 
	@$(MAKE) clean 
	@$(MAKE) build

# ----------------- Build rules ----------------
$(BIN): $(OBJS) | $(BIN_DIR) $(TMP_DIR)
	@echo Linking $@
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(TMP_DIR)
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build contents but keep directory
clean-all:
	@echo "Cleaning build outputs..."
	@mkdir -p "$(BIN_DIR)" "$(OBJ_DIR)"
	@echo "- remove object files: $(OBJ_DIR)/*.o"
	@rm -f $(OBJ_DIR)/*.o
	@echo "- remove binaries: $(BIN_DIR)/*$(EXE)"
	@rm -f $(BIN_DIR)/*$(EXE)
	@echo "Done."

