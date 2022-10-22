//Francisco António Da Cruz Faria 2019227649

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "RgbImage.h"
#include <GL\Glut.h>

/*TO  DO
adicionar textura plastico butões
adicionar luz
*/

void initMaterials(int material);
void aumentaCoef();
void diminuiCoef();

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.5, 0.5, 0.5, 1.0
#define PI		 3.14159

#define BASE1		0.15, 0.15, 0.15, 1
#define BASE2		0.0,  0.0, 0.0, 1
#define BUTTON1     0.5, 0.5, 0.5, 1
#define BUTTON2     0.4, 0.4, 0.4, 1
#define BUTTON3     0.9, 0.9, 0.9, 1
#define BUTTON4     0.6, 0.6, 0.6, 1
#define BUTTON5		0.7, 0.7,0.7, 1
#define BUTTON6     0.6, 0.6, 0.6, 1
#define RODA1		0.3, 0.3, 0.3, 1
#define RODA2		0.2, 0.2, 0.2, 1
#define NIVEL1		0.4, 0.4, 0.4, 1
#define NIVEL2		0.0, 0.0, 0.0, 1

//================================================================================
//===========================================================Variaveis e constantes
static GLfloat vertices[] = {
		-1,  -1,  1,	// 0 
		-1,   1,  1,	// 1 
		-1,   1, -1,	// 2 
		-1,  -1, -1,	// 3 

		 1,  -1,  1,	// 4 
		 1,   1,  1,	// 5 
		 1,   1, -1,	// 6 
		 1,  -1, -1,	// 7 

		-1,  1,  1,		// 8 
		-1,  1, -1,		// 9 
		 1,  1, -1,		// 10 
		 1,  1,  1,		// 11 

		-1, -1,  1,		// 12 
		-1, -1, -1,		// 13
		 1, -1, -1,		// 14 
		 1, -1,  1,		// 15 

		-1,  -1,  1,	// 16
		-1,   1,  1,    // 17
		 1,   1,  1,	// 18
		 1,  -1,  1,	// 19

		-1,  -1, -1,	// 20
		-1,   1, -1,	// 21
		 1,   1, -1,	// 22
		 1,  -1, -1,	// 23
};

static GLfloat normais[] = {
//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,

	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,

	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,

	  0.0, -1.0,  0.0,
	  0.0, -1.0,  0.0,
	  0.0, -1.0,  0.0,
	  0.0, -1.0,  0.0,

	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,
	  0.0,  0.0,  1.0,

	  0.0,  0.0, -1.0,
	  0.0,  0.0, -1.0,
	  0.0,  0.0, -1.0,
	  0.0,  0.0, -1.0,
};

static GLfloat texturas[] = {
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0, 
1, 0,
1, 1,
0, 1,
0, 0, };

static GLuint esquerda[] = { 0, 1,  2,  3 };
static GLuint  direita[] = { 4, 7,  6,  5 };
static GLuint     cima[] = { 8, 11, 10, 9 };
static GLuint    baixo[] = { 12, 13, 14, 15 };
static GLuint   frente[] = { 16, 19, 18, 17 };
static GLuint     tras[] = { 20, 21, 22, 23 };

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen = 800, hScreen = 600;		//.. janela
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;	//.. Mundo

//------------------------------------------------------------ Observador
GLfloat  rVisao = 3.0, aVisao = 1.54, incPos = 0.5;
GLfloat  angPersp = 109.0;
GLfloat  obsPini[] = { 0.16, 1.0, 7.3 };
GLfloat  obsPfin[] = { obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao * sin(aVisao) };

//………………………………………………………………………………………………………………………………… Textura
RgbImage  imag;
GLuint    tex;
GLuint    texture[9];

//------------------------------------------------------------ inic variaveis
GLint     msec = 10;

GLboolean buttons[] = { false,false,false,false,false,false,false,false,false,false,false,false,false};
GLfloat   angulos[] = { 0,0,0,0 };

GLfloat   lever1 = 0;
GLfloat   lever2 = 0;

GLboolean perspetive = 0;
GLint obser = 0;
int tipoProjeccao = 0;

