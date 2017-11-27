#pragma once


#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "shader_program.h"


//! A single vertices data store.
/*! Stores the necessary data for a single Mesh vertex. */
struct VertexData
{
	glm::vec3 vertex; /*!< The position of the vertex. */
	glm::vec3 normal; /*!< The normal vector of the vertex */
	glm::vec2 textureCoords; /*!< The texture coordinates */

	//! Default constructor.
	VertexData();

	//! Constructs a VertexData object.
	VertexData(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec2& textureCoords);
};

//! A node contained within Mesh objects.
/*! MeshNode objects a individual descriptions of geometry which alone or together with parent and/or child MeshNode objects make up a Mesh. */
struct MeshNode {
	VertexData* m_vertices; /*!< Mesh vertex data collection. */
	unsigned int m_vertexCount; /*! Number of the meshes vertices. */

	GLuint m_vao; /*!< The Meshes own Vertex Array Object for independent rendering. */
	GLuint m_vbo; /*!< The Meshes own Vertex Buffer Object containing all of its vertexc data. */
	GLuint m_ibo; /*!< The Meshes own Index Buffer Object containing the vertex indices for more efficient rendering. */

	//! Construct a MeshNode from an Assimp mesh object.
	/*! @param mesh A pointer to the Assimp mesh used to construct the MeshNode. */
	MeshNode(aiMesh* mesh);

	//! Destructor.
	~MeshNode();

	//! Render the MeshNode.
	void render();
};

//! A 3D mesh containing vertex data.
/*! Meshes are used to store buffers of vertex data including their normals and texture coordinates. */
class Mesh
{
public:

	//! Create a Mesh from file.
	/*! Create a mesh from a file containing vertex position, normal, texture coordinate, and polygonal data. */
	Mesh(const char* filepath);

	//! Destruct Mesh.
	~Mesh();

	//! Render the Mesh with some transform.
	/*! Renders the Mesh using its own OpenGL VAO and VBO.
	  * @param modelMatrix The transformation matrix to use when rendering the Mesh. */
	void render(glm::mat4& modelMatrix, const ShaderProgram& shader) const;

private:
	std::vector<MeshNode*> m_nodes; /*! Collection of the meshes nodes/components/children. */
};