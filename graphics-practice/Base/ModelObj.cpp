//
//  ModelObj.cpp
//  graphics-practice
//
//  Created by loki on 2014. 11. 8..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "ModelObj.h"
#include "MyImage.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


ModelObj* ModelObj::Create(std::string path)
{
    ModelObj *pRet = new ModelObj();
    if( pRet->Init() && pRet->InitWithFile(path) ) {
        return pRet;
    }
    
    delete pRet;
    return NULL;
}

ModelObj::ModelObj()
{
    // vertex index is started from 1
    _vertices.push_back(Vector3());
    _texcoords.push_back(Vector2());
    _normals.push_back(Vector3());
}

ModelObj::~ModelObj()
{
    
}

bool ModelObj::InitWithFile(string path)
{
    ifstream inputFile( path.c_str(), ios::in | ios::binary );
    if ( inputFile.fail() )
        return false;	// "Couldn't open the model file."

    string dir;
    dir = path.substr( 0, path.find_last_of('/') + 1 );
    
    Object *currObj = NULL;
    
    string buffer;
    while( ! inputFile.eof() ) {
        inputFile >> buffer;
        if( buffer.compare("v") == 0 ) {
            Vector3 vertex;
            inputFile >> vertex.x >> vertex.y >> vertex.z;
            _vertices.push_back( vertex );
        }
        else if( buffer.compare("vt") == 0 ) {
            Vector2 coord;
            inputFile >> coord.x >> coord.y;
            _texcoords.push_back( coord );
        }
        else if( buffer.compare("vn") == 0 ) {
            Vector3 vertex;
            inputFile >> vertex.x >> vertex.y >> vertex.z;
            _normals.push_back( vertex );
        }
        else if( buffer.compare("f") == 0 ) {
            if( currObj == NULL ) {
                continue;
            }
            
            // i assumed all of faces are triangle
            string face1, face2, face3;
            inputFile >> face1 >> face2 >> face3;
            
            Face face;
            TokenizingFaceString(face1, face);
            TokenizingFaceString(face2, face);
            TokenizingFaceString(face3, face);
            currObj->_faces.push_back(face);
        }
        else if( buffer.compare("mtllib") == 0 ) {
            string filename;
            inputFile >> filename;
            string materialLibPath( dir );
            materialLibPath.append( filename );
            LoadMaterial( materialLibPath );
        }
        else if( buffer.compare("o") == 0 ) {
            string name;
            inputFile >> name;
            
            _objects[name] = Object();
            currObj = &_objects[name];
        }
        else if( buffer.compare("usemtl") == 0 ) {
            string matName;
            inputFile >> matName;
            currObj->_materialName = matName;
        }
        
        buffer.clear();
    }
    
   return true;
}

bool ModelObj::LoadMaterial(string path)
{
    ifstream inputFile( path.c_str(), ios::in | ios::binary );
    if ( inputFile.fail() )
        return false;
    
    string dir;
    dir = path.substr( 0, path.find_last_of('/') + 1 );

    Material *currMat = NULL;

    string buffer;
    while( ! inputFile.eof() ) {
        inputFile >> buffer;
        if( buffer.compare("Ns") == 0 ) {
            inputFile >> currMat->Ns;
        }
        else if( buffer.compare("Ka") == 0 ) {
            inputFile >> currMat->Ka[0] >> currMat->Ka[1] >> currMat->Ka[2];
        }
        else if( buffer.compare("Kd") == 0 ) {
            inputFile >> currMat->Kd[0] >> currMat->Kd[1] >> currMat->Kd[2];
        }
        else if( buffer.compare("Ks") == 0 ) {
            inputFile >> currMat->Ks[0] >> currMat->Ks[1] >> currMat->Ks[2];
        }
        else if( buffer.compare("Ni") == 0 ) {
            inputFile >> currMat->Ni;
        }
        else if( buffer.compare("d") == 0 ) {
            inputFile >> currMat->d;
        }
        else if( buffer.compare("illum") == 0 ) {
            inputFile >> currMat->illum;
        }
        else if( buffer.compare("map_Kd") == 0 ) {
            string newPath, filename;
            newPath = string( dir );
            inputFile >> filename;
            newPath.append( filename );

            currMat->img = MyImage::LoadImage( newPath );
            currMat->textureName = string(filename);
        }
        else if( buffer.compare("newmtl") == 0 ) {
            string name;
            inputFile >> name;
            _materials[name] = Material();
            currMat = &_materials[name];
        }
        
        buffer.clear();
    }

    return true;
}

