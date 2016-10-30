#version 420

uniform vec3 color;
out vec4 selectionBuffer;

void main() {
	selectionBuffer = vec4(color.rgb,1.0);
} 