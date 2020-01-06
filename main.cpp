/*
 The following code shows how to generate the following vtk files:
 
---------------- file begin ------------------------- 
# vtk DataFile Version 1.0
Stroked lines spell hello...
ASCII

DATASET POLYDATA
POINTS 4 float              
0.0 0.0 0.0
0.0 2.0 0.0
0.0 1.0 0.0
1.0 1.0 0.0

LINES 3 10
3 0 1 2
2 2 3
2 3 0
---------  file end -------------------------------

Explanation for the aforementioned files:
(1) POINTS 4 float     
    means 4 points, coordinate encoded in float
(2) 0.0 0.0 0.0
    coordinates
(3) LINES 3 10
    LINES - geometry types
    3     - means there are 3 polylines
    10    - means the sum of polyline number and the reffered point number in the 3 polyline
            8 = 3 + 7
                    ^
                    |---> 7 means there are 7 times that points are referred by the three polylines, and we donnot care wether a point is repeatly referred or not
                          
            7 = 3 + 2 + 2
                3 - the 1st polyline contains 3 points ( refers points for 3 times)
                2 - the 2nd polyline contains 2 points ( refers points for 2 times)
                2 - the 3rd polyline contains 2 points ( refers points for 2 times)                


*/

#include "VTKWriter.h"
using namespace std;

struct vertex
{
   double x, y, z;
};

int main()
{
   vector<vertex> vs =
   {
     {0,0,0},
     {0,2,0},
     {0,1,0},
     {1,1,0}
   };
   vector< vector<int> > plines=
   {
       {0,1,2},
       {2,3},
       {3,0}       
   };
   
   const int point_num = vs.size();  // total point number
   const int line_num = plines.size();
   const int line_num_and_points_reffered_time = line_num;
   for(auto& pline: plines)
   {
       line_number_plus_points_referred += pline.size(); 
   }   

    vtk_file vtk("haha.vtk");
    vtk.write_point_header(point_num);
    for(auto& v: vs)
    {
       vtk.append_point(v.x,
                        v.y,
                        v.z);
    }
    vtk.end_writing_points();
    
    // 3. write lines header
    vtk.write_lines_header(line_num,line_num_and_points_reffered_time);  
    
    //4. write pline informaiton
    for(auto& pline:plines)
    {
        vtk.append_lines(pline);
    }
    vtk.end_writing_lines();
    
    //5. close the file
    vtk.append_end();
}
