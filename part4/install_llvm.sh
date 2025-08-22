#!/bin/bash

echo "VSOP Compiler - LLVM Installation Helper"
echo "========================================"
echo ""

# Detect operating system
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Detected Linux distribution"
    
    # Check if apt is available (Debian/Ubuntu)
    if command -v apt-get &> /dev/null; then
        echo "Installing LLVM using apt..."
        sudo apt-get update
        sudo apt-get install -y llvm-dev clang llvm
        echo "LLVM installed successfully!"
        
    # Check if yum is available (RHEL/CentOS/Fedora)
    elif command -v yum &> /dev/null; then
        echo "Installing LLVM using yum..."
        sudo yum install -y llvm-devel clang llvm
        echo "LLVM installed successfully!"
        
    # Check if pacman is available (Arch)
    elif command -v pacman &> /dev/null; then
        echo "Installing LLVM using pacman..."
        sudo pacman -S --noconfirm llvm clang
        echo "LLVM installed successfully!"
        
    else
        echo "Package manager not detected. Please install LLVM manually:"
        echo "  Download from: https://releases.llvm.org/"
    fi
    
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Detected macOS"
    
    if command -v brew &> /dev/null; then
        echo "Installing LLVM using Homebrew..."
        brew install llvm clang
        echo "LLVM installed successfully!"
        echo ""
        echo "Note: You may need to add LLVM to your PATH:"
        echo "  export PATH=\"/usr/local/opt/llvm/bin:\$PATH\""
        echo "  export LDFLAGS=\"-L/usr/local/opt/llvm/lib\""
        echo "  export CPPFLAGS=\"-I/usr/local/opt/llvm/include\""
    else
        echo "Homebrew not found. Please install Homebrew first:"
        echo "  /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
        echo "  Then run: brew install llvm clang"
    fi
    
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    echo "Detected Windows (MSYS2/Cygwin)"
    echo "Please install LLVM manually:"
    echo "  1. Download from: https://releases.llvm.org/"
    echo "  2. Add LLVM bin directory to your PATH"
    echo "  3. Ensure llvm-config is available"
    
else
    echo "Unknown operating system: $OSTYPE"
    echo "Please install LLVM manually from: https://releases.llvm.org/"
fi

echo ""
echo "Verifying installation..."
if command -v llvm-config &> /dev/null; then
    echo "✓ llvm-config found: $(llvm-config --version)"
    echo "✓ LLVM version: $(llvm-config --version)"
    echo "✓ Include path: $(llvm-config --includedir)"
    echo "✓ Library path: $(llvm-config --libdir)"
else
    echo "✗ llvm-config not found. LLVM installation may have failed."
    echo "Please check the installation and try again."
fi

echo ""
echo "Installation complete. You can now try building the compiler with:"
echo "  make clean"
echo "  make"
