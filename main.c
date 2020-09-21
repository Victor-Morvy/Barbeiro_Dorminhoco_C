#include <windows.h>
#include <stdio.h>
#define QTTOTAL 5
#define TEMPO 3

DWORD dxWaitResult_barbeiro;
HANDLE barbeiro;

DWORD dxWaitResult_cadeiras;
HANDLE cadeiras;

DWORD dxWaitResult_cadeiraBarbeiro;
HANDLE cadeiraBarbeiro;

DWORD dxWaitResult_dormindo;
HANDLE dormindo;

DWORD dxWaitResult_aberto;
HANDLE aberto;

void Cliente()
{
	int cortou = 1;
	
	//protocolo de entrada da regi�o cr�tica
	dxWaitResult_barbeiro = WaitForSingleObject(barbeiro, 0);
	//INFINITE esperar� uma vaga para continuar execu��o
	//0 para n�o esperar (n�o conseguiu na hora, ele desiste)
	
	switch(dxWaitResult_barbeiro)
	{
		case WAIT_OBJECT_0://O barbeiro estava dormindo e est� dispon�vel para cortar o cabelo

			printf("O cliente %d acordou o barbeiro e esta cortando o cabelo...\n", GetCurrentThreadId());
			ReleaseSemaphore(dormindo, 1, NULL);
			break;
		
		case WAIT_TIMEOUT: //O cliente vai procurar se tem cadeira para sentar
			
			printf("O barbeiro esta ocupado, o cliente %d esta procurando cadeira para sentar...\n", GetCurrentThreadId());
			
			dxWaitResult_cadeiras = WaitForSingleObject(cadeiras, 0);
			//INFINITE esperar� uma vaga para continuar execu��o
			//0 para n�o esperar (n�o conseguiu na hora, ele desiste)
			
			switch(dxWaitResult_cadeiras)
			{
				case WAIT_TIMEOUT: //O cliente vai procurar se tem cadeira para sentar
					
					printf("O cliente %d nao achou cadeiras disponiveis, e foi embora!\n", GetCurrentThreadId());
					cortou = 0;
					
					break;
				
				case WAIT_OBJECT_0://O barbeiro estava dormindo e est� dispon�vel para cortar o cabelo

					printf("O cliente %d achou uma cadeira disponivel e sentou!\n", GetCurrentThreadId());
					
					dxWaitResult_barbeiro = WaitForSingleObject(barbeiro, INFINITE);
					
					switch(dxWaitResult_barbeiro)
					{
						case WAIT_OBJECT_0://O barbeiro estava dormindo e est� dispon�vel para cortar o cabelo
							
							printf("O cliente %d esta cortando o cabelo...\n", GetCurrentThreadId());
							ReleaseSemaphore(dormindo, 1, NULL);
							ReleaseSemaphore(cadeiras, 1, NULL);

							break;
					}
			}
			break;
	}
	sleep(TEMPO);
	if (cortou)
	{
		printf("O cliente %d cortou o cabelo e foi embora...\n", GetCurrentThreadId());
	}
	system("PAUSE");
}

void Barbeiro()
{
	while(1)
	{	printf("O barbeiro esta dormindo...\n");
		
		dxWaitResult_dormindo = WaitForSingleObject(dormindo, INFINITE);
				
		switch(dxWaitResult_dormindo)
		{
			case WAIT_OBJECT_0://O barbeiro estava dormindo e est� dispon�vel para cortar o cabelo
				printf("O barbeiro est� cortando o cabelo do cliente...\n");
				
				sleep(TEMPO);
				printf("Finalizado o corte de cabelo, procurando outro cliente...\n");
				ReleaseSemaphore(barbeiro, 1, NULL);
				break;
		}
	}
}

int main(int argc, char** argv)
{
	printf("\n::::INICIANDO v1.2::::\n");
		  
	// cadeira barbeiro
	cadeiraBarbeiro = CreateSemaphore(NULL, 
	1, //valor inicial (vagas)
	1, //tamanho m�ximo
	"cadeiraBarbeiro"); //nome pra diferencia��o
	
	// barbeiro
	barbeiro = CreateSemaphore(NULL, 
	1, //valor inicial (vagas)
	1, //tamanho m�ximo
	"barbeiro"); //nome pra diferencia��o
	
	// cadeiras
	cadeiras = CreateSemaphore(NULL, 
	QTTOTAL, //valor inicial (vagas)
	QTTOTAL, //tamanho m�ximo
	"fila"); //nome pra diferencia��o
	
	//dormindo
	dormindo = CreateSemaphore(NULL, 
	0, //valor inicial (vagas)
	1, //tamanho m�ximo
	"dormindo"); //nome pra diferencia��o
	
	if(argc>1)
	{
		if(strcmp(argv[1],"CLIENTE")==0)
			Cliente();

		if(strcmp(argv[1],"BARBEIRO")==0)
			Barbeiro();
	}
	else
	{
		printf("Uso invalido. Informe o tipo [CLIENTE|BARBEIRO]\n");
	}
	
	return 0;
	
}
