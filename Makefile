INCLUDE_SFML = -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include/SFML
INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

pong:
	g++ -o pong pong.cpp Rect.cpp Ball.cpp $(INCLUDE_SFML)

clean:
	rm -rf pong *.o
