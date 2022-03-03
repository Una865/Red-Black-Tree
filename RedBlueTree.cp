
#include <iostream>
#include <fstream>
#include<stack>
#include<vector>
#include<map>

using namespace std;

int ch;
vector<pair<int, string> > v;
map<pair<int, string>, int> m1;
map<pair<int, string>, int> m2;

struct Node {

	int priority;
	string s;
	Node* parent;
	Node* left;
	Node* right;
	int color; // 1:Red, 0:Black
};
typedef Node* NodePtr;


class RBTree {

private:
	NodePtr root;
	NodePtr TNULL;
	int s = 0;

	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->priority = -1;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}
	void inOrderHelper(NodePtr node, int priority) {
		if (node != TNULL) {
			inOrderHelper(node->left, priority);
			if (node->priority == priority)s++;
			inOrderHelper(node->right, priority);
		}
	}
	NodePtr searchTreeHelper(NodePtr node, int key, string s) {
		if (node == TNULL) {
			return nullptr;
		}
		if (key == node->priority && s == node->s)
			return node;

		if (key < node->priority || (key == node->priority && s.compare(node->s) < 0)) {
			return searchTreeHelper(node->left, key, s);
		}
		return searchTreeHelper(node->right, key, s);
	}
	NodePtr searchTreeStringHelper(NodePtr node, string s) {
		if (node == TNULL) {
			return nullptr;
		}
		if (s == node->s)
			return node;

		if (s.compare(node->s) < 0) {
			return searchTreeStringHelper(node->left, s);
		}
		return searchTreeStringHelper(node->right, s);
	}
	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						// case 3.3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						// case 3.3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}
	void rbTransplant(NodePtr u, NodePtr v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}
	void deleteNodeHelper(NodePtr node, int key, string s) {
		// find the node containing key
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL) {
			if (node->priority == key && s == node->s) {
				z = node;
			}

			if (node->priority < key || (node->priority == key && s.compare(node->s) < 0)) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << " Trazena akcija ne postoji. " << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) {
			fixDelete(x);
		}
	}
	void deleteNodePrHelper(NodePtr node, int key) {

		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL) {
			if (node->priority == key) {
				z = node;
			}

			if (node->priority < key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << " Trazena akcija ne postoji. " << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) {
			fixDelete(x);
		}
	}
	void deleteTreeHelper(NodePtr &node) {
		if (node == TNULL) return;
		deleteTreeHelper(node->left);
		deleteTreeHelper(node->right);
		node = TNULL;
	}
	void fixInsert(NodePtr k) {
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}
	void printHelper(ostream& os, NodePtr root, string indent, bool last, int num) {
		
		if (root != TNULL) {/*
			os << indent;
			if (last) {
				os << "D----";
				indent += "     ";
			}
			else {
				os << "L----";
				indent += "|    ";
			}*/
			num += 10;
			printHelper(os, root->left, indent, false, num);
			os << "\n";
			for (int i = 10; i < num; i++)
				os << " ";

			string sColor = root->color ? "CRVENO" : "CRNO";
			os << root->priority <<"-" << root->s[0] << root->s[1] << root->s[2] << "(" << sColor << ")" << endl;
			
			printHelper(os, root->right, indent, true,num);
		}
		
	}
	void twoTreePrintHelper(ostream& os, NodePtr root, string indent, bool last,int num)
	{
		if (root != TNULL) {
			

			int z = 0;
			int children = 0;
			bool check = false;
			vector<pair<int, string> > ::iterator it;
			it = find(v.begin(), v.end(), make_pair(root->priority, root->s));

			if (it == v.end()) {

				check = true; //new node
				v.push_back(make_pair(root->priority, root->s));


				if (root->left == TNULL && root->right == TNULL) { //zero branches 
					z = 1;
					children = 0;

				}
				else
					if (root->left == TNULL) { //only one children - right

						if (root->right->color == 0) { //only one black branch
							z = 1;
							children = 1;
						}
						else
						{
							z = 2;
							children = 0; //only one red branch
							v.push_back(make_pair(root->right->priority, root->right->s));
							if (root->right->left != TNULL)children++;
							if (root->right->right != TNULL)children++;
							m1.insert({ make_pair(root->right->priority,root->right->s),z });
							m2.insert({ make_pair(root->right->priority,root->right->s),children });
						}
					}
					else
						if (root->right == TNULL ) { //only one children - left

							if (root->left->color == 0) { //one black branch
								z = 1;
								children = 1;

							}
							else //one red branch
							{
								z = 2;
								children = 0; //only one red branch
								v.push_back(make_pair(root->left->priority, root->left->s));
								if (root->left->left != TNULL)children++;
								if (root->left->right != TNULL)children++;
								m1.insert({ make_pair(root->left->priority,root->left->s),z });
								m2.insert({ make_pair(root->left->priority,root->left->s),children });
							}

						}
						else
						{
							if (root->left->color == 0 && root->right->color == 0) {
								z = 1;
								children = 2;
							}
							else
								if (root->left->color == 0 || root->right->color == 0) {
									z = 2;
									children = 1;

									if (root->left->color == 1) { //left is red

										if (root->left->left != TNULL)
											children++;

										if (root->right->right != TNULL)
											children++;


										v.push_back(make_pair(root->left->priority, root->left->s));

										m1.insert({ make_pair(root->left->priority,root->left->s),z });
										m2.insert({ make_pair(root->left->priority,root->left->s),children });

									}
									else
									{ //right is red

										if (root->right->left != TNULL)
											children++;

										if (root->right->right != TNULL)
											children++;

										v.push_back(make_pair(root->right->priority, root->right->s));

										m1.insert({ make_pair(root->right->priority,root->right->s),z });
										m2.insert({ make_pair(root->right->priority,root->right->s),children });
									}
								}
								else  //both are red
								{
									z = 3;
									children = 0;

									if (root->left->left != TNULL)
										children++;

									if (root->left->right != TNULL)
										children++;

									if (root->right->left != TNULL)
										children++;

									if (root->right->right != TNULL)
										children++;


									v.push_back(make_pair(root->left->priority, root->left->s));
									v.push_back(make_pair(root->right->priority, root->right->s));

									m1.insert({ make_pair(root->left->priority,root->left->s),z });
									m2.insert({ make_pair(root->left->priority,root->left->s),children });
									m1.insert({ make_pair(root->right->priority,root->right->s),z });
									m2.insert({ make_pair(root->right->priority,root->right->s),children });

								}
						}

				m1.insert({ make_pair(root->priority,root->s),z });
				m2.insert({ make_pair(root->priority,root->s),children });
			}

			map<pair<int, string>, int > ::iterator itm1, itm2;
			itm1 = m1.find(make_pair(root->priority, root->s));
			itm2 = m2.find(make_pair(root->priority, root->s));

			num += 10;
			twoTreePrintHelper(os, root->left, indent, false, num);
			os << "\n";
			for (int i = 10; i < num; i++)
				os << " ";

			if (check) {
				if (itm1->second == 1) {
					string sColor = root->color ? "CRVENO" : "CRNO";
					os << "[  |" << root->s[0]<< root->s[1]<< root->s[2] << "-" << sColor<<"|  ]"<< endl;
				}
				else
					if (itm1->second == 2)
					{
						if (root->left != TNULL && root->left->color == 1) {

							string sColor = root->left->color ? "CRVENO" : "CRNO";
							os <<"["<< root->left->s[0] << root->left->s[1] << root->left->s[2] << "-" << sColor<< "|";
							sColor = root->color ? "CRVENO" : "CRNO";
							os << root->s[0] << root->s[1] << root->s[2] << "-" <<sColor<< "|  ]" << " " << endl;


						}

						else
							if (root->right != TNULL && root->right->color == 1)
							{
								os << "[   |";
								string sColor = root->color ? "CRVENO" : "CRNO";
								os << root->s[0] << root->s[1] << root->s[2] <<"-"<< sColor << "|";
								sColor = root->right->color ? "CRVENO" : "CRNO";
								os << root->right->s[0] << root->right->s[1] << root->right->s[2] << "-" <<sColor<< "]" << " " << endl;
							}

					}
					else
					{
						string sColor = root->left->color ? "CRVENO" : "CRNO";
						os <<"["<< root->left->s[0] << root->left->s[1] << root->left->s[2] <<"-"<<sColor<< "|";
					    sColor = root->color ? "CRVENO" : "CRNO";
						os << root->s[0] << root->s[1] << root->s[2] <<"-"<<sColor<< "|";
						sColor = root->right->color ? "CRVENO" : "CRNO";
						os << root->right->s[0] << root->right->s[1] << root->right->s[2] << "-"<<sColor << "]" << endl;

					}
			}

			twoTreePrintHelper(os, root->right, indent, true, num);
		}
}


