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
 -0.02636;16.44582;-7.11324;,
 6.25672;16.44582;-2.30069;,
 6.25672;7.02903;-4.24377;,
 -0.02636;7.02903;-9.05633;,
 -0.02636;16.44582;5.17302;,
 6.25672;16.44582;5.17302;,
 -0.02636;7.02903;9.47085;,
 6.92545;7.02903;6.47115;,
 5.91015;16.44582;6.47115;,
 -0.02636;16.44582;7.76928;,
 -0.02636;7.02903;-9.05633;,
 6.25672;7.02903;-4.24377;,
 7.27203;7.02903;5.17302;,
 -0.02636;7.02903;5.17302;,
 7.20828;7.02903;-4.24377;,
 7.20828;16.44582;-2.30069;,
 5.91015;16.44582;6.47115;,
 6.92545;7.02903;6.47115;,
 -6.97818;7.02903;6.47115;,
 -5.96288;16.44582;6.47115;,
 -7.26101;16.44582;-2.30069;,
 -7.26101;7.02903;-4.24377;,
 -7.32476;7.02903;5.17302;,
 -6.30945;7.02903;-4.24377;,
 -5.96288;16.44582;6.47115;,
 -6.97818;7.02903;6.47115;,
 -6.30945;16.44582;-2.30069;,
 -6.30945;16.44582;5.17302;,
 -6.30945;7.02903;-4.24377;,
 7.27203;7.02903;5.17302;,
 6.25672;16.44582;5.17302;,
 -7.32476;7.02903;5.17302;,
 -6.30945;16.44582;5.17302;,
 -0.92035;21.35975;-6.36321;,
 -0.26517;42.72144;-19.18888;,
 0.21244;42.72144;-19.18887;,
 0.86762;21.35975;-6.36321;,
 -0.26517;43.53882;-17.48991;,
 0.21244;43.53882;-17.48991;,
 -0.92035;23.95511;-0.96869;,
 0.86762;23.95511;-0.96869;,
 -0.92035;21.35975;-6.36321;,
 0.86762;21.35975;-6.36321;,
 0.21244;43.53882;-17.48991;,
 0.86762;23.95511;-0.96869;,
 -0.92035;23.95511;-0.96869;,
 -0.26517;43.53882;-17.48991;,
 -0.02636;23.07644;-6.05699;,
 6.20465;23.54528;-2.43230;,
 7.08909;18.22865;-3.24821;,
 -0.02636;17.68807;-7.33579;,
 -0.02636;25.21358;5.35506;,
 4.13165;25.21358;4.66718;,
 4.13165;25.21358;-0.98445;,
 -0.02636;25.21358;-3.42791;,
 -0.02636;17.35026;8.08303;,
 6.75753;17.75862;6.72915;,
 6.11279;23.14699;6.13030;,
 -0.02636;22.73863;8.01455;,
 -0.02636;17.35026;-6.16820;,
 6.52659;17.35026;-2.20961;,
 5.75349;17.35026;5.37526;,
 -0.02636;17.35026;5.37526;,
 6.11279;23.14699;6.13030;,
 6.75753;17.75862;6.72915;,
 -6.81026;17.75862;6.72915;,
 -6.16552;23.14699;6.13030;,
 -6.25738;23.54528;-2.43230;,
 -7.14182;18.22865;-3.24821;,
 -5.80622;17.35026;5.37526;,
 -6.57932;17.35026;-2.20961;,
 -6.16552;23.14699;6.13030;,
 -6.81026;17.75862;6.72915;,
 -4.18437;25.21358;-0.98445;,
 -4.18437;25.21358;4.66718;,
 6.52659;17.35026;-2.20961;,
 5.75349;17.35026;5.37526;,
 4.13165;25.21358;4.66718;,
 -5.80622;17.35026;5.37526;,
 -6.57932;17.35026;-2.20961;,
 -4.18437;25.21358;4.66718;,
 -0.02636;17.35026;-6.16820;,
 -0.02636;17.73182;-5.40364;,
 5.47377;17.73182;-2.06802;,
 5.47377;16.09732;-2.06802;,
 -0.02636;16.09732;-5.40364;,
 -0.02636;17.73182;5.20098;,
 5.47377;17.73182;5.20098;,
 -0.02636;16.09732;5.20098;,
 5.47377;16.09732;5.20098;,
 -0.02636;16.09732;-5.40364;,
 5.47377;16.09732;-2.06802;,
 5.47377;17.73182;5.20098;,
 5.47377;16.09732;5.20098;,
 -5.52650;16.09732;5.20098;,
 -5.52650;17.73182;5.20098;,
 -5.52650;17.73182;-2.06802;,
 -5.52650;16.09732;-2.06802;,
 -5.52650;16.09732;5.20098;,
 -5.52650;16.09732;-2.06802;,
 -5.52650;17.73182;5.20098;,
 -8.24320;11.66887;-0.15236;,
 -8.24320;13.34406;-0.15236;,
 -6.75402;13.34406;-0.15236;,
 -6.75402;11.66887;-0.15236;,
 -8.24320;15.01924;-0.15236;,
 -6.75402;15.01924;-0.15236;,
 -8.24320;15.01924;1.02533;,
 -6.75402;15.01924;1.02533;,
 -8.24320;15.01924;2.94287;,
 -6.75402;15.01924;2.94287;,
 -8.24320;13.34406;3.19802;,
 -6.75402;13.34406;3.19802;,
 -8.24320;11.66887;3.19802;,
 -6.75402;11.66887;3.19802;,
 -8.24320;11.18193;1.02533;,
 -6.75402;11.18193;1.02533;,
 -8.24320;11.66887;-0.15236;,
 -6.75402;11.66887;-0.15236;,
 -6.71568;11.35596;1.07045;,
 -6.71568;13.32198;1.07045;,
 -6.71568;13.32198;3.04608;,
 -6.71568;11.79874;3.04608;,
 -6.71568;11.79874;-0.00042;,
 -6.71568;13.32198;-0.00042;,
 -6.71568;14.84523;1.07045;,
 -6.71568;14.84523;2.81407;,
 -6.71568;14.84523;-0.00042;,
 -8.28154;11.79874;3.04608;,
 -8.28154;13.32198;3.04608;,
 -8.28154;13.32198;1.07045;,
 -8.28154;11.35596;1.07045;,
 -8.28154;13.32198;-0.00042;,
 -8.28154;11.79874;-0.00042;,
 -8.28154;14.84523;2.81407;,
 -8.28154;14.84523;1.07045;,
 -8.28154;14.84523;-0.00042;,
 -6.75402;11.18193;1.02533;,
 -6.75402;11.66887;3.19802;,
 -6.75402;13.34406;3.19802;,
 -6.75402;15.01924;2.94287;,
 -6.75402;15.01924;1.02533;,
 -8.24320;11.66887;3.19802;,
 -8.24320;11.18193;1.02533;,
 -8.24320;13.34406;3.19802;,
 -8.24320;15.01924;1.02533;,
 -8.24320;15.01924;2.94287;,
 8.19047;11.66887;-0.15236;,
 6.70129;11.66887;-0.15236;,
 6.70129;13.34406;-0.15236;,
 8.19047;13.34406;-0.15236;,
 6.70129;15.01924;-0.15236;,
 8.19047;15.01924;-0.15236;,
 6.70129;15.01924;1.02533;,
 8.19047;15.01924;1.02533;,
 6.70129;15.01924;2.94287;,
 8.19047;15.01924;2.94287;,
 6.70129;13.34406;3.19802;,
 8.19047;13.34406;3.19802;,
 6.70129;11.66887;3.19802;,
 8.19047;11.66887;3.19802;,
 6.70129;11.18193;1.02533;,
 8.19047;11.18193;1.02533;,
 6.70129;11.66887;-0.15236;,
 8.19047;11.66887;-0.15236;,
 6.66296;11.35596;1.07045;,
 6.66296;11.79874;3.04608;,
 6.66296;13.32198;3.04608;,
 6.66296;13.32198;1.07045;,
 6.66296;11.79874;-0.00042;,
 6.66296;13.32198;-0.00042;,
 6.66296;14.84523;2.81407;,
 6.66296;14.84523;1.07045;,
 6.66296;14.84523;-0.00042;,
 8.22881;11.79874;3.04608;,
 8.22881;11.35596;1.07045;,
 8.22881;13.32198;1.07045;,
 8.22881;13.32198;3.04608;,
 8.22881;11.79874;-0.00042;,
 8.22881;13.32198;-0.00042;,
 8.22881;14.84523;1.07045;,
 8.22881;14.84523;2.81407;,
 8.22881;14.84523;-0.00042;,
 6.70129;11.18193;1.02533;,
 6.70129;11.66887;3.19802;,
 6.70129;13.34406;3.19802;,
 6.70129;15.01924;2.94287;,
 6.70129;15.01924;1.02533;,
 8.19047;11.66887;3.19802;,
 8.19047;11.18193;1.02533;,
 8.19047;13.34406;3.19802;,
 8.19047;15.01924;1.02533;,
 8.19047;15.01924;2.94287;,
 11.71662;0.00816;11.71662;,
 6.07971;16.73521;6.54420;,
 0.00000;17.22130;7.56833;,
 0.00000;0.00816;16.56980;,
 -6.01386;16.73521;6.54420;,
 -11.71662;0.00816;11.71662;,
 -10.34240;12.92022;1.41443;,
 -16.56979;0.00816;0.00000;,
 -6.58153;16.60301;-3.02727;,
 -11.71662;0.00816;-11.71662;,
 0.00000;16.57537;-7.34314;,
 0.00000;0.00816;-16.56978;,
 6.30644;16.60301;-3.28782;,
 11.71662;0.00816;-11.71662;,
 10.34240;12.92022;1.41443;,
 16.56979;0.00816;0.00000;,
 6.07971;16.73521;6.54420;,
 11.71662;0.00816;11.71662;,
 0.00000;0.00816;16.56980;,
 0.00000;0.00000;0.00000;,
 11.71662;0.00816;11.71662;,
 -11.71662;0.00816;11.71662;,
 -16.56979;0.00816;0.00000;,
 -11.71662;0.00816;-11.71662;,
 0.00000;0.00816;-16.56978;,
 11.71662;0.00816;-11.71662;,
 16.56979;0.00816;0.00000;,
 6.07971;16.73521;6.54420;,
 0.00000;3.20579;0.00000;,
 0.00000;17.22130;7.56833;,
 -6.01386;16.73521;6.54420;,
 -10.34240;12.92022;1.41443;,
 -6.58153;16.60301;-3.02727;,
 0.00000;16.57537;-7.34314;,
 6.30644;16.60301;-3.28782;,
 10.34240;12.92022;1.41443;;
 
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
  151;
  0.000000;-1.000000;-0.000000;,
  0.316274;0.191712;-0.929095;,
  0.000000;1.000000;0.000000;,
  0.600078;0.161656;-0.783437;,
  0.000000;0.114448;0.993429;,
  0.305150;0.108990;0.946047;,
  0.994992;0.050475;0.086268;,
  -0.994992;0.050475;0.086268;,
  0.000008;-0.514751;-0.857340;,
  0.000004;0.901134;-0.433541;,
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
  0.992058;-0.076696;0.099691;,
  0.994315;-0.106218;-0.007413;,
  0.992491;0.009190;0.121972;,
  1.000000;0.000000;0.000000;,
  0.991839;-0.065461;-0.109406;,
  0.992373;0.000000;-0.123274;,
  0.993122;0.084812;0.080722;,
  0.994127;0.108221;0.000000;,
  0.993940;0.072591;-0.082542;,
  -0.992058;-0.076696;0.099691;,
  -0.994315;-0.106218;-0.007413;,
  -0.992491;0.009190;0.121972;,
  -0.991839;-0.065461;-0.109406;,
  -0.992373;0.000000;-0.123274;,
  -0.994127;0.108221;0.000000;,
  -0.993122;0.084812;0.080722;,
  -0.993940;0.072591;-0.082542;,
  -0.992062;-0.076677;0.099666;,
  -0.994318;-0.106192;-0.007411;,
  -0.992495;0.009188;0.121942;,
  -0.991843;-0.065445;-0.109379;,
  -0.992376;0.000000;-0.123243;,
  -0.993125;0.084790;0.080702;,
  -0.994130;0.108194;0.000000;,
  -0.993943;0.072573;-0.082522;,
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
  -0.354851;-0.932460;0.067824;,
  -0.465308;-0.863326;-0.195339;,
  0.742111;-0.062555;-0.667352;,
  0.000000;-0.911948;-0.410306;,
  0.742111;0.062555;0.667351;,
  -0.742111;0.062555;0.667352;,
  -0.518552;0.000000;-0.855046;,
  0.000000;0.150575;0.988599;,
  0.000000;-0.975794;0.218693;,
  0.000000;-0.924122;-0.382097;,
  0.977273;-0.211470;-0.014759;,
  0.982050;-0.115016;0.149499;,
  0.970072;0.018244;0.242133;,
  0.981595;-0.098056;-0.163881;,
  0.969607;0.000000;-0.244667;,
  0.984447;0.127256;0.121118;,
  0.976576;0.215172;0.000000;,
  0.986274;0.109043;-0.123991;,
  -0.982050;-0.115016;0.149499;,
  -0.977273;-0.211470;-0.014759;,
  -0.970072;0.018244;0.242133;,
  -0.981595;-0.098056;-0.163881;,
  -0.969607;0.000000;-0.244667;,
  -0.976576;0.215172;0.000000;,
  -0.984447;0.127256;0.121118;,
  -0.986274;0.109043;-0.123991;,
  -0.977284;-0.211418;-0.014756;,
  -0.982059;-0.114987;0.149462;,
  -0.970086;0.018239;0.242074;,
  -0.981604;-0.098031;-0.163841;,
  -0.969622;0.000000;-0.244608;,
  -0.984455;0.127223;0.121088;,
  -0.976588;0.215118;0.000000;,
  -0.986281;0.109016;-0.123960;,
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
  0.260743;0.511838;-0.818556;,
  0.403643;0.537533;-0.740358;,
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
  4;78,78,4,4;,
  4;2,2,2,2;,
  4;79,79,80,80;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;1,82,82,1;,
  4;2,2,2,2;,
  4;79,83,83,79;,
  4;81,81,81,81;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;33,28,27,34;,
  4;21,16,14,22;,
  4;23,26,25,24;,
  4;19,12,18,20;,
  4;87,88,89,90;,
  4;29,32,31,30;,
  4;17,11,19,20;,
  4;91,92,23,24;,
  4;13,15,21,22;,
  4;93,93,33,34;,
  4;21,24,25,16;,
  4;18,94,95,20;,
  4;12,96,94,18;,
  4;16,89,88,14;,
  4;97,97,97,97;,
  4;17,98,99,11;,
  4;100,100,100,100;,
  4;13,31,32,15;,
  4;15,91,24,21;,
  4;20,95,98,17;,
  4;19,101,96,12;,
  4;102,87,88,102;,
  4;14,28,33,22;,
  4;11,99,101,19;,
  4;22,33,31,13;,
  4;103,103,30,103;,
  4;39,36,36,39;,
  4;2,2,2,2;,
  4;38,38,38,38;,
  4;0,0,0,0;,
  4;36,36,46,46;,
  4;37,37,35,35;,
  4;0,0,0,0;,
  4;38,38,38,38;,
  4;2,2,2,2;,
  4;35,35,104,104;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;105,41,41,105;,
  4;41,38,38,41;,
  4;106,42,42,106;,
  4;42,107,107,42;,
  4;44,46,45,43;,
  4;47,48,46,44;,
  4;46,50,49,45;,
  4;48,51,50,46;,
  4;52,54,37,53;,
  4;53,37,56,55;,
  4;54,58,57,37;,
  4;37,57,59,56;,
  4;108,44,43,109;,
  4;109,43,45,110;,
  4;111,47,44,108;,
  4;112,48,47,111;,
  4;110,45,49,113;,
  4;113,49,50,114;,
  4;114,50,51,115;,
  4;115,51,48,112;,
  4;116,52,53,117;,
  4;118,54,52,116;,
  4;117,53,55,119;,
  4;119,55,56,120;,
  4;121,57,58,122;,
  4;122,58,54,118;,
  4;120,56,59,123;,
  4;123,59,57,121;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;105,105,41,41;,
  4;41,41,38,38;,
  4;106,106,42,42;,
  4;42,42,107,107;,
  4;61,60,62,37;,
  4;63,61,37,64;,
  4;37,62,65,66;,
  4;64,37,66,67;,
  4;43,44,46,45;,
  4;44,47,48,46;,
  4;45,46,50,49;,
  4;46,48,51,50;,
  4;124,125,60,61;,
  4;125,126,62,60;,
  4;127,124,61,63;,
  4;128,127,63,64;,
  4;126,129,65,62;,
  4;129,130,66,65;,
  4;130,131,67,66;,
  4;131,128,64,67;,
  4;109,108,44,43;,
  4;110,109,43,45;,
  4;108,111,47,44;,
  4;111,112,48,47;,
  4;114,113,49,50;,
  4;113,110,45,49;,
  4;112,115,51,48;,
  4;115,114,50,51;,
  4;68,68,69,69;,
  4;69,69,70,70;,
  4;70,70,71,71;,
  4;71,71,72,72;,
  4;72,72,73,73;,
  4;73,73,74,74;,
  4;74,74,75,75;,
  4;75,75,68,68;,
  3;132,76,133;,
  3;134,76,132;,
  3;135,76,134;,
  3;136,76,135;,
  3;137,76,136;,
  3;138,76,137;,
  3;139,76,138;,
  3;133,76,139;,
  3;140,77,141;,
  3;141,77,142;,
  3;142,77,143;,
  3;144,145,146;,
  3;146,145,147;,
  3;147,145,148;,
  3;148,145,149;,
  3;150,77,140;;
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
  0.610490;0.954240;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.162500;,
  0.500000;0.000000;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;;
 }
}