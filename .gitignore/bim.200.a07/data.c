

#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 	

#define OUTFILE_CHK 1

/** Function to get the raw data from a text file, usually for ASCII art and for character map representation.
*	This function loads a "dataSize" bytes from the file name "filename" with "data" as well.
* 	The function  also outputs the "dimensions" of the image based on the longest line in the input text as data
*   in the file (which is also used as text file)
*	In the "metrics" array will be stored the width (metrics[0]) and height (metrics[1]) of the image in columns
*	and lines respectively. The "metrics[]" will be undefined when the function fails!
*/

static int loadDataFrom(char* filename, char* data, size_t dataSize, unsigned int* metrics)
{
	FILE* pFile;
	pFile = fopen(filename, "rb");
	if(pFile)
	{
		/* obtain file size: */
		/*********** ************/
		fseek(pFile, 0, SEEK_END);
		long lSize;
		lSize = ftell(pFile);
		rewind(pFile);
		if(lSize>=dataSize)
		{
			lSize = dataSize;
			printf("Warning: file is bigger as buffer, data will be truncated!\n");
		}
		int result;
		result = fread(data, sizeof(unsigned char), lSize, pFile);
		data[lSize] = 0;
		if (result != lSize)
		{
			printf("Error reading file \"%s\"\n", filename);
		}
		else
		{
			printf("Success reading file \"%s\"\n", filename);
		}
		fclose(pFile);
		/* now get the metrics of the canvas: */
		if(metrics) /* only if the dimensions of the data were requested */
		{
			long i, i0; /* for current position and old position as well */
			i = 0, i0 = 0;
			metrics[0] = 0;
			metrics[1] = 0;
			char* p;
			p = strtok(strdup(data), "\n");
			while (p)
			{
				int w;
				w = strlen(p);
				if(w > metrics[0])
				{
					metrics[0] = w; /* always the maximum is the width of the image */
				}
				metrics[1]++;
				p = strtok(0, "\n");
				printf("%d\t%d\n", metrics[0], metrics[1]);
			}
			p = 0;
			printf("\n");
			metrics[0]+=1; /* add one: works better the bitmap builder */ 
		}
		return result;
	}
	else
	{
		printf("file \"%s\" open error\n", filename);
		return -82;
	}
	return *((int*)((long*)metrics));
}


/** This function padds every line of the data with a space or padding character you specify (feature in development)
*	up to width specified as argument of the function. This function is useful especially by ASCII art where the 
*	drawn line ends with a return and a data for a 8-bit bitmap needs a full line in order to be displayed correctly.
*   NOTE: the size of the "data" must be large enough for output as well (if I expect h lines w columns I must send 
*	to function at least data = h*w.
*/

static int padLinesOf(unsigned char* data, size_t size, unsigned int* metrics)
{
	unsigned char* pline;		/* reads a line */
	unsigned char* szTemp;		/* temporary buffer, the output (data will be set to it) */
	
	if (!metrics) 	return -240;
	if (!data) 		return -250;
	if (!size) 		return -920;
	/* metrics[0] is width, metrics[1] is height */
	szTemp = (unsigned char*)malloc(size);
	memset(szTemp, 0, size);
	memcpy(szTemp, data, size);		/* predefined size */
	int i = 0; /* counts rows, row index: */
	pline = (unsigned char*)strtok(strdup(szTemp), "\n"); /* read first line */
	int crtl = 0; /* current line actual lenght */
	while(pline)
	{
		int len = strlen(pline); // current lenght of the current line
		// if (i>metrics[1]) break; /* beyond last line */
		memcpy(szTemp+crtl, pline, len); 
		memset(szTemp+crtl+len-1, ' ', metrics[0]-len+1); /* pad the rest of the line to width */
		crtl = metrics[0]*i; 
		szTemp[len+1] = '\n'; /* and add end of line */
		pline = (unsigned char*)strtok((char*)0, "\n"); /* read next raw line */
		i++;
	}
	pline = 0;		/* to be sure not to be used again */
	memset(data, '\0', size);
	memcpy(data, szTemp, size);
	free(szTemp); /* release tmp - we don't need it anymore */
	printf("%s", data);
	/******* next section saves the formatted string in a check file to see the result ****/
	if (OUTFILE_CHK)
	{
		FILE* pFile;
		pFile = fopen("out.txt", "wb");
		if(pFile)
		{
			fprintf(pFile, "%s", data);
			fclose(pFile);
		}
		else
		{
			printf("output file open error\n");
		}
	}
	return strlen(data);
}



