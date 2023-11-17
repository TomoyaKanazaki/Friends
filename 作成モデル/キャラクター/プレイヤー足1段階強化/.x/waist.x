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
 86;
 0.00000;-49.14380;-185.89520;,
 -162.85201;-14.96640;-128.77069;,
 -162.85201;34.17740;-128.77069;,
 0.00000;0.00000;-164.10690;,
 162.85201;-14.96640;-128.77069;,
 162.85201;34.17740;-128.77069;,
 -198.42790;34.17740;0.00000;,
 0.00000;0.00000;0.00000;,
 198.42790;34.17740;0.00000;,
 -159.99820;34.17740;136.40259;,
 0.00000;34.17740;174.92990;,
 159.99820;34.17740;136.40259;,
 -159.99820;-14.96640;136.40259;,
 0.00000;-41.23670;192.98801;,
 159.99820;-14.96640;136.40259;,
 -198.42790;-14.96640;0.00000;,
 0.00000;-14.96640;-0.00000;,
 198.42790;-14.96640;-0.00000;,
 -162.85201;-14.96640;-128.77069;,
 0.00000;-49.14380;-185.89520;,
 162.85201;-14.96640;-128.77069;,
 198.42790;-14.96640;-0.00000;,
 198.42790;34.17740;0.00000;,
 159.99820;34.17740;136.40259;,
 159.99820;-14.96640;136.40259;,
 -198.42790;-14.96640;0.00000;,
 -159.99820;-14.96640;136.40259;,
 -159.99820;34.17740;136.40259;,
 -198.42790;34.17740;0.00000;,
 175.91730;-67.36549;-123.55610;,
 94.29800;-81.06440;-151.95549;,
 91.04800;-65.69640;-171.24010;,
 175.69310;-33.07750;-141.73979;,
 91.61150;-23.94000;161.12550;,
 159.99820;-10.85010;136.40259;,
 198.42790;-10.85010;4.11000;,
 87.73050;-25.84210;0.60420;,
 89.01250;-95.23370;190.38319;,
 167.80260;-79.15240;156.79900;,
 168.95551;-30.05990;156.74071;,
 102.38470;-52.70190;195.43181;,
 236.72650;-81.61610;9.90530;,
 136.11240;-74.87200;32.88270;,
 168.95551;-30.05990;156.74071;,
 167.80260;-79.15240;156.79900;,
 236.72650;-81.61610;9.90530;,
 217.77930;-31.56870;5.88310;,
 -236.72650;-81.61610;9.90530;,
 -167.80260;-79.15240;156.79900;,
 -168.95551;-30.05990;156.74071;,
 -217.77930;-31.56870;5.88310;,
 0.00000;-122.80869;52.38740;,
 0.00000;-116.48161;221.93210;,
 -89.01250;-95.23370;190.38319;,
 -136.11240;-74.87200;32.88270;,
 0.00000;-75.84000;218.31119;,
 -102.38470;-52.70190;195.43181;,
 -91.61150;-23.94000;161.12550;,
 0.00000;-41.13980;192.98801;,
 0.00000;-44.94410;4.52110;,
 -87.73050;-25.84210;0.60420;,
 0.00000;-84.23960;-185.89520;,
 0.00000;-151.23790;-140.80901;,
 -94.29800;-81.06440;-151.95549;,
 -91.04800;-65.69640;-171.24010;,
 -159.99820;-10.85010;136.40259;,
 -198.42790;-10.85010;4.11000;,
 159.99820;-10.85010;136.40259;,
 198.42790;-10.85010;4.11000;,
 80.68501;-27.74430;-158.27100;,
 162.85201;-10.85010;-128.77069;,
 0.00000;-48.74840;-185.89520;,
 -80.68501;-27.74430;-158.27100;,
 -167.80260;-79.15240;156.79900;,
 -236.72650;-81.61610;9.90530;,
 -168.95551;-30.05990;156.74071;,
 -159.99820;-10.85010;136.40259;,
 -198.42790;-10.85010;4.11000;,
 -175.69310;-33.07750;-141.73979;,
 -162.85201;-10.85010;-128.77069;,
 -175.91730;-67.36549;-123.55610;,
 94.29800;-81.06440;-151.95549;,
 175.91730;-67.36549;-123.55610;,
 0.00000;-151.23790;-140.80901;,
 -94.29800;-81.06440;-151.95549;,
 -175.91730;-67.36549;-123.55610;;
 
 56;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;2,6,7,3;,
 4;3,7,8,5;,
 4;6,9,10,7;,
 4;7,10,11,8;,
 4;10,9,12,13;,
 4;11,10,13,14;,
 4;12,15,16,13;,
 4;13,16,17,14;,
 4;15,18,19,16;,
 4;16,19,20,17;,
 4;21,22,23,24;,
 4;4,5,22,21;,
 4;25,26,27,28;,
 4;1,25,28,2;,
 4;29,30,31,32;,
 4;33,34,35,36;,
 4;37,38,39,40;,
 4;41,38,37,42;,
 4;43,44,45,46;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 4;53,52,55,56;,
 4;57,58,59,60;,
 4;61,62,63,64;,
 4;49,65,66,50;,
 4;56,55,58,57;,
 4;39,34,33,40;,
 4;67,43,46,68;,
 4;69,70,32,31;,
 4;71,61,64,72;,
 4;73,74,54,53;,
 4;75,73,53,56;,
 4;76,75,56,57;,
 4;77,76,57,60;,
 4;64,78,79,72;,
 4;63,80,78,64;,
 4;42,37,52,51;,
 4;52,37,40,55;,
 4;33,58,55,40;,
 4;58,33,36,59;,
 4;61,71,69,31;,
 4;30,62,61,31;,
 4;79,77,60,72;,
 4;59,71,72,60;,
 4;36,69,71,59;,
 4;35,70,69,36;,
 4;46,32,70,68;,
 4;45,29,32,46;,
 4;81,82,41,42;,
 4;83,81,42,51;,
 4;84,83,51,54;,
 4;74,85,84,54;,
 4;80,47,50,78;,
 4;66,79,78,50;;
 
 MeshMaterialList {
  1;
  56;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  84;
  -0.225346;0.201415;-0.953232;,
  0.000000;0.206732;-0.978397;,
  0.225346;0.201415;-0.953232;,
  0.148441;0.987729;-0.048547;,
  0.000000;0.998794;-0.049091;,
  -0.148441;0.987729;-0.048547;,
  0.108324;0.986822;-0.120199;,
  0.000000;0.992663;-0.120910;,
  -0.108324;0.986822;-0.120199;,
  -0.705266;0.064414;0.706011;,
  0.000000;0.116277;0.993217;,
  0.705266;0.064414;0.706011;,
  -0.064494;-0.997852;0.011454;,
  0.000000;-0.999934;0.011477;,
  0.064494;-0.997852;0.011454;,
  -0.256956;-0.868007;-0.424896;,
  0.763154;-0.262683;-0.590418;,
  -0.518675;0.608494;-0.600592;,
  0.518675;0.608494;-0.600592;,
  -0.254842;0.912190;0.320883;,
  0.254842;0.912190;0.320883;,
  -0.746744;0.023925;0.664681;,
  0.746744;0.023925;0.664681;,
  0.000000;-0.913230;-0.407445;,
  0.000000;-0.999979;0.006550;,
  0.000000;0.920027;0.391856;,
  0.000000;0.190755;-0.981638;,
  -0.655992;0.428970;0.621015;,
  0.000000;0.352798;0.935700;,
  0.655992;0.428970;0.621015;,
  0.000000;-0.260047;-0.965596;,
  -0.336018;-0.853043;-0.399263;,
  -0.169302;-0.985351;-0.020516;,
  -0.256260;0.356896;0.898307;,
  0.056358;0.930478;0.361988;,
  -0.185520;0.331536;-0.925022;,
  -0.305525;-0.154262;-0.939605;,
  0.336018;-0.853043;-0.399263;,
  0.379434;-0.090161;0.920815;,
  0.256260;0.356896;0.898307;,
  -0.056358;0.930478;0.361988;,
  0.185520;0.331536;-0.925022;,
  0.322013;-0.365377;-0.873388;,
  -0.336384;0.941724;0.001431;,
  0.190371;0.981683;-0.007521;,
  0.000000;0.999925;-0.012256;,
  -0.190371;0.981683;-0.007521;,
  0.336384;0.941724;0.001431;,
  0.910406;0.413568;0.011053;,
  0.045878;-0.998063;-0.042009;,
  0.216453;-0.976240;-0.010215;,
  0.000000;-0.999715;0.023860;,
  -0.216453;-0.976240;-0.010215;,
  -0.990660;0.135442;0.015752;,
  -0.910406;0.413568;0.011053;,
  0.187557;0.981974;0.023432;,
  0.000000;0.999715;0.023855;,
  -0.187557;0.981974;0.023432;,
  -0.057342;-0.996086;-0.067262;,
  0.000000;-0.997728;-0.067373;,
  0.057342;-0.996086;-0.067262;,
  -0.071242;-0.993382;0.090097;,
  0.000000;-0.995912;0.090327;,
  0.071242;-0.993382;0.090097;,
  0.999997;0.000000;0.002535;,
  0.963891;0.000000;-0.266297;,
  -0.999997;0.000000;0.002535;,
  -0.963891;0.000000;-0.266297;,
  0.048989;-0.997693;-0.046991;,
  0.169302;-0.985351;-0.020516;,
  0.990660;0.135442;0.015752;,
  -0.379434;-0.090161;0.920815;,
  0.000000;-0.057229;0.998361;,
  0.176910;0.468388;-0.865630;,
  -0.048989;-0.997693;-0.046991;,
  -0.045878;-0.998063;-0.042009;,
  -0.763154;-0.262683;-0.590418;,
  0.167954;0.985654;0.016696;,
  0.198741;0.980048;0.002943;,
  0.000000;0.999938;-0.011109;,
  -0.198741;0.980048;0.002943;,
  -0.167954;0.985654;0.016696;,
  0.042765;-0.998399;-0.037025;,
  -0.940864;0.085293;-0.327873;;
  56;
  4;1,0,0,1;,
  4;2,1,1,2;,
  4;55,3,4,56;,
  4;56,4,5,57;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;10,9,9,10;,
  4;11,10,10,11;,
  4;58,12,13,59;,
  4;59,13,14,60;,
  4;12,61,62,13;,
  4;13,62,63,14;,
  4;64,64,11,11;,
  4;65,65,64,64;,
  4;66,9,9,66;,
  4;67,66,66,67;,
  4;16,37,42,16;,
  4;40,20,47,46;,
  4;38,22,29,39;,
  4;49,68,69,50;,
  4;29,22,70,48;,
  4;53,21,27,54;,
  4;51,24,32,52;,
  4;71,72,28,33;,
  4;34,25,45,44;,
  4;30,23,31,36;,
  4;27,19,43,54;,
  4;33,28,25,34;,
  4;29,20,40,39;,
  4;20,29,48,47;,
  4;41,18,18,73;,
  4;26,30,36,35;,
  4;74,75,52,32;,
  4;27,21,71,33;,
  4;19,27,33,34;,
  4;43,19,34,44;,
  4;36,17,17,35;,
  4;31,15,76,36;,
  4;50,69,24,51;,
  4;72,38,39,28;,
  4;40,25,28,39;,
  4;25,40,46,45;,
  4;30,26,41,42;,
  4;37,23,30,42;,
  4;77,43,44,78;,
  4;45,79,78,44;,
  4;46,80,79,45;,
  4;47,81,80,46;,
  4;48,18,18,47;,
  4;70,16,16,48;,
  4;37,82,49,50;,
  4;23,37,50,51;,
  4;31,23,51,52;,
  4;75,15,31,52;,
  4;83,53,54,76;,
  4;43,17,17,54;;
 }
 MeshTextureCoords {
  86;
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.562500;0.875000;,
  0.625000;0.875000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.562500;0.625000;,
  0.562500;0.250000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.562500;0.375000;,
  0.625000;0.125000;,
  0.562500;0.125000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.875000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.437500;0.250000;,
  0.437500;0.125000;,
  0.500000;0.375000;,
  0.437500;0.375000;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.437500;0.625000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.437500;0.875000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.562500;0.750000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.437500;0.750000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.875000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.375000;0.000000;;
 }
}
