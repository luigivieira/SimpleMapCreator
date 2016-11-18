#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "image.h"

// ------------------------------
// Remova se não usar OpenCV
// ------------------------------
#include <opencv2\opencv.hpp>
using namespace cv;
// ------------------------------

/**
 * Função de geração de um número inteiro aleatório entre um intervalo dado.
 * @param min Inteiro com o mímimo número esperado.
 * @param max Inteiro com o máximo número esperado.
 * @return Inteiro com o valor sorteado.
 */
int random(int min, int max)
{
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;
	do
	{
		x = rand();
	} while(x >= RAND_MAX - remainder);
	return min + x % n;
}

/**
 * Gera um mapa de regiões aleatórias.
 * @param colors Vetor de Pixels com as cores possívels
 * para as regiões.
 * @param width Inteiro positivo com o largura da imagem gerada.
 * @param width Inteiro positivo com o altura da imagem gerada.
 * @param iterations Inteiro positivo com o número de interações para
 * o agrupamento de pixels sob a imagem inicialmente aleatória. O default
 * é 100 mil. Se esse valor for 0, nenhuma permutação é realizada e a imagem
 * do mapa resultante contém apenas ruído.
 * @param window Inteiro positivo com o tamanho da janela de comparação para
 * o agrupamento. Essa janela tem que ser um número cuja raíz quadrada resulta
 * em um inteiro ímpar (9, 25, 49, 81, etc) de valor mínimo 9.
 * @return Objeto Image com a imagem gerada.
 */
Image genMap(vector<Pixel> colors, uint width, uint height, uint iterations = 100000, uint window = 9)
{
	// Checa os parâmetros de entrada
	double windowRoot = std::sqrt(window);
	if(windowRoot < 3 || (windowRoot - int(windowRoot)) != 0 || int(windowRoot) % 2 == 0)
		throw std::invalid_argument("tamanho de janela invalido");

	// Usa o horário atual como semente para o gerador de números aleatórios
	std::srand((uint)std::time(0));

	// ++++++++++++++++++++++++++++++++++++++
	// 1 - Cria o mapa totalmente em preto
	// ++++++++++++++++++++++++++++++++++++++
	Image map(width, height);

	// ++++++++++++++++++++++++++++++++++++++
	// 2 - Sorteia aleatoriamente os pixels nas cores recebidas
	// ++++++++++++++++++++++++++++++++++++++
	for(uint x = 0; x < width; x++)
	{
		for(uint y = 0; y < height; y++)
		{
			uint c = random(0, 1);
			map.pixel(x, y) = colors[c];
		}
	}

	// ++++++++++++++++++++++++++++++++++++++
	// 3 - Agrupa os pixels aleatoriamente, para formar as regiões	
	// ++++++++++++++++++++++++++++++++++++++
	uint offset = int(std::ceil(windowRoot) / 2);
	for(uint i = 0; i < iterations; i++)
	{
		// Sorteia um pixel qualquer na imagem
		int xCenter = random(0, width-1);
		int yCenter = random(0, height-1);
		Pixel color = map.pixel(xCenter, yCenter);

		// Conta quantos são os pixels vizinhos que são iguais
		// ao pixel "central" sorteado
		int count = 0;
		for(uint x = xCenter - offset; x <= xCenter + offset; x++)
		{
			for(uint y = yCenter - offset; y <= yCenter + offset; y++)
			{
				// Desconsidera pixels fora da área da imagem
				if(x < 0 || x >= width || y < 0 || y >= height)
					continue;

				// Incrementa se for a mesma cor
				if(map.pixel(x, y) == color)
					count++;
			}
		}

		// Se mais da metade da janela é da mesma cor do pixel central,
		// transforma todos os vizinhos na cor do pixel central
		if(count > int(window / 2))
		{
			for(uint x = xCenter - offset; x <= xCenter + offset; x++)
			{
				for(uint y = yCenter - offset; y <= yCenter + offset; y++)
				{
					// Desconsidera pixels fora da área da imagem
					if(x < 0 || x >= width || y < 0 || y >= height)
						continue;

					// Define a cor
					map.pixel(x, y) = color;
				}
			}
		}
	}

	// ++++++++++++++++++++++++++++++++++++++
	// Pronto! Só devolve a imagem gerada. :)
	// ++++++++++++++++++++++++++++++++++++++
	return map;
}

