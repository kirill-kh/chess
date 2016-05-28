#include "chess.h"


chess::chess(Draw * A)
{
	AnimateObj = NULL;
	Chosenfigure = NULL;
	CanChose = 1;
	Obj = A;
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
			Desk[i][j] = 0;
	//peshki

	for (int i=0; i<8; i++)
	{
		Desk[1][i] = new figure(1,1,i,"pawn",this->Obj);
		Desk[6][i] = new figure(0,6,i,"pawn",this->Obj);
	}
	Desk[0][1] = new figure(1,0,1,"knight",this->Obj);
	Desk[0][6] = new figure(1,0,6,"knight",this->Obj);
	Desk[7][1] = new figure(0,7,1,"knight",this->Obj);
	Desk[7][6] = new figure(0,7,6,"knight",this->Obj);
	Desk[0][0] = new figure(1,0,0,"castle",this->Obj);
	Desk[0][7] = new figure(1,0,7,"castle",this->Obj);
	Desk[7][0] = new figure(0,7,0,"castle",this->Obj);
	Desk[7][7] = new figure(0,7,7,"castle",this->Obj);
	Desk[0][4] = new figure(1,0,4,"king",this->Obj);
	Desk[7][3] = new figure(0,7,3,"king",this->Obj);
	Desk[0][3] = new figure(1,0,3,"queen",this->Obj);
	Desk[7][4] = new figure(0,7,4,"queen",this->Obj);
	Desk[0][2] = new figure(1,0,2,"bishop",this->Obj);
	Desk[0][5] =  new figure(1,0,5,"bishop",this->Obj);
	Desk[7][2] = new figure(0,7,2,"bishop",this->Obj);
	Desk[7][5] =  new figure(0,7,5,"bishop",this->Obj);
	








	
}


chess::~chess(void)
{
}


void chess::DrawSituation()
{
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
			if (Desk[i][j]) 
				Desk[i][j]->Drawing();

	if (Chosenfigure)
	{
		DrawtheWays(Desk[Chosenfigure->x][Chosenfigure->y]);
	}
	/*if (AnimateObj)
	{
		if (AnimateObj->it >1) 
		{
			AnimateObj->Figure->Position.x = int ((AnimateObj->Dots[3].x-40)/10+AnimateObj->Dots[3].x);
			AnimateObj->Figure->Position.y = int ((AnimateObj->Dots[3].y-40)/10+AnimateObj->Dots[3].y);
			Desk[AnimateObj->Figure->Position.x][AnimateObj->Figure->Position.y] = AnimateObj->Figure;
			delete[] AnimateObj->Dots;
			delete[] AnimateObj;
		}
		AnimateObj->DrawTheFigure();

	}*/
}