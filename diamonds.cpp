#include <cstdio>

int main() 
{
   printf("%c", 0x00);

for(unsigned short y = 0; y <= 6; y++){
   for(int i = 1; i < 10; i++){
      for(int p = 10; p > i; p--){
         printf("%c", ' ');
      }

      for(int k = 0; k < i; k++){
         printf("%c%c", ' ', '+');
      }
      printf("\n");
   }

   for(int i = 0; i < 9; i++){
      for(int p = 0; p < i; p++){
         printf("%c", ' ');
      }

       for(int p = 10; p > i; p--){
          printf("%c%c", ' ', '+');
       }
      printf("\n");
  }
}

  return 0; 
}
