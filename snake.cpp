#include<windows.h>  //ajuste da janela//
#include<stdio.h> // entrada e saida de dados//
#include<conio.h> // função getch, getche e kbhit, para receber entradas do usuario//
#include<time.h>   // ajuda a gerar o lugar aleatorio da fruta//
#include<stdlib.h> // gerar numeros aleatórios//
#include<iostream> // ajuda a gerar o lugar aleatorio da fruta//

int veloc = 170; //Define a Velocidade, que é recebida na função Sleep. Quanto menor o valor da Sleep, mais rápido  o jogo roda, entra em detalhes na função dificuldade//
int MaiorPontos; // Variavel global para a Maior Pontuação//
FILE *f; //Inicio da estrutura para fazer arquivo de Maior Pontuação//
int adicional; //VARIAVEL PARA AUMENTAR TAMANHO DA COBRA DEPENDENDO DA DIFICULDADE//
void gotoxy(int x,int y) //função que serve pra posicionar o cursor na tela, usado porque é util ao posicionar a cobra e "movimentar" ela//
{	COORD p={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}

void instrucoes() // Intruções do Jogo e sua jogabilidade//
{
// Aqui o  gotoxy é usado para posicionar as mensagens, sem ter de usar quebras de linha(\n) e espaços excessivos(\t)//

    system("cls"); //Limpar a tela//
    gotoxy(15,3);
    printf("Use as setas para controlar a cobrinha:");
    gotoxy(15,5);
    printf("Mover para cima %c", 94);
    gotoxy(15,6);
    printf("Mover para baixo %c",118);
    gotoxy(15,7);
    printf("Move para direita %c", 62);
    gotoxy(15,8);
    printf("Move para esquerda %c", 60);
    gotoxy(14,10);
    printf("Coma os alimentos %c para evoluir", 254);

    gotoxy(15,15);
    printf("Use a tecla s para finalizar a qualquer momento ");
    printf("\n\n\t");
    system("pause");
    system("cls");
}



void bem_vindo() // Tela de boas vindas e de inicio do programa//
{

//  o  gotoxy é usado para posicionar as mensagens, sem ter de usar quebras de linha(\n) e espaços excessivos(\t)//

    f=fopen("maiorpontos.txt","r"); //Cria um novo arquivo,  se já existir os seu valores são reescritos. Escrever os valores de maior Pontuação, independente de se já ter ou nao o arquivo//
    fscanf(f,"%d",&MaiorPontos); //Recebe o valor de Maior Pontuação//
    fclose(f); //  Fecha o arquivo aberto pela fopen //

    int veloc = 200; //definição da velocidade para um valor bom para o Sleep após a função dificuldade//
    char nome[20]; //Util para Ler o nome do usuario//
    int tecla, aux_dif=0;
    gotoxy(15,5);
    printf("Bem Vindo !!!\t\t Jogo Snake");
    gotoxy(15,8);
    printf("Digite seu nome: ");
    fflush(stdin);
    gets(nome);
    gotoxy(15,10);
    printf("\t\t\t\t  MENU");
    gotoxy(15,12);
    printf("Selecione uma das op%c%ces :", 135, 228);
    gotoxy(15,14);
    printf(" <ENTER> \tIniciar\t\n\t\t<ESC> \t\tInstru%c%ces\t\n\t\t<ESPACO> \tDificuldade ", 135, 228);
    printf("\t\t\t\t\t\t\n\n\n %c Produzido por Gabriel Morais", 169);

    do
    {
        tecla=_getch();

        if(tecla == 27) // Caso Queira ler as Instruções, tecle ESC//
        {

            system("cls");
            instrucoes();
            gotoxy(15,5);
            printf("<ENTER> Iniciar \t\t <ESPACO> Dificuldade ");
            tecla=_getch();
        }

        if(tecla == 32) // Caso Queira ajustar a Dificuldade, tecle ESPAÇO//
        {
            void dificuldade();
            dificuldade();
            aux_dif=1;
            gotoxy(15,5);
            printf("Pressione ENTER para come%car", 135);
            tecla=_getch();
        }
        if(aux_dif == 0) veloc=150;

        system("cls"); //limpar a tela//
    }while (tecla != 13 && tecla != 27 && tecla != 32);

}

void dificuldade()
{


   int dific;
system("cls");
            gotoxy(15,5);
            printf("Escolha o Nivel de Dificuldade: ");
            gotoxy(15,8);
            printf("<1> FACIL \t <2> MEDIA \t <3> DIFICIL ");

            dific = _getch();
            if(dific == 49){
                dific = 1;
                adicional=1;
            }
            if(dific == 50){
                dific = 2;
                adicional= 2;
            }
            if(dific == 51){
                    dific = 3;
                adicional=3;
            }
            veloc=240/dific;

system("cls");

}

 int jogar;
int main()
{
    // variavel para percorrer a matriz, d = Direção da cobra, Começa em 2 porque começa indo para a Direita//
    //cx = Coordenadas pro eixo X, linha, Cy = Coordenada pro Eixo Y, coluna, tamanhocobra = O tamanho da cobra, mx, my = MaçaY, MaçaY, coordenadas pra fruta//
     int x,d=2,cx[300]={1,2},cy[300]={7,7},tamanhocobra=1,mx,my;
    char tecla='a'; // Essa variavel define o fim do jogo, porque se ela muda pra 's', o jogo acaba.

bem_vindo();
    //DESENHAR TELA//

    for(x=0;x<18;x++)
    {   gotoxy(0,x);
        printf("%c",219);
        Sleep(10);
    }
    for(x=0;x<26;x++)
    {   gotoxy(x,0);
        printf("%c",219);
        Sleep(10);
    }
    for(x=0;x<18;x++)
    {   gotoxy(26,x);
        printf("%c",219);
    Sleep(10);
    }
    for(x=0;x<27;x++)
    {   gotoxy(x,18);
        printf("%c",219);
        Sleep(10);
    }

    // FIM DO DESENHO DA TELA//
int pontos =0;
    Sleep(veloc);

    //GERAR MAÇÃ ALEATORIA NO MAPA//

    srand(time(NULL));
    mx=(rand()%25)+1;
    my=(rand()%17)+1;

    //FIM DO GERAMENTO//

    while(tecla!='s')  // AQUI É O MOVIMENTO DA COBRA, AO MUDAR A DIREÇÃO SE MUDAM AS COORDENADAS X E Y, DE ACORDO//
    {   while(tecla!='s'&&!(tecla=_kbhit()))
        {
          for(x=tamanhocobra;x>0;x--)
            {   cx[x]=cx[x-1];
                cy[x]=cy[x-1];
            }


            if(d==0) cx[0]--;
            if(d==1)cy[0]--;
            if(d==2)cx[0]++;
            if(d==3)cy[0]++;




// O QUE É FEITO AQUI É A EXCLUIR AONDE A COBRA PASSA DE ACORDO COM O TAMANHO DE SUA CABEÇA, BASICAMENTE APAGAR SEU RASTRO//
            gotoxy(cx[tamanhocobra],cy[tamanhocobra]);
            printf(" ");
            // CASO TOQUE NA FRUTA, AUMENTAR TAMANHO DA COBRA E GERAR OUTRAS COORDENADAS PARA FRUTA, ALÉM DE AUMENTAR OS PONTOS//

            // mx, my = são as coordenadas da maça, ou fruta, para gerar no mapa de jogo//
            if(mx==cx[0]&&my==cy[0])
            {   tamanhocobra+=adicional;
                mx=(rand()%25)+1;
                my=(rand()%17)+1;
                pontos+=5;
            }

            //usa a GOTOXY para escolher posição para mostrar os pontos//
             gotoxy(10, 21);


            printf("Pontua%c%co= %d", 135, 198, pontos);
             gotoxy(10, 22);
            printf("Maior pontua%c%co : %d", 135, 198, MaiorPontos);
            gotoxy(cx[0],cy[0]);
            printf("%c",219);
            gotoxy(mx,my); // Coordenadas da fruta de acordo com as Variaveis MaçaX, MaçaY//
            printf("%c",254); // Printa a fruta//
            Sleep(veloc);
            for(x=1;x<tamanhocobra;x++)
            {   if(cx[0]==cx[x]&&cy[0]==cy[x])tecla='s'; // CASO A COBRA TOQUE EM SI MESMA, JOGO ACABA//
            }
            if(cy[0]==0||cy[0]==18||cx[0]==0||cx[0]==26)tecla='s';
        }
        if(tecla!='s')tecla=_getch();

        if(tecla=='K')d=0;
        if(tecla=='H')d=1;
        if(tecla=='M')d=2;
        if(tecla=='P')d=3;


        if(cy[0]==0||cy[0]==18||cx[0]==0||cx[0]==26)tecla='s'; // Caso toque na borda, jogo encerra//
         if(tecla=='s'){

         system("cls");
                if(pontos > MaiorPontos){
                        system("cls");
                            printf("\n\n\n\n\n\n\t\t\t\t\aNova Maior Pontua%c%co %d!!!!!!", 135, 198, pontos); // Caso o Jogador tire pontos Maior que a Maior Pontuação, salvar esse novo numero no arquivo//

        f=fopen("maiorpontos.txt","w"); //Cria um novo arquivo se não existir. Se existir os seu valores são reescritos. Ou seja, Escrever os valores de maior Pontuação, independente de se já ter ou nao o arquivo//
        fprintf(f,"%d",pontos);  // Printa os valores do arquivo//
        fclose(f); //  Fecha o arquivo aberto pela fopen //
    }


       printf("\a\a\a\n\n\n\n\t\t\t\t FIM DE JOGO \n\n\t\t\t\tPontua%c%co = %d \n\n\n ",135, 198, pontos); // Fim de Jogo com Mostra de Pontos//
    system("pause");

    }

    }

      printf("\n\n\t\t\n\n\t\t\t\t Deseja come%car denovo? \n\t\t <1>SIM <2>N%cO \n", 135, 199);      // Opção de Reiniciar o Jogo//
       jogar = _getch(); // Recebe o valor se quer ou não Jogar de Novo//

system("cls");


if(jogar == 49) main();
    else if(jogar == 50){ printf("\n\n\n\n\t\t\t\t\tObrigado Por Jogar !\n\n\n\n"); return 0;}  // Caso Aperte 2 O programa se encerra//

    if(jogar!=49 && jogar!=50){

        printf("\n1 ou 2 somente, por favor");
         jogar = _getch();
        while(jogar!= 49 && jogar!=50){
            jogar = _getch();
  if(jogar == 49) {system("cls"); main();}
    else if(jogar == 50){system("cls"); printf("\n\n\n\n\t\t\t\t\tObrigado Por Jogar !\n\n\n\n"); return 0;}

            }
    }
             system("cls");





    if(jogar == 49) main();
    else if(jogar == 50){ printf("\n\n\n\n\t\t\t\t\tObrigado Por Jogar !\n\n\n\n"); return 0;}

//USEI O GETCH POR PRATICIDADE, PARA APERTAR A TECLA SEM TER QUE TODA VEZ APERTAR O ENTER//
    _getch;
}
