#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define CHAIRS  5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t sinalAcordaBarbeiro = PTHREAD_COND_INITIALIZER;
pthread_cond_t chamaCliente = PTHREAD_COND_INITIALIZER;

int costumers=0;
int ocupado=0;


int temCadeiraVazia(){
	if (costumers<CHAIRS){
		return 1;
	}
	return 0;
}

void *barbeiro(void *args){
	while(1){
		
		pthread_mutex_lock(&mutex);
		ocupado=0;
		if(costumers==0){
			printf("\nB:Vou dormir,nao tem cliente!Clientes:%d\n",costumers);
			pthread_cond_wait(&sinalAcordaBarbeiro,&mutex);

		}

		printf("\nB:Chamei um cliente.Clientes:%d\n",costumers);
		costumers-=1;
		ocupado=1;
		

		pthread_cond_signal(&chamaCliente);


		pthread_mutex_unlock(&mutex);

		printf("\nB:Estou cortando o cabelo de um cliente.Clientes:%d\n",costumers);	
	}
}

void *cliente(void *args){
	while(1){
		pthread_mutex_lock(&mutex);
		if(temCadeiraVazia){
			costumers+=1;
			printf("\nC:Chegou um consumidor.Clientes:%d\n",costumers);
			if(costumers==1){
				pthread_cond_signal(&sinalAcordaBarbeiro);
			}
			
			if(ocupado==1){
				pthread_cond_wait(&chamaCliente,&mutex);
				
			}
			
			pthread_mutex_unlock(&mutex);
			printf("\nC:Tendo  o cabelo cortado\n");
			sleep(10);
			
				
					
				

		}
		else{
			pthread_mutex_unlock(&mutex);
		}
	}


}


int main(){
	pthread_t barbeiroT;
	pthread_t consumidor;

	pthread_create(&barbeiroT,NULL,&barbeiro,NULL);
	pthread_create(&consumidor,NULL,&cliente,NULL);

	do{

	}while(1);
}