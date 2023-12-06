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
 152;
 15.72453;4.31202;-25.50402;,
 14.34116;5.95116;-26.51731;,
 25.36209;8.41656;-26.51731;,
 24.55107;7.87159;-24.89249;,
 53.10692;71.76098;-0.10396;,
 39.82201;50.46570;-18.85218;,
 38.22153;50.73902;-0.10396;,
 16.19846;5.67989;23.75217;,
 16.95761;3.45192;21.47340;,
 25.07214;7.18048;21.47340;,
 25.66572;9.78512;23.75217;,
 53.86608;67.77233;-0.10396;,
 40.33489;45.55042;18.64427;,
 40.45803;46.01376;-0.10396;,
 39.57573;49.53915;18.64427;,
 16.25692;19.07772;-18.93145;,
 16.64993;19.90269;17.92923;,
 16.74925;21.63082;-18.85218;,
 16.62617;23.72066;-0.10396;,
 16.50303;21.36330;18.64427;,
 15.96004;18.66764;-22.26471;,
 26.92934;23.08865;-22.26471;,
 40.58117;46.47720;-18.85218;,
 26.28494;24.97257;-24.13916;,
 15.97193;19.61205;-24.13916;,
 16.48787;21.43856;21.46201;,
 27.41318;26.35288;22.17702;,
 27.46349;22.37648;20.93501;,
 16.32381;19.17645;20.90312;,
 3.03621;0.24235;-31.83474;,
 1.30539;2.29305;-33.10252;,
 15.09424;5.37762;-33.10252;,
 14.07955;4.69570;-31.06962;,
 38.57883;68.88012;-0.05547;,
 29.79557;51.92108;-23.51229;,
 28.79436;52.09202;-11.78388;,
 27.79316;52.26299;-0.05547;,
 3.62913;1.95362;29.79211;,
 4.57901;-0.83382;26.94103;,
 14.73145;3.83106;26.94103;,
 15.47407;7.08996;29.79211;,
 39.52866;63.88981;-0.05547;,
 30.43728;45.77145;23.40136;,
 30.59135;46.35117;-0.05547;,
 29.48742;50.76176;23.40136;,
 3.70235;18.71639;-23.61148;,
 4.19401;19.74842;22.50675;,
 4.31835;21.91082;-23.51229;,
 4.24129;23.21812;-11.78388;,
 4.16422;24.52541;-0.05547;,
 4.08722;23.05073;11.67295;,
 4.01024;21.57604;23.40136;,
 3.33088;18.20320;-27.78188;,
 17.05509;23.73486;-27.78188;,
 30.74539;46.93081;-23.51229;,
 16.24886;26.09150;-30.12710;,
 3.34572;19.38488;-30.12710;,
 3.99128;21.67011;26.92678;,
 17.66048;27.81872;27.82137;,
 17.72343;22.84359;26.26742;,
 3.78597;18.83980;26.22751;,
 4.31835;21.91082;-23.51229;,
 4.24129;23.21812;-11.78388;,
 28.79436;52.09202;-11.78388;,
 29.79557;51.92108;-23.51229;,
 28.64029;51.51237;11.67295;,
 44.43638;16.46702;-19.48468;,
 57.60952;15.53581;-15.37872;,
 57.60952;3.54160;-15.37872;,
 45.11894;2.59480;-25.16722;,
 -3.94369;0.00000;0.00000;,
 -3.90419;10.48588;-0.34397;,
 -3.90419;10.48588;-13.10144;,
 -3.94369;0.00000;-13.10144;,
 31.41537;-14.40002;23.52674;,
 44.06258;-11.52843;18.87764;,
 44.06746;2.17602;22.05856;,
 31.41541;0.95432;22.47911;,
 58.86909;-9.94053;12.70348;,
 58.86909;-9.94053;-14.18441;,
 58.86909;3.54160;12.70348;,
 58.86909;17.02374;12.70348;,
 58.86909;17.02374;-14.18441;,
 57.60952;18.22151;-12.70065;,
 31.41537;18.42266;-18.63124;,
 31.41537;18.42266;17.15030;,
 57.60952;18.22151;11.21972;,
 57.60952;-11.13819;11.21972;,
 31.41537;-17.08565;17.15030;,
 31.41537;-17.08565;-18.63124;,
 57.60952;-11.13819;-12.70065;,
 57.60952;-8.45257;-15.37872;,
 44.14719;17.49329;-18.63452;,
 29.42528;17.96284;-23.08463;,
 31.41537;17.38743;-23.54320;,
 31.41537;1.65455;-28.77997;,
 29.42528;1.43246;-28.25350;,
 44.49879;-11.42941;-21.46098;,
 44.14719;-13.28320;-20.62819;,
 29.42528;-16.62579;23.06816;,
 29.42528;0.66853;21.98373;,
 29.42528;17.96284;20.89930;,
 31.41537;17.38743;21.35787;,
 44.07364;16.49265;17.75280;,
 44.14719;17.49329;16.80139;,
 57.60952;3.48373;13.89779;,
 57.60952;-8.45257;13.89779;,
 44.14719;-13.28320;17.88582;,
 29.42528;-16.62579;-27.07197;,
 21.42693;17.19791;-23.08463;,
 21.39662;0.66811;-27.42251;,
 13.42857;16.43307;-23.08463;,
 13.42857;16.43307;20.89930;,
 13.30400;-16.62579;23.06816;,
 13.30400;-16.62579;-27.07197;,
 21.36465;-16.62579;-27.07197;,
 13.30400;-16.62579;-33.24788;,
 3.88144;-16.55914;-33.24788;,
 4.00599;16.49971;-28.17852;,
 13.42857;16.43307;-28.17852;,
 4.00599;16.49971;19.36980;,
 4.00599;16.49971;-0.74047;,
 4.00599;16.49971;-20.85074;,
 13.42857;16.43307;26.69760;,
 4.00599;16.49971;26.69760;,
 3.88144;-16.55914;27.00343;,
 13.30400;-16.62579;27.00343;,
 3.88144;-16.55914;-20.85074;,
 3.88144;-16.55914;0.34397;,
 3.88144;-16.55914;21.53868;,
 13.36632;-0.09636;-25.07830;,
 3.94371;-0.02972;-20.85074;,
 3.94371;-0.02972;20.45424;,
 31.41537;-14.40002;-27.53054;,
 57.60952;15.53581;13.89779;,
 -3.94369;0.00000;13.10143;,
 -3.90419;10.48588;12.41350;,
 -3.98319;-10.48588;0.34397;,
 -3.98319;-10.48588;13.78937;,
 -3.98319;-10.48588;-13.10144;,
 0.00000;-0.01484;-16.97609;,
 0.05089;13.49277;-16.97609;,
 0.05089;13.49277;-0.54222;,
 0.05089;13.49277;15.89165;,
 0.00000;-0.01484;16.77784;,
 -0.05089;-13.52253;17.66402;,
 -0.05089;-13.52253;0.34397;,
 -0.05089;-13.52253;-16.97609;,
 4.08722;23.05073;11.67295;,
 4.01024;21.57604;23.40136;,
 29.48742;50.76176;23.40136;,
 28.64029;51.51237;11.67295;;
 
 169;
 4;0,1,2,3;,
 3;4,5,6;,
 4;7,8,9,10;,
 3;11,12,13;,
 4;4,14,12,11;,
 3;15,16,17;,
 3;17,16,18;,
 3;18,16,19;,
 4;15,20,21,22;,
 4;22,21,23,5;,
 4;5,23,24,17;,
 4;17,24,20,15;,
 4;19,25,26,14;,
 4;14,26,27,12;,
 4;12,27,28,16;,
 4;16,28,25,19;,
 4;20,0,3,21;,
 4;21,3,2,23;,
 4;23,2,1,24;,
 4;24,1,0,20;,
 4;25,7,10,26;,
 4;26,10,9,27;,
 4;27,9,8,28;,
 4;28,8,7,25;,
 4;22,5,4,11;,
 4;17,18,6,5;,
 3;16,15,12;,
 3;15,13,12;,
 3;13,15,22;,
 3;14,4,6;,
 3;22,11,13;,
 4;18,19,14,6;,
 4;29,30,31,32;,
 4;33,34,35,36;,
 4;37,38,39,40;,
 3;41,42,43;,
 4;33,44,42,41;,
 3;45,46,47;,
 3;47,46,48;,
 3;48,46,49;,
 3;49,46,50;,
 3;50,46,51;,
 4;45,52,53,54;,
 4;54,53,55,34;,
 4;34,55,56,47;,
 4;47,56,52,45;,
 4;51,57,58,44;,
 4;44,58,59,42;,
 4;42,59,60,46;,
 4;46,60,57,51;,
 4;52,29,32,53;,
 4;53,32,31,55;,
 4;55,31,30,56;,
 4;56,30,29,52;,
 4;57,37,40,58;,
 4;58,40,39,59;,
 4;59,39,38,60;,
 4;60,38,37,57;,
 4;54,34,33,41;,
 4;61,62,63,64;,
 3;46,45,42;,
 3;42,45,43;,
 3;43,45,54;,
 4;44,33,36,65;,
 3;54,41,43;,
 4;49,50,65,36;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 3;78,79,80;,
 3;80,79,81;,
 3;81,79,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 3;79,91,82;,
 3;82,68,67;,
 3;68,82,91;,
 4;82,67,66,92;,
 4;93,94,95,96;,
 4;97,91,79,98;,
 4;99,74,77,100;,
 4;101,102,103,104;,
 4;105,106,78,80;,
 4;75,74,99,107;,
 4;82,83,86,81;,
 3;101,104,85;,
 3;85,104,86;,
 3;86,104,81;,
 4;101,85,84,93;,
 3;93,84,92;,
 3;84,83,92;,
 3;92,83,82;,
 4;78,87,90,79;,
 3;108,98,89;,
 3;89,98,90;,
 3;90,98,79;,
 4;108,89,88,99;,
 3;99,88,107;,
 3;88,87,107;,
 3;107,87,78;,
 4;109,93,96,110;,
 3;111,112,109;,
 3;112,101,109;,
 3;109,101,93;,
 3;112,113,101;,
 3;113,100,101;,
 3;100,113,99;,
 3;114,115,113;,
 3;113,115,99;,
 3;99,115,108;,
 4;116,117,118,119;,
 3;120,112,121;,
 3;121,112,122;,
 3;122,112,111;,
 4;123,124,125,126;,
 3;127,114,128;,
 3;128,114,129;,
 3;129,114,113;,
 3;111,130,119;,
 3;130,114,119;,
 3;119,114,116;,
 4;111,119,118,122;,
 3;117,127,118;,
 3;118,131,122;,
 3;131,118,127;,
 4;127,117,116,114;,
 4;112,123,126,113;,
 4;113,126,125,129;,
 3;120,132,124;,
 3;132,129,124;,
 3;124,129,125;,
 4;120,124,123,112;,
 4;108,115,110,96;,
 4;95,133,108,96;,
 4;91,97,69,68;,
 4;66,94,93,92;,
 4;95,94,66,69;,
 4;97,133,95,69;,
 4;108,133,97,98;,
 4;130,111,109,110;,
 4;115,114,130,110;,
 4;77,102,101,100;,
 4;103,102,77,76;,
 4;81,134,105,80;,
 4;103,134,81,104;,
 4;105,134,103,76;,
 4;75,106,105,76;,
 4;78,106,75,107;,
 4;135,136,71,70;,
 4;137,138,135,70;,
 4;139,137,70,73;,
 4;140,73,72,141;,
 4;141,72,71,142;,
 4;142,71,136,143;,
 4;143,136,135,144;,
 4;144,135,138,145;,
 4;145,138,137,146;,
 4;147,139,73,140;,
 4;146,137,139,147;,
 4;48,49,36,35;,
 4;148,149,150,151;,
 4;131,140,141,122;,
 4;122,141,142,121;,
 4;121,142,143,120;,
 4;120,143,144,132;,
 4;132,144,145,129;,
 4;129,145,146,128;,
 4;128,146,147,127;,
 4;127,147,140,131;;
 
 MeshMaterialList {
  1;
  169;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "union_arm_UV_Green.jpg";
   }
  }
 }
 MeshNormals {
  189;
  -0.982155;0.183966;0.039082;,
  0.716634;-0.674164;0.178713;,
  -0.926982;0.358155;-0.111487;,
  -0.727548;0.646800;-0.228742;,
  -0.980709;0.195468;0.001345;,
  0.575586;0.017599;0.817552;,
  -0.999548;0.022582;-0.019858;,
  0.819026;-0.434568;0.374630;,
  0.264596;-0.506381;0.820712;,
  0.875379;-0.152970;-0.458597;,
  -0.944548;0.328143;-0.012271;,
  -0.322159;0.481933;0.814834;,
  0.401293;-0.102615;0.910183;,
  0.192093;-0.399104;-0.896558;,
  0.239228;-0.744124;-0.623739;,
  0.113794;-0.294795;0.948761;,
  0.290246;-0.650441;0.701915;,
  -0.816087;0.577861;0.008852;,
  0.906227;-0.341392;0.249407;,
  -0.798011;0.602602;0.006969;,
  0.802583;-0.596465;-0.009471;,
  -0.952559;0.304336;-0.003150;,
  -0.982156;0.183962;0.039086;,
  0.724733;-0.666672;0.174100;,
  -0.924121;0.366125;-0.109327;,
  -0.728247;0.647120;-0.225592;,
  -0.978554;0.205982;0.001933;,
  0.694149;0.037781;0.718839;,
  -0.999848;-0.004337;-0.016886;,
  0.851209;-0.418784;0.316327;,
  0.265350;-0.515120;0.815010;,
  0.885279;-0.144126;-0.442165;,
  -0.943195;0.332148;-0.007769;,
  -0.323302;0.489501;0.809855;,
  0.814607;-0.121041;0.567244;,
  0.192295;-0.405064;-0.893838;,
  0.239223;-0.744118;-0.623748;,
  0.113792;-0.294792;0.948762;,
  0.290244;-0.650437;0.701918;,
  -0.838774;0.544422;0.007884;,
  0.986965;-0.160930;0.001354;,
  -0.801279;0.598253;0.006686;,
  0.815168;-0.579156;-0.008959;,
  -0.947978;0.318320;-0.002965;,
  0.884631;-0.332147;-0.327271;,
  0.718448;0.361937;-0.593998;,
  0.137946;-0.960264;-0.242620;,
  -0.022881;0.483706;-0.874932;,
  0.044281;-0.124631;0.991215;,
  -0.028235;0.987302;0.156328;,
  0.744412;-0.474166;0.470125;,
  0.877111;0.312128;0.365039;,
  0.602716;-0.126347;-0.787890;,
  0.489653;0.255840;-0.833538;,
  0.097028;0.507633;-0.856093;,
  0.212910;-0.257406;-0.942556;,
  0.114541;-0.175862;0.977728;,
  0.048105;0.373561;0.926358;,
  0.464556;0.243910;0.851291;,
  0.522581;-0.172577;0.834941;,
  0.254266;0.940709;0.224532;,
  0.254707;0.943254;-0.213066;,
  -0.016148;0.992645;0.119982;,
  -0.019130;0.994383;-0.104097;,
  0.392223;-0.904824;0.165696;,
  0.395462;-0.907000;-0.144779;,
  0.133219;-0.988243;-0.075021;,
  0.137613;-0.985103;0.103123;,
  -0.005659;-0.999984;0.000000;,
  -0.027047;0.999634;0.000000;,
  -0.027048;0.999634;-0.000000;,
  -0.002088;0.063551;0.997976;,
  -0.218603;-0.975814;0.000000;,
  -0.152058;0.988372;0.000000;,
  -0.206828;0.978377;0.000000;,
  -0.164529;-0.986372;0.000000;,
  0.001072;0.151568;-0.988446;,
  0.000065;0.009250;0.999957;,
  0.999993;-0.003767;-0.000007;,
  -0.134944;0.117991;-0.983803;,
  0.054969;0.108268;-0.992601;,
  0.598321;0.012289;-0.801163;,
  0.169507;0.861952;-0.477814;,
  0.310350;0.484689;-0.817777;,
  0.411153;0.057922;-0.909724;,
  0.454689;-0.291847;-0.841477;,
  0.386574;-0.784636;-0.484671;,
  -0.117311;0.231654;-0.965699;,
  -0.106814;0.118727;-0.987165;,
  0.000000;-1.000000;-0.000000;,
  -0.125335;0.063428;0.990085;,
  -0.037103;0.056220;0.997729;,
  0.562209;0.005732;0.826975;,
  0.918711;0.000000;0.394932;,
  0.162599;0.854912;0.492634;,
  0.262801;0.436215;0.860611;,
  0.301827;0.029160;0.952917;,
  0.365281;-0.270622;0.890693;,
  0.355998;-0.775394;0.521564;,
  -0.315975;0.948767;0.000000;,
  -0.326238;-0.945288;0.000000;,
  -0.916709;0.029595;0.398458;,
  -0.922173;0.003474;-0.386762;,
  -0.999993;0.003767;0.000000;,
  -0.922174;0.003474;-0.386760;,
  -0.906555;0.315469;-0.280425;,
  -0.895045;0.445976;0.000000;,
  -0.916710;0.029594;0.398456;,
  -0.897850;0.333958;0.286944;,
  -0.898382;-0.439216;0.000000;,
  -0.910956;-0.292990;0.290372;,
  -0.908907;-0.308627;-0.280424;,
  -0.786576;0.612677;-0.076972;,
  -0.942032;0.332815;-0.042541;,
  -0.782867;0.615703;0.089607;,
  -0.951862;0.304246;0.037323;,
  -0.700827;0.002640;-0.713327;,
  -0.700827;0.002640;-0.713327;,
  -0.605217;0.796061;0.000000;,
  -0.680912;0.050499;0.730622;,
  -0.680912;0.050498;0.730622;,
  -0.611198;-0.791478;0.000000;,
  -0.700827;0.002640;-0.713326;,
  0.719136;0.136872;0.681255;,
  0.692244;-0.709369;0.132647;,
  0.644141;-0.007675;-0.764868;,
  -0.320036;0.464548;-0.825695;,
  -0.966101;0.080605;0.245258;,
  -0.488387;0.736259;0.468402;,
  -0.712476;0.665379;0.222821;,
  0.335891;-0.692464;-0.638491;,
  0.578502;-0.740940;-0.341092;,
  -0.997776;0.005469;-0.066437;,
  0.047111;-0.200686;0.978522;,
  0.993104;-0.114006;0.027340;,
  -0.057616;0.160967;-0.985277;,
  -0.912370;-0.020576;0.408848;,
  0.987704;-0.118107;0.102424;,
  0.014998;-0.036565;-0.999219;,
  -0.997566;-0.005411;-0.069521;,
  0.727113;0.138394;-0.672424;,
  0.982326;0.186972;0.008759;,
  0.668402;-0.732754;0.127710;,
  0.754999;0.013738;-0.655582;,
  -0.319498;0.471757;-0.821807;,
  -0.966099;0.080600;0.245269;,
  -0.487925;0.745997;0.453230;,
  -0.712784;0.666613;0.218096;,
  0.335300;-0.701327;-0.629058;,
  0.558893;-0.759095;-0.333786;,
  -0.997776;0.005477;-0.066434;,
  0.047110;-0.200685;0.978522;,
  0.993104;-0.114002;0.027335;,
  -0.057615;0.160968;-0.985277;,
  -0.912365;-0.020579;0.408861;,
  0.987703;-0.118108;0.102439;,
  0.014999;-0.036565;-0.999219;,
  -0.997566;-0.005409;-0.069516;,
  0.172882;0.832953;0.525643;,
  -0.083531;0.995480;-0.045185;,
  0.012299;-0.999034;0.042179;,
  -0.095196;0.995459;-0.000000;,
  -0.006263;0.065487;0.997834;,
  -0.078759;0.064253;0.994821;,
  -0.003537;-0.999994;0.000000;,
  0.999993;-0.003766;-0.000000;,
  0.999993;-0.003768;-0.000005;,
  0.999993;-0.003768;-0.000007;,
  0.999993;-0.003768;-0.000000;,
  0.007072;0.999975;0.000000;,
  -0.999993;0.003767;0.000000;,
  -0.966840;0.003642;-0.255358;,
  -0.999993;0.003767;-0.000000;,
  -0.922173;0.003475;-0.386762;,
  -0.007073;-0.999975;0.000000;,
  0.999993;-0.003768;-0.000000;,
  -0.007073;-0.999975;0.000000;,
  -0.916709;0.029595;0.398458;,
  -0.999993;0.003768;0.000000;,
  -0.964602;0.020881;0.262883;,
  -0.999993;0.003767;0.000000;,
  0.007072;0.999975;0.000000;,
  -0.125234;-0.056476;-0.990519;,
  -0.094890;0.004180;-0.995479;,
  -0.149927;0.119226;-0.981482;,
  -0.158146;0.186856;-0.969574;,
  -0.140991;0.051026;-0.988695;,
  -0.680911;0.050499;0.730623;,
  -0.611198;-0.791478;0.000000;;
  169;
  4;14,14,14,14;,
  3;17,3,19;,
  4;15,16,16,15;,
  3;18,7,20;,
  4;123,5,7,18;,
  3;0,6,2;,
  3;2,6,21;,
  3;21,6,4;,
  4;124,8,8,1;,
  4;125,9,9,125;,
  4;3,126,10,2;,
  4;2,10,127,0;,
  4;128,11,11,129;,
  4;5,12,12,7;,
  4;130,13,13,131;,
  4;6,132,132,4;,
  4;8,133,133,8;,
  4;9,134,134,9;,
  4;126,135,135,135;,
  4;10,136,136,127;,
  4;11,15,15,11;,
  4;137,137,137,137;,
  4;13,138,138,13;,
  4;132,139,139,132;,
  4;125,125,140,140;,
  4;2,21,19,3;,
  3;131,124,7;,
  3;124,20,7;,
  3;20,124,1;,
  3;129,17,19;,
  3;1,18,20;,
  4;21,4,129,19;,
  4;36,36,36,36;,
  4;39,25,112,41;,
  4;37,38,38,37;,
  3;40,29,42;,
  4;141,27,29,40;,
  3;22,28,24;,
  3;24,28,113;,
  3;113,28,43;,
  3;43,28,115;,
  3;115,28,26;,
  4;142,30,30,23;,
  4;143,31,31,143;,
  4;25,144,32,24;,
  4;24,32,145,22;,
  4;146,33,33,147;,
  4;27,34,34,29;,
  4;148,35,35,149;,
  4;28,150,150,26;,
  4;30,151,151,30;,
  4;31,152,152,31;,
  4;144,153,153,153;,
  4;32,154,154,145;,
  4;33,37,37,33;,
  4;34,155,155,34;,
  4;35,156,156,35;,
  4;150,157,157,150;,
  4;143,143,141,40;,
  4;24,113,112,25;,
  3;149,142,29;,
  3;29,142,42;,
  3;42,142,23;,
  4;147,39,41,114;,
  3;23,40,42;,
  4;43,115,114,41;,
  4;83,53,81,84;,
  4;103,106,105,104;,
  4;56,97,96,91;,
  3;50,44,93;,
  3;93,44,51;,
  3;51,44,45;,
  4;61,63,62,60;,
  4;64,67,66,65;,
  3;44,52,45;,
  3;45,81,53;,
  3;81,45,52;,
  4;45,53,83,82;,
  4;47,54,80,79;,
  4;85,52,44,86;,
  4;48,56,91,90;,
  4;49,57,95,94;,
  4;92,59,50,93;,
  4;97,56,48,98;,
  4;45,61,60,51;,
  3;49,94,62;,
  3;62,94,60;,
  3;60,94,158;,
  4;49,62,63,159;,
  3;159,63,82;,
  3;63,61,82;,
  3;82,61,45;,
  4;50,64,65,44;,
  3;46,86,66;,
  3;66,86,65;,
  3;65,86,44;,
  4;46,66,67,160;,
  3;160,67,98;,
  3;67,64,98;,
  3;98,64,50;,
  4;87,47,79,88;,
  3;69,70,161;,
  3;70,49,161;,
  3;161,49,159;,
  3;162,71,163;,
  3;71,90,163;,
  3;90,71,48;,
  3;68,89,164;,
  3;164,89,160;,
  3;160,89,46;,
  4;76,76,76,76;,
  3;74,70,99;,
  3;99,70,73;,
  3;73,70,69;,
  4;77,77,77,77;,
  3;72,68,100;,
  3;100,68,75;,
  3;75,68,164;,
  3;165,78,166;,
  3;78,167,166;,
  3;166,167,168;,
  4;69,169,169,73;,
  3;170,171,172;,
  3;172,102,173;,
  3;102,172,171;,
  4;72,174,174,68;,
  4;175,175,175,175;,
  4;164,176,176,75;,
  3;177,101,178;,
  3;101,179,178;,
  3;178,179,180;,
  4;74,181,181,70;,
  4;182,183,88,79;,
  4;80,55,182,79;,
  4;52,85,84,81;,
  4;83,54,47,82;,
  4;80,54,83,84;,
  4;85,55,80,84;,
  4;46,55,85,86;,
  4;184,185,87,88;,
  4;183,186,184,88;,
  4;91,57,163,90;,
  4;95,57,91,96;,
  4;51,58,92,93;,
  4;95,58,51,94;,
  4;92,58,95,96;,
  4;97,59,92,96;,
  4;50,59,97,98;,
  4;107,108,106,103;,
  4;109,110,107,103;,
  4;111,109,103,104;,
  4;116,104,105,117;,
  4;118,105,106,118;,
  4;118,106,108,118;,
  4;187,108,107,119;,
  4;119,107,110,120;,
  4;188,110,109,121;,
  4;122,111,104,116;,
  4;121,109,111,121;,
  4;113,43,41,112;,
  4;115,26,147,114;,
  4;102,116,117,173;,
  4;73,118,118,99;,
  4;99,118,118,74;,
  4;177,187,119,101;,
  4;101,119,120,179;,
  4;75,188,121,100;,
  4;100,121,121,72;,
  4;171,122,116,102;;
 }
 MeshTextureCoords {
  152;
  0.605886;0.303381;,
  0.596128;0.296691;,
  0.673865;0.286629;,
  0.668144;0.288853;,
  0.869564;0.028100;,
  0.775859;0.115013;,
  0.764570;0.113898;,
  0.609229;0.297798;,
  0.614583;0.306892;,
  0.671820;0.291674;,
  0.676007;0.281044;,
  0.874919;0.044380;,
  0.779476;0.135074;,
  0.780345;0.133183;,
  0.774122;0.118795;,
  0.609641;0.243118;,
  0.612413;0.239751;,
  0.613114;0.232698;,
  0.612246;0.224168;,
  0.611377;0.233789;,
  0.607547;0.244791;,
  0.684920;0.226748;,
  0.781214;0.131292;,
  0.680374;0.219059;,
  0.607631;0.240937;,
  0.611270;0.233482;,
  0.688332;0.213425;,
  0.688687;0.229654;,
  0.610113;0.242715;,
  0.617107;0.300915;,
  0.604855;0.292956;,
  0.702463;0.280984;,
  0.695281;0.283631;,
  0.868706;0.034518;,
  0.806531;0.100340;,
  0.799443;0.099676;,
  0.792356;0.099013;,
  0.621304;0.294274;,
  0.628028;0.305092;,
  0.699895;0.286987;,
  0.705152;0.274338;,
  0.875429;0.053886;,
  0.811073;0.124208;,
  0.812164;0.121958;,
  0.804349;0.104839;,
  0.621823;0.229214;,
  0.625303;0.225208;,
  0.626183;0.216816;,
  0.625638;0.211742;,
  0.625092;0.206668;,
  0.624547;0.212391;,
  0.624002;0.218115;,
  0.619193;0.231206;,
  0.716344;0.209736;,
  0.813254;0.119708;,
  0.710637;0.200589;,
  0.619298;0.226619;,
  0.623868;0.217750;,
  0.720629;0.193886;,
  0.721075;0.213195;,
  0.622415;0.228735;,
  0.599901;0.958324;,
  0.599118;0.947103;,
  0.848543;0.699255;,
  0.858713;0.700723;,
  0.798353;0.101926;,
  0.315045;0.047917;,
  0.375725;0.055510;,
  0.375725;0.153306;,
  0.318189;0.161026;,
  0.092189;0.182183;,
  0.092371;0.096685;,
  0.092371;0.096685;,
  0.092189;0.182183;,
  0.255066;0.299595;,
  0.313323;0.276181;,
  0.313346;0.164440;,
  0.255066;0.174401;,
  0.381527;0.263234;,
  0.381527;0.263234;,
  0.381527;0.153306;,
  0.381527;0.043378;,
  0.381527;0.043378;,
  0.375725;0.033612;,
  0.255066;0.031972;,
  0.255066;0.031972;,
  0.375725;0.033612;,
  0.375725;0.272999;,
  0.255066;0.321492;,
  0.255066;0.321492;,
  0.375725;0.272999;,
  0.375725;0.251101;,
  0.313713;0.039549;,
  0.245899;0.035721;,
  0.255066;0.040412;,
  0.255066;0.168692;,
  0.245899;0.170503;,
  0.315333;0.275373;,
  0.313713;0.290488;,
  0.245899;0.317742;,
  0.245899;0.176732;,
  0.245899;0.035721;,
  0.255066;0.040412;,
  0.313374;0.047708;,
  0.313713;0.039549;,
  0.375725;0.153778;,
  0.375725;0.251101;,
  0.313713;0.290488;,
  0.245899;0.317742;,
  0.209055;0.041958;,
  0.208916;0.176735;,
  0.172212;0.048194;,
  0.172212;0.048194;,
  0.171638;0.317742;,
  0.171638;0.317742;,
  0.208768;0.317742;,
  0.171638;0.317742;,
  0.128234;0.317199;,
  0.128808;0.047651;,
  0.172212;0.048194;,
  0.128808;0.047651;,
  0.128808;0.047651;,
  0.128808;0.047651;,
  0.172212;0.048194;,
  0.128808;0.047651;,
  0.128234;0.317199;,
  0.171638;0.317742;,
  0.128234;0.317199;,
  0.128234;0.317199;,
  0.128234;0.317199;,
  0.171925;0.182968;,
  0.128521;0.182425;,
  0.128521;0.182425;,
  0.255066;0.299595;,
  0.375725;0.055510;,
  0.092189;0.182183;,
  0.092371;0.096685;,
  0.092007;0.267680;,
  0.092007;0.267680;,
  0.092007;0.267680;,
  0.110355;0.182304;,
  0.110590;0.072168;,
  0.110590;0.072168;,
  0.110590;0.072168;,
  0.110355;0.182304;,
  0.110121;0.292440;,
  0.110121;0.292440;,
  0.110121;0.292440;,
  0.597553;0.948540;,
  0.596771;0.961198;,
  0.855583;0.710674;,
  0.846977;0.704231;;
 }
}
