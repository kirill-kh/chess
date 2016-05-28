#pragma once
#include"includes.h"
#include "vector.h"



class Draw
{
public:
	const float PI;
private:
	struct Knight
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}knight;
	struct Pawn
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}pawn;
	struct Queen
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}queen;
	struct Bishop
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}bishop;
	struct Castle
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}castle;
	struct King
	{
		vector<float> * Vertexes;
		vector<float> * Normals;
		int Count;
	}king;

public:
	
	Draw(void);
	~Draw(void);
	void Desk();
	void Horse();
	void Oficer();
	void Peshka(); 
	void Korol();
	void Tura();
	void Koroleva();

	void set_silver()
	{
		float silver_ambient[4] = {0.4, 0.4, 0.4, 1.00};
		float silver_diffuse[4] =  {0.5, 0.5, 0.5, 1.00};
		float silver_specular[4] = {0.77, 0.77, 0.77, 1.00};
		float silver_shines = 100;

		/*float silver_ambient[4] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
		float silver_diffuse[4] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
		float silver_specular[4]= {0.628281f, 0.555802f, 0.366065f, 1.0f };
		float silver_shines =51.2f ;*/
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,silver_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,silver_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,silver_specular);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,silver_shines);
	}
	void set_black()
	{
		float  mat_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[4] ={0.05f, 0.05f, 0.05f, 1.0f };
		float  mat_specular[4] ={0.50f, 0.50f, 0.50f, 1.0f };
		float shine =15.0f ;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
		/*float silver_ambient[4] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
		float silver_diffuse[4] = {0.75164f, 0.60648f, 0.22648f, 1.0f };
		float silver_specular[4]= {0.628281f, 0.555802f, 0.366065f, 1.0f };
		float silver_shines =51.2f ;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,silver_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,silver_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,silver_specular);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,silver_shines);*/
	}
	void set_fordesk()
	{
		float mat_ambient[4] ={ 0.19125f, 0.0735f, 0.0225f, 1.0f };
		float mat_diffuse[4] ={0.7038f, 0.27048f, 0.0828f, 1.0f };
		float mat_specular[4] ={0.256777f, 0.137622f, 0.086014f, 1.0f };
		float shine = 50;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);

	}


	void LoadFigure(const char * NameOfFigure, const char *  FileName);
};

