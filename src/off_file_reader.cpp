#include "off_file_reader.h"
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp> 
#include <sstream>

using namespace godot;

void OffFileReader::_bind_methods() {

    ClassDB::bind_method(D_METHOD("loadOffFile", "file"), &OffFileReader::loadOffFile);

    ClassDB::bind_method(D_METHOD("set_off_path", "path"), &OffFileReader::set_off_path);
    ClassDB::bind_method(D_METHOD("get_off_path"), &OffFileReader::get_off_path);

    // el hint FILE es el selector de archivos, y "*.off" lo filtra
    ADD_PROPERTY(
        PropertyInfo(Variant::STRING, "off_path", PROPERTY_HINT_FILE, "*.off"),
        "set_off_path", "get_off_path"
    );
}

void OffFileReader::loadOffFile(String f) {
     UtilityFunctions::print("OFF -> ", f, " | existe: ", FileAccess::file_exists(f));
   
    vertices.clear();
    faces.clear();

    // Leer con FileAccess
    Ref<FileAccess> file = FileAccess::open(f, FileAccess::READ);
    if (file.is_null()) return;
    std::string content = file->get_as_text().utf8().get_data();

    // Parsear desde memoria con tu misma lógica de >>
    std::istringstream in(content);

    std::string s;
    in >> s; // nos saltamos 4OFF

    int nVertices, nFaces;
    in >> nVertices >> nFaces;
    // nos saltamos los demas numeros k no nos interesan de la line
    in >> s; 
    in >> s;

    // --- vertices
    in >> s; // nos ponemos en la linea del #
    std::getline(in, s); // nos saltamos la linea de # vertices

    float x, y, z, w;
    for(int i = 0; i < nVertices; ++i){
        in >> x >> y >> z >> w;
        vertices.push_back({i, Vector4(x, y, z, w)});
    }

    // --- caras
    in >> s; // nos ponemos en la linea del #
    std::getline(in, s); // nos saltamos la linea de # faces

    int bardoma, v1, v2, v3;
    for(int i = 0; i < nFaces; ++i){
        // bardoma es el 3 marronero ese k sale siempre al principio
        in >> bardoma >> v1 >> v2 >> v3;
        faces.push_back({v1, v2, v3});
    }
}
