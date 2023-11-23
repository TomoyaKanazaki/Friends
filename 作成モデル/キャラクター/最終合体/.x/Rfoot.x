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
 101;
 0.00078;-2.27678;-20.10445;,
 3.33131;-3.35687;-19.77167;,
 3.33131;-4.40378;-19.44910;,
 0.00078;-3.32370;-19.78188;,
 6.24615;-0.00348;-10.34475;,
 6.24615;-0.74981;-11.31013;,
 0.00078;0.33028;-11.64292;,
 0.00078;1.07660;-10.67753;,
 0.00078;1.17766;-6.62906;,
 6.24615;0.09758;-6.29628;,
 6.24615;1.14450;-6.61884;,
 0.00078;2.22458;-6.95162;,
 6.24615;-1.79672;-10.98757;,
 6.24615;-1.05040;-10.02219;,
 0.00078;0.02969;-10.35497;,
 0.00078;-0.71664;-11.32035;,
 6.24615;-0.74981;-11.31013;,
 6.24615;-0.00348;-10.34475;,
 6.24615;-1.05040;-10.02219;,
 6.24615;-1.79672;-10.98757;,
 -6.24460;-0.00348;-10.34475;,
 -6.24460;-0.74981;-11.31013;,
 -6.24460;-1.79672;-10.98757;,
 -6.24460;-1.05040;-10.02219;,
 -6.24460;-1.05040;-10.02219;,
 -6.24460;-1.79672;-10.98757;,
 -6.24460;1.14450;-6.61884;,
 -6.24460;0.09758;-6.29628;,
 -6.24460;-0.74981;-11.31013;,
 -6.24460;-0.00348;-10.34475;,
 -3.32975;-4.40378;-19.44910;,
 -3.32975;-3.35687;-19.77167;,
 0.00078;-3.32370;-19.78188;,
 3.33131;-4.40378;-19.44910;,
 -3.32975;-4.40378;-19.44910;,
 6.24615;1.14450;-6.61884;,
 6.24615;0.09758;-6.29628;,
 -6.24460;0.09758;-6.29628;,
 -6.24460;1.14450;-6.61884;,
 0.00000;-0.01467;-8.14231;,
 0.00040;-1.02359;-13.37565;,
 -4.71178;-1.25614;-13.09195;,
 -5.32948;-0.02314;-6.93459;,
 -2.91310;3.09345;-4.55532;,
 -2.88685;3.10792;0.00000;,
 0.00000;3.09875;-5.31078;,
 -2.88685;3.10792;3.14473;,
 0.00000;3.10792;4.16341;,
 2.91310;3.09345;-4.55532;,
 2.88685;3.10792;0.00000;,
 2.88685;3.10792;3.14473;,
 6.77380;-3.14849;6.19684;,
 -0.00018;-3.14849;8.58716;,
 -0.00018;-6.42926;8.58716;,
 6.77380;-6.72951;6.19684;,
 -6.77416;-10.31053;-16.27209;,
 -4.76471;-10.31053;-20.45547;,
 -6.77416;-10.31053;0.00000;,
 -6.77416;-10.31053;6.19684;,
 -0.00018;-10.31053;8.58716;,
 -0.00018;-10.31053;-22.18702;,
 6.77380;-10.31053;6.19684;,
 4.63533;-10.31053;-20.45547;,
 6.77380;-10.31053;-0.00000;,
 6.77380;-10.31053;-16.27209;,
 -6.77416;-3.14849;0.00000;,
 -6.77416;-10.31053;0.00000;,
 -6.77416;-3.14849;6.19684;,
 -6.77416;-6.72951;6.19684;,
 -6.77416;-10.31053;6.19684;,
 6.77380;-5.48978;-16.80991;,
 6.77380;-10.31053;-16.27209;,
 4.63533;-10.31053;-20.45547;,
 4.63533;-6.72951;-20.45547;,
 -6.77416;-6.72951;6.19684;,
 -6.77416;-3.14849;6.19684;,
 4.71255;-1.25653;-13.09283;,
 5.32948;-0.02314;-6.93459;,
 -6.77416;-5.48978;-16.80991;,
 -6.77416;-10.31053;-16.27209;,
 -6.77416;-3.14849;-7.96462;,
 6.77380;-10.31053;6.19684;,
 6.77380;-10.31053;-0.00000;,
 6.77380;-6.72951;6.19684;,
 6.77380;-3.14849;6.19684;,
 6.77380;-3.14849;-0.00000;,
 -0.00018;-10.31053;-22.18702;,
 -0.00018;-6.79330;-22.18702;,
 -4.76471;-6.72951;-20.45547;,
 -4.76471;-10.31053;-20.45547;,
 6.77380;-3.14849;-7.96462;,
 3.26923;-3.09859;-17.98834;,
 0.00078;-3.14166;-19.16714;,
 -3.35558;-3.09781;-17.98657;,
 5.28146;0.00000;0.00000;,
 6.77380;-3.14849;-0.00000;,
 5.28146;0.00000;6.19684;,
 0.00000;0.00000;8.25655;,
 -5.28145;0.00000;6.19684;,
 -5.28145;0.00000;0.00000;,
 -6.77416;-3.14849;0.00000;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,15,14;,
 4;26,27,8,11;,
 4;28,29,7,6;,
 4;30,31,0,3;,
 4;31,28,6,0;,
 4;5,1,0,6;,
 4;2,1,16,19;,
 4;32,33,12,15;,
 4;25,34,32,15;,
 4;21,31,30,22;,
 4;27,24,14,8;,
 4;13,9,8,14;,
 4;17,35,36,18;,
 4;11,10,4,7;,
 4;29,26,11,7;,
 4;37,38,20,23;,
 4;39,40,41,42;,
 3;43,44,45;,
 3;46,47,44;,
 3;44,47,45;,
 3;45,47,48;,
 3;47,49,48;,
 3;49,47,50;,
 4;51,52,53,54;,
 3;55,56,57;,
 3;57,56,58;,
 3;58,56,59;,
 3;56,60,59;,
 3;59,60,61;,
 3;60,62,61;,
 3;62,63,61;,
 3;63,62,64;,
 3;65,66,67;,
 3;66,68,67;,
 3;68,66,69;,
 4;70,71,72,73;,
 4;74,53,52,75;,
 4;76,40,39,77;,
 3;78,79,80;,
 3;79,66,80;,
 3;80,66,65;,
 3;81,82,83;,
 3;83,82,84;,
 3;84,82,85;,
 4;72,86,87,73;,
 4;88,87,86,89;,
 4;59,53,74,58;,
 4;54,53,59,61;,
 4;89,79,78,88;,
 3;85,82,90;,
 3;82,71,90;,
 3;90,71,70;,
 4;91,92,40,76;,
 4;41,40,92,93;,
 4;80,42,41,78;,
 4;90,77,94,95;,
 4;95,94,96,51;,
 4;51,96,97,52;,
 4;52,97,98,75;,
 4;75,98,99,100;,
 4;100,99,42,80;,
 4;70,76,77,90;,
 4;73,91,76,70;,
 4;87,92,91,73;,
 4;78,41,93,88;,
 4;88,93,92,87;,
 4;77,48,49,94;,
 4;94,49,50,96;,
 4;96,50,47,97;,
 4;97,47,46,98;,
 4;98,46,44,99;,
 4;99,44,43,42;,
 4;42,43,45,39;,
 4;39,45,48,77;;
 
 MeshMaterialList {
  1;
  80;
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
  86;
  0.000003;-0.294455;-0.955665;,
  -0.000003;-0.294455;-0.955665;,
  0.000000;0.294445;0.955668;,
  -0.000000;0.294445;0.955668;,
  -0.000000;-0.294455;-0.955665;,
  -0.000000;0.294445;0.955668;,
  -0.987383;-0.046626;-0.151328;,
  0.000000;0.879888;-0.475180;,
  0.211610;0.859963;-0.464419;,
  -0.211609;-0.859962;0.464420;,
  -0.000000;-0.879888;0.475181;,
  -1.000000;0.000000;0.000000;,
  -0.000000;-0.887606;0.460603;,
  -0.175290;-0.873863;0.453471;,
  0.175290;0.873864;-0.453471;,
  0.000000;0.887607;-0.460602;,
  0.000000;-1.000000;-0.000000;,
  0.981306;0.189689;-0.032498;,
  -0.981296;0.189740;-0.032516;,
  0.339749;0.063451;0.938373;,
  -0.989291;0.145960;0.000000;,
  0.000000;0.067475;0.997721;,
  -0.975866;0.218368;0.000619;,
  0.975877;0.218322;0.000618;,
  0.583575;0.339456;-0.737706;,
  0.004159;0.341207;-0.939979;,
  -0.588421;0.341629;-0.732837;,
  0.000000;0.000000;1.000000;,
  0.332759;0.000000;0.943012;,
  -0.907645;0.298693;-0.294894;,
  0.904096;0.299320;-0.304987;,
  0.000007;0.873688;-0.486487;,
  -0.638233;0.729466;-0.246044;,
  -0.440755;0.836036;-0.326770;,
  0.000379;0.960981;-0.276615;,
  0.535662;0.786698;-0.306876;,
  0.853330;0.521370;0.001370;,
  0.709570;0.668904;0.221534;,
  0.000000;0.505703;0.862708;,
  -0.535175;0.592927;0.601685;,
  -0.853305;0.521410;0.001370;,
  0.438307;0.836021;-0.330086;,
  0.333215;0.761004;-0.556633;,
  0.002119;0.813773;-0.581179;,
  -0.334563;0.762586;-0.553652;,
  0.276488;0.938429;-0.207136;,
  0.440255;0.897873;-0.000047;,
  0.382012;0.896220;0.225514;,
  -0.000174;0.983774;0.179412;,
  -0.382012;0.896220;0.225514;,
  -0.351580;0.936158;-0.000243;,
  -0.376374;0.883121;-0.280070;,
  0.000181;0.948366;-0.317177;,
  0.987383;-0.046626;-0.151328;,
  1.000000;0.000000;0.000000;,
  0.175290;-0.873863;0.453471;,
  0.211609;-0.859962;0.464420;,
  -0.211610;0.859963;-0.464419;,
  -0.175290;0.873864;-0.453471;,
  -0.250349;0.916166;-0.312993;,
  0.000000;0.946301;-0.323288;,
  0.250349;0.916166;-0.312993;,
  0.949852;-0.092075;-0.298837;,
  -0.000000;-0.946301;0.323288;,
  -0.250347;-0.916167;0.312993;,
  0.250347;-0.916167;0.312994;,
  -0.949852;-0.092076;-0.298838;,
  0.178072;-0.940394;0.289741;,
  -0.000000;-0.955668;0.294447;,
  -0.178072;-0.940394;0.289741;,
  0.000000;0.955668;-0.294448;,
  0.178071;0.940394;-0.289742;,
  -0.178071;0.940394;-0.289742;,
  0.986713;-0.009393;-0.162205;,
  0.657313;-0.014650;-0.753475;,
  -0.332759;0.000000;0.943012;,
  -0.339749;0.063471;0.938372;,
  -0.988023;-0.008930;-0.154045;,
  0.989295;0.145929;0.000000;,
  0.004453;0.000000;-0.999990;,
  -0.663545;-0.014060;-0.748005;,
  -0.332759;0.000000;0.943012;,
  0.332759;0.000000;0.943012;,
  0.905702;0.423909;0.002414;,
  0.345348;0.126642;0.929891;,
  -0.903591;0.428396;0.000000;;
  80;
  4;4,1,1,4;,
  4;14,8,7,15;,
  4;5,3,3,5;,
  4;9,13,12,10;,
  4;53,54,54,53;,
  4;11,6,6,11;,
  4;55,56,10,12;,
  4;2,2,5,5;,
  4;57,58,15,7;,
  4;0,0,4,4;,
  4;59,57,7,60;,
  4;8,61,60,7;,
  4;62,62,53,53;,
  4;63,64,9,10;,
  4;56,65,63,10;,
  4;6,66,66,6;,
  4;67,55,12,68;,
  4;13,69,68,12;,
  4;54,54,54,54;,
  4;70,71,14,15;,
  4;58,72,70,15;,
  4;11,11,11,11;,
  4;31,34,33,32;,
  3;51,50,52;,
  3;49,48,50;,
  3;50,48,52;,
  3;52,48,45;,
  3;48,46,45;,
  3;46,48,47;,
  4;19,21,27,28;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;22,11,20;,
  3;11,11,20;,
  3;11,11,11;,
  4;30,73,74,24;,
  4;75,27,21,76;,
  4;41,34,31,35;,
  3;29,77,18;,
  3;77,11,18;,
  3;18,11,22;,
  3;54,54,54;,
  3;54,54,78;,
  3;78,54,23;,
  4;74,79,25,24;,
  4;26,25,79,80;,
  4;27,27,75,81;,
  4;28,27,27,82;,
  4;80,77,29,26;,
  3;23,54,17;,
  3;54,73,17;,
  3;17,73,30;,
  4;42,43,34,41;,
  4;33,34,43,44;,
  4;18,32,33,29;,
  4;17,83,36,23;,
  4;23,36,37,78;,
  4;19,84,38,21;,
  4;21,38,39,76;,
  4;20,85,40,22;,
  4;22,40,32,18;,
  4;30,41,35,17;,
  4;24,42,41,30;,
  4;25,43,42,24;,
  4;29,33,44,26;,
  4;26,44,43,25;,
  4;35,45,46,36;,
  4;36,46,47,37;,
  4;37,47,48,38;,
  4;38,48,49,39;,
  4;39,49,50,40;,
  4;40,50,51,32;,
  4;32,51,52,31;,
  4;31,52,45,35;;
 }
 MeshTextureCoords {
  101;
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.625000;0.562500;,
  0.625000;0.625000;,
  0.500000;0.625000;,
  0.500000;0.562500;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.125000;,
  0.625000;0.187500;,
  0.500000;0.187500;,
  0.500000;0.125000;,
  0.750000;0.750000;,
  0.812500;0.750000;,
  0.812500;1.000000;,
  0.750000;1.000000;,
  0.187500;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;0.187500;,
  0.375000;0.125000;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.375000;0.625000;,
  0.375000;0.562500;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.795528;,
  0.625000;0.812500;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.750000;,
  0.375000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.385480;,
  0.375000;0.375000;,
  0.625000;0.062500;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.062500;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  0.375000;0.812500;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.375000;0.812500;,
  0.375000;0.750000;,
  0.625000;0.812500;,
  0.687500;1.000000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.125000;0.875000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.877227;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.877227;,
  0.625000;0.875000;,
  0.375000;0.625000;,
  0.375000;0.625000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.625000;;
 }
}
