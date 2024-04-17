#include <iostream>
#include <string>
using namespace std;

class red_black_node
{
public:
	// Variables for the nide
	bool red;
	string artist;
	string title;
	red_black_node* left;
	red_black_node* right;
	red_black_node* parent;

	// Constructor
	red_black_node(string artist, string title)
	{
		this->title = title;
		this->artist = artist;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		red = true;
	}
};

class red_black_tree
{
	red_black_node* root;
public:
	//Constructor
	red_black_tree()
	{
		this->root = nullptr;
	}
	// Getter
	red_black_node* get_root()
	{
		return this->root;
	}
	// Setter
	void set_root(red_black_node* root)
	{
		this->root = root;
	}
	red_black_node* insert_node(red_black_node* root, string artist, string title);
	void right_rot(red_black_node* root);
	void left_rot(red_black_node* root);
	red_black_node* get_uncle(red_black_node* root);
	red_black_node* get_grandparent(red_black_node* root);
	void balance(red_black_node* root);
};


red_black_node* red_black_tree::insert_node(red_black_node* root, string artist, string title)
{
	// If the tree is empty
	if (this->root == nullptr)
	{
		red_black_node* tree_root = new red_black_node(artist, title);
		tree_root->red = false;
		return tree_root;
	}
	// inserts a node
	if (root == nullptr)
	{
		return new red_black_node(artist, title);
	}
	else if (title < root->title)
	{
		root->left = insert_node(root->left, artist, title);
		root->left->parent = root;
		balance(root->left);
	}
	else if (title > root->title)
	{
		root->right = insert_node(root->right, artist, title);
		root->right->parent = root;
		balance(root->right);
	}

	//balance(root);
	return root;
}

// Right rotation
void red_black_tree::right_rot(red_black_node* root)
{
	cout << "right rotation\n";
	cout << "root: " << root->title << endl;
	red_black_node* saved = root->left;
	root->left = saved->right;
	if (saved->right != nullptr)
	{
		saved->right->parent = root;
		root->left = saved->right;
	}
	if (root->parent == nullptr)
	{
		saved->right = root;
		saved->parent = nullptr;
		return;
	}
	saved->parent = root->parent;
	if (root->parent->left == root)
		root->parent->left = saved;
	else
		root->parent->right = saved;
	saved->right = root;
	root->parent = saved;
	root->red = true;
}

// Left rotation
void red_black_tree::left_rot(red_black_node* root)
{
	cout << "left rotation\n";
	cout << "root: " << root->title << endl;
	red_black_node* saved = root->right;
	root->right = saved->left;
	if (saved->left != nullptr)
	{
		saved->left->parent = root;
		root->right = saved->left;
	}
	if (root->parent == nullptr)
	{
		saved->left = root;
		saved->parent = nullptr;
		return;
	}
	saved->parent = root->parent;
	if (root->parent->left == root)
		root->parent->left = saved;
	else
		root->parent->right = saved;
	saved->left = root;
	root->parent = saved;
	root->red = true;
}

red_black_node* red_black_tree::get_uncle(red_black_node* root)
{
	red_black_node* grandparent = get_grandparent(root);
	// root is the root of the tree or is child of the tree's root
	if (root->parent == nullptr || grandparent == nullptr)
		return nullptr;
	else
	{
		// If the grandparents left child is the root's parent
		if (grandparent->left == root->parent)
			return grandparent->right;
		else
			return grandparent->left;
	}
}

red_black_node* red_black_tree::get_grandparent(red_black_node* root)
{
	// root is the root of the tree
	if (root->parent == nullptr)
		return nullptr;
	// root is child of the tree's root
	else if (root->parent->parent == nullptr)
		return nullptr;
	return root->parent->parent;
}

// Balancing
void red_black_tree::balance(red_black_node* root)
{
	// If the root is red make it black
	if (root->parent == nullptr)
	{
		root->red = false;
		return;
	}
	// If the parent is not red
	if (root->parent->red == false)
		return;
	red_black_node* parent = root->parent;
	red_black_node* grandparent = get_grandparent(root);
	red_black_node* uncle = get_uncle(root);
	if (uncle != nullptr && uncle->red == true)
	{
		parent->red = false;
		uncle->red = false;
		grandparent->red = true;
		balance(grandparent);
		return;
	}
	if (grandparent != nullptr)
	{
		if (grandparent->left != nullptr)
		{
			if (root == parent->right && parent == grandparent->left)
			{
				left_rot(parent);
				root = parent;
				parent = root->parent;
			}
		}
		else if (grandparent->right != nullptr)
		{
			if (root == parent->left && parent == grandparent->right)
			{
				right_rot(parent);
				root = parent;
				parent = root->parent;
			}
		}
		parent->red = false;
		grandparent->red = true;
		if (root == parent->left)
			right_rot(grandparent);
		else
		{
			left_rot(grandparent);
			cout << "grandparent: " << grandparent->title << endl;
			cout << "root: " << grandparent->parent->title << " and " << parent->title << endl;
		}
	}
}