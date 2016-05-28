#include "includes.h"
#include "figure.h"




figure::figure(int color, int xpos, int ypos, const char * kind, Draw * DRobj) : Color(color), Dr(DRobj)
{
	kindofFigure = new char [strlen(kind)+1];
	strcpy(kindofFigure,kind);
	Position = vector2d <int> (xpos,ypos);
	ischecked = 0;

}
figure::~figure(void)
{
	delete[] kindofFigure;
}

void figure::Drawing()
{
	if (this->Color == 0) Dr->set_black();
	else Dr->set_silver();
	if (ischecked) Dr->set_fordesk();

	if (strcmp(kindofFigure,"pawn")== 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		glScalef(0.8,0.8,0.8);
		Dr->Peshka();
		glPopMatrix();
	}
	if (strcmp(kindofFigure,"knight") == 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		Dr->Horse();
		glPopMatrix();
	}
	if (strcmp(kindofFigure,"castle") == 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		Dr->Tura();
		glPopMatrix();
	}
	if (strcmp(kindofFigure,"king") == 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		Dr->Korol();
		glPopMatrix();
	}
	if (strcmp(kindofFigure,"queen") == 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		Dr->Koroleva();
		glPopMatrix();
	}
	if (strcmp(kindofFigure,"bishop") == 0)
	{
		glPushMatrix();
		glTranslatef(-35+10*Position.x,-35+10*Position.y, 0);
		Dr->Oficer();
		glPopMatrix();
	}


	
}
