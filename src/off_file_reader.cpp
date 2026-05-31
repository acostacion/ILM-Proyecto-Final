#include "off_file_reader.h"

using namespace godot;

// TODO cambiar antes de commitear.
void OffFileReader::_bind_methods() {
    ClassDB::bind_method(D_METHOD("loadOffFile", "file"), &OffFileReader::loadOffFile);
}

void OffFileReader::loadOffFile(std::string f) {
    vertices.clear();
    faces.clear();

    std::ifstream file(f);
    if(!file) return;

    std::string s;
    file >> s; // nos saltamos 4OFF

    int nVertices, nFaces;
    file >> nVertices >> nFaces;
    // nos saltamos los demas numeros k no nos interesan de la line
    file >> s; 
    file >> s;

    // --- vertices
    file >> s; // nos ponemos en la linea del #
    std::getline(file, s); // nos saltamos la linea de # vertices

    float x, y, z, w;
    for(int i = 0; i < nVertices; ++i){
        file >> x >> y >> z >> w;
        vertices.push_back({i, Vector4(x, y, z, w)});
    }

    // --- caras
    file >> s; // nos ponemos en la linea del #
    std::getline(file, s); // nos saltamos la linea de # faces

    int bardoma, v1, v2, v3;
    for(int i = 0; i < nFaces; ++i){
        // bardoma es el 3 marronero ese k sale siempre al principio
        file >> bardoma >> v1 >> v2 >> v3;
        faces.push_back({v1, v2, v3});
    }

}
