#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    

    if (argc != 2 || argv[1] == NULL)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int k = atoi(argv[1]);
    if (k <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
 
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')   
        {
            int a = s[i];
            a = a - 'a';
            a = (a + k) % 26;
            a = a + 'a';
            char c = a;
            printf("%c", c);
        }
      
        else if (s[i] >= 'A' && s[i] <= 'Z') 
        {
            int a = s[i];
            a = a - 'A';
            a = (a + k) % 26;
            a = a + 'A';
            char c = a;
            printf("%c", c);
        }
        
       else
       {
        printf("%c", s[i]);
       }
    }

    printf("\n");

}
