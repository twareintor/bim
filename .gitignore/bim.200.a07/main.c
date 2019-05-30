/**
* The purpose of the program is to develop and test a function that outputs a grayscale bitmap image in a file
* (e.g. "out.bmp") which pixel colors (gray scale) are read from an input text file (e.g. "level.txt") which 
* usually represent an ASCII art text. 
* It gets its dimensions from the number of lines of the input file (bitmap height) and the longest line of the
* input text (bitmap width) which buffer is processed too in order all the lines to be the same lenght, by padding
* them with spaces.
* For debug, also outputs the resulting in a text file (e.g. "out.txt") when an option is enabled.
*/

#include <stdio.h>
#include <stdlib.h>
#include "data.c"
#include "bimg.c"

/** */
extern int loadDataFrom(char* filename, char* data, size_t dataSize, unsigned int* metrics);

/** */
extern int padLinesOf(unsigned char* data, size_t size, unsigned int* metrics);

/** */
extern int drawbmpg(char* filename, unsigned char* data, int w, int h);

/** if testing or application running */
#define TESTING

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#ifdef TESTING
#define WIDTH (1024+1)		
#define HEIGHT (1024)
#define DATASIZE (1024*2014*sizeof(unsigned char))
#endif

int main(int argc, char *argv[]) 
{
	size_t size = DATASIZE;
	/* data must be large enough to hold the whole content of the file or will be truncated */
 	unsigned char* data = (unsigned char*)malloc(size); /* ... just to be sure... */
 	memset(data, 0, size);
 	int met[2]; /* stands for "metrics" 0 = width, 1 = height */
	loadDataFrom("level.txt", data, size, met);
	printf("%d, %d\n", met[0], met[1]);\
	printf("width x height = %dx%d=%d < %d\n", met[0], met[1], met[0]*met[1], size);
	/* make the data nice */
	padLinesOf(data, size, met);
	printf("ret = %d\n", 10);
	/* modifyData(data, DIMS*1); */
	if (0==drawbmpg("out.bmp", data, met[0], met[1])) printf("Program successfuly!\n");
	free(data);
	return 0;
}
