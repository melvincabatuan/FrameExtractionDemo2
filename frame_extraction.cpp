/***************************************************************************/
/*
The MIT License (MIT)

Copyright (c) 2015 Melvin Cabatuan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
/***************************************************************************/

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace cv;
using namespace std;

static void help();
const char* keys =
{
    "{c  camera   |         | use camera or not}"
    "{fn file_name|../data/tree.avi | movie file        }"
};

int main(int argc, const char** argv)
{
    cout << "Built with OpenCV " << CV_VERSION << endl;

    help();

    Mat image;
    int framecount = 0;

    stringstream ss;
    string name = "frame_";
    string type = ".jpg";

    CommandLineParser parser(argc, argv, keys);
    bool useCamera = parser.has("camera");
    string file = parser.get<string>("file_name");

    VideoCapture capture;
    namedWindow("frame", WINDOW_NORMAL);


    if(useCamera)
        capture.open(0);
    else
        capture.open(file.c_str());

    parser.printMessage();


    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for(;;)
        {
            capture >> image;

            if(image.empty())
                break;
          
            ss<<name<<setfill('0')<<setw(4)<<(framecount)<<type; 
            string filename = ss.str();
            ss.str("");	    

            imshow("frame", image);            

            char k = (char)waitKey(30);
            if( k == 27 ) break;

            imwrite(filename, image);
            framecount++;
        }
    }
    else
    {
        cout << "Can't open camera or video file\n" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        imshow("frame", image);
        waitKey(0);
    }
    return 0;
}


static void help()
{
 printf("\nDo frame extraction from a video file. \n" 
 "Usage: \n"
"			./frame_extraction [--camera]=<use camera, if this key is present>, [--file_name]=<path to movie file> \n\n");
}
