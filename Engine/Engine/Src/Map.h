#pragma once
#include <string>

class Map {

public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void AddTile(int srcX, int srcY, int xPos, int yPos);
	void LoadMap(std::string path, int sizeX, int sizeY);

	//static int mapSizeY = 0;  //for gravity to know bounds
	//static int mapSizeX = 0;

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
};