#include <stdio.h>
#include <stdlib.h>


struct pessoa {
    char nome[30];
    long long int cpf; //CHAVE PRIMÁRIA
    int rg;
    int nCarros;
    
}pessoa;

struct carros{
    char placa[9];
    char chassis[30];
    char modeloMarca[200];
    long long int idProp;
    int renavam; //CHAVE PRIMARIA


}carros;


FILE *criaArquivo (char nome[17]){
    FILE *ponteiro;
    ponteiro=fopen(nome,"rb");

    if(ponteiro == NULL){
        ponteiro = fopen(nome,"wb");
        return (ponteiro);
    }
    else{
        printf ("Arquivo Existe!");
        
    }
fclose(ponteiro);
    
    }


void leituraVeiculos(int prop){
    FILE *ptr;
    struct carros leituraC;
    ptr = fopen("bancoCarros.bin","rb");

while(1){
fread(&leituraC,sizeof(leituraC),1,ptr);
if(feof(ptr)) break;
 if(leituraC.idProp == prop){
            printf("Placa: %s  - Chassis: %s - Modelo/Marca: %s - Renavam: %d\n", leituraC.placa, leituraC.chassis,leituraC.modeloMarca,leituraC.renavam);
        }
}

fclose(ptr);
}

void leituraProp(){
    FILE *ptr;
    struct pessoa leitura;
    ptr = fopen("bancoPessoas.bin","rb");


while(1){
    fread(&leitura,sizeof(leitura),1,ptr);
    if(feof(ptr)) break;
    printf("CPF propriet: %lld  - Nome: %s\n Veículos Cadastrados:\n", leitura.cpf, leitura.nome);
    leituraVeiculos(leitura.cpf);
}  
fclose(ptr);
}


 int compararCpf(const void *x, const void *y){
    long long int a = ((struct pessoa *)x)->cpf;
    long long int b = ((struct pessoa *)y)->cpf;
    return (a-b);
}

int compararRenavam(const void *x, const void *y){
    long long int a = ((struct carros *)x)->renavam;
    long long int b = ((struct carros *)y)->renavam;
    return (a-b);
}


int cntLidos =0;

void ordenaProp(){
    FILE *ptr;
    struct pessoa leitura;
    struct pessoa *lidos;
    lidos = (struct pessoa*) malloc(sizeof(pessoa));
    cntLidos=0;
    ptr = fopen("bancoPessoas.bin","rb");
while(1){
    
    lidos =  realloc(lidos,(sizeof(lidos)*100));
    fread(&leitura,sizeof(leitura),1,ptr);
    if(feof(ptr)) break;
    lidos[cntLidos] = leitura;
    cntLidos++;
}  

fclose(ptr);

qsort(lidos,cntLidos,sizeof(pessoa),compararCpf);

        remove("bancoPessoas.bin");
        struct pessoa regPessoa;
        FILE *ptreg;
        ptreg = fopen("bancoPessoas.bin","ab");
        fwrite(lidos,sizeof(pessoa),cntLidos, ptreg);
        fclose(ptreg);      
}

int cntLidosCarros =0;
void ordenaVeiculos(){
    FILE *ptr;
    struct carros leitura;
    struct carros *lidos;
    lidos = (struct carros*) malloc(sizeof(carros));
    cntLidosCarros=0;
    ptr = fopen("bancoCarros.bin","rb");
while(1){
    
    lidos =  realloc(lidos,(sizeof(lidos)*100));
    fread(&leitura,sizeof(leitura),1,ptr);
    if(feof(ptr)) break;
    lidos[cntLidosCarros] = leitura;
    cntLidosCarros++;
}  

fclose(ptr);

qsort(lidos,cntLidosCarros,sizeof(carros),compararRenavam);

        remove("bancoCarros.bin");
        struct carros regCarros;
        FILE *ptreg;
        ptreg = fopen("bancoCarros.bin","ab");
        fwrite(lidos,sizeof(carros),cntLidosCarros, ptreg);
        fclose(ptreg);      
}




