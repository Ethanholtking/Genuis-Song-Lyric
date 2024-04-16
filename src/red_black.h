#include <string>
using namespace std;

class red_black_node 
{
	bool red;
	string artist;
	string title;
	
public:
	red_black_node(string artist, string title) 
	{
		this->title = title;
		this->artist = artist;
		red = true;
	}
};