//
//  SceneTutorial39.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial39__
#define __graphics_practice__SceneTutorial39__

#include "Prefix.h"


class SceneTutorial39 : public Scene
{
	class Mass 
	{
	public:
		float m;
		Vector3 pos;
		Vector3 velocity;
		Vector3 force;

		Mass(float m) {
			this->m = m;
		}

		void ApplyForce(const Vector3& force) {
			this->force += force;
		}

		void Init() {
			this->force.Set(0, 0, 0);
		}

		void Simulate(float dt) {
			velocity += (force / m) * dt;
			pos += velocity * dt;
		}
	};

	class Simulation
	{
	public:
		vector<Mass> masses;

		Simulation(int numOfMasses, float m) {
			masses.resize( numOfMasses, Mass(m) );
		}

		virtual void Release() {
			masses.clear();
		}

		Mass& GetMass(int index) {
			return masses[index];
		}

		virtual void Init() {
			for( int i = 0; i < masses.size(); i ++ ) {
				masses[i].Init();
			}
		}

		virtual void Solve() {

		}

		virtual void Simulate(float dt) {
			for( int i = 0; i < masses.size(); i ++ ) {
				masses[i].Simulate( dt );
			}
		}

		virtual void Operate(float dt) {
			Init();
			Solve();
			Simulate(dt);
		}
	};
    
    class ConstantVelocity : public Simulation
    {
    public:
        ConstantVelocity() : Simulation(1, 1.0f) {
            masses[0].velocity.Set(1.0f, 0.0f, 0.0f);
        }
    };
    
    class MotionUnderGravitation : public Simulation
    {
    public:
        Vector3 gravitation;
        
        MotionUnderGravitation(const Vector3& g) : Simulation(1, 1.0f) {
            this->gravitation = g;
            masses[0].pos.Set(-10.0f, 0.0f, 0.0f);
            masses[0].velocity.Set(10.0f, 15.0f, 0.0f);
        }
        
        virtual void Solve() {
            for( int i = 0; i < masses.size(); i ++ ) {
                masses[i].ApplyForce(gravitation * masses[i].m);
            }
        }
    };
    
    class MassConnectedWithSpring : public Simulation
    {
    public:
        float springConstant;
        Vector3 connectionPos;
        
        MassConnectedWithSpring(float springConstant) : Simulation(1, 1.0f) {
            this->springConstant = springConstant;
            connectionPos.Set(0.0f, -5.0f, 0.0f);
            
            masses[0].pos = connectionPos + Vector3(10.0f, 0.0f, 0.0f);
        }
        
        virtual void Solve() {
            for( int i = 0; i < masses.size(); i ++ ) {
                Vector3 springVector = masses[i].pos - connectionPos;
                masses[i].ApplyForce(-springVector * springConstant);
            }
        }
    };


private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    ConstantVelocity constantVelocity;
    MotionUnderGravitation motionUnderGravitation;
    MassConnectedWithSpring massConnectedWithSpring;
    
    float slowMotionRatio = 10.0f;
    
    
public:
    static SceneTutorial39* Create();
    
    SceneTutorial39();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};


#endif /* defined(__graphics_practice__SceneTutorial39__) */
