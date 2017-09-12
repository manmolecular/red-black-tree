#include "BinaryTree.h" // Операции над бинарным деревом
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void genTree(BinaryTree<float> &tree, unsigned int quant)
{
	srand(time(NULL));
	for (unsigned int i = 0; i ^ quant; ++i)
	{
		//float tmp = (float)((std::rand() << 2) | std::rand()) / std::rand();
		int tmp = rand() % 100;
		cout << "GENERATED " << tmp << endl;
		tree.attach(tmp);
	}
}

void display(int &a)
{
	cout << "&a == " << &a << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	try {
		BinaryTree<float> myTree;
		genTree(myTree, 10);
		myTree.printLevels();
		cout << myTree;
		while (1)
		{
			float b;
			cout << "Element for search ";
			cin >> b;
			cout << boolalpha << myTree.isExist(b);
			float a;
			cout << "Element for delete: ";
			cin >> a;
//			cin >> b;
			myTree.deleteItem(a);
			cout << a << " DELETED" << endl;
			cout << myTree;
			cout << myTree.getDepth() << " LEVELS" << endl;
		}
	}
	catch (TreeException error)
	{
		cout << error.what() << endl;
		return 1;
	}
	return 0;
} // Конец функции main