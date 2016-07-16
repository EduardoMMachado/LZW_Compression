// Implementado por Eduardo Machado e Victor Perszel
// 2015

#include "lzw.h"

using namespace std;

int main(int argc, char *argv[])
{
	ifstream fileIn;
	ofstream fileOut;
	string parameter, temp, nameFileIn, nameFileOut, inputPack="", outputUnpack;
	int *outputPack=NULL, *inputUnpack, length, i;

	// Leitura de parâmetros.
	if(argc != 4){
		cout << "Arquivo não encontrado!" << endl;
		return 0;
	}
	nameFileIn=argv[1];
	parameter=argv[2];
	nameFileOut=argv[3];


	if(parameter == "pack"){
		// Abertura do arquivo de entrada.
		fileIn.open(nameFileIn.c_str(), ios::in);
		fileIn.seekg (0);

		// Leitura do arquivo.
		while(getline(fileIn, temp)) {
			inputPack += temp + "\n";
		}

		// Compactação.
		outputPack = pack(inputPack);

		// Escrita no arquivo de saída.
		fileOut.open(nameFileOut.c_str(), ios::binary);
		for(i = 1; i <= outputPack[0]; ++i){
			fileOut.write ((char *)&outputPack[i], sizeof(int));
		}

	}else if(parameter == "unpack"){
		// Abertura do arquivo de entrada.
		fileIn.open(nameFileIn.c_str(), ios::binary);

		// Contagem do tamanho do arquivo.
		fileIn.seekg (0, ios::end);
		length = fileIn.tellg();
		fileIn.seekg (0, ios::beg);

		// Alocação do vetor para a leitura do arquivo.
		inputUnpack = new int[length/4];

		// Leitura.
		for (i = 0; i < length/4; ++i){
			fileIn.read((char*)&inputUnpack[i], sizeof(int));
		}

		// Descompactação.
		outputUnpack = unpack(inputUnpack, length/4);

		// Escrita no arquivo de saída.
		fileOut.open(nameFileOut.c_str(), ios::out);
		fileOut << outputUnpack;
	}else{
		cout << "Parâmetro inválido!" << endl;
	}

	// Fecha os arquivos
	fileIn.close();
	fileOut.close();
	return 0;
}