CXX 			= clang++

CXXFLAGS 		= -Wall -Wextra -Wno-unused-private-field

# LLVM flags with better error handling
LLVM_CONFIG		= llvm-config
LLVM_CXXFLAGS	= $(shell $(LLVM_CONFIG) --cxxflags 2>/dev/null || echo "-I/usr/include/llvm-14 -I/usr/include/llvm-13 -I/usr/include/llvm-12 -I/usr/include/llvm-11 -I/usr/include/llvm-10 -I/usr/include/llvm-9 -I/usr/include/llvm-8 -I/usr/include/llvm-7 -I/usr/include/llvm-6 -I/usr/include/llvm-5 -I/usr/include/llvm-4 -I/usr/include/llvm-3 -I/usr/include/llvm-2 -I/usr/include/llvm-1 -I/usr/include/llvm-0 -I/usr/include/llvm")
LLVM_LDFLAGS	= $(shell $(LLVM_CONFIG) --ldflags 2>/dev/null || echo "")
LLVM_LIBS		= $(shell $(LLVM_CONFIG) --libs core irreader support 2>/dev/null || echo "-lLLVMCore -lLLVMIRReader -lLLVMSupport")

# Add LLVM flags to CXXFLAGS
CXXFLAGS += $(LLVM_CXXFLAGS)

BISONFLAGS 		= -d -v

EXEC			= vsopc

SRC				= main.cpp \
				  lexer.cpp \
				  driver.cpp \
				  parser.cpp \
				  ast.cpp \
				  semantic.cpp \
				  codegen.cpp

OBJ	  			= $(SRC:.cpp=.o)

all: check-llvm $(EXEC)

check-llvm:
	@echo "Checking LLVM installation..."
	@if ! $(LLVM_CONFIG) --version >/dev/null 2>&1; then \
		echo "Warning: llvm-config not found or not working properly."; \
		echo "Trying to compile with fallback include paths..."; \
		echo "If compilation fails, please install LLVM development tools:"; \
		echo "  Ubuntu/Debian: sudo apt-get install llvm-dev clang"; \
		echo "  macOS: brew install llvm clang"; \
		echo "  Windows: Download from https://releases.llvm.org/"; \
		echo ""; \
	fi

install-tools:
	@echo "Installing LLVM development tools..."
	@echo "On Ubuntu/Debian: sudo apt-get install llvm-dev clang"
	@echo "On macOS: brew install llvm clang"
	@echo "On Windows: Download from https://releases.llvm.org/"
	@echo ""
	@echo "Verifying installation..."
	@which llvm-config || (echo "llvm-config not found. Please install LLVM development tools." && exit 1)
	@which clang || (echo "clang not found. Please install Clang." && exit 1)
	@which llc || (echo "llc not found. Please install LLVM tools." && exit 1)

main.o: driver.hpp parser.hpp codegen.hpp

driver.o: driver.hpp parser.hpp codegen.hpp

parser.o: driver.hpp parser.hpp

lexer.o: driver.hpp parser.hpp

codegen.o: codegen.hpp ast.hpp semantic.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(LLVM_LDFLAGS) $(OBJ) $(LLVM_LIBS)

parser.cpp: parser.y
	bison $(BISONFLAGS) -o parser.cpp $^

parser.hpp: parser.y
	bison $(BISONFLAGS) -o parser.cpp $^

lexer.cpp: lexer.lex
	flex $(LEXFLAGS) -o lexer.cpp $^

clean:
	@rm -f $(EXEC)
	@rm -f $(OBJ)
	@rm -f lexer.cpp
	@rm -f parser.cpp parser.hpp location.hh
	@rm -f *.output
	@rm -f *.ll *.s

.PHONY: clean install-tools
