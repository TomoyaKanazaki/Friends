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
 229;
 -0.26360;164.45821;-71.13240;,
 62.56720;164.45821;-23.00690;,
 62.56720;70.29030;-42.43770;,
 -0.26360;70.29030;-90.56329;,
 -0.26360;164.45821;51.73020;,
 62.56720;164.45821;51.73020;,
 -0.26360;70.29030;94.70850;,
 69.25450;70.29030;64.71150;,
 59.10150;164.45821;64.71150;,
 -0.26360;164.45821;77.69280;,
 -0.26360;70.29030;-90.56329;,
 62.56720;70.29030;-42.43770;,
 72.72030;70.29030;51.73020;,
 -0.26360;70.29030;51.73020;,
 72.08280;70.29030;-42.43770;,
 72.08280;164.45821;-23.00690;,
 59.10150;164.45821;64.71150;,
 69.25450;70.29030;64.71150;,
 -69.78180;70.29030;64.71150;,
 -59.62880;164.45821;64.71150;,
 -72.61010;164.45821;-23.00690;,
 -72.61010;70.29030;-42.43770;,
 -73.24760;70.29030;51.73020;,
 -63.09450;70.29030;-42.43770;,
 -59.62880;164.45821;64.71150;,
 -69.78180;70.29030;64.71150;,
 -63.09450;164.45821;-23.00690;,
 -63.09450;164.45821;51.73020;,
 -63.09450;70.29030;-42.43770;,
 72.72030;70.29030;51.73020;,
 62.56720;164.45821;51.73020;,
 -73.24760;70.29030;51.73020;,
 -63.09450;164.45821;51.73020;,
 -9.20350;213.59749;-63.63210;,
 -2.65170;427.21439;-191.88879;,
 2.12440;427.21439;-191.88870;,
 8.67620;213.59749;-63.63210;,
 -2.65170;435.38818;-174.89911;,
 2.12440;435.38818;-174.89911;,
 -9.20350;239.55109;-9.68690;,
 8.67620;239.55109;-9.68690;,
 -9.20350;213.59749;-63.63210;,
 8.67620;213.59749;-63.63210;,
 2.12440;435.38818;-174.89911;,
 8.67620;239.55109;-9.68690;,
 -9.20350;239.55109;-9.68690;,
 -2.65170;435.38818;-174.89911;,
 -0.26360;230.76439;-60.56990;,
 62.04650;235.45279;-24.32300;,
 70.89090;182.28650;-32.48210;,
 -0.26360;176.88071;-73.35789;,
 -0.26360;252.13580;53.55060;,
 41.31650;252.13580;46.67180;,
 41.31650;252.13580;-9.84450;,
 -0.26360;252.13580;-34.27910;,
 -0.26360;173.50259;80.83030;,
 67.57530;177.58620;67.29150;,
 61.12790;231.46989;61.30300;,
 -0.26360;227.38631;80.14550;,
 -0.26360;173.50259;-61.68200;,
 65.26590;173.50259;-22.09610;,
 57.53490;173.50259;53.75260;,
 -0.26360;173.50259;53.75260;,
 61.12790;231.46989;61.30300;,
 67.57530;177.58620;67.29150;,
 -68.10260;177.58620;67.29150;,
 -61.65520;231.46989;61.30300;,
 -62.57380;235.45279;-24.32300;,
 -71.41821;182.28650;-32.48210;,
 -58.06220;173.50259;53.75260;,
 -65.79320;173.50259;-22.09610;,
 -61.65520;231.46989;61.30300;,
 -68.10260;177.58620;67.29150;,
 -41.84370;252.13580;-9.84450;,
 -41.84370;252.13580;46.67180;,
 65.26590;173.50259;-22.09610;,
 57.53490;173.50259;53.75260;,
 41.31650;252.13580;46.67180;,
 -58.06220;173.50259;53.75260;,
 -65.79320;173.50259;-22.09610;,
 -41.84370;252.13580;46.67180;,
 -0.26360;173.50259;-61.68200;,
 -0.26360;177.31821;-54.03640;,
 54.73770;177.31821;-20.68020;,
 54.73770;160.97321;-20.68020;,
 -0.26360;160.97321;-54.03640;,
 -0.26360;177.31821;52.00980;,
 54.73770;177.31821;52.00980;,
 -0.26360;160.97321;52.00980;,
 54.73770;160.97321;52.00980;,
 -0.26360;160.97321;-54.03640;,
 54.73770;160.97321;-20.68020;,
 54.73770;177.31821;52.00980;,
 54.73770;160.97321;52.00980;,
 -55.26500;160.97321;52.00980;,
 -55.26500;177.31821;52.00980;,
 -55.26500;177.31821;-20.68020;,
 -55.26500;160.97321;-20.68020;,
 -55.26500;160.97321;52.00980;,
 -55.26500;160.97321;-20.68020;,
 -55.26500;177.31821;52.00980;,
 -82.43200;116.68871;-1.52360;,
 -82.43200;133.44060;-1.52360;,
 -67.54020;133.44060;-1.52360;,
 -67.54020;116.68871;-1.52360;,
 -82.43200;150.19240;-1.52360;,
 -67.54020;150.19240;-1.52360;,
 -82.43200;150.19240;10.25330;,
 -67.54020;150.19240;10.25330;,
 -82.43200;150.19240;29.42870;,
 -67.54020;150.19240;29.42870;,
 -82.43200;133.44060;31.98020;,
 -67.54020;133.44060;31.98020;,
 -82.43200;116.68871;31.98020;,
 -67.54020;116.68871;31.98020;,
 -82.43200;111.81931;10.25330;,
 -67.54020;111.81931;10.25330;,
 -82.43200;116.68871;-1.52360;,
 -67.54020;116.68871;-1.52360;,
 -67.15680;113.55960;10.70450;,
 -67.15680;133.21980;10.70450;,
 -67.15680;133.21980;30.46080;,
 -67.15680;117.98740;30.46080;,
 -67.15680;117.98740;-0.00420;,
 -67.15680;133.21980;-0.00420;,
 -67.15680;148.45230;10.70450;,
 -67.15680;148.45230;28.14070;,
 -67.15680;148.45230;-0.00420;,
 -82.81540;117.98740;30.46080;,
 -82.81540;133.21980;30.46080;,
 -82.81540;133.21980;10.70450;,
 -82.81540;113.55960;10.70450;,
 -82.81540;133.21980;-0.00420;,
 -82.81540;117.98740;-0.00420;,
 -82.81540;148.45230;28.14070;,
 -82.81540;148.45230;10.70450;,
 -82.81540;148.45230;-0.00420;,
 -67.54020;111.81931;10.25330;,
 -67.54020;116.68871;31.98020;,
 -67.54020;133.44060;31.98020;,
 -67.54020;150.19240;29.42870;,
 -67.54020;150.19240;10.25330;,
 -82.43200;116.68871;31.98020;,
 -82.43200;111.81931;10.25330;,
 -82.43200;133.44060;31.98020;,
 -82.43200;150.19240;10.25330;,
 -82.43200;150.19240;29.42870;,
 81.90469;116.68871;-1.52360;,
 67.01290;116.68871;-1.52360;,
 67.01290;133.44060;-1.52360;,
 81.90469;133.44060;-1.52360;,
 67.01290;150.19240;-1.52360;,
 81.90469;150.19240;-1.52360;,
 67.01290;150.19240;10.25330;,
 81.90469;150.19240;10.25330;,
 67.01290;150.19240;29.42870;,
 81.90469;150.19240;29.42870;,
 67.01290;133.44060;31.98020;,
 81.90469;133.44060;31.98020;,
 67.01290;116.68871;31.98020;,
 81.90469;116.68871;31.98020;,
 67.01290;111.81931;10.25330;,
 81.90469;111.81931;10.25330;,
 67.01290;116.68871;-1.52360;,
 81.90469;116.68871;-1.52360;,
 66.62960;113.55960;10.70450;,
 66.62960;117.98740;30.46080;,
 66.62960;133.21980;30.46080;,
 66.62960;133.21980;10.70450;,
 66.62960;117.98740;-0.00420;,
 66.62960;133.21980;-0.00420;,
 66.62960;148.45230;28.14070;,
 66.62960;148.45230;10.70450;,
 66.62960;148.45230;-0.00420;,
 82.28810;117.98740;30.46080;,
 82.28810;113.55960;10.70450;,
 82.28810;133.21980;10.70450;,
 82.28810;133.21980;30.46080;,
 82.28810;117.98740;-0.00420;,
 82.28810;133.21980;-0.00420;,
 82.28810;148.45230;10.70450;,
 82.28810;148.45230;28.14070;,
 82.28810;148.45230;-0.00420;,
 67.01290;111.81931;10.25330;,
 67.01290;116.68871;31.98020;,
 67.01290;133.44060;31.98020;,
 67.01290;150.19240;29.42870;,
 67.01290;150.19240;10.25330;,
 81.90469;116.68871;31.98020;,
 81.90469;111.81931;10.25330;,
 81.90469;133.44060;31.98020;,
 81.90469;150.19240;10.25330;,
 81.90469;150.19240;29.42870;,
 117.16620;0.08160;117.16620;,
 60.79710;167.35211;65.44200;,
 0.00000;172.21300;75.68330;,
 0.00000;0.08160;165.69800;,
 -60.13860;167.35211;65.44200;,
 -117.16620;0.08160;117.16620;,
 -103.42400;129.20219;14.14430;,
 -165.69789;0.08160;0.00000;,
 -65.81530;166.03009;-30.27270;,
 -117.16620;0.08160;-117.16620;,
 0.00000;165.75369;-73.43140;,
 0.00000;0.08160;-165.69780;,
 63.06440;166.03009;-32.87820;,
 117.16620;0.08160;-117.16620;,
 103.42400;129.20219;14.14430;,
 165.69789;0.08160;0.00000;,
 60.79710;167.35211;65.44200;,
 117.16620;0.08160;117.16620;,
 0.00000;0.08160;165.69800;,
 0.00000;0.00000;0.00000;,
 117.16620;0.08160;117.16620;,
 -117.16620;0.08160;117.16620;,
 -165.69789;0.08160;0.00000;,
 -117.16620;0.08160;-117.16620;,
 0.00000;0.08160;-165.69780;,
 117.16620;0.08160;-117.16620;,
 165.69789;0.08160;0.00000;,
 60.79710;167.35211;65.44200;,
 0.00000;32.05790;0.00000;,
 0.00000;172.21300;75.68330;,
 -60.13860;167.35211;65.44200;,
 -103.42400;129.20219;14.14430;,
 -65.81530;166.03009;-30.27270;,
 0.00000;165.75369;-73.43140;,
 63.06440;166.03009;-32.87820;,
 103.42400;129.20219;14.14430;;
 
 150;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,10,13;,
 4;24,25,6,9;,
 4;26,27,4,0;,
 4;28,26,0,3;,
 4;4,9,8,5;,
 4;12,7,6,13;,
 4;2,14,17,29;,
 4;30,16,15,1;,
 4;1,15,14,2;,
 4;31,18,21,28;,
 4;28,21,20,26;,
 4;26,20,19,32;,
 4;27,24,9,4;,
 4;13,6,25,22;,
 4;33,34,35,36;,
 4;34,37,38,35;,
 4;37,39,40,38;,
 4;39,41,42,40;,
 4;36,35,43,44;,
 4;45,46,34,33;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;49,48,63,64;,
 4;65,66,67,68;,
 4;69,70,59,62;,
 4;71,72,55,58;,
 4;73,74,51,54;,
 4;68,67,47,50;,
 4;51,58,57,52;,
 4;61,56,55,62;,
 4;75,49,64,76;,
 4;77,63,48,53;,
 4;53,48,49,75;,
 4;78,65,68,79;,
 4;79,68,67,73;,
 4;73,67,66,80;,
 4;74,71,58,51;,
 4;62,55,72,69;,
 4;81,50,49,75;,
 4;75,49,48,53;,
 4;53,48,47,54;,
 4;79,68,50,81;,
 4;54,47,67,73;,
 4;73,67,68,79;,
 4;82,83,84,85;,
 4;86,87,83,82;,
 4;88,89,87,86;,
 4;90,91,89,88;,
 4;84,83,92,93;,
 4;94,95,96,97;,
 4;98,99,90,88;,
 4;100,98,88,86;,
 4;96,100,86,82;,
 4;97,96,82,85;,
 4;101,102,103,104;,
 4;102,105,106,103;,
 4;105,107,108,106;,
 4;107,109,110,108;,
 4;109,111,112,110;,
 4;111,113,114,112;,
 4;113,115,116,114;,
 4;115,117,118,116;,
 4;119,120,121,122;,
 4;123,124,120,119;,
 4;120,125,126,121;,
 4;124,127,125,120;,
 4;128,129,130,131;,
 4;131,130,132,133;,
 4;129,134,135,130;,
 4;130,135,136,132;,
 4;137,119,122,138;,
 4;138,122,121,139;,
 4;104,123,119,137;,
 4;103,124,123,104;,
 4;139,121,126,140;,
 4;140,126,125,141;,
 4;141,125,127,106;,
 4;106,127,124,103;,
 4;142,128,131,143;,
 4;144,129,128,142;,
 4;143,131,133,101;,
 4;101,133,132,102;,
 4;145,135,134,146;,
 4;146,134,129,144;,
 4;102,132,136,105;,
 4;105,136,135,145;,
 4;147,148,149,150;,
 4;150,149,151,152;,
 4;152,151,153,154;,
 4;154,153,155,156;,
 4;156,155,157,158;,
 4;158,157,159,160;,
 4;160,159,161,162;,
 4;162,161,163,164;,
 4;165,166,167,168;,
 4;169,165,168,170;,
 4;168,167,171,172;,
 4;170,168,172,173;,
 4;174,175,176,177;,
 4;175,178,179,176;,
 4;177,176,180,181;,
 4;176,179,182,180;,
 4;183,184,166,165;,
 4;184,185,167,166;,
 4;148,183,165,169;,
 4;149,148,169,170;,
 4;185,186,171,167;,
 4;186,187,172,171;,
 4;187,151,173,172;,
 4;151,149,170,173;,
 4;188,189,175,174;,
 4;190,188,174,177;,
 4;189,147,178,175;,
 4;147,150,179,178;,
 4;191,192,181,180;,
 4;192,190,177,181;,
 4;150,152,182,179;,
 4;152,191,180,182;,
 4;193,194,195,196;,
 4;196,195,197,198;,
 4;198,197,199,200;,
 4;200,199,201,202;,
 4;202,201,203,204;,
 4;204,203,205,206;,
 4;206,205,207,208;,
 4;208,207,209,210;,
 3;211,212,213;,
 3;214,212,211;,
 3;215,212,214;,
 3;216,212,215;,
 3;217,212,216;,
 3;218,212,217;,
 3;219,212,218;,
 3;213,212,219;,
 3;220,221,222;,
 3;222,221,223;,
 3;223,221,224;,
 3;224,221,225;,
 3;225,221,226;,
 3;226,221,227;,
 3;227,221,228;,
 3;228,221,220;;
 
 MeshMaterialList {
  1;
  150;
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
  169;
  0.000000;-1.000000;-0.000000;,
  0.316274;0.191712;-0.929095;,
  0.000000;1.000000;0.000000;,
  0.600078;0.161656;-0.783437;,
  0.000000;0.114448;0.993429;,
  0.305150;0.108990;0.946047;,
  0.994992;0.050475;0.086268;,
  -0.994992;0.050475;0.086268;,
  0.000008;-0.514751;-0.857340;,
  0.000004;0.901134;-0.433540;,
  0.000000;0.644813;0.764340;,
  -0.315937;-0.939464;-0.132633;,
  0.315938;-0.939464;-0.132633;,
  -0.357538;0.913366;-0.194753;,
  0.357539;0.913366;-0.194753;,
  -0.310413;0.911593;0.269521;,
  0.310414;0.911593;0.269521;,
  -0.236224;-0.970649;0.045150;,
  0.236224;-0.970649;0.045150;,
  0.000000;-0.978586;-0.205837;,
  0.000000;-0.998495;0.054847;,
  0.000000;0.925313;0.379205;,
  0.000000;0.954432;-0.298429;,
  0.000000;0.078367;0.996925;,
  0.000000;0.423283;0.905997;,
  0.203931;0.414388;0.886958;,
  0.239266;0.076090;0.967968;,
  0.477893;0.206793;-0.853730;,
  0.410930;0.521751;-0.747604;,
  -0.989430;0.142200;0.028426;,
  -0.922356;0.109068;0.370627;,
  -0.752608;0.629480;-0.193228;,
  -0.886700;0.461596;0.026320;,
  0.000000;0.572305;-0.820041;,
  0.000000;0.235415;-0.971895;,
  -0.871364;0.000000;-0.490636;,
  0.871365;0.000000;-0.490636;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.518553;0.000000;-0.855046;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.075503;0.997146;,
  0.000000;-0.996322;-0.085689;,
  0.992058;-0.076697;0.099691;,
  0.994315;-0.106219;-0.007413;,
  0.992491;0.009190;0.121972;,
  1.000000;0.000000;0.000000;,
  0.991839;-0.065462;-0.109406;,
  0.992373;0.000000;-0.123274;,
  0.993122;0.084812;0.080722;,
  0.994127;0.108221;0.000000;,
  0.993940;0.072591;-0.082542;,
  -0.992058;-0.076697;0.099691;,
  -0.994315;-0.106219;-0.007413;,
  -0.992491;0.009190;0.121972;,
  -0.991839;-0.065462;-0.109406;,
  -0.992373;0.000000;-0.123274;,
  -0.994127;0.108221;0.000000;,
  -0.993122;0.084812;0.080722;,
  -0.993940;0.072591;-0.082542;,
  0.000000;-0.996322;-0.085689;,
  -0.992062;-0.076677;0.099666;,
  -0.994318;-0.106192;-0.007411;,
  -0.992495;0.009188;0.121942;,
  -0.991843;-0.065445;-0.109379;,
  -0.992376;0.000000;-0.123243;,
  -0.993125;0.084790;0.080702;,
  -0.994130;0.108194;0.000000;,
  -0.993943;0.072573;-0.082522;,
  0.992058;-0.076698;0.099693;,
  0.994315;-0.106221;-0.007413;,
  0.992491;0.009190;0.121975;,
  0.991839;-0.065463;-0.109408;,
  0.992372;0.000000;-0.123276;,
  0.994127;0.108223;0.000000;,
  0.993122;0.084813;0.080723;,
  0.993940;0.072593;-0.082544;,
  0.600989;0.436757;0.669369;,
  -0.000440;0.437594;0.899173;,
  -0.599897;0.437560;0.669824;,
  -0.896339;0.443030;0.017344;,
  -0.648777;0.486792;-0.584912;,
  -0.001629;0.535145;-0.844759;,
  0.643882;0.488517;-0.588869;,
  0.895233;0.445412;0.012867;,
  0.000000;-1.000000;-0.000000;,
  -0.000195;0.530772;-0.847515;,
  -0.305149;0.108990;0.946047;,
  -0.316273;0.191712;-0.929095;,
  -0.600077;0.161657;-0.783438;,
  0.000000;0.000000;0.000000;,
  0.000000;0.202085;-0.979368;,
  0.000000;-0.901132;0.433544;,
  0.999651;0.023789;-0.011445;,
  -0.999651;0.023789;-0.011445;,
  0.922356;0.109068;0.370626;,
  0.898925;0.347478;0.266820;,
  0.886700;0.461595;0.026320;,
  0.989430;0.142200;0.028426;,
  -0.203931;0.414388;0.886958;,
  -0.239266;0.076090;0.967968;,
  -0.477893;0.206793;-0.853730;,
  0.354851;-0.932460;0.067824;,
  0.000000;-0.993976;0.109601;,
  0.465308;-0.863326;-0.195339;,
  -0.742111;-0.062555;-0.667351;,
  -0.354850;-0.932460;0.067824;,
  -0.465308;-0.863326;-0.195339;,
  0.742110;-0.062555;-0.667352;,
  0.000000;-0.911948;-0.410306;,
  0.742111;0.062555;0.667351;,
  -0.742110;0.062555;0.667352;,
  -0.518552;0.000000;-0.855046;,
  0.000000;0.150575;0.988599;,
  0.000000;-0.975794;0.218693;,
  0.000000;-0.924122;-0.382097;,
  0.977273;-0.211470;-0.014759;,
  0.982050;-0.115017;0.149499;,
  0.970072;0.018244;0.242133;,
  0.981594;-0.098056;-0.163882;,
  0.969607;0.000000;-0.244667;,
  0.984447;0.127256;0.121118;,
  0.976576;0.215172;0.000000;,
  0.986274;0.109043;-0.123991;,
  -0.982050;-0.115017;0.149499;,
  -0.977273;-0.211470;-0.014759;,
  -0.970072;0.018244;0.242133;,
  -0.981594;-0.098056;-0.163882;,
  -0.969607;0.000000;-0.244667;,
  -0.976576;0.215172;0.000000;,
  -0.984447;0.127256;0.121118;,
  -0.986274;0.109043;-0.123991;,
  0.000000;-0.975794;0.218693;,
  0.000000;-0.924122;-0.382097;,
  -0.977284;-0.211418;-0.014756;,
  -0.982059;-0.114988;0.149462;,
  -0.970086;0.018239;0.242074;,
  -0.981604;-0.098032;-0.163841;,
  -0.969622;0.000000;-0.244608;,
  -0.984455;0.127223;0.121088;,
  -0.976588;0.215118;0.000000;,
  -0.986281;0.109016;-0.123960;,
  0.982049;-0.115019;0.149502;,
  0.977272;-0.211475;-0.014759;,
  0.970070;0.018244;0.242138;,
  0.981594;-0.098058;-0.163885;,
  0.969606;0.000000;-0.244672;,
  0.976575;0.215176;0.000000;,
  0.984447;0.127258;0.121121;,
  0.986273;0.109045;-0.123993;,
  0.000000;-1.000000;0.000492;,
  0.000348;-1.000000;0.000348;,
  -0.000348;-1.000000;0.000348;,
  -0.000492;-1.000000;0.000000;,
  -0.000348;-1.000000;-0.000348;,
  0.000000;-1.000000;-0.000492;,
  0.000348;-1.000000;-0.000348;,
  0.000492;-1.000000;-0.000000;,
  -0.261210;0.512918;-0.817731;,
  0.000596;0.475147;-0.879906;,
  0.260744;0.511838;-0.818556;,
  0.403643;0.537533;-0.740359;,
  0.494657;0.415491;0.763336;,
  0.000879;0.481594;0.876394;,
  0.497149;0.416255;0.761298;,
  0.004167;0.481405;0.876489;,
  -0.495625;0.419889;0.760295;,
  -0.498842;0.420767;0.757702;,
  -0.405570;0.539249;-0.738054;;
  150;
  4;3,1,1,3;,
  4;2,2,2,2;,
  4;4,5,5,4;,
  4;0,0,0,0;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;0,0,0,0;,
  4;87,87,4,4;,
  4;2,2,2,2;,
  4;88,88,89,89;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;90,90,90,90;,
  4;0,0,0,0;,
  4;1,91,91,1;,
  4;2,2,2,2;,
  4;88,91,91,88;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;33,28,27,34;,
  4;21,16,14,22;,
  4;23,26,25,24;,
  4;19,12,18,20;,
  4;95,96,97,98;,
  4;29,32,31,30;,
  4;17,11,19,20;,
  4;99,100,23,24;,
  4;13,15,21,22;,
  4;101,101,33,34;,
  4;21,24,25,16;,
  4;18,102,103,20;,
  4;12,104,102,18;,
  4;16,97,96,14;,
  4;105,105,105,105;,
  4;17,106,107,11;,
  4;108,108,108,108;,
  4;13,31,32,15;,
  4;15,99,24,21;,
  4;20,103,106,17;,
  4;19,109,104,12;,
  4;110,95,96,110;,
  4;14,28,33,22;,
  4;11,107,109,19;,
  4;22,33,31,13;,
  4;111,111,30,111;,
  4;39,36,36,39;,
  4;2,2,2,2;,
  4;38,38,38,38;,
  4;0,0,0,0;,
  4;36,36,46,46;,
  4;37,37,35,35;,
  4;0,0,0,0;,
  4;38,38,38,38;,
  4;2,2,2,2;,
  4;35,35,112,112;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;113,41,41,113;,
  4;41,38,38,41;,
  4;114,42,42,114;,
  4;42,115,115,42;,
  4;44,46,45,43;,
  4;47,48,46,44;,
  4;46,50,49,45;,
  4;48,51,50,46;,
  4;52,54,37,53;,
  4;53,37,56,55;,
  4;54,58,57,37;,
  4;37,57,59,56;,
  4;116,44,43,117;,
  4;117,43,45,118;,
  4;119,47,44,116;,
  4;120,48,47,119;,
  4;118,45,49,121;,
  4;121,49,50,122;,
  4;122,50,51,123;,
  4;123,51,48,120;,
  4;124,52,53,125;,
  4;126,54,52,124;,
  4;125,53,55,127;,
  4;127,55,56,128;,
  4;129,57,58,130;,
  4;130,58,54,126;,
  4;128,56,59,131;,
  4;131,59,57,129;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;113,113,41,41;,
  4;41,41,38,38;,
  4;132,132,60,60;,
  4;60,60,133,133;,
  4;62,61,63,37;,
  4;64,62,37,65;,
  4;37,63,66,67;,
  4;65,37,67,68;,
  4;69,70,46,71;,
  4;70,72,73,46;,
  4;71,46,74,75;,
  4;46,73,76,74;,
  4;134,135,61,62;,
  4;135,136,63,61;,
  4;137,134,62,64;,
  4;138,137,64,65;,
  4;136,139,66,63;,
  4;139,140,67,66;,
  4;140,141,68,67;,
  4;141,138,65,68;,
  4;142,143,70,69;,
  4;144,142,69,71;,
  4;143,145,72,70;,
  4;145,146,73,72;,
  4;147,148,75,74;,
  4;148,144,71,75;,
  4;146,149,76,73;,
  4;149,147,74,76;,
  4;77,77,78,78;,
  4;78,78,79,79;,
  4;79,79,80,80;,
  4;80,80,81,81;,
  4;81,81,82,82;,
  4;82,82,83,83;,
  4;83,83,84,84;,
  4;84,84,77,77;,
  3;150,85,151;,
  3;152,85,150;,
  3;153,85,152;,
  3;154,85,153;,
  3;155,85,154;,
  3;156,85,155;,
  3;157,85,156;,
  3;151,85,157;,
  3;158,86,159;,
  3;159,86,160;,
  3;160,86,161;,
  3;162,163,164;,
  3;164,163,165;,
  3;165,163,166;,
  3;166,163,167;,
  3;168,86,158;;
 }
 MeshTextureCoords {
  229;
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.125000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.625000;,
  0.625000;0.625000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.375000;,
  0.625000;0.375000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.125000;,
  0.625000;0.125000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.875000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.750000;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.375000;0.875000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.875000;,
  0.750000;0.875000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.875000;,
  0.125000;0.875000;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.250000;0.750000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.875000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.750000;,
  0.125000;0.750000;,
  0.375000;0.687500;,
  0.375000;0.311560;,
  0.406250;0.311560;,
  0.406250;0.687500;,
  0.437500;0.311560;,
  0.437500;0.687500;,
  0.468750;0.311560;,
  0.468750;0.687500;,
  0.500000;0.311560;,
  0.500000;0.687500;,
  0.531250;0.311560;,
  0.531250;0.687500;,
  0.562500;0.311560;,
  0.562500;0.687500;,
  0.593750;0.311560;,
  0.593750;0.687500;,
  0.625000;0.311560;,
  0.625000;0.687500;,
  0.500000;1.000000;,
  0.500000;0.850000;,
  0.610485;0.954235;,
  0.389515;0.954235;,
  0.343750;0.843750;,
  0.389515;0.733265;,
  0.500000;0.687500;,
  0.610485;0.733265;,
  0.656250;0.843750;,
  0.610485;0.045765;,
  0.500000;0.162500;,
  0.500000;0.000000;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.500000;0.312500;,
  0.610485;0.266735;,
  0.656250;0.156250;;
 }
}
