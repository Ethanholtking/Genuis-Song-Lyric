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
	
public:
	// Constructor
	red_black_node(string artist, string title) 
	{
		this->title = title;
		this->artist = artist;
		left = nullptr;
		reight = nullptr;
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
	red_black_tree* insert_node(red_black_node* root, string artist, string title);
};


red_black_tree* red_black_tree::insert_node(red_black_node* root, string artist, string title) 
{
	// Checks if the tree is empty
	if(root == nullptr) 
	{
		return new red_black_node(artist, title);
	}
	if(artist < root->artist) 
	{
		root->left = insert_node(root, artist, title);
	}
	if(artist > root->artist) 
	{
		root->right = insert_node(root, artist, title);
	}
}