#include <iostream>
#include <cmath>
#include "tools/tools.h"

int main() {
  
    std::cout << "Hello, World!" << std::endl;
    
     // Create two points
     S2d p1 = {0, 0};
     S2d p2 = {3, 4};
 
     // Create a vector from p1 to p2
     Vecteur v(p1, p2);
     
     // Display the vector's properties
     std::cout << "Vecteur from (0,0) to (3,4):" << std::endl;
     std::cout << "Angle: " << v.angle << " radians" << std::endl;
     std::cout << "Norme (Magnitude): " << v.norme << std::endl;
 
     // Create two circles
     Cercle c1(p1, 5);  // Circle at (0, 0) with radius 5
     Cercle c2(p2, 2);  // Circle at (3, 4) with radius 2
 
     // Test inclusion
     std::cout << "Does C2 include C1? " << inclusion(c2) ? "Yes" : "No") << std::endl;
 
     // Test intersection
     std::cout << "Do C1 and C2 intersect? " << (intersection(c2) ? "Yes" : "No") << std::endl;
 
     // Reflect a vector (incident vector with respect to a point)
     S2d point_of_reflection = {2, 2};
     Vecteur incident_vector(p1, p2);
     Vecteur reflected_vector = reflechis(incident_vector, point_of_reflection);
     
     // Display the reflected vector
     std::cout << "Reflected vector angle: " << reflected_vector.angle << std::endl;
     std::cout << "Reflected vector magnitude: " << reflected_vector.norme << std::endl;
 
     return 0;



    return 0;
}
