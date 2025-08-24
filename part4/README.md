# VSOP Compiler - Part 4: Code Generation

This is the final part of the VSOP compiler that implements LLVM IR generation.

## Features

- **Lexical Analysis** (`-l` flag): Tokenize source code
- **Parsing** (`-p` flag): Parse source code and build AST
- **Semantic Analysis** (`-c` flag): Perform semantic checking and type inference
- **LLVM IR Generation** (`-i` flag): Generate LLVM IR and output to stdout
- **Extended VSOP Support** (`-e` flag): Support for extended VSOP language features

## Usage

### Basic Usage

```bash
# Generate LLVM IR
./vsopc basic.vsop

# Generate LLVM IR and output to stdout
./vsopc -i basic.vsop

# Generate LLVM IR from extended VSOP
./vsopc -e -i basic.vsop

# Other analysis modes
./vsopc -l basic.vsop    # Lexical analysis
./vsopc -p basic.vsop    # Parsing
./vsopc -c basic.vsop    # Semantic analysis
```

## Building

### Prerequisites

- LLVM development tools
- Clang compiler
- Flex and Bison
- C++ compiler (clang++ or g++)

### Installation

```bash
# Install required tools
make install-tools

# Build the compiler
make

# Clean build artifacts
make clean
```

### Dependencies

The compiler requires:
- **LLVM**: For IR generation and optimization
- **Clang**: For final compilation and linking
- **Flex**: For lexical analysis
- **Bison**: For parsing

## Architecture

### Code Generation Pipeline

1. **Source Code** → Lexer → Parser → AST
2. **AST** → Semantic Analyzer → Annotated AST
3. **Annotated AST** → Code Generator → LLVM IR

### Key Components

- **CodeGenerator**: Main class for LLVM IR generation
- **Driver**: Orchestrates the compilation process
- **SemanticAnalyzer**: Provides type information for code generation
- **AST Classes**: Represent the program structure
