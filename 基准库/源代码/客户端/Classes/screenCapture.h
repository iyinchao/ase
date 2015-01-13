//
//  screenCapture.h
//  HelloWorld
//
//  Created by LAB da on 14-11-28.
//
//

#ifndef __HelloWorld__screenCapture__
#define __HelloWorld__screenCapture__

#include <stdio.h>
#include <vector>
#include <string>
#include "2d/CCNode.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"
#include "CCGLView.h"

#include "exrTexture.h"

USING_NS_CC;

void capture(exrTexture *tex, int x, int y, int w, int h, float order, bool inMem=false);
void onCapture(exrTexture *tex, int x, int y, int w, int h, bool inMem);

#endif /* defined(__HelloWorld__screenCapture__) */
