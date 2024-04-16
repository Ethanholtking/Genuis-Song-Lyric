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
	void right_rot(red_black_node* root);
	void left_rot(red_black_node* root);
	red_black_node* get_uncle(red_black_node* root);
	red_black_node* get_grandparent(red_black_node* root);
	void balance(red_black_node* root);
};


red_black_node* red_black_tree::insert_node(red_black_node* root, string artist, string title)
{
	// inserts a node
	if (root == nullptr)
	{
		return new red_black_node(artist, title);
	}
	if (artist < root->artist)
	{
		root->left = insert_node(root, artist, title);
		root->left->parent = root;
	}
	if (artist > root->artist)
	{
		root->right = insert_node(root, artist, title);
		root->right->parent = root;
	}

	balance(root);
}

// Right rotation
void red_black_tree::right_rot(red_black_node* root)
{
	red_black_node* save = root->left->right;
	red_black_node* new_root = root->left;
	root->left->right = root;
	root->left = save;
}

// Left rotation
void red_black_tree::left_rot(red_black_node* root)
{
	red_black_node* save = root->right->left;
	red_black_node* new_root = root->right;
	root->right->left = root;
	root->right = save;
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
	if (root->parent == nullptr)
	{
		root->red = false;
		return;
	}
	if (root->parent->red == false)
		return;
	red_black_node* parent = root->parent;
	red_black_node* grandparent = get_grandparent(root);
	red_black_node* uncle = get_uncle(root);
	if (uncle != nullptr && uncle->red == true)
	{
		parent->red = uncle->red = false;
		grandparent->red = true;
		balance(grandparent);
		return;
	}
	if (root == parent->right && parent == grandparent->left)
	{
		left_rot(parent);
		root = parent;
		parent = root->parent;
	}
	else if (root == parent->left && parent == grandparent->right)
	{
		right_rot(parent);
		root = parent;
		parent = root->parent;
	}
	parent->red = false;
	grandparent->red = true;
	if (root == parent->left)
		right_rot(grandparent);
	else
		left_rot(grandparent);
}