GLUquadricObj* esfera = gluNewQuadric();

int index = 0;
GLfloat cores[] = { 1,1,1 };

GLfloat localPos[4] = { 0.0, 28.0, 0, 1 };
GLfloat localCorAmb[4] = { 0.0, 0.0, 0.0, 0 };
GLfloat localCorDif[4] = { cores[0], cores[1], cores[2], 1.0 };
GLfloat localCorEsp[4] = { cores[0], cores[1], cores[2], 1.0 };

int  foco1 = 0;
int  foco2 = 0;
int pontual = 0;
GLfloat Foco_direccao[] = { 0.0f,0,  -4.0 / 30.0, 0 };	//……… -
GLfloat Foco_direccao2[] = { 0.0f, 0,  -4.0 / 30.0, 0 };	//……… -Z
GLfloat Foco1_cor[] = { 0, 1,  0, 1 };	//……… Cor da luz 1
GLfloat Foco2_cor[] = { 1, 0,  0, 1 };	//……… Cor da luz 2
GLfloat Foco_ak = 1;
GLfloat Foco_al = 0.0f;
GLfloat Foco_al2 = 0.05f;
GLfloat Foco_aq = 0.0f;
GLfloat Foco_Expon = 2.0;

GLfloat ang = 0;

GLfloat Pos1[] = { -8.0f, 10.0f,  0.0f, 1.0f };   // Foco 1
GLfloat Pos2[] = { 8.0f, 10.0f,  0.0f, 1.0f };   // Foco 2 

bool 		Focos[] = { 1,1 };		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 20.0;		//.. angulo inicial do foco
GLfloat		anguloINC = 3.0;		//.. incremento
GLfloat		anguloMIN = 3.0;		//.. minimo
GLfloat		anguloMAX = 70.0;		//.. maximo

//---------------------------------------------------- AMBIENTE - fixa
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   // 
GLint	  dim = 64;   //numero divisoes da grelha

void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//……………………………………………………………………………………………………………………………Foco Esquerda
	glLightfv(GL_LIGHT0, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao2);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon);

	//……………………………………………………………………………………………………………………………Foco Direita
	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT2, GL_POSITION, localPos);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, Foco_al2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightfv(GL_LIGHT2, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, localCorEsp);
	
	if (foco1 == 1) {
		glDisable(GL_LIGHT0);
	}
	if (foco2 == 1) {
		glDisable(GL_LIGHT1);
	}
	if (pontual == 1) {
		glDisable(GL_LIGHT2);
	}
}

void defineTexturas()
{
	//……………………………………………………………………………………………………………………………  Textura
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("madeira5.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("madeira3.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("tapete.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("tijolo.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("chao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	imag.LoadBmpFile("mesa.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[6]);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	imag.LoadBmpFile("tapete.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void init(void)
{
	glClearColor(WHITE);		
	glEnable(GL_DEPTH_TEST);	
	glShadeModel(GL_SMOOTH);	
	glEnable(GL_BLEND);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	initLights();

	glColor4f(1, 1, 1, 1);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_NORMALIZE);

	defineTexturas();

	glEnable(GL_TEXTURE_2D);

	glVertexPointer(3, GL_FLOAT, 0, vertices); 
	glNormalPointer(GL_FLOAT, 0, normais);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

//desenha quadrado usando o modo dado como parametro
void drawsquare(GLenum mode) {
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, cima);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(mode, 4, GL_UNSIGNED_INT, tras);
}

void drawfrontmesh(float size, float alt_min, float alt_max, float z) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(0, 0, -1);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, z);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, z);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), (float)alt_min + ((alt_max - alt_min) / dim) * (i + 1.0), z);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, (float)alt_min + ((alt_max - alt_min) / dim) * (i + 1.0), z);
		}
	glEnd();
}

void drawbackmesh(float size, float alt_min, float alt_max, float z) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(0, 0, 1);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, z);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, z);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), (float)alt_min + ((alt_max - alt_min) / dim) * (i + 1.0), z);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, (float)alt_min + ((alt_max - alt_min) / dim) * (i + 1.0), z);
		}
	glEnd();
}

