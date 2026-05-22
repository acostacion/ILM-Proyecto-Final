#include "mesh_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cmath>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;
// HELPERS

static Vector4 rotate4D(Vector4 v,
						float xy, float xz, float xw,
						float yz, float yw, float zw)
{

	float x = v.x, y = v.y, z = v.z, w = v.w;
	float nx, ny, nz, nw;

	// XY
	nx = x * cos(xy) - y * sin(xy);
	ny = x * sin(xy) + y * cos(xy);
	x = nx;
	y = ny;

	// XZ
	nx = x * cos(xz) - z * sin(xz);
	nz = x * sin(xz) + z * cos(xz);
	x = nx;
	z = nz;

	// XW
	nx = x * cos(xw) - w * sin(xw);
	nw = x * sin(xw) + w * cos(xw);
	x = nx;
	w = nw;

	// YZ
	ny = y * cos(yz) - z * sin(yz);
	nz = y * sin(yz) + z * cos(yz);
	y = ny;
	z = nz;

	// YW
	ny = y * cos(yw) - w * sin(yw);
	nw = y * sin(yw) + w * cos(yw);
	y = ny;
	w = nw;

	// ZW
	nz = z * cos(zw) - w * sin(zw);
	nw = z * sin(zw) + w * cos(zw);
	z = nz;
	w = nw;

	return Vector4(x, y, z, w);
}

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

void Mesh4D::_bind_methods()
{
	// Visualizacion
	ClassDB::bind_method(D_METHOD("set_wireframe", "wireframe"), &Mesh4D::set_wireframe);
	ClassDB::bind_method(D_METHOD("get_wireframe"), &Mesh4D::get_wireframe);
	// Rango visible de la dimension W
	ClassDB::bind_method(D_METHOD("set_w_min", "w_min"), &Mesh4D::set_w_min);
	ClassDB::bind_method(D_METHOD("get_w_min"), &Mesh4D::get_w_min);
	ClassDB::bind_method(D_METHOD("set_w_max", "w_max"), &Mesh4D::set_w_max);
	ClassDB::bind_method(D_METHOD("get_w_max"), &Mesh4D::get_w_max);
	// Tamanyo del hipercubo
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Mesh4D::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &Mesh4D::get_size);
	// Rotaciones 4D
	ClassDB::bind_method(D_METHOD("set_rot_xw", "v"), &Mesh4D::set_rot_xw);
	ClassDB::bind_method(D_METHOD("get_rot_xw"), &Mesh4D::get_rot_xw);
	ClassDB::bind_method(D_METHOD("set_rot_yw", "v"), &Mesh4D::set_rot_yw);
	ClassDB::bind_method(D_METHOD("get_rot_yw"), &Mesh4D::get_rot_yw);
	ClassDB::bind_method(D_METHOD("set_rot_zw", "v"), &Mesh4D::set_rot_zw);
	ClassDB::bind_method(D_METHOD("get_rot_zw"), &Mesh4D::get_rot_zw);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "wireframe", PROPERTY_HINT_RANGE, "0,1,1"), "set_wireframe", "get_wireframe");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "size"), "set_size", "get_size");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "w_min"), "set_w_min", "get_w_min");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "w_max"), "set_w_max", "get_w_max");
	// Rotaciones 4D
	ADD_GROUP("4D Rotation", "rot_");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_xw", PROPERTY_HINT_RANGE, "-6.28,6.28,0.01"), "set_rot_xw", "get_rot_xw");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_yw", PROPERTY_HINT_RANGE, "-6.28,6.28,0.01"), "set_rot_yw", "get_rot_yw");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_zw", PROPERTY_HINT_RANGE, "-6.28,6.28,0.01"), "set_rot_zw", "get_rot_zw");
}

Mesh4D::Mesh4D()
	: size(2.0f), w_min(-1.0f), w_max(1.0f),
	  rot_xy(0.0f), rot_xz(0.0f), rot_xw(0.0f),
	  rot_yz(0.0f), rot_yw(0.0f), rot_zw(0.0f)
{
	// Crea MeshInstance3D hijo
	mesh_instance = memnew(MeshInstance3D);
	add_child(mesh_instance);
	Ref<StandardMaterial3D> material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0.2f, 0.7f, 1.0f, 1.0f)); // Azul
	material->set_shading_mode(BaseMaterial3D::SHADING_MODE_UNSHADED);
	material->set_cull_mode(BaseMaterial3D::CULL_DISABLED); // Mostrar ambas caras
	mesh_instance->set_material_override(material);

	// Vector de vertices en 4D
	// Vertices proyectados en 3D
	std::vector<Vector3> projected;
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
	for (int i = 0; i < 16; i++)
	{
		// Cada bit de i representa si la coordenada es +h o -h en esa dimension
		float x = ((i >> 0) & 1) ? 1.0f : -1.0f;
		float y = ((i >> 1) & 1) ? 1.0f : -1.0f;
		float z = ((i >> 2) & 1) ? 1.0f : -1.0f;
		float w = ((i >> 3) & 1) ? 1.0f : -1.0f;
		// Almacenar el vertice con su indice
		auto v = Vector4(x, y, z, w);
		vertex.push_back({i, v});
	}

	generate_faces();
	update_mesh();
}

