#include "off_file_reader.h"
#include <godot_cpp/classes/project_settings.hpp>

using namespace godot;

void OffFileReader::_bind_methods() {
    ClassDB::bind_method(D_METHOD("loadOffFile", "file"), &OffFileReader::loadOffFile);
}

void OffFileReader::loadOffFile(String f) {
    vertices.clear();
    faces.clear();

    // pasa del string de godot al de c++ pork si no se raya el compile
    std::string ruta = f.utf8().get_data();

    std::ifstream file(ruta);
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
