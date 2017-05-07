all: hra2017 hra2017-cli

hra2017: src
	cd src &&  qmake  &&$(MAKE)
	mv src/hra2017* .

hra2017-cli: src
	cd src && $(MAKE) -f Makefile-terminal
	mv src/hra2017-cli* .

.PHONY:doxygen
doxygen:
	doxygen Doxyfile

clean:
	rm -rvf doc/* hra2017*
	cd src && $(MAKE) -f Makefile-terminal clean
	cd src && $(MAKE) clean
	rm -rvf src/Makefile


pack:
	zip -r xklemb00-xtomas32.zip src/ Makefile Doxyfile LICENSE README.md examples doc

run: hra2017 hra2017-cli
	./hra2017
	./hra2017-cli

