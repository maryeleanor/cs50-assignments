#include <stdio.h>
#include <cs50.h>

// build pyramid 
void build (height) {
   
    
    if (height >= 1)
        {
        printf("       #");
        printf("  ");
        printf("#\n");

        }
    if (height >= 2)
        {
        printf("      ##");
        printf("  ");
        printf("##\n");
        }
    if (height >= 3)
        {
        printf("     ###");
        printf("  ");
        printf("###\n");
        }
    if (height >= 4)
        {
        printf("    ####");
        printf("  ");
        printf("####\n");
        }
    if (height >= 5)
        {
        printf("   #####");
        printf("  ");
        printf("#####\n");
        }
    if (height >= 6)
        {
        printf("  ######");
        printf("  ");
        printf("######\n");
        }
    if (height >= 7)
        {
        printf(" #######");
        printf("  ");
        printf("#######\n");
        }
    if (height >= 8)
        {
        printf("########");
        printf("  ");
        printf("########\n");
        }     
    
}    
  
int get_height(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}

int main(void)
{
    int height = get_height("How high can mario jump? ");
    build(height);
}

