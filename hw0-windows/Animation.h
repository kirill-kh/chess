#pragma once
#include "includes.h"
#include "figure.h"

class Animation
{

	public:
	figure * Figure;
	float it;
	vector<float> *Dots;


	Animation(figure * Fig, vector<float> * Dot);
	~Animation(void);
	vector<float> Bezie(float t)
	{
		vector<float> B;

		B.x = (1-t)*(1-t)*(1-t)*Dots[0].x + 3*t*(1-t)*(1-t)*Dots[1].x + 3*t*3*t*(1-t)*Dots[2].x + t*t*t*Dots[3].x;
		B.y = (1-t)*(1-t)*(1-t)*Dots[0].y + 3*t*(1-t)*(1-t)*Dots[1].y + 3*t*3*t*(1-t)*Dots[2].y + t*t*t*Dots[3].y;
		B.z = (1-t)*(1-t)*(1-t)*Dots[0].z + 3*t*(1-t)*(1-t)*Dots[1].z + 3*t*3*t*(1-t)*Dots[2].z + t*t*t*Dots[3].z;
		return B;
	}
	void DrawTheFigure()
	{
		glPushMatrix();
		vector<float> A = Bezie(it);
		glTranslatef(A.x,A.y,A.z);
		Figure->Drawing();
		glPopMatrix();
		it+=0.01;
	}

};

