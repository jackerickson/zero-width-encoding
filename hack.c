#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

int main(){
char *buffer = NULL;
size_t size = 0;

FILE * fp = fopen("/home/jack/hacks/out.txt", "r");
	

	
/* Get the buffer size */
fseek(fp, 0, SEEK_END); /* Go to end of file */
size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
buffer = malloc((size+1) * sizeof(*buffer)); /* size + 1 byte for the \0 */

/* Read the file into the buffer */
fread(buffer, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
buffer[size] = '\0';

/* Print it ! */
for(int i=0;i<=size;i++){
	printf("%02X\n",buffer[i]);
}

printf("%s\n%d\n", buffer, size);

}
