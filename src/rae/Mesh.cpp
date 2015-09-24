
#include "GL/glew.h"
#include "Mesh.hpp"

#include <iostream>
#include <fstream>

namespace Rae
{

Mesh::Mesh(int set_id)
: m_id(set_id)
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &uvBufferID);
	glDeleteBuffers(1, &normalBufferID);
	glDeleteBuffers(1, &indexBufferID);	
}

//version without initializer lists (vs2012):
void Mesh::generateBox()
{
	std::cout<<"Generating Mesh.\n";

	float boxSize = 0.5f; // Actually half of the box size

    vertices.push_back( glm::vec3(-boxSize,  boxSize,  boxSize) ); // 0
	vertices.push_back( glm::vec3( boxSize,  boxSize,  boxSize) ); // 1
	vertices.push_back( glm::vec3( boxSize,  boxSize, -boxSize) ); // 2
	vertices.push_back( glm::vec3(-boxSize,  boxSize, -boxSize) ); // 3

	vertices.push_back( glm::vec3(-boxSize, -boxSize,  boxSize) ); // 4
	vertices.push_back( glm::vec3(-boxSize, -boxSize, -boxSize) ); // 5
	vertices.push_back( glm::vec3( boxSize, -boxSize, -boxSize) ); // 6
	vertices.push_back( glm::vec3( boxSize, -boxSize,  boxSize) ); // 7

	vertices.push_back( glm::vec3(-boxSize, -boxSize, -boxSize) ); // 8
	vertices.push_back( glm::vec3(-boxSize,  boxSize, -boxSize) ); // 9
	vertices.push_back( glm::vec3( boxSize,  boxSize, -boxSize) ); // 10
	vertices.push_back( glm::vec3( boxSize, -boxSize, -boxSize) ); // 11
		
	vertices.push_back( glm::vec3( boxSize, -boxSize,  boxSize) ); // 12
	vertices.push_back( glm::vec3( boxSize,  boxSize,  boxSize) ); // 13
	vertices.push_back( glm::vec3(-boxSize,  boxSize,  boxSize) ); // 14
	vertices.push_back( glm::vec3(-boxSize, -boxSize,  boxSize) ); // 15

	vertices.push_back( glm::vec3(-boxSize, -boxSize,  boxSize) ); // 16
	vertices.push_back( glm::vec3(-boxSize,  boxSize,  boxSize) ); // 17
	vertices.push_back( glm::vec3(-boxSize,  boxSize, -boxSize) ); // 18
	vertices.push_back( glm::vec3(-boxSize, -boxSize, -boxSize) ); // 19
		
	vertices.push_back( glm::vec3( boxSize, -boxSize, -boxSize) ); // 20
	vertices.push_back( glm::vec3( boxSize,  boxSize, -boxSize) ); // 21
	vertices.push_back( glm::vec3( boxSize,  boxSize,  boxSize) ); // 22
	vertices.push_back( glm::vec3( boxSize, -boxSize,  boxSize) );// 23

	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0
		
	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0

	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0

	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0

	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0

	uvs.push_back( glm::vec2( 1.0f,  0.0f) ); // 1
	uvs.push_back( glm::vec2( 1.0f,  1.0f) ); // 2
	uvs.push_back( glm::vec2( 0.0f,  1.0f) ); // 3
	uvs.push_back( glm::vec2( 0.0f,  0.0f) ); // 0

	// *--------*
	// |\      /|
	// | *----* |
	// | |    | |
	// | *----* |
	// |/      \|
	// *--------*

	// 0--------1
	//  \      /
	//   3----2 
	//       
	//   5----6 
	//  /      \
	// 4--------7

	// 14------13
	// |        |
	// | 9---10 |
	// | |    | |
	// | 8---11 |
	// |        |
	// 15------12

	// 17       22
	// |\      /|
	// | 18   21|
	// | |    | |
	// | 19   20|
	// |/      \|
	// 16      23

	normals.push_back( glm::vec3( 0.0f,  1.0f,  0.0f) ); // 0
	normals.push_back( glm::vec3( 0.0f,  1.0f,  0.0f) ); // 1
	normals.push_back( glm::vec3( 0.0f,  1.0f,  0.0f) ); // 2
	normals.push_back( glm::vec3( 0.0f,  1.0f,  0.0f) ); // 3
		
	normals.push_back( glm::vec3( 0.0f, -1.0f,  0.0f) ); // 0
	normals.push_back( glm::vec3( 0.0f, -1.0f,  0.0f) ); // 1
	normals.push_back( glm::vec3( 0.0f, -1.0f,  0.0f) ); // 2
	normals.push_back( glm::vec3( 0.0f, -1.0f,  0.0f) ); // 3

	normals.push_back( glm::vec3( 0.0f,  0.0f, -1.0f) ); // 0
	normals.push_back( glm::vec3( 0.0f,  0.0f, -1.0f) ); // 1
	normals.push_back( glm::vec3( 0.0f,  0.0f, -1.0f) ); // 2
	normals.push_back( glm::vec3( 0.0f,  0.0f, -1.0f) ); // 3

	normals.push_back( glm::vec3( 0.0f,  0.0f,  1.0f) ); // 0
	normals.push_back( glm::vec3( 0.0f,  0.0f,  1.0f) ); // 1
	normals.push_back( glm::vec3( 0.0f,  0.0f,  1.0f) ); // 2
	normals.push_back( glm::vec3( 0.0f,  0.0f,  1.0f) ); // 3

	normals.push_back( glm::vec3(-1.0f,  0.0f,  0.0f) ); // 0
	normals.push_back( glm::vec3(-1.0f,  0.0f,  0.0f) ); // 1
	normals.push_back( glm::vec3(-1.0f,  0.0f,  0.0f) ); // 2
	normals.push_back( glm::vec3(-1.0f,  0.0f,  0.0f) ); // 3

	normals.push_back( glm::vec3( 1.0f,  0.0f,  0.0f) ); // 0
	normals.push_back( glm::vec3( 1.0f,  0.0f,  0.0f) ); // 1
	normals.push_back( glm::vec3( 1.0f,  0.0f,  0.0f) ); // 2
	normals.push_back( glm::vec3( 1.0f,  0.0f,  0.0f) );// 3
	
	//roof
	indices.push_back( 0);
	indices.push_back( 1);
	indices.push_back( 2);
	indices.push_back( 0);
	indices.push_back( 2);
	indices.push_back( 3);
	
	//floor
	indices.push_back( 4);
	indices.push_back( 5);
	indices.push_back( 6); 
	indices.push_back( 4);
	indices.push_back( 6);
	indices.push_back( 7); 

	//back
	indices.push_back( 8);
	indices.push_back( 9);
	indices.push_back(10);
	indices.push_back( 8);
	indices.push_back(10);
	indices.push_back(11);

	//front
	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(12);
	indices.push_back(14);
	indices.push_back(15);

	//left
	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(16);
	indices.push_back(18);
	indices.push_back(19);

	//right
	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(20);
	indices.push_back(22);
	indices.push_back(23);

	std::cout<<"size of: vertices: "<<vertices.size()<<" size of indices: "<<indices.size()<<"\n";	
}

