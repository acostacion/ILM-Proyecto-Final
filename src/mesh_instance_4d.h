#pragma once
#include <vector>

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>

#include "node_4d.hpp"
#include "mesh_4d.hpp"

namespace godot
{
    // fordward declaration
    class MeshInstance3D;

    class MeshInstance4D : public Node4D
    {
        GDCLASS(MeshInstance4D, Node4D)

        // // Vertices de 4 coordenadas
        // std::vector<Vertex> vertices;
        // // Cada triangulo es un struct de 3 indices de vertices
        // std::vector<Triangle> faces;

        void draw_faces(const std::vector<Vector4> &transformed_vertex);
        void draw_edges(const std::vector<Vector4> &transformed_vertex);

    protected:
        static void _bind_methods();
        // Referencia a la mesh que utilizamos
        Ref<Mesh4D> mesh = nullptr;
        // Usamos un MeshInstance3D como renderer en el mundo 3D
        MeshInstance3D *mesh_instance = nullptr;

        // Mostrar aristas
        bool show_edges = false;
        // Mostrar caras (triangulos)
        bool show_faces = true;

        // Rango de w visible
        float w_min = -1.0f, w_max = 1.0f;
        // Distancia de proyeccion
        float projection_distance = 3.0f;
        // Prespectiva u ortografica en eje w
        bool orthographic = false;

        // Actualizar la malla
        void _update_mesh();

    public:
        MeshInstance4D();
        ~MeshInstance4D() = default;

        // SETTERS Y GETTERS
        // Mesh
        void set_mesh(Ref<Mesh4D> p_mesh)
        {
            mesh = p_mesh;
            if (mesh.is_valid())
                _update_mesh();
        }
        Ref<Mesh4D> get_mesh() { return mesh; }
        // Rango visible en W
        void set_w_min(float p_min)
        {
            w_min = p_min;
            _update_mesh();
        }
        float get_w_min() const { return w_min; }
        void set_w_max(float p_max)
        {
            w_max = p_max;
            _update_mesh();
        }
        float get_w_max() const { return w_max; }
        // Visualizacion
        void set_wireframe(bool p_show)
        {
            show_edges = p_show;
            show_faces = !p_show;
            _update_mesh();
        }
        bool get_wireframe() const { return show_edges; }
        void set_orthographic(bool p_ortho)
        {
            orthographic = p_ortho;
            _update_mesh();
        }
        bool get_orthographic() const { return orthographic; }
        void set_projection_distance(float p_distance)
        {
            projection_distance = p_distance;
            _update_mesh();
        }
        float get_projection_distance() const { return projection_distance; }
        // Override de setters para actualizar la malla
        void set_position(Vector4 p_position) override
        {
            Node4D::set_position(p_position);
            _update_mesh();
        }

        void set_scale(Vector4 p_scale) override
        {
            Node4D::set_scale(p_scale);
            _update_mesh();
        }
        void set_rot_xy(float p_xy) override
        {
            Node4D::set_rot_xy(p_xy);
            _update_mesh();
        }

        void set_rot_xz(float p_xz) override
        {
            Node4D::set_rot_xz(p_xz);
            _update_mesh();
        }

        void set_rot_xw(float p_xw) override
        {
            Node4D::set_rot_xw(p_xw);
            _update_mesh();
        }

        void set_rot_yz(float p_yz) override
        {
            Node4D::set_rot_yz(p_yz);
            _update_mesh();
        }

        void set_rot_yw(float p_yw) override
        {
            Node4D::set_rot_yw(p_yw);
            _update_mesh();
        }

        void set_rot_zw(float p_zw) override
        {
            Node4D::set_rot_zw(p_zw);
            _update_mesh();
        }
    };

} // namespace godot