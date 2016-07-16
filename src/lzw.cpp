// Implementado por Eduardo Machado e Victor Perszel
// 2015

#include "lzw.h"

using namespace std;


int* pack(string input){
	int *output = NULL;
	map<string, int> dictionary;
	string nextChar, currentChar = "";
	int i, size, cont=1, dictionarySize = 256;

	//inicializa o dicionário
	for(i = 0; i < 256; i++){
		dictionary[string(1, i)] = i;
	}

	size = input.size();
	for(i = 0; i < size; i++){
		nextChar = input[i];
		if(dictionary[currentChar + nextChar] != 0){
			currentChar = currentChar + nextChar;
		}else{
			output = (int*) realloc (output, sizeof(int)*(cont+1));
			output[cont] = dictionary[currentChar];
			dictionary[currentChar+nextChar] = dictionarySize;
			currentChar = nextChar;
			dictionarySize++;
			cont++;
		}
	}
	output = (int*) realloc (output, sizeof(int)*(cont+1));
	output[cont] = dictionary[currentChar];

	output[0] = cont;

	return output;

}

string unpack(int* input, int size){
	map<int, string> dictionary;
	string currentChar, nextChar, output = "";
	int i, dictionarySize = 256;
	int currentWord, nextWord;

	//inicializa o dicionário
	for (i = 0; i < 256; i++){
		dictionary[i] = string(1, i);
	}

	nextWord = input[0];
	output += dictionary[nextWord];
	for(i = 0; i < size-1; i++){
		currentWord = nextWord;
		nextWord = input[i+1];
		if(dictionary[nextWord] != ""){
			output += dictionary[nextWord];
			currentChar = dictionary[currentWord];
			nextChar = dictionary[nextWord][0];
			dictionary[dictionarySize] = currentChar + nextChar;
			dictionarySize++;
		}else{
			currentChar = dictionary[currentWord];
			nextChar = dictionary[currentWord][0];
			output += currentChar + nextChar;
			dictionary[dictionarySize] = currentChar + nextChar;
			dictionarySize++;
		}
	}
	return output;
}
