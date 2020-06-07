#include<iostream>
#include<unordered_set>


std::unordered_set<int> Ransac(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int maxIterations, float distanceTol)
{
    std::unordered_set<int> inliersResult;
    srand(time(NULL));

    // For max iterations 
    for (int iteration = 0; iteration < maxIterations; iteration++) {


        //Store 2 random points in an unordered set
        std::unordered_set<int> inliers;

        while (inliers.size() < 2) {
            inliers.insert(rand() % (cloud->points.size()));
        }

        auto itr = inliers.begin(); //This is a pointer to the first element (first index)

        float x1, y1, x2, y2;//x,y coordinates of the 2 points

        x1 = cloud->points[*itr].x;
        y1 = cloud->points[*itr].y;

        itr++; //Increment the iterator to point the second point

        x2 = cloud->points[*itr].x;
        y2 = cloud->points[*itr].y;


        //Parameters of the line
        float a = y1 - y2;
        float b = x2 - x1;
        float c = (x1 * y2 - x2 * y1);

        //Check out for inliers from the cloud data
        for (int index = 0; index < cloud->points.size(); index++) {

            //Check if the point is one of (x1,y1) or (x2,y2) if True go to next index

            if (inliers.count(index) > 0) {
                continue;
            }

            else {

                pcl::PointXYZ point = cloud->points[index];

                //Compute the distance between the point and the line
                float distance = fabs(a * point.x + b * point.y + c) / sqrt(a * a + b * b);

                //If the distance of the point is within the threshold add it to the inliers 

                if (distance < distanceTol) {

                    inliers.insert(index);
                }


            }

            //After adding all the inliers we compare inliers to the best model which is inliersResult if it has bigger size we swap
            if (inliers.size() > inliersResult.size()) {

                inliersResult = inliers;

            }
        }

    }

    return inliersResult;
}