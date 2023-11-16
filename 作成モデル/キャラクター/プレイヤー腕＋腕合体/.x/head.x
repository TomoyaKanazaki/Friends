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
 290;
 0.00000;10.46161;-3.00399;,
 4.77251;10.46161;-0.10965;,
 4.77251;7.86862;-0.10965;,
 0.00000;7.86862;-3.00399;,
 0.00000;10.46161;6.19771;,
 4.77251;10.46161;6.19771;,
 0.00000;7.86862;6.19771;,
 4.77251;7.86862;6.19771;,
 0.00000;7.86862;-3.00399;,
 4.77251;7.86862;-0.10965;,
 4.77251;10.46161;6.19771;,
 4.77251;7.86862;6.19771;,
 -4.77251;7.86862;6.19771;,
 -4.77251;10.46161;6.19771;,
 -4.77251;10.46161;-0.10965;,
 -4.77251;7.86862;-0.10965;,
 -4.77251;7.86862;6.19771;,
 -4.77251;7.86862;-0.10965;,
 -4.77251;10.46161;6.19771;,
 7.12981;4.02602;1.55258;,
 5.83764;4.02602;1.55258;,
 5.83764;5.47959;1.55258;,
 7.12981;5.47959;1.55258;,
 5.83764;6.93316;1.55258;,
 7.12981;6.93316;1.55258;,
 5.83764;6.93316;2.57447;,
 7.12981;6.93316;2.57447;,
 5.83764;6.93316;4.23833;,
 7.12981;6.93316;4.23833;,
 5.83764;5.47959;4.45973;,
 7.12981;5.47959;4.45973;,
 5.83764;4.02602;4.45973;,
 7.12981;4.02602;4.45973;,
 5.83764;3.60350;2.57447;,
 7.12981;3.60350;2.57447;,
 5.83764;4.02602;1.55258;,
 7.12981;4.02602;1.55258;,
 5.80437;3.75451;2.61362;,
 5.80437;4.13870;4.32789;,
 5.80437;5.46043;4.32789;,
 5.80437;5.46043;2.61362;,
 5.80437;4.13870;1.68442;,
 5.80437;5.46043;1.68442;,
 5.80437;6.78216;4.12657;,
 5.80437;6.78216;2.61362;,
 5.80437;6.78216;1.68442;,
 7.16307;4.13870;4.32789;,
 7.16307;3.75451;2.61362;,
 7.16307;5.46043;2.61362;,
 7.16307;5.46043;4.32789;,
 7.16307;4.13870;1.68442;,
 7.16307;5.46043;1.68442;,
 7.16307;6.78216;2.61362;,
 7.16307;6.78216;4.12657;,
 7.16307;6.78216;1.68442;,
 5.83764;3.60350;2.57447;,
 5.83764;4.02602;4.45973;,
 5.83764;5.47959;4.45973;,
 5.83764;6.93316;4.23833;,
 5.83764;6.93316;2.57447;,
 7.12981;4.02602;4.45973;,
 7.12981;3.60350;2.57447;,
 7.12981;5.47959;4.45973;,
 7.12981;6.93316;2.57447;,
 7.12981;6.93316;4.23833;,
 -7.12981;4.02602;1.55258;,
 -7.12981;5.47959;1.55258;,
 -5.83764;5.47959;1.55258;,
 -5.83764;4.02602;1.55258;,
 -7.12981;6.93316;1.55258;,
 -5.83764;6.93316;1.55258;,
 -7.12981;6.93316;2.57447;,
 -5.83764;6.93316;2.57447;,
 -7.12981;6.93316;4.23833;,
 -5.83764;6.93316;4.23833;,
 -7.12981;5.47959;4.45973;,
 -5.83764;5.47959;4.45973;,
 -7.12981;4.02602;4.45973;,
 -5.83764;4.02602;4.45973;,
 -7.12981;3.60350;2.57447;,
 -5.83764;3.60350;2.57447;,
 -7.12981;4.02602;1.55258;,
 -5.83764;4.02602;1.55258;,
 -5.80437;3.75451;2.61362;,
 -5.80437;5.46043;2.61362;,
 -5.80437;5.46043;4.32789;,
 -5.80437;4.13870;4.32789;,
 -5.80437;4.13870;1.68442;,
 -5.80437;5.46043;1.68442;,
 -5.80437;6.78216;2.61362;,
 -5.80437;6.78216;4.12657;,
 -5.80437;6.78216;1.68442;,
 -7.16307;4.13870;4.32789;,
 -7.16307;5.46043;4.32789;,
 -7.16307;5.46043;2.61362;,
 -7.16307;3.75451;2.61362;,
 -7.16307;5.46043;1.68442;,
 -7.16307;4.13870;1.68442;,
 -7.16307;6.78216;4.12657;,
 -7.16307;6.78216;2.61362;,
 -7.16307;6.78216;1.68442;,
 -5.83764;3.60350;2.57447;,
 -5.83764;4.02602;4.45973;,
 -5.83764;5.47959;4.45973;,
 -5.83764;6.93316;4.23833;,
 -5.83764;6.93316;2.57447;,
 -7.12981;4.02602;4.45973;,
 -7.12981;3.60350;2.57447;,
 -7.12981;5.47959;4.45973;,
 -7.12981;6.93316;2.57447;,
 -7.12981;6.93316;4.23833;,
 0.00000;10.21023;-3.57981;,
 1.90322;10.54605;-3.63653;,
 1.90322;9.76331;-3.46071;,
 0.00000;9.42748;-3.40400;,
 0.00000;10.26354;-3.34247;,
 1.90322;10.59936;-3.39918;,
 0.00000;9.48079;-3.16666;,
 1.90322;9.81662;-3.22337;,
 0.00000;9.42748;-3.40400;,
 1.90322;9.76331;-3.46071;,
 9.32861;17.41557;5.49249;,
 9.32861;18.19831;5.31668;,
 9.32861;18.25162;5.55402;,
 9.32861;17.46888;5.72983;,
 -8.86777;17.56930;2.51704;,
 -8.86777;18.35204;2.34123;,
 -8.86777;18.29873;2.10389;,
 -8.86777;17.51599;2.27970;,
 6.31466;9.98882;-0.84689;,
 6.31466;10.04213;-0.60954;,
 1.90322;9.81662;-3.22337;,
 6.31466;10.82487;-0.78536;,
 1.90322;10.59936;-3.39918;,
 6.31466;10.77156;-1.02270;,
 -1.90322;9.81662;-3.22337;,
 -6.30078;10.04213;-0.43695;,
 -6.30078;9.98882;-0.67429;,
 -1.90322;9.76331;-3.46071;,
 -6.30078;10.77156;-0.85011;,
 -1.90322;10.54605;-3.50690;,
 -6.30078;10.82487;-0.61276;,
 -1.90322;10.59936;-3.26955;,
 -1.90322;9.81662;-3.22337;,
 -1.90322;9.76331;-3.46071;,
 -1.90322;10.59936;-3.26955;,
 -0.00001;22.73082;-5.06148;,
 0.90534;22.73081;-5.06148;,
 2.07557;16.20630;-6.86257;,
 0.00000;16.20630;-6.86257;,
 0.00001;22.73082;-4.26925;,
 0.90535;22.73081;-4.26925;,
 0.00000;16.20630;-2.36891;,
 2.07558;16.20630;-2.36891;,
 0.00000;10.93495;-4.53247;,
 1.18060;10.93495;-3.78228;,
 1.18060;10.93495;3.22490;,
 0.00000;10.93495;3.22490;,
 0.90535;22.73081;-4.26925;,
 2.07558;16.20630;-2.36891;,
 -2.07557;16.20630;-2.36891;,
 -0.90534;22.73083;-4.26925;,
 -0.90535;22.73083;-5.06148;,
 -2.07558;16.20630;-6.86257;,
 1.18060;10.93495;-3.78228;,
 0.00000;10.93495;-4.53247;,
 1.18060;10.93495;3.22490;,
 -1.18060;10.93495;3.22490;,
 -1.18060;10.93495;-3.78228;,
 -1.18060;10.93495;3.22490;,
 -1.18060;10.93495;-3.78228;,
 -2.07557;16.20630;-2.36891;,
 -0.90534;22.73083;-4.26925;,
 0.00000;15.30989;-3.57091;,
 5.40669;15.71671;-0.42574;,
 6.17413;11.10343;-1.13371;,
 0.00000;10.63437;-4.68053;,
 0.00000;17.16430;6.33141;,
 3.60793;17.16430;5.73453;,
 3.60793;17.16430;0.83057;,
 0.00000;17.16430;-1.28963;,
 0.00000;10.34126;8.69849;,
 5.88643;10.69558;7.52371;,
 5.32698;15.37112;7.00409;,
 0.00000;15.01678;8.63907;,
 0.00000;10.34126;-3.66741;,
 5.68605;10.34126;-0.23251;,
 5.01522;10.34126;6.34894;,
 0.00000;10.34126;6.34894;,
 5.32698;15.37112;7.00409;,
 5.88643;10.69558;7.52371;,
 -5.88643;10.69558;7.52371;,
 -5.32698;15.37112;7.00409;,
 -5.40669;15.71671;-0.42574;,
 -6.17413;11.10343;-1.13371;,
 -5.01522;10.34126;6.34894;,
 -5.68605;10.34126;-0.23251;,
 -5.32698;15.37112;7.00409;,
 -5.88643;10.69558;7.52371;,
 -3.60793;17.16430;0.83057;,
 -3.60793;17.16430;5.73453;,
 5.68605;10.34126;-0.23251;,
 5.01522;10.34126;6.34894;,
 3.60793;17.16430;5.73453;,
 -5.01522;10.34126;6.34894;,
 -5.68605;10.34126;-0.23251;,
 -3.60793;17.16430;5.73453;,
 0.00000;10.34126;-3.66741;,
 0.00000;8.17102;-4.48742;,
 5.45188;8.17102;-0.31154;,
 5.45188;0.00000;-1.99757;,
 0.00000;0.00000;-6.17345;,
 0.00000;8.17102;6.17345;,
 5.45188;8.17102;6.17345;,
 5.45188;8.17102;2.93096;,
 0.00000;8.17102;0.84302;,
 0.00000;0.00000;9.90271;,
 6.03214;0.00000;7.29985;,
 5.15115;8.17102;7.29985;,
 0.00000;8.17102;8.42625;,
 5.89237;0.00000;2.08794;,
 6.33287;0.00000;6.17345;,
 0.00000;0.00000;6.17345;,
 0.00000;0.00000;0.00000;,
 5.71435;8.17102;3.49416;,
 5.15115;8.17102;7.29985;,
 6.03214;0.00000;7.29985;,
 6.15485;0.00000;2.65114;,
 -6.03214;0.00000;7.29985;,
 -5.15115;8.17102;7.29985;,
 -5.71435;8.17102;3.49416;,
 -6.15485;0.00000;2.65114;,
 -6.33287;0.00000;6.17345;,
 -5.89237;0.00000;2.08794;,
 -5.15115;8.17102;7.29985;,
 -6.03214;0.00000;7.29985;,
 -5.45188;8.17102;2.93096;,
 -5.45188;8.17102;6.17345;,
 -5.45188;0.00000;-1.99757;,
 -5.45188;8.17102;-0.31154;,
 6.33287;0.00000;6.17345;,
 5.89237;0.00000;2.08794;,
 5.45188;8.17102;6.17345;,
 5.45188;8.17102;2.93096;,
 6.27755;8.17102;-0.31154;,
 6.27755;0.00000;-1.99757;,
 -6.33287;0.00000;6.17345;,
 -5.89237;0.00000;2.08794;,
 -6.27755;0.00000;-1.99757;,
 -6.27755;8.17102;-0.31154;,
 -5.45188;8.17102;6.17345;,
 -5.45188;8.17102;2.93096;,
 0.00000;8.84832;-3.47384;,
 1.90322;9.18413;-3.53055;,
 1.90322;8.40140;-3.35474;,
 0.00000;8.06557;-3.29802;,
 0.00000;8.90163;-3.23649;,
 1.90322;9.23744;-3.29321;,
 0.00000;8.11888;-3.06068;,
 1.90322;8.45471;-3.11740;,
 0.00000;8.06557;-3.29802;,
 1.90322;8.40140;-3.35474;,
 11.93585;15.71076;7.55525;,
 11.93585;16.49349;7.37944;,
 11.93585;16.54680;7.61679;,
 11.93585;15.76406;7.79260;,
 -10.50084;15.88426;5.32783;,
 -10.50084;16.66701;5.15202;,
 -10.50084;16.61370;4.91468;,
 -10.50084;15.83095;5.09049;,
 6.31466;8.62690;-0.74091;,
 6.31466;8.68021;-0.50357;,
 1.90322;8.45471;-3.11740;,
 6.31466;9.46296;-0.67938;,
 1.90322;9.23744;-3.29321;,
 6.31466;9.40965;-0.91672;,
 -1.90322;8.45471;-3.11740;,
 -6.30078;8.68021;-0.33098;,
 -6.30078;8.62690;-0.56832;,
 -1.90322;8.40140;-3.35474;,
 -6.30078;9.40965;-0.74413;,
 -1.90322;9.18413;-3.40092;,
 -6.30078;9.46296;-0.50679;,
 -1.90322;9.23744;-3.16358;,
 -1.90322;8.45471;-3.11740;,
 -1.90322;8.40140;-3.35474;,
 -1.90322;9.23744;-3.16358;,
 0.00000;0.00000;-6.17345;,
 5.45188;0.00000;-1.99757;,
 -5.45188;0.00000;-1.99757;;
 
 198;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;8,9,7,6;,
 4;2,1,10,11;,
 4;12,13,14,15;,
 4;16,17,8,6;,
 4;18,16,6,4;,
 4;14,18,4,0;,
 4;15,14,0,3;,
 4;19,20,21,22;,
 4;22,21,23,24;,
 4;24,23,25,26;,
 4;26,25,27,28;,
 4;28,27,29,30;,
 4;30,29,31,32;,
 4;32,31,33,34;,
 4;34,33,35,36;,
 4;37,38,39,40;,
 4;41,37,40,42;,
 4;40,39,43,44;,
 4;42,40,44,45;,
 4;46,47,48,49;,
 4;47,50,51,48;,
 4;49,48,52,53;,
 4;48,51,54,52;,
 4;55,56,38,37;,
 4;56,57,39,38;,
 4;20,55,37,41;,
 4;21,20,41,42;,
 4;57,58,43,39;,
 4;58,59,44,43;,
 4;59,23,45,44;,
 4;23,21,42,45;,
 4;60,61,47,46;,
 4;62,60,46,49;,
 4;61,19,50,47;,
 4;19,22,51,50;,
 4;63,64,53,52;,
 4;64,62,49,53;,
 4;22,24,54,51;,
 4;24,63,52,54;,
 4;65,66,67,68;,
 4;66,69,70,67;,
 4;69,71,72,70;,
 4;71,73,74,72;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 4;77,79,80,78;,
 4;79,81,82,80;,
 4;83,84,85,86;,
 4;87,88,84,83;,
 4;84,89,90,85;,
 4;88,91,89,84;,
 4;92,93,94,95;,
 4;95,94,96,97;,
 4;93,98,99,94;,
 4;94,99,100,96;,
 4;101,83,86,102;,
 4;102,86,85,103;,
 4;68,87,83,101;,
 4;67,88,87,68;,
 4;103,85,90,104;,
 4;104,90,89,105;,
 4;105,89,91,70;,
 4;70,91,88,67;,
 4;106,92,95,107;,
 4;108,93,92,106;,
 4;107,95,97,65;,
 4;65,97,96,66;,
 4;109,99,98,110;,
 4;110,98,93,108;,
 4;66,96,100,69;,
 4;69,100,99,109;,
 4;111,112,113,114;,
 4;115,116,112,111;,
 4;117,118,116,115;,
 4;119,120,118,117;,
 4;121,122,123,124;,
 4;125,126,127,128;,
 4;113,129,130,131;,
 4;131,130,132,133;,
 4;133,132,134,112;,
 4;112,134,129,113;,
 4;135,136,137,138;,
 4;138,137,139,140;,
 4;140,139,141,142;,
 4;142,141,136,135;,
 4;129,121,124,130;,
 4;130,124,123,132;,
 4;132,123,122,134;,
 4;134,122,121,129;,
 4;136,125,128,137;,
 4;137,128,127,139;,
 4;139,127,126,141;,
 4;141,126,125,136;,
 4;143,144,119,117;,
 4;145,143,117,115;,
 4;140,145,115,111;,
 4;138,140,111,114;,
 4;146,147,148,149;,
 4;150,151,147,146;,
 4;152,153,151,150;,
 4;154,155,156,157;,
 4;148,147,158,159;,
 4;160,161,162,163;,
 4;149,148,164,165;,
 4;164,148,159,166;,
 4;157,156,153,152;,
 4;167,160,163,168;,
 4;169,170,154,157;,
 4;171,169,157,152;,
 4;172,171,152,150;,
 4;162,172,150,146;,
 4;163,162,146,149;,
 4;168,163,149,165;,
 4;173,174,175,176;,
 4;177,178,179,180;,
 4;181,182,183,184;,
 4;185,186,187,188;,
 4;175,174,189,190;,
 4;191,192,193,194;,
 4;195,196,185,188;,
 4;197,198,181,184;,
 4;199,200,177,180;,
 4;194,193,173,176;,
 4;177,184,183,178;,
 4;187,182,181,188;,
 4;201,175,190,202;,
 4;203,189,174,179;,
 4;179,174,175,201;,
 4;204,191,194,205;,
 4;205,194,193,199;,
 4;199,193,192,206;,
 4;200,197,184,177;,
 4;188,181,198,195;,
 4;207,176,175,201;,
 4;201,175,174,179;,
 4;179,174,173,180;,
 4;205,194,176,207;,
 4;180,173,193,199;,
 4;199,193,194,205;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,223,222;,
 4;234,235,216,219;,
 4;236,237,212,215;,
 4;238,239,208,211;,
 4;212,219,218,213;,
 4;221,217,216,222;,
 4;227,226,240,241;,
 4;242,225,224,243;,
 4;209,244,245,210;,
 4;246,228,231,247;,
 4;238,248,249,239;,
 4;230,229,250,251;,
 4;237,234,219,212;,
 4;222,216,235,232;,
 4;252,253,254,255;,
 4;256,257,253,252;,
 4;258,259,257,256;,
 4;260,261,259,258;,
 4;262,263,264,265;,
 4;266,267,268,269;,
 4;254,270,271,272;,
 4;272,271,273,274;,
 4;274,273,275,253;,
 4;253,275,270,254;,
 4;276,277,278,279;,
 4;279,278,280,281;,
 4;281,280,282,283;,
 4;283,282,277,276;,
 4;270,262,265,271;,
 4;271,265,264,273;,
 4;273,264,263,275;,
 4;275,263,262,270;,
 4;277,266,269,278;,
 4;278,269,268,280;,
 4;280,268,267,282;,
 4;282,267,266,277;,
 4;284,285,260,258;,
 4;286,284,258,256;,
 4;281,286,256,252;,
 4;279,281,252,255;,
 4;239,236,215,208;,
 4;214,209,208,215;,
 4;224,244,209,243;,
 4;245,244,224,227;,
 4;210,245,227,241;,
 4;287,288,220,223;,
 4;233,289,287,223;,
 4;231,248,238,247;,
 4;230,249,248,231;,
 4;239,249,230,251;;
 
 MeshMaterialList {
  1;
  198;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  227;
  -0.871364;0.000000;-0.490636;,
  0.871364;0.000000;-0.490636;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.518552;0.000000;-0.855046;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.075505;0.997145;,
  0.000000;-0.996322;-0.085689;,
  -0.992057;-0.076702;0.099696;,
  -0.994314;-0.106227;-0.007414;,
  -0.992490;0.009191;0.121978;,
  -0.991838;-0.065466;-0.109412;,
  -0.992372;0.000000;-0.123280;,
  -0.993122;0.084812;0.080726;,
  -0.994127;0.108221;0.000000;,
  -0.993940;0.072591;-0.082547;,
  0.992062;-0.076679;0.099666;,
  0.994318;-0.106195;-0.007412;,
  1.000000;0.000000;0.000000;,
  0.992495;0.009188;0.121942;,
  0.991843;-0.065447;-0.109379;,
  0.992376;0.000000;-0.123244;,
  0.994130;0.108188;0.000000;,
  0.993126;0.084787;0.080702;,
  0.993944;0.072569;-0.082522;,
  0.992057;-0.076702;0.099696;,
  0.994314;-0.106227;-0.007414;,
  0.992490;0.009191;0.121978;,
  0.991838;-0.065466;-0.109412;,
  0.992372;0.000000;-0.123280;,
  0.993122;0.084812;0.080726;,
  0.994127;0.108221;0.000000;,
  0.993940;0.072591;-0.082547;,
  -0.992062;-0.076679;0.099666;,
  -0.994318;-0.106195;-0.007412;,
  -0.992495;0.009188;0.121942;,
  -0.991843;-0.065447;-0.109379;,
  -0.992376;0.000000;-0.123244;,
  -0.994130;0.108188;0.000000;,
  -0.993126;0.084787;0.080702;,
  -0.993944;0.072569;-0.082522;,
  -0.044102;-0.974741;0.218940;,
  0.267751;-0.211152;-0.940066;,
  -0.287877;-0.133422;-0.948328;,
  0.040062;0.974909;-0.218971;,
  -0.048492;0.974544;-0.218891;,
  -0.267752;0.211149;0.940067;,
  -0.079717;-0.972586;0.218452;,
  -0.872568;0.267452;0.408772;,
  0.079717;0.972586;-0.218452;,
  0.088480;-0.971864;0.218295;,
  -0.721182;-0.116793;-0.682829;,
  -0.082085;0.972400;-0.218406;,
  0.971899;-0.229675;0.051587;,
  0.979380;-0.182302;-0.087068;,
  0.983103;-0.040115;-0.178601;,
  -0.983298;-0.177576;0.039886;,
  -0.977207;-0.159356;-0.140260;,
  -0.966982;-0.055851;-0.248651;,
  -0.009807;-0.179487;-0.983711;,
  0.009807;0.179482;0.983713;,
  -0.007250;0.975666;-0.219143;,
  -0.985892;-0.167384;0.000001;,
  0.000000;-1.000000;-0.000000;,
  -0.984293;0.176540;0.000007;,
  0.000001;0.266097;-0.963946;,
  0.000010;1.000000;-0.000000;,
  -0.999989;0.004647;0.000004;,
  0.130073;-0.110694;-0.985306;,
  0.000001;0.522043;0.852919;,
  0.000001;0.522043;0.852919;,
  0.000011;1.000000;-0.000000;,
  0.000001;0.266097;-0.963946;,
  0.000001;-0.111642;-0.993748;,
  -0.315933;-0.939466;-0.132630;,
  0.315933;-0.939466;-0.132630;,
  -0.357537;0.913367;-0.194753;,
  0.357537;0.913367;-0.194753;,
  -0.310413;0.911594;0.269520;,
  0.310413;0.911594;0.269520;,
  -0.236221;-0.970650;0.045149;,
  0.236221;-0.970650;0.045149;,
  0.000000;-0.978587;-0.205833;,
  0.000000;-0.998495;0.054845;,
  0.000000;0.925313;0.379204;,
  0.000000;0.954432;-0.298428;,
  0.000000;0.078366;0.996925;,
  0.000000;0.423285;0.905997;,
  0.203932;0.414389;0.886957;,
  0.239267;0.076090;0.967968;,
  0.477893;0.206793;-0.853730;,
  0.410929;0.521752;-0.747604;,
  -0.989430;0.142200;0.028426;,
  -0.922356;0.109070;0.370625;,
  -0.752607;0.629481;-0.193228;,
  -0.886699;0.461597;0.026320;,
  0.000000;0.572306;-0.820040;,
  0.000000;0.235415;-0.971895;,
  -0.316273;0.191712;-0.929095;,
  0.316273;0.191712;-0.929095;,
  0.600076;0.161657;-0.783438;,
  0.000000;0.114448;0.993429;,
  0.305150;0.108989;0.946047;,
  0.000000;0.202085;-0.979368;,
  -0.993165;0.078751;0.086149;,
  -0.044101;-0.974741;0.218940;,
  0.267752;-0.211150;-0.940066;,
  -0.287877;-0.133416;-0.948329;,
  0.040058;0.974908;-0.218975;,
  -0.048489;0.974543;-0.218893;,
  -0.267750;0.211147;0.940068;,
  0.322343;-0.923613;0.207446;,
  -0.708846;0.154579;0.688217;,
  -0.322335;0.923614;-0.207455;,
  -0.414381;-0.887979;0.199454;,
  -0.714637;-0.118349;-0.689411;,
  0.417300;0.886677;-0.199162;,
  0.914190;-0.395435;0.088810;,
  0.942875;-0.309892;-0.122286;,
  0.965407;-0.057143;-0.254411;,
  -0.951156;-0.301205;0.067656;,
  -0.960148;-0.246166;-0.132354;,
  -0.964542;-0.057839;-0.257515;,
  -0.009807;-0.179488;-0.983711;,
  0.009807;0.179482;0.983712;,
  -0.007250;0.975666;-0.219142;,
  0.995125;0.047604;0.086373;,
  -0.995125;0.047604;0.086373;,
  -0.518552;0.000000;-0.855046;,
  0.000000;0.150578;0.988598;,
  0.000000;-0.975794;0.218693;,
  0.000000;-0.924123;-0.382096;,
  -0.977270;-0.211486;-0.014760;,
  -0.982047;-0.115025;0.149507;,
  -0.970068;0.018245;0.242145;,
  -0.981592;-0.098064;-0.163890;,
  -0.969604;0.000000;-0.244680;,
  -0.984446;0.127256;0.121124;,
  -0.976577;0.215170;0.000000;,
  -0.986273;0.109043;-0.123997;,
  0.982058;-0.114991;0.149463;,
  0.977283;-0.211423;-0.014756;,
  0.970086;0.018240;0.242075;,
  0.981603;-0.098034;-0.163842;,
  0.969622;0.000000;-0.244609;,
  0.976591;0.215107;0.000000;,
  0.984456;0.127218;0.121088;,
  0.986281;0.109010;-0.123960;,
  0.977270;-0.211486;-0.014760;,
  0.982047;-0.115025;0.149507;,
  0.970068;0.018245;0.242145;,
  0.981592;-0.098064;-0.163890;,
  0.969604;0.000000;-0.244680;,
  0.984446;0.127256;0.121124;,
  0.976577;0.215170;0.000000;,
  0.986273;0.109043;-0.123997;,
  -0.982058;-0.114991;0.149463;,
  -0.977283;-0.211423;-0.014756;,
  -0.970086;0.018240;0.242075;,
  -0.981603;-0.098034;-0.163842;,
  -0.969622;0.000000;-0.244609;,
  -0.976591;0.215107;0.000000;,
  -0.984456;0.127218;0.121088;,
  -0.986281;0.109010;-0.123960;,
  0.000000;-0.975691;0.219153;,
  0.048494;-0.974543;0.218893;,
  -0.762760;0.141723;0.630961;,
  0.762760;-0.141722;-0.630962;,
  0.287878;0.133413;0.948329;,
  0.721181;0.116786;0.682832;,
  0.889176;-0.446442;0.100275;,
  -0.932985;0.078877;0.351166;,
  -0.952566;0.274621;0.131155;,
  -0.889174;0.446445;-0.100280;,
  -0.933752;-0.349220;0.078440;,
  0.933752;0.349220;-0.078438;,
  0.947442;0.240152;0.211378;,
  0.870105;0.108011;0.480886;,
  0.000001;0.279642;0.960104;,
  0.000002;0.279641;0.960105;,
  0.999989;0.004646;-0.000004;,
  0.984293;0.176540;-0.000007;,
  0.239418;-0.469846;-0.849661;,
  0.000000;-0.483920;-0.875112;,
  0.985891;-0.167386;-0.000001;,
  0.000000;0.727772;0.685819;,
  0.000001;0.522043;0.852919;,
  0.000002;0.279641;0.960105;,
  0.000012;1.000000;-0.000000;,
  -0.130071;-0.110694;-0.985306;,
  0.000002;0.266097;-0.963946;,
  -0.239417;-0.469846;-0.849661;,
  0.922356;0.109070;0.370625;,
  0.898925;0.347480;0.266819;,
  0.886699;0.461597;0.026320;,
  0.989430;0.142200;0.028426;,
  -0.203932;0.414389;0.886957;,
  -0.239267;0.076090;0.967968;,
  -0.477893;0.206793;-0.853730;,
  0.354845;-0.932462;0.067821;,
  0.000000;-0.993976;0.109597;,
  0.465302;-0.863330;-0.195336;,
  -0.742113;-0.062556;-0.667350;,
  -0.354845;-0.932462;0.067821;,
  -0.465302;-0.863330;-0.195336;,
  0.742113;-0.062556;-0.667350;,
  0.000000;-0.911951;-0.410299;,
  0.742113;0.062556;0.667350;,
  -0.742113;0.062556;0.667350;,
  0.993165;0.078751;0.086149;,
  -0.305150;0.108989;0.946047;,
  -0.600076;0.161657;-0.783438;,
  0.000000;0.000000;0.000000;,
  0.000000;-0.975691;0.219153;,
  0.048492;-0.974543;0.218896;,
  0.708846;-0.154579;-0.688217;,
  0.287875;0.133413;0.948330;,
  0.714637;0.118349;0.689411;,
  -0.864020;0.110332;0.491220;,
  -0.863736;0.468771;0.184968;,
  -0.671471;0.723017;-0.162397;,
  0.809397;0.572986;-0.128703;,
  0.906626;0.371625;0.199809;,
  0.860682;0.111577;0.496767;,
  0.996116;0.016410;0.086514;,
  -0.996116;0.016410;0.086514;;
  198;
  4;5,1,1,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;64,64,64,64;,
  4;1,1,19,19;,
  4;2,2,0,0;,
  4;64,64,64,64;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;0,0,129,129;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;130,130,7,7;,
  4;7,7,4,4;,
  4;131,131,8,8;,
  4;8,8,132,132;,
  4;10,9,11,2;,
  4;12,10,2,13;,
  4;2,11,14,15;,
  4;13,2,15,16;,
  4;17,18,19,20;,
  4;18,21,22,19;,
  4;20,19,23,24;,
  4;19,22,25,23;,
  4;133,134,9,10;,
  4;134,135,11,9;,
  4;136,133,10,12;,
  4;137,136,12,13;,
  4;135,138,14,11;,
  4;138,139,15,14;,
  4;139,140,16,15;,
  4;140,137,13,16;,
  4;141,142,18,17;,
  4;143,141,17,20;,
  4;142,144,21,18;,
  4;144,145,22,21;,
  4;146,147,24,23;,
  4;147,143,20,24;,
  4;145,148,25,22;,
  4;148,146,23,25;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;130,7,7,130;,
  4;7,4,4,7;,
  4;131,8,8,131;,
  4;8,132,132,8;,
  4;27,19,28,26;,
  4;29,30,19,27;,
  4;19,32,31,28;,
  4;30,33,32,19;,
  4;34,36,2,35;,
  4;35,2,38,37;,
  4;36,40,39,2;,
  4;2,39,41,38;,
  4;149,27,26,150;,
  4;150,26,28,151;,
  4;152,29,27,149;,
  4;153,30,29,152;,
  4;151,28,31,154;,
  4;154,31,32,155;,
  4;155,32,33,156;,
  4;156,33,30,153;,
  4;157,34,35,158;,
  4;159,36,34,157;,
  4;158,35,37,160;,
  4;160,37,38,161;,
  4;162,39,40,163;,
  4;163,40,36,159;,
  4;161,38,41,164;,
  4;164,41,39,162;,
  4;60,43,43,60;,
  4;62,46,46,62;,
  4;61,47,47,61;,
  4;165,166,166,165;,
  4;55,56,19,54;,
  4;57,2,59,58;,
  4;166,48,48,166;,
  4;47,167,49,47;,
  4;46,50,50,46;,
  4;43,168,168,43;,
  4;42,51,51,42;,
  4;44,52,52,44;,
  4;45,53,53,45;,
  4;169,170,170,169;,
  4;171,55,54,171;,
  4;167,172,173,49;,
  4;49,173,174,174;,
  4;168,56,55,168;,
  4;175,57,58,175;,
  4;52,58,59,52;,
  4;176,176,177,176;,
  4;170,177,178,170;,
  4;42,42,165,165;,
  4;169,169,61,61;,
  4;45,45,62,62;,
  4;44,44,60,60;,
  4;73,66,69,74;,
  4;72,67,67,72;,
  4;71,70,179,180;,
  4;64,64,64,64;,
  4;181,182,182,181;,
  4;68,65,65,68;,
  4;74,69,183,184;,
  4;185,181,181,185;,
  4;186,186,70,71;,
  4;63,68,68,63;,
  4;64,64,64,64;,
  4;187,186,186,71;,
  4;188,187,71,180;,
  4;189,189,72,72;,
  4;190,191,73,74;,
  4;192,190,74,184;,
  4;97,92,91,98;,
  4;85,80,78,86;,
  4;87,90,89,88;,
  4;83,76,82,84;,
  4;193,194,195,196;,
  4;93,96,95,94;,
  4;81,75,83,84;,
  4;197,198,87,88;,
  4;77,79,85,86;,
  4;199,199,97,98;,
  4;85,88,89,80;,
  4;82,200,201,84;,
  4;76,202,200,82;,
  4;80,195,194,78;,
  4;203,203,203,203;,
  4;81,204,205,75;,
  4;206,206,206,206;,
  4;77,95,96,79;,
  4;79,197,88,85;,
  4;84,201,204,81;,
  4;83,207,202,76;,
  4;208,193,194,208;,
  4;78,92,97,86;,
  4;75,205,207,83;,
  4;86,97,95,77;,
  4;209,209,94,209;,
  4;101,100,100,101;,
  4;3,3,3,3;,
  4;102,103,103,102;,
  4;64,64,64,64;,
  4;127,210,210,127;,
  4;105,105,128,128;,
  4;64,64,64,64;,
  4;211,211,102,102;,
  4;3,3,3,3;,
  4;99,99,212,212;,
  4;3,3,3,3;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;213,213,213,213;,
  4;100,104,104,100;,
  4;64,64,64,64;,
  4;99,104,104,99;,
  4;213,213,213,213;,
  4;3,3,3,3;,
  4;64,64,64,64;,
  4;124,107,107,124;,
  4;126,110,110,126;,
  4;125,111,111,125;,
  4;214,215,215,214;,
  4;119,120,19,118;,
  4;121,2,123,122;,
  4;215,112,112,215;,
  4;111,113,113,111;,
  4;110,114,114,110;,
  4;107,216,216,107;,
  4;106,115,115,106;,
  4;108,116,116,108;,
  4;109,117,117,109;,
  4;217,218,218,217;,
  4;112,119,118,112;,
  4;113,219,220,113;,
  4;114,220,221,114;,
  4;216,120,119,216;,
  4;115,121,122,115;,
  4;116,122,123,116;,
  4;117,222,223,117;,
  4;218,223,224,218;,
  4;106,106,214,214;,
  4;217,217,125,125;,
  4;109,109,126,126;,
  4;108,108,124,124;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;225,225,127,127;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;128,226,226,128;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  290;
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
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.125000;0.750000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.500000;0.875000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.125000;0.875000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
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
  0.625000;0.625000;,
  0.500000;0.625000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.125000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.750000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.375000;0.625000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.875000;1.000000;,
  0.750000;1.000000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
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
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.125000;0.750000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.375000;0.000000;;
 }
}
