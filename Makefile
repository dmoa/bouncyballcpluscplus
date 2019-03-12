all:
	g++ test.cpp Square.cpp -o main.exe -DSFML_STATIC -I C:\SFML\include -L C:\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
