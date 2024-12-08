#version 400
in vec3 fragPosition;
in vec3 fragNormal;
out vec4 fragColor;

uniform vec4 ambient = vec4(0.0, 0.0, 0.0, 0.0);
uniform vec3 cameraPosition;
uniform float specularStrength = 40.0;

struct Light {
    vec3 position;
    vec4 color;
    vec3 spotDir;
    int type;
};

struct Material {
    vec3 ra;
    vec3 rd;
    vec3 rs;
};

uniform int numLights;
uniform Light lights[100];
uniform Material material;

void main(void)
{
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraPosition - fragPosition);

    vec4 totalDiffuse = vec4(0.0);
    vec4 totalSpecular = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);
        float distance = length(lights[i].position - fragPosition);

        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

        if (lights[i].type == 0) {
            float diffIntensity = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0) * attenuation;
            totalDiffuse += diffuseColor;

            if (diffIntensity > 0.0) {
                vec3 halfVec = normalize(lightDir + viewDir);
                float spec = pow(max(dot(normal, halfVec), 0.0), 32.0);
                vec4 specularColor = specularStrength * spec * lights[i].color * vec4(material.rs, 1.0) * attenuation;
                totalSpecular += specularColor;
            }
        } else if (lights[i].type == 1) {
            float cutoff = cos(radians(20));
            float theta = dot(normalize(-lightDir), lights[i].spotDir);

            if (theta > cutoff) {
                float diffIntensity = max(dot(normal, lightDir), 0.0);
                vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0) * attenuation;

                float intense = (theta - cutoff) / (1.0 - cutoff);
                intense = clamp(intense, 0.0, 1.0);
                totalDiffuse += diffuseColor * intense;

                if (diffIntensity > 0.0) {
                    vec3 halfVec = normalize(lightDir + viewDir);
                    float spec = pow(max(dot(normal, halfVec), 0.0), 32.0);
                    vec4 specularColor = specularStrength * spec * lights[i].color * vec4(material.rs, 1.0) * attenuation;
                    totalSpecular += specularColor;
                }
            }
        }
    }

    vec4 ambientColor = vec4(material.ra, 1.0) * ambient;
    fragColor = ambientColor + (totalDiffuse + totalSpecular);
}