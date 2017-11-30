#include "../include/mesh.h"

VertexData::VertexData() 
{ 
	vertex = glm::vec3(0.0f, 0.0f, 0.0f);
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
	textureCoords = glm::vec2(0.0f, 0.0f);
}

VertexData::VertexData(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec2& textureCoords)
{
	this->vertex = vertex;
	this->normal = normal;
	this->textureCoords = textureCoords;
}

MeshNode::MeshNode(aiMesh *mesh) 
{
	m_vbo = NULL;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexCount = mesh->mNumFaces * 3;

	m_vertices = new VertexData[m_vertexCount];

	for (int i = 0; i < mesh->mNumVertices; ++i) 
	{
		// If mesh data has positions then sert vertex position
		if (mesh->HasPositions())
		{
			m_vertices[i].vertex.x = mesh->mVertices[i].x;
			m_vertices[i].vertex.y = mesh->mVertices[i].y;
			m_vertices[i].vertex.z = mesh->mVertices[i].z;
		}

		// If mesh data has normals then sert vertex position
		if (mesh->HasNormals())
		{
			m_vertices[i].normal.x = mesh->mNormals[i].x;
			m_vertices[i].normal.y = mesh->mNormals[i].y;
			m_vertices[i].normal.z = mesh->mNormals[i].z;
		}

		// If mesh data has texture coordinates then sert vertex position
		if (mesh->HasTextureCoords(0))
		{
			m_vertices[i].textureCoords.x = mesh->mTextureCoords[0][i].x;
			m_vertices[i].textureCoords.y = mesh->mTextureCoords[0][i].y;
		}
	}

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * mesh->mNumVertices * sizeof(GLfloat), m_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	if (mesh->HasFaces())
	{
		unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];
		for (int i = 0; i < mesh->mNumFaces; ++i) 
		{
			indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_STATIC_DRAW);

		delete[] indices;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

MeshNode::~MeshNode() 
{
	delete[] m_vertices;

	if (m_vbo)
		glDeleteBuffers(1, &m_vbo);

	if (m_ibo)
		glDeleteBuffers(1, &m_ibo);

	glDeleteVertexArrays(1, &m_vao);
}

void MeshNode::render() 
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

Mesh::Mesh(const char* filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, NULL);

	if (scene)
		for (int i = 0; i < scene->mNumMeshes; ++i) 
			m_nodes.push_back(new MeshNode(scene->mMeshes[i]));
}

Mesh::~Mesh()
{
	for (int i = 0; i < m_nodes.size(); ++i)
		delete m_nodes.at(i);

	m_nodes.clear();
}

void Mesh::render(glm::mat4& modelMatrix, const ShaderProgram& shader) const
{
	shader.setUniform_mat4("model", &modelMatrix[0][0]);

	for (int i = 0; i < m_nodes.size(); ++i)
		m_nodes.at(i)->render();
}