#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include <vector>

// ------------------------------
// Remova se não usar OpenCV
// ------------------------------
#include <opencv2\core.hpp>
// ------------------------------

/** Definição auxiliar de um tipo para os índices e dimensões da matriz de dados. */
typedef unsigned int uint;

/**
 * Classe simples e rápida para representar uma imagem colorida (RGB).
 */
class Image
{
	public:

		/**
		 * Construtor padrão. Cria uma imagem com a largura e altura
		 * dadas, totalmente preenchida com preto (0 nas três bandas).
		 * @param width Inteiro positivo com a largura da imagem.
		 * @param height Inteiro positivo com a altura da imagem.
		 */
		Image(uint width, uint height);
	
		/**
		 * Construtor de cópia.
		 * @param other Referência de outra instância de Image de onde
		 * copiar os dados.
		 */
		Image(const Image &other);

		/**
		 * Acesso de leitura e gravação ao valor de um pixel na imagem.
		 * Observação: Este método lança a exceção std::out_of_range se
		 * as coordenadas recebidas estiverem fora dos limites da imagem.
		 * @param x Coordenada x do pixel, no intervalo [0, width-1].
		 * @param y Coordenada y do pixel, no intervalo [0, height-1].
		 * @return Referência ao pixel nas coordenadas dadas.
		 */
		Pixel& pixel(uint x, uint y);

		/**
		 * Acesso somente leitura ao valor de um pixel na imagem.
		 * Observação: Este método lança a exceção std::out_of_range se
		 * as coordenadas recebidas estiverem fora dos limites da imagem.
		 * @param x Coordenada x do pixel, no intervalo [0, width-1].
		 * @param y Coordenada y do pixel, no intervalo [0, height-1].
		 * @return Referência constante ao pixel nas coordenadas dadas.
		 */
		const Pixel& pixel(uint x, uint y) const;

		/**
		 * Obtém a largura da imagem.
		 * @return Inteiro positivo com a largura da imagem.
		 */
		uint width() const;

		/**
		 * Obtém a altura da imagem.
		 * @return Inteiro positivo com a altura da imagem.
		 */
		uint height() const;

		// ------------------------------
		// Remova se não usar OpenCV
		// ------------------------------
		/**
		 * Converte a imagem para o formato do OpenCV.
		 * @return Mat do OpenCV com os dados da imagem.
		 */
		cv::Mat toMat() const;
		// ------------------------------

	private:

		/** Definição de um "tipo dados" para uma matriz de inteiros em 3 bandas. */
		typedef vector<vector<Pixel>> DataMatrix;

		/** Armazena os dados da imagem. */
		DataMatrix m_data;

		/** Largura da imagem. */
		uint m_width;

		/** Altura da imagem. */
		uint m_height;
};

/**
 * Sobrecarrega o operador de "impressão" via stream (para permitir std::cout << a
 * com instâncias da classe Image).
 * @param os Referência do std::ostream que vai receber os dados impressos.
 * @param pixel Referência do Pixel que vai ser impresso.
 * @return O próprio ostream de entrada.
 */
inline std::ostream &operator<<(std::ostream &os, const Image &image)
{
	uint xMax = std::min(int(image.width()), 10); // Máximo de 10 colunas
	uint yMax = std::min(int(image.height()), 10); // Máximo de 10 linhas

	os << "Largura: " << image.width() << " Altura: " << image.height() << endl;
	os << "Pixels: " << endl;
	for(uint y = 0; y < yMax; y++)
	{
		os << "[";
		for(uint x = 0; x < xMax; x++)
		{
			os << image.pixel(x, y);
			if(x < image.width() - 1)
				os << ",";
		}
		if(xMax != image.width())
			os << " mais " << image.width() - xMax << " colunas...";
		os << "]" << endl;
	}
	if(yMax != image.height())
		os << "mais " << image.height() - yMax << " linhas..." << endl;
	return os;
}

#endif // IMAGE_H