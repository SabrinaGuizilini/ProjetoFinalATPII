#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constantes
#define MAX_VETOR 500000L
#define BILHAO 1000000000L
#define DIF_MIN 0.0001

/* Fun��o que faz a busca sequencial - se n�o estiver ordenado, percorre o vetor do in�cio ao fim para encontrar 
   o valor procurado, se encontrar, o conte�do de vet[i] � atribu�do para val, que foi passada por refer�ncia
   e o retorno � o ind�ce atual, sen�o, val tem o valor 0.0 e o retorno � -1. Se o vetor estiver ordenado, 
   a �nica diferen�a � que a busca � interrompida se chegou em um elemento que � maior que o procurado */ 
long int buscaSeq(double vet[], double *val, double num, long int n, int ord){
	long int i;
	double dif;
	
	if(ord==0){
		for(i=0; i<n; i++){
		dif= num - vet[i]; //� calculada a diferen�a entre o valor buscado e o conte�do atual do vetor
		if(dif<0) dif= dif*(-1); //Se essa diferen�a for negativa, � multiplicada por -1 para ficar positiva
		if(dif< DIF_MIN){ //O valor � considerado encontrado se essa diferen�a for menor que DIF_MIN (0.0001)
			*val= vet[i];
			return i;
		 }
	   }
   	 }
   	 
	else{
		for(i=0; i<n; i++){
		dif= num - vet[i]; 
		if(dif<0) dif= dif*(-1);
		if(dif< DIF_MIN){ 
			*val= vet[i];
			return i;
		}
		else if(num < vet[i]){
			*val= 0.0;
			return -1;
		 }
	   }
	 }
	 
	//O valor n�o foi encontrado
	*val= 0.0;
	return -1;
}

/* Fun��o que faz a busca bin�ria - recebe os dois extremos do vetor, verifica se o valor procurado est�
   em algum desses extremos, se n�o estiver, calcula o meio do vetor e come�a a busca bin�ria. Se o valor 
   for encontrado, val recebe o conte�do do vetor na posi��o atual e o retorno � o ind�ce atual, sen�o, val 
   tem o valor 0.0 e o retorno � -1 */
long int buscaBin(double vet[], double *val, double num, int i, long int j){
	long int meio;
	double dif;
	
	//Confere nos extremos
	dif= num - vet[i];
	if(dif<0) dif= dif*(-1);
	if(dif< DIF_MIN){
		*val= vet[i];
		return i; 
	}
	
	dif= num - vet[j];
	if(dif<0) dif= dif*(-1);
	if(dif< DIF_MIN){
		*val= vet[j];
		return j;
	}	 
	
	meio = (i + j) / 2; //Calcula o meio do vetor (divis�o de inteiros)
	dif= num - vet[meio];
	if(dif<0) dif= dif*(-1);
	
	//Busca bin�ria
	while(i<j && dif > DIF_MIN){
		if(num < vet[meio])
			j = meio-1;
		else
			i = meio+1;
		meio = (i + j) / 2; //Nova metade � calculada a cada itera��o
		dif= num - vet[meio];
		if(dif<0) dif= dif*(-1);
	}
	
	if (dif< DIF_MIN){ //O valor foi encontrado
		*val= vet[meio];
		return meio;
	}
	else{ //O valor n�o foi encontrado
		*val= 0.0;
		return -1;
	}
}

//Fun��o que ordena o vetor por Insertion sort
void insertion(double vet[], long int n){
    long int i, j;
    double val;
    
	for (i=1; i<n; i++) 
	{ 
		val = vet[i];
		j = i-1;
		
		while (j >= 0 && vet[j] > val) { 
            vet[j+1] = vet[j]; //Deslocamento para a direita
            j--; 
        } 
        vet[j+1] = val; //Insere o elemento na parte ordenada
	}
}

