#ifndef _MESH_
#define _MESH_
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "MyMesh.h"

using namespace std;
using namespace MeshLib;
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	/*  ��������  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  ����  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
	void setupMesh();
private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;
	/*  ����  */

};

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	//��Ҫ���¶������ 
	//ͬ������Ҫ�� textures ����������
	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//face �е� vertex id //�պ�һһ��Ӧ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	//����λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//���㷨��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// ������������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
};
void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);// �ڰ�֮ǰ������Ӧ������Ԫ
		//��ȡ�������(diffuse_textureN �е�N)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	//��������

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
};

unsigned int TextureFromFile(const char *path);
class Model
{
public:
	Model() {};
	~Model() {};

	void Draw(Shader shader) {
		//TODO
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	};

	void loadModel(const char *path)
	{
		//���¿�����ô��εĶ�������
		CMyMesh pMesh;
		pMesh.read_m(path);
		meshes.push_back(processMesh(&pMesh));
	};

	void loadTexture(const char *path)
	{
		// 1. diffuse maps
		vector<Texture> diffuseMaps = loadMaterialTextures(path, "texture_diffuse");
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].textures = diffuseMaps;
		
		}
	}
private:

	/*ģ������*/
	vector<Mesh> meshes;
	string directory;

	
	Mesh processMesh(CMyMesh *pMesh)
	{
		vector<Vertex> vertices;
		vector<unsigned int>indices;
		vector<Texture> textures;
		compute_normal(pMesh);

		for (CMyMesh::MeshVertexIterator viter(pMesh); !viter.end(); viter++)
		{
			CMyVertex * pV = *viter;
		    ///����ȥ���Ļ����������������е��鷳�� 
			//��������ȥ����
			Vertex vertex;
			glm::vec3 pos;
			pos.x = pV->point()[0];
			pos.y = pV->point()[1];
			pos.z = pV->point()[2];
			vertex.Position = pos;
			glm::vec3 norm;
			norm.x = pV->normal()[0];
			norm.y = pV->normal()[1];
			norm.z = pV->normal()[2];
			vertex.Normal = norm;

			if (pV->uv()[0])
			{
				vertex.TexCoords = glm::vec2(pV->uv()[0], pV->uv()[1]);
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}			
			vertices.push_back(vertex);
		}

		//��������
		for (CMyMesh::MeshFaceIterator fiter(pMesh); !fiter.end(); fiter++)
		{
			CMyFace *pf = *fiter;
			for (CMyMesh::FaceVertexIterator fviter(pf); !fviter.end(); fviter++)
			{
				CMyVertex* pv = *fviter;
				//�洢�Ĳ���
				indices.push_back(pv->id()-1);
			}
		}

		//��Ҫ���ⲿ���ز��� ������ʱ����Ҫ��
		return Mesh(vertices, indices, textures);
	};
	//������ͼ
	vector<Texture> loadMaterialTextures(const char *path,string typeName)
	{
		vector<Texture> textures;
		// if texture hasn't been loaded already, load it
		Texture texture;
		texture.id = TextureFromFile(path);
		texture.type = typeName;
		//texture.path = str.C_Str();
		textures.push_back(texture);
		//textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		return textures;
	};
	//����Normal //���� uv vertex
	void compute_normal(CMyMesh * pMesh)
	{
		for (CMyMesh::MeshVertexIterator viter(pMesh); !viter.end(); ++viter)
		{
			CMyVertex * v = *viter;
			CPoint n(0, 0, 0);
			for (CMyMesh::VertexFaceIterator vfiter(v); !vfiter.end(); ++vfiter)
			{
				CMyFace * pF = *vfiter;

				CPoint p[3];
				CHalfEdge * he = pF->halfedge();
				for (int k = 0; k < 3; k++)
				{
					p[k] = he->target()->point();
					he = he->he_next();
				}

				CPoint fn = (p[1] - p[0]) ^ (p[2] - p[0]);
				pF->normal() = fn / fn.norm();
				n += fn;
			}

			n = n / n.norm();
			v->normal() = n;
		}
	};
};


unsigned int TextureFromFile(const char *path)
{
	string filename = string(path);
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
#endif // !_MEHS_