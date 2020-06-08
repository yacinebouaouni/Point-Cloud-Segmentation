#include"KdTree.h"


void kdtree::insert(std::vector<float> point, int id) {

	help_insert(point, id, &root, 0);
}


void kdtree::help_insert(std::vector<float> point, int id, Node** node, int depth = 0) {

	Node** compare = node;
	float x = point[0];
	float y = point[1];
	int dim = depth % 2;

	//if dim=0 we dimension->x else y
	//dim=0 point[dim]=x ; dim=1 => point[dim]=y

	if (*compare == NULL) {

		*compare = new Node(point, id);
	}

	else {

		if (point[dim] > (*compare)->point[dim]) {

			help_insert(point, id, &(*compare)->Right, depth + 1);

		}
		else {

			help_insert(point, id, &(*compare)->Left, depth + 1);
		}
	}


}