void ModelObj::TokenizingFaceString(string str, Face& face)
{
    size_t left = 0, right = 0;
    string num;
    int n;
    
    right = str.find('/');
    num = str.substr(left, right);
    n = atoi(num.c_str());
    face._vertices.push_back(n);
    
    left = right + 1;
    right = str.find('/', left);
    num = str.substr(left, right);
    n = atoi(num.c_str());
    face._texcoords.push_back(n);
    
    left = right + 1;
    right = str.find('/', left);
    num = str.substr(left, right);
    n = atoi(num.c_str());
    face._normals.push_back(n);
}

void ModelObj::Draw()
{
    bool isTextureEnabled = glIsEnabled( GL_TEXTURE_2D );
    bool isBindTexture = false;
    float *originKa = new float[3];
    float *originKd = new float[3];
    float *originKs = new float[3];
    glGetMaterialfv( GL_FRONT, GL_AMBIENT, originKa );
    glGetMaterialfv( GL_FRONT, GL_DIFFUSE, originKd );
    glGetMaterialfv( GL_FRONT, GL_SPECULAR, originKs );

    auto iterObj = _objects.begin();
    while( iterObj != _objects.end() ) {
        isBindTexture = false;
        Object &obj = iterObj->second;
        if( obj._materialName.size() > 0 ) {
            auto iterMat = _materials.find( obj._materialName );
            if( iterMat != _materials.end() ) {
                Material &mat = iterMat->second;
                glMaterialfv( GL_FRONT, GL_AMBIENT, mat.Ka );
                glMaterialfv( GL_FRONT, GL_DIFFUSE, mat.Kd );
                glMaterialfv( GL_FRONT, GL_SPECULAR, mat.Ks );
                
                if ( mat.textureName.size() > 0 )
                {
                    glBindTexture( GL_TEXTURE_2D, mat.img->GetTexture() );
                    glEnable( GL_TEXTURE_2D );
                    isBindTexture = true;
                }
                else {
                    glDisable( GL_TEXTURE_2D );
                    isBindTexture = false;
                }
            }
        }
        
        
        glBegin(GL_TRIANGLES);
        auto faces = obj._faces;
        for(Face &face : faces) {
            vector<int> &fVertices = face._vertices;
            vector<int> &fTexCoords = face._texcoords;
            vector<int> &fNormals = face._normals;
            for( int i = 0; i < 3; i ++ ) {
                Vector3& v = _vertices[ fVertices[i] ];
                Vector2& t = _texcoords[ fTexCoords[i] ];
                Vector3& n = _normals[ fNormals[i] ];
                
                glVertex3f( v.x, v.y, v.z );
                if( isBindTexture ) {
                    glTexCoord2d( t.x, t.y );
                }
                glNormal3f( n.x, n.y, n.z );
            }
        }
        glEnd();
        
        iterObj++;
    }
    
    if ( isTextureEnabled ) {
        glEnable( GL_TEXTURE_2D );
    }
    else {
        glDisable( GL_TEXTURE_2D );
    }
    
    glMaterialfv( GL_FRONT, GL_AMBIENT, originKa );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, originKd );
    glMaterialfv( GL_FRONT, GL_SPECULAR, originKs );
    delete[] originKa;
    delete[] originKd;
    delete[] originKs;
}