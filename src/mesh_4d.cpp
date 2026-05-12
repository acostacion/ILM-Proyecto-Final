#include "mesh_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cmath>
#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;
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

void Mesh4D::_bind_methods()
{
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
      rot_xy(0.0f), rot_xz(0.0f), rot_xw(0.5f),
      rot_yz(0.0f), rot_yw(0.0f), rot_zw(0.0f)
{
	// Crea MeshInstance3D hijo
	mesh_instance = memnew(MeshInstance3D);
	add_child(mesh_instance);

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
	// 						      |   \                     |  \
	//							  |    \                    |   \
	//							  |  (-h,-h,+h,-h) ------------|- (+h,-h,+h,-h)
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
	//    |   \                     |  \
	//	  |    \                    |   \
	//	  |  (-h,-h,+h,+h) ------------|- (+h,-h,+h,+h)
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
		float x = ((i >> 0) & 1) ? 1.0f : -1.0f;
		float y = ((i >> 1) & 1) ? 1.0f : -1.0f;
		float z = ((i >> 2) & 1) ? 1.0f : -1.0f;
		float w = ((i >> 3) & 1) ? 1.0f : -1.0f;

		vertex_4d.push_back(Vector4(x, y, z, w)); // ← Almacenar
		vertex_index.push_back(i);
	}
	update_mesh();
}

Mesh4D::~Mesh4D()
{
}

void Mesh4D::_process(double delta) {}

void Mesh4D::update_mesh()
{
	if (!mesh_instance)
		return;

	float h = size / 2.0f;
	const float projection_distance = 3.0f;

	// vertices proyectados en 3D
	std::vector<Vector3> projected;
	std::vector<int> filtered_indices; // Indices de vertices que pasaron el filtro W

	for (int i = 0; i < (int)vertex_4d.size(); i++)
	{
		Vector4 v = vertex_4d[i];
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
			filtered_indices.push_back(vertex_index[i]);
		}
	}

	// Crea malla de lineas conectando vertices adyacentes
	// (en un hipercubo, los vertices adyacentes son aquellos que difieren en exactamente un bit en su indice)
	SurfaceTool *st = memnew(SurfaceTool);
	st->begin(Mesh::PRIMITIVE_LINES);

	for (const auto &v : projected)
	{
		// st->set_color(Color(0.2f, 0.8f, 1.0f, 1.0f));
		st->add_vertex(v);
	}

	// Conecta solo vertices que difieren en 1 bit (aristas reales del hipercubo)
	for (int a = 0; a < (int)filtered_indices.size(); a++)
	{
		for (int b = a + 1; b < (int)filtered_indices.size(); b++)
		{
			int diff = filtered_indices[a] ^ filtered_indices[b];

			// Si diff es potencia de 2 (solo 1 bit activo),
			// los vertices son adyacentes en el hipercubo
			if (diff && !(diff & (diff - 1)))
			{
				st->add_index(a);
				st->add_index(b);
			}
		}
	}

	Ref<ArrayMesh> mesh = st->commit();
	mesh_instance->set_mesh(mesh);
}

void Mesh4D::set_size(float p_size)
{
	size = p_size;
	update_mesh();
}
float Mesh4D::get_size() const { return size; }

void Mesh4D::set_w_min(float p_min)
{
	w_min = p_min;
	update_mesh();
}
float Mesh4D::get_w_min() const { return w_min; }

void Mesh4D::set_w_max(float p_max)
{
	w_max = p_max;
	update_mesh();
}
float Mesh4D::get_w_max() const { return w_max; }

void Mesh4D::set_rot_xy(float p_rot)
{
	rot_xy = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_xy() const
{
	return rot_xy;
}

void Mesh4D::set_rot_xz(float p_rot)
{
	rot_xz = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_xz() const
{
	return rot_xz;
}

void Mesh4D::set_rot_xw(float p_rot)
{
	rot_xw = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_xw() const
{
	return rot_xw;
}

void Mesh4D::set_rot_yz(float p_rot)
{
	rot_yz = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_yz() const
{
	return rot_yz;
}

void Mesh4D::set_rot_yw(float p_rot)
{
	rot_yw = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_yw() const
{
	return rot_yw;
}

void Mesh4D::set_rot_zw(float p_rot)
{
	rot_zw = p_rot;
	update_mesh();
}

float Mesh4D::get_rot_zw() const
{
	return rot_zw;
}
