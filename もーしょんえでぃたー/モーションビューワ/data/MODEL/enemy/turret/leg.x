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
 246;
 5.37091;-0.50461;-0.00000;,
 5.37142;-0.54150;0.40910;,
 8.24269;-0.45623;0.40910;,
 8.24219;-0.41934;-0.00000;,
 5.39127;-1.98342;-0.00000;,
 5.39127;-1.98342;0.55130;,
 5.38239;-1.33849;0.65160;,
 5.38168;-1.28728;-0.00000;,
 8.26254;-1.89815;-0.00000;,
 8.26254;-1.89815;0.55130;,
 8.25366;-1.25322;0.65160;,
 8.25296;-1.20201;-0.00000;,
 5.38342;-1.41328;1.06469;,
 5.39127;-1.98342;1.10260;,
 8.26254;-1.89815;1.10260;,
 8.25469;-1.32801;1.06469;,
 8.26254;-1.89815;-1.10260;,
 5.39127;-1.98342;-1.10260;,
 5.38342;-1.41328;-1.06469;,
 8.25469;-1.32801;-1.06469;,
 8.26254;-1.89815;-0.55130;,
 8.25366;-1.25322;-0.65160;,
 5.39127;-1.98342;-0.55130;,
 5.38239;-1.33849;-0.65160;,
 5.37142;-0.54150;-0.40910;,
 8.24269;-0.45623;-0.40910;,
 5.37217;-0.59538;0.81820;,
 8.24344;-0.51011;0.81820;,
 8.24344;-0.51011;-0.81820;,
 5.37217;-0.59538;-0.81820;,
 15.04344;-13.94995;0.06634;,
 15.04344;-13.94995;3.20889;,
 17.18959;-12.99763;3.20889;,
 17.18959;-12.99763;0.06634;,
 15.04344;-13.94995;-3.07621;,
 17.18959;-12.99763;-3.07621;,
 17.18959;-12.99763;-5.21455;,
 15.04344;-13.94995;-5.21455;,
 12.03536;-9.90028;-2.75525;,
 12.03536;-9.90028;-5.21455;,
 12.71217;-10.81144;-5.21455;,
 13.75080;-12.20971;-5.21455;,
 12.03536;-9.90028;0.06634;,
 12.03536;-9.90028;2.88794;,
 12.03536;-9.90028;5.15725;,
 12.71217;-10.81144;5.15725;,
 13.75080;-12.20971;5.15725;,
 15.04344;-13.94995;5.15725;,
 17.18959;-12.99763;5.15725;,
 13.73675;-8.34919;2.84049;,
 13.73675;-8.34919;5.15725;,
 14.83208;-9.82380;5.15725;,
 16.19264;-11.65546;5.15725;,
 13.73675;-8.34919;0.06634;,
 13.73675;-8.34919;-2.70780;,
 13.73675;-8.34919;-5.21455;,
 14.81346;-10.67526;-5.21455;,
 16.19264;-11.65546;-5.21455;,
 9.99817;-15.13428;-5.21455;,
 9.77141;-12.92927;-5.21455;,
 23.98717;-9.84658;5.15725;,
 19.03018;-7.96489;5.15725;,
 10.45262;-11.55707;-5.21455;,
 19.03018;-7.96489;-5.21455;,
 9.77141;-12.92927;5.15725;,
 9.99817;-15.13428;5.15725;,
 23.98717;-9.84658;-5.21455;,
 10.45262;-11.55707;5.15725;,
 15.09498;-17.44598;-5.21455;,
 26.47314;-17.34217;-5.21455;,
 28.19822;-14.12309;-5.21455;,
 15.09498;-17.44598;5.15725;,
 26.47314;-17.34217;5.15725;,
 28.19822;-14.12309;5.15725;,
 6.88180;-1.16174;2.95841;,
 6.88180;-1.16174;-3.30537;,
 6.77906;-1.34390;-3.30537;,
 6.77906;-1.34390;2.95841;,
 6.87387;-1.52426;-3.30537;,
 6.87387;-1.52426;2.95841;,
 7.11068;-1.59716;-3.30537;,
 7.11068;-1.59716;2.95841;,
 7.35077;-1.51991;-3.30537;,
 7.35077;-1.51991;2.95841;,
 7.45350;-1.33774;-3.30537;,
 7.45350;-1.33774;2.95841;,
 7.35870;-1.15739;-3.30537;,
 7.35870;-1.15739;2.95841;,
 7.12189;-1.08448;-3.30537;,
 7.12189;-1.08448;2.95841;,
 7.11628;-1.34082;2.95841;,
 7.11628;-1.34082;-3.30537;,
 10.11837;-3.47790;-0.00544;,
 9.98333;-3.29610;2.20619;,
 17.18959;-12.99763;2.92259;,
 17.18959;-12.99763;-0.00544;,
 7.97222;-4.43023;-0.00544;,
 7.83718;-4.24843;2.20619;,
 15.04344;-13.94995;-0.00544;,
 15.04344;-13.94995;2.92259;,
 17.18959;-12.99763;5.85062;,
 10.29896;-3.72102;5.85062;,
 8.15281;-4.67335;5.85062;,
 15.04344;-13.94995;5.85062;,
 15.04344;-13.94995;-5.86150;,
 8.15281;-4.67335;-5.86150;,
 10.29896;-3.72102;-5.86150;,
 17.18959;-12.99763;-5.86150;,
 17.18959;-12.99763;-2.93347;,
 15.04344;-13.94995;-2.93347;,
 7.83718;-4.24843;-2.21708;,
 9.98333;-3.29610;-2.21708;,
 5.83110;-1.54771;2.92259;,
 5.83110;-1.54771;5.85062;,
 7.97724;-0.59538;5.85062;,
 7.97724;-0.59538;2.92259;,
 7.97724;-0.59538;-5.86150;,
 5.83110;-1.54771;-5.86150;,
 5.83110;-1.54771;-2.93347;,
 7.97724;-0.59538;-2.93347;,
 5.61746;-1.36247;-1.28744;,
 5.62172;-0.36224;-1.28744;,
 5.62172;-0.36224;-0.72395;,
 5.61746;-1.36247;-0.72395;,
 3.46390;-0.35305;-1.28744;,
 4.86626;-0.35902;-1.28744;,
 4.86199;-1.35925;-1.28744;,
 3.45964;-1.35328;-1.28744;,
 2.06156;-0.34707;-1.28744;,
 2.05729;-1.34730;-1.28744;,
 1.22730;-1.34376;-1.28744;,
 1.23156;-0.34353;-1.28744;,
 1.23156;-0.34353;-1.38595;,
 2.06156;-0.34707;-1.38595;,
 2.84047;-0.35039;-1.38595;,
 3.46390;-0.35305;-1.38595;,
 4.27350;-0.35650;-1.38595;,
 4.86626;-0.35902;-1.38595;,
 5.62172;-0.36224;-1.38595;,
 5.70654;-0.36260;-1.38595;,
 5.70654;-0.36260;-1.28744;,
 5.70654;-0.36260;-0.72395;,
 5.61746;-1.36247;-1.38595;,
 4.86199;-1.35925;-1.38595;,
 3.45964;-1.35328;-1.38595;,
 4.26924;-1.35673;-1.38595;,
 2.05729;-1.34730;-1.38595;,
 2.83621;-1.35062;-1.38595;,
 1.22730;-1.34376;-1.38595;,
 1.21759;-3.62178;-1.38595;,
 2.82650;-3.62863;-1.38595;,
 4.25954;-3.63474;-1.38595;,
 5.69257;-3.64085;-1.38595;,
 5.70228;-1.36283;-1.38595;,
 3.46390;-0.35305;1.18630;,
 2.06156;-0.34707;1.18630;,
 2.05729;-1.34730;1.18630;,
 3.45964;-1.35328;1.18630;,
 4.86626;-0.35902;1.18630;,
 4.86199;-1.35925;1.18630;,
 4.86199;-1.35925;1.28475;,
 5.61746;-1.36247;1.28475;,
 5.61746;-1.36247;1.18630;,
 5.70228;-1.36283;1.28475;,
 5.70228;-1.36283;1.18630;,
 3.46390;-0.35305;1.28475;,
 4.27350;-0.35650;1.28475;,
 4.86626;-0.35902;1.28475;,
 2.06156;-0.34707;1.28475;,
 2.84047;-0.35039;1.28475;,
 1.23156;-0.34353;1.28475;,
 1.23156;-0.34353;1.18630;,
 1.22730;-1.34376;1.18630;,
 1.22730;-1.34376;1.28475;,
 2.05729;-1.34730;1.28475;,
 2.83621;-1.35062;1.28475;,
 3.45964;-1.35328;1.28475;,
 4.26924;-1.35673;1.28475;,
 2.85397;2.81839;1.28475;,
 4.28291;1.85127;1.28475;,
 5.70790;-0.04355;1.28475;,
 5.62172;-0.36224;1.28475;,
 5.70654;-0.36260;1.28475;,
 1.24724;3.33468;1.28475;,
 4.28291;1.85127;-1.38595;,
 5.70790;-0.04355;-1.38595;,
 5.69257;-3.64085;1.28475;,
 4.25954;-3.63474;1.28475;,
 2.85397;2.81839;-1.38595;,
 2.82650;-3.62863;1.28475;,
 1.24724;3.33468;-1.38595;,
 1.21759;-3.62178;1.28475;,
 5.70654;-0.36260;1.18630;,
 5.70654;-0.36260;1.13884;,
 5.70654;-0.36260;0.20745;,
 5.70228;-1.36283;1.13884;,
 5.70228;-1.36283;0.20745;,
 5.70228;-1.36283;-0.72395;,
 5.70228;-1.36283;-1.28744;,
 5.61746;-1.36247;0.20745;,
 5.61746;-1.36247;1.13884;,
 5.62172;-0.36224;1.18630;,
 5.62172;-0.36224;1.13884;,
 5.62172;-0.36224;0.20745;,
 1.92492;1.76428;0.00000;,
 1.84709;1.76461;0.38095;,
 1.83953;-0.00784;0.38095;,
 1.91737;-0.00817;-0.00000;,
 -1.19547;1.77757;0.00000;,
 -1.19547;1.77757;0.51337;,
 0.16537;1.77177;0.60677;,
 0.27342;1.77131;0.00000;,
 -1.20303;0.00513;0.51337;,
 -1.20303;0.00513;0.00000;,
 0.15026;-1.77312;0.60677;,
 -1.21058;-1.76732;0.51337;,
 -1.21058;-1.76732;0.00000;,
 0.25832;-1.77358;-0.00000;,
 0.00755;1.77245;1.21354;,
 -1.19547;1.77757;1.02674;,
 -1.20303;0.00513;1.02674;,
 0.00000;0.00000;1.21354;,
 -1.20303;0.00513;-1.02674;,
 -1.19547;1.77757;-1.02674;,
 0.00755;1.77245;-1.21354;,
 0.00000;0.00000;-1.21354;,
 -1.21058;-1.76732;-0.51337;,
 0.15026;-1.77312;-0.60677;,
 -1.19547;1.77757;-0.51337;,
 -1.20303;0.00513;-0.51337;,
 0.16537;1.77177;-0.60677;,
 1.84709;1.76461;-0.38095;,
 1.83953;-0.00784;-0.38095;,
 1.73339;1.76509;0.76191;,
 1.72584;-0.00736;0.76191;,
 -0.00755;-1.77245;1.21354;,
 -1.21058;-1.76732;1.02674;,
 -1.21058;-1.76732;-1.02674;,
 -0.00755;-1.77245;-1.21354;,
 1.72584;-0.00736;-0.76191;,
 1.73339;1.76509;-0.76191;,
 1.83198;-1.78029;0.38095;,
 1.71829;-1.77980;0.76191;,
 1.90982;-1.78062;-0.00000;,
 1.83198;-1.78029;-0.38095;,
 1.71829;-1.77980;-0.76191;;
 
 314;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,5,4;,
 4;10,9,8,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;11,8,20,21;,
 4;20,8,4,22;,
 4;22,4,7,23;,
 4;24,0,3,25;,
 4;1,26,27,2;,
 4;5,13,12,6;,
 4;9,14,13,5;,
 4;15,14,9,10;,
 4;16,19,21,20;,
 4;17,16,20,22;,
 4;18,17,22,23;,
 4;28,29,24,25;,
 4;29,18,23,24;,
 4;7,0,24,23;,
 4;6,1,0,7;,
 4;12,26,1,6;,
 4;27,26,12,15;,
 4;2,27,15,10;,
 4;3,2,10,11;,
 4;25,3,11,21;,
 4;19,28,25,21;,
 4;18,29,28,19;,
 4;30,31,32,33;,
 4;34,30,33,35;,
 4;36,37,34,35;,
 3;38,34,39;,
 3;39,34,40;,
 3;40,34,41;,
 3;41,34,37;,
 4;38,42,30,34;,
 4;42,43,31,30;,
 3;44,45,43;,
 3;45,46,43;,
 3;43,46,31;,
 3;31,46,47;,
 4;47,48,32,31;,
 3;49,32,50;,
 3;50,32,51;,
 3;51,32,52;,
 3;52,32,48;,
 4;49,53,33,32;,
 4;53,54,35,33;,
 3;55,56,54;,
 3;56,57,54;,
 3;54,57,35;,
 3;35,57,36;,
 4;41,58,59,40;,
 4;51,60,61,50;,
 4;40,59,62,39;,
 3;55,54,63;,
 3;54,53,63;,
 3;53,49,63;,
 3;49,50,63;,
 3;63,50,61;,
 4;45,64,65,46;,
 4;55,63,66,56;,
 4;66,63,61,60;,
 4;44,67,64,45;,
 4;62,59,64,67;,
 3;58,41,68;,
 3;41,37,68;,
 3;37,36,68;,
 3;68,36,69;,
 3;57,70,36;,
 3;36,70,69;,
 4;58,68,71,65;,
 3;65,71,46;,
 3;46,71,47;,
 3;47,71,48;,
 3;71,72,48;,
 3;52,48,73;,
 3;73,48,72;,
 4;69,70,73,72;,
 4;56,66,70,57;,
 4;52,73,60,51;,
 4;68,69,72,71;,
 4;59,58,65,64;,
 3;62,67,39;,
 3;39,67,38;,
 3;38,67,42;,
 3;42,67,43;,
 3;43,67,44;,
 4;70,66,60,73;,
 4;74,75,76,77;,
 4;77,76,78,79;,
 4;79,78,80,81;,
 4;81,80,82,83;,
 4;83,82,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,75,74;,
 3;77,90,74;,
 3;79,90,77;,
 3;81,90,79;,
 3;83,90,81;,
 3;85,90,83;,
 3;87,90,85;,
 3;89,90,87;,
 3;74,90,89;,
 3;75,91,76;,
 3;76,91,78;,
 3;78,91,80;,
 3;80,91,82;,
 3;82,91,84;,
 3;84,91,86;,
 3;86,91,88;,
 3;88,91,75;,
 4;92,93,94,95;,
 4;96,97,93,92;,
 4;98,99,97,96;,
 4;95,94,99,98;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,95,98,109;,
 4;109,98,96,110;,
 4;110,96,92,111;,
 4;111,92,95,108;,
 4;93,101,100,94;,
 4;112,113,114,115;,
 4;99,103,102,97;,
 4;94,100,103,99;,
 4;104,107,108,109;,
 4;105,104,109,110;,
 4;116,117,118,119;,
 4;107,106,111,108;,
 4;97,112,115,93;,
 4;93,115,114,101;,
 4;101,114,113,102;,
 4;102,113,112,97;,
 4;106,116,119,111;,
 4;111,119,118,110;,
 4;110,118,117,105;,
 4;105,117,116,106;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,124,127,129;,
 4;130,131,128,129;,
 4;132,133,128,131;,
 3;133,134,128;,
 3;128,134,124;,
 3;124,134,135;,
 3;135,136,124;,
 3;124,136,125;,
 3;125,136,137;,
 3;137,138,125;,
 3;125,138,121;,
 3;138,139,121;,
 3;121,139,122;,
 3;122,140,141;,
 3;140,122,139;,
 4;121,120,126,125;,
 4;120,142,143,126;,
 3;127,126,144;,
 3;144,126,145;,
 3;145,126,143;,
 3;129,127,146;,
 3;146,127,147;,
 3;147,127,144;,
 4;146,148,130,129;,
 3;149,148,150;,
 3;148,146,150;,
 3;150,146,147;,
 3;150,147,151;,
 3;147,144,151;,
 3;151,144,145;,
 3;151,145,152;,
 3;145,143,152;,
 3;143,142,152;,
 3;152,142,153;,
 4;154,155,156,157;,
 4;158,154,157,159;,
 3;160,161,159;,
 3;159,161,162;,
 3;161,163,162;,
 3;162,163,164;,
 3;154,158,165;,
 3;165,158,166;,
 3;166,158,167;,
 3;155,154,168;,
 3;168,154,169;,
 3;169,154,165;,
 4;170,171,155,168;,
 4;171,172,156,155;,
 4;172,173,174,156;,
 3;174,175,156;,
 3;156,175,157;,
 3;157,175,176;,
 3;176,177,157;,
 3;157,177,159;,
 3;159,177,160;,
 3;169,165,178;,
 3;178,165,179;,
 3;179,165,166;,
 3;166,167,179;,
 3;179,167,180;,
 3;167,181,180;,
 3;180,181,182;,
 3;170,168,183;,
 3;183,168,178;,
 3;178,168,169;,
 3;136,184,137;,
 3;184,185,137;,
 3;137,185,138;,
 3;138,185,139;,
 4;151,152,186,187;,
 3;187,186,177;,
 3;177,186,160;,
 3;160,186,161;,
 3;161,186,163;,
 4;185,184,179,180;,
 3;134,188,135;,
 3;188,184,135;,
 3;135,184,136;,
 4;150,151,187,189;,
 3;189,187,175;,
 3;175,187,176;,
 3;176,187,177;,
 4;184,188,178,179;,
 3;132,190,133;,
 3;190,188,133;,
 3;133,188,134;,
 3;191,189,173;,
 3;173,189,174;,
 3;174,189,175;,
 4;149,150,189,191;,
 3;149,191,148;,
 3;148,191,130;,
 3;132,131,190;,
 3;190,131,183;,
 3;130,191,131;,
 3;131,171,183;,
 3;183,171,170;,
 3;171,131,172;,
 3;131,191,172;,
 3;172,191,173;,
 4;188,190,183,178;,
 3;182,192,180;,
 3;180,192,185;,
 3;192,193,185;,
 3;193,194,185;,
 3;194,141,185;,
 3;141,140,185;,
 3;185,140,139;,
 3;186,152,163;,
 3;163,152,164;,
 3;164,152,195;,
 3;195,152,196;,
 3;196,152,197;,
 3;197,152,198;,
 3;198,152,153;,
 3;123,197,120;,
 3;120,197,142;,
 3;142,198,153;,
 3;198,142,197;,
 4;196,197,123,199;,
 4;195,196,199,200;,
 4;201,162,200,202;,
 3;158,201,167;,
 3;167,201,181;,
 3;202,193,201;,
 3;201,193,181;,
 3;181,192,182;,
 3;192,181,193;,
 4;194,193,202,203;,
 4;141,194,203,122;,
 4;122,203,199,123;,
 4;203,202,200,199;,
 4;201,158,159,162;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,209,208,213;,
 4;214,215,216,217;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;217,216,226,227;,
 4;213,208,228,229;,
 4;228,208,211,230;,
 4;231,204,207,232;,
 4;205,233,234,206;,
 4;209,219,218,210;,
 4;220,219,209,212;,
 4;235,236,215,214;,
 4;237,238,227,226;,
 4;223,222,229,228;,
 4;224,223,228,230;,
 4;239,240,231,232;,
 4;240,224,230,231;,
 4;211,204,231,230;,
 4;210,205,204,211;,
 4;218,233,205,210;,
 4;234,233,218,221;,
 4;241,242,235,214;,
 4;243,241,214,217;,
 4;244,243,217,227;,
 4;238,245,244,227;,
 4;224,240,239,225;,
 4;245,239,232,244;,
 4;207,243,244,232;,
 4;206,241,243,207;,
 4;234,242,241,206;,
 4;242,234,221,235;,
 4;220,236,235,221;,
 4;215,236,220,212;,
 4;216,215,212,213;,
 4;226,216,213,229;,
 4;222,237,226,229;,
 4;237,222,225,238;,
 4;239,245,238,225;;
 
 MeshMaterialList {
  1;
  314;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "turret_UV.jpg";
   }
  }
 }
 MeshNormals {
  265;
  -0.029430;0.991002;-0.130573;,
  -0.029430;0.991002;0.130573;,
  -0.001970;0.066319;-0.997797;,
  -0.001970;0.066319;0.997797;,
  -0.029685;0.999559;0.000000;,
  0.029685;-0.999559;-0.000000;,
  -0.999905;-0.013771;0.000000;,
  -0.029504;0.993470;0.110213;,
  -0.999905;-0.013769;0.000002;,
  -0.029504;0.993470;-0.110213;,
  0.999905;0.013765;-0.000002;,
  -0.005302;0.178517;-0.983922;,
  -0.999905;-0.013763;-0.000005;,
  -0.999905;-0.013766;0.000000;,
  -0.999905;-0.013763;0.000005;,
  -0.005302;0.178517;0.983922;,
  0.999905;0.013762;0.000001;,
  0.999905;0.013763;0.000000;,
  0.999905;0.013762;-0.000001;,
  -0.405596;0.914052;0.000000;,
  -0.405596;0.914052;0.000000;,
  0.802768;0.596292;0.000001;,
  0.802767;0.596293;0.000000;,
  0.802767;0.596293;0.000003;,
  0.802767;0.596293;0.000003;,
  0.802767;0.596292;0.000000;,
  0.802767;0.596293;-0.000001;,
  0.802766;0.596294;0.000000;,
  0.802768;0.596292;0.000000;,
  0.802768;0.596292;-0.000001;,
  0.802767;0.596293;-0.000001;,
  -0.802767;-0.596293;0.000002;,
  -0.802768;-0.596292;0.000004;,
  -0.802768;-0.596292;0.000000;,
  -0.802768;-0.596292;-0.000002;,
  -0.802768;-0.596292;0.000000;,
  -0.786007;-0.606965;0.117417;,
  -0.756008;-0.608873;0.240263;,
  -0.907493;-0.420068;0.000000;,
  -0.732531;-0.662566;0.156224;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.001207;0.999999;0.000000;,
  -0.206839;-0.978375;0.000000;,
  -0.632127;0.774865;0.000000;,
  -0.999891;0.014781;0.000000;,
  -0.638639;-0.769506;0.000000;,
  0.006328;-0.999980;-0.000000;,
  0.632138;-0.774856;-0.000000;,
  0.999891;-0.014757;-0.000000;,
  0.638662;0.769487;0.000000;,
  -0.006328;0.999980;0.000000;,
  0.802767;0.596292;-0.000000;,
  -0.802767;-0.596293;0.000000;,
  -0.405600;0.914051;-0.000000;,
  0.802767;0.596292;-0.000000;,
  0.802767;0.596293;-0.000000;,
  -0.403591;0.909523;-0.099407;,
  -0.802767;-0.596293;0.000000;,
  0.405596;-0.914052;-0.000000;,
  -0.802767;-0.596293;-0.000000;,
  -0.403591;0.909523;0.099407;,
  -0.405601;0.914050;0.000000;,
  0.999991;-0.004259;-0.000000;,
  -0.004265;-0.999991;0.000000;,
  -0.004264;-0.999991;0.000000;,
  -0.004264;-0.999991;0.000000;,
  -0.004264;-0.999991;-0.000005;,
  -0.004257;-0.999991;0.000000;,
  -0.004257;-0.999991;0.000012;,
  -0.004244;-0.999991;0.000000;,
  -0.004244;-0.999991;0.000000;,
  -0.004256;-0.999991;0.000000;,
  0.004257;0.999991;0.000000;,
  0.004249;0.999991;0.000000;,
  0.004256;0.999991;-0.000030;,
  0.004262;0.999991;-0.000020;,
  0.004264;0.999991;0.000014;,
  0.004264;0.999991;0.000009;,
  0.004265;0.999991;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.004257;0.999991;0.000000;,
  0.004250;0.999991;0.000000;,
  0.004244;0.999991;0.000000;,
  0.004256;0.999991;0.000000;,
  -0.004256;-0.999991;-0.000030;,
  -0.004259;-0.999991;0.000000;,
  -0.004262;-0.999991;-0.000020;,
  -0.004264;-0.999991;0.000009;,
  -0.004265;-0.999991;0.000014;,
  0.004264;0.999991;0.000000;,
  0.004265;0.999991;0.000000;,
  0.004264;0.999991;-0.000005;,
  0.004264;0.999991;0.000000;,
  0.004257;0.999991;0.000012;,
  -0.004264;-0.999991;0.000000;,
  -0.004264;-0.999991;0.000000;,
  -0.004261;-0.999991;0.000000;,
  -0.000000;0.000000;1.000000;,
  0.999991;-0.004262;-0.000000;,
  0.999991;-0.004262;-0.000000;,
  0.999991;-0.004262;-0.000000;,
  0.999991;-0.004262;-0.000000;,
  0.004244;0.999991;0.000000;,
  0.999991;-0.004259;-0.000000;,
  -0.004261;-0.999991;-0.000005;,
  -0.004261;-0.999991;0.000005;,
  0.694947;-0.002962;-0.719054;,
  0.694947;-0.002962;0.719054;,
  -0.153434;0.000654;-0.988159;,
  -0.153434;0.000654;0.988159;,
  -0.004263;-0.999991;0.000002;,
  -0.004263;-0.999991;-0.000002;,
  -0.004263;-0.999991;0.000000;,
  -0.004262;-0.999991;0.000000;,
  0.004262;0.999991;0.000000;,
  0.999991;-0.004262;-0.000000;,
  -0.004262;-0.999991;0.000001;,
  0.969937;-0.004134;0.243321;,
  0.004261;0.999991;-0.000003;,
  -0.004262;-0.999991;-0.000001;,
  -0.004262;-0.999991;-0.000001;,
  -0.004262;-0.999991;0.000001;,
  -0.999991;0.004265;0.000000;,
  0.969937;-0.004134;-0.243321;,
  0.050928;-0.000217;-0.998702;,
  0.004260;0.999991;0.000001;,
  0.004260;0.999991;0.000000;,
  0.004260;0.999991;-0.000001;,
  0.050928;-0.000217;0.998702;,
  -0.004262;-0.999991;0.000002;,
  -0.004262;-0.999991;-0.000000;,
  -0.004263;-0.999991;0.000000;,
  -0.004262;-0.999991;0.000000;,
  -0.004262;-0.999991;-0.000002;,
  0.694950;-0.002961;-0.719052;,
  0.969937;-0.004133;-0.243321;,
  0.999991;-0.004261;-0.000000;,
  0.969937;-0.004133;0.243321;,
  0.694950;-0.002961;0.719052;,
  0.050929;-0.000217;0.998702;,
  -0.153434;0.000654;0.988159;,
  -0.999991;0.004262;0.000000;,
  -0.153434;0.000654;-0.988159;,
  0.050929;-0.000217;-0.998702;,
  0.999905;0.013765;0.000002;,
  0.999905;0.013763;0.000000;,
  -0.999905;-0.013769;-0.000002;,
  -0.999905;-0.013768;0.000000;,
  -0.999905;-0.013761;0.000006;,
  0.029685;-0.999559;-0.000000;,
  0.999905;0.013761;-0.000006;,
  0.999905;0.013767;-0.000000;,
  0.999905;0.013767;0.000000;,
  0.999905;0.013761;0.000006;,
  -0.999905;-0.013761;-0.000006;,
  -0.999905;-0.013768;-0.000000;,
  -0.999905;-0.013754;-0.000012;,
  -0.999905;-0.013757;-0.000009;,
  -0.999905;-0.013760;0.000000;,
  -0.999905;-0.013757;0.000009;,
  -0.999905;-0.013754;0.000012;,
  -0.008566;0.288432;0.957462;,
  0.999905;0.013759;0.000001;,
  0.999905;0.013756;-0.000011;,
  0.999905;0.013763;0.000000;,
  0.999905;0.013759;-0.000001;,
  0.999905;0.013756;0.000011;,
  -0.008566;0.288432;-0.957462;,
  0.802767;0.596293;0.000001;,
  0.802767;0.596292;-0.000000;,
  -0.802768;-0.596292;0.000001;,
  -0.802770;-0.596289;0.000000;,
  -0.802768;-0.596291;-0.000001;,
  -0.072409;0.997375;0.000000;,
  -0.072409;0.997375;0.000000;,
  0.144655;0.989482;0.000000;,
  0.546313;0.837581;0.000000;,
  -0.818691;0.574234;0.000000;,
  -0.983994;0.178200;0.000000;,
  -0.756614;0.653862;0.000000;,
  -0.413058;-0.910705;0.000000;,
  0.881415;-0.472343;-0.000000;,
  0.009123;-0.999958;-0.000000;,
  -0.994754;-0.102299;0.000000;,
  -0.723081;0.690763;0.000000;,
  -0.723081;0.690763;0.000000;,
  0.712539;0.701632;0.000000;,
  -0.802767;-0.596293;0.000000;,
  0.405596;-0.914052;-0.000000;,
  -0.802767;-0.596293;-0.000000;,
  0.802767;0.596293;0.000000;,
  0.802767;0.596292;0.000000;,
  0.802767;0.596293;-0.000000;,
  0.802767;0.596292;-0.000000;,
  -0.802767;-0.596293;0.000000;,
  -0.802767;-0.596292;0.000000;,
  0.405596;-0.914052;-0.000000;,
  -0.802767;-0.596292;-0.000000;,
  -0.802767;-0.596293;-0.000000;,
  0.802767;0.596292;0.000000;,
  0.802767;0.596293;0.000000;,
  -0.086492;0.194916;-0.976999;,
  0.802766;0.596294;-0.000000;,
  -0.802768;-0.596292;0.000000;,
  0.802766;0.596294;0.000000;,
  -0.086491;0.194913;0.977000;,
  -0.802768;-0.596292;-0.000000;,
  -0.004264;-0.999991;-0.000005;,
  -0.004262;-0.999991;0.000005;,
  -0.004258;-0.999991;0.000009;,
  -0.004250;-0.999991;0.000000;,
  0.004258;0.999991;-0.000015;,
  0.004263;0.999991;0.000007;,
  0.004265;0.999991;0.000000;,
  0.004258;0.999991;0.000009;,
  -0.004263;-0.999991;0.000007;,
  -0.004258;-0.999991;-0.000015;,
  -0.004265;-0.999991;0.000000;,
  0.004264;0.999991;-0.000005;,
  0.004262;0.999991;0.000005;,
  0.996437;0.084337;0.000000;,
  0.689276;0.724499;0.000000;,
  0.978323;0.207087;0.000000;,
  0.437620;0.899160;0.000000;,
  -0.004258;-0.999991;0.000000;,
  -0.999991;0.004262;0.000000;,
  -0.999991;0.004262;-0.000000;,
  -0.999991;0.004262;0.000000;,
  -0.999991;0.004261;-0.000002;,
  -0.999991;0.004263;0.000000;,
  -0.999991;0.004262;-0.000000;,
  -0.999991;0.004263;0.000000;,
  -0.999991;0.004263;0.000000;,
  -0.999991;0.004262;0.000000;,
  -0.999991;0.004261;0.000000;,
  -0.999991;0.004262;0.000000;,
  0.305924;0.952056;0.000000;,
  0.999991;-0.004262;-0.000000;,
  0.999991;-0.004262;-0.000000;,
  0.004244;0.999991;0.000000;,
  -0.004253;-0.999991;0.000000;,
  -0.004249;-0.999991;0.000000;,
  -0.004244;-0.999991;0.000000;,
  0.004261;0.999991;0.000003;,
  0.004259;0.999991;-0.000006;,
  0.004261;0.999991;-0.000003;,
  -0.999991;0.004265;0.000000;,
  0.004261;0.999991;0.000003;,
  0.004259;0.999991;0.000006;,
  0.004262;0.999991;0.000000;,
  0.004260;0.999991;-0.000001;,
  0.004257;0.999991;0.000000;,
  0.004260;0.999991;0.000001;,
  0.004262;0.999991;-0.000000;,
  0.694952;-0.002960;-0.719050;,
  0.969937;-0.004132;-0.243321;,
  0.999991;-0.004260;-0.000000;,
  0.969937;-0.004132;0.243321;,
  0.694952;-0.002960;0.719050;,
  0.050929;-0.000217;0.998702;,
  -0.153433;0.000654;0.988159;,
  -0.999991;0.004260;0.000000;,
  -0.153433;0.000654;-0.988159;,
  0.050929;-0.000217;-0.998702;;
  314;
  4;4,7,7,4;,
  4;6,8,14,13;,
  4;5,5,5,5;,
  4;16,145,146,17;,
  4;15,3,3,15;,
  4;2,2,11,11;,
  4;17,146,10,18;,
  4;5,5,5,5;,
  4;147,6,13,12;,
  4;9,4,4,9;,
  4;7,1,1,7;,
  4;8,148,149,14;,
  4;5,150,150,5;,
  4;151,152,145,16;,
  4;153,154,18,10;,
  4;150,150,5,5;,
  4;155,156,147,12;,
  4;0,0,9,9;,
  4;157,155,12,158;,
  4;13,159,158,12;,
  4;14,160,159,13;,
  4;149,161,160,14;,
  4;162,162,15,15;,
  4;163,164,151,16;,
  4;165,163,16,17;,
  4;166,165,17,18;,
  4;154,167,166,18;,
  4;11,168,168,11;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,19,19;,
  3;22,169,23;,
  3;23,169,24;,
  3;24,169,21;,
  3;21,169,28;,
  4;22,25,25,169;,
  4;25,26,170,25;,
  3;27,30,26;,
  3;30,29,26;,
  3;26,29,170;,
  3;170,29,28;,
  4;19,19,19,19;,
  3;33,171,34;,
  3;34,171,31;,
  3;31,171,32;,
  3;32,171,172;,
  4;33,35,35,171;,
  4;35,36,173,35;,
  3;38,37,36;,
  3;37,39,36;,
  3;36,39,173;,
  3;173,39,172;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  3;174,175,42;,
  3;175,175,42;,
  3;175,175,42;,
  3;175,175,42;,
  3;42,175,176;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;177,42,176,177;,
  4;41,41,41,41;,
  4;178,179,179,180;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  4;181,43,43,181;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;182,182,182,182;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;43,183,183,43;,
  4;179,184,184,179;,
  3;178,180,185;,
  3;185,180,185;,
  3;185,180,185;,
  3;185,180,185;,
  3;185,180,186;,
  4;187,177,177,187;,
  4;44,44,45,45;,
  4;45,45,46,46;,
  4;46,46,47,47;,
  4;47,47,48,48;,
  4;48,48,49,49;,
  4;49,49,50,50;,
  4;50,50,51,51;,
  4;51,51,44,44;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  4;52,56,55,52;,
  4;54,57,57,54;,
  4;53,58,188,53;,
  4;189,59,59,189;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;59,189,189,59;,
  4;190,53,53,60;,
  4;61,54,54,61;,
  4;191,52,52,192;,
  4;56,193,194,55;,
  4;62,62,62,62;,
  4;58,195,196,188;,
  4;59,59,59,59;,
  4;197,197,59,59;,
  4;198,199,190,60;,
  4;62,62,62,62;,
  4;200,201,191,192;,
  4;202,202,202,202;,
  4;56,203,203,193;,
  4;41,41,41,41;,
  4;196,204,204,188;,
  4;201,205,205,191;,
  4;206,206,206,206;,
  4;60,207,207,198;,
  4;40,40,40,40;,
  4;63,63,63,63;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;64,65,208,64;,
  3;65,67,208;,
  3;208,67,209;,
  3;209,67,66;,
  3;66,69,209;,
  3;209,69,210;,
  3;210,69,68;,
  3;68,72,210;,
  3;210,72,211;,
  3;72,71,211;,
  3;211,71,71;,
  3;71,71,70;,
  3;71,71,71;,
  4;40,40,40,40;,
  4;82,74,73,212;,
  3;213,212,76;,
  3;76,212,75;,
  3;75,212,73;,
  3;214,213,78;,
  3;78,213,77;,
  3;77,213,76;,
  4;78,79,79,214;,
  3;80,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  3;81,84,215;,
  3;215,84,82;,
  3;84,83,82;,
  3;82,83,83;,
  3;216,217,87;,
  3;87,217,85;,
  3;85,217,86;,
  3;218,216,88;,
  3;88,216,89;,
  3;89,216,87;,
  4;64,64,218,88;,
  4;41,41,41,41;,
  4;91,91,90,219;,
  3;90,92,219;,
  3;219,92,220;,
  3;220,92,93;,
  3;93,94,220;,
  3;220,94,215;,
  3;215,94,81;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  4;95,96,96,95;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;221,222,222,223;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  4;97,95,95,97;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;222,224,224,222;,
  3;40,40,40;,
  3;40,40,40;,
  3;40,40,40;,
  3;98,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;225,97,97,225;,
  3;226,227,228;,
  3;228,227,229;,
  3;230,231,232;,
  3;232,231,233;,
  3;229,227,231;,
  3;231,234,233;,
  3;233,234,233;,
  3;234,231,235;,
  3;231,227,235;,
  3;235,227,236;,
  4;224,237,237,224;,
  3;100,100,223;,
  3;223,100,221;,
  3;100,100,221;,
  3;100,99,221;,
  3;99,99,221;,
  3;99,99,221;,
  3;221,99,99;,
  3;238,238,239;,
  3;239,238,239;,
  3;239,238,101;,
  3;101,238,101;,
  3;101,238,102;,
  3;102,238,102;,
  3;102,238,239;,
  3;240,103,82;,
  3;82,103,74;,
  3;74,103,83;,
  3;103,74,103;,
  4;103,103,240,103;,
  4;103,103,103,103;,
  4;104,104,63,63;,
  3;217,241,86;,
  3;86,241,242;,
  3;71,71,241;,
  3;241,71,242;,
  3;242,70,243;,
  3;70,242,71;,
  4;71,71,71,71;,
  4;70,71,71,71;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;41,41,41,41;,
  4;116,118,138,137;,
  4;115,119,128,127;,
  4;142,123,123,142;,
  4;131,120,114,132;,
  4;129,110,141,140;,
  4;143,109,125,144;,
  4;132,114,122,133;,
  4;142,123,123,142;,
  4;244,115,127,126;,
  4;124,116,137,136;,
  4;118,108,139,138;,
  4;119,245,246,128;,
  4;142,247,123,142;,
  4;130,112,120,131;,
  4;111,134,133,122;,
  4;247,142,142,123;,
  4;248,249,244,126;,
  4;135,107,124,136;,
  4;250,248,126,251;,
  4;127,252,251,126;,
  4;128,253,252,127;,
  4;246,254,253,128;,
  4;139,108,129,140;,
  4;117,106,130,131;,
  4;113,117,131,132;,
  4;121,113,132,133;,
  4;134,105,121,133;,
  4;125,107,135,144;,
  4;255,135,136,256;,
  4;137,257,256,136;,
  4;138,258,257,137;,
  4;139,259,258,138;,
  4;259,139,140,260;,
  4;141,261,260,140;,
  4;262,262,142,142;,
  4;262,262,142,142;,
  4;262,262,142,142;,
  4;142,262,262,142;,
  4;263,143,144,264;,
  4;135,255,264,144;;
 }
 MeshTextureCoords {
  246;
  0.213963;0.436788;,
  0.223414;0.436952;,
  0.223414;0.463577;,
  0.213963;0.463413;,
  0.213963;0.443359;,
  0.226699;0.443359;,
  0.229016;0.440493;,
  0.213963;0.440266;,
  0.213963;0.469984;,
  0.226699;0.469984;,
  0.229016;0.467118;,
  0.213963;0.466890;,
  0.238559;0.440826;,
  0.239435;0.443359;,
  0.239435;0.469984;,
  0.238559;0.467450;,
  0.188490;0.469984;,
  0.188490;0.443359;,
  0.189366;0.440826;,
  0.189366;0.467450;,
  0.201226;0.469984;,
  0.198909;0.467118;,
  0.201226;0.443359;,
  0.198909;0.440493;,
  0.204511;0.436952;,
  0.204511;0.463577;,
  0.232865;0.437191;,
  0.232865;0.463816;,
  0.195060;0.463816;,
  0.195060;0.437191;,
  0.214652;0.624521;,
  0.287252;0.624521;,
  0.287252;0.612409;,
  0.214652;0.612409;,
  0.142053;0.624521;,
  0.142053;0.612409;,
  0.092653;0.612409;,
  0.092653;0.624521;,
  0.149468;0.571579;,
  0.092653;0.571579;,
  0.092653;0.583491;,
  0.092653;0.601770;,
  0.214652;0.571579;,
  0.279837;0.571579;,
  0.332263;0.571579;,
  0.332263;0.583491;,
  0.332263;0.601770;,
  0.332263;0.624521;,
  0.332263;0.612409;,
  0.278741;0.551639;,
  0.332263;0.551639;,
  0.332263;0.570917;,
  0.332263;0.594863;,
  0.214652;0.551639;,
  0.150564;0.551639;,
  0.092653;0.551639;,
  0.092653;0.581971;,
  0.092653;0.594863;,
  0.092653;0.639302;,
  0.092653;0.610642;,
  0.332263;0.572298;,
  0.332263;0.547276;,
  0.092653;0.592905;,
  0.092653;0.547276;,
  0.332263;0.610642;,
  0.332263;0.639302;,
  0.092653;0.572298;,
  0.332263;0.592905;,
  0.092653;0.669923;,
  0.092653;0.669923;,
  0.092653;0.628327;,
  0.332263;0.669923;,
  0.332263;0.669923;,
  0.332263;0.628327;,
  0.837630;0.097603;,
  0.633417;0.097603;,
  0.633417;0.169803;,
  0.837630;0.169803;,
  0.633417;0.242004;,
  0.837630;0.242004;,
  0.633417;0.271909;,
  0.837630;0.271909;,
  0.633417;0.242004;,
  0.837630;0.242004;,
  0.633417;0.169803;,
  0.837630;0.169803;,
  0.633417;0.097603;,
  0.837630;0.097603;,
  0.633417;0.067696;,
  0.837630;0.067696;,
  0.837630;0.169803;,
  0.633417;0.169803;,
  0.229840;0.100718;,
  0.277356;0.097286;,
  0.292747;0.280437;,
  0.229840;0.280437;,
  0.229840;0.118208;,
  0.277356;0.114776;,
  0.229840;0.297928;,
  0.292747;0.297928;,
  0.355654;0.280437;,
  0.355654;0.105307;,
  0.355654;0.122798;,
  0.355654;0.297928;,
  0.104026;0.297928;,
  0.104026;0.122798;,
  0.104026;0.105307;,
  0.104026;0.280437;,
  0.166933;0.280437;,
  0.166933;0.297928;,
  0.182324;0.114776;,
  0.182324;0.097286;,
  0.292747;0.063790;,
  0.355654;0.063790;,
  0.355654;0.046300;,
  0.292747;0.046300;,
  0.104026;0.046300;,
  0.104026;0.063790;,
  0.166933;0.063790;,
  0.166933;0.046300;,
  0.146343;0.460142;,
  0.146343;0.447145;,
  0.175939;0.447145;,
  0.175939;0.460142;,
  0.146343;0.447145;,
  0.146343;0.447145;,
  0.146343;0.460142;,
  0.146343;0.460142;,
  0.146343;0.447145;,
  0.146343;0.460142;,
  0.146343;0.460142;,
  0.146343;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.141168;0.447145;,
  0.146343;0.447145;,
  0.175939;0.447145;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.460142;,
  0.141168;0.489743;,
  0.141168;0.489743;,
  0.141168;0.489743;,
  0.141168;0.489743;,
  0.141168;0.460142;,
  0.276271;0.447145;,
  0.276271;0.447145;,
  0.276271;0.460142;,
  0.276271;0.460142;,
  0.276271;0.447145;,
  0.276271;0.460142;,
  0.281442;0.460142;,
  0.281442;0.460142;,
  0.276271;0.460142;,
  0.281442;0.460142;,
  0.276271;0.460142;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.276271;0.447145;,
  0.276271;0.460142;,
  0.281442;0.460142;,
  0.281442;0.460142;,
  0.281442;0.460142;,
  0.281442;0.460142;,
  0.281442;0.460142;,
  0.281442;0.405968;,
  0.281442;0.418456;,
  0.281442;0.442999;,
  0.281442;0.447145;,
  0.281442;0.447145;,
  0.281442;0.399349;,
  0.141168;0.418456;,
  0.141168;0.442999;,
  0.281442;0.489743;,
  0.281442;0.489743;,
  0.141168;0.405968;,
  0.281442;0.489743;,
  0.141168;0.399349;,
  0.281442;0.489743;,
  0.276271;0.447145;,
  0.273778;0.447145;,
  0.224858;0.447145;,
  0.273778;0.460142;,
  0.224858;0.460142;,
  0.175939;0.460142;,
  0.146343;0.460142;,
  0.224858;0.460142;,
  0.273778;0.460142;,
  0.276271;0.447145;,
  0.273778;0.447145;,
  0.224858;0.447145;,
  0.213963;0.419717;,
  0.233972;0.419717;,
  0.233972;0.442749;,
  0.213963;0.442749;,
  0.213963;0.419717;,
  0.240926;0.419717;,
  0.245832;0.419717;,
  0.213963;0.419717;,
  0.240926;0.442749;,
  0.213963;0.442749;,
  0.245832;0.465780;,
  0.240926;0.465780;,
  0.213963;0.465780;,
  0.213963;0.465780;,
  0.277701;0.419717;,
  0.267890;0.419717;,
  0.267890;0.442749;,
  0.277701;0.442749;,
  0.160035;0.442749;,
  0.160035;0.419717;,
  0.150224;0.419717;,
  0.150224;0.442749;,
  0.186999;0.465780;,
  0.182093;0.465780;,
  0.186999;0.419717;,
  0.186999;0.442749;,
  0.182093;0.419717;,
  0.193954;0.419717;,
  0.193954;0.442749;,
  0.253980;0.419717;,
  0.253980;0.442749;,
  0.277701;0.465780;,
  0.267890;0.465780;,
  0.160035;0.465780;,
  0.150224;0.465780;,
  0.173945;0.442749;,
  0.173945;0.419717;,
  0.233972;0.465780;,
  0.253980;0.465780;,
  0.213963;0.465780;,
  0.193954;0.465780;,
  0.173945;0.465780;;
 }
}
