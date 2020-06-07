


void crossProduct(float A[], float B[], float cross_P[]) {

    cross_P[0] = A[1] * B[2] - A[2] * B[1];
    cross_P[1] = A[2] * B[0] - A[0] * B[2];
    cross_P[2] = A[0] * B[1] - A[1] * B[0];
}

std::unordered_set<int> RansacPlane(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int maxIterations, float distanceTol) {

    std::unordered_set<int> BestInliers;
    //Iterate for maxIterations
    while (maxIterations--) {

        std::unordered_set<int> inliers;

        //Get 3 data points into inliers
        while (inliers.size() < 3) {

            inliers.insert(rand() % cloud->points.size());
        }

        float x1, y1, z1, x2, y2, z2, x3, y3, z3;

        auto itr = inliers.begin();

        x1 = cloud->points[*itr].x;
        y1 = cloud->points[*itr].y;
        z1 = cloud->points[*itr].z;

        //Go to second Point
        itr++;

        x2 = cloud->points[*itr].x;
        y2 = cloud->points[*itr].y;
        z2 = cloud->points[*itr].z;

        //Go to third point
        itr++;

        x3 = cloud->points[*itr].x;
        y3 = cloud->points[*itr].y;
        z3 = cloud->points[*itr].z;

        //2 Vectors of the plane

        float vect1[] = { x2 - x1,y2 - y1,z2 - z1 };
        float vect2[] = { x3 - x1,y3 - y1,z3 - z1 };

        //Normal Vector of the plane

        float Normal[3];
        crossProduct(vect1, vect2, Normal);

        //Plane Parameters
        float A, B, C, D;

        A = Normal[0]; B = Normal[1]; C = Normal[2];

        //Get D : Plane Equation A*x+B*y+C*z+D=0
        D = -(A * x1 + B * y1 + C * z1);

        for (int index = 0; index < cloud->points.size(); index++) {

            if (inliers.count(index) > 0) {
                continue;
            }

            else {

                pcl::PointXYZ point = cloud->points[index];
                float distance = fabs(A * point.x + B * point.y + C * point.z + D) / sqrt(A * A + B * B + C * C);

                if (distance < distanceTol) {
                    inliers.insert(index);
                }

            }
        }

        //After counting inliers fot this iteration store the best model:
        if (inliers.size() > BestInliers.size()) {

            BestInliers = inliers;
        }


    }

    return BestInliers;
}
