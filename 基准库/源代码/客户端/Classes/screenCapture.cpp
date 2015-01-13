//
//  screenCapture.cpp
//  HelloWorld
//
//  Created by LAB da on 14-11-28.
//
//

#include "screenCapture.h"

void capture(exrTexture *tex, int x, int y, int w, int h, float order, bool inMem){
    static CustomCommand captureCommand;
    captureCommand.init(order);
    //captureCommand.init(std::numeric_limits<float>::max());
    captureCommand.func = std::bind(onCapture, tex, x, y, w, h, inMem);
    Director::getInstance()->getRenderer()->addCommand(&captureCommand);
}

void onCapture(exrTexture *tex, int x, int y, int w, int h, bool inMem){
 //   auto glView = Director::getInstance()->getOpenGLView();
 //   auto frameSize = glView->getFrameSize();
    
  //  int width = static_cast<int>(frameSize.width);
 //   int height = static_cast<int>(frameSize.height);
    
    //bool succeed = false;
    
    int bytePerPixel = 4;
    
    do{
        int size = w*h*bytePerPixel;
        GLubyte *buffer = (GLubyte*)malloc(size);
        if(!buffer)
            break;
        
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        
        //GLint gs;
        //glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &gs);
        
        
        glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        
        glFlush();
        CHECK_GL_ERROR_DEBUG();
        
        GLubyte *flip = (GLubyte*)malloc(size);
        if(!flip)
            break;
        
        for (int row=0; row<h; ++row) {
            memcpy(flip+(h-row-1)*w*bytePerPixel, buffer+row*w*bytePerPixel, w*bytePerPixel);
        }
        
        if(!inMem){
            tex->initWithExrData(w, h, flip, false);
            free(flip);
        }
        else{
            if(tex->_imageData)
                free(tex->_imageData);
            
            tex->_imageData = (float*)malloc(w*h*sizeof(float)*4);
            int off = 0;
            for(int i=0;i<h;i++)
                for(int j=0;j<w;j++,off+=4){
                    tex->_imageData[off] = flip[off]/255.0;
                    tex->_imageData[off+1] = flip[off+1]/255.0;
                    tex->_imageData[off+2] = flip[off+2]/255.0;
                    tex->_imageData[off+3] = 1.0;
                }
            
            tex->initWithExrData(w, h, tex->_imageData, true);
        }
        
        free(buffer);
        free(flip);
        
        
    }while(0);
}
