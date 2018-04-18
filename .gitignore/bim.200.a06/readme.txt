
Version.Number = "200.A06/24.01.2018"
Version.Name = "bim"
Version.Description = "Bitmap Image Mapping: BIM is a test application that outputs a 256 gray nuances bitmap file mapping an input text file, for example an ASCII art text"
Version.Author = "Claudiu Ciutacu - Copyright (c) 2017/2018 Claudiu Ciutacu"
Version.Comment = "/**
* The purpose of the program is to develop and test a function that outputs a grayscale bitmap image in a file
* (e.g. "out.bmp") which pixel colors (gray scale) are read from an input text file (e.g. "level.txt") which 
* usually represent an ASCII art text. I use to use it for creating heightmaps at runtime in another applications. 
* It gets its dimensions from the number of lines of the input file (bitmap height) and the longest line of the
* input text (bitmap width) which buffer is processed too in order all the lines to be the same lenght, by padding
* them with spaces.
* For debug, also outputs the resulting in a text file (e.g. "out.txt") when an option is enabled.
*/
"
Version.Copyright = "Claudiu Ciutacu - Copyright (c) 2017/2018 Claudiu Ciutacu"

!-- NOTE: "Twareintor" is copyright Claudiu Ciutacu --

!----------------------------------------------------------------
names: "bim", "bimg"

saved on: "bim.200.a06"

Development path: "D:\\PROJECTS.TEST.018\\TestCreateBmp\\Imgbim.200.a06"

creating a grayscale bitmap image after a text file, usually ASCII art

Alpha Version 000.a06

files:
"main.c"	// starting program
"data.c"	// text input data processing
"bimg.c"	// bitmap output data processing 

// 


----------------------------------------------------------------
