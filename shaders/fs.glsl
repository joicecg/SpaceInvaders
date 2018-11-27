#version 330

uniform sampler2D dbuffer;
noperspective in vec2 TexCoord;

out vec3 outColor;

void main(void){
    outColor = texture(dbuffer, TexCoord).rgb;
}