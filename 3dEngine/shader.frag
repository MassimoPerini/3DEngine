/*varying vec3 lightDir,normal;
varying vec3 N;
varying vec3 v;
uniform sampler2D tex;



void main()
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
    
    vec3 L = normalize(gl_LightSource[0].position.xyz - v);
    vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(L,N));

    
    intensity = max(dot(lightDir,normalize(normal)),0.0);
    
    cf = intensity * (gl_FrontMaterial.diffuse).rgb +gl_FrontMaterial.ambient.rgb;
    af = gl_FrontMaterial.diffuse.a;
    texel = texture2D(tex,gl_TexCoord[0].st);
    
    vec4 Iamb = gl_FrontLightProduct[0].ambient;
    vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);

    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    ct = texel.rgb;
    at = texel.a;
    vec4 diff = vec4(ct * cf, at * af);
    finalColor+=Iamb+diff+Ispec;
    gl_FragColor=finalColor;

}*/
varying vec3 vN;
varying vec3 v;

varying vec3 lightDir,normal;
uniform sampler2D tex;

//---
uniform sampler2D ShadowMap;

varying vec4 ShadowCoord;
//----

#define MAX_LIGHTS 8




void main (void)
{
    vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
    intensity = max(dot(lightDir,normalize(normal)),0.0);
    
//    cf = intensity * (gl_FrontMaterial.diffuse).rgb +gl_FrontMaterial.ambient.rgb;
    cf = (gl_FrontMaterial.diffuse).rgb*intensity;
    af = gl_FrontMaterial.diffuse.a;
    texel = texture2D(tex,gl_TexCoord[0].st);
    
    ct = texel.rgb;
    at = texel.a;

    //--------------------
    vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	
	// Used to lower moiré pattern and self-shadowing
	shadowCoordinateWdivide.z += 0.0005;
	
	
	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;
	
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
  	
    //-------------------
    
    
    vec3 N = normalize(vN);
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    for (int i=0;i<8;i++)
    {
        if (true){
        vec3 L = normalize(gl_LightSource[i].position.xyz - v);
            
        vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
        vec3 R = normalize(-reflect(L,N));
        
        //calculate Ambient Term:
            
        vec4 Iamb = gl_FrontLightProduct[i].ambient;
            
        
        //calculate Diffuse Term:
        
     //   vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
        
       vec4 Idiff = texel * gl_FrontLightProduct[i].diffuse;
        
        //Teniamo conto delle texture!!
        
  //      vec4 Idiff = vec4(ct * cf, at * af) * max(dot(N,L), 0.0);
        
        Idiff = clamp(Idiff, 0.0, 1.0);
        
        // calculate Specular Term:
        vec4 Ispec = gl_FrontLightProduct[i].specular
        * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);

        Ispec = clamp(Ispec, 0.0, 1.0);
        
        finalColor += Iamb + Idiff + Ispec;
            
    }
    }
    
    // write Total Color:
    gl_FragColor = (((gl_FrontLightModelProduct.sceneColor + finalColor)*shadow)*texel.aaaa)*gl_FrontMaterial.diffuse.aaaa;
}
