#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "MultiAVLImplementation.h"

using namespace std;

int main()
{
    MultisetAVLTree<string> tree = MultisetAVLTree<string>();

    string hola0 = "Hola0";
    string hola1 = "Hola1";
    string hola2 = "Hola2";
    string hola3 = "Hola3";
    string hola4 = "Hola4";
    string hola5 = "Hola5";
    string hola6 = "Hola6";
    string hola66 = "Hola66";
    string hola22 = "Hola22";

    tree.insert(&hola0,6);
    
    tree.insert(&hola1,2);
    
    tree.insert(&hola2,7);
    
    tree.insert(&hola3,1);
    
    tree.insert(&hola6,0);

    tree.insert(&hola5,3);

    tree.insert(&hola4,8);

    tree.insert(&hola4,-8);


    tree.printInorder();
    tree.printReverseInOrder();

    cout << "top vector" << endl;
    





    return 0;
}
