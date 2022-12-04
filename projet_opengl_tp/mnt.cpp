#include "mnt.h"


MNT::MNT(const char* mntPath) : h(0), w(0), m_scale(1), coordinates()
{

	src = new CImg<unsigned char>(mntPath);
	w = src->width();
	h = src->height();
	//coordinates->push_back(glm::vec3());

}

MNT::~MNT()
{
}

unsigned int MNT::getAltitude(int x, int y, unsigned int scale)
{
	//std::cout << "get altitude" << std::endl;
	m_scale = scale;
	unsigned char* ptr_px = src->data(x, y);
	unsigned int px = (unsigned int) *ptr_px;
	return px/5;
}

void MNT::setAltitude(unsigned int x, unsigned int y, unsigned int a)
{
	glm::vec3 coord(x, a, y);
	coordinates.push_back(coord);
	//std::cout << "cooridnates size: " << coordinates.size() << std::endl;
}

unsigned int MNT::MNTWidth()
{
	return w;
}

unsigned int MNT::MNTHeight()
{
	return h;
}

void MNT::generateTerrainCoordinates()
{
	unsigned int altitude;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			altitude = getAltitude(x, y, 1);
			setAltitude(x, y, altitude);
		}
	}
}

vector<glm::vec3> MNT::getCoordinates()
{
	return coordinates;
}


vector<glm::vec3> MNT::generateVertexBufferMNT()
{
	vector<glm::vec3> g_vertex_buffer_data; 

	for (int i = 0; i < h - 1; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			g_vertex_buffer_data.push_back(coordinates.at(i * w + j));
			g_vertex_buffer_data.push_back(coordinates.at((i + 1) * w + j));
			g_vertex_buffer_data.push_back(coordinates.at((i + 1) * w + j + 1));

			g_vertex_buffer_data.push_back(coordinates.at(i * w + j));
			g_vertex_buffer_data.push_back(coordinates.at(i * w + j + 1));
			g_vertex_buffer_data.push_back(coordinates.at((i + 1) * w + j + 1));
		}
	}
	return g_vertex_buffer_data;
}


vector<glm::vec2> MNT::generateUVBufferMNT(int vertex_buffer_data_size)
{
	vector<glm::vec2> g_uv_buffer_data;

	int val = 0;
	for (int i = 0; i < vertex_buffer_data_size / 6 ; i++)
	{
		g_uv_buffer_data.push_back(glm::vec2(0.0f, 0.0f));
		g_uv_buffer_data.push_back(glm::vec2(1.0f, 0.0f));
		g_uv_buffer_data.push_back(glm::vec2(1.0f, 1.0f));

		g_uv_buffer_data.push_back(glm::vec2(0.0f, 0.0f));
		g_uv_buffer_data.push_back(glm::vec2(0.0f, 1.0f));
		g_uv_buffer_data.push_back(glm::vec2(1.0f, 1.0f));
	}

	return g_uv_buffer_data;
}