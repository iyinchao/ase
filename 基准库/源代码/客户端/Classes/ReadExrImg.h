//
//  ReadExrImg.h
//  HelloWorld
//
//  Created by LAB da on 14-10-29.
//
//

#ifndef __HelloWorld__ReadExrImg__
#define __HelloWorld__ReadExrImg__

#include <iostream>
#include <ImfInputFile.h>
#include <ImfRgbaFile.h>
#include <OpenEXRConfig.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <ImfNamespace.h>

namespace IMF = OPENEXR_IMF_NAMESPACE;

using namespace IMF;
using namespace std;
using namespace IMATH_NAMESPACE;

struct myPixel {
    float r;
    float g;
    float b;
    float a;
};

void readImage(const char fileName[], Array2D<myPixel> &pixels, int &width, int &height);
void *getPixelData(Array2D<myPixel> &pixels, int width, int height);
void readRgba1 (const char fileName[],Array2D<Rgba> &pixels,int &width,int &height);
void *getPixelData1(Array2D<Rgba> &pixels, int width, int height);

#endif /* defined(__HelloWorld__ReadExrImg__) */
