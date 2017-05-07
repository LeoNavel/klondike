ICP 2016/2017 - Klondike

Jednoduch8 hra solitaire ktora je hratelna v grafickom a aj v terminalovom
prostredi.

Hru je mozne vytvorit prikazom make pricom sa predpoklada nainstalovane 
QT verzie 5.5.1 so simlinkom qmake priamo na tuto verziu.

po prikaze make sa objavia dva subory. prvy hra2017 predstavuje 
solitaire s grafickym prostredim a druhy hra2017-cli bez samostetneho
grafickeho prostredia ktoru je mozne hrat z terminaloveho prostredia

MERLIN
    pri kompilacii na merlinovi je potrebne pridat
    export QT_PLUGIN_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/plugins:${QT_PLUGIN_PATH}
    export LD_LIBRARY_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:${LD_LIBRARY_PATH}
    a namiesto qmake treba pouzit  /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake

Pravoplatnymi autormi su:
	Adrian Tomasov (xtomas32)
	Filip Klembara (xklemb00)

