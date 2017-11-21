LDFLAGS = -L"C:/msys64/mingw64/lib" -L"C:/msys64/mingw64/bin" -lsfml-graphics -lsfml-window -lsfml-system -lgdi32 -lsqlite3
CFLAGS = -fPIC -O3 -I./src -I./src/lib -I./src/bin -I./src/include

all: checkers.exe

checkers.exe: libcheckers.dll ./src/bin/Actions/GameHit.cpp ./src/bin/Actions/MenuHit.cpp ./src/bin/Data/GameData.cpp ./src/bin/Graphics/Animations.cpp ./src/bin/Graphics/buttonRect.cpp ./src/bin/Graphics/buttonRectDrawn.cpp ./src/bin/Graphics/buttonRectImage.cpp ./src/bin/Graphics/dragDropRect.cpp ./src/bin/Graphics/Drawing.cpp ./src/bin/Graphics/LinLeg.cpp ./src/bin/Graphics/Menu.cpp ./src/bin/Graphics/Path.cpp ./src/bin/Graphics/Sprites.cpp ./src/bin/main.cpp
	g++ -o checkers.exe ${CFLAGS} ./src/bin/Actions/GameHit.cpp ./src/bin/Actions/MenuHit.cpp ./src/bin/Data/GameData.cpp ./src/bin/Graphics/Animations.cpp ./src/bin/Graphics/buttonRect.cpp ./src/bin/Graphics/buttonRectDrawn.cpp ./src/bin/Graphics/buttonRectImage.cpp ./src/bin/Graphics/dragDropRect.cpp ./src/bin/Graphics/Drawing.cpp ./src/bin/Graphics/LinLeg.cpp ./src/bin/Graphics/Menu.cpp ./src/bin/Graphics/Path.cpp ./src/bin/Graphics/Sprites.cpp ./src/bin/main.cpp libcheckers.dll ${LDFLAGS}

libcheckers.dll: ./src/lib/Database/Database.cpp
	g++ ${CFLAGS} -shared -o libcheckers.dll ./src/lib/Database/Database.cpp ${LDFLAGS} -Wl,--export-all-symbols,--out-implib,libdatabase.a

clean:
	rm -f libcheckers.dll
	rm -f libcheckers.a
	rm -f checkers.exe