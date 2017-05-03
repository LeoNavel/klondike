all: klondike

klondike:
	cd src &&  qmake-qt5  &&$(MAKE)
.PHONY:doc
doc:
	doxygen Doxyfile
