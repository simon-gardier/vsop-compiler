CXX 			= clang++

CXXFLAGS 		= -Wall -Wextra -Wno-unused-private-field

BISONFLAGS 		= -d -v

EXEC			= vsopc

SRC				= main.cpp \
				  lexer.cpp \
				  driver.cpp \
				  parser.cpp \
				  ast.cpp

OBJ	  			= $(SRC:.cpp=.o)

all: $(EXEC)

install-tools:
	@echo "nothing to do"

main.o: driver.hpp parser.hpp

driver.o: driver.hpp parser.hpp

parser.o: driver.hpp parser.hpp

lexer.o: driver.hpp parser.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ)

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

.PHONY: clean
