#version 330


uniform sampler2D tex;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec2 i_tc;

void main(void) {
	//pixelColor=vec4(i_tc,i_tc);
	pixelColor=texture(tex,i_tc);
}
