#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

struct red_black_node
{
public:
	// Variables for the node
	bool red;
	string title;
	red_black_node* left;
	red_black_node* right;
	red_black_node* parent;

	// Constructor
	red_black_node(string title)
	{
		this->title = title;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		red = true;
	}
};

struct red_black_tree
{
	red_black_node* root;
    int size;

	//Constructor
	red_black_tree()
	{
		this->root = nullptr;
        this->size = 0;
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
	// Desturctor from clemson uni
	~red_black_tree()
	{
		deleteTree(root);
	}
	void deleteTree(red_black_node* curr)
	{
		if (curr == nullptr)
			return;
		deleteTree(curr->left);
		deleteTree(curr->right);
		delete curr;
	}
	string to_lower(string title);
	red_black_node* insert_node(red_black_node* root, string title);
	void right_rot(red_black_node* root);
	void left_rot(red_black_node* root);
	red_black_node* get_uncle(red_black_node* root);
	red_black_node* get_grandparent(red_black_node* root);
	string balance(red_black_node* root);
	string search(red_black_node* root, string target);
	vector<string> in_order_traversal(red_black_node* root, vector<string> &titles);
	float get_song_titles(red_black_node* root, float percent, string target);
	map<string, float> update_map(map<string, float> freq, string title);
	map<string, float> freq_of_words(red_black_node* root, map<string, float> freq);
	vector<pair<string, float>> most_used_words(map<string, float> freq);
};

string red_black_tree::to_lower(string title)
{
	for (int i = 0; i < title.length(); i++)
		title[i] = tolower(title[i]);
	return title;
}

red_black_node* red_black_tree::insert_node(red_black_node* root, string title)
{
	string rot;
	red_black_node* prev;
	red_black_node* prev_left;
	red_black_node* prev_right;
	title = to_lower(title);
	// If the tree is empty
	if (this->root == nullptr)
	{
		red_black_node* tree_root = new red_black_node(title);
		tree_root->red = false;
        this->root = tree_root;
		return tree_root;
	}
	// inserts a node
	if (root == nullptr)
		return new red_black_node(title);
	// Inserts a node to the left
	else if (title < root->title)
	{
		prev = root->parent;
		prev_left = root->left;
		prev_right = root->right;
		root->left = insert_node(root->left, title);
		// Updates the left nodes parent
		if (root->left != nullptr)
			root->left->parent = root;
		rot = balance(root->left);
		// Changes the return node if a rotation occured
		if (rot != "" || root->parent != prev)
		{
			if (rot == "l")
				return root->left->right;
			if (rot == "r")
				return root->right->left;
			else if (rot == "lr")
				return root->parent->right->left;
			else if (rot == "rl")
				return root->parent->left->right;
			else if (root->parent != prev)
				return root->parent;
		}
	}
	// Inserts a node to the right
	else if (title > root->title)
	{
		prev = root->parent;
		prev_left = root->left;
		prev_right = root->right;
		root->right = insert_node(root->right, title);
		// Updates the right nodes parent
		if (root->right != nullptr)
			root->right->parent = root;
		rot = balance(root->right);
		// Changes the return node if a rotation occured
		if (rot != "" || root->parent != prev)
		{
			if (rot == "l")
				return root->left->right;
			if (rot == "r")
				return root->right->left;
			else if (rot == "lr")
				return root->parent->right->left;
			else if (rot == "rl")
				return root->parent->left->right;
			else if (root->parent != prev)
				return root->parent;
		}
	}
    size++;
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
	}
	else if (grandparent != nullptr)
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
	return rot;
}
string red_black_tree::search(red_black_node* root, string target)
{
	if (root == nullptr)
		return "";
	if (root->title == target)
		return target;
	else if (root->title < target)
		return search(root->left, target);
	else if (root->title > target)
		return search(root->right, target);
}

vector<string> red_black_tree::in_order_traversal(red_black_node* root, vector<string> &titles)
{
	if (root != nullptr)
	{
		titles = in_order_traversal(root->left, titles);
		titles.push_back(root->title);
		titles = in_order_traversal(root->right, titles);
	}
	return titles;
}

float red_black_tree::get_song_titles(red_black_node* root, float percent, string target)
{
	if (root != nullptr)
	{
		percent = get_song_titles(root->left, percent, target);
        stringstream songTitle(root->title);
        string singleWord;
        bool alreadyContains = false;
        while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
            if (!alreadyContains) {
                if (target == singleWord) {
                    percent++;
                    alreadyContains = true;
                }
            }
        }
		percent = get_song_titles(root->right, percent, target);
	}
	return (float)percent / (float)size;
}

map<string, float> red_black_tree::update_map(map<string, float> freq, string title)
{
	string curr = "";
	for (int i = 0; i < title.length(); i++)
	{
		if (title[i] != (char)' ')
			curr += title[i];
		else
		{
			if (freq.find(curr) != freq.end())
			{
				freq[curr] += 1;
				curr = "";
			}
			else
			{
				freq.emplace(curr, 1);
				curr = "";
			}
		}
	}
	if (freq.find(curr) != freq.end())
		freq[curr] += 1;
	else
		freq.emplace(curr, 1);
	return freq;
}

map<string, float> red_black_tree::freq_of_words(red_black_node* root, map<string, float> freq)
{
	if (root != nullptr)
	{
		freq = freq_of_words(root->left, freq);
		freq = update_map(freq, root->title);
		freq = freq_of_words(root->right, freq);
	}
    for (auto &item : freq) {
        item.second /= (float)size;
    }
	return freq;
}

vector<pair<string, float>> red_black_tree::most_used_words(map<string, float> freq)
{
	priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> pq;
	auto it = freq.begin();
	for (; it != freq.end(); ++it)
	{
		if (pq.size() < 5)
			pq.emplace(make_pair(it->second, it->first));
		else if (it->second > pq.top().first)
		{
			pq.pop();
			pq.emplace(make_pair(it->second, it->first));
		}
		else
			continue;
	}
	vector<pair<string, float>> most_used(5);
	vector<pair<string, float>> most_used_r(5); // Most used in reverse order
	for (int i = 0; i < 5; i++)
	{
		pair<string, float> word = make_pair(pq.top().second, pq.top().first);
		most_used_r[i] = word;
		pq.pop();
	}
	for (int i = 0; i < 5; i++)
	{
		most_used[i] = most_used_r[most_used_r.size() - (i + 1)];
	}
	return most_used;
}