#version 460

out vec4 colour;
in vec4 vCol;
in vec2 Texcol;
in vec3 Normal;
in vec3 fragpos;
in vec4 DirectionalLightspacepos;
const int MAX_POINT_LIGHT = 5;
const int MAX_SPOT_LIGHT = 5;
//some adt
struct Light {
    float ambientIntensity;
    float diffuseIntensity;
    vec3 color;
};
struct DirectionalLight {
    Light base;
    vec3 direction;
};

struct Material {
    float specular_intensity;
    float shininess;
};

struct Pointlight {
    Light base;
    vec3 position;
    float exponent;
    float Linear;
    float constant;
};

struct Spotlight {
    Pointlight base;
    float edge;
    vec3 direction;
};

struct Omnishadowmap {
    samplerCube shadowmap;
    float farplane;
};
/// uniforms
//
uniform sampler2D theTexture;
uniform sampler2D theDirectionalShadowMap;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 eyeposition;
uniform int PointlightCount;
uniform Pointlight Pointlights[MAX_POINT_LIGHT];
uniform int SpotlightCount;
uniform Spotlight Spotlights[MAX_SPOT_LIGHT];
uniform Omnishadowmap omnishadowmaps[MAX_POINT_LIGHT + MAX_SPOT_LIGHT];


vec3 gridSamplingDisk[20] = vec3[]
(
vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);



float DirectionalShadowFactorCalc(DirectionalLight dlight) {
    vec3 Projcoord = DirectionalLightspacepos.xyz / DirectionalLightspacepos.w;
    Projcoord = (Projcoord * 0.5) + 0.5;
    float closest = texture(theDirectionalShadowMap, Projcoord.xy).r;
    float currentdepth = Projcoord.z;
    vec3 normal = normalize(Normal);
    vec3 lightdir = normalize(dlight.direction);
    float bias = max(0.05 * (1 - dot(normal, lightdir)), 0.005);

    float shadow = 00.0;
    vec2 texelsize = vec2(1.0f) / (textureSize(theDirectionalShadowMap, 0));
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(theDirectionalShadowMap, Projcoord.xy + vec2(x, y) * texelsize).r;

            shadow += currentdepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9;
    if (Projcoord.z > 1.0) {
        shadow = 0.0;
    }

    return (shadow);
}

float Omnishadowfactorcalc(Pointlight plight, int index)
{
   vec3 fragToLight = fragpos - plight.position;
	float currentDepth = length(fragToLight);

	float shadow = 0.0;
	float bias   = 0.15;
	int samples  = 20;
	float viewDistance = length(eyeposition - fragpos);
	float diskRadius = (1.0 + (viewDistance / omnishadowmaps[index].farplane)) / 25.0;
	for(int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(omnishadowmaps[index].shadowmap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= omnishadowmaps[index].farplane;   // Undo mapping [0;1]
		if(currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow /= float(samples);

	return shadow;

}

vec4 calclightbyDirection(Light light, vec3 direction, float shadow) {

    //coding for ambient lighting
    vec4 ambientcolor = vec4(light.color, 1.0f) * light.ambientIntensity;

    // coding for diffuse lighting
    float DiffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec4 DiffuseColor = vec4(light.color * light.diffuseIntensity * DiffuseFactor, 1.0f); ///specularcolor

    //specular light
    vec4 specularcolor = vec4(0, 0, 0, 0);
    if (DiffuseFactor > 0.0f) {
        vec3 fragtoeye = normalize(eyeposition - fragpos);

        vec3 reflectedvertex = normalize(reflect(direction, normalize(Normal)));

        float specularfactor = dot(fragtoeye, reflectedvertex);
        if (specularfactor > 0.0f) {
            specularfactor = pow(specularfactor, material.shininess);
            specularcolor = vec4(light.color * material.specular_intensity * specularfactor, 1.0f);
        }
    }

    return (ambientcolor + (1- shadow) * (DiffuseColor + specularcolor));
}

vec4 DirectionalLightcalc() {
    float shadow = DirectionalShadowFactorCalc(directionalLight);

    return calclightbyDirection(directionalLight.base, directionalLight.direction, shadow);
}

vec4 Pointlightcalc(Pointlight plight, int index) {
    vec4 totalcolor;
    float attenuation = 0;
    vec3 distance = vec3(0, 0, 0);

    distance = vec3(fragpos - plight.position);

    float shadow = Omnishadowfactorcalc(plight, index);
    totalcolor = calclightbyDirection(plight.base, normalize(distance), shadow);
    attenuation = (plight.exponent * length(distance) * length(distance)
            + plight.Linear * length(distance)
            + plight.constant);
    totalcolor /= attenuation;
    return (totalcolor);
}

vec4 Pointlightscalc()

{
    vec4 finalcolor = vec4(0, 0, 0, 0);
    for (int i = 0; i < PointlightCount; i++)
    {
        finalcolor += Pointlightcalc(Pointlights[i], i);
    }
    return finalcolor;
}

vec4 spotlightcalc() {
    vec4 totalcolor = vec4(0, 0, 0, 0);
    float slfactor = 0;
    for (int i = 0; i < SpotlightCount; i++)

    {
        float slfactor = 0;
        slfactor = dot(normalize(fragpos - Spotlights[i].base.position), Spotlights[i].direction);
        if (slfactor > Spotlights[i].edge)
        {
            totalcolor += (Pointlightcalc(Spotlights[i].base, i + PointlightCount) * (1.0f - (1.0f - slfactor) * (1.0f / (1.0f - Spotlights[i].edge))));
        }
    }

    return totalcolor;
}

void main()
{
    vec4 finalcolor = DirectionalLightcalc() + Pointlightscalc() + spotlightcalc();

    colour = texture(theTexture, Texcol) * finalcolor; //* spotlightcalc();
}