public:

	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	NodePtr searchTree(int k, string s) {
		return searchTreeHelper(this->root, k, s);
	}
	NodePtr searchTreeString(string s) {
		return searchTreeStringHelper(this->root, s);
	}
	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}
	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	NodePtr predecessor(NodePtr x) {
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	void insert(int key, string s) {
		// Ordinary Binary Search Insertion
		NodePtr node = new Node;
		node->parent = nullptr;
		node->priority = key;
		node->s = s;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // new node must be red

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if ((node->priority < x->priority) || (node->priority == x->priority && node->s.compare(x->s) < 0)) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if ((node->priority < y->priority) || (node->priority == y->priority && node->s.compare(y->s) < 0)) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}
	NodePtr getRoot() {
		return this->root;
	}
	void deleteNode(int priority, string s) {
		deleteNodeHelper(this->root, priority, s);
	}
	void deleteNodePr(int priority) {
		deleteNodePrHelper(this->root, priority);
	}
	void deleteTree() {
		deleteTreeHelper(this->root);
	}
	void redBlackPrint(ostream& os, int num =0) {
		if (root!=TNULL) {
			printHelper(os, this->root, "", true, num);
		}
		else
			cout << "Stablo je prazno. " << endl;
	}
	void changePriority(NodePtr node, int priority) {
		if (node == nullptr || node == TNULL) {
			cout << " Zelite da promenite prioritet nepostojecoj akciji. " << endl;
			return;
		}
		NodePtr n2 = new Node;
		insert(priority, node->s);
		deleteNode(node->priority, node->s);
		cout << " Prioritet uspesno zamenjen." << endl;
	}
	int numberOfPriorities(int pr)
	{
		this->s = 0;
		inOrderHelper(this->root, pr);
		return s;
	}
	void twoTreePrint(ostream& os, int num = 0) {
		if (root!=TNULL) {
			twoTreePrintHelper(os, this->root, "", true,num);
		}
		else
			cout << "Stablo je prazno. " << endl;
	}
	friend ostream& operator<<(ostream& os, const RBTree& bst);

};

