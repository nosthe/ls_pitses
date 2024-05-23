
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

int ARITHMOS_PELATWN=5;

void* order(void* arg){
    int orderID=*(int*)arg;
    printf("pareigghla.. order: %d\n",orderID);
    // edw 4 whiles me mutex aoy conditions? gia kathe stadio
    
}

int main(int argc, char* argv[]){
    
    
    pthread_t pelatesThreads[ARITHMOS_PELATWN];

    //anoigei threads pelates pernaei to id sthn order
    for(int i=1; i <= ARITHMOS_PELATWN; i++){

        int* a = malloc(sizeof(int));
        *a = i;

        if(pthread_create(&pelatesThreads[i],NULL,&order,a)){
            perror("den anoikse to thread ");
        }
    }

    //joins
    for (int i = 1; i <=ARITHMOS_PELATWN; i++) {
        if (pthread_join(pelatesThreads[i], NULL) != 0) {
            perror("den joinare to thread");
        }
    }

}
