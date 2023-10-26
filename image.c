#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* Viabiliza uso de 'strcmp()', para comparação de strings */

/* Definindo a estrutura Imagem */
struct Imagem {
  char tipo[3];                  /* Tipo da imagem (exemplo, "P2" ou "P3") */
  int largura;                  /* Largura da imagem em matriz_pixel */
  int altura;                   /* Altura da imagem em matriz_pixel */
  int max_pixel;                /* Valor máximo do pixel */
  unsigned char **matriz_pixel; /* Matriz de matriz_pixel do corpo da imagem */
};

/* Criando uma nova imagem */
Image *criaImagem(int largura, int altura, char tipo[]){

  Image *Figura = (Image*)malloc(sizeof(Image));
    if (Figura == NULL) {
        printf("ERROR: Alocação de memória falhou.\n");
        exit(EXIT_FAILURE);
    }

    Figura->largura = largura;
    Figura->altura = altura;
    Figura->max_pixel = 255;

    strncpy(Figura->tipo, tipo, sizeof(Figura->tipo));

    if (strcmp(tipo, "P2") == 0) 
    {
    /* Aloca memória para matriz de matriz_pixel do tipo P2 */
        Figura->matriz_pixel = (unsigned char**)malloc(largura * sizeof(unsigned char*));

        for (int i = 0; i < largura; i++) 
        {
            Figura->matriz_pixel[i] = (unsigned char*)malloc(altura * sizeof(unsigned char));
        }
    } 
     /* Aloca memória para matriz de matriz_pixel do tipo P3 */
    else if (strcmp(tipo, "P3") == 0 ) {
        Figura->matriz_pixel = (unsigned char**)malloc(largura * sizeof(unsigned char*));

        for (int i = 0; i < largura; i++) {
            Figura->matriz_pixel[i] = (unsigned char*)malloc(largura * 3 * sizeof(unsigned char));
        }
    } 
    else {
        printf("ERROR: Tipo de imagem não suportado.\n");
        exit(EXIT_FAILURE);
    }
    return Figura;
}

/* Carregando uma imagem de um arquivo PPM e retornando ponteiro para uma imagem carregada */
Image *ler_ppm(const char *filename){

  FILE *arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
      printf("ERROR: Não foi possível abrir o arquivo em %s.\n", filename);
      exit(EXIT_FAILURE);
  }

  char tipo[3];
  int largura, altura, max, num;

  fscanf(arquivo, "%s", tipo);

  if (strcmp(tipo, "P3") == 0){

    fscanf(arquivo, "%d %d", &largura,&altura);
    fscanf(arquivo, "%d", &max);

    Image *Figura = criaImagem(largura, altura, tipo);
    for (int i = 0; i < Figura->largura; i++) 
    {
        for (int j = 0; j < Figura->altura * 3; j++) 
        {
            fscanf(arquivo, "%d", &num);
            Figura->matriz_pixel[i][j] = (unsigned char) num;
        }
    }
    return Figura;
  }

  else
  {
    printf("ERROR: O arquivo %s não é do tipo P3.\n", filename);
    exit(EXIT_FAILURE);
  }
  fclose(arquivo);
}

/* Gravando uma imagem no arquivo PPM */
void escreve_ppm(Image *figura, const char *filename) {

  FILE *arquivo = fopen(filename, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n\n");
    return;
  }

  fprintf(arquivo, "%s\n", figura->tipo);
  fprintf(arquivo, "%d %d\n", figura->largura, figura->altura);
  fprintf(arquivo, "%d\n", figura->max_pixel);


  if (strcmp(figura->tipo,"P2") == 0)
  {
    for (int i = 0; i < figura->largura; i++) 
    {
      for (int j = 0; j < figura->altura; j++) 
      {
        fprintf(arquivo, "%hhu ", figura->matriz_pixel[i][j]);
      }
      fprintf(arquivo, "\n");
    }
  }
  else if(strcmp(figura->tipo,"P3" ) == 0) 
  {
    for (int i = 0; i < figura->largura; i++) 
    {
      for (int j = 0; j < figura->altura * 3; j+=3) 
      {
        fprintf(arquivo, "%hhu ", figura->matriz_pixel[i][j]);
        fprintf(arquivo, "%hhu ", figura->matriz_pixel[i][j+1]);
        fprintf(arquivo, "%hhu ", figura->matriz_pixel[i][j+2]);
      }
      fprintf(arquivo, "\n");
    }
  }
  fclose(arquivo);
}

/* Convertendo uma imagem RGB para escala de cinza 
*
* FUNÇÃO NÃO ESTÁ FUNCIONANDO CORRETAMENTE. Não encontramos o erro.
*
*/
void rgb_para_cinza(Image *image_rgb, Image *image_cinza) 
{
  image_cinza = criaImagem(image_rgb->largura,image_rgb->altura,"P2");
  image_cinza->max_pixel = 255;
  if(strcmp(image_rgb->tipo,"P3")==0)
  {
    for (int i = 0; i < image_rgb->largura; i++) 
    {
      for (int j = 0; i < image_rgb->altura; i++) 
      {
          image_cinza->matriz_pixel[i][j * 3] =
            (0.229 * image_rgb->matriz_pixel[i][j * 3]) +        //RED
            (0.587 * image_rgb->matriz_pixel[i][j * 3 + 1])+   //GREEN
            (0.114 * image_rgb->matriz_pixel[i][j * 3 + 2]);   //BLUE
      }
    }
  }
  else
    printf("Arquivo inserido já está na escala de cinza.\n");
}

void liberarImagem(Image *Figura){
    for (int i = 0; i < Figura->largura; ++i) {
        free(Figura->matriz_pixel[i]);
    }
    free(Figura->matriz_pixel);
    free(Figura);
}