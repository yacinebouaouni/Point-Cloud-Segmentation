#include"KdTree.h"

using std::vector;

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


vector<int> kdtree::search(std::vector<float> point, float distanceTol) {

	vector<int> ids;
	vector<float> pointmax = { point[0] + distanceTol,point[1] + distanceTol };
	vector<float> pointmin = { point[0] - distanceTol,point[1] - distanceTol };

	
	help_search(point, distanceTol,root, 0,ids,pointmax,pointmin);

	return ids;
}


void kdtree::help_search(vector<float>point, float distanceTol, Node* node, int depth, vector<int>& ids, vector<float>max,vector<float>min) {

	if (!(node == NULL)) {

		//Check if the node is in the Box:
		if ((node->point[0]<max[0] && node->point[0]>min[0]) && (node->point[1]<max[1] && node->point[1]>min[1])) {

			float distance = sqrt((node->point[0] - point[0]) * (node->point[0] - point[0]) + (node->point[1] - point[1]) * (node->point[1] - point[1]));

			//If the node is within the tolerance add it to the ids:
			if (distance < distanceTol) {

				ids.push_back(node->id);
			}

		}

		//After checking for the present node The function checks either on the right or left of the node:

		//Check if the node is on the Right
		if (node->point[depth % 2] > min[depth % 2]) {

			help_search(point, distanceTol, node->Left, depth + 1, ids, max, min);
		}

		//Check if the node is on the left
		if (node->point[depth % 2] < max[depth % 2]) {

			help_search(point, distanceTol, node->Right, depth + 1, ids, max, min);
		}

	}
}




