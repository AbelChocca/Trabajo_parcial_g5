#include "UtilsFunc.h"
#include "Map.h"

namespace FrameLoader {
    void cargarFrame(
        vector<vector<vector<Tile>>>& sprites,
        const string& archivo,
        CharToTileFunc charToTile) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
        }

        std::vector<std::vector<Tile>> nuevoFrame;
        std::vector<std::string> lineas;
        std::string linea;
        size_t maxAncho = 0;

        while (std::getline(file, linea)) {
            if (!linea.empty() && linea.back() == '\r') {
                linea.pop_back();
            }

            lineas.push_back(linea);

            if (linea.size() > maxAncho) {
                maxAncho = linea.size();
            }
        }

        for (int i = 0; i < (int)lineas.size(); i++) {
            const std::string& l = lineas[i];
            std::vector<Tile> fila;
            for (int j = 0; j < (int)maxAncho; j++) {
                char c = (j < (int)l.size()) ? l[j] : ' ';
                fila.push_back(charToTile(c));
            }
            nuevoFrame.push_back(fila);
        }

        sprites.push_back(nuevoFrame);
    }
}