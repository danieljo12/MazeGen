﻿#include "Cell.h"


Cell::Cell() : x(0), y(0), visted(false), walls{ true, true, true, true }, ID(666)
{
	cols = WIDTH / cellWidth;
	rows = HEIGHT / cellWidth;
}

Cell::Cell(float i, float j, int id) : x(i), y(j), visted(false), walls{ true, true, true, true }, ID(id)
{
	cols = WIDTH / cellWidth;
	rows = HEIGHT / cellWidth;
}

void Cell::drawCell(Renderer* line, float i)
{
	int x = this->x * cellWidth;
	int y = this->y * cellWidth;

	if(walls[0] == true) { // top
		line->drawLine(glm::vec2(x, y), glm::vec2(cellWidth / 2, 0), glm::vec3(1.0f, 1.0f, i)); // top
		//^^^^^^^ i did `cellWidth / 2` because the line x vertex data is -1 to 1 so its a length of 2 so if you didnt divide it then it will 20(default cellwidth) will end up scalled to 40. 20*2=40
	}
	if(walls[1] == true) { // right
		line->drawLine(glm::vec2(x + cellWidth, y), glm::vec2(cellWidth / 2, 0), glm::vec3(1.0f, 1.0f, i), 90.0f);// right siede
	}
	if(walls[2] == true) { // botom
		line->drawLine(glm::vec2(x, y + cellWidth), glm::vec2(cellWidth / 2, 0), glm::vec3(1.0f, 1.0f, i)); // bottom
	}
	if(walls[3] == true) { // left
		line->drawLine(glm::vec2(x, y), glm::vec2(cellWidth / 2, 0), glm::vec3(1.0f, 1.0f, i), 90.0f);//left side
	}
}

int Cell::index(int i, int j)
{
	if(i < 0 || j < 0 || i > cols - 1 || j > rows - 1)
		return -1;

	return i + j * cols;
}

void Cell::removeWalls(Cell& nextCell)
{
	int x = this->x - nextCell.x;
	if(x == 1) {
		this->walls[3] = false; // removes the left
		nextCell.walls[1] = false; // removes right
	}
	else if(x == -1) {
		this->walls[1] = false; // removes the right
		nextCell.walls[3] = false; // removes left
	}

	int y = this->y - nextCell.y;
	if(y == 1) {
		this->walls[0] = false; // removes the top
		nextCell.walls[2] = false; // remvoves the bottom
	}
	else if(y == -1) {
		this->walls[2] = false; // removes the bottom
		nextCell.walls[0] = false; // removes top
	}
}

void Cell::highlight(Renderer* sqaure)
{
	if(this->valid == true) {
		sqaure->drawSquare(glm::vec2((this->x * cellWidth), (this->y * cellWidth)), glm::vec2(10, 10), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

int Cell::checkNeighbours(std::vector<Cell>& grid)
{
	std::vector<int> neighbors;

	int topIndex = index(x, y - 1);
	Cell top;
	if(topIndex != -1)
		top = grid[topIndex];

	int rightIndex = index(x + 1, y);
	Cell right;
	if(rightIndex != -1)
		right = grid[rightIndex];

	int bottomIndex = index(x, y + 1);
	Cell bottom;
	if(bottomIndex != -1)
		bottom = grid[bottomIndex];

	int leftIndex = index(x - 1, y);
	Cell left;
	if(leftIndex != -1)
		left = grid[leftIndex];

	if(topIndex != -1 && !top.visted)
		neighbors.push_back(topIndex);
	if(rightIndex != -1 && !right.visted)
		neighbors.push_back(rightIndex);
	if(bottomIndex != -1 && !bottom.visted)
		neighbors.push_back(bottomIndex);
	if(leftIndex != -1 && !left.visted)
		neighbors.push_back(leftIndex);

	if(neighbors.size() > 0) {
#if _DEBUG
		// debug bit
#else
		// release bit
		// Sets the seed so the maze is different every time
#endif
		std::srand(static_cast<unsigned int>(std::time(nullptr)));


		int randomInt = rand() % neighbors.size();
		return neighbors[randomInt];
	}
	else {
		return -1;
	}

}
