
#include "includes.h"
#include "Draw.h"
#include "chess.h"

GLuint Program;
GLint  Attrib_vertex;
GLint unif_EyePosition;
GLint unif_TheColor;
GLint Textu;

GLuint texture[1];
AUX_RGBImageRec * Chess;

float Lastclick = 0;

float light_position[3] = {100,0,0};
float light_position2[3] = {-50,-50,0};

Draw A;
chess Game(&A);


void LoadTexture()
{
	Chess = auxDIBImageLoadA("chess.bmp");
	glGenTextures(1,&texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Chess->sizeX, Chess->sizeY,0,
		GL_RGB, GL_UNSIGNED_BYTE, Chess->data);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

char * ReadTxtInString(char Sh)
{
	FILE * f;
	if (Sh == 'V')
		f = fopen("VertShader.txt","r+");
	else 
		f = fopen("FragShader.txt","r+");

	int a=0;
	fgetc(f);
	while(!feof(f)) 
	{
		a++;
		fgetc(f);
	}

	fseek(f,0,SEEK_SET);
	char * String = new char [a+2];
	int c = 0 ;
	do
	String[c++] = fgetc(f);
	while (!feof(f));

	return String;
}
void shaderLog(unsigned int shader) 
{ 
	int   infologLen   = 0;
	int   charsWritten = 0;
	char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

	if(infologLen > 1)
	{ 
		infoLog = new char[infologLen];
		if(infoLog == NULL)
		{
			std::cout<<"ERROR: Could not allocate InfoLog buffer\n";
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout<< "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}
void checkOpenGLerror()
{
	GLenum errCode;
	if((errCode=glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}
void initShader()
{
	//! Исходный код шейдеров


	const char* vsSource = ReadTxtInString('V');
	const char* fsSource = ReadTxtInString('F');

	//! Переменные для хранения идентификаторов шейдеров
	GLuint vShader, fShader;

	//! Создаем вершинный шейдер
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//! Передаем исходный код
	glShaderSource(vShader, 1, &vsSource, NULL);
	//! Компилируем шейдер
	glCompileShader(vShader);

	std::cout << "vertex shader \n";
	shaderLog(vShader);

	//! Создаем фрагментный шейдер
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//! Передаем исходный код
	glShaderSource(fShader, 1, &fsSource, NULL);
	//! Компилируем шейдер
	glCompileShader(fShader);

	std::cout << "fragment shader \n";
	shaderLog(fShader);

	//! Создаем программу и прикрепляем шейдеры к ней
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);

	//! Линкуем шейдерную программу
	glLinkProgram(Program);

	//! Проверяем статус сборки
	int link_ok;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
	if(!link_ok)
	{
		std::cout << "error attach shaders \n";
		return;
	}

	const char * unif_name = "eyepos";
	unif_TheColor = glGetUniformLocation(Program,unif_name);
	if(unif_EyePosition == -1)
	{
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}
	const char * unif_name2 = "TheColor";
	unif_TheColor = glGetUniformLocation(Program,unif_name2);
	if(unif_TheColor == -1)
	{
		std::cout << "could not bind uniform " << unif_name2 << std::endl;
		return;
	}


	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	Textu = glGetUniformLocation(Program, "tex") ; 
	glUniform1i(Textu,GL_TEXTURE0); // Could also be GL_TEXTURE0 */

	glUseProgram(Program); 
	checkOpenGLerror();
}
void freeShader()
{
	//! Передавая ноль, мы отключаем шейдрную программу
	glUseProgram(0); 
	//! Удаляем шейдерную программу
	glDeleteProgram(Program);
}

vector2d<int>*  whichRectangular(int x, int y)
{
	GLint  viewport[4]; // Место для данных окна просмотра
	GLdouble mvmatrix[16], projmatrix[16]; // Место для матрицы трансформации


	glGetIntegerv (GL_VIEWPORT, viewport); // Извлечь текущее окно просмотра
	glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix); // Извлечь текущую матрицу просмотра
	glGetDoublev (GL_PROJECTION_MATRIX, projmatrix); // Извлечь матрицу проекции

	GLdouble x1,y1,z1;
	float zbuf;
	glReadPixels(x,viewport[3]-y-1,1,1,GL_DEPTH_COMPONENT, GL_FLOAT,&zbuf);

	gluUnProject(x,viewport[3]-y-1,zbuf,mvmatrix,projmatrix,viewport,&x1,&y1,&z1);

	y1 =y1;
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			if (x1>(-40+10*i+z1))
			{
				if (x1<(-30+10*i+z1))
				{
					if (y1>(-40+10*j+z1))
					{
						if (y1<(-30+10*j+z1))
						{
							vector2d<int> * X = new vector2d<int>(i,j);
							return X;
						}
					}
				}
			}
		}
	}
	return NULL;

}

float Scale = 1;
int px = 0;
int py = 0;
float latitude = 0;
float longitude = 0;
bool looking = true;

float Position[3] = {0,0,150};


float PI = 3.14159;

//void DrawDesk()
//{
//	glBegin(GL_QUADS);
//	glTexCoord2i(0,0); glNormal3f(0,0,-1); glVertex3f(-40,-40,0);
//	glTexCoord2i(0,2); glNormal3f(0,0,-1); glVertex3f(-40,40,0);
//	glTexCoord2i(2,2); glNormal3f(0,0,-1); glVertex3f(40,40,0);
//	glTexCoord2i(2,0); glNormal3f(0,0,-1); glVertex3f(40,-40,0);
//	glEnd();
//}
////void Peshka(int stacks)
////{
////	glBegin(GL_QUAD_STRIP);
////	for (float i=0; i<=2*PI; i+=PI/stacks)
////	{
////		glNormal3f(cos(i),sin(i),0);
////		glVertex3f(4*cos(i),4*sin(i), 0.1);
////		glNormal3f(cos(i),sin(i),0);
////		glVertex3f(4*cos(i),4*sin(i), 3);
////	}
////	glEnd();
////	
////	glBegin(GL_QUAD_STRIP);
////	for (float j=0; j<=PI; j+= PI/8)
////	{
////		for (float i=0; i<=2*PI; i+=PI/stacks)
////		{
////			glNormal3f(cos(i),sin(i),cos(j));
////			glVertex3f((3+cos(j))*cos(i),(3+cos(j))*sin(i), 2*j+3);
////			
////			j+=PI/8;
////			glNormal3f(cos(i),sin(i),cos(j));
////			glVertex3f((3+cos(j))*cos(i),(3+cos(j))*sin(i), 2*j+3);
////			j-= PI/8;
////		}
////	}
////	glEnd();
////
////	glBegin(GL_QUAD_STRIP);
////	glNormal3f(0,0,1);
////
////	
////	for (float i=0; i<=2*PI; i+=PI/stacks)
////	{
////		glNormal3f(0,0,1);
////		glVertex3f(3.5*cos(i),3.5*sin(i),10.1);
////		glNormal3f(0,0,1);
////		glVertex3f(0,0,10.1);
////	}
////	glEnd();
////
////	glPushMatrix();
////	glTranslatef(0,0,12.2);
////	glutSolidSphere(2.5,stacks,stacks);
////	glPopMatrix();
////}
//void King(int stacks)
//{
//	//нижнее кольцо
//	glBegin(GL_QUAD_STRIP);
//	for (float i=0; i<=2*PI; i+=PI/stacks)
//	{
//		glNormal3f(cos(i),sin(i),0);
//		glVertex3f(5*cos(i),5*sin(i), 0.1);
//		glNormal3f(cos(i),sin(i),0);
//		glVertex3f(5*cos(i),5*sin(i), 1.5);
//	}
//	glEnd();
//	//диск 
//
//	glBegin(GL_QUAD_STRIP);
//	for (float i=0; i<=2*PI; i+=PI/stacks)
//	{
//		glNormal3f(0,0,1);
//		glVertex3f(5*cos(i),5*sin(i),1.5);
//		glNormal3f(0,0,1);
//		glVertex3f(4*cos(i),4*sin(i),1.5);
//	}
//	glEnd();
//
//	glBegin(GL_QUAD_STRIP);
//	for (float i=0; i<=2*PI; i+=PI/stacks)
//	{
//		glNormal3f(cos(i),sin(i),0);
//		glVertex3f(4*cos(i),4*sin(i), 1.5);
//		glNormal3f(cos(i),sin(i),0);
//		glVertex3f(4*cos(i),4*sin(i), 3);
//	}
//	glEnd();
//	//disk
//	glBegin(GL_QUAD_STRIP);
//	for (float i=0; i<=2*PI; i+=PI/stacks)
//	{
//		glNormal3f(0,0,1);
//		glVertex3f(4*cos(i),4*sin(i),3);
//		glNormal3f(0,0,1);
//		glVertex3f(2.5*cos(i),2.5*sin(i),3);
//	}
//	glEnd();
//
//	glBegin(GL_QUAD_STRIP);
//	for (float k=0; k<=1.5; k+= 0.1)
//	{
//		for (float i=0; i<=2*PI; i+=PI/stacks)
//		{
//			glNormal3f(cos(i), sin(i), -1);
//			glVertex3f((2.5+k)*cos(i),(2.5+k)*sin(i), k+3); 
//			glNormal3f(cos(i), sin(i), -1);
//			glVertex3f((2.5+k+0.1)*cos(i),(2.5+k+0.1)*sin(i), k+3+0.1); 
//		}
//	}
//	glEnd();
//
//
//	glBegin(GL_QUAD_STRIP);
//	
//	for (float j = 4.5; j< 12; j+=0.5)
//	{
//		for (float i = 0; i <=2*PI; i+= PI/stacks)
//		{
//			glNormal3f(cos(i),sin(i), exp(j*0.1));
//			glVertex3f((4-exp(j*0.1)) * cos(i), (4-exp(j*0.1)) * sin(i), j);
//			glNormal3f(cos(i),sin(i), exp((j+0.5)*0.1));
//			glVertex3f((4-exp((j+0.5)*0.1)) * cos(i), (4-exp((j+0.5)*0.1)) * sin(i), j+0.5);
//		}
//	}
//	glEnd();
//	//disk
//	glBegin(GL_QUAD_STRIP);
//	for (float i=0; i<=2*PI; i+=PI/stacks)
//	{
//		glNormal3f(0,0,1);
//		glVertex3f(4*cos(i),4*sin(i),4.5);
//		glNormal3f(0,0,1);
//		glVertex3f(2*cos(i),2*sin(i),4.5);
//
//	}
//	glEnd();
//}





void Keybord(unsigned char key, int x, int y)
{
	switch(key) 
	{

	case '1':
		Scale*=0.8;
		break;
	case '2':
		Scale*=1.25;
		break;
	}
}
void Display()
{

	glLoadIdentity();
	gluLookAt(Position[0],Position[1],Position[2],0,0,0,0,1,0);
	//glTranslatef(0.0, 0.0, -100.0); // отодвинуться от сцены
	glRotatef(latitude, 1.0, 0.0, 0.0); // повернуть камеру по широте
	glRotatef(longitude, 0.0, 0.0, 1.0); // повернуть камеру по долготе

	glScalef(Scale,Scale,Scale);

	glUniform3f(unif_EyePosition,Position[0],Position[1],Position[2]);

	/*static float light[3] = {50,50,50};
	glUniform3fv(lightDir,1,light);*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION,light_position2);


	glLightfv(GL_LIGHT0, GL_POSITION,light_position);

	glPushMatrix();
	glTranslatef(light_position[0],light_position[1],light_position[2]);
	glUniform1i(unif_TheColor, 1);
	//glutSolidSphere(5,5,5);
	glPopMatrix();

	glPushMatrix();
	float mat[3] = {Position[0],Position[1],Position[2]};

	glTranslatef(Position[0], Position[1], Position[2]);

	//glutSolidCube(10);
	glPopMatrix();

	float light_ambient[4] = {0.33, 0.33, 0.33, 1.00};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	float light_diffuse[4] = {1.0, 1.0, 1.0, 1.00};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	float light_specular[4] = {0.57, 0.57, 0.77, 1.00};
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular);
	float fonlight[4] = {0.3,0.3,0.3,0.3};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,fonlight);

	glUniform1i(unif_TheColor, 0);
	A.set_silver();
	A.Desk();

	/*float silver_ambient[4] = {0.4, 0.4, 0.4, 1.00};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,silver_ambient);
	float silver_diffuse[4] =  {0.5, 0.5, 0.5, 1.00};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,silver_diffuse);
	float silver_specular[4] = {0.77, 0.77, 0.77, 1.00};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,silver_specular);
	float silver_shines = 100;
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,silver_shines);*/

	glUniform1i(unif_TheColor,1);
	/*glPushMatrix();
	glScalef(0.6,0.6,0.75);
	Peshka(15);
	glPopMatrix();*/

	// King(8);
	//glutSolidTorus(10,20,300,300);

	//A.Peshka();
	//A.Korol();

	Game.DrawSituation();

	//freeShader();

	glPushMatrix();
	glScalef(5,5,5);
	glRotatef(90,1.0,0,0);
	glTranslatef(0,5,0);
	//A.Horse();

	glPopMatrix();
	glPushMatrix();
	glRotatef(90,1.0,0,0);
	glTranslatef(0,5,0);
	glScalef(5,5,5);


	glPopMatrix();




	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}
void MouseMove (int x, int y)
{
	looking = false;
}
void MousePressed(int button, int state, int x, int y)
{

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (Game.CanChose)
		{
			if (clock() - Lastclick > 300)
			{
				Game.set_ChosePos(whichRectangular(x,y));
				Lastclick = clock();
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		looking = true;
		px = x;
		py = y;
		break;
	}
}
void MousePressedMove(int x, int y)
{
	if( looking )
	{
		if( px && x>px ){
			longitude = longitude + float(x-px)/7.0; // чем быстрее двигаем мышкой тем угол поворота больше
			// if ( longitude < -180.0 ) longitude = -180.0;
		}
		if( px && x<px ){
			longitude = longitude - float(px-x)/7.0;
			// if ( longitude > 180.0 ) longitude = 180.0;
		}
		if( py && y<py ){
			latitude = latitude - float(py-y)/3.0;
			// if ( latitude > 90.0 ) latitude = 90.0;
		}
		if( py && y>py ){
			latitude = latitude + float(y-py)/3.0;
			// if ( latitude < 0.0 ) latitude = 0.0;
		}
		px=x; py=y;
	}
}

void InitOpenGL(int * argc, char ** argv)
{
	glutInit(argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Magic Chess");

	GLenum glew_status = glewInit();
	if(GLEW_OK != glew_status) 
	{
		std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
		system("pause");
		//return 0;
	}

	if(!GLEW_VERSION_2_0) 
	{
		//! OpenGl 2.0 оказалась не доступна
		std::cout << "No support for OpenGL 2.0 found\n";
		system("pause");
		//return 1;
	}
	initShader();

	LoadTexture();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keybord);
	glutMotionFunc(MousePressedMove);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MousePressed);
	// glutTimerFunc(0, Timer, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1,1,-1,1,5000,-5000);
	gluPerspective ( 40 , 1.0, 5 , 5000);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,1.0);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST) ;
	glDepthFunc(GL_LESS) ; // The default option
	glEnable(GL_NORMALIZE);
}

int main(int argc, char ** argv)
{
	//BlendeFigures A;
	A.LoadFigure("knight","Horse.txt");

	InitOpenGL(&argc, argv);

	glutMainLoop();
	freeShader();

	system("pause");
	return 0;
}