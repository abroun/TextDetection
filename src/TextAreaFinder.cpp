//--------------------------------------------------------------------------------------------------
// File: TextAreaFinder.cpp
// Desc: Keeps track of text areas and provides commands for a robotic system in order to explore
//       an object of interest.
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "TextDetection/TextAreaFinder.h"

//--------------------------------------------------------------------------------------------------
// TextAreaFinder
//--------------------------------------------------------------------------------------------------
TextAreaFinder::TextAreaFinder()
{
}

//--------------------------------------------------------------------------------------------------
TextAreaFinder::~TextAreaFinder()
{
}

//--------------------------------------------------------------------------------------------------
Eigen::Vector2f TextAreaFinder::processImage( IplImage* pImage, bool bDumpDebugData )
{
    printf( "Doing funky stuff to the image!\n" );
    
    return Eigen::Vector2f::Zero();
}