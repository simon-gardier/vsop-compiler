# VSOP Compiler - Part 4: Code Generation

This is the final part of the VSOP compiler that implements LLVM IR generation and native executable compilation.

## Features

- **Lexical Analysis** (`-l` flag): Tokenize source code
- **Parsing** (`-p` flag): Parse source code and build AST
- **Semantic Analysis** (`-c` flag): Perform semantic checking and type inference
- **LLVM IR Generation** (`-i` flag): Generate LLVM IR and output to stdout
- **Native Executable Generation** (default): Generate native executable from source
- **Extended VSOP Support** (`-e` flag): Support for extended VSOP language features

## Usage

### Basic Usage

```bash
# Generate native executable (default behavior)
./vsopc source.vsop

# Generate native executable from extended VSOP
./vsopc -e source.vsop

# Generate LLVM IR and output to stdout
./vsopc -i source.vsop

# Generate LLVM IR from extended VSOP
./vsopc -e -i source.vsop

# Other analysis modes
./vsopc -l source.vsop    # Lexical analysis
./vsopc -p source.vsop    # Parsing
./vsopc -c source.vsop    # Semantic analysis
```

### Examples

```bash
# Compile a VSOP program to native executable
./vsopc examples/hello.vsop
# Creates: examples/hello (executable)

# Generate LLVM IR for debugging
./vsopc -i examples/hello.vsop
# Outputs LLVM IR to stdout

# Use with extended VSOP features
./vsopc -e -i extended_program.vsop
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
4. **LLVM IR** → LLVM Backend → Native Assembly
5. **Assembly** → Linker → Native Executable

### Key Components

- **CodeGenerator**: Main class for LLVM IR generation
- **Driver**: Orchestrates the compilation process
- **SemanticAnalyzer**: Provides type information for code generation
- **AST Classes**: Represent the program structure

## LLVM IR Structure

The generated LLVM IR follows the VSOP object model:

- **Class Structures**: Each VSOP class becomes a LLVM struct
- **Vtables**: Method dispatch tables for dynamic dispatch
- **Methods**: Functions with implicit `self` parameter
- **Fields**: Struct members with proper typing
- **Runtime Support**: Integration with VSOP runtime library

## Error Handling

The compiler provides comprehensive error reporting:

- **Lexical Errors**: Invalid tokens or characters
- **Syntax Errors**: Malformed program structure
- **Semantic Errors**: Type mismatches, undefined references
- **Code Generation Errors**: LLVM IR generation failures

## Testing

Test the compiler with various VSOP programs:

```bash
# Test basic compilation
./vsopc test.vsop
./test

# Test IR generation
./vsopc -i test.vsop > test.ll

# Test extended VSOP
./vsopc -e extended_test.vsop
```

## Troubleshooting

### Common Issues

1. **LLVM not found**: Install LLVM development packages
2. **Clang not found**: Install Clang compiler
3. **Compilation errors**: Check source code syntax and semantics
4. **Linking errors**: Ensure VSOP runtime library is available

### Debug Mode

For debugging, use the `-i` flag to inspect generated LLVM IR:

```bash
./vsopc -i problematic.vsop
```

This will show the exact LLVM IR being generated, helping identify code generation issues.

## Future Enhancements

- **Optimization Passes**: LLVM optimization pipeline integration
- **Runtime Library**: Enhanced VSOP runtime support
- **Debug Information**: Source-level debugging support
- **Cross-compilation**: Support for different target architectures

