#ifndef MNT_H
#define MNT_H



#include <string>
#include <glm/glm.hpp>
#define cimg_use_jpeg
#include "CImg/CImg.h"
#include <vector>
#include <iostream>

using namespace cimg_library;
using namespace std;

class MNT
{
public:
	MNT(const char* mntPath);
	~MNT();
	unsigned int getAltitude(int x, int y, unsigned int scale);
	void setAltitude(unsigned int x, unsigned int y, unsigned int a);
	unsigned int MNTWidth();
	unsigned int MNTHeight();
	void generateTerrainCoordinates();
	vector<glm::vec3> getCoordinates();
	vector<glm::vec3> generateVertexBufferMNT();
	vector<glm::vec2> generateUVBufferMNT(int vertex_buffer_data_size);

	CImg<unsigned char>* src;

private:
	vector<glm::vec3> coordinates;
	unsigned int w; //width of the MNT image
	unsigned int h; //height of the MNT image;
	unsigned int m_scale; //scale for the DEM
};

#endif // MNT_H