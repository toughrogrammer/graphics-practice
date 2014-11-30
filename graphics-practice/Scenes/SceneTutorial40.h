//
//  SceneTutorial40.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial40__
#define __graphics_practice__SceneTutorial40__

#include "Prefix.h"


class SceneTutorial40 : public Scene
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

	class Spring
	{
	public:
		Mass *mass1, *mass2;
		float springConstant, springLength, frictionConstant;

		Spring(Mass* mass1, 
			Mass* mass2, 
			float springConstant, 
			float springLength, 
			float frictionConstant)
		{
			this->springConstant = springConstant;
			this->springLength = springLength;
			this->frictionConstant = frictionConstant;

			this->mass1 = mass1;
			this->mass2 = mass2;
		}

		void Solve()
		{
			Vector3 springVector = mass1->pos - mass2->pos;
			float r = springVector.Length();
			
			Vector3 force;
			if (r != 0) {
				force += (springVector / r) * (r - springLength) * (-springConstant);
			}
			force += -(mass1->velocity - mass2->velocity) * frictionConstant;

			mass1->ApplyForce(force);
			mass2->ApplyForce(-force);
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
    
    class RopeSimulation : public Simulation				//An object to simulate a rope interacting with a planer surface and air
	{
	public:
		vector<Spring> springs;									//Springs binding the masses (there shall be [numOfMasses - 1] of them)

		Vector3 gravitation;								//gravitational acceleration (gravity will be applied to all masses)

		Vector3 ropeConnectionPos;							//A point in space that is used to set the position of the 
															//first mass in the system (mass with index 0)
		
		Vector3 ropeConnectionVel;							//a variable to move the ropeConnectionPos (by this, we can swing the rope)

		float groundRepulsionConstant;						//a constant to represent how much the ground shall repel the masses
		
		float groundFrictionConstant;						//a constant of friction applied to masses by the ground
															//(used for the sliding of rope on the ground)
		
		float groundAbsorptionConstant;						//a constant of absorption friction applied to masses by the ground
															//(used for vertical collisions of the rope with the ground)
		
		float groundHeight;									//a value to represent the y position value of the ground
															//(the ground is a planer surface facing +y direction)

		float airFrictionConstant;							//a constant of air friction applied to masses

		RopeSimulation(										//a long long constructor with 11 parameters starts here
			int numOfMasses,								//1. the number of masses
			float m,										//2. weight of each mass
			float springConstant,							//3. how stiff the springs are
			float springLength,								//4. the length that a spring does not exert any force
			float springFrictionConstant,					//5. inner friction constant of spring
			Vector3 gravitation,							//6. gravitational acceleration
			float airFrictionConstant,						//7. air friction constant
			float groundRepulsionConstant,					//8. ground repulsion constant
			float groundFrictionConstant,					//9. ground friction constant
			float groundAbsorptionConstant,					//10. ground absorption constant
			float groundHeight								//11. height of the ground (y position)
			) : Simulation(numOfMasses, m)					//The super class creates masses with weights m of each
		{
			this->gravitation = gravitation;
			
			this->airFrictionConstant = airFrictionConstant;

			this->groundFrictionConstant = groundFrictionConstant;
			this->groundRepulsionConstant = groundRepulsionConstant;
			this->groundAbsorptionConstant = groundAbsorptionConstant;
			this->groundHeight = groundHeight;

			for (int i = 0; i < masses.size(); i ++ )			//To set the initial positions of masses loop with for(;;)
			{
				masses[i].pos.x = i * springLength;		//Set x position of masses[a] with springLength distance to its neighbor
				masses[i].pos.y = 0;						//Set y position as 0 so that it stand horizontal with respect to the ground
				masses[i].pos.z = 0;						//Set z position as 0 so that it looks simple
			}

			for( int i = 0; i < masses.size() - 1; i ++ ) {
				Spring spring(&masses[i], &masses[i+1],
					springConstant, springLength, springFrictionConstant);
				springs.push_back(spring);
			}
		}

		virtual void Release()										//release() is overriden because we have springs to delete
		{
			Simulation::Release();							//Have the super class release itself

			springs.clear();
		}

		virtual void Solve()										//solve() is overriden because we have forces to be applied
		{
			for (int a = 0; a < masses.size() - 1; ++a)		//apply force of all springs
			{
				springs[a].Solve();						//Spring with index "a" should apply its force
			}

			for (int a = 0; a < masses.size(); ++a)				//Start a loop to apply forces which are common for all masses
			{
				masses[a].ApplyForce(gravitation * masses[a].m);				//The gravitational force
				
				masses[a].ApplyForce(-masses[a].velocity * airFrictionConstant);	//The air friction

				if (masses[a].pos.y < groundHeight)		//Forces from the ground are applied if a mass collides with the ground
				{
					Vector3 v;								//A temporary Vector3D

					v = masses[a].velocity;						//get the velocity
					v.y = 0;								//omit the velocity component in y direction

					//The velocity in y direction is omited because we will apply a friction force to create 
					//a sliding effect. Sliding is parallel to the ground. Velocity in y direction will be used
					//in the absorption effect.
					masses[a].ApplyForce(-v * groundFrictionConstant);		//ground friction force is applied

					v = masses[a].velocity;						//get the velocity
					v.x = 0;								//omit the x and z components of the velocity
					v.z = 0;								//we will use v in the absorption effect
					
					//above, we obtained a velocity which is vertical to the ground and it will be used in 
					//the absorption force

					if (v.y < 0)							//let's absorb energy only when a mass collides towards the ground
						masses[a].ApplyForce(-v * groundAbsorptionConstant);		//the absorption force is applied
					
					//The ground shall repel a mass like a spring. 
					//By "Vector3D(0, groundRepulsionConstant, 0)" we create a vector in the plane normal direction 
					//with a magnitude of groundRepulsionConstant.
					//By (groundHeight - masses[a]->pos.y) we repel a mass as much as it crashes into the ground.
					Vector3 force = Vector3(0, groundRepulsionConstant, 0) * (groundHeight - masses[a].pos.y);

					masses[a].ApplyForce(force);			//The ground repulsion force is applied
				}
			}
		}

		virtual void Simulate(float dt)								//simulate(float dt) is overriden because we want to simulate
															//the motion of the ropeConnectionPos
		{
			Simulation::Simulate(dt);						//the super class shall simulate the masses

			ropeConnectionPos += ropeConnectionVel * dt;	//iterate the positon of ropeConnectionPos

			if (ropeConnectionPos.y < groundHeight)			//ropeConnectionPos shall not go under the ground
			{
				ropeConnectionPos.y = groundHeight;
				ropeConnectionVel.y = 0;
			}

			masses[0].pos = ropeConnectionPos;				//mass with index "0" shall position at ropeConnectionPos
			masses[0].velocity = ropeConnectionVel;				//the mass's velocity is set to be equal to ropeConnectionVel
		}

		void SetRopeConnectionVel(Vector3 ropeConnectionVel)	//the method to set ropeConnectionVel
		{
			this->ropeConnectionVel = ropeConnectionVel;
		}

	};


private:
    RopeSimulation ropeSimulation;
    float slowMotionRatio = 15.0f;
    
    
public:
    static SceneTutorial40* Create();
    
    SceneTutorial40();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};


#endif /* defined(__graphics_practice__SceneTutorial40__) */
