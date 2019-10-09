layout(early_fragment_tests) in;

layout (location = 0) out vec4 FragTex;
layout (location = 1) out vec4 FragMat;
layout (location = 2) out vec4 FragNormalGrass;
layout (location = 3) out vec4 FragRoughMetal;

in vec4 vNormalHeight;

#define BottomColor vec4(0.0025, 0.02, 0.005, 1.0)
#define TopColor vec4(0.1, 0.2, 0.05, 1.0)
#define GrassMat vec4(0.5, 0.0, 0.0, 1.0)
#define GrassRM vec4(0.0, 0.0, 0.0, 1.0)

void main() {
	FragTex = mix(BottomColor, TopColor, vNormalHeight.w);
	FragMat = GrassMat;
	FragNormalGrass = vec4(normalize(vNormalHeight.xyz) * 0.5 + 0.5, 0.0);
	FragRoughMetal = GrassRM;
}