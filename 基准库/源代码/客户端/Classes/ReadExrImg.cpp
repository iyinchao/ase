//
//  ReadExrImg.cpp
//  HelloWorld
//
//  Created by LAB da on 14-10-29.
//
//

#include "ReadExrImg.h"

void readImage(const char fileName[], Array2D<myPixel> &pixels, int &width, int &height){
    InputFile file (fileName);
    Box2i dw = file.header().dataWindow();
    
    width  = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    int dx = dw.min.x;
    int dy = dw.min.y;
    
    pixels.resizeErase (height, width);
    
    FrameBuffer frameBuffer;
    
    frameBuffer.insert("R", Slice(FLOAT, (char*)&pixels[-dy][-dx].r, sizeof(pixels[0][0])*1,sizeof(pixels[0][0])*width));
    frameBuffer.insert("G", Slice(FLOAT, (char*)&pixels[-dy][-dx].g, sizeof(pixels[0][0])*1,sizeof(pixels[0][0])*width));
    frameBuffer.insert("B", Slice(FLOAT, (char*)&pixels[-dy][-dx].b, sizeof(pixels[0][0])*1,sizeof(pixels[0][0])*width));
    frameBuffer.insert("A", Slice(FLOAT, (char*)&pixels[-dy][-dx].a, sizeof(pixels[0][0])*1,sizeof(pixels[0][0])*width));
    
    file.setFrameBuffer (frameBuffer);
    file.readPixels (dw.min.y, dw.max.y);
}

void *getPixelData(Array2D<myPixel> &pixels, int width, int height){
    float *data = NULL;
    
    int offset = 0;
    int len = width*height*sizeof(float)*4;
    data = (float*)malloc(len);
    
    if(!data)
        return nullptr;

    for(int y=0;y<height;y++){
        for (int x=0; x<width; x++) {
            data[offset] = pixels[y][x].r;
            data[offset+1] = pixels[y][x].g;
            data[offset+2] = pixels[y][x].b;
            data[offset+3] = 1.0;
            offset += 4;
        }
    }
    
    return data;
}

void
readRgba1 (const char fileName[],
           Array2D<Rgba> &pixels,
           int &width,
           int &height)
{
    //
    // Read an RGBA image using class RgbaInputFile:
    //
    //	- open the file
    //	- allocate memory for the pixels
    //	- describe the memory layout of the pixels
    //	- read the pixels from the file
    //
    
    RgbaInputFile file (fileName);
    
    Box2i dw = file.dataWindow();
    width  = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    
    pixels.resizeErase (height, width);
    
    file.setFrameBuffer (&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels (dw.min.y, dw.max.y);
}

void *getPixelData1(Array2D<Rgba> &pixels, int width, int height){
    half *data = NULL;
    int offset = 0;
    
    int len = width*height*sizeof(Rgba);
    data = (half*)malloc(len);
    
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            Rgba p = pixels[y][x];
            data[offset] = p.r;
            data[offset+1] = p.g;
            data[offset+2] = p.b;
            data[offset+3] = p.a;
            offset += 4;
        }
    }
    
    return data;
}