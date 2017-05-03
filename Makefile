all: klondike klondike_terminal

klondike:
	cd src &&  qmake-qt5  &&$(MAKE)
	mv klondike .

klondike_terminal: src
	cd src && $(MAKE) -f Makefile-terminal
	mv src/klondike-terminal .

.PHONY:doc
doc:
	doxygen Doxyfile

clean:
	cd src $(MAKE) clean
	cd src && $(MAKE) -f Makefile-terminal clean