void drawleftmesh(float size, float alt_min, float alt_max, float x) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(1, 0, 0);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d(x, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, (float)-size + (size * 2.0 / dim) * j);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d(x, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, (float)-size + (size * 2.0 / dim) * (j + 1.0));
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d(x, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0), (float)-size + (size * 2.0 / dim) * (j + 1.0));
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d(x, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0), (float)-size + (size * 2.0 / dim) * j);
		}
	glEnd();
}

void drawrightmesh(float size, float alt_min, float alt_max, float x) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(-1, 0, 0);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d(x, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, (float)-size + (size * 2.0 / dim) * j);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d(x, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i, (float)-size + (size * 2.0 / dim) * (j + 1.0));
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d(x, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0), (float)-size + (size * 2.0 / dim) * (j + 1.0));
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d(x, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0), (float)-size + (size * 2.0 / dim) * j);
		}
	glEnd();
}

void drawtopmesh(float size, float alt_min, float alt_max, float y) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(0, 1, 0);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)(-size + (size * 2.0 / dim) * j),y, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), y, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), y, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0));
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, y, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0));
		}
	glEnd();
}

void drawdownmesh(float size, float alt_min, float alt_max, float y) {
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glNormal3f(0, 1, 0);
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)(-size + (size * 2.0 / dim) * j), y, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), y, (float)alt_min + (float)((float)(alt_max - alt_min) / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * (j + 1.0), y, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0));
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)-size + (size * 2.0 / dim) * j, y, (float)alt_min + ((float)(alt_max - alt_min) / dim) * (i + 1.0));
		}
	glEnd();
}

void drawSky() {
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	initMaterials(21);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	drawleftmesh(30, -10, 30, -30);
	drawrightmesh(30, -10, 30, 30);
	drawfrontmesh(30,-10,30,30);
	drawbackmesh(30,-10,30,-30);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	initMaterials(7);
	drawtopmesh(30,-30,30,30);
	glPopMatrix();
	drawdownmesh(30, -30, 30, -10);
	glDisable(GL_TEXTURE_2D);
}

//desenha base com dimensões e cor defenidas
void drawBase() {
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor4f(WHITE);
	glPushMatrix();
	glScalef(1.7, 0.25, 2);
	drawsquare(GL_POLYGON);

	glColor4f(BASE2);
	drawsquare(GL_LINE_LOOP);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//desenha nivel com dimensões e cor defenidas
void drawlever() {
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glScalef(0.1, 0.2, 0.1);
	glColor4f(NIVEL1);
	drawsquare(GL_POLYGON);
	glColor4f(NIVEL2);
	drawsquare(GL_LINE_LOOP);
	glPopMatrix();
}

//desenha botão tipo 1 com dimensões e cor defenidas
void drawbuton(GLboolean y) {
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE);
	glPushMatrix();
	glScalef(0.3, 0.2, 0.3);
	glColor4f(BUTTON1);
	if (y) {
		glColor4f(BUTTON3);
	}
	drawsquare(GL_POLYGON);
	glColor4f(BUTTON2);
	if (y) {
		glColor4f(BUTTON4);
	}
	drawsquare(GL_LINE_LOOP);
	glPopMatrix();
}

//desenha roda com dimensões e cor defenidas
void drawang(GLfloat a) {
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glRotated(a, 0, 1, 0);
	glScalef(0.15, 0.2, 0.07);
	glColor4f(RODA1);
	drawsquare(GL_POLYGON);
	glColor4f(RODA2);
	drawsquare(GL_LINE_LOOP);
	glPopMatrix();
}

//desenha botão tipo 2 com dimensões e cor defenidas
void drawSmallButton(GLboolean t){
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(BUTTON5);
	glPushMatrix();
	if (t) {
		glTranslatef(0, -0.07, 0);
	}
	glScalef(0.15, 0.1, 0.1);
	drawsquare(GL_POLYGON);
	glColor4f(BUTTON6);
	drawsquare(GL_LINE_LOOP);
	glPopMatrix();
}

