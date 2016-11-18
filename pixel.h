#ifndef PIXEL_H
#define PIXEL_H

#include <string>

using namespace std;

/** Definição auxiliar para o tipo de dados dos componentes. */
typedef unsigned char uchar;

/**
 * Classe simples e rápida para representar os valores de um pixel
 * com três bandas de cor (RGB).
 */
class Pixel
{
public:

	/**
	 * Construtor padrão. Cria um pixel preto (todos componentes com 0).
	 */
	Pixel();

	/**
	 * Construtor auxiliar.
	 * @param red Valor do componente vermelho do pixel, no
	 * intervalo [0, 255].
	 * @param green Valor do componente verde do pixel, no
	 * intervalo [0, 255].
	 * @param blue Valor do componente azul do pixel, no
	 * intervalo [0, 255].
	 */
	Pixel(uchar red, uchar green, uchar blue);

	/**
	 * Construtor de cópia.
	 * @param other Referência de outra instância de Pixel de onde
	 * copiar os dados.
	 */
	Pixel(const Pixel &other);

	/** Valor do componente vermelho do pixel no intervalo [0, 255]. */
	uchar red;

	/** Valor do componente verde do pixel no intervalo [0, 255]. */
	uchar green;

	/** Valor do componente azul do pixel no intervalo [0, 255]. */
	uchar blue;
};


/**
 * Sobrecarrega o operador de comparação (para permitir a == b com
 * instâncias da classe Pixel).
 * @param one Referência de primeira instância de Pixel a ser comparada.
 * @param two Referência de segunda instância de Pixel a ser comparada.
 * @return Booleano indicando se as duas instâncias são iguais ou não.
 */
inline bool operator==(const Pixel &one, const Pixel& two)
{
	return one.red == two.red && one.green == two.green && one.blue == two.blue;
}

/**
 * Sobrecarrega o operador de "impressão" via stream (para permitir std::cout << a
 * com instâncias da classe Pixel).
 * @param os Referência do std::ostream que vai receber os dados impressos.
 * @param pixel Referência do Pixel que vai ser impresso.
 * @return O próprio ostream de entrada.
 */
inline std::ostream &operator<<(std::ostream &os, const Pixel &pixel)
{
	return os << "(" << int(pixel.red) << "," << int(pixel.green) << "," << int(pixel.blue) << ")";
}

#endif // PIXEL_H