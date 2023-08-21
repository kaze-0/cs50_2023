#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid_check(string key);
string substitute(string input, string key);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    } else if (valid_check(argv[1])) {
        string plain = get_string("plaintext: ");
        string cipher = substitute(plain, argv[1]);
        printf("ciphertext: %s\n", cipher);
    } else return 1;
    return 0;
}

bool valid_check(string key) {
    bool flag = 0;
    for (int i = 0; key[i]; i ++) if (!(toupper(key[i])<='Z' && toupper(key[i])>='A')) flag = 1;

    if (strlen(key) != 26 || flag) {

        printf("Key must contain 26 characters.\n");
        return false;
    }
    else {

        for (int l = 'A'; l <= 'Z'; l ++) {
            int tmp = 0;
            for (int i = 1; key[i]; i ++) {
                if (toupper(key[i]) == l) tmp ++;
                if (tmp > 1) return false;
            }
        }

        return true;
    }
}

string substitute(string input, string key) {
    string KEY = key;
    for (int i = 0 ; key[i]; i ++) {
        KEY[i] = toupper(key[i]);
    }

    int enc[26] = {0};
    string cipher = input;

    for (int i = 0; key[i]; i ++) {
        enc[i] = KEY[i] - 'A'; // enc[input] -> cipher
    }

    for (int i = 0 ; input[i]; i ++) {

            if (input[i]>='a' && input[i]<='z') cipher[i] = enc[toupper(input[i]) - 'A'] + 'a';
            if (input[i]>='A' && input[i]<='Z') cipher[i] = enc[toupper(input[i]) - 'A'] + 'A';

    }





    return cipher;
}