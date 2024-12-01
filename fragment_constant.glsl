#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 fragUV;  // UV coordinates passed from the vertex shader

out vec4 out_Color;

uniform sampler2D textureUnitID; // Texture sampler

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

uniform Light lights[10];
uniform int numLights;
uniform vec3 cameraPosition;
uniform float specularStrength = 70.0;
uniform vec4 ambientColor = vec4(0.01, 0.01, 0.01, 1.0);
uniform Material material;

void main(void) {
    vec3 normal = normalize(ex_worldNormal);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

    // Sample the texture using UV coordinates
    vec4 textureColor = texture(textureUnitID, fragUV);

    // Initialize lighting contributions
    vec4 totalDiffuse = vec4(0.0);
    vec4 totalSpecular = vec4(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - ex_worldPosition.xyz);
        float distance = length(lights[i].position - ex_worldPosition.xyz);

        // Attenuation factors
        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

        // Point light calculations
        if (lights[i].type == 0) {
            float diffIntensity = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0) * attenuation;
            totalDiffuse += diffuseColor;

            // Specular calculation
            if (diffIntensity > 0.0) {
                vec3 halfVec = normalize(lightDir + viewDir);
                float spec = pow(max(dot(normal, halfVec), 0.0), 32.0);
                vec4 specularColor = specularStrength * spec * lights[i].color * vec4(material.rs, 1.0) * attenuation;
                totalSpecular += specularColor;
            }
        }
        // Spotlight calculations
        else if (lights[i].type == 1) {
            float cutoff = cos(radians(20.0));
            float theta = dot(normalize(-lightDir), lights[i].spotDir);

            if (theta > cutoff) {
                float spotFactor = (theta - cutoff) / (1.0 - cutoff);
                spotFactor = clamp(spotFactor, 0.0, 1.0);

                float diffIntensity = max(dot(normal, lightDir), 0.0);
                vec4 diffuseColor = diffIntensity * lights[i].color * vec4(material.rd, 1.0) * spotFactor * attenuation;
                totalDiffuse += diffuseColor * spotFactor;

                if (diffIntensity > 0.0) {
                    vec3 halfVec = normalize(lightDir + viewDir);
                    float spec = pow(max(dot(normal, halfVec), 0.0), 32.0);
                    vec4 specularColor = specularStrength * spec * lights[i].color * vec4(material.rs, 1.0) * spotFactor * attenuation;
                    totalSpecular += specularColor;
                }
            }
        }
    }

    out_Color = (vec4(material.ra, 1.0) * ambientColor) + totalDiffuse + totalSpecular;
    out_Color = out_Color * textureColor;
    out_Color = clamp(out_Color, vec4(0.0), vec4(1.0));
}