void godot::Mesh4D::_process(double delta)
{
}

void godot::Mesh4D::generate_faces()
{

	// Generar los 24 cuadrados del hipercubo 4D
	// Hay C(4,2) = 6 formas de elegir 2 dimensiones que varían
	// Para cada forma, hay 2^2 = 4 valores para las dimensiones fijas
	// Total = 6 × 4 = 24 cuadrados

	faces.clear();
	faces.reserve(24);
	for (const auto &v1 : vertex)
	{
		for (const auto &v2 : vertex)
		{
			// Verificar que v1 y v2 difieran en exactamente 2 bits (2 dimensiones)
			int diff = v1.index ^ v2.index; // XOR
			if (count_set_bits(diff) == 2)
			{
				
				// Extraer los dos bits que difieren
				int bit1 = -1, bit2 = -1;
				for (int b = 0; b < 4; b++)
				{
					if ((diff >> b) & 1)
					{
						if (bit1 == -1) bit1 = b;
						else { bit2 = b; break; }
					}
				}
				
				// Encontrar los otros 2 vErtices que forman el cuadrado con v1 y v2
				int v3_index = v1.index ^ (1 << bit1);  // Flip solo bit1
				int v4_index = v1.index ^ (1 << bit2);  // Flip solo bit2
				if (v1.index < v3_index)		// Solo procesar una vez
				{
					faces.push_back({v1.index, v3_index, v2.index});
					faces.push_back({v3_index, v4_index, v2.index});
				}
			}
		}
	}
}

void Mesh4D::update_mesh()
{
	if (!mesh_instance)
		return;

	float h = size / 2.0f;
	const float projection_distance = 3.0f;

	// vertices proyectados en 3D
	std::vector<Vector3> projected;
	std::vector<int> filtered_indices; // Indices de vertices que pasaron el filtro W
	std::vector<int> index_mapping;	   // Mapeo de índice original a índice en projected
	index_mapping.resize(16, -1);
	for (const auto &v_org : vertex)
	{
		Vector4 v = v_org.position;
		// Aplica tamanyo
		v = Vector4(v.x * h, v.y * h, v.z * h, v.w * h);

		// Aplica rotaciones 4D
		v = rotate4D(v,
					 rot_xy, rot_xz, rot_xw,
					 rot_yz, rot_yw, rot_zw);

		// Rango visible de la dimension W
		if (v.w >= w_min && v.w <= w_max)
		{
			float scale = projection_distance / (projection_distance - v.w);
			projected.push_back(Vector3(v.x * scale, v.y * scale, v.z * scale));
			filtered_indices.push_back(v_org.index);
			index_mapping[v_org.index] = filtered_indices.size() - 1;
		}
	}

	if (projected.empty())
	{
		print_error("[MESH 4D] No hay vertices para mostrar");
		return;
	}

	SurfaceTool *st = memnew(SurfaceTool);
	if (show_faces)
		st->begin(Mesh::PRIMITIVE_TRIANGLES);
	else
		st->begin(Mesh::PRIMITIVE_LINES);

	for (const auto &v : projected)
	{
		st->add_vertex(v);
	}

	// Para cada cuadrado, crear 2 triangulos
	if (show_faces)
	{
		//  pinta caras
		for (const auto &face : faces)
		{
			// si todos los vertices del cuadrado no estan visibles, se omite la cara
			if (index_mapping[face.v1] == -1 || index_mapping[face.v2] == -1 || index_mapping[face.v3] == -1)
				continue;

			// Triangulo
			st->add_index(index_mapping[face.v1]);
			st->add_index(index_mapping[face.v2]);
			st->add_index(index_mapping[face.v3]);
		}
	}
	else
	{
		// pinta aristas
		// Crea malla de lineas conectando vertices adyacentes
		// (en un hipercubo, los vertices adyacentes son aquellos que difieren en exactamente un bit en su indice)
		// if (show_edges)
		{
			for (int a = 0; a < (int)filtered_indices.size(); a++)
			{
				for (int b = a + 1; b < (int)filtered_indices.size(); b++)
				{
					int diff = filtered_indices[a] ^ filtered_indices[b];

					// Si diff es potencia de 2 (solo 1 bit activo),
					// los vertices son adyacentes en el hipercubo
					if (count_set_bits(diff) == 1)
					{
						st->add_index(a);
						st->add_index(b);
					}
				}
			}
		}
	}

	Ref<ArrayMesh> mesh = st->commit();
	mesh_instance->set_mesh(mesh);
}