/*
// C++11 version. TODO fix UVs in this version to be the same as above

void Mesh::generateBox()
{
	std::cout<<"Generating Mesh.\n";

	float boxSize = 0.5f; // Actually half of the box size

	vertices =
	{
		glm::vec3(-boxSize,  boxSize,  boxSize), // 0
		glm::vec3( boxSize,  boxSize,  boxSize), // 1
		glm::vec3( boxSize,  boxSize, -boxSize), // 2
		glm::vec3(-boxSize,  boxSize, -boxSize), // 3

		glm::vec3(-boxSize, -boxSize,  boxSize), // 4
		glm::vec3(-boxSize, -boxSize, -boxSize), // 5
		glm::vec3( boxSize, -boxSize, -boxSize), // 6
		glm::vec3( boxSize, -boxSize,  boxSize), // 7

		glm::vec3(-boxSize, -boxSize, -boxSize), // 8
		glm::vec3(-boxSize,  boxSize, -boxSize), // 9
		glm::vec3( boxSize,  boxSize, -boxSize), // 10
		glm::vec3( boxSize, -boxSize, -boxSize), // 11
		
		glm::vec3( boxSize, -boxSize,  boxSize), // 12
		glm::vec3( boxSize,  boxSize,  boxSize), // 13
		glm::vec3(-boxSize,  boxSize,  boxSize), // 14
		glm::vec3(-boxSize, -boxSize,  boxSize), // 15

		glm::vec3(-boxSize, -boxSize,  boxSize), // 16
		glm::vec3(-boxSize,  boxSize,  boxSize), // 17
		glm::vec3(-boxSize,  boxSize, -boxSize), // 18
		glm::vec3(-boxSize, -boxSize, -boxSize), // 19
		
		glm::vec3( boxSize, -boxSize, -boxSize), // 20
		glm::vec3( boxSize,  boxSize, -boxSize), // 21
		glm::vec3( boxSize,  boxSize,  boxSize), // 22
		glm::vec3( boxSize, -boxSize,  boxSize) // 23
	};

	uvs =
	{
		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f), // 3
		
		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f), // 3

		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f), // 3

		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f), // 3

		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f), // 3

		glm::vec2( 0.0f,  0.0f), // 0
		glm::vec2( 1.0f,  0.0f), // 1
		glm::vec2( 1.0f,  1.0f), // 2
		glm::vec2( 0.0f,  1.0f) // 3
	};

	// *--------*
	// |\      /|
	// | *----* |
	// | |    | |
	// | *----* |
	// |/      \|
	// *--------*

	// 0--------1
	//  \      /
	//   3----2 
	//       
	//   5----6 
	//  /      \
	// 4--------7

	// 14------13
	// |        |
	// | 9---10 |
	// | |    | |
	// | 8---11 |
	// |        |
	// 15------12

	// 17       22
	// |\      /|
	// | 18   21|
	// | |    | |
	// | 19   20|
	// |/      \|
	// 16      23

	normals =
	{
		glm::vec3( 0.0f,  1.0f,  0.0f), // 0
		glm::vec3( 0.0f,  1.0f,  0.0f), // 1
		glm::vec3( 0.0f,  1.0f,  0.0f), // 2
		glm::vec3( 0.0f,  1.0f,  0.0f), // 3
		
		glm::vec3( 0.0f,  -1.0f,  0.0f), // 0
		glm::vec3( 0.0f,  -1.0f,  0.0f), // 1
		glm::vec3( 0.0f,  -1.0f,  0.0f), // 2
		glm::vec3( 0.0f,  -1.0f,  0.0f), // 3

		glm::vec3( 0.0f,  0.0f,  -1.0f), // 0
		glm::vec3( 0.0f,  0.0f,  -1.0f), // 1
		glm::vec3( 0.0f,  0.0f,  -1.0f), // 2
		glm::vec3( 0.0f,  0.0f,  -1.0f), // 3

		glm::vec3( 0.0f,  0.0f,  1.0f), // 0
		glm::vec3( 0.0f,  0.0f,  1.0f), // 1
		glm::vec3( 0.0f,  0.0f,  1.0f), // 2
		glm::vec3( 0.0f,  0.0f,  1.0f), // 3

		glm::vec3( -1.0f,  0.0f,  0.0f), // 0
		glm::vec3( -1.0f,  0.0f,  0.0f), // 1
		glm::vec3( -1.0f,  0.0f,  0.0f), // 2
		glm::vec3( -1.0f,  0.0f,  0.0f), // 3

		glm::vec3( 1.0f,  0.0f,  0.0f), // 0
		glm::vec3( 1.0f,  0.0f,  0.0f), // 1
		glm::vec3( 1.0f,  0.0f,  0.0f), // 2
		glm::vec3( 1.0f,  0.0f,  0.0f) // 3
	};

	
	
	indices =
	{
		//roof
		0, 1, 2,
		0, 2, 3,
		
		//floor
		4, 5, 6, 
		4, 6, 7, 
		
		//back
		8, 9, 10,
		8, 10, 11,

		//front
		12, 13, 14,
		12, 14, 15,

		//left
		16, 17, 18,
		16, 18, 19,

		//right
		20, 21, 22,
		20, 22, 23

	};

	std::cout<<"size of: vertices: "<<vertices.size()<<" size of indices: "<<indices.size()<<"\n";	
}
*/

