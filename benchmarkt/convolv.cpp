//
// Created by zwakr on 8/22/2018.
//
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;
using namespace cv;

string cascadeName;
string nestedCascadeName;
std::chrono::duration<double> totalCalcTime;

void convolvimg( Mat& img,  CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip, int fps
);

int main( int argc, const char** argv )
{
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    bool tryflip;
    CascadeClassifier cascade, nestedCascade;
    double scale;

    int timeOut = atof(argv[2]);
    int width   = atof(argv[3]);
    int height  = atof(argv[4]);
    int frames  = 0 ;

    std::vector<int> fpsVector;
	cv::CommandLineParser parser(argc, argv,
		    "{help h||}"
		    "{cascade|data/haarcascades/haarcascade_frontalface_default.xml|}"
		    "{nested-cascade|data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}"
		    "{scale|1|}{try-flip||}{@filename||}"
		);

    if (parser.has("help"))
    {
        //help();
        return 0;
    }
    cascadeName = parser.get<string>("cascade");
    nestedCascadeName = parser.get<string>("nested-cascade");
    scale = parser.get<double>("scale");
    if (scale < 1)
        scale = 1;
    tryflip = parser.has("try-flip");
    inputName = parser.get<string>("@filename");
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    if ( !nestedCascade.load( nestedCascadeName ) )
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        //help();
        return -1;
    }
    if( inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1) )
    {
        int camera = inputName.empty() ? 0 : inputName[0] - '0';
        if(!capture.open(camera))
            cout << "Capture from camera #" <<  camera << " didn't work" << endl;
    }
    else if( inputName.size() )
    {
        image = imread( inputName, 1 );
        if( image.empty() )
        {
            if(!capture.open( inputName ))
                cout << "Could not read " << inputName << endl;
        }
    }
    else
    {
        image = imread( "../data/lena.jpg", 1 );
        if(image.empty()) cout << "Couldn't read ../data/lena.jpg" << endl;
    }

    if( capture.isOpened() ) {
		std::chrono::time_point<std::chrono::system_clock> beginTime , endTime;
		beginTime = std::chrono::system_clock::now();
        capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

        int frameCounter = 0;
        int tick = 0;
        int fps;

        std::time_t start = std::time(0);
        for(;;){
            while(std::time(0)- start <= timeOut){

                frameCounter++;
                capture.read(frame);
                if( frame.empty() )
                    break;
                std::time_t timeNow = std::time(0) - start;
                if (timeNow - tick >= 1){
                    tick++;
                    fps = frameCounter;
                    frameCounter = 0;
                    fpsVector.push_back(fps);
                }
                convolvimg( frame, cascade, nestedCascade, scale, tryflip,fps );
                char c = (char)waitKey(10);
                if( c == 27 || c == 'q' || c == 'Q' )
                    break;
            }			
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_totalTime= endTime -beginTime;
			
			//std::time_t endtime = std::time(0) - beginTime;
			//cout << "totaltime," << elapsed_totalTime.count() << endl;
			double ratio = totalCalcTime/ elapsed_totalTime *100;
			
			cout << "ratioCalTime,"<<  ratio << "," <<endl;
            //std::cout << "myvector stores " << int(fpsVector.size()) << " numbers.\n";
            cout << "fps,";
            for (int i=0; i<fpsVector.size();i++){
                cout << fpsVector[i] << ",";
            }
            cout << endl;
            break;
        }
    }
    else
    {
        cout << "Detecting face(s) in " << inputName << endl;
        if( !image.empty() )
        {
            //detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
            waitKey(0);
        }
        else if( !inputName.empty() )
        {
            /* assume it is a text file containing the
            list of the image filenames to be processed - one per line */
            FILE* f = fopen( inputName.c_str(), "rt" );
            if( f )
            {
                char buf[1000+1];
                while( fgets( buf, 1000, f ) )
                {
                    int len = (int)strlen(buf);
                    while( len > 0 && isspace(buf[len-1]) )
                        len--;
                    buf[len] = '\0';
                    cout << "file " << buf << endl;
                    image = imread( buf, 1 );
                    if( !image.empty() )
                    {
                        //detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
                        char c = (char)waitKey(0);
                        if( c == 27 || c == 'q' || c == 'Q' )
                            break;
                    }
                    else
                    {
                        cerr << "Aw snap, couldn't read image " << buf << endl;
                    }
                }
                fclose(f);
            }
        }
    }

    return 0;
}

void convolvimg( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip , int fps)
{

    Mat dst;
	Mat kernel;
	std::chrono::time_point<std::chrono::system_clock> beginCalcTime , endCalcTime;
	beginCalcTime = std::chrono::system_clock::now();
    kernel = Mat::ones( 5, 5, CV_32F )/ 25;

    filter2D(img, dst, -1 , kernel, Point(-1,-1), 0, BORDER_DEFAULT );
	endCalcTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds= endCalcTime -beginCalcTime;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(
	totalCalcTime = totalCalcTime + elapsed_seconds;

    cv::putText(img, cv::format("FPS=%d", fps ), cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,255,0));
    cv::putText(dst, cv::format("FPS=%d", fps ), cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,255,0));

    imshow( "original", img );
    imshow( "convolv", dst );
}
