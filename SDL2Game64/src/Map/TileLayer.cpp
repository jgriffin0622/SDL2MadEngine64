#include "TileLayer.h"
#include "../TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets):
	m_TileSize(tilesize), m_ColCount(colcount),m_RowCount(rowcount), m_TileMap(tilemap), m_Tilesets(tilesets) {

	for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
		TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/Maps/" + m_Tilesets[i].Source);
	}
}

void TileLayer::Update() {

}

void TileLayer::Render() {
	for (unsigned int r = 0; r < m_RowCount; r++) {
		for (unsigned int c = 0; c < m_ColCount; c++) {
			int tileID = m_TileMap[r][c];
			if (tileID == 0) {
				continue;
			}
			else {
				int index=0;
				if (m_Tilesets.size() > 1) {
					for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
						if (tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID) {
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							break;
						}
					}
				}

				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - tileRow * ts.ColCount - 1;

				if (tileID % ts.ColCount == 0) {
					tileRow--;
					tileCol = ts.ColCount - 1;
				}
				TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, c * ts.TileSize, r * ts.TileSize, tileRow, tileCol);
//				TextureManager::GetInstance()->DrawTile(ts.Name, 32, c * 32, r * 32, tileRow, tileCol);
			}
		}
	}
}