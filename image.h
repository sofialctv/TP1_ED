#ifndef IMAGE_H
#define IMAGE_H

/* Definindo estrutura Imagem */
typedef struct Imagem Image;

/** criaImagem - Cria uma nova imagem 
 * 
 * @parametro linha    Nº de linhas (altura) da imagem
 * @parametro coluna   Nº de colunas (largura) da imagem
 * @parametro tipo      Tipo do PPM, sendo "P2" em escala de cinza e "P3" em colorido
 * 
 * */
Image *criaImagem(int linha, int coluna, char tipo[]);

/** ler_ppm - Carrega uma imagem de um arquivo PPM
 * 
 * @parametro nome_arquivo   Corresponde ao nome do arquivo PPM a ser carregado
 * @return                  Ponteiro para imagem carregada
 * 
 * */
Image *ler_ppm(const char *nome_arquivo);

/**
* escreve_ppm - Grava uma imagem no arquivo PPM 
* 
* @parametro figura     É a imagem a ser escrita no arquivo
* @param filename       Nome do arquivo PPM a ser escrito
*/
void escreve_ppm(Image *imagem, const char *nome_arquivo);

/**
* rgb_para_cinza - Converte uma imagem RGB para escala de cinza
* 
* @parametro image_rgb A imagem RGB de entrada a ser convertida
* @param image_cinza       A imagem de saída em tons de cinza onde o resultado é armazenado
*/
void rgb_para_cinza(Image *imagem_rgb, Image *imagem_cinza); /* FUNÇÃO COM ERROS :( */

/**
* liberaImagem - Libera a memória alocada da estrutura Imagem e da matriz da imagem
*@param Figura   Ponteiro para a estrutura da imagem que contém a matriz a ser liberada
*/
void liberarImagem(Image *Figura);
#endif