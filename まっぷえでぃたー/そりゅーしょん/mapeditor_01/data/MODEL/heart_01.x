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
 178;
 -46.14110;-32.18489;-4.28619;,
 -24.88554;-16.71249;-28.67891;,
 -26.94699;-49.51111;-0.39764;,
 -61.70345;-8.70159;-5.58515;,
 -24.88554;-16.71249;-28.67891;,
 -46.14110;-32.18489;-4.28619;,
 -46.22090;10.53829;-28.76808;,
 -39.84535;46.77469;-23.65891;,
 -11.10163;17.41690;-32.21252;,
 -11.10163;17.41690;-32.21252;,
 -39.84535;46.77469;-23.65891;,
 -7.16771;45.95903;-21.41671;,
 -39.84535;46.77469;-23.65891;,
 -46.22090;10.53829;-28.76808;,
 -70.13765;18.80020;-11.93396;,
 19.03871;-9.67384;-30.23074;,
 0.33600;-41.48705;-23.77163;,
 -24.88554;-16.71249;-28.67891;,
 -26.94699;-49.51111;-0.39764;,
 -24.88554;-16.71249;-28.67891;,
 0.33600;-41.48705;-23.77163;,
 -11.10163;17.41690;-32.21252;,
 19.03871;-9.67384;-30.23074;,
 -24.88554;-16.71249;-28.67891;,
 -11.10163;17.41690;-32.21252;,
 -24.88554;-16.71249;-28.67891;,
 -46.22090;10.53829;-28.76808;,
 -61.70345;-8.70159;-5.58515;,
 -46.22090;10.53829;-28.76808;,
 -24.88554;-16.71249;-28.67891;,
 -70.13765;18.80020;-11.93396;,
 -46.22090;10.53829;-28.76808;,
 -61.70345;-8.70159;-5.58515;,
 -42.36963;62.94874;1.10136;,
 -39.84535;46.77469;-23.65891;,
 -65.47491;47.00609;2.31939;,
 -39.84535;46.77469;-23.65891;,
 -70.13765;18.80020;-11.93396;,
 -65.47491;47.00609;2.31939;,
 -7.16771;45.95903;-21.41671;,
 -39.84535;46.77469;-23.65891;,
 -10.94827;48.02751;14.44691;,
 -10.94827;48.02751;14.44691;,
 -39.84535;46.77469;-23.65891;,
 -42.36963;62.94874;1.10136;,
 -3.79055;-63.78272;-8.76219;,
 -26.94699;-49.51111;-0.39764;,
 0.33600;-41.48705;-23.77163;,
 19.03871;-9.67384;-30.23074;,
 53.83698;-16.37246;-5.16090;,
 29.98073;-46.20587;-3.70060;,
 66.97192;9.22084;-2.66508;,
 53.83698;-16.37246;-5.16090;,
 50.64001;30.39981;-23.09882;,
 37.30571;63.29393;-1.02933;,
 50.64001;30.39981;-23.09882;,
 17.78288;53.81061;-14.22175;,
 -7.16771;45.95903;-21.41671;,
 17.78288;53.81061;-14.22175;,
 50.64001;30.39981;-23.09882;,
 -11.10163;17.41690;-32.21252;,
 0.33600;-41.48705;-23.77163;,
 19.03871;-9.67384;-30.23074;,
 29.98073;-46.20587;-3.70060;,
 -11.10163;17.41690;-32.21252;,
 50.64001;30.39981;-23.09882;,
 19.03871;-9.67384;-30.23074;,
 19.03871;-9.67384;-30.23074;,
 50.64001;30.39981;-23.09882;,
 53.83698;-16.37246;-5.16090;,
 59.08044;43.77440;10.57352;,
 50.64001;30.39981;-23.09882;,
 37.30571;63.29393;-1.02933;,
 66.97192;9.22084;-2.66508;,
 50.64001;30.39981;-23.09882;,
 59.08044;43.77440;10.57352;,
 -10.94827;48.02751;14.44691;,
 17.78288;53.81061;-14.22175;,
 -7.16771;45.95903;-21.41671;,
 0.33600;-41.48705;-23.77163;,
 29.98073;-46.20587;-3.70060;,
 -3.79055;-63.78272;-8.76219;,
 -37.28668;40.00961;23.92098;,
 -65.47491;47.00609;2.31939;,
 -59.94006;23.76910;19.26725;,
 -37.28668;40.00961;23.92098;,
 -42.36963;62.94874;1.10136;,
 -65.47491;47.00609;2.31939;,
 -46.14110;-32.18489;-4.28619;,
 -26.94699;-49.51111;-0.39764;,
 -30.07746;-20.49980;23.32835;,
 -24.28309;4.37977;28.67999;,
 -37.28668;40.00961;23.92098;,
 -59.94006;23.76910;19.26725;,
 -59.94006;23.76910;19.26725;,
 -70.13765;18.80020;-11.93396;,
 -61.70345;-8.70159;-5.58515;,
 -10.94827;48.02751;14.44691;,
 -42.36963;62.94874;1.10136;,
 -37.28668;40.00961;23.92098;,
 -10.94827;48.02751;14.44691;,
 -37.28668;40.00961;23.92098;,
 7.25281;17.86189;29.20728;,
 -26.94699;-49.51111;-0.39764;,
 -0.40261;-46.21890;17.82732;,
 -30.07746;-20.49980;23.32835;,
 4.85948;-21.83687;25.97807;,
 -30.07746;-20.49980;23.32835;,
 -0.40261;-46.21890;17.82732;,
 -24.28309;4.37977;28.67999;,
 7.25281;17.86189;29.20728;,
 -37.28668;40.00961;23.92098;,
 -30.07746;-20.49980;23.32835;,
 4.85948;-21.83687;25.97807;,
 -24.28309;4.37977;28.67999;,
 7.25281;17.86189;29.20728;,
 -24.28309;4.37977;28.67999;,
 4.85948;-21.83687;25.97807;,
 -61.70345;-8.70159;-5.58515;,
 -30.07746;-20.49980;23.32835;,
 -59.94006;23.76910;19.26725;,
 -59.94006;23.76910;19.26725;,
 -30.07746;-20.49980;23.32835;,
 -24.28309;4.37977;28.67999;,
 -59.94006;23.76910;19.26725;,
 -65.47491;47.00609;2.31939;,
 -70.13765;18.80020;-11.93396;,
 -30.07746;-20.49980;23.32835;,
 -61.70345;-8.70159;-5.58515;,
 -46.14110;-32.18489;-4.28619;,
 -26.94699;-49.51111;-0.39764;,
 -3.79055;-63.78272;-8.76219;,
 -0.40261;-46.21890;17.82732;,
 29.98073;-46.20587;-3.70060;,
 29.44218;-28.91216;19.47698;,
 -0.40261;-46.21890;17.82732;,
 7.25281;17.86189;29.20728;,
 32.81021;3.37218;27.01179;,
 30.72450;39.81987;22.56176;,
 30.72450;39.81987;22.56176;,
 66.97192;9.22084;-2.66508;,
 59.08044;43.77440;10.57352;,
 37.30571;63.29393;-1.02933;,
 30.72450;39.81987;22.56176;,
 59.08044;43.77440;10.57352;,
 32.81021;3.37218;27.01179;,
 66.97192;9.22084;-2.66508;,
 30.72450;39.81987;22.56176;,
 30.72450;39.81987;22.56176;,
 -10.94827;48.02751;14.44691;,
 7.25281;17.86189;29.20728;,
 4.85948;-21.83687;25.97807;,
 -0.40261;-46.21890;17.82732;,
 29.44218;-28.91216;19.47698;,
 -3.79055;-63.78272;-8.76219;,
 29.98073;-46.20587;-3.70060;,
 -0.40261;-46.21890;17.82732;,
 7.25281;17.86189;29.20728;,
 4.85948;-21.83687;25.97807;,
 32.81021;3.37218;27.01179;,
 32.81021;3.37218;27.01179;,
 4.85948;-21.83687;25.97807;,
 29.44218;-28.91216;19.47698;,
 32.81021;3.37218;27.01179;,
 29.44218;-28.91216;19.47698;,
 53.83698;-16.37246;-5.16090;,
 17.78288;53.81061;-14.22175;,
 30.72450;39.81987;22.56176;,
 37.30571;63.29393;-1.02933;,
 29.44218;-28.91216;19.47698;,
 29.98073;-46.20587;-3.70060;,
 53.83698;-16.37246;-5.16090;,
 66.97192;9.22084;-2.66508;,
 32.81021;3.37218;27.01179;,
 53.83698;-16.37246;-5.16090;,
 30.72450;39.81987;22.56176;,
 17.78288;53.81061;-14.22175;,
 -10.94827;48.02751;14.44691;;
 
 60;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 3;15,16,17;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,28,29;,
 3;30,31,32;,
 3;33,34,35;,
 3;36,37,38;,
 3;39,40,41;,
 3;42,43,44;,
 3;45,46,47;,
 3;48,49,50;,
 3;51,52,53;,
 3;54,55,56;,
 3;57,58,59;,
 3;57,59,60;,
 3;61,62,63;,
 3;64,65,66;,
 3;67,68,69;,
 3;70,71,72;,
 3;73,74,75;,
 3;76,77,78;,
 3;79,80,81;,
 3;82,83,84;,
 3;85,86,87;,
 3;88,89,90;,
 3;91,92,93;,
 3;94,95,96;,
 3;97,98,99;,
 3;100,101,102;,
 3;103,104,105;,
 3;106,107,108;,
 3;109,110,111;,
 3;112,113,114;,
 3;115,116,117;,
 3;118,119,120;,
 3;121,122,123;,
 3;124,125,126;,
 3;127,128,129;,
 3;130,131,132;,
 3;133,134,135;,
 3;136,137,138;,
 3;139,140,141;,
 3;142,143,144;,
 3;145,146,147;,
 3;148,149,150;,
 3;151,152,153;,
 3;154,155,156;,
 3;157,158,159;,
 3;160,161,162;,
 3;163,164,165;,
 3;166,167,168;,
 3;169,170,171;,
 3;172,173,174;,
 3;175,176,177;;
 
 MeshMaterialList {
  1;
  60;
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
   0.800000;0.059608;0.059608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.100000;0.007451;0.007451;;
  }
 }
 MeshNormals {
  48;
  -0.370759;0.396489;-0.839842;,
  -0.470848;-0.499546;-0.727156;,
  0.080508;0.389063;-0.917686;,
  -0.305156;-0.356820;-0.882926;,
  -0.405367;-0.103446;-0.908282;,
  -0.448153;-0.526163;-0.722711;,
  -0.628887;0.100709;-0.770947;,
  -0.507500;0.696780;-0.506894;,
  -0.068556;-0.548370;-0.833421;,
  -0.020880;-0.483129;-0.875300;,
  0.006417;0.129034;-0.991619;,
  0.275162;-0.234553;-0.932347;,
  0.467703;0.269257;-0.841876;,
  0.543248;-0.313441;-0.778869;,
  0.052557;0.902647;-0.427161;,
  -0.675597;-0.048822;0.735653;,
  -0.436745;-0.396351;0.807564;,
  -0.137109;-0.050132;0.989286;,
  -0.171489;0.431017;0.885898;,
  -0.570557;-0.395224;-0.719905;,
  -0.582368;0.569982;-0.579627;,
  0.805304;0.453423;-0.381959;,
  0.276293;0.386069;0.880121;,
  0.804190;0.048603;-0.592382;,
  0.086168;0.917186;0.389031;,
  0.037272;-0.208863;0.977234;,
  0.034278;0.166130;0.985508;,
  0.446702;-0.470800;-0.760792;,
  0.473339;-0.452710;0.755648;,
  0.431785;-0.122915;0.893562;,
  0.496111;0.613396;-0.614507;,
  0.022211;-0.650454;0.759220;,
  -0.125626;0.989582;-0.070318;,
  0.296464;0.920350;-0.255079;,
  0.529296;0.734017;-0.425518;,
  -0.660016;0.383678;0.645887;,
  -0.176697;0.674205;0.717095;,
  -0.650933;-0.485098;0.583923;,
  -0.436073;-0.654155;0.617998;,
  -0.940491;-0.103098;0.323802;,
  -0.782730;-0.354846;0.511290;,
  0.032714;-0.835862;0.547964;,
  0.495178;-0.710235;0.500365;,
  0.581728;-0.175564;0.794210;,
  0.350072;0.237060;0.906229;,
  -0.226826;0.721292;0.654437;,
  0.712052;-0.395560;0.580099;,
  -0.619706;0.635954;0.459920;;
  60;
  3;1,3,5;,
  3;19,3,1;,
  3;4,0,10;,
  3;10,0,2;,
  3;0,4,6;,
  3;11,9,3;,
  3;5,3,9;,
  3;10,11,3;,
  3;10,3,4;,
  3;19,4,3;,
  3;6,4,19;,
  3;7,0,20;,
  3;0,6,20;,
  3;32,33,24;,
  3;24,33,34;,
  3;8,5,9;,
  3;11,13,27;,
  3;23,13,12;,
  3;30,12,14;,
  3;2,14,12;,
  3;2,12,10;,
  3;9,11,27;,
  3;10,12,11;,
  3;11,12,13;,
  3;21,12,30;,
  3;23,12,21;,
  3;24,14,32;,
  3;9,27,8;,
  3;18,35,15;,
  3;18,36,35;,
  3;37,38,16;,
  3;17,18,15;,
  3;15,39,40;,
  3;24,36,18;,
  3;24,18,26;,
  3;38,31,16;,
  3;25,16,31;,
  3;17,26,18;,
  3;16,25,17;,
  3;26,17,25;,
  3;40,16,15;,
  3;15,16,17;,
  3;15,35,39;,
  3;16,40,37;,
  3;38,41,31;,
  3;42,28,31;,
  3;26,29,22;,
  3;22,43,44;,
  3;45,22,44;,
  3;29,43,22;,
  3;22,24,26;,
  3;25,31,28;,
  3;41,42,31;,
  3;26,25,29;,
  3;29,25,28;,
  3;29,28,46;,
  3;47,47,45;,
  3;28,42,46;,
  3;43,29,46;,
  3;22,14,24;;
 }
 MeshTextureCoords {
  178;
  0.130900;0.887900;,
  0.132300;0.882600;,
  0.143600;0.893000;,
  0.107500;0.834100;,
  0.119000;0.838800;,
  0.116800;0.844500;,
  0.113800;0.667000;,
  0.123900;0.653900;,
  0.123500;0.667800;,
  0.156600;0.621600;,
  0.157700;0.610300;,
  0.168000;0.613800;,
  0.045500;0.673300;,
  0.053400;0.681900;,
  0.046300;0.685500;,
  0.238100;0.857000;,
  0.238300;0.869200;,
  0.230500;0.868400;,
  0.201200;0.892600;,
  0.200400;0.882200;,
  0.208400;0.885400;,
  0.237000;0.776600;,
  0.237100;0.790400;,
  0.228200;0.789700;,
  0.124800;0.724200;,
  0.126200;0.737700;,
  0.117300;0.736400;,
  0.102900;0.772900;,
  0.106200;0.760600;,
  0.109500;0.771900;,
  0.054900;0.738600;,
  0.065100;0.748200;,
  0.059000;0.751600;,
  0.028300;0.317300;,
  0.014600;0.316900;,
  0.014200;0.310000;,
  0.455400;0.417800;,
  0.467600;0.424600;,
  0.453000;0.423700;,
  0.138300;0.356100;,
  0.125900;0.355900;,
  0.125900;0.348700;,
  0.112800;0.348500;,
  0.099400;0.355200;,
  0.099200;0.348100;,
  0.195600;0.954100;,
  0.195600;0.947600;,
  0.204200;0.953000;,
  0.367400;0.860600;,
  0.379800;0.855400;,
  0.369200;0.866300;,
  0.467300;0.721800;,
  0.458500;0.733700;,
  0.461600;0.719900;,
  0.391300;0.558300;,
  0.390400;0.566100;,
  0.378200;0.565100;,
  0.294300;0.616000;,
  0.303300;0.611700;,
  0.304700;0.621700;,
  0.295600;0.625800;,
  0.291600;0.882200;,
  0.299800;0.878300;,
  0.299000;0.888600;,
  0.301400;0.712800;,
  0.310900;0.710100;,
  0.310900;0.724200;,
  0.410100;0.754300;,
  0.420600;0.744800;,
  0.416500;0.757400;,
  0.424100;0.316900;,
  0.423700;0.323800;,
  0.410000;0.324300;,
  0.080800;0.472600;,
  0.065200;0.478700;,
  0.064300;0.472700;,
  0.230700;0.318800;,
  0.236900;0.326600;,
  0.230800;0.326600;,
  0.288300;0.938100;,
  0.296600;0.940600;,
  0.288000;0.945800;,
  0.954900;0.621100;,
  0.965400;0.623600;,
  0.962000;0.629100;,
  0.935800;0.571900;,
  0.937900;0.565400;,
  0.949800;0.573500;,
  0.875300;0.860600;,
  0.864900;0.870700;,
  0.863600;0.864100;,
  0.895700;0.666900;,
  0.895700;0.653100;,
  0.905100;0.654000;,
  0.565000;0.514200;,
  0.564900;0.509500;,
  0.580600;0.509200;,
  0.860700;0.551000;,
  0.873700;0.549800;,
  0.873800;0.557600;,
  0.803500;0.625800;,
  0.812600;0.621700;,
  0.813900;0.632500;,
  0.798800;0.892600;,
  0.790900;0.896000;,
  0.791600;0.885400;,
  0.769900;0.856200;,
  0.777900;0.854900;,
  0.777300;0.867000;,
  0.828000;0.693200;,
  0.817900;0.682500;,
  0.827400;0.679400;,
  0.804400;0.822800;,
  0.795900;0.825400;,
  0.796900;0.812100;,
  0.772300;0.748200;,
  0.781300;0.760700;,
  0.772200;0.761900;,
  0.941600;0.767900;,
  0.930600;0.776800;,
  0.936200;0.764400;,
  0.918100;0.754300;,
  0.907500;0.763600;,
  0.911400;0.751700;,
  0.498400;0.495600;,
  0.497100;0.490100;,
  0.513500;0.489600;,
  0.903300;0.852700;,
  0.916700;0.844000;,
  0.905800;0.856500;,
  0.795600;0.971800;,
  0.787500;0.976700;,
  0.787600;0.970600;,
  0.646200;0.917800;,
  0.647200;0.913500;,
  0.659700;0.924800;,
  0.641300;0.669300;,
  0.631300;0.682000;,
  0.631500;0.667800;,
  0.539100;0.650300;,
  0.531900;0.657800;,
  0.535000;0.647200;,
  0.620500;0.542100;,
  0.621000;0.549700;,
  0.607700;0.550300;,
  0.557200;0.711700;,
  0.548700;0.701600;,
  0.555400;0.698400;,
  0.703200;0.636400;,
  0.713200;0.629900;,
  0.712000;0.640300;,
  0.715600;0.874300;,
  0.716300;0.885400;,
  0.708400;0.882200;,
  0.198800;0.194700;,
  0.206900;0.190700;,
  0.206800;0.194800;,
  0.717800;0.773000;,
  0.709400;0.784900;,
  0.708800;0.771100;,
  0.683700;0.790700;,
  0.685000;0.803800;,
  0.676200;0.800300;,
  0.599700;0.792600;,
  0.610300;0.799300;,
  0.606200;0.803400;,
  0.299700;0.295200;,
  0.287700;0.287400;,
  0.299700;0.287400;,
  0.583200;0.852700;,
  0.580500;0.855200;,
  0.569100;0.841700;,
  0.545200;0.763500;,
  0.550400;0.761000;,
  0.556200;0.774200;,
  0.236800;0.287400;,
  0.236800;0.295200;,
  0.230700;0.295200;;
 }
}
