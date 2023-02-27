#include <stdio.h>

int main() {
   FILE *fp;
   char filename[100];
   char line[100];

   printf("Enter the filename to read: ");
   scanf("%s", filename);

   fp = fopen(filename, "r");

   if (fp == NULL) {
      printf("Error opening file!\n");
      return 1;
   }

   while (fgets(line, 100, fp) != NULL) {
      printf("%s", line);
   }

   fclose(fp);
   return 0;
}
