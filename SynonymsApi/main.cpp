#include <iostream>
#include "SynonymsApi.h"


int main(){
    apiGetter<Synonym> api; // Suponiendo que Synonym es la clase para almacenar sinónimos
    // Palabra para la que deseas obtener sinónimos
    string wordToLookup = "asdasdasdasdasdasdasd";

    Synonym *synonyms = api.getSynonyms(wordToLookup);

    if (synonyms) {
        if (synonyms->synonyms.size() == 0){
            cout << "No se encontraron sinónimos para la palabra: " << wordToLookup << endl;
        }else{
            cout << "Sinónimos de " << synonyms->word << ":" << endl;
            for (const string &synonym : synonyms->synonyms) {
                cout << synonym << endl;
            }
        }
        delete synonyms;
    } else {
        cout << "No se encontraron sinónimos para la palabra: " << wordToLookup << endl;
    }

    return 0;
}