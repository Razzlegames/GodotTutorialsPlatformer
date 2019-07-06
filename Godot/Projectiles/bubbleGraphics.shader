shader_type canvas_item;

uniform float deformScale = 2;
uniform vec2 amplitude = vec2(0.2, 10);

uniform vec2 center = vec2(16, 16);

void fragment() {
	
	vec3 normal = - texture(NORMAL_TEXTURE, UV).rgb * vec3(1.0,-1.0,1.0);
	
    float xMix = sin(UV.x*3.14);
	float yMix = sin(UV.y*3.14);
	float mixAmount = (xMix + yMix)/ 2.0;

	vec4 textureRead = texture(TEXTURE, UV);
	vec2 textureOffset = center - UV;
	//vec2 textureOffset = UV - vec2(mixAmount, mixAmount);
	vec4 offsetScreenRead = textureLod(SCREEN_TEXTURE, SCREEN_UV + textureOffset/100.5, 0.0);
	offsetScreenRead = textureLod(SCREEN_TEXTURE, SCREEN_UV + normal.rg/30.0, 0.0);

//	COLOR = mix(textureLod(SCREEN_TEXTURE, SCREEN_UV + 
//		vec2(xMix, yMix)/100.0, 0.0), textureRead, 0.5);

	if (textureRead.a  > .04) {
		COLOR = mix(offsetScreenRead, textureRead, .5);
		COLOR = offsetScreenRead;
	}
	else {
		COLOR = textureRead;
	}
	//COLOR = mix(vec4(1,1,1,1), vec4(1,0,0,1), mixAmount/1.2);
	
	
}