//ASSIMP
bool Mesh::loadModel(const string& filepath)
{
	Assimp::Importer importer;

	//Assimp::Logger::LogSeverity severity = Assimp::Logger::NORMAL;
	Assimp::Logger::LogSeverity severity = Assimp::Logger::VERBOSE;
	// Create a logger instance for Console Output
	Assimp::DefaultLogger::create("",severity, aiDefaultLogStream_STDOUT);
	// And another for file output
	Assimp::DefaultLogger::create("assimp_log.txt",severity, aiDefaultLogStream_FILE);
	Assimp::DefaultLogger::get()->info("this is my info-call");

	const aiScene* scene = nullptr;

	//check if file exists
	std::ifstream fin(filepath.c_str());
	if(!fin.fail())
	{
		fin.close();
	}
	else
	{
		cout << "Couldn't open file: " << filepath << "\n";
		//logInfo( importer.GetErrorString());
		cout << importer.GetErrorString() << "\n";
		return false;
	}

	scene = importer.ReadFile( filepath, /*aiProcessPreset_TargetRealtime_Quality*/0);

	if( !scene )
	{
		//logInfo( importer.GetErrorString());
		cout << importer.GetErrorString() << "\n";
		return false;
	}

	loadNode(scene, scene->mRootNode);

	createVBOs();

	cout << "Succesfully imported scene " << filepath << "\n";
	return true;
}

