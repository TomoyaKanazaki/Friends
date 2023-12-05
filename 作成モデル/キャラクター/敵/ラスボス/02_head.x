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
 199;
 10.86723;20.64845;0.00852;,
 10.86723;23.64390;-0.06615;,
 22.32215;23.64390;-0.06615;,
 22.84913;20.64845;0.00852;,
 10.86723;26.63937;-0.16160;,
 10.86723;26.63937;1.97195;,
 20.81645;26.63937;1.97195;,
 20.81645;26.63937;-0.16160;,
 10.86723;23.64390;2.30753;,
 10.86723;20.64845;2.45933;,
 22.84913;20.64845;2.45933;,
 22.32215;23.64390;2.30753;,
 10.86723;14.65755;1.97195;,
 10.86723;14.65755;-0.16160;,
 20.81645;14.65755;-0.16160;,
 20.81645;14.65755;1.97195;,
 10.86723;17.65300;-0.06615;,
 22.32215;17.65300;-0.06615;,
 22.32215;17.65300;2.30753;,
 10.86723;17.65300;2.30753;,
 -10.86723;20.64845;0.00852;,
 -22.84913;20.64845;0.00852;,
 -22.32215;23.64390;-0.06615;,
 -10.86723;23.64390;-0.06615;,
 -10.86723;26.63937;-0.16160;,
 -20.81645;26.63937;-0.16160;,
 -20.81645;26.63937;1.97195;,
 -10.86723;26.63937;1.97195;,
 -10.86723;23.64390;2.30753;,
 -22.32215;23.64390;2.30753;,
 -22.84913;20.64845;2.45933;,
 -10.86723;20.64845;2.45933;,
 -10.86723;14.65755;1.97195;,
 -20.81645;14.65755;1.97195;,
 -20.81645;14.65755;-0.16160;,
 -10.86723;14.65755;-0.16160;,
 -10.86723;17.65300;-0.06615;,
 -22.32215;17.65300;-0.06615;,
 -22.32215;17.65300;2.30753;,
 -10.86723;17.65300;2.30753;,
 0.00000;5.91198;4.63950;,
 0.00000;14.74462;17.07903;,
 -14.72290;14.74462;11.82335;,
 -9.20070;5.91198;1.79515;,
 -17.43013;13.41230;-2.51353;,
 -12.88220;6.09997;-8.27903;,
 -12.13193;13.41230;-16.99023;,
 -11.49068;12.23542;-16.93555;,
 -10.84938;11.05865;-16.88090;,
 -9.32495;7.52823;-16.71695;,
 -8.68648;6.35140;-16.66228;,
 -8.05295;5.41000;-16.61857;,
 -7.54290;4.65677;-16.58362;,
 -6.98815;3.75305;-16.54165;,
 -6.50338;2.90943;-16.50245;,
 -5.71927;1.64413;-16.44370;,
 0.00000;13.41230;-25.99077;,
 0.00000;11.62247;-25.59073;,
 0.00000;22.48622;22.57988;,
 -15.58900;22.48622;15.71305;,
 -20.81750;22.48622;-0.86480;,
 -15.58900;22.48622;-16.59308;,
 0.00000;22.48622;-24.30950;,
 0.00000;31.61800;24.51153;,
 -16.87343;31.61800;17.07903;,
 -22.79930;31.61800;-0.86480;,
 -16.87343;31.61800;-16.50058;,
 0.00000;31.61800;-26.15703;,
 0.00000;26.74630;-25.53208;,
 0.00000;40.74992;22.57988;,
 -15.58900;40.74992;15.71305;,
 -22.04617;40.74992;-0.86480;,
 -15.58900;40.74992;-17.44267;,
 0.00000;36.87013;-26.23665;,
 0.00000;48.03105;19.44247;,
 -13.50287;48.03105;13.49460;,
 -19.09598;48.03105;-0.86480;,
 -13.50287;48.03120;-15.22423;,
 0.00000;48.03120;-21.17210;,
 0.00000;41.21410;-24.89105;,
 0.00000;53.61165;13.05172;,
 -9.25348;53.61165;8.97568;,
 -13.08640;53.61165;-0.86480;,
 -9.25348;53.61165;-10.70528;,
 0.00000;53.61165;-14.78138;,
 0.00000;1.27330;-6.67560;,
 0.00000;-1.27157;-21.51218;,
 -0.95895;-0.78273;-20.66235;,
 0.00000;56.21467;-0.86480;,
 -6.15622;9.12933;-20.43322;,
 -4.79840;7.97125;-21.23687;,
 -7.12480;10.47260;-20.45103;,
 0.00000;10.20055;-25.92635;,
 0.00000;9.52970;-25.38602;,
 0.00000;8.37630;-23.67522;,
 0.00000;7.90762;-24.25163;,
 -4.18980;6.99023;-21.40948;,
 0.00000;6.70232;-24.36362;,
 -3.25453;5.97990;-21.31925;,
 0.00000;5.71428;-23.56205;,
 -2.44142;5.01713;-21.06662;,
 0.00000;3.12025;-22.40353;,
 -1.64200;3.06620;-20.89168;,
 9.20070;5.91198;1.79515;,
 14.72290;14.74462;11.82335;,
 12.88215;6.09997;-8.27903;,
 17.43013;13.41230;-2.51353;,
 12.13193;13.41230;-16.99023;,
 9.32493;7.52823;-16.71695;,
 11.49068;12.23542;-16.93555;,
 10.84938;11.05865;-16.88090;,
 8.68648;6.35140;-16.66228;,
 8.05295;5.41000;-16.61857;,
 7.54290;4.65677;-16.58362;,
 6.98815;3.75305;-16.54165;,
 6.50335;2.90943;-16.50245;,
 5.71927;1.64413;-16.44370;,
 15.58900;22.48622;15.71305;,
 20.81750;22.48622;-0.86480;,
 15.58900;22.48622;-16.59308;,
 16.87340;31.61800;17.07903;,
 22.79930;31.61800;-0.86480;,
 16.87340;31.61800;-16.50058;,
 15.58900;40.74992;15.71305;,
 22.04617;40.74992;-0.86480;,
 15.58900;40.74992;-17.44267;,
 13.50287;48.03105;13.49460;,
 19.09598;48.03105;-0.86480;,
 13.50287;48.03120;-15.22423;,
 9.25348;53.61165;8.97568;,
 13.08640;53.61165;-0.86480;,
 9.25348;53.61165;-10.70528;,
 0.95895;-0.78273;-20.66235;,
 4.79840;7.97125;-21.23687;,
 6.15622;9.12933;-20.43322;,
 7.12480;10.47260;-20.45103;,
 4.18980;6.99023;-21.40948;,
 3.25453;5.97990;-21.31925;,
 2.44142;5.01713;-21.06662;,
 1.64200;3.06620;-20.89168;,
 0.00000;13.37780;-28.83455;,
 0.00000;14.66155;-27.69890;,
 1.51770;13.49617;-25.02208;,
 0.00000;15.92825;-26.72840;,
 0.00000;19.81985;-24.78275;,
 0.00000;17.39585;-25.93260;,
 1.06550;14.06410;-24.72145;,
 0.00000;18.58667;-24.72145;,
 0.00000;12.77525;-24.72145;,
 -1.06550;14.06410;-24.72145;,
 -1.51770;13.49617;-25.02208;,
 0.00000;11.54218;-25.42313;,
 0.00000;11.54218;-25.42313;,
 8.46505;-10.60550;8.78925;,
 7.09745;-3.42070;7.42165;,
 0.00000;-3.42070;10.36153;,
 0.00000;-10.60550;12.29560;,
 -7.09745;-3.42070;7.42165;,
 -8.46505;-10.60550;8.78925;,
 -10.03730;-3.42070;0.32423;,
 -11.97140;-10.60550;0.32423;,
 -7.09745;-3.42070;-6.77320;,
 -8.46505;-10.60550;-8.14085;,
 0.00000;-3.42070;-9.71308;,
 0.00000;-10.60550;-10.76700;,
 7.09745;-3.42070;-6.77320;,
 8.46505;-10.60550;-8.14085;,
 10.03730;-3.42070;0.32423;,
 11.97140;-10.60550;0.32423;,
 6.29415;2.54443;6.61843;,
 0.00000;2.54443;9.22555;,
 -6.29415;2.54443;6.61843;,
 -8.90135;2.54443;0.32423;,
 -6.29415;2.54443;-5.96995;,
 0.00000;2.54443;-9.70625;,
 6.29415;2.54443;-5.96995;,
 8.90135;2.54443;0.32423;,
 5.61447;7.53988;5.93868;,
 0.00000;7.53988;8.26423;,
 -5.61447;7.53988;5.93868;,
 -7.94003;7.53988;0.32423;,
 -5.61447;7.53988;-5.29022;,
 0.00000;7.53988;-8.63933;,
 5.61447;7.53988;-5.29022;,
 7.94003;7.53988;0.32423;,
 5.21015;12.20015;5.53435;,
 0.00000;12.20015;7.69248;,
 -5.21015;12.20015;5.53435;,
 -7.36825;12.20015;0.32423;,
 -5.21015;12.20015;-4.88592;,
 0.00000;12.20015;-7.04402;,
 5.21015;12.20015;-4.88592;,
 7.36825;12.20015;0.32423;,
 0.00000;-10.60550;0.32423;,
 0.00000;12.20015;0.32423;,
 0.00000;36.87013;-26.23665;,
 0.00000;26.74630;-25.53208;,
 8.43672;36.41607;-21.66987;,
 -8.43672;36.41607;-21.66987;;
 
 228;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;3,2,11,10;,
 4;9,8,1,0;,
 4;16,0,3,17;,
 4;17,3,10,18;,
 4;9,19,18,10;,
 4;19,9,0,16;,
 4;5,8,11,6;,
 4;2,7,6,11;,
 4;1,4,7,2;,
 4;8,5,4,1;,
 4;13,16,17,14;,
 4;14,17,18,15;,
 4;19,12,15,18;,
 4;12,19,16,13;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;21,30,29,22;,
 4;31,20,23,28;,
 4;36,37,21,20;,
 4;37,38,30,21;,
 4;31,30,38,39;,
 4;39,36,20,31;,
 4;27,26,29,28;,
 4;22,29,26,25;,
 4;23,22,25,24;,
 4;28,23,24,27;,
 4;35,34,37,36;,
 4;34,33,38,37;,
 4;39,38,33,32;,
 4;32,35,36,39;,
 4;40,41,42,43;,
 4;43,42,44,45;,
 3;46,47,44;,
 3;47,48,44;,
 3;48,49,44;,
 3;49,50,44;,
 3;50,51,44;,
 3;51,52,44;,
 3;52,53,44;,
 3;53,54,44;,
 3;54,55,44;,
 3;44,55,45;,
 4;47,46,56,57;,
 4;41,58,59,42;,
 4;42,59,60,44;,
 4;44,60,61,46;,
 4;46,61,62,56;,
 4;58,63,64,59;,
 4;59,64,65,60;,
 4;60,65,66,61;,
 3;67,68,66;,
 3;68,62,66;,
 3;66,62,61;,
 4;63,69,70,64;,
 4;64,70,71,65;,
 4;65,71,72,66;,
 3;67,66,73;,
 4;69,74,75,70;,
 4;70,75,76,71;,
 4;71,76,77,72;,
 4;72,77,78,79;,
 4;74,80,81,75;,
 4;75,81,82,76;,
 4;76,82,83,77;,
 4;77,83,84,78;,
 3;43,85,40;,
 3;45,85,43;,
 3;55,85,45;,
 4;86,85,55,87;,
 3;80,88,81;,
 3;81,88,82;,
 3;82,88,83;,
 3;83,88,84;,
 4;50,49,89,90;,
 4;91,92,93,89;,
 3;57,92,47;,
 3;92,91,47;,
 3;47,91,48;,
 4;90,94,95,96;,
 4;96,95,97,98;,
 4;98,97,99,100;,
 4;100,99,101,102;,
 4;102,101,86,87;,
 4;89,93,94,90;,
 4;51,50,90,96;,
 4;52,51,96,98;,
 4;49,48,91,89;,
 4;53,52,98,100;,
 4;54,53,100,102;,
 4;55,54,102,87;,
 4;40,103,104,41;,
 4;103,105,106,104;,
 3;106,105,107;,
 3;105,108,107;,
 3;108,109,107;,
 3;109,108,110;,
 3;108,105,111;,
 3;111,105,112;,
 3;112,105,113;,
 3;113,105,114;,
 3;114,105,115;,
 3;115,105,116;,
 4;109,57,56,107;,
 4;41,104,117,58;,
 4;104,106,118,117;,
 4;106,107,119,118;,
 4;107,56,62,119;,
 4;58,117,120,63;,
 4;117,118,121,120;,
 4;118,119,122,121;,
 3;119,62,122;,
 4;63,120,123,69;,
 4;120,121,124,123;,
 4;121,122,125,124;,
 4;69,123,126,74;,
 4;123,124,127,126;,
 4;124,125,128,127;,
 4;125,79,78,128;,
 4;74,126,129,80;,
 4;126,127,130,129;,
 4;127,128,131,130;,
 4;128,78,84,131;,
 3;103,40,85;,
 3;105,103,85;,
 3;116,105,85;,
 4;86,132,116,85;,
 3;80,129,88;,
 3;129,130,88;,
 3;130,131,88;,
 3;131,84,88;,
 4;111,133,134,108;,
 4;135,134,93,92;,
 3;110,135,109;,
 3;109,135,57;,
 3;57,135,92;,
 4;133,136,95,94;,
 4;136,137,97,95;,
 4;137,138,99,97;,
 4;138,139,101,99;,
 4;139,132,86,101;,
 4;134,133,94,93;,
 4;112,136,133,111;,
 4;113,137,136,112;,
 4;108,134,135,110;,
 4;114,138,137,113;,
 4;115,139,138,114;,
 4;116,132,139,115;,
 3;140,141,142;,
 3;141,143,142;,
 3;142,143,144;,
 3;144,143,145;,
 3;146,147,148;,
 3;147,149,148;,
 3;144,145,150;,
 3;145,143,150;,
 3;143,141,150;,
 3;150,141,140;,
 3;151,150,140;,
 3;142,151,140;,
 4;142,146,148,152;,
 4;144,147,146,142;,
 4;152,148,149,150;,
 4;149,147,144,150;,
 4;153,154,155,156;,
 4;156,155,157,158;,
 4;158,157,159,160;,
 4;160,159,161,162;,
 4;162,161,163,164;,
 4;164,163,165,166;,
 4;166,165,167,168;,
 4;168,167,154,153;,
 4;154,169,170,155;,
 4;155,170,171,157;,
 4;157,171,172,159;,
 4;159,172,173,161;,
 4;161,173,174,163;,
 4;163,174,175,165;,
 4;165,175,176,167;,
 4;167,176,169,154;,
 4;169,177,178,170;,
 4;170,178,179,171;,
 4;171,179,180,172;,
 4;172,180,181,173;,
 4;173,181,182,174;,
 4;174,182,183,175;,
 4;175,183,184,176;,
 4;176,184,177,169;,
 4;177,185,186,178;,
 4;178,186,187,179;,
 4;179,187,188,180;,
 4;180,188,189,181;,
 4;181,189,190,182;,
 4;182,190,191,183;,
 4;183,191,192,184;,
 4;184,192,185,177;,
 3;156,193,153;,
 3;158,193,156;,
 3;160,193,158;,
 3;162,193,160;,
 3;164,193,162;,
 3;166,193,164;,
 3;168,193,166;,
 3;153,193,168;,
 3;185,194,186;,
 3;186,194,187;,
 3;187,194,188;,
 3;188,194,189;,
 3;189,194,190;,
 3;190,194,191;,
 3;191,194,192;,
 3;192,194,185;,
 3;195,122,67;,
 3;196,122,62;,
 3;196,67,122;,
 3;197,125,122;,
 3;197,79,125;,
 3;197,195,79;,
 3;197,122,195;,
 3;198,72,79;,
 3;198,66,72;,
 3;198,73,66;,
 3;198,79,73;;
 
 MeshMaterialList {
  1;
  228;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.150000;0.150000;0.150000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\モーションビューワ\\data\\TEXTURE\\tyuuni\\tyuuni_face.png";
   }
  }
 }
 MeshNormals {
  210;
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.081009;0.996713;,
  0.000000;-0.028385;-0.999597;,
  0.000000;0.028385;-0.999597;,
  0.949248;-0.314528;-0.000000;,
  0.000000;-0.081009;0.996713;,
  -0.949248;-0.314528;0.000000;,
  0.000000;-0.873005;0.487711;,
  -0.364989;-0.866512;0.340501;,
  -0.492479;-0.852206;0.176659;,
  -0.777395;-0.253802;-0.575537;,
  0.000000;-0.985606;0.169059;,
  0.000000;-0.682794;0.730611;,
  -0.591058;-0.623774;0.511426;,
  -0.859993;-0.450779;-0.239188;,
  -0.754590;-0.271782;-0.597268;,
  -0.557303;-0.125876;-0.820713;,
  0.000000;-0.376001;0.926619;,
  -0.709204;-0.330125;0.622935;,
  -0.966541;-0.255333;-0.024552;,
  -0.752274;-0.138038;-0.644227;,
  -0.119519;-0.130916;-0.984163;,
  0.000000;-0.000002;1.000000;,
  -0.737481;-0.017429;0.675143;,
  -0.999185;-0.038056;-0.013489;,
  -0.629702;-0.082952;-0.772395;,
  -0.187378;-0.088459;-0.978297;,
  0.000000;0.303271;0.952905;,
  -0.698659;0.281391;0.657795;,
  -0.969036;0.246851;-0.005798;,
  -0.675974;0.212307;-0.705680;,
  -0.000000;0.305916;-0.952059;,
  0.000000;0.592318;0.805704;,
  -0.589369;0.581015;0.561307;,
  -0.821525;0.570173;0.000002;,
  -0.590003;0.588365;-0.552922;,
  -0.000000;0.610794;-0.791789;,
  0.000000;0.902044;0.431644;,
  -0.320637;0.897223;0.303616;,
  -0.451080;0.892484;0.000001;,
  -0.320635;0.897225;-0.303612;,
  0.000000;0.902047;-0.431638;,
  0.000000;-0.975616;0.219486;,
  0.000000;1.000000;0.000000;,
  -0.269016;0.001404;-0.963135;,
  -0.503323;-0.174287;-0.846339;,
  -0.762924;-0.403372;-0.505210;,
  -0.202272;-0.576224;-0.791866;,
  -0.763655;-0.414736;-0.494797;,
  -0.604436;-0.072018;-0.793392;,
  -0.731037;-0.235196;-0.640521;,
  -0.598107;-0.037013;-0.800561;,
  -0.756121;-0.447172;-0.477827;,
  -0.537743;-0.129169;-0.833156;,
  -0.731036;-0.511585;-0.451517;,
  -0.575885;0.049674;-0.816020;,
  -0.709960;-0.533217;-0.460040;,
  -0.552114;-0.393443;-0.735100;,
  -0.726998;-0.477991;-0.492950;,
  -0.572329;-0.446405;-0.687867;,
  -0.754505;-0.425337;-0.499810;,
  -0.659999;-0.236752;-0.712986;,
  -0.601358;-0.252090;-0.758169;,
  -0.570673;-0.435302;-0.696307;,
  -0.616124;-0.205676;-0.760322;,
  -0.560556;-0.448327;-0.696261;,
  -0.629685;-0.299284;-0.716886;,
  -0.579462;-0.435914;-0.688624;,
  -0.648852;-0.278260;-0.708211;,
  -0.332561;-0.929507;0.159437;,
  0.364989;-0.866512;0.340500;,
  0.756947;-0.600150;-0.258556;,
  0.613352;-0.758583;-0.219887;,
  0.591058;-0.623774;0.511426;,
  0.907830;-0.416966;-0.044554;,
  0.781910;-0.265375;-0.564087;,
  0.709204;-0.330124;0.622935;,
  0.966542;-0.255332;-0.024552;,
  0.752274;-0.138037;-0.644228;,
  0.737481;-0.017429;0.675143;,
  0.999185;-0.038056;-0.013489;,
  0.629702;-0.082953;-0.772395;,
  0.698659;0.281391;0.657795;,
  0.969036;0.246850;-0.005798;,
  0.675974;0.212306;-0.705680;,
  0.589369;0.581015;0.561307;,
  0.821525;0.570173;0.000002;,
  0.590003;0.588365;-0.552922;,
  0.320637;0.897223;0.303616;,
  0.451080;0.892484;0.000001;,
  0.320635;0.897225;-0.303612;,
  0.731646;-0.399596;-0.552284;,
  0.470218;-0.295491;-0.831613;,
  0.398207;-0.135376;-0.907251;,
  0.720025;-0.428837;-0.545585;,
  0.692316;-0.489164;-0.530487;,
  0.672475;-0.511567;-0.534862;,
  0.689823;-0.458649;-0.560165;,
  0.716515;-0.406602;-0.566817;,
  0.601359;-0.252088;-0.758168;,
  0.570674;-0.435302;-0.696307;,
  0.616124;-0.205676;-0.760322;,
  0.560556;-0.448327;-0.696261;,
  0.634071;-0.196857;-0.747798;,
  0.579462;-0.435916;-0.688623;,
  0.648852;-0.278261;-0.708210;,
  0.332561;-0.929507;0.159437;,
  -0.783042;-0.547712;-0.294714;,
  0.864787;0.224549;-0.449133;,
  -0.905240;0.109581;-0.410528;,
  0.922827;-0.127797;-0.363398;,
  0.914777;0.075650;-0.396812;,
  0.301577;-0.087564;0.949412;,
  0.000000;-0.187041;0.982352;,
  0.000000;0.057023;0.998373;,
  -0.301577;-0.087564;0.949412;,
  -0.936994;0.157983;-0.311584;,
  0.874217;0.256161;-0.412463;,
  0.879644;0.302496;-0.367045;,
  0.682800;0.259937;0.682800;,
  0.000000;0.259937;0.965626;,
  -0.682800;0.259937;0.682800;,
  -0.965625;0.259939;0.000001;,
  -0.670109;0.231220;-0.705330;,
  0.000000;0.194630;-0.980877;,
  0.670109;0.231220;-0.705330;,
  0.965625;0.259939;0.000001;,
  0.689186;0.223706;0.689187;,
  0.000000;0.223705;0.974657;,
  -0.689186;0.223706;0.689187;,
  -0.974656;0.223707;0.000000;,
  -0.698166;0.185031;-0.691613;,
  0.000000;0.147739;-0.989026;,
  0.698166;0.185031;-0.691613;,
  0.974656;0.223707;0.000000;,
  0.694494;0.188020;0.694497;,
  0.000000;0.188021;0.982165;,
  -0.694494;0.188020;0.694497;,
  -0.982165;0.188020;-0.000000;,
  -0.733626;0.163749;-0.659529;,
  0.000000;0.153558;-0.988140;,
  0.733626;0.163749;-0.659529;,
  0.982165;0.188020;-0.000000;,
  0.698506;0.155489;0.698507;,
  0.000000;0.155489;0.987838;,
  -0.698506;0.155489;0.698507;,
  -0.987838;0.155488;0.000000;,
  -0.733358;0.176985;-0.656402;,
  -0.185630;0.213818;-0.959074;,
  0.733358;0.176985;-0.656402;,
  0.987838;0.155488;0.000000;,
  0.701844;0.121780;0.701844;,
  0.000000;0.121778;0.992557;,
  -0.701844;0.121780;0.701844;,
  -0.992557;0.121780;0.000000;,
  -0.723432;0.165960;-0.670152;,
  0.000000;0.220975;-0.975280;,
  0.723432;0.165960;-0.670152;,
  0.992557;0.121780;0.000000;,
  0.476373;0.071389;-0.876340;,
  -0.476373;0.071390;-0.876340;,
  1.000000;0.000000;0.000000;,
  0.949249;0.314526;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.111331;0.993783;,
  0.893475;0.449112;0.000000;,
  0.000000;-0.031849;-0.999493;,
  0.000000;0.031849;-0.999493;,
  0.893474;-0.449115;-0.000000;,
  0.000000;-0.111332;0.993783;,
  -1.000000;0.000000;0.000000;,
  -0.949249;0.314526;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.893475;0.449112;0.000000;,
  -0.893474;-0.449115;0.000000;,
  -0.724256;0.088700;-0.683802;,
  -0.348674;-0.921852;0.169158;,
  -0.681059;-0.152190;-0.716238;,
  -0.671199;-0.220929;-0.707589;,
  -0.000111;-0.046339;-0.998926;,
  -0.000217;-0.046290;-0.998928;,
  0.601359;0.015063;-0.798837;,
  0.557303;-0.125876;-0.820713;,
  0.521680;0.009365;-0.853090;,
  0.543244;-0.472450;-0.694029;,
  0.603155;-0.152540;-0.782902;,
  0.575885;0.049674;-0.816020;,
  0.537743;-0.129169;-0.833156;,
  0.552114;-0.393443;-0.735100;,
  0.572329;-0.446405;-0.687867;,
  0.659999;-0.236752;-0.712986;,
  0.671200;-0.220926;-0.707589;,
  0.681059;-0.152190;-0.716238;,
  -0.962875;0.115695;-0.243897;,
  -0.943609;0.179601;-0.278112;,
  -0.879644;0.302496;-0.367045;,
  -0.922827;-0.127797;-0.363398;,
  0.783042;-0.547712;-0.294714;,
  0.445366;-0.129314;0.885961;,
  0.000000;-0.378787;0.925484;,
  0.521493;0.105476;0.846711;,
  -0.445366;-0.129314;0.885961;,
  -0.521493;0.105476;0.846711;,
  0.502830;0.182016;-0.845004;,
  0.488196;0.125184;-0.863709;,
  0.496658;-0.013157;-0.867846;,
  0.503324;-0.174287;-0.846339;;
  228;
  4;2,5,5,2;,
  4;1,1,1,1;,
  4;4,3,3,4;,
  4;0,0,0,0;,
  4;164,165,165,164;,
  4;166,166,166,166;,
  4;6,2,2,6;,
  4;7,164,164,7;,
  4;3,8,8,3;,
  4;166,166,166,166;,
  4;167,4,4,167;,
  4;165,168,168,165;,
  4;5,169,169,5;,
  4;166,166,166,166;,
  4;170,6,6,170;,
  4;171,7,7,171;,
  4;8,172,172,8;,
  4;166,166,166,166;,
  4;2,2,5,5;,
  4;1,1,1,1;,
  4;4,4,3,3;,
  4;0,0,0,0;,
  4;173,173,174,174;,
  4;175,175,175,175;,
  4;6,6,2,2;,
  4;9,9,173,173;,
  4;3,3,8,8;,
  4;175,175,175,175;,
  4;167,167,4,4;,
  4;174,174,176,176;,
  4;5,5,169,169;,
  4;175,175,175,175;,
  4;170,170,6,6;,
  4;177,177,9,9;,
  4;8,8,172,172;,
  4;175,175,175,175;,
  4;10,15,16,11;,
  4;11,16,17,12;,
  3;18,53,17;,
  3;53,51,17;,
  3;51,49,17;,
  3;49,55,17;,
  3;55,57,17;,
  3;57,59,17;,
  3;59,61,17;,
  3;61,63,17;,
  3;63,13,17;,
  3;17,13,178;,
  4;53,18,19,54;,
  4;15,20,21,16;,
  4;16,21,22,17;,
  4;17,22,23,18;,
  4;18,23,24,19;,
  4;20,25,26,21;,
  4;21,26,27,22;,
  4;22,27,28,23;,
  3;29,48,28;,
  3;48,24,28;,
  3;28,24,23;,
  4;25,30,31,26;,
  4;26,31,32,27;,
  4;27,32,33,28;,
  3;29,28,47;,
  4;30,35,36,31;,
  4;31,36,37,32;,
  4;32,37,38,33;,
  4;33,38,39,34;,
  4;35,40,41,36;,
  4;36,41,42,37;,
  4;37,42,43,38;,
  4;38,43,44,39;,
  3;11,45,10;,
  3;12,45,11;,
  3;179,45,12;,
  4;14,45,179,72;,
  3;40,46,41;,
  3;41,46,42;,
  3;42,46,43;,
  3;43,46,44;,
  4;55,49,66,65;,
  4;69,52,50,66;,
  3;54,52,53;,
  3;52,69,53;,
  3;53,69,51;,
  4;65,56,58,67;,
  4;67,58,60,68;,
  4;68,60,62,70;,
  4;70,62,64,71;,
  4;71,64,180,181;,
  4;66,50,56,65;,
  4;57,55,65,67;,
  4;59,57,67,68;,
  4;49,51,69,66;,
  4;61,59,68,70;,
  4;63,61,70,71;,
  4;13,63,71,181;,
  4;10,73,76,15;,
  4;73,74,77,76;,
  3;77,74,78;,
  3;74,94,78;,
  3;182,96,183;,
  3;96,182,95;,
  3;94,74,97;,
  3;97,74,98;,
  3;98,74,99;,
  3;99,74,100;,
  3;100,74,101;,
  3;101,74,75;,
  4;96,184,185,78;,
  4;15,76,79,20;,
  4;76,77,80,79;,
  4;77,78,81,80;,
  4;78,185,186,81;,
  4;20,79,82,25;,
  4;79,80,83,82;,
  4;80,81,84,83;,
  3;81,24,84;,
  4;25,82,85,30;,
  4;82,83,86,85;,
  4;83,84,87,86;,
  4;30,85,88,35;,
  4;85,86,89,88;,
  4;86,87,90,89;,
  4;87,34,39,90;,
  4;35,88,91,40;,
  4;88,89,92,91;,
  4;89,90,93,92;,
  4;90,39,44,93;,
  3;73,10,45;,
  3;74,73,45;,
  3;75,74,45;,
  4;14,109,75,45;,
  3;40,91,46;,
  3;91,92,46;,
  3;92,93,46;,
  3;93,44,46;,
  4;97,102,103,94;,
  4;106,103,187,188;,
  3;95,106,96;,
  3;96,106,184;,
  3;184,106,188;,
  4;102,104,189,190;,
  4;104,105,191,189;,
  4;105,107,192,191;,
  4;107,108,193,192;,
  4;108,194,195,193;,
  4;103,102,190,50;,
  4;98,104,102,97;,
  4;99,105,104,98;,
  4;94,103,106,95;,
  4;100,107,105,99;,
  4;101,108,107,100;,
  4;75,194,108,101;,
  3;113,121,114;,
  3;121,120,114;,
  3;114,120,111;,
  3;196,197,119;,
  3;115,117,116;,
  3;117,118,116;,
  3;196,119,112;,
  3;119,197,112;,
  3;197,198,112;,
  3;112,198,199;,
  3;110,112,199;,
  3;114,200,113;,
  4;201,115,116,202;,
  4;203,117,115,201;,
  4;202,116,118,204;,
  4;118,117,205,204;,
  4;122,130,131,123;,
  4;123,131,132,124;,
  4;124,132,133,125;,
  4;125,133,134,126;,
  4;126,134,135,127;,
  4;127,135,136,128;,
  4;128,136,137,129;,
  4;129,137,130,122;,
  4;130,138,139,131;,
  4;131,139,140,132;,
  4;132,140,141,133;,
  4;133,141,142,134;,
  4;134,142,143,135;,
  4;135,143,144,136;,
  4;136,144,145,137;,
  4;137,145,138,130;,
  4;138,146,147,139;,
  4;139,147,148,140;,
  4;140,148,149,141;,
  4;141,149,150,142;,
  4;142,150,151,143;,
  4;143,206,152,144;,
  4;144,152,153,145;,
  4;145,153,146,138;,
  4;146,154,155,147;,
  4;147,155,156,148;,
  4;148,156,157,149;,
  4;149,157,158,150;,
  4;150,158,159,151;,
  4;151,159,160,152;,
  4;152,160,161,153;,
  4;153,161,154,146;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;207,84,208;,
  3;209,84,24;,
  3;209,29,84;,
  3;162,87,84;,
  3;162,34,87;,
  3;162,207,34;,
  3;162,84,47;,
  3;163,33,34;,
  3;163,28,33;,
  3;163,47,28;,
  3;163,34,47;;
 }
 MeshTextureCoords {
  199;
  0.910590;0.053340;,
  0.910590;0.035310;,
  0.979560;0.035310;,
  0.982730;0.053340;,
  0.910590;0.017270;,
  0.910590;0.017270;,
  0.970490;0.017270;,
  0.970490;0.017270;,
  0.910590;0.035310;,
  0.910590;0.053340;,
  0.982730;0.053340;,
  0.979560;0.035310;,
  0.910590;0.089410;,
  0.910590;0.089410;,
  0.970490;0.089410;,
  0.970490;0.089410;,
  0.910590;0.071370;,
  0.979560;0.071370;,
  0.979560;0.071370;,
  0.910590;0.071370;,
  0.910590;0.053340;,
  0.982730;0.053340;,
  0.979560;0.035310;,
  0.910590;0.035310;,
  0.910590;0.017270;,
  0.970490;0.017270;,
  0.970490;0.017270;,
  0.910590;0.017270;,
  0.910590;0.035310;,
  0.979560;0.035310;,
  0.982730;0.053340;,
  0.910590;0.053340;,
  0.910590;0.089410;,
  0.970490;0.089410;,
  0.970490;0.089410;,
  0.910590;0.089410;,
  0.910590;0.071370;,
  0.979560;0.071370;,
  0.979560;0.071370;,
  0.910590;0.071370;,
  0.500000;0.861740;,
  0.500000;0.724010;,
  0.270430;0.724010;,
  0.356530;0.861740;,
  0.222000;0.744790;,
  0.292160;0.858810;,
  0.310830;0.744790;,
  0.320830;0.763140;,
  0.330830;0.781480;,
  0.354600;0.836530;,
  0.364550;0.854880;,
  0.374430;0.869570;,
  0.382380;0.881310;,
  0.391030;0.895400;,
  0.398590;0.908560;,
  0.410820;0.928290;,
  0.500000;0.744790;,
  0.500000;0.772690;,
  0.500000;0.603290;,
  0.256920;0.603290;,
  0.175390;0.603290;,
  0.256920;0.603290;,
  0.500000;0.603290;,
  0.500000;0.460900;,
  0.236890;0.460900;,
  0.144490;0.460900;,
  0.236890;0.460900;,
  0.500000;0.460900;,
  0.500000;0.536870;,
  0.500000;0.318510;,
  0.256920;0.318510;,
  0.156230;0.318510;,
  0.256920;0.318510;,
  0.500000;0.379010;,
  0.500000;0.204980;,
  0.289450;0.204980;,
  0.202240;0.204980;,
  0.289450;0.204970;,
  0.500000;0.204970;,
  0.500000;0.311270;,
  0.500000;0.117960;,
  0.355710;0.117960;,
  0.295940;0.117960;,
  0.355710;0.117960;,
  0.500000;0.117960;,
  0.500000;0.934070;,
  0.500000;0.973750;,
  0.485050;0.966130;,
  0.500000;0.077370;,
  0.404010;0.811570;,
  0.425180;0.829630;,
  0.446360;0.790620;,
  0.500000;0.794870;,
  0.500000;0.805330;,
  0.500000;0.823310;,
  0.500000;0.830620;,
  0.434670;0.844920;,
  0.500000;0.849410;,
  0.449250;0.860680;,
  0.500000;0.864820;,
  0.461930;0.875690;,
  0.500000;0.905270;,
  0.474400;0.906110;,
  0.643470;0.861740;,
  0.729570;0.724010;,
  0.707840;0.858810;,
  0.778000;0.744790;,
  0.689170;0.744790;,
  0.645400;0.836530;,
  0.679170;0.763140;,
  0.669170;0.781480;,
  0.635450;0.854880;,
  0.625570;0.869570;,
  0.617620;0.881310;,
  0.608970;0.895400;,
  0.601410;0.908560;,
  0.589180;0.928290;,
  0.743080;0.603290;,
  0.824610;0.603290;,
  0.743080;0.603290;,
  0.763110;0.460900;,
  0.855510;0.460900;,
  0.763110;0.460900;,
  0.743080;0.318510;,
  0.843770;0.318510;,
  0.743080;0.318510;,
  0.710550;0.204980;,
  0.797760;0.204980;,
  0.710550;0.204970;,
  0.644290;0.117960;,
  0.704060;0.117960;,
  0.644290;0.117960;,
  0.514950;0.966130;,
  0.574820;0.829630;,
  0.595990;0.811570;,
  0.553640;0.790620;,
  0.565330;0.844920;,
  0.550750;0.860680;,
  0.538070;0.875690;,
  0.525600;0.906110;,
  0.500000;0.745320;,
  0.500000;0.725300;,
  0.523670;0.743480;,
  0.500000;0.705550;,
  0.500000;0.644870;,
  0.500000;0.682670;,
  0.516610;0.734620;,
  0.500000;0.664100;,
  0.500000;0.754720;,
  0.483390;0.734620;,
  0.476330;0.743480;,
  0.500000;0.773940;,
  0.500000;0.773950;,
  0.961060;0.172260;,
  0.951740;0.123270;,
  0.903340;0.123270;,
  0.903340;0.172260;,
  0.854940;0.123270;,
  0.845620;0.172260;,
  0.834900;0.123270;,
  0.821710;0.172260;,
  0.854940;0.123270;,
  0.845620;0.172260;,
  0.903340;0.123270;,
  0.903340;0.172260;,
  0.951740;0.123270;,
  0.961060;0.172260;,
  0.971780;0.123270;,
  0.984970;0.172260;,
  0.946260;0.082590;,
  0.903340;0.082590;,
  0.860420;0.082590;,
  0.842640;0.082590;,
  0.860420;0.082590;,
  0.903340;0.082590;,
  0.946260;0.082590;,
  0.964040;0.082590;,
  0.941620;0.048530;,
  0.903340;0.048530;,
  0.865060;0.048530;,
  0.849200;0.048530;,
  0.865060;0.048530;,
  0.903340;0.048530;,
  0.941620;0.048530;,
  0.957480;0.048530;,
  0.938870;0.016750;,
  0.903340;0.016750;,
  0.867810;0.016750;,
  0.853100;0.016750;,
  0.867810;0.016750;,
  0.903340;0.016750;,
  0.938870;0.016750;,
  0.953580;0.016750;,
  0.903340;0.172260;,
  0.903340;0.016750;,
  0.500000;0.386090;,
  0.500000;0.532100;,
  0.631550;0.386090;,
  0.368450;0.386090;;
 }
}
