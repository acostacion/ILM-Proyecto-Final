#include "mesh_instance_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>

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

static Vector3 v4_to_v3(const Vector4 &v4, bool orthographic, float projection_distance, Vector4 p_scale = Vector4(1, 1, 1, 1))
{
    Vector3 v3;
    float scale;
    if (orthographic)
        scale = 1;
    else
        scale = projection_distance / (projection_distance - (p_scale.w * v4.w));

    return Vector3(v4.x * p_scale.x * scale, v4.y * p_scale.y * scale, v4.z * p_scale.z * scale);
}

// Interpolar 4D para que W = w_target
static Vector4 interp_w(const Vector4 &a, const Vector4 &b, float w_target)
{
    float t = (w_target - a.w) / (b.w - a.w);
    return Vector4(
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z),
        w_target);
}

// Clip un poligono contra un plano W
// Si true keep_above, mantiene W >= w_plane; si false, W <= w_plane
static std::vector<Vector4> clip_polygon_w(const std::vector<Vector4> &polygon, float w_plane, bool keep_above)
{
    std::vector<Vector4> result;
    if (polygon.empty())
        return result;

    for (size_t i = 0; i < polygon.size(); i++)
    {
        Vector4 current = polygon[i];
        Vector4 next = polygon[(i + 1) % polygon.size()];

        bool curr_in = keep_above ? (current.w >= w_plane) : (current.w <= w_plane);
        bool next_in = keep_above ? (next.w >= w_plane) : (next.w <= w_plane);

        if (curr_in)
        {
            result.push_back(current);
            if (!next_in)
                result.push_back(interp_w(current, next, w_plane));
        }
        else if (next_in)
        {
            result.push_back(interp_w(current, next, w_plane));
        }
    }
    return result;
}
#pragma endregion

void MeshInstance4D::draw_faces(const std::vector<Vector4> &transformed_vertex)
{
    SurfaceTool *st = memnew(SurfaceTool);
    st->begin(Mesh::PRIMITIVE_TRIANGLES);

    int vertex_count = 0;
    //  pinta caras
    for (const auto &face : faces)
    {
        std::vector<Vector4> polygon = {
            transformed_vertex[face.v1],
            transformed_vertex[face.v2],
            transformed_vertex[face.v3]};

        // Clip contra w_min (mantener W >= w_min)
        polygon = clip_polygon_w(polygon, w_min, true);
        // Clip contra w_max (mantener W <= w_max)
        polygon = clip_polygon_w(polygon, w_max, false);
        // Si quedan menos de 3 vertices, no hay triangulo que dibujar
        if (polygon.size() < 3)
            continue;

        // Convertir poligono en triangulos, un poligono de N vertices se divide en N-2 triangulos
        for (size_t i = 1; i < polygon.size() - 1; i++)
        {
            // Proyectamos en el mundo 3D los vertices 4D
            Vector3 p1 = v4_to_v3(polygon[0] + position, orthographic, projection_distance, scale);
            Vector3 p2 = v4_to_v3(polygon[i] + position, orthographic, projection_distance, scale);
            Vector3 p3 = v4_to_v3(polygon[i + 1] + position, orthographic, projection_distance, scale);

            // Calcular la normal
            Vector3 normal = (p2 - p1).cross(p3 - p1).normalized();

            // Agregar a la malla su normal y vertices
            st->set_normal(normal);
            st->add_vertex(p1);
            st->add_vertex(p2);
            st->add_vertex(p3);
            // Triangulo
            st->add_index(vertex_count);
            st->add_index(vertex_count + 1);
            st->add_index(vertex_count + 2);
            vertex_count += 3;
        }
    }

    Ref<ArrayMesh> mesh = st->commit();
    mesh_instance->set_mesh(mesh);
}

void MeshInstance4D::draw_edges(const std::vector<Vector4> &transformed_vertex)
{
    SurfaceTool *st = memnew(SurfaceTool);
    st->begin(Mesh::PRIMITIVE_LINES);

    for (const auto &v : transformed_vertex)
        st->add_vertex(v4_to_v3(v + position, orthographic, projection_distance, scale));

    // Conectar segun los indices originales
    for (const auto &face : faces)
    {
        st->add_index(face.v1);
        st->add_index(face.v2);
        st->add_index(face.v2);
        st->add_index(face.v3);
        st->add_index(face.v3);
        st->add_index(face.v1);
    }

    Ref<ArrayMesh> mesh = st->commit();
    mesh_instance->set_mesh(mesh);
}

