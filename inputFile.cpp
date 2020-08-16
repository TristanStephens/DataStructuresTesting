#include "Lab2_BTree_menu.cpp"
#include <cstdlib>

void inputFile(string fObject, btree& b);

int main()
{
	int n, x, op;
	string input = "", input2 = "", fs = "";
	string fileName;
	system("cls");
	node *p;
	cout << "\nEnter number of keys in the node:";
	cin >> n;
	btree b(n);
	
	do
	{
		cout << "\n*****MENU*****";
		cout << "\n1.Insert \n2.Search \n3.Delete \n4.Display \n5.Input Data File \n6.Quit";
		cout << "\nEnter your choice:";
		cin >> op;
		switch (op)
		{
		case 1:
				cout << "\nEnter Student ID: \n";
				cin.ignore();
				while (true) {
					getline(cin, input);

					stringstream myStream(input);
					if (myStream >> x)
						break;
					cout << "Invalid number, please try again" << endl;
				}
				cout << "\nEnter Student Last Name: \n";
				cin >> input2;
				cout << "\nEnter Student First Name: \n";
				cin >> fs;
				b.insert(x, input, input2, fs);
				cout << "\nTree after insertion:";
				b.displaytree();
				break;
		case 2:
			cout << "\nEnter Student ID:\n";
			cin.ignore();
			while (true) {
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> x)
					break;
				cout << "Invalid number, please try again" << endl;
			}
			p = b.search(x);
			if (p != NULL)
			{
				cout << "Found in the node!";
				p->display();
			}
			else
				cout << "\nElement not found!";
			break;

		case 3:
			cout << "\nEnter Student ID:";
			cin.ignore();
			while (true) {
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> x)
					break;
				cout << "Invalid number, please try again" << endl;
			}
			p = b.search(x);
			if (p != NULL)
			{
				b.delet(x);
				b.displaytree();
			}
			else
				cout << "\nNot found!";
			break;

		case 4:
			b.displaytree();
			break;

		case 5:
			cout << "Type a valid file name:" << endl;
			cin >> fileName;
			inputFile(fileName, b);
		}
	} while (op != 6);

	return 0;
}

//ADDED INPUT FUNCTION
void inputFile(string fObject, btree& b)
{
	string line;
	string temp;
	int x = 0;

	ifstream ifile_obj;

	ifile_obj.open(fObject);

	while (getline(ifile_obj, line))
	{
		istringstream S(line);
		vector<string> tString;
		while (S >> temp)
			tString.push_back(temp);

		x = stoi(tString[0]);
		b.insert(x, tString[0], tString[1], tString[2]);
	}

	ifile_obj.close();

	cout << "Records added succussfully." << endl;

}