//
// Created by zwakr on 8/23/2018.
//

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <chrono>
#include <ctime>
#include <iostream>


using namespace std;
using namespace cv;

static void help()
{
    cout << "\nThis program demonstrates the cascade recognizer. Now you can use Haar or LBP features.\n"
            "This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
            "It's most known use is for faces.\n"
            "Usage:\n"
            "./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
            "   [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]\n"
            "   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
            "   [--try-flip]\n"
            "   [filename|camera_index]\n\n"
            "see facedetect.cmd for one call:\n"
            "./facedetect --cascade=\"../../data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml\" --scale=1.3\n\n"
            "During execution:\n\tHit any key to quit.\n"
            "\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}
void pixeltransform( Mat& img,  CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip, int fps
);

string cascadeName;
string nestedCascadeName;
//std::time_t totalCalcTime;
std::chrono::duration<double> totalCalcTime;

int main( int argc, const char** argv ) {
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    bool tryflip;
    CascadeClassifier cascade, nestedCascade;
    double scale;

    int timeOut = atof(argv[2]);
    int width = atof(argv[3]);
    int height = atof(argv[4]);
    int frames = 0;



	std::vector<int> fpsVector;
    cv::CommandLineParser parser(argc, argv,
                                 "{help h||}"
                                 "{cascade|data/haarcascades/haarcascade_frontalface_default.xml|}"
                                 "{nested-cascade|data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}"
                                 "{scale|1|}{try-flip||}{@filename||}"
    );
    if (parser.has("help"))
    {
        help();
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
        help();
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
                pixeltransform( frame, cascade, nestedCascade, scale, tryflip,fps );
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
			
			//cout << "totalCalctime,"<<totalCalcTime.count()<< endl;
			
            break;
        }
    }
    else
    {
        cout << "not working " << inputName << endl;
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

void pixeltransform( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip , int fps) {

    
    cv::Mat imgpixeltransform( img.rows, img.cols,CV_8UC3,Scalar(0,0,0));

    int i,j;
    int r,g,b;
	std::chrono::time_point<std::chrono::system_clock> beginCalcTime , endCalcTime;
	beginCalcTime = std::chrono::system_clock::now();
    for(int i = 0;i < img.rows;i++){
        for(int j = 0;j < img.cols;j++){
            Vec3b intensity = img.at<Vec3b>(i, j);
            b=intensity.val[0] * 1.5 + 100;
            g=intensity.val[1] * 1.5 + 100;
            r=intensity.val[2] * 1.5 + 100;
			intensity.val[0] = b;
			intensity.val[1] = g;
			intensity.val[2] = r;
			imgpixeltransform.at<cv::Vec3b>(i,j) = intensity;
			
			//cout << "intensity = "  <<endl <<" " << r << " " << g << " " << b << endl << endl;
            //imgpixeltransform.at<Vec3b>(i,j)[0] = 0;
            //imgpixeltransform.at<Vec3b>(i,j)[1] = 200;
            //imgpixeltransform.at<Vec3b>(i,j)[2] = 0;
		
        }
    }
	endCalcTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds= endCalcTime -beginCalcTime;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(
	totalCalcTime = totalCalcTime + elapsed_seconds;
	//cout << "lol,"<<totalCalcTime.count()<< endl;


    cv::putText(img, cv::format("FPS=%d", fps ), cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0,255,0));
    cv::imshow( "original", img );
    cv::imshow( "pixeltransform", imgpixeltransform );

}