class AABB
{
public:
	AABB()
	: min(FLT_MAX, FLT_MAX, FLT_MAX),
	max(FLT_MIN, FLT_MIN, FLT_MIN)
	{
	}

	void grow(glm::vec3 set);

	glm::vec3 dimensions()
	{
		return max - min;
	}

	glm::vec3 min;
	glm::vec3 max;
};

void AABB::grow(glm::vec3 set)
{
	if(min.x > set.x)
		min.x = set.x;
	if(min.y > set.y)
		min.y = set.y;
	if(min.z > set.z)
		min.z = set.z;

	if(max.x < set.x)
		max.x = set.x;
	if(max.y < set.y)
		max.y = set.y;
	if(max.z < set.z)
		max.z = set.z;
}


void Mesh::loadNode(const aiScene* scene, const aiNode* node)
{
	cout << "Node mesh count: " << node->mNumMeshes << "\n";

	if(node->mNumMeshes > 0)
	{

		for(unsigned i = 0; i < node->mNumMeshes; ++i)
		{
			cout << "Node: " << i << "\n";

			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			unsigned f;
			for(f = 0; f < mesh->mNumFaces; ++f)
			{
			
			}

			cout << "Faces: " << f << "\n";

			for(unsigned n = 0; n < node->mNumChildren; ++n)
			{
				loadNode(scene, node->mChildren[n]);
			}

		}
	}
	else
	{
		const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

		cout << "vertices: " << mesh->mNumVertices << "\n";
		cout << "faces: " << mesh->mNumFaces << "\n";
		
		if(mesh->HasTextureCoords(0) == false)
		{
			cout << "no texture coordinates in mesh.\n";
		}

		AABB aabb;

		// Fill vertices positions
		vertices.reserve(mesh->mNumVertices);
		for(unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			aiVector3D pos = mesh->mVertices[i];
			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
			aabb.grow(vertices[i]);
		}

		// Fill vertices texture coordinates
		uvs.reserve(mesh->mNumVertices);
		for(unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			//REMOVE cout <<"uv: " << i <<"\n";
			if(mesh->HasTextureCoords(0))
			{
				aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
				uvs.push_back(glm::vec2(UVW.x, UVW.y));
			}
			else
			{
				// really TEMP uvs
				//uvs.push_back(glm::vec2(float(i) / float(mesh->mNumVertices), float(i) / float(mesh->mNumVertices)));

				uvs.push_back(glm::vec2((vertices[i].x - aabb.min.x) / aabb.dimensions().x, (vertices[i].y - aabb.min.y) / aabb.dimensions().y));
			}
		}

		// Fill vertices normals
		normals.reserve(mesh->mNumVertices);
		for(unsigned i = 0; i<mesh->mNumVertices; i++)
		{
			if(mesh->HasNormals())
			{
				aiVector3D n = mesh->mNormals[i];
				normals.push_back(glm::vec3(n.x, n.y, n.z));
			}
			else
			{
				// really TEMP normals
				normals.push_back(glm::normalize( glm::vec3(float(i) / float(mesh->mNumVertices), float(i) / float(mesh->mNumVertices), 1.0f) ));
			}
		}


		// Fill face indices
		indices.reserve(3*mesh->mNumFaces);
		for (unsigned i = 0; i<mesh->mNumFaces; i++)
		{
			// Assume the model has only triangles.
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
		}
		
	}
}
//end // ASSIMP


void Mesh::createVBOs()
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
}

void Mesh::render(unsigned set_shader_program_id)
{

	// Get a handle for our buffers
	GLuint vertex_position_id = glGetAttribLocation(set_shader_program_id, "inPosition");
	GLuint vertex_uv_id = glGetAttribLocation(set_shader_program_id, "inUV");
	GLuint vertex_normal_id = glGetAttribLocation(set_shader_program_id, "inNormal");

		// vertices
		glEnableVertexAttribArray(vertex_position_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(
			vertex_position_id,  // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// UVs
		glEnableVertexAttribArray(vertex_uv_id);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glVertexAttribPointer(
			vertex_uv_id,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// normals
		glEnableVertexAttribArray(vertex_normal_id);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(
			vertex_normal_id,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

		glDrawElements(
			GL_TRIANGLES,
			(GLsizei)indices.size(),
			GL_UNSIGNED_SHORT,
			(void*)0
		);

		glDisableVertexAttribArray(vertex_position_id);
		glDisableVertexAttribArray(vertex_uv_id);
		glDisableVertexAttribArray(vertex_normal_id);
}

}//end namespace Rae
