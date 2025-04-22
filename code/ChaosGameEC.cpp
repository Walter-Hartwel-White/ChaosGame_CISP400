// libraries and stuff
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace sf;
using namespace std;

struct coor {
	int x;
	int y;
};

void triangle(int currSize, vector<Vector2f> vertices, vector<Vector2f>& points, int vertice);
void square(int currSize, vector<Vector2f> vertices, vector<Vector2f>& points, int& prevVec);

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game :O!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// clicked coor
	coor clicked;
	int vertice = 0;
	bool chosen = false;
	bool choiceClick = true;
	int prevVer = 0;

	// rand seed for picking points
	srand(time(0));

	// color that will be used
	Color color(245, 245, 245, 150);

	// Text
	sf::Font font;
	if (!font.loadFromFile("fonts/lucon.ttf"))
	{
		// error...
		return 1;
	}

	Text choice;
	choice.setFont(font);
	choice.setString("Choose one of the following:     Triangle     Square     Pentagon");
	choice.setCharacterSize(20);
	choice.setFillColor(Color::White);
	choice.setPosition(20, 20);

	bool written = true;
	Text shapeChosen;
	shapeChosen.setFont(font);
	shapeChosen.setString("Click Points of Verticies");
	shapeChosen.setCharacterSize(20);
	shapeChosen.setFillColor(Color::White);
	shapeChosen.setPosition(20, 50);

	Text directions2;
	directions2.setFont(font);
	directions2.setString("Click on a fourth point to start the magic incantation muhahahaha.");
	directions2.setCharacterSize(20);
	directions2.setFillColor(sf::Color::White);
	directions2.setPosition(20, 80);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

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

					clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

					if (clicked.y > 19 && clicked.y < 42) {
						if (clicked.x > 415 && clicked.x < 512) {
							vertice = 3;
							choiceClick = true;
							written = false;
							points.clear();
							vertices.clear();
						}
						if (clicked.x > 572 && clicked.x < 645) {
							vertice = 4;
							choiceClick = true;
							written = false;
							points.clear();
							vertices.clear();
						}
						if (clicked.x > 702 && clicked.x < 791) {
							vertice = 5;
							choiceClick = true;
							written = false;
							points.clear();
							vertices.clear();
						}
					}

					if (vertice != 0) {
						if (vertices.size() < vertice) {
							vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
							if (choiceClick) { vertices.pop_back(); choiceClick = false; }
						}
						else if (points.size() == 0) {
							points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						}
					}
				}
			}
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			switch (vertice) {
			case 3: 
				triangle(points.size(), vertices, points, 3);
				break;
			case 4:
				square(points.size(), vertices, points, prevVer);
				break;
			case 5:
				triangle(points.size(), vertices, points, 5);
				break;
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/

		window.clear();

		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
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

		window.draw(choice);
		if (vertices.size() == vertice && vertice != 0) {
			window.draw(directions2);
		}
		if (!written) { window.draw(shapeChosen); }

		window.display();
	}

    return 0;
}

void triangle(int currSize, vector<Vector2f> vertices, vector<Vector2f>& points, int vertice) {
	currSize = points.size();
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	double pointX = 0;
	double pointY = 0;
	int randNum = 0;

	if (currSize < 8000) {
		for (int i = 1; i < (currSize + 1); i++) {
			randNum = rand() % ((vertice - 1) + 1);
			x1 = vertices[randNum].x; y1 = vertices[randNum].y;
			x2 = points[i - 1].x; y2 = points[i - 1].y;
			if (vertice == 3) {
				pointX = (x1 + x2) / 2; pointY = (y1 + y2) / 2;
			}
			else{
				pointX = ((x2 - x1) * .382) + x1; pointY = ((y2 - y1) * .382) + y1;
			}
			points.push_back(Vector2f(pointX, pointY));
		}
	}
}
//
void square(int currSize, vector<Vector2f> vertices, vector<Vector2f>& points, int& prevVec) {
	currSize = points.size();
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;
	double pointX = 0;
	double pointY = 0;
	int randNum = 0;

	if (currSize < 3000) {
		for (int i = 1; i < (currSize + 1); i++) {
			randNum = rand() % (4);
			while (randNum == prevVec) {
				randNum = rand() % (4);
			}
			
			//std::cout << randNum << endl;

			x1 = vertices[randNum].x; y1 = vertices[randNum].y;
			x2 = points[i - 1].x; y2 = points[i - 1].y;
			pointX = ((x2 - x1) * .3333) + x1; pointY = ((y2 - y1) * .3333) + y1;
			points.push_back(Vector2f(pointX, pointY));

			prevVec = randNum;
		}
	}
}