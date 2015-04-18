/**
 * example_output_program.c
 * (C) 2014 Christian Gunderman
 * Modified by:
 * Author Email: gundermanc@gmail.com
 * Modifier Email:
 *
 * Description:
 * Opens a binary file for reading and outputs file embedded in this
 * application to it.
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

#include "image_data.h"

int main() {
  FILE * outFile = fopen("image_after.jpg", "w");
  if(outFile != NULL) {
    size_t i = 0;

    for(i = 0; i < kImageDataSize; i++) {
      fputc(kImageData[i], outFile);
    }
    fclose(outFile);
  }
}
