#include "main.h"
#include <iostream>
#include "tree/tree.h"

using namespace std;

ITree<int>* build_tree() {
	int* data1 = new int(1);
	ITree<int>* tn = new Tree<int>("a", data1, true);

	int* data2 = new int(2);
	ITree<int>* tn2 = new Tree<int>("b", data2, false);
	tn2 = tn->insert(tn2);

	int* data3 = new int(3);
	ITree<int>* tn3 = new Tree<int>("c", data3, false);
	tn->insert(tn3);

	int* data4 = new int(4);
	ITree<int>* tn4 = new Tree<int>("d", data4, false);
	tn->insert(tn4);

	int* data5 = new int(5);
	ITree<int>* tn5 = new Tree<int>("e", data5, false);
	tn2->insert(tn5);

	int* data6 = new int(6);
	ITree<int>* tn6 = new Tree<int>("f", data6, false);
	tn->insert(tn6, "e");

	return tn;
}

int main() {
	cout << "main starts to run..." << endl;

	auto tr = build_tree();
	cout << tr->str() << endl;
}