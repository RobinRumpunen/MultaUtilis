#include <iostream>
#include <vector>

struct node
{
	node(const int thisID, std::vector<int> theseEdges) : id(thisID), edges(theseEdges) {};

	int id;
	std::vector<int> edges;

	bool visited = false;
	int group;
};

/// Global data
node graph[] = {
	{0,  std::initializer_list<int>{1}},     /// 0
	{1,  std::initializer_list<int>{2, 3}},  /// 1
	{2,  std::initializer_list<int>{}},		 /// 2
	{3,  std::initializer_list<int>{4}},     /// 3
	{4,  std::initializer_list<int>{2, 5}},  /// 4
	{5,  std::initializer_list<int>{6, 8}},  /// 5
	{6,  std::initializer_list<int>{7}},     /// 6
	{7,  std::initializer_list<int>{8, 9}},  /// 7
	{8,  std::initializer_list<int>{9, 10}}, /// 8
	{9,  std::initializer_list<int>{10}},    /// 9
	{10, std::initializer_list<int>{}},		 /// 10
	{11, std::initializer_list<int>{}},		 /// 11
	{12, std::initializer_list<int>{15, 14}},/// 12
	{13, std::initializer_list<int>{}},		 /// 13
	{14, std::initializer_list<int>{13, 15}},/// 14
	{15, std::initializer_list<int>{}},		 /// 15
};

void DFS(node* thisNode, const int& groupID)
{
	std::cout << thisNode->id << " is visited. ";
	if (thisNode->visited)
	{
		std::cout << "Though, " << thisNode->id << " was already visited before.\n";
		return;
	}
	thisNode->group = groupID;

	thisNode->visited = true;
	if (thisNode->edges.size() == 0)
	{
		std::cout << thisNode->id << " has no neighbour.\n";
		return;
	}

	for (int i = 0; i < thisNode->edges.size(); i++)
	{
		std::cout << thisNode->id << " has a neighbour whom he visits called " << thisNode->edges[i] << " \n";
		int thisEdge = thisNode->edges[i];
		DFS(&graph[thisEdge], groupID);
	}
}

int main() {
	std::cout << "\nStarting Depth First Search." << std::endl;

	int groupID = 0;
	for(node& thisNode : graph)
		if (!thisNode.visited)
		{
			DFS(&thisNode, groupID);
			++groupID;
		}
	for (node& thisNode : graph)
		std::cout << "Node: " << thisNode.id << ". Group: " << thisNode.group << std::endl;

	return 1;
}