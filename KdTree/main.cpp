#include<iostream>
#include<vector>

#include"KdTree.h"
using std::cout;
using std::cin;
using std::endl;


int main() {

	kdtree* tree = new kdtree;
	std::vector<std::vector<float>> points = { {-6.2,7}, {-6.3,8.4}, {-5.2,7.1}, {-5.7,6.3}, {7.2,6.1}, {8.0,5.3}, 
											{7.2,7.1}, {0.2,-7.1}, {1.7,-6.9}, {-1.2,-7.2}, {2.2,-8.9} };
	int id = 0;
	for (std::vector<float> point : points) {

		tree->insert(point, id);
		id++;
	}

	cout <<"The root is :(x,y)="<<"("<< tree->root->point[0] << "," << tree->root->point[1] <<")"<< endl;
	cout << "The Right Node is :(x,y)=" << "(" << tree->root->Right->point[0] << "," << tree->root->Right->point[1] << ")" << endl;
	cout <<"The Left Node is:(x,y) = " << "(" << tree->root->Left->point[0] << ", " << tree->root->Left->point[1] << ")" << endl;
	
	return 0;

}
