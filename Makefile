all: klondike klondike-terminal

klondike:
	cd src &&  qmake-qt5  &&$(MAKE)
	mv src/klondike .

klondike-terminal: src
	cd src && $(MAKE) -f Makefile-terminal
	mv src/klondike-terminal .

.PHONY:doc
doxygen:
	mkdir doc
	doxygen Doxyfile

clean:
	cd src && $(MAKE) clean
	cd src && $(MAKE) -f Makefile-terminal clean
	rm -rf klondike klondike-terminal doc src/Makefile

pack:
	zip -r xklemb00-xtomas32.zip src/ Makefile Doxyfile 

run: klondike klondike-terminal 
	./klondike &
	./klondike-terminal
