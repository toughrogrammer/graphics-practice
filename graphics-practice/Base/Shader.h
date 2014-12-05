//
//  Shader.h
//  graphics-practice
//
//  Created by loki on 2014. 12. 5..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Shader__
#define __graphics_practice__Shader__

#include "GL.h"

#include <string>


class Shader {
private:
    GLuint _hProgram;
    GLuint _hVertexShader;
    GLuint _hFragmentShader;
    
    
public:
    Shader();
    Shader(std::string pathVertexShader, std::string pathFragmentShader);
    
    GLuint GetProgram();
    void LoadShader(const std::string pathVertex, const std::string pathFragment);
    void LoadVertexShader(const std::string path);
    void LoadFragmentShader(const std::string path);
    void ReadContentFromFile(const std::string path, std::string &result);
};



#endif /* defined(__graphics_practice__Shader__) */
