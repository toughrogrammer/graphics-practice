//
//  ModelMilkshape3D.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 8..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__ModelMilkshape3D__
#define __graphics_practice__ModelMilkshape3D__

#include "Model.h"


class ModelMilkshape3D : public Model
{
public:
    static ModelMilkshape3D* Create(std::string path);
    virtual bool InitWithFile(std::string path);
};



#endif /* defined(__graphics_practice__ModelMilkshape3D__) */
