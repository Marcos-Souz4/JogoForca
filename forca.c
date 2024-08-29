//importação de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//declaração de variáveis globais
int chutesDados = 0;
char palavraSecreta[20];
char chutes[26];

//Main
int main() {

  //abrindo o jogo e lendo a palavra secreta
  escolhePalavra();
  abertura();

  //loop para fazer a forca
  do {

    desenhaForca();
    chuta();

  } while(!ganhou() && !enforcou()); //enquanto não ganhar nem enforcar

  if (ganhou()) {

    printf("\nParabens, voce ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
  } else {

    printf("\n***OHHHH NAO, voce foi enforcado***\n");
    printf("A palavra era %s\n\n", palavraSecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }

  adicionaPalavra();

  return 0;
}

//Funções
void abertura() {

  printf("\n");
  printf("                  OOOOOOOOOO                 \n");
  printf("              OOOOOOOOOOOOOOOOO              \n");
  printf("            OOOOOO  OOOOOOO  OOOOOO          \n");
  printf("          OOOOOO      OOO      OOOOOO        \n"); 
  printf("        OOOOOOOO  #   OOO  #   OOOOOOOO      \n"); 
  printf("      OOOOOOOOOO    OOOOOO    OOOOOOOO000    \n");
  printf("     0OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0OO0    BEM VINDO    \n");
  printf("     0OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0       AO        \n");
  printf("      OOOO  OOOOOOOOOOOOOOOOOOOOOOO  OOOO    JOGO DE FORCA \n");
  printf("      OOOO  OOOOOOOOOOOOOOOOOOOOO   0OOOO                  \n");
  printf("        OOOO   OOOOOOOOOOOOOOOOOO  OOOO    QUERIDO USUARIO ;)\n");
  printf("          OOOOO   OOOOOOOOOOOOO   OOOO      \n");
  printf("            OOOOOO   OOOOOOO   OOOOOO       \n");
  printf("              OOOOOO       OOOOOO           \n");
  printf("                  OOOOOOOOOO                \n");
  printf("                                            \n");
  printf("\n");    
}

int letraExiste(char letra) {

  for (unsigned i=0; i<strlen(palavraSecreta);i++) {

    if (palavraSecreta[i]==letra) {

      return 1;
    }
  }

  return 0;
}

void adicionaPalavra() {

  //declaração de variáveis
  int quantidade;
  char quer, novaPalavra[TAMANHO_PALAVRA];

  printf("\n\nQuer adicionar uma nova palavra?(S/N): ");
  scanf(" %c", &quer);

  if (quer=='S') {

    printf("Qual a nova palavra?\n");
    scanf("%s", novaPalavra);

    //começando a manipular arquivos
    FILE *f;

    f = fopen("C:\\Users\\Tommy Marques\\Desktop\\Marcos\\alura\\C\\forca.c\\palavras.txt", "r+");

    if (f==NULL) {

      perror("\n\nDesculpe, bando de dados indisponivel!\n");
      exit(1); //bom usar para evitar erros graves
    }

    fscanf(f, "%d", &quantidade);
    quantidade++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", quantidade);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novaPalavra);

    fclose(f);
  }
}

void escolhePalavra() {

  //declaração de variáveis
  int i, quantidadePalavras, randomico;
  FILE* f; //tipo de variável que guarda um arquivo

  //abrindo o arquivo e atribuindo a uma variável por ponteiro
  f = fopen("C:\\Users\\Tommy Marques\\Desktop\\Marcos\\alura\\C\\forca.c\\palavras.txt", "r");

  if (f==0) {

    perror("Desculpe, banco de dados nao disponivel\n\n");
    exit(1);
  }

  //lendo o arquivo
  fscanf(f, "%d", &quantidadePalavras);

  //gerando um número randomico
  srand(time(0));
  randomico = rand() % quantidadePalavras;

  //iterando o arquivo até uma palavra aleatória
  for (i = 0; i <= randomico; i++) {

    fscanf(f, "%s", palavraSecreta);
  }

  //fechando o arquivo
  fclose(f);
}

void chuta() {

  char chute;
  printf("Qual a letra? \n");
  scanf(" %c", &chute);

  if (letraExiste(chute)) {

    printf("Voce acertou: a palavra tem a letra %c\n\n", chute);
  } else {

    printf("\nVoce errou: a palavra nao tem a letra %c\n\n", chute);
  }

  chutes[chutesDados] = chute;
  chutesDados++;
}

int jaChutou(char letra) {

  //declaração de variáveis
  int achou = 0, i;

  for (i = 0; i < chutesDados; i++) {

    if (chutes[i]==letra) {

      achou = 1;
      break;
    }
  }

  return achou;
}

void desenhaForca() {

  int erros = chutesErrados();

  printf("  _______        \n");
  printf(" |/      |       \n");
  printf(" |      %c%c%c   \n", (erros>=1? '(':' '), (erros>=1? '_':' '), erros>=1? ')':' ');
  printf(" |      %c%c%c   \n", (erros>=3? '\\':' '), (erros>=2? '|':' '), (erros>=3? '/':' '));
  printf(" |       %c      \n", (erros>=2? '|':' '));
  printf(" |      %c %c    \n", (erros>=4? '/':' '), (erros>4? '\\':' '));
  printf(" |               \n");
  printf("_|___            \n");
  printf("\n\n");

  int achou;
  printf("Voce ja deu %d chutes \n", chutesDados);

  for (unsigned i = 0; i < strlen(palavraSecreta); i++) {

    achou = jaChutou(palavraSecreta[i]);

    if (achou) {

      printf("%c ", palavraSecreta[i]);
    } else {

      printf("_ ");
    }
  }
  printf("\n");
}

int chutesErrados() {

  //declaração de variáveis
  int i, erros=0;

  for (i = 0; i<chutesDados; i++) {

    if (!letraExiste(chutes[i])) {

      erros++;
    }
  }

  return erros;
}

int enforcou() {

  return chutesErrados() >= 5;
}

int ganhou() {

  for (unsigned i = 0; i<strlen(palavraSecreta); i++) {

    if (!jaChutou(palavraSecreta[i])) {

      return 0;
    }
  }

  return 1;
}