#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct tree
{
	int data;
	tree* left;
	tree* right;
};

void add(tree*& top, int x)
{
	if (!top)
	{
		top = new tree;
		top->data = x;
		top->left = NULL;
		top->right = NULL;
		return;
	}
	if (x < top->data)
		add(top->left, x);
	else
		add(top->right, x);
}

void Create(ifstream& f, tree*& top)
{
	int x;
	while (f.peek() != EOF)
	{
		f >> x;
		add(top, x);
	}
}

// 1
void preorder(tree* top, vector<int>& result)
{
	if (!top)
		return;
	result.push_back(top->data);
	preorder(top->left, result);
	preorder(top->right, result);
}
vector<int> preorder_begin(tree* top)
{
	vector<int> result;
	preorder(top, result);
	return result;
}
// 2
void postorder(tree* root, vector<int>& result)
{
	if (!root)
		return;

	postorder(root->left, result);
	postorder(root->right, result);
	result.push_back(root->data);
}
vector<int> postorder_begin(tree* root)
{
	vector<int> result;
	postorder(root, result);
	return result;
}
// 3
bool is_BST(tree* root, long min, long max)
{
	if (root == NULL)
		return true;
	if (root->data <= min || root->data >= max)
		return false;
	return is_BST(root->left, min, root->data) && is_BST(root->right, root->data, max);
}
bool is_tree_BST(tree* root)
{
	if (root == NULL)
		return true;
	return is_BST(root, LONG_MIN, LONG_MAX);
}
// 4
tree* min_Value(tree* root) 
{
	tree* current = root;
	while (current && current->left != nullptr)
		current = current->left;
	return current;
}
tree* delete_x(tree* root, int data) {
	if (root == nullptr) {
		return root;
	}
	if (data < root->data) {
		root->left = delete_x(root->left, data);
	}
	else if (data > root->data) {
		root->right = delete_x(root->right, data);
	}
	else 
	{
		if (root->left == nullptr) {
			tree* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			tree* temp = root->left;
			delete root;
			return temp;
		}
		tree* temp = min_Value(root->right);
		root->data = temp->data;
		root->right = delete_x(root->right, temp->data);
	}
	return root;
}

bool isEmpty(tree* root)
{
	return root == NULL;
}
int main()
{
	ifstream fin("input.txt");
	tree* top = NULL;
	Create(fin, top);
	vector<int> pre = preorder_begin(top);
	cout << "preorder:\n";
	for (int i = 0; i < pre.size(); i++)
		cout << pre[i] << " ";
	cout << endl;

	vector<int> post = postorder_begin(top);
	cout << "postorder:\n";
	for (int i = 0; i < post.size(); i++)
		cout << post[i] << " ";
	cout << endl;

	cout << "is_tree_BST: " << is_tree_BST(top) << endl;

	int x;
	cout << "x = ";
	cin >> x;
	top = delete_x(top, x);
	pre = preorder_begin(top);
	cout << "preorder:\n";
	for (int i = 0; i < pre.size(); i++)
		cout << pre[i] << " ";
	cout << endl;
	return 0;
}