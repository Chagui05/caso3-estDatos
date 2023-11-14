#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

#define MAX 4
#define MIN 2

struct NodoBtree {
	int val[MAX + 1], count;
	NodoBtree *link[MAX + 1];
};

NodoBtree *root;

//Crear nodo 
NodoBtree * crearnodo(int val, NodoBtree *hijo) {
	NodoBtree *NuevoNodo = new NodoBtree;
	NuevoNodo->val[1] = val;
	NuevoNodo->count = 1;
	NuevoNodo->link[0] = root;
	NuevoNodo->link[1] = hijo;
	return NuevoNodo;
}

//coloca el nodo en la posicion adecuada, de acuerdo a su valor
void Colocarnodo(int val, int pos, NodoBtree *node, NodoBtree *hijo) {
	int j = node->count;
	while (j > pos) {
		node->val[j + 1] = node->val[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	node->val[j + 1] = val;
	node->link[j + 1] = hijo;
	node->count++;
}


void PartirNodo(int val, int *pval, int pos, NodoBtree *node, NodoBtree *hijo, NodoBtree **NuevoNodo) {
	int median, j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*NuevoNodo = new NodoBtree;
	j = median + 1;
	while (j <= MAX) {
		(*NuevoNodo)->val[j - median] = node->val[j];
		(*NuevoNodo)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*NuevoNodo)->count = MAX - median;

	if (pos <= MIN) {
		Colocarnodo(val, pos, node, hijo);
	}
	else {
		Colocarnodo(val, pos - median, *NuevoNodo, hijo);
	}
	*pval = node->val[node->count];
	(*NuevoNodo)->link[0] = node->link[node->count];
	node->count--;
}

//colocar valor
int SetValorNodo(int val, int *pval, NodoBtree *node, NodoBtree **hijo) {

	int pos;
	if (!node) {
		*pval = val;
		*hijo = NULL;
		return 1;
	}

	if (val < node->val[1]) {
		pos = 0;
	}
	else {
		for (pos = node->count;
			(val < node->val[pos] && pos > 1); pos--);
		if (val == node->val[pos]) {
			cout << "No est permitido nodos duplicados\n";
			return 0;
		}
	}
	if (SetValorNodo(val, pval, node->link[pos], hijo)) {
		if (node->count < MAX) {
			Colocarnodo(*pval, pos, node, *hijo);
		}
		else {
			PartirNodo(*pval, pval, pos, node, *hijo, hijo);
			return 1;
		}
	}
	return 0;
}

//inserta valores en el btree
void insertar(int val) {
	int flag, i;
	NodoBtree *hijo;

	flag = SetValorNodo(val, &i, root, &hijo);
	if (flag)
		root = crearnodo(i, hijo);
}

//copia el sucesor del nodo que ser borrado
void copySuccessor(NodoBtree *minodo, int pos) {
	NodoBtree *dummy;
	dummy = minodo->link[pos];

	for (; dummy->link[0] != NULL;)
		dummy = dummy->link[0];
	minodo->val[pos] = dummy->val[1];

}

//remueve un valor de un nodo y reacomoda el arbol
void removeVal(NodoBtree *minodo, int pos) {
	int i = pos + 1;
	while (i <= minodo->count) {
		minodo->val[i - 1] = minodo->val[i];
		minodo->link[i - 1] = minodo->link[i];
		i++;
	}
	minodo->count--;
}

//shift a la derecha
void doRightShift(NodoBtree *minodo, int pos) {
	NodoBtree *x = minodo->link[pos];
	int j = x->count;

	while (j > 0) {
		x->val[j + 1] = x->val[j];
		x->link[j + 1] = x->link[j];
	}
	x->val[1] = minodo->val[pos];
	x->link[1] = x->link[0];
	x->count++;

	x = minodo->link[pos - 1];
	minodo->val[pos] = x->val[x->count];
	minodo->link[pos] = x->link[x->count];
	x->count--;
	return;
}

//shift a la izquierda
void doLeftShift(NodoBtree *minodo, int pos) {
	int j = 1;
	NodoBtree *x = minodo->link[pos - 1];

	x->count++;
	x->val[x->count] = minodo->val[pos];
	x->link[x->count] = minodo->link[pos]->link[0];

	x = minodo->link[pos];
	minodo->val[pos] = x->val[1];
	x->link[0] = x->link[1];
	x->count--;

	while (j <= x->count) {
		x->val[j] = x->val[j + 1];
		x->link[j] = x->link[j + 1];
		j++;
	}
	return;
}

//Fusionar nodos
void UnirNodos(NodoBtree *minodo, int pos) {
	int j = 1;
	NodoBtree *x1 = minodo->link[pos], *x2 = minodo->link[pos - 1];

	x2->count++;
	x2->val[x2->count] = minodo->val[pos];
	x2->link[x2->count] = minodo->link[0];

	while (j <= x1->count) {
		x2->count++;
		x2->val[x2->count] = x1->val[j];
		x2->link[x2->count] = x1->link[j];
		j++;
	}

	j = pos;
	while (j < minodo->count) {
		minodo->val[j] = minodo->val[j + 1];
		minodo->link[j] = minodo->link[j + 1];
		j++;
	}
	minodo->count--;
	free(x1);
}

//Ajusta el nodo dado
void AjustarNodo(NodoBtree *minodo, int pos) {
	if (!pos) {
		if (minodo->link[1]->count > MIN) {
			doLeftShift(minodo, 1);
		}
		else {
			UnirNodos(minodo, 1);
		}
	}
	else {
		if (minodo->count != pos) {
			if (minodo->link[pos - 1]->count > MIN) {
				doRightShift(minodo, pos);
			}
			else {
				if (minodo->link[pos + 1]->count > MIN) {
					doLeftShift(minodo, pos + 1);
				}
				else {
					UnirNodos(minodo, pos);
				}
			}
		}
		else {
			if (minodo->link[pos - 1]->count > MIN)
				doRightShift(minodo, pos);
			else
				UnirNodos(minodo, pos);
		}
	}
}

//borrar un valor del nodo
int BorrarDeNodo(int val, NodoBtree *minodo) {
	int pos, flag = 0;
	if (minodo) {
		if (val < minodo->val[1]) {
			pos = 0;
			flag = 0;
		}
		else {
			for (pos = minodo->count;
				(val < minodo->val[pos] && pos > 1); pos--);
			if (val == minodo->val[pos]) {
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
		if (flag) {
			if (minodo->link[pos - 1]) {
				copySuccessor(minodo, pos);
				flag = BorrarDeNodo(minodo->val[pos], minodo->link[pos]);
				if (flag == 0) {
					cout << "No existe en el B-Tree\n";
				}
			}
			else {
				removeVal(minodo, pos);
			}
		}
		else {
			flag = BorrarDeNodo(val, minodo->link[pos]);
		}
		if (minodo->link[pos]) {
			if (minodo->link[pos]->count < MIN)
				AjustarNodo(minodo, pos);
		}
	}
	return flag;
}

/* delete val from B-tree */
void borrado(int val, NodoBtree *minodo) {
	NodoBtree *tmp;
	if (!BorrarDeNodo(val, minodo)) {
		cout << "No existe ese valor en el B-Tree\n";
		system("pause");
		return;
	}
	else {
		if (minodo->count == 0) {
			tmp = minodo;
			minodo = minodo->link[0];
			free(tmp);
		}
	}
	root = minodo;
	cout << "Borrado"<<endl;
	system("pause");
	return;
}

/* search val in B-Tree */
void busqueda(int val, int *pos, NodoBtree *minodo) {
	if (!minodo) {
		return;
	}

	if (val < minodo->val[1]) {
		*pos = 0;
	}
	else {
		for (*pos = minodo->count;
			(val < minodo->val[*pos] && *pos > 1); (*pos)--);
		if (val == minodo->val[*pos]) {
			cout << "Se ha encontrado el Nodo\n";
			system("pause");
			return;
		}
	}
	busqueda(val, pos, minodo->link[*pos]);
	cout << "No se ha encontrado el Nodo\n";
	system("pause");
	return;
}

// B-Tree desplegar
void desplegar(NodoBtree *minodo) {
	int i;
	if (minodo) {
		for (i = 0; i < minodo->count; i++) {
			desplegar(minodo->link[i]);
			cout << minodo->val[i + 1] << ' ';
		}
		desplegar(minodo->link[i]);
	}
}

int main() {
	
	int val, opt;
	while (true) {
		system("CLS");
		cout << "1. insertar\n";
		cout << "2. Borrar\n";
		cout << "3. Buscar\n";
		cout << "4. Desplegar (InOrder)\n";
		cout << "5. Salir \n Opcion? ";
		cin >> opt;
		cout << endl;
		switch (opt) {
		case 1:
			cout << "Ingrese valor del nodo:";
			cin >> val;
			insertar(val);
			break;
		case 2:
			cout << "Cual elemento desea borrar:";
			cin >> val;
			borrado(val, root);
			break;
		case 3:
			cout << "Cual elemento desea buscar?";
			cin >> val;
			busqueda(val, &opt, root);
			break;
		case 4:
			desplegar(root);
			break;
		case 5:
			exit(0);
		}
		cout << endl;
	}

	system("pause");
}