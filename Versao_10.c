/*
	Síntese 
	Objetivo: Projeto Final - Tema: Pokemon
	Nome: Giovana Pinho de Souza  e  Luiz Gustavo Pereira de Sousa
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

//Cores para o texto
#define vermelho "\x1b[1;31m"
#define verde "\x1b[32m"
#define amarelo "\x1b[1;33m"
#define azul "\x1b[34m"
#define rosa "\x1b[35m"
#define ciano "\x1b[36m"
#define reset "\x1b[0m"

//Função para impressão do texto em determinadas coordenadas da tela
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct tPokemon {
	int codigo;
	char nome[20];
	char tipo[10];
	char transferido; //deletado
	int quantPoke;
};

struct tCentroPoke {
	int computador;
	int enfermaria;
	int transferir;
	int pokeball;
};

struct tMochila {
	int pocaoHP[5];
	int pokeball;
	struct tPokemon *poke;
	char carteirinha[50];
};

struct tCarteirinha {
	char nome[100];
	char sexo[10];
	char regiao[10];
	int idade;
};

typedef enum {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

textcolor (int color) {
	__FOREGROUND = color;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
	                         color + (__BACKGROUND << 4));
}
// ARQUIVOS
int menu(void);
void professorCarvalho();
void apresentacao();
void logoJogo();
void pokeball();
void centroPoke();
void computador();
void enfermeiraJoy();
// funcoes e procedimentos
FILE *abrirArquivo(char arquivo[]);
void pokedex(char deletado, FILE *arq);
int consultar(int codigo, char deletado, FILE *arq);
struct tPokemon lerPoke(int registro, FILE *arq);
void gravarPoke(struct tPokemon poke, int registro, FILE *arq);
void gravarTreinador(struct tCarteirinha carte, int, FILE *arq);
void transferirPoke(int registro, char deletado, FILE *arq);
void deletarPoke(FILE**, char[]);
void nomeTreinador(struct tCarteirinha *carte, FILE *arqPoke);
void sexo(struct tCarteirinha *carte, FILE *arqPoke);
void regiao(struct tCarteirinha *carte, FILE *arqPoke);
int idade(struct tCarteirinha *carte, FILE *arqPoke);
int menu(void);
void capturarPoke(int registro, char deletado, FILE *arq);
void equipePoke(char deletado, FILE *arq);


int main (void) {
	struct tPokemon poke;
	struct tCarteirinha carte;
	struct tMochila *mochila;
	char nomeTreina[10], sexoTreina[10], sexoTreinador;
	int regiaoTreinador, idadeTreinador, professor[1000];
	int op, op2, op3, op4, codigo, posicao, cont, num, pode = 0, mOp;
	FILE *arqPoke = abrirArquivo("pokemon.dat");
	FILE *arqCarte = abrirArquivo("carteirinha.dat");

	mochila = malloc(sizeof(struct tMochila)); // alocando a variavel mochila

	mochila->pokeball = 10;

	if(arqPoke == NULL) {
		printf("\n\t-ERRO de abertura de arquivo-");
		return 1;
	}
	
	if(arqCarte == NULL) {
		printf("\n\t-ERRO de abertura de arquivo-");
		return 1;
	}

//	nomeTreinador(&carte, arqPoke); // perguntar nome do treinador

//	sexo(&carte, arqPoke); // perguntar sexo do treinador

//	regiao(&carte, arqPoke); // perguntar regiao do treinador

//	idadeTreinador = idade(&carte, arqPoke); // perguntar idade do treinador
//	carte.idade = idadeTreinador;

//	system("pause");
	system("cls");
	do {
		logoJogo();
		mOp = menuJogo();
		switch (mOp) {

			case 1: // CONTINUAR
				mochila = malloc(sizeof(struct tMochila)); // alocando a variavel mochila
				mochila->pokeball = 10;
				arqPoke = fopen("pokemon.dat", "rb");
				arqCarte = fopen("carteirinha.dat", "rb");
				
				fread(&carte, sizeof(carte), 1, arqCarte);

				if(arqPoke == NULL || arqCarte == NULL) {
					printf("\n\t-ERRO de abertura de arquivo-");
					return 1;
				}
				
				do {
					system("cls");
					logoJogo();
					op = menu();
					switch (op) {
						case 1: // INCLUIR
							system("cls");
							logoJogo();
							gotoxy(50, 17);
							printf(" INCLUIR POKEMON \n");
							do {
								gotoxy(46, 19);
								printf("Digite o codigo do pokemon: ");
								scanf("%d", &codigo);
								posicao = consultar(codigo, -1, arqPoke);

								if(posicao >= 0) {
									poke = lerPoke(posicao, arqPoke);
									gotoxy(44, 21);
									printf("-Codigo do pokemon ja registrado-\n");
									break;
								} else {
									poke.codigo = codigo;
									gotoxy(46, 20);
									printf("Digite o nome do pokemon: ");
									fflush(stdin);
									gets(poke.nome);
									gotoxy(46, 21);
									printf("Digite o tipo do pokemon: ");
									fflush(stdin);
									gets(poke.tipo);
									gravarPoke(poke, -1, arqPoke);
									//quantPoke++;
									//printf("%d",quantPoke);
									system("pause");
								} // adicionar um limite de 6 pokemons onde após eles todos iriam para o pokedex e só poderiam ser trocados na mochila
							} while(posicao > 0);


							system("pause");
						break;

						case 2: // CAPTURAR
						
							system("cls");
							gotoxy(50, 4);
							printf("CAPTURAR POKEMON");
							
							gotoxy(34, 6);
							printf("Informe o codigo do pokemon que deseja capturar: ");
							scanf("%d", &codigo);
						
							posicao = consultar(codigo, ' ', arqPoke);
							
							printf("%d", posicao);
							system("pause");
							
							if(posicao > 0) {
								poke = lerPoke(posicao, arqPoke);
								gotoxy(40, 8);
								printf("Codigo encontrado!\n\n");
								system("pause");
								gotoxy(40, 11);
								printf("Voce joga a Pokeball e o captura!! \n\n");
								system("pause");
								
								capturarPoke(posicao, '1', arqPoke);
								mochila->pokeball = mochila->pokeball - 1;
								
							} else {
								poke = lerPoke(posicao, arqPoke);
								gotoxy(40, 8);
								printf("Codigo nao encontrado!\n");
								system("pause");
								break;						
							}


						
//							system("cls");
//							gotoxy(50, 4);
//							printf("CAPTURAR POKEMON");
//
//							srand(time(NULL));
//
//							do{
//								num = (rand() % 10)+1;
//								for(cont = 0; cont < 10; cont++)
//									if(num == poke.codigo){
//										pode = 1;
//									}
//										printf("\n%d", num);
//										fseek(arqPoke, 0, SEEK_SET);
//								while (fread(&poke, sizeof(poke), 1, arqPoke)) {
//									if(num == poke.codigo){
//										printf("funciona merda");
//									}
//								}
//							}while(!pode);
//								
//							if(posicao > 0) {
//								poke = lerPoke(posicao, arqPoke);
//								gotoxy(40, 8);
//								printf("Codigo encontrado!\n");
//								capturarPoke(posicao, '/', arqPoke);
//								mochila->pokeball = mochila->pokeball - 1;
//								system("pause");
//							} else {
//								poke = lerPoke(posicao, arqPoke);
//								gotoxy(40, 8);
//								printf("Codigo nao encontrado!\n");
//								system("pause");
//								break;
//							}

							
						break;

						case 3: // MOCHILA
							system("cls");
							logoJogo();
							gotoxy(55, 16);
							printf("MOCHILA \n");
							gotoxy(50, 18);
							printf(" 1. Pokedex");
							gotoxy(50, 19);
							printf(" 2. Sua equipe Pokemon");
							gotoxy(50, 20);
							printf(" 3. Carteirinha do treinador");
							gotoxy(50, 21);
							printf(" 4. Quantidade de Pokeballs");
							gotoxy(50, 22);
							printf(" 0. Voltar");
							gotoxy(51, 24);
							printf("Escolha sua opcao: ");
							fflush(stdin);
							scanf("%d", &op2);

							if(op2 == 1) { // pokedex
								system("cls");
								gotoxy(47, 3);
								printf("POKEDEX - Pokemon cadastrados");
								pokedex(' ', arqPoke);

								system("pause");

							} else if(op2 == 2) { // equipe pokemon
								system("cls");
								gotoxy(52, 3);
								printf("Sua Equipe Pokemon");
								equipePoke('/', arqPoke);
								system("pause");

							} else if(op2 == 3) { // carteirinha de treinador
								system("cls");
								printf("\t\t\t\t\t _________________________________________\n");
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t|        CARTEIRINHA DE TREINADOR         |\n");
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t|    Nome: %s         \n", carte.nome);
								printf("\t\t\t\t\t|    Sexo: %s         \n", carte.sexo);
								printf("\t\t\t\t\t|    Regiao: %s       \n", carte.regiao);
								printf("\t\t\t\t\t|    Idade: %d anos   \n", carte.idade);
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t -----------------------------------------\n");
								system("pause");

							} else if(op2 == 4) { // quantidade de pokeballs
								system("cls");
								pokeball();
								gotoxy(50, 7);
								printf("Voce tem %d Pokeballs \n", mochila->pokeball);
								system("pause");
							}
						break;

						case 4: // CENTRO POKEMON
							system("cls");
							centroPoke();
							gotoxy(53, 18);
							printf("CENTRO POKEMON \n");
							gotoxy(50, 20);
							printf(" 1. Para transferir um pokemon");
							gotoxy(50, 21);
							printf(" 2. Para alterar pokemon da sua equipe");
							gotoxy(50, 22);
							printf(" 3. Para falar com a Enfermeira Joy\n");
							gotoxy(50, 23);
							printf(" 0. Voltar");
							gotoxy(51, 25);
							printf("Escolha sua opcao: ");
							scanf("%d", &op3);

							if(op3 == 1) { // transferir pokemon
								system("cls");
								computador();
								gotoxy(34, 18);
								printf("Informe o codigo do pokemon que deseja transferir: ");
								scanf("%d", &codigo);

								posicao = consultar(codigo, ' ', arqPoke);

								if(posicao >= 0) {
									gotoxy(48, 21);
									printf("Codigo encontrado!\n");
									transferirPoke(posicao, '*', arqPoke);
									system("pause");
								} else {
									gotoxy(48, 21);
									printf("Codigo nao encontrado!\n");
									system("pause");
									break;
								}

							} else if(op3 == 2) { // alterar pokemon
								system("cls");
								computador();
								gotoxy(36, 18);
								printf("Informe o codigo do pokemon que deseja alterar: ");
								scanf("%d", &codigo);

								posicao = consultar(codigo, ' ', arqPoke);

								if(posicao >= 0) {
									poke = lerPoke(posicao, arqPoke);
									gotoxy(50, 20);
									printf("Codigo encontrado!");
									gotoxy(50, 21);
									printf("Nome: %s ", poke.nome);
									gotoxy(50, 22);
									printf("Tipo...: %s ", poke.tipo);

									gotoxy(44, 24);
									printf("Digite o novo nome do pokemon: ");
									fflush(stdin);
									gets(poke.nome);
									gotoxy(44, 25);
									printf("Digite o novo tipo do pokemon: ");
									fflush(stdin);
									gets(poke.tipo);

									gravarPoke(poke, posicao, arqPoke);
									system("pause");
								} else {
									gotoxy(50, 20);
									printf("Codigo nao encontrado!\n");
									system("pause");
								}

							} else if(op3 == 3) { // ENFERMEIRA JOY
								system("cls");
								enfermeiraJoy();

								gotoxy(31, 13);
								printf("Ola, eu sou a Enfermeira Joy, estou aqui para ajuda-lo.");

								gotoxy(50, 16);
								printf(" 1. Pegar mais Pokeballs");
								gotoxy(50, 17);
								printf(" 2. Alterar informacoes da carteirinha");
								gotoxy(50, 18);
								printf(" 0. Voltar");
								gotoxy(50, 20);
								printf("O que deseja fazer? ");
								scanf("%d", &op4);


								if(op4 == 1) { // pegar mais pokeballs
									system("cls");
									enfermeiraJoy();
									gotoxy(45, 13);
									printf("Aqui estao! Volte sempre!");
									gotoxy(42, 15);
									printf("Voce recebeu mais 10 Pokeballs\n");
									mochila->pokeball = mochila->pokeball + 10;
									system("pause");

								} else if(op4 == 2) { // alterar informacoes da carteirinha
									system("cls");
									enfermeiraJoy();
									gotoxy(42, 13);
									printf("Por favor, me diga seus dados: ");
									do {
										gotoxy(44, 15);
										printf("Qual seu nome? ");
										fflush(stdin);
										gets(nomeTreina);
									} while(strlen(nomeTreina) == 0);

									do {
										gotoxy(44, 17);
										printf("Qual seu sexo?");
										gotoxy(44, 18);
										printf(" M - Masculino");
										gotoxy(44, 19);
										printf(" F - Feminino");
										gotoxy(44, 20);

										fflush(stdin);
										scanf("%c", carte.sexo);
										*carte.sexo = toupper(*carte.sexo);

									} while(*carte.sexo != 'M' && *carte.sexo != 'F');

									if(*carte.sexo == 'F') {
										strcpy(carte.sexo,"Feminino");
									} else {
										strcpy(carte.sexo,"Masculino");
									}

									do {
										gotoxy(44, 22);
										printf("REGIOES POKEMON: \n\n");
										gotoxy(44, 23);
										printf(" 1 - Kanto\n");
										gotoxy(44, 24);
										printf(" 2 - Johto\n");
										gotoxy(44, 25);
										printf(" 3 - Hoenn\n");
										gotoxy(44, 26);
										printf(" 4 - Unova\n");
										gotoxy(44, 27);
										printf("De onde voce vem? ");
										fflush(stdin);
										scanf("%d", &regiaoTreinador);
									} while(regiaoTreinador < 1 || regiaoTreinador > 4);

									if (regiaoTreinador == 1) {
										strcpy(carte.regiao,"kanto");
									} else if(regiaoTreinador == 2) {
										strcpy(carte.regiao,"Johto");
									} else if(regiaoTreinador == 3) {
										strcpy(carte.regiao,"Hoenn");
									} else if(regiaoTreinador == 4) {
										strcpy(carte.regiao,"Unova");
									}

									do {
										gotoxy(44, 29);
										printf("Qual sua idade? ");
										fflush(stdin);
										scanf("%d", &idadeTreinador);
									} while(idadeTreinador <= 0);

									carte.idade = idadeTreinador;
									system("pause");
								}
							}
						break;
					}
					system("cls");
				} while (op != 0);
				
			free(mochila);
			fclose(arqPoke);
			fclose(arqCarte);
			break;
			
			case 2: // NOVO JOGO
				
				arqCarte = fopen("carteirinha.dat", "r+b");
				arqPoke = fopen("pokemon.dat", "r+b");
				
				if(arqCarte == NULL)
					arqCarte = fopen("carteirinha.dat", "w+b"); // se nao tiver ele cria um 	
				
				if(arqPoke == NULL)
					arqPoke = fopen("pokemon.dat", "w+b"); // se nao tiver ele cria um 
					
				nomeTreinador(&carte, arqPoke);
				sexo(&carte, arqPoke);
				regiao(&carte, arqPoke);
				idadeTreinador = idade(&carte, arqPoke);
				carte.idade = idadeTreinador;
				
				gravarTreinador(carte, -1, arqCarte);
				
				system("pause");
				do {
					system("cls");
					logoJogo();
					op = menu();
					switch (op) {
						case 1: // INCLUIR
							system("cls");
							logoJogo();
							gotoxy(50, 17);
							printf(" INCLUIR POKEMON \n");
							do {
								gotoxy(46, 19);
								printf("Digite o codigo do pokemon: ");
								scanf("%d", &codigo);
								posicao = consultar(codigo, -1, arqPoke);


								if(posicao >= 0) {
									poke = lerPoke(posicao, arqPoke);
									gotoxy(44, 21);
									printf("-Codigo do pokemon ja registrado-\n");
									break;
								} else {
									poke.codigo = codigo;
									gotoxy(46, 20);
									printf("Digite o nome do pokemon: ");
									fflush(stdin);
									gets(poke.nome);
									gotoxy(46, 21);
									printf("Digite o tipo do pokemon: ");
									fflush(stdin);
									gets(poke.tipo);
									gravarPoke(poke, -1, arqPoke);
									//quantPoke++;
									//printf("%d",quantPoke);
									system("pause");
								} // adicionar um limite de 6 pokemons onde após eles todos iriam para o pokedex e só poderiam ser trocados na mochila
							} while(posicao > 0);


							system("pause");
						break;

						case 2: // CAPTURAR
							system("cls");
							gotoxy(50, 4);
							printf("CAPTURAR POKEMON");
							
							gotoxy(34, 6);
							printf("Informe o codigo do pokemon que deseja capturar: ");
							scanf("%d", &codigo);
						
							posicao = consultar(codigo, ' ', arqPoke);
							
							printf("%d", posicao);
							system("pause");
							
							if(posicao > 0) {
								poke = lerPoke(posicao, arqPoke);
								gotoxy(40, 8);
								printf("Codigo encontrado!\n\n");
								system("pause");
								gotoxy(40, 11);
								printf("Voce joga a Pokeball e o captura!! \n\n");
								system("pause");
								
								capturarPoke(posicao, '1', arqPoke);
								mochila->pokeball = mochila->pokeball - 1;
								
							} else {
								poke = lerPoke(posicao, arqPoke);
								gotoxy(40, 8);
								printf("Codigo nao encontrado!\n");
								system("pause");
								break;						
							}
							
							


						
//							system("cls");
//							gotoxy(50, 4);
//							printf("CAPTURAR POKEMON");
//
//							srand(time(NULL));
//
//							do{
//								num = (rand() % 10)+1;
//								for(cont = 0; cont < 10; cont++)
//									if(num == poke.codigo){
//										pode = 1;
//									}
//										printf("\n%d", num);
//										fseek(arqPoke, 0, SEEK_SET);
//								while (fread(&poke, sizeof(poke), 1, arqPoke)) {
//									if(num == poke.codigo){
//										printf("funciona merda");
//									}
//								}
//							}while(!pode);
//								
//							if(posicao > 0) {
//								poke = lerPoke(posicao, arqPoke);
//								gotoxy(40, 8);
//								printf("Codigo encontrado!\n");
//								capturarPoke(posicao, '/', arqPoke);
//								mochila->pokeball = mochila->pokeball - 1;
//								system("pause");
//							} else {
//								poke = lerPoke(posicao, arqPoke);
//								gotoxy(40, 8);
//								printf("Codigo nao encontrado!\n");
//								system("pause");
//								break;
//							}

						break;

						case 3: // MOCHILA
							system("cls");
							logoJogo();
							gotoxy(55, 16);
							printf("MOCHILA \n");
							gotoxy(50, 18);
							printf(" 1. Pokedex");
							gotoxy(50, 19);
							printf(" 2. Sua equipe Pokemon");
							gotoxy(50, 20);
							printf(" 3. Carteirinha do treinador");
							gotoxy(50, 21);
							printf(" 4. Quantidade de Pokeballs");
							gotoxy(50, 22);
							printf(" 0. Voltar");
							gotoxy(51, 24);
							printf("Escolha sua opcao: ");
							fflush(stdin);
							scanf("%d", &op2);

							if(op2 == 1) { // pokedex
								system("cls");
								gotoxy(47, 3);
								printf("POKEDEX - Pokemon cadastrados");
								pokedex(' ', arqPoke);

								system("pause");

							} else if(op2 == 2) { // equipe pokemon
								system("cls");
								gotoxy(52, 3);
								printf("Sua Equipe Pokemon");
								equipePoke('/', arqPoke);
								system("pause");

							} else if(op2 == 3) { // carteirinha de treinador
								system("cls");
								printf("\t\t\t\t\t _________________________________________\n");
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t|        CARTEIRINHA DE TREINADOR         |\n");
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t|    Nome: %s         \n", carte.nome);
								printf("\t\t\t\t\t|    Sexo: %s         \n", carte.sexo);
								printf("\t\t\t\t\t|    Regiao: %s       \n", carte.regiao);
								printf("\t\t\t\t\t|    Idade: %d anos   \n", carte.idade);
								printf("\t\t\t\t\t|                                         |\n");
								printf("\t\t\t\t\t -----------------------------------------\n");
								system("pause");

							} else if(op2 == 4) { // quantidade de pokeballs
								system("cls");
								pokeball();
								gotoxy(50, 7);
								printf("Voce tem %d Pokeballs \n", mochila->pokeball);
								system("pause");

							} 
						break;

						case 4: // CENTRO POKEMON
							system("cls");
							centroPoke();
							gotoxy(53, 18);
							printf("CENTRO POKEMON \n");
							gotoxy(50, 20);
							printf(" 1. Para transferir um pokemon");
							gotoxy(50, 21);
							printf(" 2. Para alterar pokemon da sua equipe");
							gotoxy(50, 22);
							printf(" 3. Para falar com a Enfermeira Joy\n");
							gotoxy(50, 23);
							printf(" 0. Voltar");
							gotoxy(51, 25);
							printf("Escolha sua opcao: ");
							scanf("%d", &op3);

							if(op3 == 1) { // transferir pokemon
								system("cls");
								computador();
								gotoxy(34, 18);
								printf("Informe o codigo do pokemon que deseja transferir: ");
								scanf("%d", &codigo);

								posicao = consultar(codigo, ' ', arqPoke);

								if(posicao >= 0) {
									gotoxy(48, 21);
									printf("Codigo encontrado!\n");
									transferirPoke(posicao, '*', arqPoke);
									system("pause");
								} else {
									gotoxy(48, 21);
									printf("Codigo nao encontrado!\n");
									system("pause");
									break;
								}

							} else if(op3 == 2) { // alterar pokemon
								system("cls");
								computador();
								gotoxy(36, 18);
								printf("Informe o codigo do pokemon que deseja alterar: ");
								scanf("%d", &codigo);

								posicao = consultar(codigo, ' ', arqPoke);

								if(posicao >= 0) {
									poke = lerPoke(posicao, arqPoke);
									gotoxy(50, 20);
									printf("Codigo encontrado!");
									gotoxy(50, 21);
									printf("Nome: %s ", poke.nome);
									gotoxy(50, 22);
									printf("Tipo...: %s ", poke.tipo);

									gotoxy(44, 24);
									printf("Digite o novo nome do pokemon: ");
									fflush(stdin);
									gets(poke.nome);
									gotoxy(44, 25);
									printf("Digite o novo tipo do pokemon: ");
									fflush(stdin);
									gets(poke.tipo);

									gravarPoke(poke, posicao, arqPoke);
									system("pause");
								} else {
									gotoxy(50, 20);
									printf("Codigo nao encontrado!\n");
									system("pause");
								}

							} else if(op3 == 3) { // ENFERMEIRA JOY
								system("cls");
								enfermeiraJoy();

								gotoxy(31, 13);
								printf("Ola, eu sou a Enfermeira Joy, estou aqui para ajuda-lo.");

								gotoxy(50, 16);
								printf(" 1. Pegar mais Pokeballs");
								gotoxy(50, 17);
								printf(" 2. Alterar informacoes da carteirinha");
								gotoxy(50, 18);
								printf(" 0. Voltar");
								gotoxy(50, 20);
								printf("O que deseja fazer? ");
								scanf("%d", &op4);


								if(op4 == 1) { // pegar mais pokeballs
									system("cls");
									enfermeiraJoy();
									gotoxy(45, 13);
									printf("Aqui estao! Volte sempre!");
									gotoxy(42, 15);
									printf("Voce recebeu mais 10 Pokeballs\n");
									mochila->pokeball = mochila->pokeball + 10;
									system("pause");

								} else if(op4 == 2) { // alterar informacoes da carteirinha
									system("cls");
									enfermeiraJoy();
									gotoxy(42, 13);
									printf("Por favor, me diga seus dados: ");
									do {
										gotoxy(44, 15);
										printf("Qual seu nome? ");
										fflush(stdin);
										gets(nomeTreina);
									} while(strlen(nomeTreina) == 0);

									do {
										gotoxy(44, 17);
										printf("Qual seu sexo?");
										gotoxy(44, 18);
										printf(" M - Masculino");
										gotoxy(44, 19);
										printf(" F - Feminino");
										gotoxy(44, 20);

										fflush(stdin);
										scanf("%c", carte.sexo);
										*carte.sexo = toupper(*carte.sexo);

									} while(*carte.sexo != 'M' && *carte.sexo != 'F');

									if(*carte.sexo == 'F') {
										strcpy(carte.sexo,"Feminino");
									} else {
										strcpy(carte.sexo,"Masculino");
									}

									do {
										gotoxy(44, 22);
										printf("REGIOES POKEMON: \n\n");
										gotoxy(44, 23);
										printf(" 1 - Kanto\n");
										gotoxy(44, 24);
										printf(" 2 - Johto\n");
										gotoxy(44, 25);
										printf(" 3 - Hoenn\n");
										gotoxy(44, 26);
										printf(" 4 - Unova\n");
										gotoxy(44, 27);
										printf("De onde voce vem? ");
										fflush(stdin);
										scanf("%d", &regiaoTreinador);
									} while(regiaoTreinador < 1 || regiaoTreinador > 4);

									if (regiaoTreinador == 1) {
										strcpy(carte.regiao,"kanto");
									} else if(regiaoTreinador == 2) {
										strcpy(carte.regiao,"Johto");
									} else if(regiaoTreinador == 3) {
										strcpy(carte.regiao,"Hoenn");
									} else if(regiaoTreinador == 4) {
										strcpy(carte.regiao,"Unova");
									}

									do {
										gotoxy(44, 29);
										printf("Qual sua idade? ");
										fflush(stdin);
										scanf("%d", &idadeTreinador);
									} while(idadeTreinador <= 0);

									carte.idade = idadeTreinador;
									system("pause");
								}
							}
						break;
					}
					system("cls");
				} while (op != 0);
				
			free(mochila);
			fclose(arqPoke);
			fclose(arqCarte);
			break;
			}
		} while(mOp != 0);
		return 0;
	}
	
	FILE *abrirArquivo(char arquivo[]) {
		FILE *arq = fopen(arquivo, "r+b");
		if (arq == NULL)
			arq = fopen(arquivo, "w+b");
		return arq;
	}

	void professorCarvalho() {
		FILE *arqProf;
		char professor[100];
		int y = 0;

		arqProf = fopen("arquivos/professorCarvalho.txt","r");

		while(fgets(professor, 100, arqProf)!=NULL) {
			gotoxy(42, y);
			printf("%s", professor);
			y++;
		}
		fclose(arqProf);
	}

	void apresentacao() {
		FILE *arqApresent;
		char apresentacao[100];
		int y = 16;

		arqApresent = fopen("arquivos/apresentacao.txt","r");

		while(fgets(apresentacao, 100, arqApresent) != NULL) {
			gotoxy(28, y);
			printf("%s", apresentacao);
			y++;
		}
		fclose(arqApresent);
	}

	void logoJogo() {
		FILE *arqLogo;
		char logo[100];
		int y = 2;

		arqLogo = fopen("arquivos/logo.txt","r");

		while(fgets(logo, 100, arqLogo)!=NULL) {
			gotoxy(35, y);
			if(y > 2 && y <= 7) {
				printf(amarelo "%s" reset, logo);
			} else if(y > 7) {
				printf(vermelho "%s" reset, logo);
			}
			y++;
		}
		fclose(arqLogo);
	}

	void pokeball() {
		FILE *arq;
		char pokeball[100];
		int y = 2, x = 57;

		arq = fopen("arquivos/pokeball.txt","r");

		while(fgets(pokeball, 100, arq)!=NULL) {
			gotoxy(x, y);
			printf(vermelho "%s" reset, pokeball);

			y++;
		}
		fclose(arq);
	}

	void centroPoke() {
		FILE *arqCentro;
		char centro[100];
		int y = 2, x = 37;

		arqCentro = fopen("arquivos/centroPoke.txt","r");

		while(fgets(centro, 100, arqCentro)!=NULL) {
			gotoxy(x, y);
			if(y > 2 && y <= 7) {
				printf(vermelho "%s" reset, centro);
			} else if(y==8) {
				printf(" |                       "ciano"_______________"reset"   | ");
			} else if(y==9) {
				printf(" |         _____        "ciano"|       |       |"reset"  |");
			} else if(y==10) {
				printf(" |        |     |       "ciano"|_______|_______|"reset"  |");
			} else if(y > 7) {
				printf("%s", centro);
			}
			gotoxy(37,8);
			if((x == 62 && y == 8)) {
				printf(ciano "%s" reset, centro);
			}
			y++;
		}
		fclose(arqCentro);
	}

	void computador() {
		FILE *arqComp;
		char computador[100];
		int y = 2, x = 45;

		arqComp = fopen("arquivos/computador.txt","r");

		while(fgets(computador, 100, arqComp)!=NULL) {
			gotoxy(x, y);
			if(y > 2 && y <= 8) {
				printf(ciano "%s" reset, computador);
			} else if(y > 8) {
				printf("%s", computador);
			}
			y++;
		}
		fclose(arqComp);
	}

	void enfermeiraJoy() {
		FILE *arqJoy;
		char enfermeira[200];
		int y = 2, x = 23;

		arqJoy = fopen("arquivos/enfermeiraJoy.txt","r");

		while(fgets(enfermeira, 200, arqJoy)!=NULL) {
			gotoxy(x, y);
			printf("%s", enfermeira);
			y++;
		}
		fclose(arqJoy);
	}

	void nomeTreinador(struct tCarteirinha *carte, FILE *arqPoke) {
		char professor[100];
		int y = 24;

		do {
			system("cls");
			professorCarvalho();
			apresentacao();

			gotoxy(46, y);
			printf("Qual seu nome?\n ");
			fflush(stdin);
			gotoxy(46, y = 25);
			gets((*carte).nome);

		} while(strlen((*carte).nome) == 0);
	}

	void sexo(struct tCarteirinha *carte, FILE *arqPoke) {
		char sexoTreina, professor[100];
		int y = 17, x = 47;

		do {
			system("cls");
			professorCarvalho();

			gotoxy(x, y);
			printf("Qual seu sexo? \n");
			gotoxy(x, y+2);
			printf("M - Masculino\n");
			gotoxy(x, y+3);
			printf("F - Feminino\n");

			fflush(stdin);
			gotoxy(x, y+4);
			scanf("%c", &sexoTreina);
			sexoTreina = toupper(sexoTreina);

		} while(sexoTreina != 'M' && sexoTreina != 'F');

		if(sexoTreina == 'F') {
			strcpy((*carte).sexo,"Feminino");
		} else {
			strcpy((*carte).sexo,"Masculino");
		}
	}

	void regiao(struct tCarteirinha *carte, FILE *arqPoke) {
		int regiaoTreinador, y = 17, x = 45;
		char professor[100];

		while(regiaoTreinador < 1 || regiaoTreinador > 4) {
			system("cls");

			professorCarvalho();
			gotoxy(x, y+1);
			printf("  REGIOES POKEMON: \n\n");
			gotoxy(x, y+3);
			printf(" 1 - Kanto\n");
			gotoxy(x, y+4);
			printf(" 2 - Johto\n");
			gotoxy(x, y+5);
			printf(" 3 - Hoenn\n");
			gotoxy(x, y+6);
			printf(" 4 - Unova\n");
			gotoxy(x, y+7);
			printf(" De onde voce vem? ");
			fflush(stdin);
			gotoxy(x, y+8);
			scanf("%d", &regiaoTreinador);
		}

		if (regiaoTreinador == 1) {
			strcpy((*carte).regiao,"Kanto");
		} else if(regiaoTreinador == 2) {
			strcpy((*carte).regiao,"Johto");
		} else if(regiaoTreinador == 3) {
			strcpy((*carte).regiao,"Hoenn");
		} else if(regiaoTreinador == 4) {
			strcpy((*carte).regiao,"Unova");
		}
	}

	int idade(struct tCarteirinha *carte, FILE *arqPoke) {
		int idadeTreinador, y = 18, x = 47;
		char professor[100];
		do {
			system("cls");
			professorCarvalho();
			gotoxy(x, y);
			printf("Qual sua idade? ");
			fflush(stdin);
			gotoxy(x, y+1);
			scanf("%d", &idadeTreinador);
		} while(idadeTreinador <= 0);

		return idadeTreinador;
	}
	
	int menuJogo(void) {
		int mOp, y = 16;
		FILE *arqMenu;
		char char_menu[200];

		arqMenu = fopen("arquivos/menuJogo.txt","r");

		while(fgets(char_menu, 200, arqMenu) != NULL) {
			gotoxy(51, y);
			printf("%s", char_menu);
			y++;
			if(y == 28) {
				y++;
			}
		}

		fflush(stdin);
		scanf("%d", &mOp);
		return mOp;
	}
	
	int menu(void) {
		int op, y = 16;
		FILE *arqMenu;
		char char_menu[200];

		arqMenu = fopen("arquivos/menu.txt","r");

		while(fgets(char_menu, 200, arqMenu) != NULL) {
			gotoxy(51, y);
			printf("%s", char_menu);
			y++;
			if(y == 28) {
				y++;
			}
		}

		fflush(stdin);
		scanf("%d", &op);
		return op;
	}

	void gravarPoke(struct tPokemon poke, int registro, FILE *arq) { // cadastrar pokemons
		if(registro <= 0) {
			poke.transferido = ' ';
			fseek(arq, 0, SEEK_END); // ponteiro, quantas vezes, seek(alguma coisa) é final, inicio ou meio
		} else {
			fseek(arq, (registro-1)*sizeof(struct tPokemon), SEEK_SET);
		}
		fwrite(&poke, sizeof(poke), 1, arq);
	}
	
	void gravarTreinador(struct tCarteirinha carte, int registro, FILE *arq){
		if(registro <= 0) {
			fseek(arq, 0, SEEK_END); // ponteiro, quantas vezes, seek(alguma coisa) é final, inicio ou meio
		} else {
			fseek(arq, (registro-1)*sizeof(struct tCarteirinha), SEEK_SET);
		}
		fwrite(&carte, sizeof(carte), 1, arq);
		
	}

	void pokedex(char deletado, FILE *arq) { // listar os pokemons cadastrados
		struct tPokemon poke;
		printf("\n\t\t\t\t\t\t---------------------------\n");
		fseek(arq, 0, SEEK_SET);
		while (fread(&poke, sizeof(poke), 1, arq)) {
			if (poke.transferido == deletado)
				printf("\n\t\t\t\t\t\t%d - %s - %s\n", poke.codigo, poke.nome, poke.tipo);
		}
	}

	void transferirPoke(int registro, char deletado, FILE *arq) { // excluir um pokemon
		struct tPokemon poke;

		fseek(arq, (registro-1)*sizeof(poke), SEEK_SET); // apontando pro prox
		fread(&poke, sizeof(poke), 1, arq);
		poke.transferido = '*';
		fseek(arq, -sizeof(poke), SEEK_CUR); // -sizeof fazer ele recuar
		fwrite(&poke, sizeof(poke), 1, arq);
	}

	struct tPokemon lerPoke(int registro, FILE *arq) {
		struct tPokemon poke;

		fseek(arq, (registro-1)*sizeof(poke), SEEK_SET);
		fread(&poke, sizeof(poke), 1, arq);
		return poke;
	}

	int consultar(int codigo, char deletado, FILE *arq) { // consultar se esse pokemon esta cadastrado
		struct tPokemon poke;
		int registro = 0;

		fseek(arq, 0, SEEK_SET);
		while (fread(&poke, sizeof(struct tPokemon), 1, arq)) {
			registro++;
			if((poke.codigo == codigo) && (poke.transferido != '*')) {
				return registro; // se ja tiver um retorna 1
			}

		}
		return -1; // se nao tiver retorna -1
	}

	void capturarPoke(int registro, char deletado, FILE *arq) { // capturar um pokemon
		struct tPokemon poke;

		fseek(arq, (registro-1)*sizeof(poke), SEEK_SET);
		fread(&poke, sizeof(poke), 1, arq);
		poke.transferido = '/';
		fseek(arq, -sizeof(poke), SEEK_CUR);
		fwrite(&poke, sizeof(poke), 1, arq);
	}

	void equipePoke(char deletado, FILE *arq) {
		struct tPokemon poke;
		printf("\n\t\t\t\t\t\t---------------------------\n");
		fseek(arq, 0, SEEK_SET);
		while (fread(&poke, sizeof(poke), 1, arq)) {
			if (poke.transferido == deletado)
				printf("\n\t\t\t\t\t\t%d - %s - %s\n", poke.codigo, poke.nome, poke.tipo);
		}
	}

