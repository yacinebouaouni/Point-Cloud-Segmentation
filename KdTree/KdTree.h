#pragma once
#include<vector>


struct Node {

	Node* Right;
	Node* Left;
	int id;
	std::vector<float> point;

	Node(std::vector<float> point, int id) :id(id), point(point),Right(NULL),Left(NULL){}

};


struct kdtree {

	Node* root;

	kdtree():root(NULL){}
	void help_insert(std::vector<float> point, int id, Node** node, int depth);
	void insert(std::vector<float> point, int id);
	
};