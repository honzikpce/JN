//
//  glTexture.h
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef glTexture_h
#define glTexture_h

#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL_opengl.h>


namespace JN {

struct GLTexture {
    GLuint id;
    int widht;
    int height;
};

}
    
#endif /* glTexture_h */
