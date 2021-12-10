#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

void cabecalho();
char* esconderSenha(char* senha);

int main(void) {
	
	//Definir idioma
	setlocale(LC_ALL, "portuguese");
	
	//Criando variáveis
	char text[999], usuarios[4][30], chaves[4][20], chaveDigitada[20], usuario[20], retornoSenha[20];
	int textCriptografado[999], escolhido, menu=1, opcao=0, contUsuario=0, tamText, tentativas=3;
	char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	//char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
	
	//VARIÁVEIS MÁSCARA	
	int tam = 0;
	char senha[20];
	
	//Muda cor de fundo
	system("color 1F");
	
	while(menu==1) {
		printf("\n\t\t\t\t*****SEGURANÇA DE DADOS*****\n");
		printf("\n\t\t\t\t   *****CRIPTOGRAFIA*****\n\n");
		printf("\t\t\t\t1. CADASTRAR USUÁRIO E CHAVE\n");
		printf("\t\t\t\t2. MOSTRAR LISTA DE CONTATOS\n");
		printf("\t\t\t\t3. ENVIAR MENSAGEM\n");
		printf("\t\t\t\t4. SAIR\n\n");
		printf("\t\t\t\t#  OPÇÃO: ");
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch(opcao) {
			case 1: 
				cabecalho();
				printf("\t\t\t\tDigite o nome do usuário: ");
				gets(usuarios[contUsuario]);
				fflush(stdin);
				if(strlen(usuarios[contUsuario]) == 0) {
					printf("\t\t\t\tNome do usuário não pode ficar em branco!!! Digite o nome do usúario: ");
				}
				while(strlen(usuarios[contUsuario]) == 0) {
					gets(usuarios[contUsuario]);
					fflush(stdin);	
				}
				
				strcpy (chaves[contUsuario], esconderSenha(senha));
				
				while(strlen(chaves[contUsuario]) < 3) {
					printf("\n\t\t\t\tA senha deve conter no mínimo 3 caracteres!!!\n");
					strcpy (chaves[contUsuario], esconderSenha(senha));				
				}
				
				printf("\n\n\t\t\t\tUsuário cadastrado com sucesso!!!");
				Sleep(2000);
				system("cls");		
				contUsuario++;
				opcao = 0;
			break;
			
			case 2:
				cabecalho();
				for(int i=0; i<contUsuario; i++) {
					printf("\t\t\t\t%i - %s\n",i+1 ,usuarios[i]);
				}
			
				//Visualizar senhas
				for(int i=0; i<contUsuario; i++) {
					printf("\t\t\t\t%i - %s\n",i+1 ,chaves[i]);
				}
				
				printf("\n\t\t\t\t");
				system("pause");
				system("cls");
				opcao = 0;
			break;
			
			case 3:
				if(contUsuario > 1) {
					cabecalho();
					printf("\t\t\tDigite o número do contato que deseja enviar a mensagem? ");
					scanf("%d", &escolhido);
					fflush(stdin);
					while(escolhido > contUsuario || escolhido <= 0) {
						cabecalho();
						printf("\t\t\t\t\tContato Inválido!!!\n");
						printf("\t\t\tDigite o número do contato que deseja enviar a mensagem? ");
						scanf("%i", &escolhido);
						fflush(stdin);					
					}
					printf("\t\t\tDigite a mensagem: ");
					gets(text);
					fflush(stdin);
					tamText = strlen(text);
					for(int i=0; i<tamText; i++) {
						for(int j=0; j<26; j++) {
							if(text[i] == alfabeto[j]) {
								textCriptografado[i] = j;
								break;
							}
						}	
					}
					
					printf("\n\n\t\t\tMensagem criptografada!\n\t\t\t");
					for(int i=0; i<tamText; i++) {
						printf("%i ", textCriptografado[i]);
					}
					
					printf("\n\n\t\t\t");
					system("pause");
					system("cls");						
					cabecalho();
					printf("\n\t\t\t\tMensagem recebida para %s\n", usuarios[escolhido-1]);
						
					strcpy (chaveDigitada, esconderSenha(senha));
							
					if(strcmp(chaves[escolhido-1], chaveDigitada) == 0) {
						printf("\n\t\t\t\tA mensagem diz: \n");
						printf("\n\t\t\t\t%s", text);
					} else {
						while(strcmp(chaves[escolhido-1], chaveDigitada) != 0) {
							tentativas--;
							if(tentativas > 0) {
								cabecalho();
								printf("\n\t\t\t\tMensagem recebida para %s\n", usuarios[escolhido-1]);
								if(tentativas > 1) {
									printf("\n\n\t\t\t\tChave incorreta!! Você tem %i tentativas\n", tentativas);
								} else {
									printf("\n\n\t\t\t\tChave incorreta!! Você tem %i tentativa\n", tentativas);
								}
						
								strcpy (chaveDigitada, esconderSenha(senha));
								
								if(strcmp(chaves[escolhido-1], chaveDigitada) == 0) {
									printf("\n\n\t\t\t\tA mensagem diz: \n");
									printf("\n\t\t\t\t%s", text);
									tentativas = 3;									
									break;
								}											
							} else {
								printf("\n\n\t\t\t\tVocê ultrapassou o limite de tentativas. \nNão é possível ver a mensagem!");
								//Limpando texto
								for(int i=0; i<999; i++) {
									text[i] = ' ';
								}
								tentativas = 3;
								break;
							}
						}
					}					
					
					printf("\n\n\t\t\t\t");
					system("pause");
					system("cls");					
				} else {
					cabecalho();
					printf("\t\t\t\tÉ necessário no mínimo 2 usuários cadastrados"
					"\n\t\t\t\tpara envio de mensagens!!!");
					system("color 4F");
					Sleep(3000);
					system("cls");
					system("color 1F");
					opcao = 0;
				}
			break;
			
			case 4:
				cabecalho();
				menu = 0;
				printf("\n\n\n\t\t\t\t     Fim de Programa!!!\n\n\n\n\n");
			break;
			
			default:
				cabecalho();
				printf("\t\t\t\t       OPÇÃO INVÁLIDA!!!");
				Sleep(3000);
				system("cls");
				fflush(stdin);
				opcao = 0;
			break;
		}
	}
	return 0;
}

void cabecalho() {
	system("cls");
	printf("\n\t\t\t\t*****SEGURANÇA DE DADOS*****\n");
	printf("\n\t\t\t\t   *****CRIPTOGRAFIA*****\n\n");
}

char* esconderSenha(char* senha) {
	int tam = 0;
	memset(senha, 0x00, sizeof(senha));
	printf("\t\t\t\tDigite sua chave de seguranca: ");
	fflush(stdin);
	do {  
		senha[tam] = getch();
		//Backspace          
		if(senha[tam] == 0x08 && tam > 0) {  
			printf("\b \b");
			senha[tam] = 0x00;
			tam--;
		}
		// Enter
		else if (senha[tam] == 13) {  
			senha[tam] = 0x00;
			break;
		}
		else if (senha[tam] != 0x08) {
			putchar('*');
			tam++;              
		}
	} while(tam < 10) ;
	tam=0;
	
	return senha;
}