//Fun��o que ordena o vetor por Shell sort
void shell(double vet[], long int n){
	long int i, j, k=1, l;
	double val;
	
	while(k < n/2)
    	k = 3*k + 1; //Passo inicial
    while(k!=1){
    	k = k/3; //O passo � diminu�do a cada itera��o
    	for(l=0; l<k; l++){
    		//Cada vetor � ordenado utilizando o Insertion sort adaptado p/ o passo k
    		for(i=l+k; i<n; i=i+k){
    			val = vet[i];
    			j = i;
    			while(j-k>=0 && vet[j-k] > val){
    				vet[j] = vet[j-k];
    				j=j-k;
				}
				vet[j] = val;
			}
		}
	}
}

//Separa os elementos em duas parti��es
long int separa(double vet[], long int lo, long int hi){
    double pivo = vet[hi], t; 
    long int k, j = lo;
    
    for(k=lo; k<hi; k++){
        if(vet[k] <= pivo){
        	//Faz a troca
            t = vet[j];
            vet[j] = vet[k];
            vet[k] = t;
            j++; 
        } 
    }
    //Faz a troca
    t = vet[j];
    vet[j] = vet[hi];
    vet[hi] = t;
    return j; //Retorna a atual posi��o do piv�
}

//Fun��o que ordena o vetor por Quicksort
void quicksort(double vet[], long int lo, long int hi){
   if(lo < hi){                   
      long int j = separa (vet, lo, hi); 
	  //Faz a chamada recursiva para as duas metades	   
      quicksort(vet, lo, j-1);      
      quicksort(vet, j+1, hi);      
   }
}

/* Fun��o que l� um valor do arquivo de busca, chama a fun��o da busca sequencial para procurar esse valor,
   armazena o ind�ce retornado e imprime no arquivo de s�ida o ind�ce, o valor encontrado e o valor procurado */
void leEscreveSeq(FILE *arq1, FILE *arq2, double vet[], long int n, int ord){
	double val, num;
	long int indice;
	
	while(!feof(arq1)) //Repete at� chegar ao final do arquivo
	{
		fscanf(arq1, "%lf\n", &num);
		indice= buscaSeq(vet, &val, num, n, ord);
		fprintf(arq2, "%li %lf %lf\n", indice, val, num);
	}
}

/* Fun��o que l� um valor do arquivo de busca, chama a fun��o da busca bin�ria para procurar esse valor,
   armazena o ind�ce retornado e imprime no arquivo de s�ida o ind�ce, o valor encontrado e o valor procurado */
void leEscreveBin(FILE *arq1, FILE *arq2, double vet[], long int n){
	double val, num;
	long int indice;
	
	while(!feof(arq1)) //Repete at� chegar ao final do arquivo
	{
		fscanf(arq1, "%lf\n", &num);
		indice= buscaBin(vet, &val, num, 0, n-1);
		fprintf(arq2, "%li %lf %lf\n", indice, val, num);
	}
}

