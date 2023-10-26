#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/********************/

int main() {

  int operacao;
  char caminho_padrao[20]; /* Armazenando o nome do arquivo */
  int opcao;
  Image *Figura = (Image *)malloc(sizeof(Image*));
  Image *FiguraCinza = (Image *)malloc(sizeof(Image*));


  while (operacao != 4) {

    printf("\n# Menu de Operações #\nEscolha uma das opções: \n");
    printf("(1) Carregar imagem.\n");
    printf("(2) Converter para níveis de cinza.\n");
    printf("(3) Gravar imagem.\n");
    printf("(4) Encerrar programa.\n");

    scanf("\n%d", &operacao);

    switch (operacao) {
        
    case 1:
      printf("\nCARREGAR IMAGEM");

      printf("\nDeseja utilizar o nome padrão 'figura.ppm' para o arquivo?\n");
      printf("(1) SIM\n");
      printf("(2) NÃO\n");
      scanf("%d", &opcao);

      if (opcao == 1) {
        strcpy(caminho_padrao, "figura.ppm");
      } else if (opcao == 2) {
        printf("\nInforme o nome de origem do arquivo: \n");
        scanf("%s", caminho_padrao);
      }

      Figura = ler_ppm(caminho_padrao);

      printf("\n\nImagem carregada com sucesso. Você será redirecionado ao Menu.\n\n");

      operacao = 1;
      break;

    case 2:
      printf("CONVERSÃO PARA NÍVEIS DE CINZA\n");

      if (Figura != NULL) {
        rgb_para_cinza(Figura, FiguraCinza);
        free(Figura);
        printf("Operação concluída com sucesso.\n");
      } else {
        fprintf(stderr, "Erro ao converter imagem. Você será redirecionado ao Menu.\n");
      }

      operacao = 2;
      break;

    case 3:
      printf("\nGRAVANDO IMAGEM");

      printf("\nDeseja utilizar o nome padrão 'figura.ppm' para o arquivo?\n");
      printf("(1) SIM\n");
      printf("(2) NÃO\n");
      scanf("%d", &opcao);

      if (opcao == 1) {
        strcpy(caminho_padrao, "figura.ppm");
      } else if (opcao == 2) {
        printf("\nInforme o nome de origem do arquivo: \n");
        scanf("%s", caminho_padrao);
      }
      if(Figura != NULL)
      escreve_ppm(Figura, caminho_padrao);
      else
        escreve_ppm(FiguraCinza, caminho_padrao);
      operacao = 3;
      break;

    case 4:
      printf("Programa encerrado.");
      operacao = 4;
      break;
    }
  }
  return 0;
}