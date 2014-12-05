//
//  Shader.cpp
//  graphics-practice
//
//  Created by loki on 2014. 12. 5..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Shader.h"
#include <fstream>

using namespace std;


Shader::Shader() 
{
	_hProgram = glCreateProgram();
}

Shader::Shader(string pathVertexShader, string pathFragmentShader) 
{
	_hProgram = glCreateProgram();
}

GLuint Shader::GetProgram() 
{
	return _hProgram;
}

void Shader::LoadShader(const std::string pathVertex, const std::string pathFragment)
{
    LoadVertexShader(pathVertex);
    LoadFragmentShader(pathVertex);

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
}

void Shader::ReadContentFromFile(const string path, string &result, bool linefeed)
{
	result.clear();

	ifstream ifs(path.c_str(), std::ios::in);
	if( ifs.fail() ) {
		return;
	}

    string buffer;
    while( ! ifs.eof() ) {
        ifs >> buffer;
        result.append(buffer);
        if( linefeed ) {
            result.append("\n");
        }
    }
    
    ifs.close();
}