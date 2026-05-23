#pragma once
#include "node_4d.hpp"

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

	class Mesh4D : public Node4D
	{
		GDCLASS(Mesh4D, Node4D)
		std::vector<vertex> vertex;
		// Cada triangulo es un struct de 3 indices de vertices
		std::vector<triangle> faces;

		bool show_edges = false; // Mostrar aristas
		bool show_faces = true;	 // Mostrar caras (triangulos)

		void draw_faces(const std::vector<Vector4> &transformed_vertex);
		void draw_edges(const std::vector<Vector4> &transformed_vertex);

	protected:
		static void _bind_methods();
		float w_min = -1.0f, w_max = 1.0f;
		float projection_distance = 3.0f;
		bool orthographic = false;
		float size = 2.0f;

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
		void set_orthographic(bool p_ortho)
		{
			orthographic = p_ortho;
			update_mesh();
		}
		bool get_orthographic() const { return orthographic; }
		void set_projection_distance(float p_distance)
		{
			projection_distance = p_distance;
			update_mesh();
		}
		float get_projection_distance() const { return projection_distance; }
		void set_size(float p_size)
		{
			size = p_size;
			update_mesh();
		}
		float get_size() { return size; }

		// Override de setters para actualizar la malla
		void set_position(Vector4 p_position) override
		{
			Node4D::set_position(p_position);
			update_mesh();
		}

		void set_scale(Vector4 p_scale) override
		{
			Node4D::set_scale(p_scale);
			update_mesh();
		}
		void set_rot_xy(float p_xy) override
		{
			Node4D::set_rot_xy(p_xy);
			update_mesh();
		}

		void set_rot_xz(float p_xz) override
		{
			Node4D::set_rot_xz(p_xz);
			update_mesh();
		}

		void set_rot_xw(float p_xw) override
		{
			Node4D::set_rot_xw(p_xw);
			update_mesh();
		}

		void set_rot_yz(float p_yz) override
		{
			Node4D::set_rot_yz(p_yz);
			update_mesh();
		}

		void set_rot_yw(float p_yw) override
		{
			Node4D::set_rot_yw(p_yw);
			update_mesh();
		}

		void set_rot_zw(float p_zw) override
		{
			Node4D::set_rot_zw(p_zw);
			update_mesh();
		}
	};

} // namespace godot