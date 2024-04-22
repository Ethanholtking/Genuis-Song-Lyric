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
	bool ll;
	bool rr;
	bool rl;
	bool lr;
	red_black_node* root;
	int size;

	//Constructor
	red_black_tree()
	{
		this->root = nullptr;
		bool ll = false;
		bool rr = false;
		bool rl = false;
		bool lr = false;
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
	red_black_node* insertHelp(red_black_node* root, string data);
	void insert(string data);
	red_black_node* right_rot(red_black_node* root);
	red_black_node* left_rot(red_black_node* root);
	red_black_node* get_uncle(red_black_node* root);
	red_black_node* get_grandparent(red_black_node* root);
	string search(red_black_node* root, string target);
	vector<string> in_order_traversal(red_black_node* root, vector<string> titles);
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

red_black_node* red_black_tree::insertHelp(red_black_node* root, string data) {
	bool f = false; // Flag to check RED-RED conflict

	if (root == nullptr)
		return new red_black_node(data);
	else if (data < root->title) {
		root->left = insertHelp(root->left, data);
		root->left->parent = root;
		if (root != this->root) {
			if (root->red == true && root->left->red == true)
				f = true;
		}
	}
	else {
		root->right = insertHelp(root->right, data);
		root->right->parent = root;
		if (root != this->root) {
			if (root->red == true && root->right->red == true)
				f = true;
		}
	}

	// Perform rotations
	if (ll == true)
	{
		root = left_rot(root);
		root->red = false;
		root->left->red = true;
		ll = false;
	}
	else if (rr == true) {
		root = right_rot(root);
		root->red = false;
		root->right->red = true;
		rr = false;
	}
	else if (rl == true) {
		root->right = right_rot(root->right);
		root->right->parent = root;
		root = left_rot(root);
		root->red = false;
		root->left->red = true;
		rl = false;
	}
	else if (lr == true) {
		root->left = left_rot(root->left);
		root->left->parent = root;
		root = right_rot(root);
		root->red = false;
		root->right->red = true;
		lr = false;
	}

	// Handle RED-RED conflicts
	if (f) {
		if (root->parent->right == root) {
			if (root->parent->left == nullptr || root->parent->left->red == false) {
				if (root->left != nullptr && root->left->red == true)
					rl = true;
				else if (root->right != nullptr && root->right->red == true)
					ll = true;
			}
			else {
				root->parent->left->red = false;
				root->red = false;
				if (root->parent != this->root)
					root->parent->red = true;
			}
		}
		else {
			if (root->parent->right == nullptr || root->parent->right->red == false) {
				if (root->left != nullptr && root->left->red == true)
					rr = true;
				else if (root->right != nullptr && root->right->red == true)
					lr = true;
			}
			else {
				root->parent->right->red = false;
				root->red = false;
				if (root->parent != this->root)
					root->parent->red = true;
			}
		}
		f = false;
	}
	return root;
}

void red_black_tree::insert(string data) {
	if (root == nullptr) {
		root = new red_black_node(data);
		root->red = false;
	}
	else
		root = insertHelp(root, data);
}

red_black_node* red_black_tree::right_rot(red_black_node* node) {
	red_black_node* x = node->left;
	red_black_node* y = x->right;
	x->right = node;
	node->left = y;
	node->parent = x;
	if (y != nullptr)
		y->parent = node;
	return x;
}

red_black_node* red_black_tree::left_rot(red_black_node* node) {
	red_black_node* x = node->right;
	red_black_node* y = x->left;
	x->left = node;
	node->right = y;
	node->parent = x;
	if (y != nullptr)
		y->parent = node;
	return x;
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

vector<string> red_black_tree::in_order_traversal(red_black_node* root, vector<string> titles)
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
		if (root->title.find(target))
			percent++;
		percent = get_song_titles(root->right, percent, target);
	}
	return percent;
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