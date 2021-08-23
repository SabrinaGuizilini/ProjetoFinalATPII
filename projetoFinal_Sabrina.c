#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constantes
#define MAX_VETOR 500000L
#define BILHAO 1000000000L
#define DIF_MIN 0.0001

/* Função que faz a busca sequencial - se não estiver ordenado, percorre o vetor do início ao fim para encontrar 
   o valor procurado, se encontrar, o conteúdo de vet[i] é atribuído para val, que foi passada por referência
   e o retorno é o indíce atual, senão, val tem o valor 0.0 e o retorno é -1. Se o vetor estiver ordenado, 
   a única diferença é que a busca é interrompida se chegou em um elemento que é maior que o procurado */ 
long int buscaSeq(double vet[], double *val, double num, long int n, int ord){
	long int i;
	double dif;
	
	if(ord==0){
		for(i=0; i<n; i++){
		dif= num - vet[i]; //É calculada a diferença entre o valor buscado e o conteúdo atual do vetor
		if(dif<0) dif= dif*(-1); //Se essa diferença for negativa, é multiplicada por -1 para ficar positiva
		if(dif< DIF_MIN){ //O valor é considerado encontrado se essa diferença for menor que DIF_MIN (0.0001)
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
	 
	//O valor não foi encontrado
	*val= 0.0;
	return -1;
}

/* Função que faz a busca binária - recebe os dois extremos do vetor, verifica se o valor procurado está
   em algum desses extremos, se não estiver, calcula o meio do vetor e começa a busca binária. Se o valor 
   for encontrado, val recebe o conteúdo do vetor na posição atual e o retorno é o indíce atual, senão, val 
   tem o valor 0.0 e o retorno é -1 */
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
	
	meio = (i + j) / 2; //Calcula o meio do vetor (divisão de inteiros)
	dif= num - vet[meio];
	if(dif<0) dif= dif*(-1);
	
	//Busca binária
	while(i<j && dif > DIF_MIN){
		if(num < vet[meio])
			j = meio-1;
		else
			i = meio+1;
		meio = (i + j) / 2; //Nova metade é calculada a cada iteração
		dif= num - vet[meio];
		if(dif<0) dif= dif*(-1);
	}
	
	if (dif< DIF_MIN){ //O valor foi encontrado
		*val= vet[meio];
		return meio;
	}
	else{ //O valor não foi encontrado
		*val= 0.0;
		return -1;
	}
}

//Função que ordena o vetor por Insertion sort
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

//Função que ordena o vetor por Shell sort
void shell(double vet[], long int n){
	long int i, j, k=1, l;
	double val;
	
	while(k < n/2)
    	k = 3*k + 1; //Passo inicial
    while(k!=1){
    	k = k/3; //O passo é diminuído a cada iteração
    	for(l=0; l<k; l++){
    		//Cada vetor é ordenado utilizando o Insertion sort adaptado p/ o passo k
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

//Separa os elementos em duas partições
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
    return j; //Retorna a atual posição do pivô
}

//Função que ordena o vetor por Quicksort
void quicksort(double vet[], long int lo, long int hi){
   if(lo < hi){                   
      long int j = separa (vet, lo, hi); 
	  //Faz a chamada recursiva para as duas metades	   
      quicksort(vet, lo, j-1);      
      quicksort(vet, j+1, hi);      
   }
}

/* Função que lê um valor do arquivo de busca, chama a função da busca sequencial para procurar esse valor,
   armazena o indíce retornado e imprime no arquivo de sáida o indíce, o valor encontrado e o valor procurado */
void leEscreveSeq(FILE *arq1, FILE *arq2, double vet[], long int n, int ord){
	double val, num;
	long int indice;
	
	while(!feof(arq1)) //Repete até chegar ao final do arquivo
	{
		fscanf(arq1, "%lf\n", &num);
		indice= buscaSeq(vet, &val, num, n, ord);
		fprintf(arq2, "%li %lf %lf\n", indice, val, num);
	}
}

/* Função que lê um valor do arquivo de busca, chama a função da busca binária para procurar esse valor,
   armazena o indíce retornado e imprime no arquivo de sáida o indíce, o valor encontrado e o valor procurado */
void leEscreveBin(FILE *arq1, FILE *arq2, double vet[], long int n){
	double val, num;
	long int indice;
	
	while(!feof(arq1)) //Repete até chegar ao final do arquivo
	{
		fscanf(arq1, "%lf\n", &num);
		indice= buscaBin(vet, &val, num, 0, n-1);
		fprintf(arq2, "%li %lf %lf\n", indice, val, num);
	}
}

//Função principal
int main(){
	FILE *arq1, *arq2; 
	struct timespec inicio, fim1, fim2;
	int op;
	long int n=0;
	double tempB, tempO, *vet= (double *)malloc(MAX_VETOR*sizeof(double)); //Aloca espaço do tamanho máximo que o vetor pode ter
	printf("Lendo arquivo...");
	arq1= fopen("vetor.dat", "r"); //Abre o arquivo vetor.dat p/ leitura
	while(!feof(arq1))
	{
		//Lê e guarda os números do arquivo no vetor
		fscanf(arq1, "%lf\n", &vet[n]);
		n++; //Incrementa a variável que conta a qtd de elementos
	}
	fclose(arq1); //Fecha o arquivo
	if(n!=MAX_VETOR) //Se a qtd de elementos for diferente do tamanho máximo que o vetor pode ter
		vet= (double *)realloc(vet, n*sizeof(double)); //Muda o tamanho do vetor para essa qtd

	//Menu para exibir as opções de ordenação e busca e ler a opção desejada
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
	arq2= fopen("resultado.dat", "w"); //Cria o arquivo de saída resultado.dat
	
	/* De acordo com a opção escolhida, é chamada uma das funções que lê do arquivo de busca, que chama a função da busca em si e 
	que imprime no arquivo de saída, e se for o caso, também é chamada antes, uma das funções que ordena o vetor. Além disso, é 
	utilizada a função clock_gettime para se ter o tempo de início e de término das funções */
	switch(op)
	{
		case 1:
			clock_gettime(CLOCK_REALTIME, &inicio);
			leEscreveSeq(arq1, arq2, vet, n, 0);
			clock_gettime(CLOCK_REALTIME, &fim1);
			tempO = 0.0; //Nesse caso o tempo de ordenação é zero
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
	
	//Se a opção escolhida for diferente da primeira, se calcula além do tempo de busca, o tempo de ordenação também
	if(op!=1){
		/* O cálculo é feito subtraindo o tempo de início do tempo de término das funções e somando-se os campos de
		   segundo e nanossegundo da struct, porém os nanossegundos são transformados em segundos também, por meio 
		   da divisão por um bilhão */
		tempO = (fim1.tv_sec - inicio.tv_sec)+(double)(fim1.tv_nsec - inicio.tv_nsec)/(double)BILHAO;
		tempB = (fim2.tv_sec - fim1.tv_sec)+(double)(fim2.tv_nsec - fim1.tv_nsec)/(double)BILHAO;
	}
	
	//Exibe na tela os tempos, em segundos, de ordenação e busca já calculados e também o tempo total
	printf("Tempo de ordenacao: %lf s\nTempo de busca: %lf s\nTempo total: %lf s\n", tempO, tempB, (tempO+tempB));
	
	return 0;
}