// ------------------------------
// Remova se não usar OpenCV
// ------------------------------
void showImage(char *title, Mat image)
{
	namedWindow(title, cv::WINDOW_AUTOSIZE);
	imshow(title, image);
}
// ------------------------------

/**
 * Converte a imagem (bidimensional) para um longo vetor de
 * valores (unidimensional).
 * @return Vetor de com todos os valores dos pixels (na ordem
 * R, G, B) agrupados linha após linha.
 */
vector<uchar> imageToVector(const Image &image)
{
	vector<uchar> ret;
	for(uint y = 0; y < image.height(); y++)
	{
		for(uint x = 0; x < image.width(); x++)
		{
			Pixel p = image.pixel(x, y);
			ret.push_back(p.red);
			ret.push_back(p.green);
			ret.push_back(p.blue);
		}
	}
	return ret;
}

/**
 * Converte um longo vetor de valores (unidimensional) para uma
 * imagem (bidimensional).
 * @param data Vetor com todos os valores dos pixels (na ordem
 * R, G, B) agrupados linha após linha.
 * @param width Inteiro positivo com a largura da imagem.
 * @param height Inteiro positivo com a altura da imagem.
 */
Image vectorToImage(vector<uchar> data, uint width, uint height)
{
	if(data.size() != (width * height * 3))
		throw std::invalid_argument("os dados e as dimensoes recebidos não são condizentes com uma imagem em 3 canais");

	Image ret(width, height);
	for(uint i = 0; i < data.size(); i += 3)
	{
		int x = (i / 3) % width;
		int y = (i / 3) / width;
		ret.pixel(x, y) = Pixel(data[i], data[i + 1], data[i + 2]);
	}

	return ret;
}

/**
 * Função principal.
 */
int main()
{
	Pixel amarelo(255, 255, 0);
	Pixel verde(0, 255, 0);

	Image t1 = genMap({ amarelo, verde }, 400, 300, 0);
	Image t2 = genMap({ amarelo, verde }, 400, 300, 100000);
	Image t3 = genMap({ amarelo, verde }, 400, 300, 100000, 25);
	Image t4 = genMap({ amarelo, verde }, 400, 300, 500000, 25);

	cout << "Teste 1: " << endl;
	cout << t1 << endl << endl;

	cout << "Teste 2: " << endl;
	cout << t2 << endl << endl;

	cout << "Teste 3: " << endl;
	cout << t3 << endl << endl;

	cout << "Teste 4: " << endl;
	cout << t4 << endl << endl;

	// ------------------------------
	// Remova se não usar OpenCV
	// ------------------------------
	showImage("Teste 1 - Aleatoria", t1.toMat());
	showImage("Teste 2 - Janela: 9 e Iteracoes: 100 mil", t2.toMat());
	showImage("Teste 3 - Janela: 25 e Iteracoes: 100 mil", t3.toMat());
	showImage("Teste 4 - Janela: 25 e Iteracoes: 500 mil", t4.toMat());
	waitKey(0);
	// ------------------------------

	cout << endl << "Teste de Conversao" << endl;
	Image t = genMap({ amarelo, verde }, 4, 10, 0);

	cout << "Imagem bidimensional original: " << endl;
	cout << t << endl << endl; 

	cout << "Convertida para vetor unidimensional: " << endl;
	vector<uchar> v = imageToVector(t);
	for(uint i = 0; i < v.size(); i++)
		cout << int(v[i]) << " ";
	cout << endl << endl;

	cout << "Convetida de volta para imagem bidimensional: " << endl;
	cout << vectorToImage(v, 4, 10) << endl;

    return 0;
}