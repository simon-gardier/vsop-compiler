CXX 			= clang++

CXXFLAGS 		+= -Wall $(shell llvm-config --cxxflags) -fexceptions
LDFLAGS			+= $(shell llvm-config --ldflags --system-libs --libs all)

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

all: $(EXEC)

install-tools:
	@echo "Nothing to do"

main.o: driver.hpp parser.hpp codegen.hpp

driver.o: driver.hpp parser.hpp codegen.hpp

parser.o: driver.hpp parser.hpp

lexer.o: driver.hpp parser.hpp

codegen.o: codegen.hpp ast.hpp semantic.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ) $(LLVM_LIBS)

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
	@rm -f parser.cpp parser.hpp location.hh *.output

.PHONY: clean
