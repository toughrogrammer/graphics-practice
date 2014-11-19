//
//  ModelObj.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 8..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__ModelObj__
#define __graphics_practice__ModelObj__

#include "Model.h"
#include "../Math/Matrix.h"

#include <map>

class MyImage;
class ModelObj : public Model
{
	class Material
	{
	public:
		int illum = 0;
		float Ns = 0;
		float Ni = 0;
		float d = 0;
		float Ka[3] = { 0, };
		float Kd[3] = { 0, };
		float Ks[3] = { 0, };
		float Tf[3] = { 0, };
        std::string textureName;
		MyImage *img = NULL;
        
        ~Material()
        {
            if( img ) {
                delete img;
                img = NULL;
            }
        }
	};

	class Face
	{
	public:
		std::vector<int> _vertices;
        std::vector<int> _texcoords;
        std::vector<int> _normals;
	};

	class Object
	{
	public:
        std::vector<Face> _faces;
        std::string _materialName;
	};

private:
	std::map<std::string, Material> _materials;
	std::map<std::string, Object> _objects;

	std::vector<Vector3> _vertices;
	std::vector<Vector2> _texcoords;
	std::vector<Vector3> _normals;


public:
    static ModelObj* Create(std::string path);
    ModelObj();
    ~ModelObj();
    virtual bool InitWithFile(std::string path);
    bool LoadMaterial(std::string path);
    void TokenizingFaceString(std::string str, Face& face);
    virtual void Draw();

};



#endif /* defined(__graphics_practice__ModelObj__) */
