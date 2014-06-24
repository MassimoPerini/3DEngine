/*varying vec3 lightDir,normal, v, N;

void main()
{
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    N = normalize(gl_NormalMatrix * gl_Normal);

    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    lightDir = normalize(vec3(gl_LightSource[0].position));
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    //gl_Position = ftransform();
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

}*/

varying vec3 vN;
varying vec3 v;
varying vec3 lightDir,normal;
varying vec4 ShadowCoord;




void main(void)
{
    ShadowCoord= gl_TextureMatrix[7] * gl_Vertex;

    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    for (int i=0;i<8;i++)
    {
        lightDir = normalize(vec3(gl_LightSource[i].position));

    }
    gl_TexCoord[0] = gl_MultiTexCoord0;

    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    vN = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
