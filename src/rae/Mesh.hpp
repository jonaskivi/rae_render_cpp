#ifndef RAE_3D_MESH_HPP
#define RAE_3D_MESH_HPP

#include <vector>
#include <string>
using namespace std;

#include <glm/glm.hpp>

//ASSIMP
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
//end // ASSIMP

namespace Rae
{

class Mesh
{
public:
	int id() { return m_id; }
protected:
	void id(int set) { m_id = set; }
	int m_id;

public:
	Mesh(int set_id);
	~Mesh();
	
	void generateBox();

	//ASSIMP
	bool loadModel(const string& filepath);
	void loadNode(const aiScene* scene, const aiNode* node);
	//end // ASSIMP

	void createVBOs();

	void render(unsigned set_shader_program_id);

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;

	unsigned vertexBufferID;
	unsigned uvBufferID;
	unsigned normalBufferID;
	unsigned indexBufferID;
};

}//end namespace Rae

#endif
