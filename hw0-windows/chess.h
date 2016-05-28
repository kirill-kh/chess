#pragma once
#include "vector.h"
#include "figure.h"
#include "Animation.h"

class chess
{
public:
	vector2d<int> * ChosenPos;
	Draw * Obj;
	figure * Desk[8][8];
	Animation * AnimateObj;


	chess(Draw * A);
	~chess(void);
	bool CanChose;
	vector2d<int> * Chosenfigure;


	void DrawSituation();
	void set_ChosePos(vector2d<int> * Pos)
	{
		if (Pos == NULL)
		{
			if (Chosenfigure) 
			{
				Desk[Chosenfigure->x][Chosenfigure->y]->ischecked = 0;
				delete Chosenfigure;
				Chosenfigure = NULL;

			}
			return;
		}

		if (Chosenfigure == NULL)
		{
			if (Desk[Pos->x][Pos->y])
			{
				Chosenfigure = new vector2d<int>(Pos->x,Pos->y);
				Desk[Pos->x][Pos->y]->ischecked = 1;
			}
		}
		else
		{
			if (Pos->x == Chosenfigure->x && Pos->y == Chosenfigure->y) return;
			else
			{
				char * str = correctWays(Desk[Chosenfigure->x][Chosenfigure->y]->PosibleMoves());
				int i=0;
				if (str[0] == '\0') return;
				while (str[i-1]!='\0')
				{
					if (Pos->x == str[i]-'0' && Pos->y == str[i+1]-'0') 
					{
						figure * B = Desk[Chosenfigure->x][Chosenfigure->y];
						/*vector<float> * Vec = new vector<float>[4];
						Vec[0] = vector<float>(0,0,0);
						Vec[1] = vector<float>(0,0,20);
						Vec[2] = vector<float>(B->Position.x*10-Pos->x*10+40,B->Position.y*10-Pos->y*10,20);
						Vec[3] = vector<float>(B->Position.x*10-Pos->x*10+40,B->Position.y*10-Pos->y*10,0);
						AnimateObj = new Animation(B,Vec);*/

						Desk[Chosenfigure->x][Chosenfigure->y] = NULL;
						Desk[Pos->x][Pos->y] = B;
						Desk[Pos->x][Pos->y]->Position.x = Pos->x;
						Desk[Pos->x][Pos->y]->Position.y = Pos->y;
						Desk[Pos->x][Pos->y]->ischecked = 0;
						delete Chosenfigure;
						delete [] str;
						Chosenfigure = NULL;
						


						return;
					}
					i+=3;
				}
				Desk[Chosenfigure->x][Chosenfigure->y]->ischecked = 0;
				delete Chosenfigure;
				delete [] str;
				Chosenfigure = NULL;
			}
		}
	}
	char * DeleteFromStr(char * str, int first, int count)
	{
		for (int i=first; i<strlen(str)+3-count; i++)
		{
			str[i] = str[i+count];
		}
		/*if (str[strlen(str)-1] == ' ') 
			str[strlen(str)-1] ='\0';*/
		return str;
	}
	char * AddToStr(char * str, int x, int y)
	{
		int i= strlen(str);
		if (i!=0) str[i++] = ' ';
		str[i++] = x+'0';
		str[i++] = y+'0';
		str[i++] = '\0';
		return str;
		
	}
	char * correctWays(char * string)
	{
		figure * Using = Desk[Chosenfigure->x][Chosenfigure->y];

		if (strcmp(Using->kindofFigure,"pawn") == 0)
		{
			if (Using->Color == 1)
			{
				if (Desk[Chosenfigure->x+1][Chosenfigure->y]) string[0] = '\0';
				if (Desk[Chosenfigure->x+2][Chosenfigure->y] && Chosenfigure->x == 1) string[3] = '\0';
				if (Desk[Chosenfigure->x+1][Chosenfigure->y+1])
				{
					if (Desk[Chosenfigure->x+1][Chosenfigure->y+1]->Color == 0)
					{
						AddToStr(string,Chosenfigure->x+1,Chosenfigure->y+1);
					}
				}
				if (Desk[Chosenfigure->x+1][Chosenfigure->y-1])
				{
					if (Desk[Chosenfigure->x+1][Chosenfigure->y-1]->Color == 0)
					{
						AddToStr(string,Chosenfigure->x+1,Chosenfigure->y-1);
					}
				}
			}
			else 
			{
				if (Desk[Chosenfigure->x-1][Chosenfigure->y]) string[0] = '\0';
				if (Desk[Chosenfigure->x-2][Chosenfigure->y]) string[3] = '\0';
				if (Desk[Chosenfigure->x-1][Chosenfigure->y-1])
				{
					if (Desk[Chosenfigure->x-1][Chosenfigure->y-1]->Color ==1)
					{
						AddToStr(string,Chosenfigure->x-1,Chosenfigure->y-1);
					}
				}
				if (Desk[Chosenfigure->x-1][Chosenfigure->y+1])
				{
					if (Desk[Chosenfigure->x-1][Chosenfigure->y+1]->Color == 1)
					{
						AddToStr(string,Chosenfigure->x-1,Chosenfigure->y+1);
					}
				}
			}
			
		}
		if (strcmp(Using->kindofFigure,"king") == 0 || strcmp(Using->kindofFigure,"knight") == 0 )
		{
			for (int i=0; ;i+=3)
			{
				if (string[i] == '\0') break;
				if (Desk[string[i]-'0'][string[i+1]-'0'])
				{
					if (Desk[string[i]-'0'][string[i+1]-'0']->Color == Using->Color)
					{
						DeleteFromStr(string,i,3);
						i-=3;
					}
				}
			}
		}
		if (strcmp(Using->kindofFigure,"bishop") == 0)
		{
			for (int i=0; ;i+=3)
			{
				if (string[i] == '\0') break;
				if (Desk[string[i]-'0'][string[i+1]-'0'])
				{
					int priviousx = string[i];
					int priviousy = string[i+1];
					i+=3;
					while(abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 1)
					{
						priviousx = string[i];
						priviousy = string[i+1];
						DeleteFromStr(string,i,3);
						
					}
					i-=3;
					if (Desk[string[i]-'0'][string[i+1]-'0'])
					if (Desk[string[i]-'0'][string[i+1]-'0']->Color == Using->Color)
					{
						DeleteFromStr(string,i,3);
						i-=3;
					}
				}
			}
		}
		if (strcmp(Using->kindofFigure,"castle") == 0)
		{
			for (int i=0; ;i+=3)
			{
				if (string[i] == '\0') break;
				if (Desk[string[i]-'0'][string[i+1]-'0'])
				{
					int priviousx = string[i];
					int priviousy = string[i+1];
					i+=3;
					while((abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 0) || (abs(string[i]-priviousx) == 0 && abs(string[i+1] - priviousy) == 1))
					{
						priviousx = string[i];
						priviousy = string[i+1];
						DeleteFromStr(string,i,3);
						
					}
					i-=3;
					if (Desk[string[i]-'0'][string[i+1]-'0'])
					if (Desk[string[i]-'0'][string[i+1]-'0']->Color == Using->Color)
					{
						DeleteFromStr(string,i,3);
						i-=3;
					}
				}
			}
		}
		if (strcmp(Using->kindofFigure,"queen") == 0)
		{
			m2:
			for (int i=0; ;i+=3)
			{
				if (string[i] == '\0') break;
				if (Desk[string[i]-'0'][string[i+1]-'0'])
				{
					int priviousx = string[i];
					int priviousy = string[i+1];
					i+=3;
					while(abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 1)
					{
						priviousx = string[i];
						priviousy = string[i+1];
						DeleteFromStr(string,i,3);
						
					}
					if ((abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 0) || (abs(string[i]-priviousx) == 0 && abs(string[i+1] - priviousy) == 1)) goto m;
					i-=3;
					if (Desk[string[i]-'0'][string[i+1]-'0'])
					if (Desk[string[i]-'0'][string[i+1]-'0']->Color == Using->Color)
					{
						DeleteFromStr(string,i,3);
						i-=3;
					}
				}
			}
m:
			for (int i=0; ;i+=3)
			{
				if (string[i] == '\0') break;
				if (Desk[string[i]-'0'][string[i+1]-'0'])
				{
					int priviousx = string[i];
					int priviousy = string[i+1];
					i+=3;
					while((abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 0) || (abs(string[i]-priviousx) == 0 && abs(string[i+1] - priviousy) == 1))
					{
						priviousx = string[i];
						priviousy = string[i+1];
						DeleteFromStr(string,i,3);
						
					}
					if (abs(string[i]-priviousx) == 1 && abs(string[i+1] - priviousy) == 1) goto m2;
					i-=3;
					if (Desk[string[i]-'0'][string[i+1]-'0'])
					if (Desk[string[i]-'0'][string[i+1]-'0']->Color == Using->Color)
					{
						DeleteFromStr(string,i,3);
						i-=3;
					}
				}
			}
		}
		return string;
	}
	void DrawtheWays(figure * A)
	{
		char * str = correctWays(A->PosibleMoves());
		if (str[0] == '\0') return;
		Obj->set_fordesk();
		glBegin(GL_QUADS);
		for (int i=0; 1; i+=3)
		{
			if (i>2 && str[i-2] == '\0') break;
			glPushMatrix();
			int k = -39+10*(str[i]-'0');
			int k2 = -39+10*(str[i+1]-'0');
			//glTranslatef(-35+10*(str[i]-'0')/100,-35+10*(str[i+1]-'0')/100,0);
			glVertex3f(k,k2,0.1);
			glVertex3f(k,k2+8,0.1);
			glVertex3f(k+8,k2+8,0.1);
			glVertex3f(k+8,k2,0.1);
			glPopMatrix();

		}
		glEnd();
		delete[] str;
	}




};

