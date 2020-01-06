/*
  a simple VTKWriter interface for writting lines to a vtk file
  by Dr. Xiaoguo Zhang
*/
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

/*
  vtk_file, written by xiaoguo zhang, SEU, China
*/
class vtk_file:public ofstream
{
public:
    vtk_file(const string & file):ofstream(file)
    {   
    }   
public:
    // 1. header
    void write_header() 
    {        
          (*this)<<VTK_HEAD<<endl;
    }   

   // 2.  dataset declaration
    void write_polydataset_header()
    {   
          (*this)<<VTK_DATA_SET<<endl;
    }   
        
    // 3. write point data information
    void write_point_header(const int point_num)
    {        
          (*this)<<VTK_POINTS<<point_num<<VTK_BLANK_STRING<<VTK_FLOAT<<endl;
    }   
    void  append_point(const double x, 
                       const double y, 
                       const double z)
    {   
         (*this)<<std::fixed<<std::setprecision(2);
         (*this)<< x << VTK_BLANK_STRING
                << y << VTK_BLANK_STRING
                << z << endl;
    }   
    void  append_point(const double x, 
                       const double y, 
                       const double z,
                       const double f)
    {   
        (*this)<<std::fixed<<std::setprecision(2);
        (*this) << x <<VTK_BLANK_STRING
                << y <<VTK_BLANK_STRING
                << z <<VTK_BLANK_STRING
                << f << endl;
    }   
    void end_writing_points()
    {
         (*this)<<endl;
    }
    
    //4. write line informaiton
    void write_lines_header(const int lines_number, 
                            const int line_number_plus_points_referred) // like "LINES 5 17", 5 means there are five polylines
                                                                        // 17 = 5 + 12, 12 means point referred times by the 5 polylines
                                                                        //                 just simply count the referred point number, we do not care whether it is repeatly reffered or not
    {
           (*this)<<VTK_LINES <<VTK_BLANK_STRING <<lines_number<<VTK_BLANK_STRING <<line_number_plus_points_referred<<endl;
    }
    void append_lines(const vector<int> & ids)   // like line with 3 points: "3 0 1 2"
    {
           (*this)<<ids.size()<<VTK_BLANK_STRING;
           for(auto it = ids.begin(); it != ids.end(); ++it)
           {
                 (*this) << (*it)<<VTK_BLANK_STRING;
           }
           (*this)<<endl;
    }
    void end_writing_lines()
    {
    }

   // 5. end writing the file, and close the file
   void append_end()
   {
         // do nothing currently
         ofstream::close();
   }   

protected:
    const string VTK_BLANK_STRING = " ";
    const string VTK_HEAD = "# vtk DataFile Version 2.0\r\nRoad Network Center Lines\r\nASCII\r\n";
    const string VTK_DATA_SET = "DATASET POLYDATA";
    const string VTK_POINTS = "POINTS ";
    const string VTK_FLOAT = "float";
    const string VTK_LINES = "LINES";
};
