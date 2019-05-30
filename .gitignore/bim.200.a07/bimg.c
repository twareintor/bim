
#include <stdio.h>
#include <stdlib.h> // memcpy

/*it must result a 8 bit grayscale bitmap:*/


static int drawbmpg(char* filename, unsigned char* data, int w, int h) 
{

    FILE *f;
	/* defining file header and color table (palette) : */
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 8,0, 0,0,0,0, 0,0,0,0, 1,0,0,0, 1,0,0,0, 256,0,0,0, 256,0,0,0};
	unsigned char colorTable[0x400] = {0};
    unsigned char bmppad[3] = {0,0,0};

	/* calculating the file size: */
	/*w is your image width, h is image height, both int*/
    int filesize = 14 + 40 + 0x400 + 1*(4-w%4)*h;  
	/* fileheader */
    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	/* infoheader */
    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);
	/* image size: */   
    int imgSize;
    imgSize = 1*(w+(4-w%4))*h;
    bmpinfoheader[34] = (unsigned char)( imgSize    );
    bmpinfoheader[35] = (unsigned char)( imgSize>> 8);
    bmpinfoheader[36] = (unsigned char)( imgSize>>16);
    bmpinfoheader[37] = (unsigned char)( imgSize>>24);
	/* fill the color table for a nice grayscale image: */
	int i;
	for(i=0; i<0x400; i+=0x04)
	{
		char gray = i/4; char alpha = 0xff;
		colorTable[i+0] = gray;
		colorTable[i+1] = gray;
		colorTable[i+2] = gray;
		colorTable[i+3] = alpha;
	}
	/* now do the work: */
    f = fopen(filename,"wb");
    if(f)
    {
   	    fwrite(bmpfileheader,1,14,f);
	    fwrite(bmpinfoheader,1,40,f);
		fwrite(colorTable, 1, 0x400, f);
	    unsigned int i;
	    for(i=0; i<h; i++)
	    {
            fwrite(data + (w*(h-i)), 1, w, f);
            fwrite(bmppad, 1, 1*(4-w%4), f);
	    }
	    fclose(f);
	    return -1;
	}
    return 0;
}


