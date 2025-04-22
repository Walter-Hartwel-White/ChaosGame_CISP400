// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game :]", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// rand seed for picking points
	srand(time(0));
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int pointX = 0;
	int pointY = 0;
	int randNum = 0;

	// color that will be used
	Color color(245, 245, 245, 150);

	// font / text that will be used
	sf::Font font;
	if (!font.loadFromFile("fonts/lucon.ttf"))
	{
		// error...
		return 1;
	}

	Text directions1;
	Text note;
	Text directions2;
	directions1.setFont(font);
	directions2.setFont(font);
	note.setFont(font);
	directions1.setString("Click on three points to make a triangle.");
	note.setString(" Note: I commissioned my local wizard to make this a univeral phenomenon");
	directions2.setString("Click on a fourth point to start the magic process.");
	directions1.setCharacterSize(20);
	note.setCharacterSize(10);
	directions2.setCharacterSize(20);
	directions1.setFillColor(sf::Color::White);
	note.setFillColor(sf::Color::White);
	directions2.setFillColor(sf::Color::White);
	directions1.setPosition(20, 20);
	directions2.setPosition(20, 45);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3) ///less than the vertices required
			    {
					vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			int currSize = points.size();

			if (currSize < 8000) {
				for (int i = 1; i < (currSize + 1); i++) {
					randNum = rand() % (2 + 1);
					x1 = vertices[randNum].x; y1 = vertices[randNum].y;
					x2 = points[i - 1].x; y2 = points[i - 1].y;
					pointX = (x1 + x2) / 2; pointY = (y1 + y2) / 2;
					points.push_back(Vector2f(pointX, pointY));
				}
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(color);
		    window.draw(rect);
		}

		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(4, 4));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(color);
			window.draw(rect);
		}

		if (vertices.size() == 3) {
			window.draw(directions2);
		}
		window.draw(directions1);
		window.draw(note);

		///TODO:  Draw points
		window.display();
	}
}
