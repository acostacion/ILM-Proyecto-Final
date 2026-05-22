#pragma once

#ifndef MESH_4D_HPP
#define MESH_4D_HPP

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>
#include <vector>
#include <unordered_map>

namespace godot
{
	// Cada vertice tiene un indice unico
	// Cada vertice es un Vector4 (x, y, z, w)
	struct vertex
	{
		int index;
		Vector4 position;
		bool operator==(const vertex &other) const
		{
			return position == other.position;
		}
	};
	struct triangle
	{
		int v1, v2, v3; // Indices de los vertices que forman el triangulo
	};

	class Mesh4D : public Node3D
	{
		GDCLASS(Mesh4D, Node3D)
		std::vector<vertex> vertex;
		// Almacenar los vertices del modelo
		// std::vector<vertex> vertex;
		// Cada triangulo es un struct de 3 indices de vertices
		std::vector<triangle> faces;

		bool show_edges = false; // Mostrar aristas
		bool show_faces = true;	 // Mostrar caras (triangulos)
	private:
	protected:
		static void _bind_methods();
		float projection_distance = 10.0f;

		float size = 1.0f;
		float w_min = -0.5f, w_max = 0.5f;
		float rot_xy = 0.0f, rot_xz = 0.0f, rot_xw = 0.0f;
		float rot_yz = 0.0f, rot_yw = 0.0f, rot_zw = 0.0f;
		MeshInstance3D *mesh_instance = nullptr;

		// Generar los 24 cuadrados (6 caras * 4 cuadrados por cara)
		void generate_faces();

		// Actualizar la malla
		void update_mesh();

	public:
		Mesh4D();
		~Mesh4D() = default;

		void _process(double delta) override;
		// SETTERS Y GETTERS

		void set_size(float p_size)
		{
			size = p_size;
			update_mesh();
		}
		float get_size() const { return size; }

		// Rango visible en W
		void set_w_min(float p_min)
		{
			w_min = p_min;
			update_mesh();
		}
		float get_w_min() const { return w_min; }
		void set_w_max(float p_max)
		{
			w_max = p_max;
			update_mesh();
		}
		float get_w_max() const { return w_max; }
		// Visualizacion
		void set_wireframe(bool p_show)
		{
			show_edges = p_show;
			show_faces = !p_show;
			update_mesh();
		}
		bool get_wireframe() const { return show_edges; }
		void set_projection_distance(float p_distance)
		{
			projection_distance = p_distance;
			update_mesh();
		}
		float get_projection_distance() const
		{ return projection_distance; }
		// Rotaciones 4D
		void set_rot_xy(float p_rot)
		{
			rot_xy = p_rot;
			update_mesh();
		}
		float get_rot_xy() const
		{
			return rot_xy;
		}
		void set_rot_xz(float p_rot)
		{
			rot_xz = p_rot;
			update_mesh();
		}
		float get_rot_xz() const
		{
			return rot_xz;
		}
		void set_rot_xw(float p_rot)
		{
			rot_xw = p_rot;
			update_mesh();
		}
		float get_rot_xw() const
		{
			return rot_xw;
		}
		void set_rot_yz(float p_rot)
		{
			rot_yz = p_rot;
			update_mesh();
		}
		float get_rot_yz() const
		{
			return rot_yz;
		}
		void set_rot_yw(float p_rot)
		{
			rot_yw = p_rot;
			update_mesh();
		}
		float get_rot_yw() const
		{
			return rot_yw;
		}
		void set_rot_zw(float p_rot)
		{
			rot_zw = p_rot;
			update_mesh();
		}
		float get_rot_zw() const
		{
			return rot_zw;
		}
	};

} // namespace godot
#endif