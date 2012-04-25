#include <iostream>
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

#ifdef WIN32
#include "1394Camera.h" //---1394camera.lib;
#endif // WIN32

using namespace cv;
using namespace std;

// NOTE: This demo is completely broken on Linux at the moment, but is included to show how
// to build an 'example' program

int main()
{

#ifdef WIN32
	C1394Camera Camera;

	 if(Camera.CheckLink() != CAM_SUCCESS)
        {
                printf("\nNo Link.");
                return -1;
        }
        if(Camera.InitCamera() != CAM_SUCCESS)
        {
                printf("\nInitialization failed.");
                return -2;
        }

        Camera.SetVideoFormat(1);
		Camera.SetVideoMode(3);
		Camera.SetVideoFrameRate(3);

        if(Camera.StartImageAcquisition() != CAM_SUCCESS)
        {
                printf("\nCould not start image acquisation.");
                return -6;
        }
#endif // WIN32

	IplImage* InputFrame = cvCreateImage( cvSize(1024, 768), 8, 3);
	int fps = 4;//( int )Camera.GetMaxSpeed();

	IplImage* GrayImage;
	IplImage* OutPutFrame;
	IplImage* CovertedColourFrame;
	IplImage* Canny;

	CvSeq* contours;
	CvMemStorage* storage;

	CvScalar RandomColour;

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 0, 1, CV_AA);

	string FPS;
	stringstream ss (stringstream::in | stringstream::out);

	double StartTime = (double)cvGetTickCount();
	double CurrentTime = 0;

	cvNamedWindow("Input Frame",0);

	bool record = false;
	CvVideoWriter* writer = cvCreateVideoWriter("out.avi", CV_FOURCC('D','I','B',' '), fps, cvSize(1024,768), 3);

	while(1)
	{
#ifdef WIN32
		Camera.AcquireImage(); 
		Camera.getRGB((unsigned char*)(InputFrame->imageData), (1024*768*3));
#endif // WIN32
		CurrentTime = (double)cvGetTickCount();
		cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		GrayImage = cvCreateImage(cvGetSize(InputFrame),8, 1);
		Canny = cvCreateImage(cvGetSize(InputFrame),8, 1);
		OutPutFrame = cvCreateImage(cvGetSize(InputFrame),8, 3);
		CovertedColourFrame = cvCreateImage(cvGetSize(InputFrame),8, 3);

		cvCvtColor(InputFrame, CovertedColourFrame, CV_BGR2RGB);
		cvCvtColor(CovertedColourFrame, GrayImage, CV_BGR2GRAY);
		cvCanny(GrayImage,Canny,50,120,3);

		CvMSERParams params = cvMSERParams(2,30,1000,0.06,0.2);
		storage= cvCreateMemStorage();
		cvExtractMSER(GrayImage, NULL, &contours, storage, params );

		uchar* rsptr = (uchar*)OutPutFrame->imageData;

		for ( int i = contours->total-1; i >= 0; i-- )
		{
			CvSeq* r = *(CvSeq**)cvGetSeqElem( contours, i );
			RandomColour = cvScalar(rand()%255,rand()%255,rand()%255);
			for ( int j = 0; j < r->total; j++ )
			{
				CvPoint* pt = CV_GET_SEQ_ELEM( CvPoint, r, j );
				rsptr[pt->x*3+pt->y*OutPutFrame->widthStep] = RandomColour.val[0];
				rsptr[pt->x*3+1+pt->y*OutPutFrame->widthStep] = RandomColour.val[1];
				rsptr[pt->x*3+2+pt->y*OutPutFrame->widthStep] = RandomColour.val[2];
			}
		}

		
		cvPutText(OutPutFrame, ("FPS = " + FPS).c_str() , cvPoint(3, 12), &font, cvScalar(255, 0, 255, 0));

		
		cvShowImage("Default MSER",OutPutFrame);
		cvShowImage("Input Frame",CovertedColourFrame);

		if(record == true)
		cvWriteFrame(writer, OutPutFrame);
		
		cvReleaseImage(&GrayImage);
		cvReleaseImage(&OutPutFrame);
		cvReleaseImage(&CovertedColourFrame);
		cvReleaseImage(&Canny);
		cvReleaseMemStorage(&storage);
		  
		if ( (cvWaitKey(1) & 255) == 27 ) break;
		
		CurrentTime = (double)cvGetTickCount()-CurrentTime;
		ss << 1000/((double)CurrentTime/((double)cvGetTickFrequency()*1000));
		ss >> FPS;
		cout << "FPS = " << FPS;

		ss.clear();
	}

	if(record == true)
	cvReleaseVideoWriter(&writer);

	cvReleaseImage(&GrayImage);
	cvReleaseImage(&OutPutFrame);
	cvReleaseMemStorage(&storage);

	cvDestroyWindow("Default MSER");
	cvDestroyWindow("Input Frame");
		
	return 0;
	
}


