// This is the main DLL file.

#include "stdafx.h"

#include "OpenTld.Net.h"


OpenTldNet::OpenTLD::OpenTLD()
{
	tldTracker = new tld::TLD();
}

OpenTldNet::OpenTLD::~OpenTLD()
{
	this->!OpenTLD();
}

OpenTldNet::OpenTLD::!OpenTLD()
{
	if(tldTracker != nullptr)
	{
		delete tldTracker;
	}
	tldTracker = nullptr;
}

void OpenTldNet::OpenTLD::Init(OpenCV::Net::IplImage ^image)
{
	tldTracker->detectorCascade->imgWidth = image->Width;
	tldTracker->detectorCascade->imgHeight = image->Height;
	tldTracker->detectorCascade->imgWidthStep = image->WidthStep;
}

void OpenTldNet::OpenTLD::Release()
{
	tldTracker->release();	
}

void OpenTldNet::OpenTLD::SelectObject(OpenCV::Net::IplImage ^image, OpenCV::Net::Rect ^roi)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	cv::Rect *cvRoi = new cv::Rect(roi->X, roi->Y, roi->Width, roi->Height);
	if (cvRoi->x < 0) cvRoi->x = 0;
	if (cvRoi->y < 0) cvRoi->y = 0;
	if (cvRoi->x > cvimage.cols) cvRoi->x = cvimage.cols;
	if (cvRoi->y > cvimage.rows) cvRoi->y = cvimage.rows;
	if (cvRoi->x + cvRoi->width > cvimage.cols) cvRoi->width -= (cvRoi->x + cvRoi->width) - cvimage.cols;
	if (cvRoi->y + cvRoi->height > cvimage.rows) cvRoi->height -= (cvRoi->y + cvRoi->height) - cvimage.rows;

	tldTracker->selectObject(cvimage,  cvRoi);	
}

void OpenTldNet::OpenTLD::ProcessImage(OpenCV::Net::IplImage ^image)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	tldTracker->processImage(cvimage);
}