ostream& operator<<(ostream& os, RBTree& bst)
{

	if (ch == 1)
		bst.twoTreePrint(os);
	if (ch == 2)
		bst.redBlackPrint(os);

	return os;
}

int main() {



	int start = 1;
	ifstream dat;
	RBTree bst;
	while (start) {

		cout << "---------------------------------------------------------------------" << endl;
		cout << " 0  :  Create an empty Tree.                                     " << endl;
		cout << " 1  :  Load action from console.                                 " << endl;
		cout << " 2  :  Load action from file.                                    " << endl;
		cout << " 3  :  Search action.                                            " << endl;
		cout << " 4  :  Insert action.                                            " << endl;
		cout << " 5  :  Delete action based on priority.                          " << endl;
		cout << " 6  :  Delete highest priority action.                           " << endl;
		cout << " 7  :  Print 2-3-4 Tree.                                         " << endl;
		cout << " 8  :  Print Red-Black Tree.                                     " << endl;
		cout << " 9  :  Change priority of action.                                " << endl;
		cout << " 10  : Search all actions with given priority.                   " << endl;
		cout << " 11  : Delete Tree.                                              " << endl;
		cout << " 12  : End of program.                                           " << endl;
		cout << "---------------------------------------------------------------------" << endl;

		int choice;
		int pr;
		string s;
		NodePtr node = new Node;
		cout << " Vas izbor -> " << endl;
		cin >> choice;


		switch (choice) {

		case 0:

			RBTree();
			break;

		case 1:

			bst.deleteTree();
			cout << "Load action and its priority until you input word STOP : " << endl;
			cin >> s;

			while (s.compare("STOP") != 0) {

				cin >> pr;
				bst.insert(pr, s);
				cin >> s;

			}
			break;

		case 2:

			bst.deleteTree();
			cout << "Insert file name : "; cin >> s;

			dat.open(s);
			if (!dat.is_open())
				cout << "Error loading a file " << endl;
			else
			{
				while (!dat.eof()) {
					dat >> s;
					dat >> pr;
					bst.insert(pr, s);
				}
			}
			dat.close();
			break;

		case 3:

			cout << "Insert action to search : "; cin >> s;
			cout << "Insert its priority : "; cin >> pr;
			if (bst.searchTree(pr, s) != nullptr)cout << " The action exists." << endl;
			else cout << "The action does not exist " << endl;
			break;

		case 4:

			cout << "Insert action which needs to be inserted "; cin >> s;
			cout << " Insert its priority: "; cin >> pr;
			bst.insert(pr, s);
			break;

		case 5:

			cout << "Insert priority of action which you want to delete : "; cin >> pr;
			bst.deleteNodePr(pr);
			break;

		case 6:

			node = bst.maximum(bst.getRoot());
			bst.deleteNode(node->priority, node->s);
			break;

		case 7:

			ch = 1;
			cout << bst;
			v.clear();
			m1.clear();
			m2.clear();
			break;

		case 8:

			ch = 2;
			cout << bst;
			v.clear();
			m1.clear();
			m2.clear();
			break;

		case 9:

			cout << " Insert actioon which you want to change : "; cin >> s;
			cout << " Insert new priority you want to adress to it :  "; cin >> pr;
			bst.changePriority(bst.searchTreeString(s), pr);
			break;

		case 10:

			cout << "Insert priority : "; cin >> pr;
			cout << "Number of actions with that priority -> " << bst.numberOfPriorities(pr) << endl;
			break;

		case 11:

			bst.deleteTree();
			cout << " Tree is successfully deleted. " << endl;
			break;

		case 12:

			start = 0;
			break;


		}
	}


	
	return 0;
}



