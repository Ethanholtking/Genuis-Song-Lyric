#include <iostream>
#include <string>
using namespace std;

class red_black_node
{
public:
	// Variables for the node
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
	string balance(red_black_node* root);
	red_black_node* search(red_black_node* root, string target);
};


red_black_node* red_black_tree::insert_node(red_black_node* root, string artist, string title)
{
	string rot;
	red_black_node* prev;
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
	// Inserts a node to the left
	else if (title < root->title)
	{
		prev = root->parent;
		root->left = insert_node(root->left, artist, title);
		// Updates the left nodes parent
		if (root->left != nullptr)
			root->left->parent = root;
		rot = balance(root->left);
		// Changes the return node if a rotation occured
		if (rot != "" || root->parent != prev)
		{
			if (rot == "cr")
				return root;
			if (rot == "l")
				return root->left->right;
			if (rot == "r")
				return root->right->left;
			else if (rot == "lr")
				return root->parent->right->left;
			else if (rot == "rl")
				return root->parent->left->right;
			else if (root->parent == nullptr && get_root() == root->left)
				return root->left->right;
			else if (root->parent == nullptr && get_root() == root->right)
				return root->right->left;
			else if (root->parent != prev)
				return root->parent;
		}
	}
	// Inserts a node to the right
	else if (title > root->title)
	{
		prev = root->parent;
		root->right = insert_node(root->right, artist, title);
		// Updates the right nodes parent
		if (root->right != nullptr)
			root->right->parent = root;
		rot = balance(root->right);
		// Changes the return node if a rotation occured
		if (rot != "" || root->parent != prev)
		{
			if (rot == "cr")
				return root;
			if (rot == "l")
				return root->left->right;
			if (rot == "r")
				return root->right->left;
			else if (rot == "lr")
				return root->parent->right->left;
			else if (rot == "rl")
				return root->parent->left->right;
			else if (root->parent == nullptr && get_root() == root->left)
				return root->left->right;
			else if (root->parent == nullptr && get_root() == root->right)
				return root->right->left;
			else if (root->parent != prev)
				return root->parent;
		}
	}
	return root;
}

// Right rotation
void red_black_tree::right_rot(red_black_node* root)
{
	red_black_node* saved = root->left->right;
	root->left->parent = root->parent;
	// rotation at the root
	if (root->parent == nullptr)
		root->left->parent = nullptr;
	// Updating parents child
	else if (root->parent->right == root)
		root->parent->right = root->left;
	else
		root->parent->left = root->left;
	// Updating node pointers
	root->parent = root->left;
	root->left->right = root;
	root->left = saved;
	// Udpates the saved nodes parent if it is not null
	if (root->left != nullptr)
		root->left->parent = root;
	return;
}

// Left rotation
void red_black_tree::left_rot(red_black_node* root)
{
	red_black_node* saved = root->right->left;
	root->right->parent = root->parent;
	// rotation at the root
	if (root->parent == nullptr)
		root->right->parent = nullptr;
	// Updating parents child
	else if (root->parent->right == root)
		root->parent->right = root->right;
	else
		root->parent->left = root->right;
	// Updating node pointers
	root->parent = root->right;
	root->right->left = root;
	root->right = saved;
	// Udpates the saved nodes parent if it is not null
	if (root->right != nullptr)
		root->right->parent = root;
	return;
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
string red_black_tree::balance(red_black_node* root)
{
	string rot = "";
	// If the root is a null pointer no changes need to be made
	if (root == nullptr)
		return rot;
	// If the root is red make it black
	if (root->parent == nullptr)
	{
		root->red = false;
		return rot;
	}
	// If the parent is not red or the root itself is black no changes needed
	if (root->parent->red == false || root->red == false)
		return rot;
	red_black_node* parent = root->parent;
	red_black_node* grandparent = get_grandparent(root);
	red_black_node* uncle = get_uncle(root);
	// Color fliping
	if (uncle != nullptr && uncle->red == true)
	{
		parent->red = false;
		uncle->red = false;
		grandparent->red = true;
		rot = balance(grandparent);
		if (rot != "")
			return "cr";
		else
			return "";
	}
	if (grandparent != nullptr)
	{
		if (grandparent->left != nullptr)
		{
			// Left-right rotation
			if (root == parent->right && parent == grandparent->left)
			{
				left_rot(parent);
				root = parent;
				parent = root->parent;
				rot = "lr";
			}
		}
		else if (grandparent->right != nullptr)
		{
			// Right-left rotation
			if (root == parent->left && parent == grandparent->right)
			{
				right_rot(parent);
				root = parent;
				parent = root->parent;
				rot = "rl";
			}
		}
		// Changes rotated node colors
		parent->red = false;
		grandparent->red = true;
		// right rotation
		if (root == parent->left)
		{
			right_rot(grandparent);
			// If it is not a left right rotation, then it is a right
			if (rot == "")
				rot = "r";
			return rot;
		}
		// left rotation
		else
		{
			left_rot(grandparent);
			// If it is not a right left rotation, then it is a left
			if (rot == "")
				rot = "l";
			return rot;
		}
	}
}

red_black_node* red_black_tre::search(red_black_node* root, string target) 
{
	if (root == nullptr) 
	{
		cout << "Unsuccesful\n";
		return nullptr;
	}
	if (root->title == target)
		return root;
	else if (root->title < target)
		return search(root->left, target);
	else if (root->title > target)
		return search(root->right, target);
}