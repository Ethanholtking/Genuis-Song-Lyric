#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <stack>
#include <map>
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
	bool l;
	bool r;
	bool rl;
	bool lr;
	red_black_node* root;
	int size = 0;

	//Constructor
	red_black_tree()
	{
		this->root = nullptr;
		bool l = false;
		bool r = false;
		bool rl = false;
		bool lr = false;
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
	red_black_node* insert_node(red_black_node* root, string& title);
	void insert(string& title);
	red_black_node* right_rot(red_black_node* root);
	red_black_node* left_rot(red_black_node* root);
	string search(red_black_node* root, string& target, string title);
	vector<string> in_order_traversal(red_black_node* root, vector<string>& titles);
	float get_song_titles(red_black_node* root, float& percent, string& target);
	map<string, float> update_map(map<string, float>& freq, string& title);
	map<string, float> freq_of_words(red_black_node* root, map<string, float>& freq);
	vector<pair<string, float>> most_used_words(map<string, float>& freq);
	vector<pair<string, float>> mostUsedWords();
	vector<red_black_node*> getAllNodes();
};

string red_black_tree::to_lower(string title)
{
	for (int i = 0; i < title.length(); i++)
		title[i] = tolower(title[i]);
	return title;
}
//Inspired by geeks for geeks
red_black_node* red_black_tree::insert_node(red_black_node* root, string& title) {
	bool red_red = false; // Flag to check RED-RED conflict

	// Insertes a node into the tree
	if (root == nullptr)
		return new red_black_node(title);
	// Inserts a node on the left branch
	else if (title < root->title)
	{
		root->left = insert_node(root->left, title);
		root->left->parent = root;
		if (root != this->root)
		{
			if (root->red == true && root->left->red == true)
				red_red = true;
		}
	}
	// Inserts a node on the right branch
	else
	{
		root->right = insert_node(root->right, title);
		root->right->parent = root;
		if (root != this->root)
		{
			if (root->red == true && root->right->red == true)
				red_red = true;
		}
	}

	// Perform rotations
	if (l == true)
	{
		root = left_rot(root);
		root->red = false;
		root->left->red = true;
		l = false;
	}
	else if (r == true)
	{
		root = right_rot(root);
		root->red = false;
		root->right->red = true;
		r = false;
	}
	else if (rl == true)
	{
		root->right = right_rot(root->right);
		root->right->parent = root;
		root = left_rot(root);
		root->red = false;
		root->left->red = true;
		rl = false;
	}
	else if (lr == true)
	{
		root->left = left_rot(root->left);
		root->left->parent = root;
		root = right_rot(root);
		root->red = false;
		root->right->red = true;
		lr = false;
	}

	// Handle RED-RED conflicts
	if (red_red)
	{
		// If the root is a right child
		if (root->parent->right == root)
		{
			// If the uncle is black (rotation)
			if (root->parent->left == nullptr || root->parent->left->red == false)
			{
				if (root->left != nullptr && root->left->red == true)
					rl = true;
				else if (root->right != nullptr && root->right->red == true)
					l = true;
			}
			// If the uncle is red (Color flip)
			else
			{
				root->parent->left->red = false;
				root->red = false;
				if (root->parent != this->root)
					root->parent->red = true;
			}
		}
		// If the root is a left child
		else
		{
			// If the uncle is black (rotation)
			if (root->parent->right == nullptr || root->parent->right->red == false)
			{
				if (root->left != nullptr && root->left->red == true)
					r = true;
				else if (root->right != nullptr && root->right->red == true)
					lr = true;
			}
			// If the uncle is red (color flip)
			else
			{
				root->parent->right->red = false;
				root->red = false;
				if (root->parent != this->root)
					root->parent->red = true;
			}
		}
		red_red = false;
	}
	return root;
}

void red_black_tree::insert(string& title) {
	title = to_lower(title);
	if (root == nullptr) {
		root = new red_black_node(title);
		root->red = false;
	}
	else
		root = insert_node(root, title);
	size++;
}

