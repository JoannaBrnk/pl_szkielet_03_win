unsigned int PacManvertexCount = 48;

float PacManverts[] = {
	1.0f,-1.0f,-1.0f,1.0f, //A
	1.0f, 0.0f, 0.0f,1.0f, //J  //przod lewo
	-1.0f,-1.0f,-1.0f,1.0f,  //C

	-1.0f,0.0f,0.0f,1.0f,  //I
	1.0f, 0.0f,0.0f,1.0f,  //J //przod prawo
	-1.0f, 1.0f,-1.0f,1.0f, //B

	-1.0f,-1.0f,-1.0f,1.0f, //C
	-1.0f,0.0f,0.0f,1.0f,  //I
	1.0f, 0.0f,0.0f,1.0f,  //J

	-1.0f, 1.0f,-1.0f,1.0f, //B
	1.0f, 1.0f,-1.0f,1.0f,  //D
	1.0f, 0.0f, 0.0f,1.0f, //J 



	-1.0f,-1.0f, 1.0f,1.0f, //G
	1.0f, 1.0f, 1.0f,1.0f, //H    TYL PRAWO
	1.0f,-1.0f, 1.0f,1.0f,  //E

	-1.0f,-1.0f, 1.0f,1.0f,  //G
	-1.0f, 1.0f, 1.0f,1.0f,  //F  TYL LEWO
	1.0f, 1.0f, 1.0f,1.0f,   //H 


	1.0f,-1.0f, 1.0f,1.0f,  //E
	1.0f, 0.0f, 0.0f,1.0f,  //J   PRAWA
	1.0f,-1.0f,-1.0f,1.0f,  //A

	1.0f, 0.0f, 0.0f,1.0f,  //J 
	1.0f, 1.0f, 1.0f,1.0f,  //H  PRAWA
	1.0f, 1.0f,-1.0f,1.0f,  //D

	1.0f, 0.0f, 0.0f,1.0f,  //J 
	1.0f, 1.0f, 1.0f,1.0f,  //H 
	1.0f,-1.0f, 1.0f,1.0f,  //E


	-1.0f,-1.0f,-1.0f,1.0f,  //C
	-1.0f,0.0f,0.0f,1.0f,    //I   LEWA
	-1.0f,-1.0f, 1.0f,1.0f,  //G

	-1.0f,0.0f,0.0f,1.0f,  //I
	-1.0f, 1.0f,-1.0f,1.0f,  //B  LEWA
	-1.0f, 1.0f, 1.0f,1.0f,  //F

	-1.0f,0.0f,0.0f,1.0f,    //I   LEWA
	-1.0f,-1.0f, 1.0f,1.0f,  //G
	-1.0f, 1.0f, 1.0f,1.0f,  //F


	-1.0f,-1.0f,-1.0f,1.0f,
	1.0f,-1.0f, 1.0f,1.0f,
	1.0f,-1.0f,-1.0f,1.0f,

	-1.0f,-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f, 1.0f,1.0f,
	1.0f,-1.0f, 1.0f,1.0f,


	-1.0f, 1.0f, 1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
	1.0f, 1.0f, 1.0f,1.0f,

	-1.0f, 1.0f, 1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,

};

float PacMancolors[] = {
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,

	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,

	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,

	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,

	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,

	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
};

float PacMannormals[] = {
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,

	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,

	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,

	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
};

float PacManvertexNormals[] = {
	1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	-1.0f,-1.0f,-1.0f,0.0f,

	1.0f,-1.0f,-1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,


	-1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,

	-1.0f,-1.0f, 1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,

	1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	1.0f,-1.0f,-1.0f,0.0f,

	1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,
	-1.0f,-1.0f, 1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,
	1.0f,-1.0f,-1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f,-1.0f, 1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,

	-1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,

	-1.0f, 1.0f, 1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
};

float PacMantexCoords[] = {
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};
	