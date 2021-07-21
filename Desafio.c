#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void menu();

struct products {
  char name[20];
  float quant, value;
  int monthValidate, yearValidate;
};

void header(){
  printf("------------------------------------------------------------\n");
  printf("CONTROLE DE ESTOQUE\n");
  printf("------------------------------------------------------------\n\n");
}

void cleanScreen() { 
    system("cls"); 
    header();
}

int searchName(struct products *p) { 
  char searchName[20];
  int i = 0, j;
  int read;

  FILE *f;

  cleanScreen();

  f = fopen("product.txt", "r");

  if(f == NULL) {
    cleanScreen();
    printf(": Nenhum arquivo encontrado.");
    getch();

    cleanScreen();
    menu(p);
  }

  printf("Procurar produto pelo nome: ");
  scanf("%s", &searchName);

  for(;;i++) {
    read = fread(&(*p), sizeof(struct products), 1, f);

    for(j = 0; p -> name[j] != '\0'; j++) {
      if(searchName[j] != p -> name[j]) {
        break;
      }
    }

    if(read == 0) {
      break;
    }

    if(searchName[j] == '\0' && p -> name[j] == '\0') {
      cleanScreen();

      printf("Produto: %s\n", p -> name);

      if(p -> quant < 0) {
        printf("Estoque: 0\n", p -> quant);
      } else {
        printf("Estoque: %.2f\n", p -> quant);
      }

      printf("Preco: R$ %.2f\n", p -> value);

      if(p -> monthValidate > 9) {
        printf("Validade: %d/%d\n", p -> monthValidate, p -> yearValidate);
      } else {
        printf("Validade: 0%d/%d\n", p -> monthValidate, p -> yearValidate);
      }

      printf("\n");

      fclose(f);

      return i;
    }
  }

  fclose(f);

  return -1;
}

void input(struct products *p) { 
  int i;
  int read;

  FILE *f;

  cleanScreen();

  f = fopen("product.txt", "a");

  if(p -> name[0] == NULL) {
    for(;;) {
      for(i = 0; i < 20; i++) {
        p -> name[i] == NULL;

        if(read == 0) {
          break;
        }
      }
    }
  }

  printf("Digite o produto: ");
  scanf("%s", &p -> name);

  printf("Digite a Estoque: ");
  scanf("%f", &p -> quant);

  printf("Digite a preco: ");
  scanf("%f", &p -> value);

  printf("Digite o mes: ");
  scanf("%d", &p -> monthValidate);

  printf("Digite o ano: ");
  scanf("%d", &p -> yearValidate);

  fwrite(&(*p), sizeof(struct products), 1, f);

  printf("\n");
  
  fclose(f);

  cleanScreen();

  menu(p);
}

void list(struct products *p) { 
  int i, j;
  int read;

  FILE *f;

  cleanScreen();

  f = fopen("product.txt", "r");

  if(f == NULL) {
    cleanScreen();
    printf(": Nenhum arquivo encontrado.");
    getch();

    cleanScreen();
    menu(p);
  }

  if(p -> name[0] == NULL) {
    for(i = 0; i < 20; i++) {
      for(j = 0; j < 20; j++) {
        p -> name[j] == NULL;
      }
    }
  }

  for(;;) {
    read = fread(&(*p), sizeof(struct products), 1, f);
    
    if(read == 0) {
      break;
    }

    if(
      p -> name && 
      p -> quant && 
      p -> value && 
      p -> monthValidate && 
      p -> yearValidate
    ) {
      printf("Produto: %s\n", p -> name);

      if(p -> quant < 0) {
        printf("Estoque: 0\n", p -> quant);
      } else {
        printf("Estoque: %.2f\n", p -> quant);
      }

      printf("Preco: R$ %.2f\n", p -> value);

      if(p -> monthValidate > 9) {
        printf("Validade: %d/%d\n", p -> monthValidate, p -> yearValidate);
      } else {
        printf("Validade: 0%d/%d\n", p -> monthValidate, p -> yearValidate);
      }
      printf("------------------------------------------------------------\n");
    } 
  }

  fclose(f);

  printf("\n");
  printf("Pressione ENTER para continuar...");
  
  getch();

  cleanScreen();

  menu(p);
}