//Fun��o principal
int main(){
	FILE *arq1, *arq2; 
	struct timespec inicio, fim1, fim2;
	int op;
	long int n=0;
	double tempB, tempO, *vet= (double *)malloc(MAX_VETOR*sizeof(double)); //Aloca espa�o do tamanho m�ximo que o vetor pode ter
	printf("Lendo arquivo...");
	arq1= fopen("vetor.dat", "r"); //Abre o arquivo vetor.dat p/ leitura
	while(!feof(arq1))
	{
		//L� e guarda os n�meros do arquivo no vetor
		fscanf(arq1, "%lf\n", &vet[n]);
		n++; //Incrementa a vari�vel que conta a qtd de elementos
	}
	fclose(arq1); //Fecha o arquivo
	if(n!=MAX_VETOR) //Se a qtd de elementos for diferente do tamanho m�ximo que o vetor pode ter
		vet= (double *)realloc(vet, n*sizeof(double)); //Muda o tamanho do vetor para essa qtd

	//Menu para exibir as op��es de ordena��o e busca e ler a op��o desejada
	do{
	printf("\n\nMENU");
	printf("\n\n1- Busca sem ordenacao");
	printf("\n2- Ordenacao por insertion sort e busca sequencial\n3- Ordenacao por shell sort e busca sequencial");
	printf("\n4- Ordenacao por quicksort e busca sequencial\n5- Ordenacao por insertion sort e busca binaria ");
	printf("\n6- Ordenacao por shell sort e busca binaria\n7- Ordenacao por quicksort e busca binaria");
	printf("\n\nDigite a opcao desejada: ");
	scanf("%d", &op);
	if(op<1 || op>7)
		printf("\nOpcao invalida!");
	}while(op<1 || op>7);
	
	arq1= fopen("busca.dat", "r"); //Abre o arquivo busca.dat p/ leitura
	arq2= fopen("resultado.dat", "w"); //Cria o arquivo de sa�da resultado.dat
	
	/* De acordo com a op��o escolhida, � chamada uma das fun��es que l� do arquivo de busca, que chama a fun��o da busca em si e 
	que imprime no arquivo de sa�da, e se for o caso, tamb�m � chamada antes, uma das fun��es que ordena o vetor. Al�m disso, � 
	utilizada a fun��o clock_gettime para se ter o tempo de in�cio e de t�rmino das fun��es */
	switch(op)
	{
		case 1:
			clock_gettime(CLOCK_REALTIME, &inicio);
			leEscreveSeq(arq1, arq2, vet, n, 0);
			clock_gettime(CLOCK_REALTIME, &fim1);
			tempO = 0.0; //Nesse caso o tempo de ordena��o � zero
			tempB = (fim1.tv_sec - inicio.tv_sec)+(double)(fim1.tv_nsec - inicio.tv_nsec)/(double)BILHAO; //Calcula tempo de busca p/ esse caso
			break;
			
		case 2:
			clock_gettime(CLOCK_REALTIME, &inicio);
			insertion(vet, n);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveSeq(arq1, arq2, vet, n, 1);
			clock_gettime(CLOCK_REALTIME, &fim2);
			break;
			
		case 3:
			clock_gettime(CLOCK_REALTIME, &inicio);
			shell(vet, n);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveSeq(arq1, arq2, vet, n, 1);
			clock_gettime(CLOCK_REALTIME, &fim2);
			break;
			
		case 4: 
			clock_gettime(CLOCK_REALTIME, &inicio);
			quicksort(vet, 0, n-1);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveSeq(arq1, arq2, vet, n, 1);
			clock_gettime(CLOCK_REALTIME, &fim2);
			break;
			
		case 5: 
			clock_gettime(CLOCK_REALTIME, &inicio);
			insertion(vet, n);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveBin(arq1, arq2, vet, n);
			clock_gettime(CLOCK_REALTIME, &fim2);
			break;
			
		case 6:
			clock_gettime(CLOCK_REALTIME, &inicio);
			shell(vet, n);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveBin(arq1, arq2, vet, n);
			clock_gettime(CLOCK_REALTIME, &fim2);
			break;
			
		default:
			clock_gettime(CLOCK_REALTIME, &inicio);
			quicksort(vet, 0, n-1);
			clock_gettime(CLOCK_REALTIME, &fim1);
			leEscreveBin(arq1, arq2, vet, n);
			clock_gettime(CLOCK_REALTIME, &fim2);	 	
	}
	
	//Fechamento dos arquivos
	fclose(arq1);
	fclose(arq2);
	free(vet); //Libera o vetor
	
	//Se a op��o escolhida for diferente da primeira, se calcula al�m do tempo de busca, o tempo de ordena��o tamb�m
	if(op!=1){
		/* O c�lculo � feito subtraindo o tempo de in�cio do tempo de t�rmino das fun��es e somando-se os campos de
		   segundo e nanossegundo da struct, por�m os nanossegundos s�o transformados em segundos tamb�m, por meio 
		   da divis�o por um bilh�o */
		tempO = (fim1.tv_sec - inicio.tv_sec)+(double)(fim1.tv_nsec - inicio.tv_nsec)/(double)BILHAO;
		tempB = (fim2.tv_sec - fim1.tv_sec)+(double)(fim2.tv_nsec - fim1.tv_nsec)/(double)BILHAO;
	}
	
	//Exibe na tela os tempos, em segundos, de ordena��o e busca j� calculados e tamb�m o tempo total
	printf("Tempo de ordenacao: %lf s\nTempo de busca: %lf s\nTempo total: %lf s\n", tempO, tempB, (tempO+tempB));
	
	return 0;
}
