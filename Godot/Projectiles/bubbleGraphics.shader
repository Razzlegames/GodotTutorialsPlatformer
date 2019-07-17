shader_type canvas_item;

uniform float refractionMagnitude = 30.0;

void fragment() {
	
	// Possibly a more acturate way to do refraction? Uncomment and see how you like it (and comment out below refraction)
	//vec3 refraction = -refract(vec3(0,0,-1), texture(NORMAL_TEXTURE, UV).rgb, 1.1) *2.0;
	
	vec3 refraction = - texture(NORMAL_TEXTURE, UV).rgb * vec3(1.0,-1.0,1.0);
	
	vec4 textureRead = texture(TEXTURE, UV);
	vec4 offsetScreenRead = textureLod(SCREEN_TEXTURE, SCREEN_UV + refraction.rg/refractionMagnitude, 0.0);

	if (textureRead.a  > .04) {
		COLOR = offsetScreenRead;
	}
	else {
		COLOR = textureRead;
	}
}