void listValueRange(struct products *p) { 
  int read;
  float searchvalueRange1 = 0;
  float searchvalueRange2 = 0;

  FILE *f;

  cleanScreen();

  f = fopen("product.txt", "r");

  if(f == NULL) {
    cleanScreen();
    printf(": Nenhum arquivo encontrado.");
    getch();

    cleanScreen();
    menu(p);
  }

  printf("Preco Minimo: ");
  scanf("%f", &searchvalueRange1);

  printf("Preco Maximo: ");
  scanf("%f", &searchvalueRange2);

  cleanScreen();

  printf("Faixa de preco: R$ %.2f - R$ %.2f\n\n", searchvalueRange1, searchvalueRange2);

  for(;;) {
    read = fread(&(*p), sizeof(struct products), 1, f);

    if(read == 0) {
      break;
    }
    if(p -> value >= searchvalueRange1 && p -> value <= searchvalueRange2) {

      if((p -> name && 
        p -> quant && 
        p -> value && 
        p -> monthValidate && 
        p -> yearValidate)
        ) {
        printf("Produto: %s\n", p -> name);
        printf("Estoque: %.2f\n", p -> quant);
        printf("Preco: R$ %.2f\n", p -> value);

        if(p -> monthValidate > 9) {
          printf("Validade: %d/%d\n", p -> monthValidate, p -> yearValidate);
        } else {
          printf("Validade: 0%d/%d\n", p -> monthValidate, p -> yearValidate);
        }
      }

      printf("\n");

    } 
  }

  fclose(f);

  printf("\n");
  printf("Pressione ENTER para continuar...");

  getch();

  cleanScreen();

  menu(p);
}

void dataSearchName(struct products *p) { 
  int search;

  search = searchName(p);
  if(search == -1) {
    cleanScreen();
    printf("Nenhum dado encontrado.\n");
  }

  printf("\n");
  printf("Pressione ENTER para continuar...");
  
  getch();

  cleanScreen();

  menu(p);
}

void searchValidateDate(struct products *p) { 
  int i, j;
  int read;
  int searchValidateDatemonthValidate;
  int searchValidateDateyearValidate;

  FILE *f;

  cleanScreen();

  f = fopen("product.txt", "r");

  if(f == NULL) {
    cleanScreen();
    printf(": Nenhum arquivo encontrado.");
    getch();

    cleanScreen();
    menu(p);
  }

  printf("Digite o mes: ");
  scanf("%d", &searchValidateDatemonthValidate);

  printf("Digite o ano: ");
  scanf("%d", &searchValidateDateyearValidate);

  cleanScreen();

  for(;;) {
     read = fread(&(*p), sizeof(struct products), 1, f);

     if(read == 0) {
       break;
     }

    if(p -> monthValidate == searchValidateDatemonthValidate && p -> yearValidate == searchValidateDateyearValidate) {
      if((p -> name && 
        p -> quant && 
        p -> value && 
        p -> monthValidate && 
        p -> yearValidate)
        ) {
        printf("Produto: %s\n", p -> name);
        printf("Estoque: %.2f\n", p -> quant);
        printf("Preco: R$ %.2f\n", p -> value);

        if(p -> monthValidate > 9) {
          printf("Validade: %d/%d\n", p -> monthValidate, p -> yearValidate);
        } else {
          printf("Validade: 0%d/%d\n", p -> monthValidate, p -> yearValidate);
        }
      }

      printf("\n");

    } 
  }
  fclose(f);

  printf("\n");
  printf("Pressione ENTER para continuar...");
  
  getch();

  cleanScreen();

  menu(p);
}

void editName(struct products *p) { 

  int search;
  int read;

  FILE *f;

  cleanScreen();

  search = searchName(p);
  if(search == -1) {
    cleanScreen();

    printf("Nenhum dado encontrado.\n");
    printf("\n");
    printf("Pressione ENTER para continuar...");
    
    getch();

    cleanScreen();

    menu(p);
  }

  f = fopen("product.txt", "r+");

  for(;;) {

    fseek(f, search * sizeof(struct products), 0);
    read = fread(&(*p), sizeof(struct products), 1, f);

    if(read == 1) {
      break;
    }
  }

  printf("Alterar produto %s ->: ", p -> name);
  scanf("%s", &p -> name);

  printf("Alterar estoque %.2f ->: ", p -> quant);
  scanf("%f", &p -> quant);

  printf("Alterar preco %.2f ->: ", p -> value);
  scanf("%f", &p -> value);

  printf("Alterar mes %d ->: ", p -> monthValidate);
  scanf("%d", &p -> monthValidate);

  printf("Alterar ano %d ->: ", p -> yearValidate);
  scanf("%d", &p -> yearValidate);

  fseek(f, search * sizeof(struct products), 0);
  fwrite(&(*p), sizeof(struct products), 1, f);
  fclose(f);

  cleanScreen();

  printf("Produto alterado(a) com sucesso.");
  getch();

  cleanScreen();

  menu(p);
}

