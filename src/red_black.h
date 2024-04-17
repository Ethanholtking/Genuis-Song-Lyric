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
	red_black_node* right_rot(red_black_node* root);
	red_black_node* left_rot(red_black_node* root);
	red_black_node* get_uncle(red_black_node* root);
	red_black_node* get_grandparent(red_black_node* root);
	red_black_node* balance(red_black_node* root);
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

	return root;
}

// Right rotation
red_black_node* red_black_tree::right_rot(red_black_node* root)
{
	cout << "right rotation\n";
	cout << "root: " << root->title << endl;
	red_black_node* saved = root->left->right;
	root->left->parent = root->parent;
	if (root->parent->right == root)
		root->parent->right = root->left;
	else
		root->parent->left = root->left;
	root->parent = root->left;
	root->left->right = root;
	root->left = saved;
	if (root->left != nullptr)
	{
		root->left->parent = root;
	}
	return root->parent;
}

// Left rotation
red_black_node* red_black_tree::left_rot(red_black_node* root)
{
	cout << "left rotation\n";
	cout << "root: " << root->title << endl;
	red_black_node* saved = root->right->left;
	root->right->parent = root->parent;
	if (root->parent->right == root)
		root->parent->right = root->right;
	else
		root->parent->left = root->right;
	root->parent = root->right;
	root->right->left = root;
	root->right = saved;
	if (root->right != nullptr)
	{
		root->right->parent = root;
	}
	return root->parent;
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
red_black_node* red_black_tree::balance(red_black_node* root)
{
	// If the root is red make it black
	if (root->parent == nullptr)
	{
		root->red = false;
		return root;
	}
	// If the parent is not red
	if (root->parent->red == false)
		return root;
	red_black_node* parent = root->parent;
	red_black_node* grandparent = get_grandparent(root);
	red_black_node* uncle = get_uncle(root);
	if (uncle != nullptr && uncle->red == true)
	{
		cout << "color switch" << endl;
		cout << "root: " << root->title << endl;
		cout << "parent: " << root->parent->title << endl;
		parent->red = false;
		uncle->red = false;
		grandparent->red = true;
		balance(grandparent);
		return root;
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
			return right_rot(grandparent);
		else
		{
			return left_rot(grandparent);
		}
	}
}