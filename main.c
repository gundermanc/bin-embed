/**
 * main.c
 * (C) 2014 Christian Gunderman
 * Modified by:
 * Author Email: gundermanc@gmail.com
 * Modifier Email:
 *
 * Description:
 * Opens a binary file for reading and outputs it to a C header.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BYTE_AS_STRING_MAX   10
#define VAR_NAME             75
#define MAX_COLUMN_WIDTH     76

static bool file_to_header(const char * varName, const char * inputFileName,
			   const char * outputFileName) {
  FILE * inputFile;
  FILE * outputFile;

  inputFile = fopen(inputFileName, "r");
  if(inputFile == NULL) {
    return false;
  }

  outputFile = fopen(outputFileName, "w");
  if(outputFile != NULL) {
    int c = 0;
    int columnStart = 0;
    int column = 0;
    size_t objSize = 0;
    char variableCrap[75];

    fputs("/* DO NOT EDIT: Generated with bin-embed by Christian Gunderman */\r\n#include <stdlib.h>\r\n\r\n", outputFile);
    sprintf(variableCrap, "const int %s[] = {", varName);
    column = columnStart = strlen(variableCrap);
    fputs(variableCrap, outputFile);

    while((c = fgetc(inputFile)) != EOF) {
      char byteAsString[BYTE_AS_STRING_MAX];
      sprintf(byteAsString, "0x%02x, ", c);

      if(fputs(byteAsString, outputFile) == EOF) {
	return false;
      }

      column += strlen(byteAsString);

      if(column >= MAX_COLUMN_WIDTH) {
	int i = 0;
	if(fputs("\r\n", outputFile) == EOF) {
	  return false;
	}

	for(i = 0; i < columnStart; i++) {
	  if(fputc(' ', outputFile) == EOF) {
	    return false;
	  }
	}
	column = columnStart;
      }
      objSize++;
    }

    sprintf(variableCrap, "};\r\nconst size_t %sSize = %lu;", varName, (unsigned long)objSize);
    fputs(variableCrap, outputFile);

    fclose(outputFile);
  }

  fclose(inputFile);
  return true;
}

static void print_help() {
  printf("bin-embed\r\n");
  printf("(C) 2014 Christian Gunderman\r\n\r\n");
  printf("Convert binary files to C headers.\r\n");
  printf("Usage:\r\n");
  printf("  bin-embed [constantName] [inputFile] [outputFile] ... repeat\r\n");
}

int main(int argc, const char* argv[]) {
  if(argc % 4 != 0) {
    print_help();
  }

  
  if(!file_to_header(argv[1], argv[2], argv[3])) {
    perror("Can't serialize");
  }
}
