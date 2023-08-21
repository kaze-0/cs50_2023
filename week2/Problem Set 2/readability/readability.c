#include <cs50.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int l = count_letters(text);   // printf("%d\n",l);
    int w = count_words(text);     // printf("%d\n",w);
    int s = count_sentences(text); // printf("%d\n",s);
    float r = 0.0588 * l / w * 100 - 0.296 * s / w * 100 - 15.8;
    if (r < 1)
        printf("Before Grade 1\n");
    else if (r > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n", (int) round(r));
}

int count_letters(string text)
{

    int ctrLett = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            ctrLett++;
    }
    return ctrLett;
}

int count_words(string text)
{

    int ctrWord = 1; // space to sperate a word

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
            ctrWord++;
    }
    return ctrWord;
}

int count_sentences(string text)
{

    int ctrSent = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            ctrSent++;
    }
    return ctrSent;
}