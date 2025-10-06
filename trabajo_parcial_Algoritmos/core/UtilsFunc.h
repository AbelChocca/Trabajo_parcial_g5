#pragma once
#include <vector>
#include <string>

using namespace std;

struct Tile;
typedef Tile(*CharToTileFunc)(char);

namespace FrameLoader {
    void cargarFrame(
        vector<vector<vector<Tile>>>& sprites,
        const string& archivo,
        CharToTileFunc charToTile);
}