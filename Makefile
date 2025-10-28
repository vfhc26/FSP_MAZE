## =============== SIMPLE MANUAL Makefile ==================
## Manual config, one block per program (copy to add more)
## run by name: `make Quest`; run program: `make run Quest`
## clean by name: `make clean Quest`; build all: `make build`
## ---------------------------------------------------------

.DEFAULT_GOAL := help
.PHONY: help build run clean clean-all all $(NAME)

# Compiler settings (override on cmdline if needed)
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Werror -g
LDFLAGS  ?=

ifeq ($(OS),Windows_NT)
  EXE := .exe
else ifneq (,$(findstring MINGW,$(shell uname -s 2>/dev/null)))
  EXE := .exe
else
  EXE :=
endif

# Project layout
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj

# ----------------- USER CONFIG (edit manually) ----------------
# Program name and its source files (basenames in $(SRC_DIR))
NAME := Quest
SRCS := main.cpp source.cpp

# Derived values for this program
SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN  := $(BIN_DIR)/$(NAME)$(EXE)

# ----------------- PHONY & HELP ----------------
help:
	@echo "Manual Makefile"
	@echo
	@echo "Edit NAME and SRCS above to configure your program."
	@echo
	@echo "Examples:"
	@echo "  make $(NAME)              # build program by name"
	@echo "  make run $(NAME)          # build and run program by name"
	@echo "  make clean $(NAME)        # clean objects and binary for program"
	@echo "  make clean              # clean build contents (keeps directories)"
	@echo "  make build              # build all (here just $(NAME))"

all: help

# Ensure bin dir exists
$(BIN_DIR):
	@mkdir -p "$(BIN_DIR)"

# Ensure obj dir exists (shared for all targets)
$(OBJ_DIR):
	@mkdir -p "$(OBJ_DIR)"

# Build all configured targets (here: just one)
build: $(NAME)

# Build by name, e.g. `make $(NAME)`
$(NAME): $(BIN)

# -------- Name-dispatch helpers (run/clean by name) --------
RUN_NAME := $(word 2,$(MAKECMDGOALS))
CLEAN_NAME := $(word 2,$(MAKECMDGOALS))

# make run <Name>
run:
ifeq ($(RUN_NAME),$(NAME))
	@$(MAKE) $(BIN)
	@echo Running: $(BIN) $(ARGS)
	@"$(BIN)" $(ARGS)
else ifeq ($(strip $(RUN_NAME)),)
	$(error Usage: make run <TargetName>)
else
	$(error Unknown target name '$(RUN_NAME)'. Known: $(NAME))
endif


# make clean <Name>  or plain 'make clean' for full cleanup
clean:
ifeq ($(strip $(CLEAN_NAME)),)
	@$(MAKE) clean-all
else ifeq ($(CLEAN_NAME),$(NAME))
	@echo Cleaning program $(NAME)
	@rm -f $(OBJS) "$(BIN)" 2>/dev/null || true
else
	$(error Unknown target name '$(CLEAN_NAME)'. Known: $(NAME))
endif


# ----------------- Build rules ----------------
$(BIN): $(OBJS) | $(BIN_DIR)
	@echo Linking $@
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
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

