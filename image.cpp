#include "image.h"
#include <exception>
#include <sstream>

//-----------------------------------------
Image::Image(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	m_data.reserve(height);
	for(uint y = 0; y < height; y++)
	{
		vector<Pixel> line;
		line.reserve(width);
		for(uint x = 0; x < width; x++)
			line.push_back(Pixel());
		m_data.push_back(line);
	}
}

//-----------------------------------------
Image::Image(const Image &other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_data = other.m_data;
}

//-----------------------------------------
Pixel& Image::pixel(uint x, uint y)
{
	if(x < 0 || x >= m_width || y < 0 || y >= m_height)
		throw std::out_of_range("coordenadas do pixel fora do intervalo da imagem");

	return m_data[y][x];
}

//-----------------------------------------
const Pixel& Image::pixel(uint x, uint y) const
{
	if(x < 0 || x >= m_width || y < 0 || y >= m_height)
		throw std::out_of_range("coordenadas do pixel fora do intervalo da imagem");

	return m_data[y][x];
}

//-----------------------------------------
uint Image::width() const
{
	return m_width;
}

//-----------------------------------------
uint Image::height() const
{
	return m_height;
}

// ------------------------------
// Remova se não usar OpenCV
// ------------------------------
cv::Mat Image::toMat() const
{
	cv::Mat ret;

	ret.create(cv::Size(m_width, m_height), CV_8UC3);
	for(uint y = 0; y < m_height; y++)
	{
		for(uint x = 0; x < m_width; x++)
		{
			Pixel p = m_data[y][x];
			ret.at<cv::Vec3b>(y, x) = cv::Vec3b(p.blue, p.green, p.red);
		}
	}

	return ret;
}
// ------------------------------