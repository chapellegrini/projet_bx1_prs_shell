#include <stdio.h>
#include <stdlib.h>


typedef struct rem {
	int filedef;
	int pid;
	char* filename
};

void remote (int argc, char* argv[]) {
	rem *tab = NULL;
	int tabSize = 0;
	int tabAllocated = 0;
	int nbArg;
	int i;

	if (strcmp(argv[2], "add") == 0) {
		//fordesarguments
			if(tabAllocated == tabSize){
				if((tab = realloc(*tab, tabSize == 0 ? 10 : sizeof(rem) * tabSize * 2)) == NULL)
					exit(-1);
				tabSize *= 2;
				tabAllocated++;
			}
			tab[tabAllocated - 1].pid = fork();
			if(tab[tabAllocated - 1].pid == 0){
				//TODO IAMTHESON
			} 
			else{
				//TODO FILEDEF DU PERE

				for(i = 0; argv[nbArg][i] != 0; i++);
				if(tab[tabAllocated - 1].filename = malloc(i * sizeof(char)))
					exit(-1)
				for(i--; i >= 0; i--)
					tab[tabAllocated - 1].filename[i] = argv[nbArg][i];
			}
	}
}