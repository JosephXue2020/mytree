#include "main.h"
#include <iostream>
#include "tree/node.h"
#include "tree/tree.h"
#include <vector>

using namespace std;

// ≤‚ ‘Node
void test_node() {
	Node<int> n1{ "n1", 99 };
	cout << n1.str() << endl;

	Node<int> n2;
	n2.setId("n2");
	n2.setData(99);
	cout << n2.str() << endl;
	cout << n2.equal(n1) << endl;

	Node<int> n3(n1);
	cout << n3.str() << endl;
	cout << n1.duplicate(n3) << endl;
}

Tree<int>* build_tree() {
	Tree<int>* t = new Tree<int>("a", 1, true);

	Tree<int>* t2 = new Tree<int>("b", 2, false);
	auto pt2 = t->insert(*t2);

	Tree<int>* t3 = new Tree<int>("c", 3, false);
	t->insert(*t3);

	Tree<int>* t4 = new Tree<int>("d", 4, false);
	t->insert(*t4);

	Tree<int>* t5 = new Tree<int>("e", 5, false);
	pt2->insert(*t5);

	Tree<int>* t6 = new Tree<int>("f", 6, false);
	t->insert(*t6, "e");

	cout << t->str() << endl;
	return t;
}

void test_tree() {
	/*Tree<int> t1 = Tree<int>("t1", 99, true);
	auto children = t1.children();
	cout << t1.str() << endl;*/

	Tree<int>* t2 = build_tree();
	cout << t2->str() << endl;
	cout << t2->search("e")->str() << endl << endl;

	//// ≤‚ ‘branch
	//auto vec = t2->branch("e");
	//for (auto it = vec.begin(); it != vec.end(); it++) {
	//	cout << (*it)->str() << endl;
	//}

	// ≤‚ ‘Œˆππ
	delete t2;
}

int main() {
	cout << "main starts to run..." << endl;

	// test_node();

	/*auto tr = build_tree();
	cout << tr->str() << endl;*/

	test_tree();

	cin.get();
}