//
//  Shader.cpp
//  graphics-practice
//
//  Created by loki on 2014. 12. 5..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Shader.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "string.h"


using namespace std;


Shader::Shader()
{
    
}

Shader::Shader(string pathVertexShader, string pathFragmentShader)
{
    LoadShader(pathVertexShader, pathFragmentShader);
}

GLuint Shader::GetProgram()
{
    return _hProgram;
}

void Shader::LoadShader(const std::string pathVertex, const std::string pathFragment)
{
    _hProgram = glCreateProgram();
    LoadVertexShader(pathVertex);
    LoadFragmentShader(pathFragment);
    
    glAttachShader(_hProgram, _hVertexShader);
    glAttachShader(_hProgram, _hFragmentShader);
    
    glLinkProgram(_hProgram);
    
    glDeleteShader(_hVertexShader);
    glDeleteShader(_hFragmentShader);
}

void Shader::LoadVertexShader(const string path)
{
    string shaderCode;
    ReadContentFromFile(path, shaderCode);
    
    _hVertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    const char *src = shaderCode.c_str();
    int len = (int)shaderCode.length();
    glShaderSource(_hVertexShader, 1, &src, &len);
    glCompileShader(_hVertexShader);
    
    GLint success = GL_FALSE, logSize = 0;
    glGetShaderiv(_hVertexShader, GL_COMPILE_STATUS, &success);
    if( success == GL_FALSE ) {
        glGetShaderiv(_hVertexShader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> message(logSize);
        glGetShaderInfoLog(_hVertexShader, logSize, &logSize, &message[0]);
        for( int i = 0; i < message.size(); i ++ ) {
            cout << message[i];
        }
        cout << endl;
    }
}

void Shader::LoadFragmentShader(const string path)
{
    string shaderCode;
    ReadContentFromFile(path, shaderCode);
    
    _hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char *src = shaderCode.c_str();
    int len = (int)shaderCode.length();
    glShaderSource(_hFragmentShader, 1, &src , &len);
    glCompileShader(_hFragmentShader);
    
    GLint success = GL_FALSE, logSize = 0;
    glGetShaderiv(_hFragmentShader, GL_COMPILE_STATUS, &success);
    if( success == GL_FALSE ) {
        glGetShaderiv(_hFragmentShader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> message(logSize);
        glGetShaderInfoLog(_hFragmentShader, logSize, &logSize, &message[0]);
        for( int i = 0; i < message.size(); i ++ ) {
            cout << message[i];
        }
        cout << endl;
    }
}

void Shader::ReadContentFromFile(const string path, string &result)
{
    result.clear();
    
    ifstream ifs(path.c_str(), std::ios::in);
    if( ifs.fail() ) {
        return;
    }
    
    string buffer;
    while( ! ifs.eof() ) {
        buffer.clear();
        getline(ifs, buffer);
        result += "\n" + buffer;
    }
    
    ifs.close();
}
