#pragma once
#include <vector>
#include <string>
#include "Layer.h"

struct Tileset {
	int FirstID;
	int LastID;
	int RowCount;
	int ColCount;
	int TileCount;
	int TileSize;
	std::string Name;
	std::string Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer:public Layer {
public:
	TileLayer(int tilesize,int rowcount,int colcount,TileMap tilemap, TilesetList tilesets);
	virtual void Update();
	virtual void Render();
	inline TileMap GetTileMap() {
		return m_TileMap;
	}
private:
	int m_TileSize;
	int m_RowCount;
	int m_ColCount;

	TileMap m_TileMap;
	TilesetList m_Tilesets;
};