red_black_node* red_black_tree::right_rot(red_black_node* node) {
	red_black_node* new_root = node->left;
	red_black_node* saved = new_root->right;
	new_root->right = node;
	node->left = saved;
	node->parent = new_root;
	if (saved != nullptr)
		saved->parent = node;
	return new_root;
}

red_black_node* red_black_tree::left_rot(red_black_node* node) {
	red_black_node* new_root = node->right;
	red_black_node* saved = new_root->left;
	new_root->left = node;
	node->right = saved;
	node->parent = new_root;
	if (saved != nullptr)
		saved->parent = node;
	return new_root;
}

string red_black_tree::search(red_black_node* root, string& target, string title)
{
	if (root != nullptr)
	{
		if (root->title == target)
			title = target;
		title = search(root->left, target, title);
		title = search(root->right, target, title);
	}
	return title;
}

vector<string> red_black_tree::in_order_traversal(red_black_node* root, vector<string>& titles)
{
	if (root != nullptr)
	{
		titles = in_order_traversal(root->left, titles);
		titles.push_back(root->title);
		titles = in_order_traversal(root->right, titles);
	}
	return titles;
}

float red_black_tree::get_song_titles(red_black_node* root, float& percent, string& target)
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
	return percent;
}

map<string, float> red_black_tree::update_map(map<string, float>& freq, string& title)
{
	stringstream songTitle(title);
	string singleWord;
	vector<string> alreadyContains;
	while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
		if (find(alreadyContains.begin(), alreadyContains.end(), singleWord) == alreadyContains.end()) {
			if (freq.find(singleWord) != freq.end()) {
				freq[singleWord]++;
				alreadyContains.push_back(singleWord);
			}
			else {
				freq.emplace(singleWord, 1);
				alreadyContains.push_back(singleWord);
			}
		}
	}
	return freq;
}

map<string, float> red_black_tree::freq_of_words(red_black_node* root, map<string, float>& freq)
{
	if (root != nullptr)
	{
		freq = freq_of_words(root->left, freq);
		stringstream songTitle(root->title);
		string singleWord;
		while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
			if (freq.find(singleWord) != freq.end()) {
				freq[singleWord]++;
			}
			else {
				freq.emplace(singleWord, 1);
			}
		}
		freq = freq_of_words(root->right, freq);
	}
	return freq;
}

vector<pair<string, float>> red_black_tree::most_used_words(map<string, float>& freq)
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

vector<pair<string, float>> red_black_tree::mostUsedWords() {
	vector<red_black_node*> nodes = getAllNodes();
	unordered_map<string, int> words;
	for (auto& node : nodes) { // iterates through list (chaining) to find song
		stringstream songTitle(node->title);
		string singleWord;
		vector<string> alreadyContains;
		while (songTitle >> singleWord) { // place all words in title into map to store words and frequencies
			if (find(alreadyContains.begin(), alreadyContains.end(), singleWord) == alreadyContains.end()) {
				if (words.find(singleWord) != words.end()) {
					words[singleWord]++;
					alreadyContains.push_back(singleWord);
				}
				else {
					words.emplace(singleWord, 1);
					alreadyContains.push_back(singleWord);
				}
			}
		}
	}
	priority_queue<pair<int, string>> pQueue;
	for (auto& word : words) {
		pQueue.emplace(word.second, word.first);
	}
	vector<pair<string, float>> topFive;
	for (int i = 0; i < 5; i++) {
		pair<int, string> greatestWord = pQueue.top();
		pQueue.pop();
		topFive.emplace_back(greatestWord.second, ((float)greatestWord.first / (float)size));
	}
	return topFive;
}

vector<red_black_node*> red_black_tree::getAllNodes() {
	vector<red_black_node*> data;
	stack<red_black_node*> nodes;
	red_black_node* current = this->root;

	while (current != nullptr || !nodes.empty()) {
		while (current != nullptr) {
			nodes.push(current);
			current = current->left;
		}

		// Current must be NULL at this point
		current = nodes.top();
		nodes.pop();

		data.push_back(current);

		current = current->right;

	}
	return data;
}