void drawGround() {
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glPushMatrix();
	int				i, j;
	glBegin(GL_QUADS);
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)(-15.0 + (30.0 / dim) * j), -9.9, (float)-10.0 + (20.0 / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)-15.0 + (30.0 / dim) * (j + 1.0), -9.9, (float)-10.0 + (20.0 / dim) * i);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)-15.0 + (30.0 / dim) * (j+1.0), -9.9, (float)-10.0 + (20.0 / dim) * (i+1.0));
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)-15.0 + (30.0 / dim) * j, -9.9, (float)-10.0 + (20.0 / dim) * (i + 1.0));
		}
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[5]);

	//pernas messa
	glPushMatrix();
	glTranslatef(-8+ 2, -0.25 -4 - 1.8, -4+ 2);
	glScalef(0.4, 5, 0.4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8 - 2, -0.25 - 4 - 1.8, 4 - 2);
	glScalef(0.4, 5, 0.4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8 - 2, -0.25 - 4 - 1.8, -4 + 2);
	glScalef(0.4, 5, 0.4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8 + 2, -0.25 - 4 -1.8, 4 - 2);
	glScalef(0.4, 5, 0.4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glColor4f(0.1, 0.1, 0.1, 0.7);
	glDisable(GL_TEXTURE_2D);

	//glass table
	glPushMatrix();
	glTranslatef(0, -0.25 - 0.4, 0);
	glScalef(8, 0.4, 4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
}

void drawScene() {
	drawSky();
	glPushMatrix();
	drawBase();
	//quadrados tipo 1
	glPushMatrix();
	glTranslatef(-1, 0.25, -0.25);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			drawbuton(buttons[x * 3 + y]);
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-3, 0, 0.75);
	}
	glPopMatrix();

	//nivel
	glPushMatrix();
	glTranslatef(1.4, 0.40, -1.5);
	glTranslatef(- lever1, 0, 0);
	drawlever();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 0.40, -1);
	glTranslatef(- lever2, 0, 0);
	drawlever();
	glPopMatrix();

	//roda
	glPushMatrix();
	glTranslatef(-0.25, 0.40, -1.5);
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			drawang(angulos[x*2 + y]);
			glTranslatef(0, 0, 0.5);
		}
		glTranslatef(0.5, 0, -1);
	}
	glPopMatrix();

	//botão tipo 2
	glPushMatrix();
	glTranslatef(-1.25, 0.30, -1.5);
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			drawSmallButton(buttons[9+x*2 + y]);
			glTranslatef(0.5, 0, 0);
		}
		glTranslatef(-1, 0, +0.5);
	}
	glPopMatrix();
	drawGround();
	glPopMatrix();
}

void drawObservador_Onde()
{
	glColor4f(GREEN);
	glPushMatrix();
	glTranslatef(obsPini[0], obsPini[1], obsPini[2]);
	glutSolidCube(1);
	glPopMatrix();
}

