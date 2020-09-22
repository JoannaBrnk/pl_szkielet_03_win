#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor wierzcho³ka
in vec4 normal; //wektor normalny wierzcho³ka w przestrzeni modelu
in vec2 texCoord0;

out vec4 iC;
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0;

void main(void) {
    l = normalize(V * (lp - M * vertex));//znormalizowany wektor do œwiat³a w przestrzeni oka
    n = normalize(V * M * normal);//znormalizowany wektor normalny w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //Wektor do obserwatora w przestrzeni oka
    iC = color;
	iTexCoord0= texCoord0;
    gl_Position=P*V*M*vertex;
}