void MeshInstance4D::_bind_methods()
{
    // Visualizacion
    ClassDB::bind_method(D_METHOD("set_mesh", "mesh"), &MeshInstance4D::set_mesh);
    ClassDB::bind_method(D_METHOD("get_mesh"), &MeshInstance4D::get_mesh);
    ClassDB::bind_method(D_METHOD("set_wireframe", "wireframe"), &MeshInstance4D::set_wireframe);
    ClassDB::bind_method(D_METHOD("get_wireframe"), &MeshInstance4D::get_wireframe);
    ClassDB::bind_method(D_METHOD("set_orthographic", "orthographic"), &MeshInstance4D::set_orthographic);
    ClassDB::bind_method(D_METHOD("get_orthographic"), &MeshInstance4D::get_orthographic);
    // Distancia de proyeccion
    ClassDB::bind_method(D_METHOD("set_projection_distance", "distance"), &MeshInstance4D::set_projection_distance);
    ClassDB::bind_method(D_METHOD("get_projection_distance"), &MeshInstance4D::get_projection_distance);
    // Rango visible de la dimension W
    ClassDB::bind_method(D_METHOD("set_w_min", "w_min"), &MeshInstance4D::set_w_min);
    ClassDB::bind_method(D_METHOD("get_w_min"), &MeshInstance4D::get_w_min);
    ClassDB::bind_method(D_METHOD("set_w_max", "w_max"), &MeshInstance4D::set_w_max);
    ClassDB::bind_method(D_METHOD("get_w_max"), &MeshInstance4D::get_w_max);
    // Propiedades
    ADD_GROUP("4D Visual", "");    
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "wireframe", PROPERTY_HINT_RANGE, "0,1,1"), "set_wireframe", "get_wireframe");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "orthographic", PROPERTY_HINT_RANGE, "0,1,1"), "set_orthographic", "get_orthographic");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "projection_distance"), "set_projection_distance", "get_projection_distance");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "w_min"), "set_w_min", "get_w_min");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "w_max"), "set_w_max", "get_w_max");
}

MeshInstance4D::MeshInstance4D() : w_min(-1.0f), w_max(1.0f)
{
    // Crea MeshInstance3D hijo
    mesh_instance = memnew(MeshInstance3D);
    add_child(mesh_instance);
    // Ref<StandardMaterial3D> material = memnew(StandardMaterial3D);
    // material->set_albedo(Color(0.2f, 0.7f, 1.0f, 1.0f)); // Azul
    // material->set_shading_mode(BaseMaterial3D::SHADING_MODE_UNSHADED);
    // material->set_cull_mode(BaseMaterial3D::CULL_DISABLED);             // Mostrar ambas caras
    // material->set_shading_mode(BaseMaterial3D::SHADING_MODE_PER_PIXEL); // Iluminacion por pixel
    // mesh_instance->set_material_override(material);
}

void MeshInstance4D::_generate_vertex()
{
    vertex.clear();

    // Validar que la mesh exista y tenga surfaces
    if (!mesh.is_valid() || mesh->get_surface_count() == 0)
    {
        print_error("[MeshInstance4D] Mesh no valida o sin superficies");
        return;
    }

    // Obtener los arrays del primer surface
    Array surface_arrays = mesh->surface_get_arrays(0);

    // ARRAY_VERTEX contiene los vertices como Vector3
    PackedVector3Array vertices_3d = surface_arrays[Mesh::ARRAY_VERTEX];

    // Convertir cada vertice 3D a 4D (agregando W=0)
    for (int i = 0; i < vertices_3d.size(); i++)
    {
        Vector3 v3 = vertices_3d[i];
        Vector4 v4(v3.x, v3.y, v3.z, 0.0f); // W=0 por defecto
        vertex.push_back({i, v4});
    }
}

void MeshInstance4D::_generate_faces()
{
    faces.clear();

    if (!mesh.is_valid() || mesh->get_surface_count() == 0)
    {
        print_error("[MeshInstance4D] Mesh no valida o sin superficies");
        return;
    }

    // Obtener los arrays del primer surface
    Array surface_arrays = mesh->surface_get_arrays(0);

    // ARRAY_INDEX contiene los indices como enteros
    PackedInt32Array indices = surface_arrays[Mesh::ARRAY_INDEX];

    // Los indices vienen en trio. (i0, i1, i2) forman un triangulo
    for (int i = 0; i < indices.size(); i += 3)
    {
        faces.push_back({indices[i], indices[i + 1], indices[i + 2]});
    }
}

void MeshInstance4D::_update_mesh()
{
    if (!mesh_instance)
        return;

    // Vertices transformados
    std::vector<Vector4> transformed_vertex;

    // Aplicamos las transformaciones a los vertices
    for (const auto &v_org : vertex)
    {
        Vector4 v = v_org.position;
        // Aplica size
        v += position;
        // Aplica rotaciones 4D
        v = rotate4D(v, rotation);
        transformed_vertex.push_back(v);
    }

    if (transformed_vertex.empty())
    {
        print_error("[MESH 4D] No hay vertices para mostrar");
        return;
    }

    // Distinguir modo wireframe
    if (show_edges)
        draw_edges(transformed_vertex);
    else
        draw_faces(transformed_vertex);
}