int verifCpf(long long int cpf){
    FILE *ptr;
    int count =0;
    struct pessoa leitura;
    ptr = fopen("bancoPessoas.bin","rb");


while(1){
    fread(&leitura,sizeof(leitura),1,ptr);
    if (leitura.cpf == cpf) count++;
    if(feof(ptr)) break;
    
}  
fclose(ptr);
}
int verifRg(int rg){
    FILE *ptr;
    int count =0;
    struct pessoa leitura;
    ptr = fopen("bancoPessoas.bin","rb");


while(1){
    fread(&leitura,sizeof(leitura),1,ptr);
    if (leitura.rg == rg) count++;
    if(feof(ptr)) break;
    
}  
fclose(ptr);
}






int main(){
    printf("Aguarde, verificando a existencia do arquivo de pessoas\n");
    char nomeP[17] = "bancoPessoas.bin";
    FILE *criaArquivo (char nomeP[17]);
    if(criaArquivo(nomeP) != NULL)
        printf("Arquivo criado!\n\n");
    else 
        printf("Arquivo encontrado!\n\n");
        printf("Aguarde, verificando a existencia do arquivo de veiculos\n");
    char nomeV[17] = "bancoCarros.bin";
    FILE *criaArquivo (char nomeV[17]);
    if(criaArquivo(nomeV) != NULL)
        printf("Arquivo criado!\n\n\n");
    else 
        printf("Arquivo encontrado!\n\n\n");

   






    int opt = 0;

    while(opt !=5){
    printf("#################################################################################################################################\n");
    printf("Olá, seja bem vindo ao sistema de registro de carros e proprietários\n");
    printf("Escolha abaixo o que deseja fazer:\n");
    printf("[1] - Cadastrar proprietário\n[2] - Cadastrar Veículo\n[3] - Listar donos de veículos e seus veículos\n[5] - Sair do sistema.\n");
    printf("#################################################################################################################################\n\n");
    scanf("%d", &opt);
    

    if(opt == 1){

        struct pessoa regPessoa;
        FILE *ptreg;
        ptreg = fopen("bancoPessoas.bin","ab");
        printf("Que legal! Vamos cadastrar um novo proprietário de veículo.\n");
        printf("Digite o nome da pessoa:\n");
        scanf("%s",regPessoa.nome);
        printf("Digite o cpf\n");
        scanf("%lld", &regPessoa.cpf);
        
        printf("Digite o rg\n");
        scanf("%d", &regPessoa.rg);
        if(verifCpf(regPessoa.cpf) == 0 && verifRg(regPessoa.rg) == 0){
        regPessoa.nCarros = 0;

        fflush(stdin);
    
        fwrite(&regPessoa,sizeof(pessoa),1, ptreg);
        fclose(ptreg);
        printf("Pessoa registrada com sucesso!\n");
        }
        else{
            printf("OPS! CPF ou RG DUPLICADO!\n");
        }
        ordenaProp();
        
    }

    else if(opt == 2){

        struct carros regVeiculo;
        FILE *ptreg;
        ptreg = fopen("bancoCarros.bin","ab");
        printf("Que legal! Vamos cadastrar um novo veículo.\n");
        printf("Digite a placa do veículo:\n");
        scanf("%s",regVeiculo.placa);
        printf("Digite o chassis\n");
        scanf("%s", regVeiculo.chassis);
        printf("Digite o Modelo/Marca\n");
        scanf("%s", regVeiculo.modeloMarca);
        printf("Digite o cpf do proprietário\n");
        scanf("%lld", &regVeiculo.idProp);
        printf("Digite o renavam\n");
        scanf("%d", &regVeiculo.renavam);
        

        fflush(stdin);
    
        fwrite(&regVeiculo,sizeof(carros),1, ptreg);
        fclose(ptreg);
        printf("Veiculo registrado com sucesso!\n");
        
        ordenaVeiculos();
       
    }
    else if(opt == 3){

        leituraProp();
        
    }
    }
    printf("OBRIGADO POR USAR O SISTEMA!\n");

    return 0;
}