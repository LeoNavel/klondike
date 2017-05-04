all: hra2017 hra2017-cli

hra2017: src
	cd src &&  qmake-qt5  &&$(MAKE)
	mv src/klondike ./hra2017

hra2017-cli: src
	cd src && $(MAKE) -f Makefile-terminal
	mv src/klondike-terminal ./hra2017-cli

.PHONY:doc
doxygen:
	mkdir doc
	doxygen Doxyfile

clean:
	cd src && $(MAKE) clean
	cd src && $(MAKE) -f Makefile-terminal clean
	rm -rf hra2017* doc src/Makefile

pack:
	zip -r xklemb00-xtomas32.zip src/ Makefile Doxyfile 

run: hra2017 hra2017-cli
	./hra2017
	./hra2017-cli
