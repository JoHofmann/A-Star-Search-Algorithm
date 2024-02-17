//============================================================================
// Name        : main.cpp
// Author      : Johannes Hofmann
//============================================================================

#include <iostream>
#include "SFML/Graphics.hpp"

#include "a_star/a_star.hpp"


int main()
{
	const uint width = 800;
	const uint height = 600;

	const uint cellSize = 10;

    sf::RenderWindow window(sf::VideoMode(width, height), "A*");

    std::vector<std::vector<int>> map(width/cellSize, std::vector<int>(height/cellSize, 0));
    std::vector<std::vector<int>> drawMap(width/cellSize, std::vector<int>(height/cellSize, 0));


    vec2 start{2, 2};
    vec2 target{width/cellSize - 2, height/cellSize - 2};

    A_star a_star(&map, start, target);
    bool run = false;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            	run = true;
            }
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int indexX = mousePos.x/cellSize;
            int indexY = mousePos.y/cellSize;

            map[indexX][indexY] = 1;
            map[indexX+1][indexY] = 1;
            map[indexX-1][indexY] = 1;
            map[indexX][indexY+1] = 1;
            map[indexX][indexY-1] = 1;

        }

        for (size_t i = 0; i < 10; i++)
        {
            if(run && !a_star.isPathFound()) {
        	    a_star.iteration();
            }
        }
        


        for (auto it = drawMap.begin(); it != drawMap.end(); ++it) {
        	it->assign(drawMap[0].size(), 0);
		}

        auto openList = a_star.getopenList();
        auto closedList = a_star.getclosedList();
        auto path = a_star.getPath();

		for (auto it = openList.begin(); it != openList.end(); ++it) {
			drawMap[it->getPosition().x][it->getPosition().y] = 2;
		}

		for (auto it = closedList.begin(); it != closedList.end(); ++it) {
			drawMap[(*it)->getPosition().x][(*it)->getPosition().y] = 3;
		}

		for (auto it = path.begin(); it != path.end(); ++it) {
			drawMap[it->x][it->y] = 4;
		}


        // draw
        window.clear();

        // draw map
        for (uint y = 0; y < height/cellSize; ++y) {
            for (uint x = 0; x < width/cellSize; ++x) {
        		sf::RectangleShape rect(sf::Vector2f((float)cellSize, (float)cellSize));
        		rect.setFillColor(sf::Color::Black);
        		rect.setPosition(x * cellSize, y * cellSize);

            	if(map[x][y] == 1) {	// barrier
            		rect.setFillColor(sf::Color::Blue);
            	}
            	if(drawMap[x][y] == 2) {	// openList
            		rect.setFillColor(sf::Color::Yellow);
            	}
            	if(drawMap[x][y] == 3) {	// closedList
            		rect.setFillColor(sf::Color::Red);
            	}
               	if(drawMap[x][y] == 4) {	// current path
                	rect.setFillColor(sf::Color::Cyan);
                }

        		window.draw(rect);

    		}
		}

        window.display();
    }

    return 0;
}













