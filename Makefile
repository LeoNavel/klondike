all: hra2017 hra2017-cli

hra2017: src
	cd src &&  qmake  &&$(MAKE)
	mv src/klondike ./hra2017

hra2017-cli: src
	cd src && $(MAKE) -f Makefile-terminal
	mv src/klondike-terminal ./hra2017-cli

.PHONY:doxygen
doxygen:
	mkdir doc
	doxygen Doxyfile

clean:
	rm -rf doc hra2017*
	cd src && $(MAKE) -f Makefile-terminal clean
	cd src && $(MAKE) clean
	rm -rf src/Makefile


pack:
	zip -r xklemb00-xtomas32.zip src/ Makefile Doxyfile LICENSE README.md examples

run: hra2017 hra2017-cli
	./hra2017
	./hra2017-cli
