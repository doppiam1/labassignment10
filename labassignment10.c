#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie* children[26];
};


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int index = 0;
    for (int i = 0; i < strlen(word); i++)
        {
            index = word[i] - 'a';
            if (pTrie->children[index] == NULL)
                {
                    return 0;
                }
            pTrie = pTrie->children[index];
        }
    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    int i;
    for (i=0; i<26; i++)
    {
        if (pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* trie = malloc(sizeof(struct Trie));
    trie->count = 0;

    for (int i = 0; i < 26; i++)
    {
        trie->children[i] = NULL;
    }

    return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int index = 0;
    for (int i = 0; i < strlen(word); i++)
        {
            index = word[i] - 'a';
            if (pTrie->children[index] == NULL)
                {
                    pTrie->children[index] = createTrie();
                }
            pTrie = pTrie->children[index];
        }
    pTrie->count += 1;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fptr = fopen("dictionary.txt", "r");

    int numWords;
    fscanf(fptr, "%d", &numWords);
    char tempString[22];

    for (int i = 0; i < numWords; i++)
        {
            fscanf(fptr, "%s", tempString);
            pInWords[i] = malloc(sizeof(char) * (strlen(tempString) + 1));
            strcpy(pInWords[i], tempString);
        }

    fclose(fptr);
    return numWords;
}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
