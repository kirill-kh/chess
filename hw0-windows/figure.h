#pragma once
#include "vector.h"
#include "Draw.h"

class figure 
{
	public:
	Draw * Dr;
	int Color;
	vector2d<int> Position;
	
	char * kindofFigure;

	bool ischecked;


	void Drawing();
	char * PosibleMoves()
	{
		if (strcmp(kindofFigure,"pawn") == 0)
		{
			if (Color == 1)
			{
				char * str = new char [50];
				if (Position.x<7)
				{
					str[0] = Position.x+1+'0';
					str[1] = Position.y+'0';
				}
				if (Position.x == 1) 
				{
					str[2] = ' ';
					str[3] = Position.x+2+'0';
					str[4] = Position.y+'0';
				}
				str[5] = '\0';
				return str;
			}
			if (Color == 0)
			{
				char * str = new char [50];
				if (Position.x >0) 
				{
					str[0] = Position.x-1+'0';
					str[1] = Position.y+'0';
				}
				if (Position.x == 6) 
				{
					str[2] = ' ';
					str[3] = Position.x-2+'0';
					str[4] = Position.y+'0';
				}
				str[5] = '\0';
				return str;
			}
		}

		if (strcmp(kindofFigure,"castle") == 0)
		{
			char * str= new char [50];
			int ch =0;
			int i,j;
			i = Position.x;
			j = Position.y;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				j++;
			}
			i = Position.x;
			j = Position.y;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
			}
			i = Position.x;
			j = Position.y;
			i--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
			}
			str[ch] = '\0';
			return str;
		}
		if (strcmp(kindofFigure,"bishop") == 0)
		{
			char * str= new char [50];
			int ch =0;
			int i,j;
			i = Position.x;
			j = Position.y;
			i++;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
				j++;
			}
			i = Position.x;
			j = Position.y;
			i--;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i++;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i--;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
				j++;
			}
			str[ch] = '\0';
			return str;
		}

		if (strcmp(kindofFigure,"queen") == 0)
		{
			char * str= new char [100];
			int ch =0;
			int i,j;
			i = Position.x;
			j = Position.y;
			i++;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
				j++;
			}
			i = Position.x;
			j = Position.y;
			i--;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i++;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i--;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
				j++;
			}
			
			i = Position.x;
			j = Position.y;
			j++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				j++;
			}
			i = Position.x;
			j = Position.y;
			j--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				j--;
			}
			i = Position.x;
			j = Position.y;
			i++;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i++;
			}
			i = Position.x;
			j = Position.y;
			i--;
			while (i >-1 && i<8 && j>-1 && j<8)
			{
				str[ch] = i+'0';
				str[ch+1] = j+'0';
				str[ch+2] = ' ';
				ch+=3;
				i--;
			}
			str[ch] = '\0';
			return str;
		}
		if (strcmp(kindofFigure,"knight") == 0)
		{
			char * str = new char [30];
			int ch =0;
			int i = Position.x;
			int j = Position.y;
			if (i-2>-1 && j+1<8)
			{
				str[ch++] = i-2+'0';
				str[ch++] = j+1+'0';
				str[ch++] = ' ';
			}
			if (i-1>-1 && j+2<8)
			{
				str[ch++] = i-1+'0';
				str[ch++] = j+2+'0';
				str[ch++] = ' ';
			}
			if (i+1<8 && j+2<8)
			{
				str[ch++] = i+1+'0';
				str[ch++] = j+2+'0';
				str[ch++] = ' ';
			}
			if (i+2<8 && j+1<8)
			{
				str[ch++] = i+2+'0';
				str[ch++] = j+1+'0';
				str[ch++] = ' ';
			}
				if (i+2<8 && j-1>-1)
			{
				str[ch++] = i+2+'0';
				str[ch++] = j-1+'0';
				str[ch++] = ' ';
			}
			if (i+1<8 && j-2>-1)
			{
				str[ch++] = i+1+'0';
				str[ch++] = j-2+'0';
				str[ch++] = ' ';
			}
				if (i-1>-1 && j-2>-1)
			{
				str[ch++] = i-1+'0';
				str[ch++] = j-2+'0';
				str[ch++] = ' ';
			}
				if (i-2>-1 &&  j-1>-1)
			{
				str[ch++] = i-2+'0';
				str[ch++] = j-1+'0';
				str[ch++] = ' ';
			}
			str[ch] = '\0';
			return str;
		}
		if(strcmp(kindofFigure,"king") == 0)
		{
			char * str = new char [50];
			int ch =0;
			int i=Position.x;
			int j=Position.y;

			if (i != 7 && j!=7)
			{
				str[ch++] = i+1+'0';
				str[ch++] = j+1+'0';
				str[ch++] =' ';
			}
			if (i!= 0 && j!=0)
			{
				str[ch++] = i-1+'0';
				str[ch++] = j-1+'0';
				str[ch++] =' ';
			}
			if (i!= 0 && j!=7)
			{
				str[ch++] = i-1+'0';
				str[ch++] = j+1+'0';
				str[ch++] =' ';
			}
			if (i!= 7 && j!=0)
			{
				str[ch++] = i+1+'0';
				str[ch++] = j-1+'0';
				str[ch++] =' ';
			}
			if (Position.x<6)
			{
				str[ch++] = Position.x+1+'0';
				str[ch++] = Position.y+'0';
				str[ch++] =' ';
			}
			if (Position.x>0)
			{
				str[ch++] = Position.x-1+'0';
				str[ch++] = Position.y+'0';
				str[ch++] =' ';
			}
			if (Position.y>0)
			{
				str[ch++] = Position.x+'0';
				str[ch++] = Position.y-1+'0';
				str[ch++] = ' ';
			} 
			if (Position.y<6)
			{
				str[ch++] = Position.x+'0';
				str[ch++] = Position.y+1+'0';
				str[ch++] = ' ';
			}
			str[ch] = '\0';
			return str;
		}
		
		char * str = new char [1];
		str[0] = '\0';
		return str;
	}

	figure(int color, int xpos, int ypos, const char * kind,Draw * Obj);
	~figure(void);
};

