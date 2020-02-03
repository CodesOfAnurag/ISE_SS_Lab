#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
   
void main( ) 
{ 
    // w --> writing into file
    // r --> reading the file
    FILE *filePointer = fopen("poem.txt", "r");
    FILE *newFilePointer = fopen("poem_new.txt", "w");

    char fileReader[5000];
    char fileWriter[5000];
    char readChar;

    if ( filePointer == NULL || newFilePointer == NULL) 
        printf("File Not Found\n"); 
    else
    { 
        
        // // **** Writing **** 
        // if ( strlen (  fileWriter ) > 0 ) 
        // { 
        //     fputs(fileWriter, filePointer) ;    
        //     fputs("\n", filePointer) ; 
        // } 
                
        // **** Reading ****
        // printf("File Content\n-----------------------------------------------------\n");
        // while( fgets ( fileReader, 3000, filePointer ) != NULL ) 
        //     printf( "%s" , fileReader ) ;
        
        // // **** Copying ****
        /*fseek(filePointer, 0, SEEK_SET);
        while ((readChar = fgetc(filePointer)) != EOF)
            fputc(readChar, newFilePointer);*/

		//char ch=fgetc(filePointer); 

		char ch=fgetc(filePointer);
		fputc(ch, newFilePointer);
		char prevch=' ';
		printf(" The content of the file are : \n");
		int i=0, count=1, spaces=0, newLine=1;
		while(ch!=EOF)
		{ 
		    // displaying
		    printf("%c",ch);

		    // counting  
		    if((ch==' ' && prevch!=' ')||ch=='\n')
		   	    count++; 
		    else if (isalpha(ch)||isdigit(ch))
		    	i++;
		    if (isspace(ch) && ch!='\n')
		    	spaces++;
		    if (ch=='\n')
		    	newLine++;
		    prevch=ch;
		    ch=fgetc(filePointer);

		    // copying
		    fputc(ch, newFilePointer);
		} 

        printf("\n\nNumber of Characters:%d\n", i);
        printf("Number of Words:%d\n", count);
        printf("Number of Spaces:%d\n", spaces);
        printf("Number of Lines:%d\n", newLine);

        fclose(filePointer);
        fclose(newFilePointer);
        printf("\nFiles closed.\n") ; 
    }        
} 