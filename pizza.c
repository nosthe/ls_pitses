
//header me oles tis metavlites poy leei

//create client threads
// ena ews N aoy, join sto telos klp checks gia errors aoy

//mutex 
// thlefwnhtes,mageires,fournoi,deliverades
//        ola me metavlhtes se mutex kai cond px.mageires=50
// me whiles to ena stadio meta to allo
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "pizza.h"

pthread_mutex_t mutexTel;
pthread_cond_t condTel;

void* order(void* arg){

    int orderID=*(int*)arg;
    
    
    pthread_mutex_lock(&mutexTel);

    while(thlefwnhtes<1){
        printf("perimenw na vrw thlefwniti.. nima: %d\n",orderID);
        pthread_cond_wait(&condTel,&mutexTel);
        //vazei to thread na perimenei na akoysei signal kai eleytherwnei to mutex
        //otan akoysei signal apto broadcast, to pairnei kapoio thread poy perimene,ksanakleidwnei kai proxwraei
    }
	
    //apasxolei enan thlefwnhth( an ftasei edw to mutex einai locked hdh)
	thlefwnhtes--;
    pthread_mutex_unlock(&mutexTel);
	

    // edw arxizei h paraggelia
	printf("parhggeila order: %d\n",orderID);
	
	
	
	sleep(1); // foo() paraggelias
	
	
	//edw exei teleiwsei h paraggelia. apeleytherwnei ton thlefwnhth kai stelnei shma se ola ta threads na psaksoyn thlefwnhth
	pthread_mutex_lock(&mutexTel);
	thlefwnhtes++;
	pthread_mutex_unlock(&mutexTel);
	pthread_cond_broadcast(&condTel);//*

	free(arg);
	

}


int main(int argc, char* argv[]){
    
    
    if(argc!=3 ){
        printf("Den exeis dwsei swsta orismata, termatizw");
        exit(1);
    }

    Ncust=atoi(argv[1]);
    seed=atoi(argv[2]);

    pthread_t pelatesThreads[Ncust];

    pthread_mutex_init(&mutexTel,NULL);
    pthread_cond_init(&condTel,NULL);
    
    

    //anoigei threads pelates pernaei to id sthn order
    for(int i=1; i <= Ncust; i++){
		
        int* a = malloc(sizeof(int));
        *a = i;
	
        if(pthread_create(&pelatesThreads[i],NULL,&order,a)){
            perror("den anoikse to thread ");
        }
        
    }

    //joins
    for (int i = 1; i <=Ncust; i++) {
        if (pthread_join(pelatesThreads[i], NULL) != 0) {
            perror("den joinare to thread");
        }
    }

    pthread_mutex_destroy(&mutexTel);
    pthread_cond_destroy(&condTel);

}
