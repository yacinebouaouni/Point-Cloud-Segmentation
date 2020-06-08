#pragma once


#include<vector>
#include"KdTree.h"


using std::vector;

//Proximity:Gets the nearest neighbours of a point inside a threshold distance.
void Proximity(kdtree* tree, const vector<vector<float>>points, int index, vector<int>& cluster, vector<bool>& processed, const float distanceTol) {

	processed[index] = true;
	cluster.push_back(index);

	vector<int> closepts = tree->search(points[index], distanceTol);

	for (int index : closepts) {

		if (processed[index] == false) {
			Proximity(tree, points, index, cluster, processed, distanceTol);
		}
	}

}

vector<vector<int>> EuclideanClustering(vector<vector<float>> points, kdtree* tree, float distanceTol) {

	vector<vector<int>> clusters;
	vector<bool> processed(points.size(), false);

	int index = 0;

	while (index < points.size()) {

		if (processed[index] == false) {

			vector<int> cluster;
			Proximity(tree, points, index, cluster, processed, distanceTol);
			clusters.push_back(cluster);

		}
		index++;

	}

	return clusters;
}
