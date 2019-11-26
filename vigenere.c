#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
void cipher(char a, int k);

int main(int argc, string argv[])
{
    // error checking for key
    if (argc != 2 || argv[1] == NULL)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
   
    string k = argv[1];
    // cycle through characters in k
    for (int i = 0, n = strlen(k); i < n; i++)
    { 
        if  (isalpha(k[i]) == 0)
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }  
   
    //get plaintext string
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");
    
    int keyIndex = 0;
    int keyLength = strlen(k);
    
    //cycle through characters in plaintext
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        if (keyLength == keyIndex)
        {
            keyIndex = 0;
        }
        
        if (isalpha(plainText[i]) != 0) 
        {
            int key = shift(k[keyIndex]);
            cipher(plainText[i], key);  //run char through cipher
            keyIndex++;
        }
        else 
        {
             printf("%c", plainText[i]);
        }
        
    } 
    
    printf("\n");  

}

int shift(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        c = toupper(c);
    }    
   
    c = c - 'A';
    return c;
}



void cipher(char a, int k)
{
	if (a >= 'a' && a <= 'z')   
    {
        a = a - 'a';
        a = (a + k) % 26;
        a = a + 'a';
        char c = a;
        printf("%c", c);
    }
      
    else if (a >= 'A' && a <= 'Z') 
    {
        a = a - 'A';
        a = (a + k) % 26;
        a = a + 'A';
        char c = a;
        printf("%c", c);
    } 
}
