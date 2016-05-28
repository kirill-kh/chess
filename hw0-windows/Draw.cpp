#include "Draw.h"


Draw::Draw(void): PI(3.14159)
{
	
}


Draw::~Draw(void)
{
}

void Draw::Desk()
{
	glBegin(GL_QUADS);
	glTexCoord2i(0,0); glNormal3f(0,0,-1); glVertex3f(-40,-40,0);
	glTexCoord2i(0,2); glNormal3f(0,0,-1); glVertex3f(-40,40,0);
	glTexCoord2i(2,2); glNormal3f(0,0,-1); glVertex3f(40,40,0);
	glTexCoord2i(2,0); glNormal3f(0,0,-1); glVertex3f(40,-40,0);
	glEnd();
}
void Draw::LoadFigure(const char * NameOfFigure, const char *  FileName)
{
	FILE * f = fopen(FileName,"r+");

	if (strcmp(NameOfFigure,"knight") == 0)
	{

		vector<float> *JustVertex = new vector<float> [4100];
		vector<float> *JustNormals = new vector<float>[7550];
		knight.Vertexes = new vector<float> [25000];
		knight.Normals = new vector<float> [25000];
		

		int vert=1;
		int norm=1;
		int vertnorm=0;

		char * str = new char [50];
		while (!feof(f))
		{
			fgets(str,50,f);
			if (str[0] == 'v') 
			{
				float x,y,z;
				sscanf(str,"v %f %f %f",&x,&y,&z);
				JustVertex[vert] = vector<float>(x,y,z);
				vert++;
			}
			if (str[1] == 'n')
			{
				float x,y,z;
				sscanf(str,"vn %f %f %f",&x,&y,&z);
				JustNormals[norm] = vector<float>(x,y,z);
				norm++;
			}
			if (str[0] == 'f')
			{
				int x,x1,y,y1,z,z1;
				sscanf(str,"f %i//%i %i//%i %i//%i",&x,&x1,&y,&y1,&z,&z1);
				knight.Vertexes[vertnorm] = JustVertex[x];
				knight.Normals[vertnorm] = JustNormals[x1];
				knight.Vertexes[vertnorm+1] = JustVertex[y];
				knight.Normals[vertnorm+1] = JustNormals[y1];
				knight.Vertexes[vertnorm+2] = JustVertex[z];
				knight.Normals[vertnorm+2] = JustNormals[z1];
				vertnorm+=3;
			}
		}
		for (int i=0; i<4100; i++)
		{
			JustVertex[i].~vector();
		}
		for (int i=0; i<7550; i++)
		{
			JustNormals[i].~vector();
		}

		knight.Count = vertnorm;

		for (int i=0; i<vertnorm; i+=3)
		{
			vector<float> A = A.vecmul((knight.Vertexes[i]-knight.Vertexes[i+1]),(knight.Vertexes[i]-knight.Vertexes[i+2]));
			knight.Normals[i] = A;
			knight.Normals[i+1] = A;
			knight.Normals[i+2] = A;
			
		}

		
	}
	
	
	fclose(f);
}
void Draw::Horse()
{
	// А потом попросим OpenGL отрендерить фигуры из массива:
glEnableClientState(GL_VERTEX_ARRAY);   // Включаем режим вершинных массивов.
glEnableClientState(GL_NORMAL_ARRAY);
glPushMatrix();
glRotatef(90,1.0,0,0);
glScalef(3.5,3.5,3.5);
glTranslatef(0,1,0);
glEnable(GL_NORMALIZE);
// Делаем это только один раз (или если позже выключим), как и glEnable().

// Указываем OpenGL исходный массив. Передаём кол-во координат для каждой
// точки (x,y,z), тип данных (float), размер структуры и саму структуру.
glVertexPointer(3,GL_FLOAT,sizeof(vector<float>),knight.Vertexes);
glNormalPointer(GL_FLOAT,0,knight.Normals);

glDrawArrays(GL_TRIANGLES,0,knight.Count);

glPopMatrix();
glDisable(GL_NORMALIZE);
glDisableClientState(GL_NORMAL_ARRAY);
glDisableClientState(GL_VERTEX_ARRAY);


	/*glBegin(GL_LINES);

	for (int i=0; i<knight.Count; i++)
	{
		glVertex3f(knight.Vertexes[i].x,this->HorseVertexes[i].y,this->HorseVertexes[i].z);
		glVertex3f(this->HorseNoramls[i].x+this->HorseVertexes[i].x,this->HorseNoramls[i].y+this->HorseVertexes[i].y,this->HorseNoramls[i].z+this->HorseVertexes[i].z);
	}

	glEnd();*/
}
void Draw::Oficer()
{
	GLUquadric * A = gluNewQuadric();
	int stacks = 16;

	glPushMatrix();
	glScalef(0.8,0.8,0.8);
	gluCylinder(A,3.5,3.5,2,stacks,stacks);
	glTranslatef(0,0,2);
	glScalef(1,1,0.5);
	gluSphere(A,3.5,stacks,stacks);
	glPopMatrix();

	glBegin(GL_QUAD_STRIP);
	for (float i=2.5; i<7.9; i+=0.1)
	{
		for (float j=0; j<= 2*PI; j+=2*PI/stacks)
		{
			glNormal3f(cos(j),sin(j),(i-7)/4.5*(i-7)/4.5);
			glVertex3f( (0.75+(i-7)/5.5*(i-7)/5.5)*cos(j),(0.75+(i-7)/5.5*(i-7)/5.5)*sin(j),i);
			i+=0.1;
			glNormal3f(cos(j),sin(j),(i-7)/4.5*(i-7)/4.5);
			glVertex3f( (0.75+(i-7)/5.5*(i-7)/5.5)*cos(j),(0.75+(i-7)/5.5*(i-7)/5.5)*sin(j),i);
			
			i-=0.1;
		}
	}
	glEnd();

	glPushMatrix();
	glTranslatef(0,0,8);
	gluDisk(A,0,2.5,stacks,stacks);
	glPopMatrix();


	glPushMatrix();
	glScalef(0.8,0.8,1);
	glBegin(GL_QUAD_STRIP);
	for (float i=8; i<10.9; i+=0.1)
	{
		for (float j=0; j<= 2*PI; j+=2*PI/stacks)
		{
			glNormal3f(cos(j),sin(j),2-(i-9)*(i-9));
			glVertex3f( (2-(i-9)*(i-9)/2.5)*cos(j),(2-(i-9)*(i-9)/2.5)*sin(j),i);
			i+=0.1;
			glNormal3f(cos(j),sin(j),2-(i-9)*(i-9));
			glVertex3f( (2-(i-9)*(i-9)/2.5)*cos(j),(2-(i-9)*(i-9)/2.5)*sin(j),i);
			
			i-=0.1;
		}
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,11);
	gluSphere(A,0.5,stacks,stacks);
	glPopMatrix();

	gluDeleteQuadric(A);
}
void Draw::Peshka()
{
	int stacks = 8;
	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(4*cos(i),4*sin(i), 0.1);
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(4*cos(i),4*sin(i), 3);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	for (float j=0; j<=PI; j+= PI/8)
	{
		for (float i=0; i<=2*PI; i+=PI/stacks)
		{
			glNormal3f(cos(i),sin(i),cos(j));
			glVertex3f((3+cos(j))*cos(i),(3+cos(j))*sin(i), 2*j+3);
			
			j+=PI/8;
			glNormal3f(cos(i),sin(i),cos(j));
			glVertex3f((3+cos(j))*cos(i),(3+cos(j))*sin(i), 2*j+3);
			j-= PI/8;
		}
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glNormal3f(0,0,1);

	
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(0,0,1);
		glVertex3f(3.5*cos(i),3.5*sin(i),10.1);
		glNormal3f(0,0,1);
		glVertex3f(0,0,10.1);
	}
	glEnd();

	glPushMatrix();
	glTranslatef(0,0,12.2);
	glutSolidSphere(2.5,stacks,stacks);
	glPopMatrix();
}
void Draw::Korol()
{
	int stacks = 8;
	GLUquadric * A = gluNewQuadric();
	glPushMatrix();
	glScalef(0.85,0.85,1);
	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(5*cos(i),5*sin(i), 0.1);
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(5*cos(i),5*sin(i), 1.5);
	}
	glEnd();
	//диск 

	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(0,0,1);
		glVertex3f(5*cos(i),5*sin(i),1.5);
		glNormal3f(0,0,1);
		glVertex3f(4*cos(i),4*sin(i),1.5);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(4*cos(i),4*sin(i), 1.5);
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(4*cos(i),4*sin(i), 3);
	}
	glEnd();
	//disk
	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(0,0,1);
		glVertex3f(4*cos(i),4*sin(i),3);
		glNormal3f(0,0,1);
		glVertex3f(2.5*cos(i),2.5*sin(i),3);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (float k=0; k<=1.5; k+= 0.1)
	{
		for (float i=0; i<=2*PI; i+=PI/stacks)
		{
			glNormal3f(cos(i), sin(i), -1);
			glVertex3f((2.5+k)*cos(i),(2.5+k)*sin(i), k+3); 
			glNormal3f(cos(i), sin(i), -1);
			glVertex3f((2.5+k+0.1)*cos(i),(2.5+k+0.1)*sin(i), k+3+0.1); 
		}
	}
	glEnd();


	glBegin(GL_QUAD_STRIP);
	
	for (float j = 4.5; j< 12; j+=0.5)
	{
		for (float i = 0; i <=2*PI; i+= PI/stacks)
		{
			glNormal3f(cos(i),sin(i), 0);
			glVertex3f((4-exp(j*0.1)) * cos(i), (4-exp(j*0.1)) * sin(i), j);
			glNormal3f(cos(i),sin(i), 0);
			glVertex3f((4-exp((j+0.5)*0.1)) * cos(i), (4-exp((j+0.5)*0.1)) * sin(i), j+0.5);
		}
	}
	glEnd();
	//disk
	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<=2*PI; i+=PI/stacks)
	{
		glNormal3f(0,0,1);
		glVertex3f(4*cos(i),4*sin(i),4.5);
		glNormal3f(0,0,1);
		glVertex3f(2*cos(i),2*sin(i),4.5);

	}
	glEnd();

	stacks *=2;
	glPushMatrix();
	glTranslatef(0,0,12);
	gluDisk(A,0,3,stacks,stacks);
	gluCylinder(A,3,3,1,stacks,stacks);
	glTranslatef(0,0,1);
	gluDisk(A,0,3,stacks,stacks);
	gluCylinder(A,1,2,2,4,4);
	glTranslatef(0,0,2);
	gluDisk(A,0,2,4,4);
	glTranslatef(0,0,1);
	glScalef(0.5,0.5,1);
	glutSolidCube(2);
	glScalef(1,2,0.5);
	glutSolidCube(2);
	glPopMatrix();

	gluDeleteQuadric(A);
	glPopMatrix();
}
void Draw::Tura()
{
	GLUquadric * A = gluNewQuadric();
	int stacks = 16;

	glPushMatrix();
	gluCylinder(A,4,4,2,stacks,stacks);
	glTranslatef(0,0,2);
	gluDisk(A,0,4,stacks,stacks);
	gluCylinder(A,3,2.5,6,stacks,stacks);
	glTranslatef(0,0,6);
	gluDisk(A,0,3,stacks,stacks);
	
	glPopMatrix();

	glBegin(GL_QUADS);
	for (float i=0; i<2*PI; i+=2*PI/stacks)
	{
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(3*cos(i),3*sin(i),8);
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(3*cos(i),3*sin(i),10);
	}

	for (float i=2*PI/stacks; i<=2*PI; i+=2*PI/stacks)
	{
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(3*cos(i),3*sin(i),8);
		glNormal3f(cos(i),sin(i),0);
		glVertex3f(3*cos(i),3*sin(i),9);
	}

	glEnd();



	gluDeleteQuadric(A);
}
void Draw::Koroleva()
{
	GLUquadric * A = gluNewQuadric();
	int stacks = 16;


	glPushMatrix();
	gluCylinder(A,4,4,1.5,stacks,stacks);
	glTranslatef(0,0,1.5);
	gluDisk(A,0,4,stacks,stacks);
	glTranslatef(0,0,0.75);
	glScalef(2,2,1);
	gluSphere(A,1.5,stacks,stacks);
	glPopMatrix();
	
	glBegin(GL_QUAD_STRIP);
	for (float i=3; i<8.9; i+=0.1)
	{
		for (float j=0; j<= 2*PI; j+=2*PI/stacks)
		{
			glNormal3f(cos(j),sin(j),(i-7)/4.5*(i-7)/4.5);
			glVertex3f( (1+(i-7)/4.5*(i-7)/4.5)*cos(j),(1+(i-7)/4.5*(i-7)/4.5)*sin(j),i);
			i+=0.1;
			glNormal3f(cos(j),sin(j),(i-7)/4.5*(i-7)/4.5);
			glVertex3f( (1+(i-7)/4.5*(i-7)/4.5)*cos(j),(1+(i-7)/4.5*(i-7)/4.5)*sin(j),i);
			
			i-=0.1;
		}
	}
	glEnd();

	glPushMatrix();
	glTranslatef(0,0,9);
	gluDisk(A,0,2.5,stacks,stacks);
	glPopMatrix();

	glBegin(GL_QUAD_STRIP);
	for (float i=9; i<11.9; i+=0.1)
	{
		for (float j=0; j<= 2*PI; j+=2*PI/stacks)
		{
			glNormal3f(cos(j),sin(j),1+(i-10.5)*(i-10.5)/3-1);
			glVertex3f( (1+(i-10.5)*(i-10.5)/3)*cos(j),(1+(i-10.5)*(i-10.5)/3)*sin(j),i);
			i+=0.1;
			glNormal3f(cos(j),sin(j),1+(i-10.5)*(i-10.5)/3-1);
			glVertex3f( (1+(i-10.5)*(i-10.5)/3)*cos(j),(1+(i-10.5)*(i-10.5)/3)*sin(j),i);
			
			i-=0.1;
		}
	}
	glEnd();
	
	glPushMatrix();
	glTranslatef(0,0,12.5);
	gluSphere(A,1,stacks,stacks);
	glPopMatrix();

	gluDeleteQuadric(A);
}


