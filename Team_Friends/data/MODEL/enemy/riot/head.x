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
 287;
 0.00000;4.41860;-11.68012;,
 0.00000;17.21492;-11.68012;,
 9.04836;17.21492;0.00000;,
 9.04836;4.41860;0.00000;,
 -9.04836;17.21492;0.00000;,
 0.00000;17.21492;11.68012;,
 -9.04836;4.41860;0.00000;,
 0.00000;4.41860;11.68012;,
 0.00000;0.00000;0.00000;,
 6.22948;0.00000;8.04134;,
 0.00000;0.00000;16.08270;,
 -6.22948;0.00000;8.04134;,
 -1.16576;12.67330;-11.06370;,
 -6.47506;13.83488;-8.10690;,
 -6.19930;15.24640;-7.81446;,
 -1.37984;14.08482;-10.77128;,
 -6.19930;15.24640;-4.99142;,
 -2.10766;14.08482;-8.16586;,
 -6.47506;13.83488;-5.28386;,
 -2.38344;12.67330;-8.45830;,
 -1.28186;11.26176;-8.16586;,
 -3.77034;11.26176;-4.99142;,
 -3.77034;11.26176;-7.81446;,
 -0.83920;11.26176;-10.77128;,
 1.16576;12.67330;-11.06370;,
 1.37984;14.08482;-10.77128;,
 6.19930;15.24640;-7.81446;,
 6.47506;13.83488;-8.10690;,
 2.10766;14.08482;-8.16586;,
 6.19930;15.24640;-4.99142;,
 2.38344;12.67330;-8.45830;,
 6.47506;13.83488;-5.28386;,
 1.28186;11.26176;-8.16586;,
 0.83920;11.26176;-10.77128;,
 3.77034;11.26176;-7.81446;,
 3.77034;11.26176;-4.99142;,
 0.00000;13.38206;-13.56236;,
 1.84614;14.49314;-12.73498;,
 1.84614;13.84430;-12.73498;,
 0.00000;12.73322;-13.56236;,
 0.00000;13.38206;-12.32578;,
 1.84614;14.49314;-11.49840;,
 0.00000;12.73322;-12.32578;,
 1.84614;13.84430;-11.49840;,
 7.18382;16.94780;-10.34786;,
 7.18382;17.59664;-10.34786;,
 7.18382;17.59664;-9.11130;,
 7.18382;16.94780;-9.11130;,
 -7.18382;16.94780;-9.11130;,
 -7.18382;17.59664;-9.11130;,
 -7.18382;17.59664;-10.34786;,
 -7.18382;16.94780;-10.34786;,
 -1.84614;13.84430;-12.73498;,
 -1.84614;13.84430;-11.49840;,
 -1.84614;14.49314;-11.49840;,
 -1.84614;14.49314;-12.73498;,
 3.69230;15.60442;-11.97260;,
 3.69230;14.95558;-11.97260;,
 3.69230;15.60442;-10.73602;,
 3.69230;14.95558;-10.73602;,
 -3.69230;14.95558;-10.73602;,
 -3.69230;14.95558;-11.97260;,
 -3.69230;15.60442;-10.73602;,
 -3.69230;15.60442;-11.97260;,
 5.88644;16.27106;-10.91966;,
 5.88644;16.27106;-9.68310;,
 5.88644;16.91990;-9.68310;,
 5.88644;16.91990;-10.91966;,
 -5.88644;16.27106;-9.68310;,
 -5.88644;16.27106;-10.91966;,
 -5.88644;16.91990;-10.91966;,
 -5.88644;16.91990;-9.68310;,
 -6.93398;17.27606;-10.30738;,
 -4.59826;28.99338;-8.23698;,
 -4.12980;28.57520;-8.40272;,
 -6.46552;17.11666;-10.30738;,
 -4.59826;28.99338;-7.76852;,
 -4.12980;28.57520;-7.93426;,
 -6.93398;17.27606;-9.83892;,
 -6.46552;17.11666;-9.83892;,
 0.00000;21.99286;-11.53284;,
 1.09792;23.93652;-10.70546;,
 1.09792;23.28768;-10.70546;,
 0.00000;21.34402;-11.53284;,
 0.00000;21.99286;-10.29628;,
 1.09792;23.93652;-9.46890;,
 0.00000;21.34402;-10.29628;,
 1.09792;23.28768;-9.46890;,
 4.68750;28.92156;-8.31836;,
 4.68750;29.57040;-8.31836;,
 4.68750;29.57040;-7.08178;,
 4.96312;28.92156;-7.08178;,
 -4.96312;28.92156;-7.08178;,
 -4.68750;29.57040;-7.08178;,
 -4.68750;29.57040;-8.31836;,
 -4.68750;28.92156;-8.31836;,
 -1.09792;23.28768;-10.70546;,
 -1.09792;23.28768;-9.46890;,
 -1.09792;23.93652;-9.46890;,
 -1.09792;23.93652;-10.70546;,
 2.02528;25.92004;-9.94308;,
 2.02528;25.27118;-9.94308;,
 2.02528;25.92004;-8.70652;,
 2.02528;25.27118;-8.70652;,
 -2.02528;25.27118;-8.70652;,
 -2.02528;25.27118;-9.94308;,
 -2.02528;25.92004;-8.70652;,
 -2.02528;25.92004;-9.94308;,
 3.58132;27.36858;-8.89016;,
 3.58132;27.36858;-7.65358;,
 3.58132;28.01742;-7.65358;,
 3.58132;28.01742;-8.89016;,
 -3.58132;27.36858;-7.65358;,
 -3.58132;27.36858;-8.89016;,
 -3.58132;28.01742;-8.89016;,
 -3.58132;28.01742;-7.65358;,
 -5.35350;16.37848;-11.01320;,
 -3.49674;27.51808;-8.82292;,
 -3.02828;27.09992;-8.98866;,
 -4.88504;16.21908;-11.01320;,
 -3.49674;27.51808;-8.35446;,
 -3.02828;27.09992;-8.52020;,
 -5.35350;16.37848;-10.54474;,
 -4.88504;16.21908;-10.54474;,
 -3.82798;15.26898;-11.82162;,
 -2.24208;25.59512;-9.63134;,
 -1.77362;25.17692;-9.79708;,
 -3.35952;15.10958;-11.82162;,
 -2.24208;25.59512;-9.16288;,
 -1.77362;25.17692;-9.32862;,
 -3.82798;15.26898;-11.35316;,
 -3.35952;15.10958;-11.35316;,
 -2.18244;14.11288;-12.51664;,
 -1.32924;23.85432;-10.31018;,
 -0.86078;23.43614;-10.69000;,
 -1.71398;13.95350;-12.51664;,
 -1.32924;23.85432;-9.84172;,
 -0.86078;23.43614;-10.22152;,
 -2.18244;14.11288;-12.04818;,
 -1.71398;13.95350;-12.04818;,
 0.21646;13.28004;-13.26802;,
 -0.25200;13.12068;-13.26802;,
 -0.25204;21.90316;-11.27172;,
 0.21304;21.89854;-11.28234;,
 -0.25204;21.90316;-10.97906;,
 0.21304;21.89854;-10.98968;,
 -0.25200;13.12068;-12.79956;,
 0.21646;13.28004;-12.79956;,
 2.18244;14.11288;-12.51664;,
 1.71398;13.95350;-12.51664;,
 0.86078;23.43614;-10.69000;,
 1.32924;23.85432;-10.31018;,
 0.86078;23.43614;-10.22152;,
 1.32924;23.85432;-9.84172;,
 1.71398;13.95350;-12.04818;,
 2.18244;14.11288;-12.04818;,
 3.82798;15.26898;-11.82162;,
 3.35952;15.10958;-11.82162;,
 1.77362;25.17692;-9.79708;,
 2.24208;25.59512;-9.63134;,
 1.77362;25.17692;-9.32862;,
 2.24208;25.59512;-9.16288;,
 3.35952;15.10958;-11.35316;,
 3.82798;15.26898;-11.35316;,
 5.35350;16.37848;-11.01320;,
 4.88504;16.21908;-11.01320;,
 3.02828;27.09992;-8.98866;,
 3.49674;27.51808;-8.82292;,
 3.02828;27.09992;-8.52020;,
 3.49674;27.51808;-8.35446;,
 4.88504;16.21908;-10.54474;,
 5.35350;16.37848;-10.54474;,
 6.93398;17.27606;-10.30738;,
 6.46552;17.11666;-10.30738;,
 4.12980;28.57520;-8.40272;,
 4.59826;28.99338;-8.23698;,
 4.12980;28.57520;-7.93426;,
 4.59826;28.99338;-7.76852;,
 6.46552;17.11666;-9.83892;,
 6.93398;17.27606;-9.83892;,
 0.00000;39.35462;-7.48198;,
 -1.48756;35.70310;-7.95026;,
 -1.48756;36.82426;-7.95026;,
 0.00000;40.47578;-7.48198;,
 0.00000;39.35462;-6.24542;,
 -1.48756;35.70310;-6.71368;,
 0.00000;40.47578;-6.24542;,
 -1.48756;36.82426;-6.71368;,
 -6.35106;27.08920;-8.22316;,
 -6.35106;25.96804;-8.22316;,
 -6.35106;25.96804;-6.98660;,
 -6.72448;27.08920;-6.98660;,
 6.72448;27.08920;-6.98660;,
 6.35106;25.96804;-6.98660;,
 6.35106;25.96804;-8.22316;,
 6.35106;27.08920;-8.22316;,
 1.48756;36.82426;-7.95026;,
 1.48756;36.82426;-6.71368;,
 1.48756;35.70310;-6.71368;,
 1.48756;35.70310;-7.95026;,
 -2.74402;32.27570;-8.28320;,
 -2.74402;33.39686;-8.28320;,
 -2.74402;32.27570;-7.04664;,
 -2.74402;33.39686;-7.04664;,
 2.74402;33.39686;-7.04664;,
 2.74402;33.39686;-8.28320;,
 2.74402;32.27570;-7.04664;,
 2.74402;32.27570;-8.28320;,
 -4.85228;29.77266;-8.43432;,
 -4.85228;29.77266;-7.19776;,
 -4.85228;28.65150;-7.19776;,
 -4.85228;28.65150;-8.43432;,
 4.85228;29.77266;-7.19776;,
 4.85228;29.77266;-8.43432;,
 4.85228;28.65150;-8.43432;,
 4.85228;28.65150;-7.19776;,
 1.71530;77.83162;-1.93260;,
 2.57296;77.83162;-0.96630;,
 5.00602;47.20830;-2.05724;,
 3.33736;46.98938;-3.95994;,
 0.00000;77.83162;1.93260;,
 0.74858;77.83162;0.96630;,
 0.00000;77.83162;0.00000;,
 -0.74858;77.83162;0.96630;,
 -1.33594;47.01810;4.51802;,
 -0.74858;77.83162;2.89890;,
 -1.71530;77.83162;1.93260;,
 -3.06122;46.81834;3.21666;,
 3.18982;15.95846;3.61712;,
 0.00000;16.42464;7.73472;,
 -3.18982;15.95846;3.61712;,
 0.00000;16.05094;0.00000;,
 1.71530;77.83162;1.93260;,
 0.74858;77.83162;2.89890;,
 1.33594;47.01810;4.51802;,
 3.06122;47.01810;3.21666;,
 -2.57296;77.83162;-0.96630;,
 -1.71530;77.83162;-1.93260;,
 -3.33736;46.78962;-3.95994;,
 -5.00602;46.97126;-2.05724;,
 -7.30922;15.92498;0.00000;,
 -3.18982;16.52224;-4.11758;,
 -2.57296;77.83162;0.96630;,
 -4.59184;46.81834;1.49216;,
 -0.74858;77.83162;-0.96630;,
 -1.71530;77.83162;0.00000;,
 0.74858;77.83162;-2.89890;,
 1.33594;45.87804;-4.92794;,
 -12.19158;16.75198;-4.91552;,
 -8.12772;16.21358;-9.56130;,
 -3.43060;77.83162;0.00000;,
 -5.66012;47.12680;-0.06352;,
 0.00000;45.24894;-5.82880;,
 0.00000;77.83162;-3.86520;,
 3.43060;77.83162;0.00000;,
 5.66012;47.36384;-0.06352;,
 0.00000;47.01810;5.43820;,
 0.00000;77.83162;3.86520;,
 7.30922;16.89080;7.73472;,
 3.18982;16.89080;10.59794;,
 -0.74858;77.83162;-2.89890;,
 0.00000;77.83162;-1.93260;,
 0.74858;77.83162;-0.96630;,
 1.71530;77.83162;0.00000;,
 2.57296;77.83162;0.96630;,
 4.59184;47.01810;1.49216;,
 10.96384;16.89080;3.61712;,
 7.30922;16.51710;0.00000;,
 3.18982;16.52224;-4.11758;,
 0.00000;16.33952;-8.23518;,
 -3.18982;13.51142;-11.43642;,
 -1.33594;45.87804;-4.92794;,
 12.19158;17.45458;-4.91552;,
 13.24800;17.91562;0.00000;,
 8.12772;16.80568;-9.56130;,
 3.18982;13.51142;-11.43642;,
 0.00000;11.64672;-13.11256;,
 -13.24800;17.21300;0.00000;,
 -10.96384;16.29868;3.61712;,
 -7.30922;16.29868;7.73472;,
 -3.18982;16.89080;10.59794;,
 0.00000;16.89080;12.33138;,
 -12.45896;0.00000;0.00000;,
 12.45896;0.00000;0.00000;,
 6.22948;0.00000;-8.04134;,
 0.00000;0.00000;-16.08270;,
 -6.22948;0.00000;-8.04134;;
 
 261;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,9,10,11;,
 4;3,2,5,7;,
 4;6,4,1,0;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;20,21,22,23;,
 4;13,18,16,14;,
 4;19,12,15,17;,
 4;23,22,13,12;,
 4;22,21,18,13;,
 4;19,18,21,20;,
 4;20,23,12,19;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;32,33,34,35;,
 4;27,26,29,31;,
 4;30,28,25,24;,
 4;33,24,27,34;,
 4;34,27,31,35;,
 4;30,32,35,31;,
 4;32,30,24,33;,
 4;36,37,38,39;,
 4;40,41,37,36;,
 4;42,43,41,40;,
 4;39,38,43,42;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,39,42,53;,
 4;53,42,40,54;,
 4;54,40,36,55;,
 4;55,36,39,52;,
 4;37,56,57,38;,
 4;41,58,56,37;,
 4;43,59,58,41;,
 4;38,57,59,43;,
 4;60,61,52,53;,
 4;62,60,53,54;,
 4;63,62,54,55;,
 4;61,63,55,52;,
 4;57,64,65,59;,
 4;59,65,66,58;,
 4;58,66,67,56;,
 4;56,67,64,57;,
 4;60,68,69,61;,
 4;61,69,70,63;,
 4;63,70,71,62;,
 4;62,71,68,60;,
 4;64,44,47,65;,
 4;65,47,46,66;,
 4;66,46,45,67;,
 4;67,45,44,64;,
 4;68,48,51,69;,
 4;69,51,50,70;,
 4;70,50,49,71;,
 4;71,49,48,68;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,72,75,79;,
 4;75,74,77,79;,
 4;78,76,73,72;,
 4;80,81,82,83;,
 4;84,85,81,80;,
 4;86,87,85,84;,
 4;83,82,87,86;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,83,86,97;,
 4;97,86,84,98;,
 4;98,84,80,99;,
 4;99,80,83,96;,
 4;81,100,101,82;,
 4;85,102,100,81;,
 4;87,103,102,85;,
 4;82,101,103,87;,
 4;104,105,96,97;,
 4;106,104,97,98;,
 4;107,106,98,99;,
 4;105,107,99,96;,
 4;101,108,109,103;,
 4;103,109,110,102;,
 4;102,110,111,100;,
 4;100,111,108,101;,
 4;104,112,113,105;,
 4;105,113,114,107;,
 4;107,114,115,106;,
 4;106,115,112,104;,
 4;108,88,91,109;,
 4;109,91,90,110;,
 4;110,90,89,111;,
 4;111,89,88,108;,
 4;112,92,95,113;,
 4;113,95,94,114;,
 4;114,94,93,115;,
 4;115,93,92,112;,
 4;116,117,118,119;,
 4;117,120,121,118;,
 4;120,122,123,121;,
 4;122,116,119,123;,
 4;119,118,121,123;,
 4;122,120,117,116;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,124,127,131;,
 4;127,126,129,131;,
 4;130,128,125,124;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;136,138,139,137;,
 4;138,132,135,139;,
 4;135,134,137,139;,
 4;138,136,133,132;,
 4;140,141,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 4;147,146,141,140;,
 4;141,146,144,142;,
 4;147,140,143,145;,
 4;148,149,150,151;,
 4;151,150,152,153;,
 4;153,152,154,155;,
 4;155,154,149,148;,
 4;149,154,152,150;,
 4;155,148,151,153;,
 4;156,157,158,159;,
 4;159,158,160,161;,
 4;161,160,162,163;,
 4;163,162,157,156;,
 4;157,162,160,158;,
 4;163,156,159,161;,
 4;164,165,166,167;,
 4;167,166,168,169;,
 4;169,168,170,171;,
 4;171,170,165,164;,
 4;165,170,168,166;,
 4;171,164,167,169;,
 4;172,173,174,175;,
 4;175,174,176,177;,
 4;177,176,178,179;,
 4;179,178,173,172;,
 4;173,178,176,174;,
 4;179,172,175,177;,
 4;180,181,182,183;,
 4;184,185,181,180;,
 4;186,187,185,184;,
 4;183,182,187,186;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,183,186,197;,
 4;197,186,184,198;,
 4;198,184,180,199;,
 4;199,180,183,196;,
 4;181,200,201,182;,
 4;185,202,200,181;,
 4;187,203,202,185;,
 4;182,201,203,187;,
 4;204,205,196,197;,
 4;206,204,197,198;,
 4;207,206,198,199;,
 4;205,207,199,196;,
 4;201,208,209,203;,
 4;203,209,210,202;,
 4;202,210,211,200;,
 4;200,211,208,201;,
 4;204,212,213,205;,
 4;205,213,214,207;,
 4;207,214,215,206;,
 4;206,215,212,204;,
 4;208,188,191,209;,
 4;209,191,190,210;,
 4;210,190,189,211;,
 4;211,189,188,208;,
 4;212,192,195,213;,
 4;213,195,194,214;,
 4;214,194,193,215;,
 4;215,193,192,212;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;231,230,240,241;,
 4;227,226,242,243;,
 4;223,222,244,245;,
 4;246,216,219,247;,
 4;248,249,241,240;,
 4;250,251,243,242;,
 4;237,236,245,244;,
 4;252,253,246,247;,
 4;217,254,255,218;,
 4;233,232,221,220;,
 4;256,257,225,224;,
 4;258,259,229,228;,
 4;260,237,244,261;,
 4;222,262,261,244;,
 4;221,263,262,222;,
 4;232,264,263,221;,
 4;264,232,235,265;,
 4;266,258,228,267;,
 4;267,228,231,268;,
 4;268,231,241,269;,
 4;249,270,269,241;,
 4;237,260,271,238;,
 4;253,260,261,246;,
 4;262,216,246,261;,
 4;263,217,216,262;,
 4;264,254,217,263;,
 4;255,254,264,265;,
 4;272,273,266,267;,
 4;274,272,267,268;,
 4;275,274,268,269;,
 4;270,276,275,269;,
 4;260,253,252,271;,
 4;277,248,240,278;,
 4;230,279,278,240;,
 4;229,280,279,230;,
 4;259,281,280,229;,
 4;233,257,256,234;,
 4;225,257,233,220;,
 4;226,225,220,223;,
 4;242,226,223,245;,
 4;236,250,242,245;,
 4;251,250,236,239;,
 4;276,252,247,275;,
 4;219,274,275,247;,
 4;218,272,274,219;,
 4;255,273,272,218;,
 4;273,255,265,266;,
 4;235,258,266,265;,
 4;234,259,258,235;,
 4;256,281,259,234;,
 4;280,281,256,224;,
 4;279,280,224,227;,
 4;278,279,227,243;,
 4;251,277,278,243;,
 4;277,251,239,248;,
 4;238,249,248,239;,
 4;271,270,249,238;,
 4;252,276,270,271;,
 3;282,11,6;,
 3;6,11,7;,
 3;7,11,10;,
 3;10,9,7;,
 3;7,9,3;,
 3;3,9,283;,
 3;3,283,0;,
 3;283,284,0;,
 3;0,284,285;,
 3;285,286,0;,
 3;0,286,6;,
 3;6,286,282;,
 4;284,283,9,8;,
 4;286,285,284,8;,
 4;282,286,8,11;;
 
 MeshMaterialList {
  1;
  261;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "riot_UV.jpg";
   }
  }
 }
 MeshNormals {
  329;
  0.723902;0.401843;-0.560793;,
  0.761060;0.270528;-0.589578;,
  0.790537;0.000000;-0.612414;,
  0.000000;1.000000;0.000000;,
  -0.737798;0.359131;0.571558;,
  -0.737799;0.359131;0.571558;,
  0.000000;-1.000000;-0.000000;,
  -0.371138;-0.928578;0.000000;,
  -0.462304;0.188909;-0.866365;,
  0.275984;0.960374;0.038922;,
  -0.560642;-0.137875;-0.816499;,
  0.648825;0.201957;0.733648;,
  0.818283;0.204456;0.537225;,
  0.371138;-0.928578;-0.000000;,
  0.462304;0.188909;-0.866365;,
  -0.275984;0.960374;0.038922;,
  0.560642;-0.137875;-0.816499;,
  -0.648825;0.201957;0.733648;,
  -0.818283;0.204456;0.537225;,
  -0.514963;-0.857213;0.000000;,
  0.407328;0.000000;-0.913282;,
  0.514963;0.857212;0.000000;,
  0.407324;0.000000;0.913284;,
  -0.514963;0.857212;0.000000;,
  -0.407324;0.000000;0.913284;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.515654;0.856797;0.000000;,
  0.395375;0.000000;-0.918520;,
  -0.515686;0.856778;0.000000;,
  -0.395375;0.000000;0.918520;,
  -0.515686;-0.856778;0.000000;,
  0.395375;0.000000;0.918520;,
  0.515686;0.856778;0.000000;,
  0.488560;-0.872530;-0.000000;,
  -0.418026;0.000000;0.908435;,
  -0.488560;0.872530;0.000000;,
  -0.488560;-0.872530;0.000000;,
  -0.418030;0.000000;-0.908433;,
  0.488560;0.872530;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.054624;0.179141;-0.982306;,
  0.665938;0.746007;0.000000;,
  0.054624;-0.179141;0.982306;,
  -0.837151;-0.293808;-0.461363;,
  0.837151;-0.293808;-0.461363;,
  0.858829;0.512262;0.000000;,
  0.598384;0.000000;-0.801210;,
  0.837152;0.293808;0.461361;,
  -0.837152;0.293808;0.461361;,
  -0.858829;-0.512262;0.000000;,
  -0.598387;0.000000;0.801207;,
  0.843438;-0.281712;-0.457439;,
  -0.843439;-0.281712;0.457438;,
  -0.843439;0.281712;0.457438;,
  0.843438;0.281712;-0.457439;,
  0.856208;-0.260081;-0.446393;,
  0.618578;0.000000;-0.785723;,
  -0.856208;0.260079;0.446393;,
  -0.618578;0.000000;0.785723;,
  -0.856208;-0.260081;-0.446393;,
  -0.888942;-0.458019;0.000000;,
  0.856208;0.260079;0.446393;,
  0.888943;0.458018;0.000000;,
  0.799196;-0.599535;-0.042928;,
  -0.456240;-0.032789;0.889253;,
  -0.808844;0.588023;0.000000;,
  -0.799196;-0.599535;-0.042928;,
  -0.510693;0.000000;-0.859763;,
  0.808844;0.588023;0.000000;,
  0.969455;-0.222368;-0.103487;,
  0.888447;-0.161788;-0.429520;,
  0.975096;0.196390;-0.103047;,
  0.817448;0.111929;-0.565022;,
  -0.969455;-0.222368;-0.103487;,
  -0.888447;-0.161788;-0.429520;,
  -0.817448;0.111929;-0.565022;,
  -0.975096;0.196390;-0.103047;,
  -0.045739;0.194927;-0.979751;,
  0.665918;0.746025;0.000000;,
  0.943907;0.330211;0.000000;,
  0.045739;-0.194927;0.979751;,
  -0.038087;0.207628;-0.977466;,
  0.665954;0.745993;0.000000;,
  0.941787;0.336210;0.000000;,
  0.038087;-0.207628;0.977466;,
  -0.216410;0.217166;-0.951843;,
  0.665937;0.746008;0.000000;,
  0.930083;0.367349;0.000000;,
  0.216395;-0.217167;0.951847;,
  -0.047621;0.222828;-0.973694;,
  0.009934;0.999951;0.000000;,
  0.044606;-0.204039;0.977946;,
  0.216410;0.217166;-0.951843;,
  -0.665937;0.746008;0.000000;,
  -0.930083;0.367349;0.000000;,
  -0.216395;-0.217167;0.951847;,
  0.038087;0.207628;-0.977466;,
  -0.665954;0.745993;0.000000;,
  -0.941787;0.336210;0.000000;,
  -0.038087;-0.207628;0.977466;,
  0.045739;0.194927;-0.979751;,
  -0.665918;0.746025;0.000000;,
  -0.943907;0.330211;0.000000;,
  -0.045739;-0.194927;0.979751;,
  0.054624;0.179141;-0.982306;,
  -0.665938;0.746007;0.000000;,
  -0.054624;-0.179141;0.982306;,
  0.905124;0.425147;0.000000;,
  0.164542;0.000000;-0.986370;,
  -0.905125;-0.425146;0.000000;,
  0.164549;0.000000;0.986369;,
  0.905125;-0.425146;-0.000000;,
  -0.164549;0.000000;0.986369;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.926101;-0.377276;-0.000000;,
  0.278280;0.000000;-0.960500;,
  0.932647;-0.360792;-0.000000;,
  -0.278281;0.000000;0.960500;,
  0.932647;0.360792;0.000000;,
  0.278281;0.000000;0.960500;,
  -0.932647;-0.360792;0.000000;,
  -0.856777;0.512023;-0.061363;,
  0.014302;0.007346;0.999871;,
  0.868754;-0.495245;-0.000000;,
  0.856777;0.512023;-0.061363;,
  0.034198;0.000000;-0.999415;,
  -0.868754;-0.495245;0.000000;,
  -0.970980;0.193747;-0.140212;,
  -0.977769;-0.155342;-0.140845;,
  0.970980;0.193747;-0.140212;,
  0.977769;-0.155342;-0.140845;,
  0.000000;-0.720611;0.693340;,
  0.228996;-0.972427;-0.044127;,
  0.675258;0.052700;-0.735696;,
  0.863094;0.072644;-0.499792;,
  -0.783132;0.057973;0.619147;,
  -0.686337;0.045135;0.725882;,
  -0.211838;-0.976737;-0.033310;,
  0.000000;-0.994897;0.100895;,
  0.112103;-0.974530;0.194228;,
  -0.016054;-0.995775;0.090408;,
  -0.703298;0.057521;0.708564;,
  0.659357;0.079774;-0.747586;,
  0.059984;-0.827627;0.558064;,
  -0.128619;-0.991666;0.007483;,
  -0.765154;0.058927;0.641145;,
  0.621274;0.064332;-0.780948;,
  0.165246;-0.985641;-0.034725;,
  0.808099;0.078089;-0.583848;,
  -0.671921;0.050067;0.738929;,
  0.006100;-0.993154;0.116651;,
  -0.660725;0.079296;-0.746428;,
  0.702271;0.058700;0.709486;,
  0.086988;-0.992121;0.090161;,
  0.059516;-0.997512;0.037778;,
  0.020196;-0.999241;-0.033296;,
  0.007055;-0.998070;0.061696;,
  0.005384;-0.984205;0.176951;,
  0.172420;-0.985022;0.001911;,
  0.127415;-0.991567;-0.023680;,
  0.072071;-0.994994;0.069235;,
  0.039346;-0.925729;0.376134;,
  0.016784;-0.837304;0.546480;,
  -0.117680;-0.992469;-0.034020;,
  -0.065656;-0.997596;-0.022156;,
  -0.003730;-0.999233;0.038980;,
  0.017780;-0.994590;0.102346;,
  0.029443;-0.992744;0.116589;,
  0.670865;0.051047;0.739820;,
  -0.808327;0.077511;-0.583609;,
  0.256577;0.171042;-0.951269;,
  0.492484;0.137450;-0.859399;,
  0.590937;0.156213;-0.791449;,
  0.830170;0.161713;-0.533542;,
  0.977498;0.197146;-0.075037;,
  0.766231;0.131868;0.628888;,
  0.681854;0.130048;0.719835;,
  0.610876;0.125285;0.781751;,
  -0.604524;0.122264;0.787148;,
  -0.615593;0.123944;0.778256;,
  -0.686265;0.127910;0.716017;,
  -0.767300;0.130473;0.627876;,
  -0.923276;0.184275;0.337053;,
  -0.831156;0.159662;-0.532623;,
  -0.596854;0.154765;-0.787282;,
  -0.497818;0.137084;-0.856379;,
  -0.674826;0.520880;0.522775;,
  0.674826;0.520880;0.522775;,
  0.674827;0.520879;-0.522775;,
  -0.674826;0.520880;-0.522775;,
  0.674827;0.520879;-0.522775;,
  -0.790537;0.000000;0.612414;,
  0.737798;0.359131;0.571558;,
  0.790537;0.000000;0.612414;,
  0.737799;0.359131;0.571558;,
  -0.737798;0.359131;-0.571558;,
  -0.790537;0.000000;-0.612414;,
  -0.737799;0.359131;-0.571558;,
  0.775445;-0.192354;0.601403;,
  0.540962;-0.270667;0.796304;,
  -0.952730;-0.303817;0.000000;,
  -0.981446;0.191739;0.000000;,
  0.925546;0.194628;0.324785;,
  0.933080;-0.094977;0.346902;,
  -0.592295;-0.448259;-0.669515;,
  0.601662;0.626327;0.495699;,
  0.732821;0.556211;0.391920;,
  0.839879;0.467803;0.275252;,
  -0.775445;-0.192354;0.601403;,
  -0.540962;-0.270667;0.796304;,
  0.952730;-0.303817;-0.000000;,
  0.981446;0.191739;0.000000;,
  -0.933080;-0.094977;0.346902;,
  -0.925546;0.194628;0.324785;,
  0.592295;-0.448259;-0.669515;,
  -0.732821;0.556211;0.391920;,
  -0.601662;0.626327;0.495699;,
  -0.839879;0.467803;0.275252;,
  0.515654;-0.856797;-0.000000;,
  0.515686;-0.856778;-0.000000;,
  -0.515654;-0.856797;0.000000;,
  0.515654;0.856797;0.000000;,
  -0.395375;0.000000;-0.918520;,
  0.514963;-0.857213;-0.000000;,
  -0.407328;0.000000;-0.913282;,
  0.418030;0.000000;-0.908433;,
  0.418026;0.000000;0.908435;,
  0.462483;-0.886628;-0.000000;,
  -0.403302;0.000000;0.915067;,
  -0.462483;0.886628;0.000000;,
  0.403302;0.000000;-0.915067;,
  -0.462483;-0.886628;0.000000;,
  -0.403302;0.000000;-0.915067;,
  0.462483;0.886628;0.000000;,
  0.403302;0.000000;0.915067;,
  -0.322129;-0.946696;0.000000;,
  0.979850;-0.199734;-0.000000;,
  -0.980705;0.195493;0.000000;,
  -0.888943;0.458018;0.000000;,
  -0.843438;0.281712;-0.457439;,
  0.888942;-0.458019;-0.000000;,
  0.843439;-0.281712;0.457438;,
  -0.843438;-0.281712;-0.457439;,
  0.618578;0.000000;0.785723;,
  0.843439;0.281712;0.457438;,
  -0.618578;0.000000;-0.785723;,
  -0.858829;0.512262;0.000000;,
  0.858829;-0.512262;-0.000000;,
  0.598387;0.000000;0.801207;,
  -0.598384;0.000000;-0.801210;,
  0.510693;0.000000;-0.859763;,
  0.456240;-0.032789;0.889253;,
  -0.344908;-0.065065;0.936379;,
  -0.814500;0.580164;0.000000;,
  0.814500;0.580164;0.000000;,
  0.344908;-0.065065;0.936379;,
  -0.322128;-0.946696;0.000000;,
  0.985751;-0.168213;-0.000000;,
  -0.986392;0.164413;0.000000;,
  -0.322128;-0.946696;0.000000;,
  0.987819;-0.155610;-0.000000;,
  -0.988411;0.151801;0.000000;,
  -0.322090;-0.946709;0.000000;,
  0.995977;-0.089613;-0.000000;,
  -0.996186;0.087251;0.000000;,
  0.322054;-0.946721;-0.000000;,
  -1.000000;-0.000005;0.000000;,
  1.000000;0.000397;0.000000;,
  0.322090;-0.946709;-0.000000;,
  -0.995977;-0.089613;0.000000;,
  0.996186;0.087251;0.000000;,
  0.322128;-0.946696;-0.000000;,
  -0.987819;-0.155610;0.000000;,
  0.988411;0.151801;0.000000;,
  0.322128;-0.946696;-0.000000;,
  -0.985751;-0.168213;0.000000;,
  0.986392;0.164413;0.000000;,
  0.322129;-0.946696;-0.000000;,
  -0.979850;-0.199734;0.000000;,
  0.980705;0.195493;0.000000;,
  -0.926101;0.377276;0.000000;,
  -0.932647;0.360792;0.000000;,
  0.926101;0.377276;0.000000;,
  -0.926101;-0.377276;0.000000;,
  -0.278280;0.000000;-0.960500;,
  -0.905124;0.425147;0.000000;,
  -0.164542;0.000000;-0.986370;,
  -0.034198;0.000000;-0.999415;,
  -0.014302;0.007346;0.999871;,
  0.099995;0.014637;0.994880;,
  0.873054;-0.487623;-0.000000;,
  -0.139510;0.000000;-0.990221;,
  0.139510;0.000000;-0.990221;,
  -0.873054;-0.487623;0.000000;,
  -0.099995;0.014637;0.994880;,
  0.764926;0.059316;0.641381;,
  -0.622435;0.064156;-0.780037;,
  0.782707;0.058364;0.619647;,
  -0.675258;0.052700;-0.735696;,
  0.686337;0.045135;0.725882;,
  0.604524;0.122264;0.787148;,
  -0.863143;0.072088;-0.499788;,
  0.000000;0.219344;-0.975648;,
  0.349767;0.206750;-0.913738;,
  0.512884;0.232808;-0.826287;,
  0.844120;0.245339;-0.476728;,
  0.954136;0.248596;0.166806;,
  0.763379;0.203762;0.612972;,
  0.657514;0.200922;0.726158;,
  0.544214;0.198196;0.815199;,
  0.512799;0.197387;0.835509;,
  -0.552939;0.196628;0.809689;,
  -0.512799;0.197387;0.835509;,
  -0.665534;0.197806;0.719679;,
  -0.765375;0.201392;0.611263;,
  -0.955448;0.245079;0.164485;,
  -0.845986;0.241801;-0.475226;,
  -0.524197;0.230382;-0.819843;,
  -0.359931;0.206351;-0.909873;,
  -0.674826;0.520880;0.522775;,
  -0.674827;0.520879;0.522775;,
  0.674827;0.520879;0.522775;,
  0.674826;0.520880;0.522775;,
  0.674827;0.520879;-0.522775;,
  -0.674827;0.520879;-0.522775;,
  -0.674826;0.520880;-0.522775;;
  261;
  4;0,2,2,1;,
  4;3,3,3,3;,
  4;194,4,5,194;,
  4;6,6,6,6;,
  4;195,196,196,197;,
  4;198,199,199,200;,
  4;10,10,8,8;,
  4;9,9,9,9;,
  4;201,202,11,12;,
  4;6,7,7,6;,
  4;203,203,204,204;,
  4;12,205,206,201;,
  4;207,207,10,10;,
  4;7,7,203,203;,
  4;12,11,208,209;,
  4;209,210,205,12;,
  4;16,14,14,16;,
  4;15,15,15,15;,
  4;211,18,17,212;,
  4;6,6,13,13;,
  4;213,214,214,213;,
  4;18,211,215,216;,
  4;217,16,16,217;,
  4;13,213,213,13;,
  4;18,218,219,17;,
  4;218,18,216,220;,
  4;25,28,28,25;,
  4;27,29,29,27;,
  4;26,30,30,26;,
  4;221,222,222,221;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;31,223,223,31;,
  4;32,26,26,32;,
  4;33,224,224,33;,
  4;225,25,25,225;,
  4;28,20,20,28;,
  4;29,23,23,29;,
  4;30,24,24,30;,
  4;222,226,226,222;,
  4;19,19,31,31;,
  4;22,22,32,32;,
  4;21,21,33,33;,
  4;227,227,225,225;,
  4;226,34,34,226;,
  4;24,35,35,24;,
  4;23,36,36,23;,
  4;20,228,228,20;,
  4;19,37,37,19;,
  4;227,38,38,227;,
  4;21,39,39,21;,
  4;22,229,229,22;,
  4;34,230,230,34;,
  4;35,231,231,35;,
  4;36,232,232,36;,
  4;228,233,233,228;,
  4;37,234,234,37;,
  4;38,235,235,38;,
  4;39,236,236,39;,
  4;229,237,237,229;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;238,238,238,238;,
  4;239,239,239,239;,
  4;240,240,240,240;,
  4;56,58,57,53;,
  4;55,59,241,242;,
  4;54,60,59,55;,
  4;53,57,243,244;,
  4;72,74,73,71;,
  4;75,78,77,76;,
  4;61,245,54,62;,
  4;246,244,247,63;,
  4;63,247,56,64;,
  4;248,242,245,61;,
  4;58,48,46,57;,
  4;59,50,249,241;,
  4;60,52,50,59;,
  4;57,46,250,243;,
  4;51,45,61,62;,
  4;49,251,246,63;,
  4;47,49,63,64;,
  4;45,252,248,61;,
  4;46,65,65,250;,
  4;52,66,66,50;,
  4;50,67,67,249;,
  4;48,253,253,46;,
  4;51,68,68,45;,
  4;45,69,69,252;,
  4;47,70,70,49;,
  4;49,254,254,251;,
  4;65,72,71,65;,
  4;66,255,255,66;,
  4;67,256,256,67;,
  4;253,74,72,253;,
  4;68,75,76,68;,
  4;69,76,77,69;,
  4;70,257,257,70;,
  4;254,258,258,254;,
  4;79,79,79,79;,
  4;80,80,81,81;,
  4;82,82,82,82;,
  4;259,259,259,259;,
  4;260,81,81,260;,
  4;261,261,261,261;,
  4;83,83,83,83;,
  4;84,84,85,85;,
  4;86,86,86,86;,
  4;262,262,262,262;,
  4;263,85,85,263;,
  4;264,264,264,264;,
  4;87,87,87,87;,
  4;88,88,89,89;,
  4;90,90,90,90;,
  4;265,265,265,265;,
  4;266,89,89,266;,
  4;267,267,267,267;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;268,268,268,268;,
  4;269,269,269,269;,
  4;270,270,270,270;,
  4;94,94,94,94;,
  4;95,96,96,95;,
  4;97,97,97,97;,
  4;271,271,271,271;,
  4;272,272,96,96;,
  4;273,273,273,273;,
  4;98,98,98,98;,
  4;99,100,100,99;,
  4;101,101,101,101;,
  4;274,274,274,274;,
  4;275,275,100,100;,
  4;276,276,276,276;,
  4;102,102,102,102;,
  4;103,104,104,103;,
  4;105,105,105,105;,
  4;277,277,277,277;,
  4;278,278,104,104;,
  4;279,279,279,279;,
  4;106,106,106,106;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;280,280,280,280;,
  4;281,281,281,281;,
  4;282,282,282,282;,
  4;115,118,118,115;,
  4;117,119,119,117;,
  4;116,120,120,116;,
  4;283,284,284,283;,
  4;130,131,131,130;,
  4;132,133,133,132;,
  4;121,285,285,121;,
  4;122,116,116,122;,
  4;123,286,286,123;,
  4;287,115,115,287;,
  4;118,110,110,118;,
  4;119,113,113,119;,
  4;120,114,114,120;,
  4;284,288,288,284;,
  4;109,109,121,121;,
  4;112,112,122,122;,
  4;111,111,123,123;,
  4;289,289,287,287;,
  4;288,124,124,288;,
  4;114,125,125,114;,
  4;113,126,126,113;,
  4;110,290,290,110;,
  4;109,127,127,109;,
  4;289,128,128,289;,
  4;111,129,129,111;,
  4;112,291,291,112;,
  4;124,130,130,124;,
  4;125,292,292,125;,
  4;126,293,293,126;,
  4;290,294,294,290;,
  4;127,132,132,127;,
  4;128,295,295,128;,
  4;129,296,296,129;,
  4;291,297,297,291;,
  4;145,151,176,175;,
  4;3,3,3,3;,
  4;182,152,144,183;,
  4;157,169,168,158;,
  4;155,171,180,179;,
  4;172,154,187,186;,
  4;158,168,167,159;,
  4;183,144,148,184;,
  4;3,3,3,3;,
  4;149,145,175,174;,
  4;166,160,159,167;,
  4;138,185,184,148;,
  4;3,3,3,3;,
  4;173,136,149,174;,
  4;151,137,177,176;,
  4;3,3,3,3;,
  4;181,139,152,182;,
  4;156,170,169,157;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;298,155,179,178;,
  4;161,156,157,162;,
  4;162,157,158,163;,
  4;163,158,159,164;,
  4;160,165,164,159;,
  4;154,299,188,187;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;300,300,298,178;,
  4;150,135,161,162;,
  4;142,150,162,163;,
  4;146,142,163,164;,
  4;165,134,146,164;,
  4;299,301,301,188;,
  4;140,166,167,147;,
  4;168,143,147,167;,
  4;169,153,143,168;,
  4;170,141,153,169;,
  4;171,302,303,180;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;304,304,172,186;,
  4;305,173,174,306;,
  4;175,307,306,174;,
  4;176,308,307,175;,
  4;177,309,308,176;,
  4;309,177,178,310;,
  4;179,311,310,178;,
  4;180,312,311,179;,
  4;303,313,312,180;,
  4;314,315,181,182;,
  4;316,314,182,183;,
  4;317,316,183,184;,
  4;185,318,317,184;,
  4;318,185,186,319;,
  4;187,320,319,186;,
  4;188,321,320,187;,
  4;173,305,321,188;,
  3;189,322,4;,
  3;4,322,5;,
  3;5,322,323;,
  3;324,325,197;,
  3;197,325,195;,
  3;195,325,190;,
  3;1,326,0;,
  3;326,193,0;,
  3;0,193,191;,
  3;327,192,200;,
  3;200,192,198;,
  3;198,192,328;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;;
 }
 MeshTextureCoords {
  287;
  0.721670;0.952796;,
  0.721670;0.578287;,
  0.908924;0.578287;,
  0.908924;0.952796;,
  0.534415;0.578287;,
  0.721670;0.578287;,
  0.534415;0.952796;,
  0.721670;0.952796;,
  0.721670;0.952796;,
  0.815297;0.952796;,
  0.721670;0.952796;,
  0.628042;0.952796;,
  0.290222;0.897708;,
  0.092653;0.836571;,
  0.102915;0.762280;,
  0.282256;0.823417;,
  0.102915;0.762280;,
  0.255172;0.823417;,
  0.092653;0.836571;,
  0.244910;0.897708;,
  0.285902;0.972001;,
  0.193301;0.972001;,
  0.193301;0.972001;,
  0.302374;0.972001;,
  0.116514;0.881516;,
  0.123871;0.812907;,
  0.289494;0.756446;,
  0.298971;0.825055;,
  0.148883;0.812907;,
  0.289494;0.756446;,
  0.158360;0.881516;,
  0.298971;0.825055;,
  0.120504;0.950126;,
  0.105292;0.950126;,
  0.206022;0.950126;,
  0.206022;0.950126;,
  0.211368;0.672625;,
  0.248569;0.661030;,
  0.248569;0.667801;,
  0.211368;0.679396;,
  0.211368;0.672625;,
  0.248569;0.661030;,
  0.211368;0.679396;,
  0.248569;0.667801;,
  0.356128;0.635413;,
  0.356128;0.628641;,
  0.356128;0.628641;,
  0.356128;0.635413;,
  0.066607;0.635413;,
  0.066607;0.628641;,
  0.066607;0.628641;,
  0.066607;0.635413;,
  0.174166;0.667801;,
  0.174166;0.667801;,
  0.174166;0.661030;,
  0.174166;0.661030;,
  0.285771;0.649432;,
  0.285771;0.656204;,
  0.285771;0.649432;,
  0.285771;0.656204;,
  0.136965;0.656204;,
  0.136965;0.656204;,
  0.136965;0.649432;,
  0.136965;0.649432;,
  0.329985;0.642475;,
  0.329985;0.642475;,
  0.329985;0.635704;,
  0.329985;0.635704;,
  0.092751;0.642475;,
  0.092751;0.642475;,
  0.092751;0.635704;,
  0.092751;0.635704;,
  0.071642;0.631987;,
  0.118709;0.509706;,
  0.128149;0.514070;,
  0.081082;0.633651;,
  0.118709;0.509706;,
  0.128149;0.514070;,
  0.071642;0.631987;,
  0.081082;0.633651;,
  0.211368;0.582763;,
  0.233492;0.562479;,
  0.233492;0.569250;,
  0.211368;0.589534;,
  0.211368;0.582763;,
  0.233492;0.562479;,
  0.211368;0.589534;,
  0.233492;0.569250;,
  0.305825;0.510455;,
  0.305825;0.503684;,
  0.305825;0.503684;,
  0.311379;0.510455;,
  0.111356;0.510455;,
  0.116910;0.503684;,
  0.116910;0.503684;,
  0.116910;0.510455;,
  0.189244;0.569250;,
  0.189244;0.569250;,
  0.189244;0.562479;,
  0.189244;0.562479;,
  0.252179;0.541779;,
  0.252179;0.548550;,
  0.252179;0.541779;,
  0.252179;0.548550;,
  0.170557;0.548550;,
  0.170557;0.548550;,
  0.170557;0.541779;,
  0.170557;0.541779;,
  0.283534;0.526662;,
  0.283534;0.526662;,
  0.283534;0.519891;,
  0.283534;0.519891;,
  0.139201;0.526662;,
  0.139201;0.526662;,
  0.139201;0.519891;,
  0.139201;0.519891;,
  0.103490;0.641354;,
  0.140905;0.525102;,
  0.150345;0.529466;,
  0.112930;0.643018;,
  0.140905;0.525102;,
  0.150345;0.529466;,
  0.103490;0.641354;,
  0.112930;0.643018;,
  0.134230;0.652933;,
  0.166188;0.545170;,
  0.175628;0.549534;,
  0.143670;0.654596;,
  0.166188;0.545170;,
  0.175628;0.549534;,
  0.134230;0.652933;,
  0.143670;0.654596;,
  0.167389;0.664998;,
  0.184582;0.563337;,
  0.194022;0.567701;,
  0.176829;0.666661;,
  0.184582;0.563337;,
  0.194022;0.567701;,
  0.167389;0.664998;,
  0.176829;0.666661;,
  0.215730;0.673689;,
  0.206290;0.675353;,
  0.206289;0.583699;,
  0.215661;0.583747;,
  0.206289;0.583699;,
  0.215661;0.583747;,
  0.206290;0.675353;,
  0.215730;0.673689;,
  0.255346;0.664998;,
  0.245906;0.666661;,
  0.228713;0.567701;,
  0.238153;0.563337;,
  0.228713;0.567701;,
  0.238153;0.563337;,
  0.245906;0.666661;,
  0.255346;0.664998;,
  0.288505;0.652933;,
  0.279065;0.654596;,
  0.247108;0.549534;,
  0.256548;0.545170;,
  0.247108;0.549534;,
  0.256548;0.545170;,
  0.279065;0.654596;,
  0.288505;0.652933;,
  0.319245;0.641354;,
  0.309806;0.643018;,
  0.272390;0.529466;,
  0.281830;0.525102;,
  0.272390;0.529466;,
  0.281830;0.525102;,
  0.309806;0.643018;,
  0.319245;0.641354;,
  0.351093;0.631987;,
  0.341653;0.633651;,
  0.294587;0.514070;,
  0.304027;0.509706;,
  0.294587;0.514070;,
  0.304027;0.509706;,
  0.341653;0.633651;,
  0.351093;0.631987;,
  0.211368;0.401576;,
  0.181392;0.439683;,
  0.181392;0.427983;,
  0.211368;0.389876;,
  0.211368;0.401576;,
  0.181392;0.439683;,
  0.211368;0.389876;,
  0.181392;0.427983;,
  0.083388;0.529578;,
  0.083388;0.541278;,
  0.083388;0.541278;,
  0.075864;0.529578;,
  0.346872;0.529578;,
  0.339347;0.541278;,
  0.339347;0.541278;,
  0.339347;0.529578;,
  0.241343;0.427983;,
  0.241343;0.427983;,
  0.241343;0.439683;,
  0.241343;0.439683;,
  0.156073;0.475451;,
  0.156073;0.463751;,
  0.156073;0.475451;,
  0.156073;0.463751;,
  0.266662;0.463751;,
  0.266662;0.463751;,
  0.266662;0.475451;,
  0.266662;0.475451;,
  0.113590;0.501573;,
  0.113590;0.501573;,
  0.113590;0.513273;,
  0.113590;0.513273;,
  0.309145;0.501573;,
  0.309145;0.501573;,
  0.309145;0.513273;,
  0.309145;0.513273;,
  0.758191;0.032718;,
  0.767215;0.032718;,
  0.792816;0.161713;,
  0.775258;0.162635;,
  0.740142;0.032718;,
  0.748019;0.032718;,
  0.740142;0.032718;,
  0.732266;0.032718;,
  0.726085;0.162514;,
  0.732266;0.032718;,
  0.722094;0.032718;,
  0.707932;0.163356;,
  0.773705;0.293347;,
  0.740142;0.291383;,
  0.706579;0.293347;,
  0.740142;0.292957;,
  0.758191;0.032718;,
  0.748019;0.032718;,
  0.754199;0.162514;,
  0.772352;0.162514;,
  0.713069;0.032718;,
  0.722094;0.032718;,
  0.705027;0.163477;,
  0.687469;0.162711;,
  0.663234;0.293488;,
  0.706579;0.290972;,
  0.713069;0.032718;,
  0.691827;0.163356;,
  0.732266;0.032718;,
  0.722094;0.032718;,
  0.748019;0.032718;,
  0.754199;0.167316;,
  0.611862;0.290004;,
  0.654622;0.292272;,
  0.704045;0.032718;,
  0.680586;0.162056;,
  0.740142;0.169966;,
  0.740142;0.032718;,
  0.776239;0.032718;,
  0.799698;0.161058;,
  0.740142;0.162514;,
  0.740142;0.032718;,
  0.817050;0.289420;,
  0.773705;0.289420;,
  0.732266;0.032718;,
  0.740142;0.032718;,
  0.748019;0.032718;,
  0.758191;0.032718;,
  0.767215;0.032718;,
  0.788458;0.162514;,
  0.855504;0.289420;,
  0.817050;0.290994;,
  0.773705;0.290972;,
  0.740142;0.291742;,
  0.706579;0.303655;,
  0.726085;0.167316;,
  0.868422;0.287045;,
  0.879538;0.285103;,
  0.825662;0.289778;,
  0.773705;0.303655;,
  0.740142;0.311509;,
  0.600747;0.288062;,
  0.624781;0.291914;,
  0.663234;0.291914;,
  0.706579;0.289420;,
  0.740142;0.289420;,
  0.534415;0.952796;,
  0.908924;0.952796;,
  0.815297;0.952796;,
  0.721670;0.952796;,
  0.628042;0.952796;;
 }
}
