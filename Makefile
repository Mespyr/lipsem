LEXER=src/lexer.cpp src/lexer.h
PARSER=src/parser.h src/parser.cpp
MAIN=src/lipsem.h src/lipsem.cpp
STANDALONE_HEADERS=src/errors.h src/tokens.h src/dict.h

BUILD_FILES=src/main.cpp src/lexer.cpp src/parser.cpp src/lipsem.cpp
FILES=$(MAIN) $(LEXER) $(PARSER) $(STANDALONE_HEADERS) src/main.cpp 


lipsem: $(FILES)
	g++ $(BUILD_FILES) -o lipsem -Wall 

remove_trash: 
	rm -r source.lpm
	rm -r examples/

clean:
	rm -r lipsem