void iluminacao() {
	GLfloat localCorDif[]= { cores[0], cores[1], cores[2], 1.0 };
	GLfloat localCorEsp[] = { cores[0], cores[1], cores[2], 1.0 };
	GLfloat Foco_direccao[] = { sin(ang),0,  -cos(ang) };
	GLfloat Foco_direccao2[] = { -sin(ang), 0,  -cos(ang) };

	//……………………………………………………………………………………………………………………………Foco Esquerda
	glLightfv(GL_LIGHT0, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao2);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon);

	//……………………………………………………………………………………………………………………………Foco Direita
	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

	glLightfv(GL_LIGHT2, GL_POSITION, localPos);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, Foco_al2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightfv(GL_LIGHT2, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, localCorEsp);

	if (foco1 == 1) {
		glDisable(GL_LIGHT0);
	}
	else {
		glEnable(GL_LIGHT0);
	}
	if (foco2 == 1) {
		glDisable(GL_LIGHT1);
	}
	else {
		glEnable(GL_LIGHT1);
	}
	if (pontual == 1) {
		glDisable(GL_LIGHT2);
	}
	else {
		glEnable(GL_LIGHT2);
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_TEXTURE_2D);

	if (perspetive) {
		glViewport(0.30 * wScreen, 0.30 * hScreen, 0.70 * wScreen, 0.70 * hScreen);
	}
	else {
		glViewport(0, 0, 0.30 * wScreen, 0.30 * hScreen);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (obser == 0) {
		gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);
	}
	else if (obser == 1) {
		gluLookAt(0, -5, 0, 0, 0, 0, 0, 0, -1);
	}
	else if (obser == 2) {
		gluLookAt(2, 0, 0, 0, 0, 0, 0, 1, 0);
	}
	else if (obser == 3) {
		gluLookAt(-2, 0, 0, 0, 0, 0, 0, 1, 0);
	}
	else if (obser == 4) {
		gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	}
	else if (obser == 5) {
		gluLookAt(0, 0, -2, 0, 0, 0, 0, 1, 0);
	}
	iluminacao();
	glPushMatrix();
	glColor4f(0.0f, 1.0f, 0.0f, 1.);
	glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
	glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();
	drawScene();
	drawObservador_Onde();

	if (perspetive) {
		glViewport(0, 0, 0.30 * wScreen, 0.30 * hScreen);
	}
	else {
		glViewport(0.30 * wScreen, 0.30 * hScreen, 0.70 * wScreen, 0.70 * hScreen);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (tipoProjeccao == 0) {
		gluPerspective(90, (float)wScreen / hScreen, 0.1, 9000);
	}
	if (tipoProjeccao == 1){
		glOrtho(-10, 10, -10, 10, -50, 50);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPini[0], obsPini[1], obsPini[2]+1, obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

	iluminacao();
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glColor4f(0.0f, 1.0f, 0.0f, 1.);
		glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
		glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();
	glPushMatrix();
		glColor4f(1.0f, 0.0f, 0.0f, 1.);
		glTranslatef(Pos2[0], Pos2[1], Pos2[2]);
		glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();
	glPushMatrix();
		glColor4f(localCorDif[0], localCorDif[1], localCorDif[2], localCorDif[3]);
		glTranslatef(localPos[0], localPos[1], localPos[2]);
		glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	if (tipoProjeccao == 1)drawObservador_Onde();
	glTranslatef(0, -2, 0);
	drawScene();


	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		buttons[0] = !buttons[0];
		break;
	case '2':
		buttons[1] = !buttons[1];
		break;
	case '3':
		buttons[2] = !buttons[2];
		break;
	case '4':
		buttons[3] = !buttons[3];
		break;
	case '5':
		buttons[4] = !buttons[4];
		break;
	case '6':
		buttons[5] = !buttons[5];
		break;
	case '7':
		buttons[6] = !buttons[6];
		break;
	case '8':
		buttons[7] = !buttons[7];
		break;
	case '9':
		buttons[8] = !buttons[8];
		break;
	case 'z':
		buttons[9] = !buttons[9];
		break;
	case 'x':
		buttons[10] = !buttons[10];
		break;
	case 'c':
		buttons[11] = !buttons[11];
		break;
	case 'v':
		buttons[12] = !buttons[12];
		break;
	case 'q':
		if (lever1 < 0.7) {
			lever1 = lever1 + 0.1;
		}
		break;
	case 'w':
		if (lever1 > 0.01) {
			lever1 = lever1 - 0.1;
		}
		break;
	case 'a':
		if (lever2 < 0.7) {
			lever2 = lever2 + 0.1;
		}
		break;
	case 's':
		if (lever2 > 0.01) {
			lever2 = lever2 - 0.1;
		}
		break;
	case 'e':
		if (angulos[0] < 360) {
			angulos[0] = angulos[0] + 5;
		}
		break;
	case 'r':
		if (angulos[0] > 0.01) {
			angulos[0] = angulos[0] - 5;
		}
		break;
	case 'd':
		if (angulos[1] < 360) {
			angulos[1] = angulos[1] + 5;
		}
		break;
	case 'f':
		if (angulos[1] > 0.01) {
			angulos[1] = angulos[1] - 5;
		}
		break;
	case 't':
		if (angulos[2] < 360) {
			angulos[2] = angulos[1] + 5;
		}
		break;
	case 'y':
		if (angulos[2] > 0.01) {
			angulos[2] = angulos[1] - 5;
		}
		break;
	case 'g':
		if (angulos[3] < 360) {
			angulos[3] = angulos[1] + 5;
		}
		break;
	case 'h':
		if (angulos[3] > 0.01) {
			angulos[3] = angulos[1] - 5;
		}
		break;
	case 'Q':
		aberturaFoco = aberturaFoco - 1;
		if (aberturaFoco <= 0) {
			aberturaFoco = 0;
		}
		break;
	case 'W':
		aberturaFoco = aberturaFoco + 1 ;
		break;
	case 'P':
	case 'p':
		perspetive = !perspetive;
		break;
	case 'O':
	case 'o':
		obser = obser++;
		if (obser == 6) {
			obser = 0;
		}
		break;
	case 'n':
	case 'N':
		obsPfin[1] = obsPfin[1] - incPos;
		break;
	case 'M':
	case 'm':
		obsPfin[1] = obsPfin[1] + incPos;
		break;
	case 'B':
	case 'b':
		obsPfin[1] = obsPini[1];
		break;
	case 'L':
	case 'l':
		tipoProjeccao = (tipoProjeccao + 1) % 2;
		break;
	case 'X':
		Foco_al2 = Foco_al2 + 0.01;
		break;
	case 'Z':
		Foco_al2 = Foco_al2 - 0.01;
		if (Foco_al2 <= 0) {
			Foco_al2 = 0;
		}
		break;
	case 'A':
		ang = ang + 0.1;
		break;
	case 'S':
		ang = ang - 0.1;
		break;
	case 'E':
		cores[0] = cores[0] - 0.1;
		if (cores[0] < 0) {
			cores[0] = 0;
		}
		break;
	case 'D':
		cores[0] = (cores[0] + 0.1);
		if (cores[0] > 1) {
			cores[0] = 1;
		}
		break;
	case 'R':
		cores[1] = cores[1] - 0.1;
		if (cores[1] < 0) {
			cores[1] = 0;
		}
		break;
	case 'F':
		cores[1] = (cores[1] + 0.1);
		if (cores[1] > 1) {
			cores[1] = 1;
		}
		break;
	case 'T':
		cores[2] = cores[2] - 0.1;
		if (cores[2] < 0) {
			cores[2] = 0;
		}
		break;
	case 'G':
		cores[2] = (cores[2] + 0.1);
		if (cores[2] > 1) {
			cores[2] = 1;
		}
		break;
	case 'C':
		dim = dim / 2;
		if (dim == 0) {
			dim = 1;
		}
		break;
	case 'V':
		dim = dim * 2;
		break;
	case 'Y':
		aumentaCoef();
		break;
	case 'H':
		diminuiCoef();
		break;
	case 'U':
		foco1 = (foco1 + 1) % 2;
		break;
	case 'J':
		foco2 = (foco2 + 1) % 2;
		break;
	case 'I':
		pontual = (pontual + 1) % 2;
		break;
	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		obsPini[0] = obsPini[0] + incPos * cos(aVisao);
		obsPini[2] = obsPini[2] - incPos * sin(aVisao);
	}
	if (key == GLUT_KEY_DOWN) {
		obsPini[0] = obsPini[0] - incPos * cos(aVisao);
		obsPini[2] = obsPini[2] + incPos * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
	obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("META 1(MINUSCULAS) : |BotaoGrande-'1-9'||BotaoRodar-e/r/d/f/t/y/g/h||Observador:'SETAS'||BotaoPequeno-'z/x/c/v'||nivel -'q/w/a/s'||mudar perspetive-'o'||trocar visoes-'p'||tipo projecao-'l'| META2(MAISCULAS):|coef-'Y/H'||grelha-'C/V'||cores-'E/D/R/F/T/G'||ang focal-'A/S'||intesensidade-'Z/X'||abertura foco-'Q/W'|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
