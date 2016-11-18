#ifndef PIXEL_H
#define PIXEL_H

#include <string>

using namespace std;

/** Defini��o auxiliar para o tipo de dados dos componentes. */
typedef unsigned char uchar;

/**
 * Classe simples e r�pida para representar os valores de um pixel
 * com tr�s bandas de cor (RGB).
 */
class Pixel
{
public:

	/**
	 * Construtor padr�o. Cria um pixel preto (todos componentes com 0).
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
	 * Construtor de c�pia.
	 * @param other Refer�ncia de outra inst�ncia de Pixel de onde
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
 * Sobrecarrega o operador de compara��o (para permitir a == b com
 * inst�ncias da classe Pixel).
 * @param one Refer�ncia de primeira inst�ncia de Pixel a ser comparada.
 * @param two Refer�ncia de segunda inst�ncia de Pixel a ser comparada.
 * @return Booleano indicando se as duas inst�ncias s�o iguais ou n�o.
 */
inline bool operator==(const Pixel &one, const Pixel& two)
{
	return one.red == two.red && one.green == two.green && one.blue == two.blue;
}

/**
 * Sobrecarrega o operador de "impress�o" via stream (para permitir std::cout << a
 * com inst�ncias da classe Pixel).
 * @param os Refer�ncia do std::ostream que vai receber os dados impressos.
 * @param pixel Refer�ncia do Pixel que vai ser impresso.
 * @return O pr�prio ostream de entrada.
 */
inline std::ostream &operator<<(std::ostream &os, const Pixel &pixel)
{
	return os << "(" << int(pixel.red) << "," << int(pixel.green) << "," << int(pixel.blue) << ")";
}

#endif // PIXEL_H