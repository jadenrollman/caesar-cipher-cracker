// simple program to crack a ceasar cipher

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 2048

// function prototypes
void crack(int, int, int);
void help(void);

int main(int argc, char *argv[]) {
	char *ifile = NULL;
	char *ofile = NULL;
	int option = 0;
	int offset = 0;
	int ifd = STDIN_FILENO;
	int ofd = STDOUT_FILENO;

	while ((option = getopt(argc, argv, "i:o:h")) != -1) {
		switch (option) {
			case 'i':
				ifile = optarg;
				break;
			
			case 'o':
				ofile = optarg;
				break;

			case 'h':
				help();
				exit(EXIT_SUCCESS);
				break;

			default:
				help();
				exit(EXIT_SUCCESS);
				break;
		}
	}

	if (ifile != NULL) {
		ifd = open(ifile, O_RDONLY);

		if (ifd < 0) {
			perror("failed to read input file!\n");
			exit(EXIT_FAILURE);
		}
	}

	if (ofile != NULL) {
		ofd = open(ofile, O_CREAT | O_TRUNC | O_WRONLY, 0664);

		if (ofd < 0) {
			perror("failed to open output file!\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Enter an Offset: ");
	scanf("%d", &offset);

	crack(ifd, ofd, offset);

	if (ifile) close(ifd);
	if (ofile) close(ofd);

	return EXIT_SUCCESS;
}


// attempt to decrypt the file
void crack(int ifd, int ofd, int offset) {
	char buffer[BUFSIZE] = {0};
	ssize_t nbytes = 0;

	while ((nbytes = read(ifd, buffer, BUFSIZE)) > 0) {
		for (ssize_t i = 0; i < nbytes; ++i) buffer[i] += offset;

		write(ofd, buffer, nbytes);
	}
}



// help message
void help(void) {
	printf("Usage: i:o:h\n");
	printf("-i [FILE]\n");
	printf("-o [FILE]\n");
	printf("-h (show this help message)\n");
}
