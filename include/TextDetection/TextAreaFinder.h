//--------------------------------------------------------------------------------------------------
// File: TextAreaFinder.h
// Desc: Keeps track of text areas and provides commands for a robotic system in order to explore
//       an object of interest.
//--------------------------------------------------------------------------------------------------

#ifndef TEXT_AREA_FINDER_H
#define TEXT_AREA_FINDER_H

//--------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <vector>
#include <Eigen/Core>
#include <cv.h>

//--------------------------------------------------------------------------------------------------
class TextAreaFinder
{
    public: TextAreaFinder();
    public: virtual ~TextAreaFinder();
    
    public: Eigen::Vector2f processImage( IplImage* pImage, bool bDumpDebugData );
        
    /*public: uint32_t getNumTextAreas() const;
    public: TextArea getTextArea( uint32_t textAreaIdx ) const;
        
    private: std::vector<TextArea> mTextAreas;*/
};

#endif // TEXT_AREA_FINDER_H
