#include <stdio.h>
#include <string.h>

struct notas_aluno{
	int matricula;
	int aprovacao;
	float nota[3];
	float media;
};
struct lista_nomes{
	int matricula;
	char nome[51];
};

float media(struct notas_aluno a){
    return (a.nota[0] + a.nota[1] + a.nota[2]) / 3;
}

int main() {
	int i = 0;
	float todas_medias;
	struct notas_aluno notas[31];
	struct lista_nomes nomes[31];
    FILE *arquivo1, *arquivo2, *aprovado, *reprovado;
    arquivo1 = fopen("nomes_alunos.txt", "r");
    if (arquivo1 == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
	arquivo2 = fopen("notas_alunos.txt", "r");
	if (arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    aprovado = fopen("aprovado.txt", "a");
    if (aprovado == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    reprovado = fopen("reprovado.txt", "a");
    if (reprovado == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    while (fscanf(arquivo2, "%d %f %f %f", &(notas[i].matricula), &(notas[i].nota[0]), &(notas[i].nota[1]), &(notas[i].nota[2])) != EOF) {
		notas[i].media = media(notas[i]);
		if (notas[i].media >= 6){
			notas[i].aprovacao = 0;
		} else {
			notas[i].aprovacao = 1;
		}
		i++;
	}
	i = 0;
    while (fscanf(arquivo1, "%d %[^\n]s", &nomes[i].matricula, nomes[i].nome) != EOF){
    	if (notas[i].aprovacao == 0){
    		fprintf(aprovado, "%d %s %.3f \n", notas[i].matricula, nomes[i].nome, notas[i].media);
		} else {
			fprintf(reprovado, "%d %s %.3f \n", notas[i].matricula, nomes[i].nome, notas[i].media);
		}
		todas_medias += notas[i].media;
		i++;
	}
	
	printf("Media da turma: %.3f", todas_medias/i+1);
    fclose(arquivo1);
    fclose(arquivo2);
    fclose(aprovado);
    fclose(reprovado);

    return 0;
}
