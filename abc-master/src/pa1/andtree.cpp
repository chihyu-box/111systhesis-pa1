#include "andtree.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <algorithm>
using namespace std;

struct Node
{
	string name;
	int level;
	string fanin0 = "-1";
	int phase0 = -1;
	string fanin1 = "-1";
	int phase1 = -1;
	int fanout_num = 0;
};

unordered_map<string, Node> parser(char * s);
void print_aig_hstable(unordered_map<string, Node> &aig_hstable);
void bfs(unordered_map<string, Node> &aig_hstable, vector<Node> &sorted_aig, int num);
vector<Node> sorted_aig_by_level(unordered_map<string, Node> &aig_hstable);
void setFanouts(unordered_map<string, Node> &aig_hstable);
void print(vector<Node> &group, int input_size);
bool node_level_cmp(const Node& a, const Node& b);
void print_sorted_aig(vector<Node> &sorted_aig);

void ilovecplusplus(char *s, int num)
{
	unordered_map<string, Node> aig_hstable = parser(s);
	vector<Node> sorted_aig = sorted_aig_by_level(aig_hstable);
	setFanouts(aig_hstable);
	//print_sorted_aig(sorted_aig);
	bfs(aig_hstable, sorted_aig, num);
}

unordered_map<string, Node> parser(char * s)
{	
	unordered_map<string, Node> aig_hstable;

	stringstream ss;
	ss << s;

	string line;
	string nodename;
	while (getline(ss, line, ';')) 
	{
		Node node;
        if (line.empty()) continue;

        istringstream iss(line);
        string word;
        int stage = 0;
        while (iss >> word) {
        	switch(stage)
        	{
        	case 0:
        		node.name = word;
        		nodename = word;
        		stage++;
        		break;
        	case 1:
        		node.level = stoi(word);
        		stage++;
        		break;
        	case 2:
        		node.fanin0 = word;
        		stage++;
        		break;
        	case 3:
        		node.phase0 = stoi(word);
        		stage++;
        		break;
        	case 4:
        		node.fanin1 = word;
        		stage++;
        		break;
        	case 5:
        		node.phase1 = stoi(word);
        		stage++;
        		break;  
        	} 
        }
        aig_hstable.insert(make_pair(nodename, node));
    }
    return aig_hstable;
}

void print_aig_hstable(unordered_map<string, Node> &aig_hstable)
{	
	for(auto &node : aig_hstable)
    {
    	cout << node.second.name << " " << node.second.level << " ";
    	if(node.second.fanin0 != "-1") cout << " " << node.second.fanin0 << " " << node.second.phase0 << " ";
    	if(node.second.fanin1 != "-1") cout << " " << node.second.fanin1 << " " << node.second.phase1 << " ";
    	cout << ";\n";
    }
    cout << "size:" << aig_hstable.size() << endl;
}

vector<Node> sorted_aig_by_level(unordered_map<string, Node> &aig_hstable)
{
	vector<Node> sorted_aig;
	sorted_aig.reserve(aig_hstable.size());
	for(auto &component : aig_hstable)
	{
		sorted_aig.push_back(component.second);
	}
	sort(sorted_aig.begin(), sorted_aig.end(), node_level_cmp);
	return sorted_aig;
}

void setFanouts(unordered_map<string, Node> &aig_hstable)
{
	for(auto &node : aig_hstable)
	{
		if(node.second.fanin0 != "-1")
		{
			aig_hstable.at(node.second.fanin0).fanout_num++;
		}
		if(node.second.fanin1 != "-1")
		{
			aig_hstable.at(node.second.fanin1).fanout_num++;
		}
	}
}

void bfs(unordered_map<string, Node> &aig_hstable, vector<Node> &sorted_aig, int num)
{
	vector<Node> group;
	vector<string> andtree_input;
	deque<Node> box;
	Node current_node;
	unordered_set<string> visited;
	for(auto &component : sorted_aig)
	{
		if(visited.find(component.name) != visited.end())
		{
			continue;
		}
		current_node = aig_hstable.at(component.name);
		if(current_node.phase0 == 0 && current_node.phase1 == 0)
		{
			group.push_back(current_node);
			box.push_back(aig_hstable.at(current_node.fanin0));
			box.push_back(aig_hstable.at(current_node.fanin1));	
		}
		while(!box.empty())
		{
			current_node = box.back();
			box.pop_back();		
			if(current_node.fanout_num == 1 && current_node.phase0 == 0 && current_node.phase1 == 0) 
			{
				group.push_back(current_node);
				box.push_back(aig_hstable.at(current_node.fanin0));
				box.push_back(aig_hstable.at(current_node.fanin1));
			}
			else
			{
				auto it = find(andtree_input.begin(), andtree_input.end(), current_node.name);
				if(it == andtree_input.end())
					andtree_input.push_back(current_node.name);
			}
		}
		if(andtree_input.size() >= num)
		{
			print(group, andtree_input.size());
			for(auto &member : group)
			{
				visited.insert(member.name);
			}
		}
		group.clear();
		andtree_input.clear();
	}
}

void print(vector<Node> &group, int input_size)
{
	cout << input_size << " ";
	for(auto &member : group)
	{
		cout << member.name << " ";
	}
	cout << endl;
}

bool node_level_cmp(const Node& a, const Node& b) {
    return a.level > b.level;
}

void print_sorted_aig(vector<Node> &sorted_aig)
{
	for(auto &node : sorted_aig)
	{
		cout << node.name << " " << node.level << " ";
    	if(node.fanin0 != "-1") cout << " " << node.fanin0 << " " << node.phase0 << " ";
    	if(node.fanin1 != "-1") cout << " " << node.fanin1 << " " << node.phase1 << " ";
    	cout << ";\n";
	}
}

