#include <bits/stdc++.h>

using namespace std;

int main(){
	int n_levels;

	FILE *answer = fopen("answer.dat", "wb");

	printf("Digite o número de levels: ");
	scanf("%d", &n_levels);

	fwrite(&n_levels, sizeof(int), 1, answer);

	for(int level=1; level<=n_levels; level++){
		int n_frames;

		printf("Digite o número de frames do level %d: ", level);
		scanf("%d", &n_frames);

		int level_answer[5][100];

		printf("Digite as %d respostas da entrada\n", n_frames);
		for(int frame=0; frame<n_frames; frame++){
			scanf("%d", &level_answer[0][frame]);
		}

		printf("Digite as %d respostas da trilha principal\n", n_frames);
		for(int frame=0; frame<n_frames; frame++){
			scanf("%d", &level_answer[1][frame]);
		}

		printf("Digite as %d respostas da saída\n", n_frames);
		for(int frame=0; frame<n_frames; frame++){
			scanf("%d", &level_answer[2][frame]);
		}

		fwrite(&n_frames, sizeof(int), 1, answer);
		fwrite(level_answer, sizeof(int), 3 * n_frames, answer);
	}

	

	return 0;
}
