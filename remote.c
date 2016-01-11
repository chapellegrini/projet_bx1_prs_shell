#include <stdio.h>
#include <stdlib.h>


typedef struct rem {
	int filedef;
	pid_t pid;
	char* filename;
};

void remote (int argc, char* argv[]) {
	rem *tab = NULL;
	int tabSize = 0;
	int tabAllocated = 0;
	int nbArg;
	int i;

	if (strcmp(argv[2], "add") == 0) {
			if(tabAllocated == tabSize){
				if(tabAllocated == 0)
					tabAllocated = 5;
				tabAllocated *= 2;
				if((tab = realloc(*tab, sizeof(rem) * tabAllocated) == NULL)
					exit(-1);
			}
			tabSize++;

			//double fork pour affiche et attendre les réponses dans notre shell

			int tube1[2];
			pipe(tube1);
			tab[tabAllocated - 1].pid = fork();
			
			if(tab[tabAllocated - 1].pid == 0){
				int tube2[2];
				pipe(tube2);
				//tube2  = ecoute
				pid_t pid_use = fork();

				if (pid_use == 0) {
					dup2(tube1[0], 0);
					dup2(tube2[1], 1);
					close(tube1[0]);
					close(tube1[1]);
					close(tube2[0]);
					close(tube2[1]);

					//chemin de notre sshShell
					char *use_path = getcwd(NULL, 0);
					strcat(use_path, "/sshShell");

					//Shell sans ssh
					if (strcmp(/*notre machine*/, "localhost") == 0) {
						execlp(use_path, "sshShell", NULL);
						perror("execlp Shell distant");
						exit(EXIT_FAILURE);
					}

					//Shell en ssh
					else {
						execlp("ssh", "ssh", /*nom machine*/);
						perror("execlp ssh");
						exit(EXIT_FAILURE);
					}
				}

				else {
					dup2(tube2[0], 0);
					close(tube1[0]);
					close(tube1[1]);
					close(tube2[0]);
					close(tube2[1]);
				}

				setvbuf(stdout, NULL, _IOLBF, 0); 
			} 

			else {

				for(i = 0; argv[nbArg][i] != 0; i++);
				if((tab[tabAllocated - 1].filename = malloc(i * sizeof(char))) < 0)
					exit(-1);
				for(i--; i >= 0; i--)
					tab[tabAllocated - 1].filename[i] = argv[nbArg][i];
			}
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[2], "list") == 0) {
		(for i = 0; i <= tabSize; i++)
			printf("%s", tab.filename[i]);
	}

	if (strcmp(argv[2], "remove") == 0) {

		tabSize = 0;
		free(tab);
		return EXIT_SUCCESS;
	}

	if (strcmp(argv[2], "all") == 0) {
		//execute sur toutes les machines en ssh
	}
}