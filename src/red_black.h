#include <string>
using namespace std;

class red_black_node 
{
	// Variables for the nide
	bool red;
	string artist;
	string title;
	red_black_node* left;
	red_black_node* right;
	red_black_node* parent;
	
public:
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
		root = nullptr;
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
	red_black_node* color_flip(red_black_node* root);
};


red_black_node* red_black_tree::insert_node(red_black_node* root, string artist, string title) 
{
	// inserts a node
	if(root == nullptr) 
	{
		return new red_black_node(artist, title);
	}
	if(artist < root->artist) 
	{
		root->left = insert_node(root, artist, title);
		root->left->parent = root;
	}
	if(artist > root->artist) 
	{
		root->right = insert_node(root, artist, title);
		root->right->parent = root;
	}
}

// Right rotation
red_black_node* red_black_tree::right_rot(red_black_node* root)
{
	Node* save = root->left->right;
	Node* new_root = root->left;
	root->left->right = root;
	root->left = save;
	return new_root;
}

// Left rotation
red_black_node* red_black_tree::left_rot(red_black_node* root)
{
	Node* save = root->right->left;
	Node* new_root = root->right;
	root->right->left = root;
	root->right = save;
	return new_root;
}

// Color switch
red_black_node* red_black_tree::color_flip(red_black_node* root) 
{
	root->red = true;
	root->left->red = false;
	root->right->red = false;
}

red_black_node* red_black_tree::get_uncle(red_black_node* root) 
{
	red_black_node grandparent = get_grandparent(root);
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
	else if (root->parent->parent = = nullptr)
		return nullptr;
	return root->parent->parent;
}