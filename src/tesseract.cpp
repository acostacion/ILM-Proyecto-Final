#include "tesseract.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

#pragma region HELPERS
// Brian Kernighan's Algorithm para contar bits activos
static int count_set_bits(int n)
{
    int count = 0;
    while (n > 0)
    {
        n &= (n - 1);
        count += 1;
    }
    return count;
}
#pragma endregion

void Tesseract::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_size", "size"), &Tesseract::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &Tesseract::get_size);
    // Propiedades
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "size"), "set_size", "get_size");
}
#pragma region Explicacion de vertices y caras del hipercubo 4D
// Un hipercubo 4D tiene 16 vertices.
// Cada vertice es una combinacion de +h o -h en cada dimension.
// mientras que un cubo tiene 8 vertices, con combinaciones de +h o -h en x,y,z.
//
// (-h,-h,-h) -------------- (+h,-h,-h)
//    |   \                     |  \
//	  |    \                    |   \
//	  |  (-h,-h,+h) ------------|- (+h,-h,+h)
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
// (-h,+h,-h) -------------- (+h,+h,-h)
//	   \   |                     \    |
//	    \  |                      \   |
//      (-h,+h,+h) -------------- (+h,+h,+h)
//
// En 4D, cada vertice se extiende a una nueva dimension W, con combinaciones de +h o -h en w, dando un total de 16 vertices.
//				=== cubo interno ===
// 						   (-h,-h,-h,-h) -------------- (+h,-h,-h,-h)
// 						      |   \                     |   \
//							  |    \                    |    \
//							  |  (-h,-h,+h,-h) ----------- (+h,-h,+h,-h)
//							  |    |                    |     |
//							  |    |                    |     |
//							  |    |                    |     |
//							  |    |                    |     |
//							  |    |                    |     |
//							  |    |                    |     |
// 						(-h,+h,-h,-h) -------------- (+h,+h,-h,-h)
//							   \   |                     \    |
//							    \  |                      \   |
// 						     (-h,+h,+h,-h) -------------- (+h,+h,+h,-h)
//			  	=== cubo externo ===
// (-h,-h,-h,+h) -------------- (+h,-h,-h,+h)
//    |   \                     |   \
//	  |    \                    |    \
//	  |  (-h,-h,+h,+h) ----------- (+h,-h,+h,+h)
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
//	  |    |                    |     |
// (-h,+h,-h,+h) -------------- (+h,+h,-h,+h)
//	   \   |                     \    |
//	    \  |                      \   |
//      (-h,+h,+h,+h) -------------- (+h,+h,+h,+h)
#pragma endregion
void Tesseract::_generate_vertices()
{
    for (int i = 0; i < 16; i++)
    {
        // Cada bit de i representa si la coordenada es +h o -h en esa dimension
        // el indice corresponde a la posicion del vertice en el hipercubo,
        // y se puede usar para generar las caras 1 = 1, 0 = -1
        float x = ((i >> 0) & 1) ? 1.0f : -1.0f;
        float y = ((i >> 1) & 1) ? 1.0f : -1.0f;
        float z = ((i >> 2) & 1) ? 1.0f : -1.0f;
        float w = ((i >> 3) & 1) ? 1.0f : -1.0f;
        // Almacenar el vertice con su indice
        auto v = Vector4(x, y, z, w);
        vertices.push_back({i, v});
    }
}

void Tesseract::_generate_faces()
{
    // Generar los 24 cuadrados del hipercubo 4D
    // Hay C(4,2) = 6 formas de elegir 2 dimensiones que varian
    // Para cada forma, hay 2^2 = 4 valores para las dimensiones fijas
    // Total = 6 × 4 = 24 cuadrados

    faces.clear();
    faces.reserve(24);
    for (const auto &v1 : vertices)
    {
        for (const auto &v2 : vertices)
        {
            // Verificar que v1 y v2 difieran en exactamente 2 bits (2 dimensiones)
            int diff = v1.index ^ v2.index; // XOR
            if (count_set_bits(diff) != 2)  // si es igual a 2 v1 y v2 son vertices opuestos en exactamente 2 dimensiones, formando un cuadrado
                continue;
            // Extraer los dos bits que difieren
            int bit1 = -1, bit2 = -1;

            // Encontrar la posicion de los bits que difieren
            for (int b = 0; b < 4; b++)
            {
                if ((diff >> b) & 1)
                {
                    if (bit1 == -1)
                        bit1 = b;
                    else
                    {
                        bit2 = b;
                        break;
                    }
                }
            }

            // Obtener los otros dos vertices del cuadrado formado por v1 y v2
            int v3_index = v1.index ^ (1 << bit1); // Flip solo bit1
            int v4_index = v1.index ^ (1 << bit2); // Flip solo bit2
            // Construimos los triangulos que forman el cuadrado
            faces.push_back({v1.index, v3_index, v4_index});
            faces.push_back({v1.index, v4_index, v2.index});
        }
    }
}

Tesseract::Tesseract() : size(1, 1, 1, 1)
{
    _generate_vertices();
    _generate_faces();
}
