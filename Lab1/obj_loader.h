#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct OBJIndex
{
    unsigned int vertexIndex;						// Integer to store index of the vertex.
    unsigned int uvIndex;							// Integer to store index of the uv.
    unsigned int normalIndex;						// Integer to store index of the normal.
    
    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }		// Set vertexIndex to r.vertexIndex when called. 
};

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;				// Vector template of vector3 to store the positions.
    std::vector<glm::vec2> texCoords;				// Vector template of vector2 to store the texture coordinates.
    std::vector<glm::vec3> normals;					// Vector template of vector3 to store the normals.
    std::vector<unsigned int> indices;				// Vector template of integer to store the indices.
    
    void CalcNormals();								// used to calculate the normals.
};

class OBJModel
{
public:
    std::vector<OBJIndex> OBJIndices;				// Vector template of OBJIndex to store object indices.
    std::vector<glm::vec3> vertices;				// Vector template of vector3 to store vertices. 
    std::vector<glm::vec2> uvs;						// Vector template of vector2 to store uvs.
    std::vector<glm::vec3> normals;					// Vector template of vector3 to store normals.
    bool hasUVs;									// Boolean to check if object has uvs. 
    bool hasNormals;								// Boolean to check if object has normals.
    
    OBJModel(const std::string& fileName);			// Constructor.
    
    IndexedModel ToIndexedModel();					// Create an indexed model.
private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);	// Find the last vertex index.
    void CreateOBJFace(const std::string& line);	// Create a face of an object.
    
    glm::vec2 ParseOBJVec2(const std::string& line);	//
    glm::vec3 ParseOBJVec3(const std::string& line);	//
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);	//
};

#endif												// OBJ_LOADER_H_INCLUDED
