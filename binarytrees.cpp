#include<iostream>
#include<queue>
#include<string>
using namespace std;
class Node
{
public:
	int info;
	Node* left;
	Node* right;
	Node(int data)
	{
		info = data;
		left = nullptr;
		right = nullptr;
	}
};
int getValidInput();
Node* BuildTree(Node* root)
{
	int data;
	cout << "Enter Data (-1 for null): ";
	data = getValidInput();
	root = new Node(data);
	//Check if Null
	if (data == -1)
	{
		return nullptr; //no children can be made when node is null
	}
	//else
	cout << "Enter data for left of: " << data << endl;
	root->left = BuildTree(root->left); //calls to enter left of successive nodes until a node has null left child 
	cout << "Enter data for right of: " << data << endl;
	root->right = BuildTree(root->right);
	return root; //root is returned when a node has no left or right children 
}
Node* returnLeftChild(Node* root, int data) {
	if (!root)
	{
		return nullptr;
	}
	if (root->info == data) return root->left;
	Node* leftResult = returnLeftChild(root->left, data);
	if (leftResult) return leftResult;
	return returnLeftChild(root->right, data);
}
Node* returnRightChild(Node* root, int data) {
	if (!root)
	{
		return nullptr;
	}
	if (root->info == data)
	{
		if (root->right)
		{
			return root->right;
		}
	}
	Node* leftResult = returnRightChild(root->left, data);
	if (leftResult) return leftResult;
	return returnRightChild(root->right, data);
}
Node* returnSibling(Node* root, int data) {
	if (!root || !root->left || !root->right)
	{
		return nullptr;
	}
	if (root->left->info == data) return root->right;
	if (root->right->info == data) return root->left;
	Node* leftResult = returnSibling(root->left, data);
	if (leftResult) return leftResult;
	return returnSibling(root->right, data);
}
Node* returnParent(Node* root, int childData) {
	// Base case: if the tree is empty or the root itself is the target
	if (root == nullptr ||
		(root->left && root->left->info == childData) ||
		(root->right && root->right->info == childData))
	{
		return root;
	}

	// Recursively search in the left subtree
	Node* leftResult = returnParent(root->left, childData);
	if (leftResult != nullptr) {
		return leftResult;
	}

	// Recursively search in the right subtree
	return returnParent(root->right, childData);
}
int getValidInput() {
	int value;
	while (true) {
		if (cin >> value)
		{
			break;
		}
		else
		{
			cout << "Enter a valid integer: ";
			cin.clear();            // Clear the error flag
			cin.ignore(123, '\n');  // Discard invalid input
		}
	}
	return value;
}
void LevelOrderTraversal(Node* root)
{
	if (root == NULL) {
		cout << "No Tree to Traverse!" << endl;
	}
	cout << "Tree Right now: " << endl;
	queue<Node*>q;
	q.push(root);
	q.push(NULL); //seperator after level 0
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();
		if (temp == NULL)//shows last level is complete first go to next line
		{                //then again check if not empty push NULL again 
			cout << endl;
			if (!q.empty())
			{
				q.push(NULL);
			}
		}
		else//when temp is not null print its info and push its childs if any
		{
			cout << temp->info << "  ";
			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);
		}
	}
}
void clearScreen() {
#ifdef _WIN32
	system("cls");
#endif
}
int main()
{
	//1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
	string option;
	Node* root=nullptr;
	while (true)
	{
		cout << "Enter\n1. To BuildTree.\n2. To Find Left Chlid of a Node in Tree.\n3. To Find Right Chlid of a Node in Tree.\n4. To find sibling of a Node in Tree.\n5. To find Parent of a Node.\nx. To exit\nEnter Your Choice: ";
		getline(cin, option);
		if (option == "1")
		{
			clearScreen();
			root = BuildTree(root);
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			cout << "\nTree Built Successfully!\n";
			LevelOrderTraversal(root);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean up input
			system("pause"); // Pause for the user to view the output
		}
		else if (option == "2")
		{
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (root == nullptr)
			{
				cout << "Tree not Found! Build a Tree First to find any Node's Left Child" << endl;
				continue;
			}
			cout << "Enter Data of the Node to find its Left Child: ";
			int data = getValidInput();
			Node* ans = returnLeftChild(root, data);
			if (ans == nullptr)
			{
				cout << "The node with data " << data << " either doesn't exist in the tree or has no left child." << endl;
			}
			else
			{
				cout << "Left Child of: " << data << " is: " << ans->info;
			}
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			cin.ignore();
		}
		else if (option == "3")
		{
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (root == nullptr)
			{
				cout << "Tree not Found! Build a Tree First to find any Node's Right Child." << endl;
				continue;
			}
			cout << "Enter Data of the Node to find its Right Child: ";
			int data = getValidInput();
			Node* ans = returnRightChild(root, data);
			if (ans == nullptr)
			{
				cout << "The node with data " << data << " either doesn't exist in the tree or has no right child." << endl;
			}
			else
			{
				cout << "Right Child of: " << data << " is: " << ans->info<<endl;
			}
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			cin.ignore();
		}
		else if (option == "4")
		{
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (root == nullptr)
			{
				cout << "Tree not Found! Build a Tree First to find any Node's Sibling." << endl;
				continue;
			}
			cout << "Enter Data of the Node to find its Sibling: ";
			int data = getValidInput();
			Node* ans = returnSibling(root, data);
			if (ans == nullptr)
			{
				cout << "The node with data " << data << " either doesn't exist in the tree or has no sibling." << endl;
			}
			else
			{
				cout << "Sibling of: " << data << " is: " << ans->info<<endl;
			}
			cin.ignore();
		}
		else if (option == "5")
		{
			clearScreen();
			if (root == nullptr)
			{
				cout << "Tree not Found! Build a Tree First to find any Node's Parent." << endl;
				continue;
			}
			cout << "Enter Data of the Node to find its Parent: ";
			int data = getValidInput();
			Node* ans = returnParent(root, data);
			if (ans == nullptr)
			{
				cout << "The node with data " << data << " either doesn't exist in the tree or has no Parent." << endl;
			}
			else
			{
				cout << "Parent of: " << data << " is: " << ans->info<<endl;
			}
			cin.ignore();
		}
		else if (option == "x")
		{
			cout << "Exiting...\n";
			break;
		}
		else
		{
			clearScreen();
			cout << "Invalid Choice Entered!\n";
			cin.ignore();
		}
	}

}