xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 57;
 -0.04261;-12.07583;-9.33709;,
 -0.04261;-14.08155;-16.86240;,
 -6.81660;-14.41712;-16.45083;,
 -6.81660;-12.07583;-7.60554;,
 -6.81660;-12.07583;6.55593;,
 -0.04261;-12.07583;8.94625;,
 -6.81660;-12.07583;0.35909;,
 6.73138;-12.07583;-7.60554;,
 6.73138;-12.07583;0.35909;,
 6.73138;-12.07583;6.55593;,
 -0.04261;-15.35661;8.94625;,
 6.73138;-15.65685;6.55593;,
 -6.81660;-19.23787;-15.91301;,
 -4.80713;-19.23787;-20.09638;,
 -6.81660;-19.23787;0.35909;,
 -6.81660;-19.23787;6.55593;,
 -0.04261;-19.23787;8.94625;,
 -0.04261;-19.23787;-21.82793;,
 6.73138;-19.23787;6.55593;,
 4.59293;-19.23787;-20.09638;,
 6.73138;-19.23787;0.35909;,
 6.73138;-19.23787;-15.91301;,
 -6.81660;-15.65685;6.55593;,
 6.73138;-14.41712;-16.45083;,
 4.59293;-15.65685;-20.09638;,
 -0.04261;-15.72064;-21.82793;,
 -4.80713;-15.65685;-20.09638;,
 0.07030;-5.02322;-8.96444;,
 -0.15202;-12.35423;-6.67838;,
 -6.16447;-12.35423;-5.42627;,
 -7.78999;-5.02322;-5.42627;,
 0.00029;0.00000;0.20729;,
 0.00633;0.00000;4.71732;,
 4.16161;0.00000;3.34746;,
 7.54677;-5.02322;6.14701;,
 0.09396;-5.02322;8.60396;,
 -0.15202;-12.35423;7.76514;,
 5.86048;-12.35423;5.71235;,
 -6.16447;-12.35423;0.14304;,
 -6.16447;-12.35423;5.71235;,
 5.86048;-12.35423;0.14304;,
 5.86048;-12.35423;-5.42627;,
 -9.04018;-5.02322;0.14304;,
 -7.35889;-5.02322;5.71235;,
 8.83205;-5.02322;0.14304;,
 7.93056;-5.02322;-5.42627;,
 -0.00683;0.00000;-5.07780;,
 4.37557;0.00000;-3.10512;,
 -4.38931;0.00000;-3.10512;,
 -5.08633;0.00000;0.00000;,
 -4.14894;0.00000;3.10512;,
 4.87820;0.00000;0.00000;,
 -0.08396;0.00000;0.14372;,
 0.00011;0.00000;0.08247;,
 0.11332;0.00000;0.00000;,
 -0.27441;0.00000;0.00000;,
 0.00000;0.00000;0.00000;;
 
 73;
 4;0,1,2,3;,
 3;4,5,6;,
 3;6,5,3;,
 3;3,5,0;,
 3;0,5,7;,
 3;5,8,7;,
 3;8,5,9;,
 4;9,5,10,11;,
 3;12,13,14;,
 3;14,13,15;,
 3;15,13,16;,
 3;13,17,16;,
 3;16,17,18;,
 3;17,19,18;,
 3;19,20,18;,
 3;20,19,21;,
 3;6,14,4;,
 3;14,22,4;,
 3;22,14,15;,
 4;23,21,19,24;,
 4;22,10,5,4;,
 4;23,1,0,7;,
 3;2,12,3;,
 3;12,14,3;,
 3;3,14,6;,
 3;18,20,11;,
 3;11,20,9;,
 3;9,20,8;,
 4;19,17,25,24;,
 4;26,25,17,13;,
 4;16,10,22,15;,
 4;11,10,16,18;,
 4;13,12,2,26;,
 3;8,20,7;,
 3;20,21,7;,
 3;7,21,23;,
 4;24,25,1,23;,
 4;2,1,25,26;,
 4;27,28,29,30;,
 3;31,32,33;,
 4;34,35,36,37;,
 3;29,28,38;,
 3;38,28,39;,
 3;39,28,36;,
 3;36,28,37;,
 3;28,40,37;,
 3;40,28,41;,
 4;42,38,39,43;,
 4;44,40,41,45;,
 4;29,38,42,30;,
 4;37,40,44,34;,
 4;36,35,43,39;,
 4;41,28,27,45;,
 4;45,27,46,47;,
 4;27,30,48,46;,
 4;30,42,49,48;,
 4;42,43,50,49;,
 4;43,35,32,50;,
 4;35,34,33,32;,
 4;34,44,51,33;,
 4;44,45,47,51;,
 4;50,32,31,52;,
 3;52,31,53;,
 3;53,31,54;,
 3;31,33,54;,
 3;54,33,51;,
 4;49,50,52,55;,
 4;55,52,53,56;,
 3;56,53,54;,
 3;48,49,55;,
 4;46,48,55,56;,
 4;47,46,56,54;,
 3;47,54,51;;
 
 MeshMaterialList {
  1;
  73;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\union\\SuperUnion\\Feet\\union_feet_UV_Green.jpg";
   }
  }
 }
 MeshNormals {
  54;
  0.000000;-1.000000;-0.000000;,
  0.021614;0.996054;-0.086075;,
  -0.021614;0.996054;-0.086075;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.991604;-0.129310;,
  0.657313;-0.014650;-0.753475;,
  0.004452;0.000000;-0.999990;,
  -0.663543;-0.014060;-0.748006;,
  -1.000000;0.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  0.332758;0.000000;0.943012;,
  -0.074352;0.952600;-0.294998;,
  0.969631;-0.014140;-0.244164;,
  0.000360;0.955159;-0.296095;,
  -0.305307;-0.190631;-0.932978;,
  0.979865;0.163801;-0.114168;,
  -0.559304;0.389890;-0.731550;,
  0.526874;0.426645;0.735105;,
  -0.809582;0.373314;0.453005;,
  0.315700;-0.122789;0.940881;,
  -0.981684;0.188789;0.025602;,
  0.984905;0.172173;0.017869;,
  -0.019328;0.275899;0.960992;,
  -0.013647;-0.106294;0.994241;,
  -0.000892;0.219416;-0.975631;,
  -0.000564;-0.209456;-0.977818;,
  0.319605;0.914236;-0.249049;,
  -0.000570;0.904107;-0.427305;,
  -0.318613;0.910406;-0.263909;,
  -0.431761;0.901853;0.015630;,
  -0.301624;0.910664;0.282336;,
  -0.012092;0.901800;0.431984;,
  0.231261;0.950027;0.209681;,
  0.434129;0.900785;0.010882;,
  0.332758;0.000000;0.943012;,
  0.986713;-0.009393;-0.162204;,
  -0.332758;0.000000;0.943012;,
  -0.332758;0.000000;0.943012;,
  0.075073;0.952377;-0.295536;,
  -0.972670;-0.013438;-0.231801;,
  -0.988023;-0.008931;-0.154047;,
  1.000000;0.000000;0.000000;,
  0.085682;0.938543;-0.334358;,
  0.000721;0.942203;-0.335041;,
  -0.084246;0.939049;-0.333302;,
  -0.960791;-0.276738;0.017218;,
  -0.955784;-0.260040;0.137315;,
  0.949999;-0.312029;0.011836;,
  0.943462;-0.323001;-0.074494;,
  -0.951648;-0.289360;-0.103132;,
  0.949300;-0.298681;0.098075;,
  -0.341472;-0.077938;0.936655;,
  0.304232;-0.208335;-0.929537;,
  0.349290;0.203238;-0.914708;;
  73;
  4;4,13,11,2;,
  3;3,3,3;,
  3;3,3,2;,
  3;2,3,4;,
  3;4,3,1;,
  3;3,3,1;,
  3;3,3,3;,
  4;34,9,9,10;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  4;12,35,5,5;,
  4;36,9,9,37;,
  4;38,13,4,1;,
  3;39,40,8;,
  3;40,8,8;,
  3;8,8,8;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;5,6,6,5;,
  4;7,6,6,7;,
  4;9,9,36,37;,
  4;10,9,9,34;,
  4;7,40,39,7;,
  3;41,41,41;,
  3;41,35,41;,
  3;41,35,12;,
  4;42,43,13,38;,
  4;11,13,43,44;,
  4;24,25,14,16;,
  3;3,31,32;,
  4;17,22,23,19;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;20,45,46,18;,
  4;21,47,48,15;,
  4;49,45,20,49;,
  4;50,47,21,50;,
  4;23,22,51,51;,
  4;52,25,24,53;,
  4;53,24,27,26;,
  4;24,16,28,27;,
  4;16,20,29,28;,
  4;20,18,30,29;,
  4;18,22,31,30;,
  4;22,17,32,31;,
  4;17,21,33,32;,
  4;21,15,26,33;,
  4;30,31,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,32,3;,
  3;3,32,33;,
  4;29,30,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  3;28,29,3;,
  4;27,28,3,3;,
  4;26,27,3,3;,
  3;26,3,33;;
 }
 MeshTextureCoords {
  57;
  0.744760;0.053582;,
  0.744760;0.116091;,
  0.856365;0.126550;,
  0.856365;0.053582;,
  0.856365;0.053582;,
  0.744760;0.053582;,
  0.856365;0.053582;,
  0.633156;0.053582;,
  0.633156;0.053582;,
  0.633156;0.053582;,
  0.744760;0.155829;,
  0.633156;0.165186;,
  0.856365;0.276791;,
  0.823258;0.276791;,
  0.856365;0.276791;,
  0.856365;0.276791;,
  0.744760;0.276791;,
  0.744760;0.276791;,
  0.633156;0.276791;,
  0.668388;0.276791;,
  0.633156;0.276791;,
  0.633156;0.276791;,
  0.856365;0.165186;,
  0.633156;0.126550;,
  0.668388;0.165186;,
  0.744760;0.167174;,
  0.823258;0.165186;,
  0.231449;0.022498;,
  0.235286;0.330965;,
  0.339058;0.330965;,
  0.367114;0.022498;,
  0.231229;0.022498;,
  0.231041;0.022498;,
  0.102409;0.022498;,
  0.102409;0.022498;,
  0.231041;0.022498;,
  0.235286;0.330965;,
  0.131513;0.330965;,
  0.339058;0.330965;,
  0.339058;0.330965;,
  0.131513;0.330965;,
  0.131513;0.330965;,
  0.388692;0.022498;,
  0.359674;0.022498;,
  0.080225;0.022498;,
  0.095784;0.022498;,
  0.231449;0.022498;,
  0.095784;0.022498;,
  0.367114;0.022498;,
  0.388692;0.022498;,
  0.359674;0.022498;,
  0.080225;0.022498;,
  0.233837;0.022498;,
  0.231234;0.022498;,
  0.227730;0.022498;,
  0.239733;0.022498;,
  0.231237;0.022498;;
 }
}