void editQuant(struct products *p) { 
  int search;
  int read;
  float editquant;

  FILE *f;

  cleanScreen();

  search = searchName(p);
  if(search == -1) {
    cleanScreen();

    printf("Nenhum dado encontrado.\n");
    printf("\n");
    printf("Pressione ENTER para continuar...");
   
    getch();

    cleanScreen();

    menu(p);
  }

  f = fopen("product.txt", "r+");

  for(;;) {
 
    fseek(f, search * sizeof(struct products), 0);
    read = fread(&(*p), sizeof(struct products), 1, f);

    if(read == 1) {
      break;
    }
  }

  printf("Alterar Estoque %.2f ->: ", p -> quant);
  scanf("%f", &editquant);

  if(editquant >= 0) {
    p -> quant = p -> quant + editquant;
  } else if(editquant < 0) {
    p -> quant = p -> quant + editquant;
  }

  rewind(f);

  fseek(f, (search * sizeof(struct products)) + sizeof(p -> name), 0);
  fwrite(&p -> quant, sizeof(p -> quant), 1, f);
  fclose(f);

  cleanScreen();

  printf("Estoque alterado(a) com sucesso.");
  getch();

  cleanScreen();

  menu(p);
}

void editValue(struct products *p) { 
  
  int search;
  int read;

  FILE *f;

  cleanScreen();

  search = searchName(p);

  if(search == -1) {
    cleanScreen();

    printf("Nenhum dado encontrado.\n");
    printf("\n");
    printf("Pressione ENTER para continuar...");
    
    getch();

    cleanScreen();

    menu(p);
  }

  f = fopen("product.txt", "r+");

  for(;;) {
    fseek(f, search * sizeof(struct products), 0);

    read = fread(&(*p), sizeof(struct products), 1, f);

    if(read == 1) {
      break;
    }
  }

  printf("Alterar preco R$ %.2f ->: ", p -> value);
  scanf("%f", &p -> value);

  rewind(f);

  fseek(f, (search * sizeof(struct products)) + sizeof(p -> name) + sizeof(p -> quant), 0);
  fwrite(&p -> value, sizeof(p -> value), 1, f);

  fclose(f);

  cleanScreen();

  printf("Preco alterado(a) com sucesso.");
  getch();

  cleanScreen();

  menu(p);
}

void delete(struct products *p) { 
  
  int search;
  int read;

  FILE *f;

  cleanScreen();

  search = searchName(p);

  if(search == -1) {
    cleanScreen();

    printf("Nenhum dado encontrado.\n");
    printf("\n");
    printf("Pressione ENTER para continuar...");
    
    getch();

    cleanScreen();

    menu(p);
  }

  f = fopen("product.txt", "r+");

  for(;;) {
    fseek(f, search * sizeof(struct products), 0);

    read = fread(&(*p), sizeof(struct products), 1, f);

    if(read == 1) {
      break;
    }
  }

  int auxquant;
  int auxvalue;

  p -> name[0] = '*';
  auxquant = p -> quant;
  auxvalue = p -> value;
  auxquant = NULL;
  auxvalue = NULL;
  
  p -> quant = auxquant;
  p -> value = auxvalue;
  p -> monthValidate = NULL;
  p -> yearValidate = NULL;

  fseek(f, search * sizeof(struct products), 0); 
  fwrite(&(*p), sizeof(struct products), 1, f);
  fclose(f);

  cleanScreen();

  printf("Produto excluido(a) com sucesso.");
  getch();

  cleanScreen();

  menu(p);
}

void quit() { 
  printf("Saindo...");
}

void menu(struct products *p) {

  int op;
  
  printf("1  - Entrada de dados                                                   \n");
  printf("2  - Listar todos os produtos                                           \n");
  printf("3  - Listar produtos por faixa de preco                                 \n");
  printf("4  - Pesquisar um produto por nome completo                             \n");
  printf("5  - Pesquisar por data de validade (MM/AAAA)                           \n");
  printf("6  - Altera produto pesquisado por nome completo                        \n");
  printf("7  - Altera Estoque em estoque (entrada e saida) pesquisado por nome    \n");
  printf("8  - Altera preco de um produto pesquisado por nome completo            \n");
  printf("9  - Excluir produto por nome                                           \n");
  printf("10 - Sair                                                               \n");
  printf("\n");

  printf("Digite uma opcao: ");
  scanf("%d", &op);

  switch(op) {
    case 1: 
      input(p);
    break;
    case 2:
      list(p);
    break;
    case 3:
      listValueRange(p);
    break;
    case 4:
      dataSearchName(p);
    break;
    case 5:
      searchValidateDate(p);
    break;
    case 6: 
      editName(p);
    break;
    case 7: 
      editQuant(p);
    break;
    case 8:
      editValue(p);
    break;
    case 9: 
      delete(p);
    break;
    case 10:
      quit();
    break;
    default:
      cleanScreen();
      printf("Algo deu errado.\n");
      printf("Pressione ENTER para continuar...\n");
      getch();
      cleanScreen();
      menu(p);
  }
}

int main(void) {
  struct products products;
  struct products *p;

  p = &products;

  cleanScreen();
  menu(p);

  return 0;
}
