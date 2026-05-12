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

namespace godot
{

	class Mesh4D : public Node3D
	{
		GDCLASS(Mesh4D, Node3D)

		std::vector<int> vertex_index;
		std::vector<Vector4> vertex_4d;
	private:
	protected:
		static void _bind_methods();

		float size = 1.0f;
		float w_min = -0.5f, w_max = 0.5f;
		float rot_xy = 0.0f, rot_xz = 0.0f, rot_xw = 0.0f;
		float rot_yz = 0.0f, rot_yw = 0.0f, rot_zw = 0.0f;
		MeshInstance3D *mesh_instance = nullptr;

	public:
		Mesh4D();
		~Mesh4D();

		void _process(double delta) override;
		void set_size(float p_size);
		float get_size() const;
		void set_w_min(float p_min);
		float get_w_min() const;
		void set_w_max(float p_max);
		float get_w_max() const;
		void update_mesh();
		// Rotaciones 4D
		void set_rot_xy(float p_rot);
		float get_rot_xy() const;
		void set_rot_xz(float p_rot);
		float get_rot_xz() const;
		void set_rot_xw(float p_rot);
		float get_rot_xw() const;
		void set_rot_yz(float p_rot);
		float get_rot_yz() const;
		void set_rot_yw(float p_rot);
		float get_rot_yw() const;
		void set_rot_zw(float p_rot);
		float get_rot_zw() const;
	};

} // namespace godot
#endif