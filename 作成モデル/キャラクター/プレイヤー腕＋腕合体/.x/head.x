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
 224;
 -0.71750;17.69663;-9.98781;,
 3.08894;18.36826;-10.10125;,
 3.08894;16.80279;-9.74962;,
 -0.71750;16.13113;-9.63619;,
 -0.71750;17.80325;-9.51313;,
 3.08894;18.47488;-9.62656;,
 -0.71750;16.23775;-9.16151;,
 3.08894;16.90941;-9.27494;,
 23.15419;31.42151;12.07037;,
 23.15419;32.98698;11.71875;,
 23.15419;33.09361;12.19343;,
 23.15419;31.52811;12.54506;,
 -21.71918;31.76851;7.61552;,
 -21.71918;33.33401;7.26390;,
 -21.71918;33.22739;6.78921;,
 -21.71918;31.66189;7.14083;,
 11.91181;17.25380;-4.52196;,
 11.91181;17.36042;-4.04728;,
 11.91181;18.92591;-4.39890;,
 11.91181;18.81929;-4.87359;,
 -4.52394;16.90941;-9.27494;,
 -13.31906;17.36042;-3.70209;,
 -13.31906;17.25380;-4.17678;,
 -4.52394;16.80279;-9.74962;,
 -13.31906;18.81929;-4.52840;,
 -4.52394;18.36826;-9.84199;,
 -13.31906;18.92591;-4.05372;,
 -4.52394;18.47488;-9.36730;,
 -0.71750;16.34203;-12.01499;,
 10.18626;16.34203;-3.66322;,
 10.18626;0.00000;-7.03527;,
 -0.71750;0.00000;-15.38705;,
 -0.71750;16.34203;9.30677;,
 10.18626;16.34203;9.30677;,
 10.18626;16.34203;2.82178;,
 -0.71750;16.34203;-1.35411;,
 -0.71750;0.00000;16.76528;,
 11.34678;0.00000;11.55956;,
 9.58480;16.34203;11.55956;,
 -0.71750;16.34203;13.81235;,
 11.06724;0.00000;1.13575;,
 9.84370;0.00000;9.30677;,
 -0.71750;0.00000;9.30677;,
 -0.71750;0.00000;-3.04014;,
 10.71120;16.34203;3.94817;,
 11.59219;0.00000;2.26214;,
 -12.78178;0.00000;11.55956;,
 -11.01981;16.34203;11.55956;,
 -12.14621;16.34203;3.94817;,
 -13.02719;0.00000;2.26214;,
 -11.78449;0.00000;9.30677;,
 -12.50225;0.00000;1.13575;,
 -11.62126;16.34203;2.82178;,
 -11.62126;16.34203;9.30677;,
 -11.62126;0.00000;-7.03527;,
 -11.62126;16.34203;-3.66322;,
 -0.71750;22.27333;9.75711;,
 -0.71750;22.27333;14.26270;,
 9.58480;22.27333;12.00990;,
 10.18626;22.27333;9.75711;,
 11.83760;16.34203;-3.66322;,
 11.83760;0.00000;-7.03527;,
 -13.27261;0.00000;-7.03527;,
 -13.27261;16.34203;-3.66322;,
 -11.62126;22.27333;9.75712;,
 -11.01981;22.27333;12.00991;,
 -0.71750;30.61977;-10.18195;,
 10.09588;31.43341;-3.89161;,
 11.63075;22.20686;-5.30755;,
 -0.71750;21.26873;-12.40120;,
 -0.71750;34.32859;9.62268;,
 6.49837;34.32859;8.42891;,
 6.49837;34.32859;-1.37900;,
 -0.71750;34.32859;-5.61941;,
 -0.71750;20.68251;14.35684;,
 11.43397;21.39116;10.40393;,
 9.93647;30.74223;10.96804;,
 -0.71750;30.03355;14.23800;,
 -0.71750;20.68251;-10.37495;,
 10.65459;20.68251;-3.50515;,
 8.54659;20.68251;10.87234;,
 -0.71750;20.68251;9.65773;,
 -12.86898;21.39116;10.40393;,
 -11.37147;30.74223;10.96804;,
 -11.53089;31.43341;-3.89161;,
 -13.06576;22.20686;-5.30755;,
 -9.98159;20.68251;10.87234;,
 -12.08960;20.68251;-3.50515;,
 -7.93337;34.32859;-1.37900;,
 -7.93337;34.32859;8.42891;,
 10.08337;15.61319;-3.38099;,
 11.46075;15.86386;-3.42473;,
 9.67685;16.17462;10.80064;,
 6.72937;16.00348;11.38524;,
 -8.16438;16.00348;11.38524;,
 -11.11185;16.17462;10.80064;,
 -12.89576;15.86386;-3.42473;,
 -11.51837;15.61319;-3.38099;,
 -0.71752;45.46164;-13.16311;,
 1.09317;45.46162;-13.16311;,
 3.43364;32.41259;-16.76528;,
 -0.71751;32.41259;-16.76528;,
 -0.71749;45.46164;-11.57864;,
 1.09320;45.46162;-11.57864;,
 -0.71750;32.41259;-7.77797;,
 3.43365;32.41259;-7.77797;,
 -0.71750;21.86989;-12.10509;,
 1.64370;21.86989;-10.60470;,
 1.64370;21.86989;3.40965;,
 -0.71750;21.86989;3.40965;,
 -4.86864;32.41259;-7.77797;,
 -2.52818;45.46165;-11.57864;,
 -2.52820;45.46165;-13.16311;,
 -4.86866;32.41259;-16.76528;,
 -3.07870;21.86989;3.40965;,
 -3.07870;21.86989;-10.60470;,
 -0.71750;20.42046;-10.19976;,
 3.08894;21.09209;-10.31319;,
 3.08894;19.52662;-9.96157;,
 -0.71750;18.85496;-9.84814;,
 -0.71750;20.52708;-9.72508;,
 3.08894;21.19871;-9.83851;,
 -0.71750;18.96158;-9.37345;,
 3.08894;19.63324;-9.48689;,
 17.93972;34.83114;7.94484;,
 17.93972;36.39662;7.59322;,
 17.93972;36.50324;8.06790;,
 17.93972;34.93776;8.41953;,
 -18.45303;35.13859;1.99394;,
 -18.45303;36.70408;1.64232;,
 -18.45303;36.59746;1.16763;,
 -18.45303;35.03197;1.51925;,
 11.91181;19.97763;-4.73391;,
 11.91181;20.08425;-4.25923;,
 11.91181;21.64974;-4.61085;,
 11.91181;21.54312;-5.08554;,
 -4.52394;19.63324;-9.48689;,
 -13.31906;20.08425;-3.91404;,
 -13.31906;19.97763;-4.38873;,
 -4.52394;19.52662;-9.96157;,
 -13.31906;21.54312;-4.74035;,
 -4.52394;21.09209;-10.05393;,
 -13.31906;21.64974;-4.26567;,
 -4.52394;21.19871;-9.57925;,
 -14.97711;13.86631;0.06502;,
 -14.97711;13.86631;2.10880;,
 -12.39278;13.86631;2.10880;,
 -12.39278;13.86631;0.06502;,
 -14.97711;13.86631;5.43652;,
 -12.39278;13.86631;5.43652;,
 -14.97711;10.95917;5.87931;,
 -12.39278;10.95917;5.87931;,
 -14.97711;8.05204;5.87931;,
 -12.39278;8.05204;5.87931;,
 -14.97711;7.20699;2.10880;,
 -12.39278;7.20699;2.10880;,
 -14.97711;8.05204;0.06502;,
 -12.39278;8.05204;0.06502;,
 -12.32624;7.50902;2.18711;,
 -12.32624;10.92085;2.18711;,
 -12.32624;10.92085;5.61563;,
 -12.32624;8.27740;5.61563;,
 -12.32624;8.27740;0.32870;,
 -12.32624;10.92085;0.32870;,
 -12.32624;13.56432;2.18711;,
 -12.32624;13.56432;5.21300;,
 -12.32624;13.56432;0.32870;,
 -15.04364;8.27740;5.61563;,
 -15.04364;10.92085;5.61563;,
 -15.04365;10.92085;2.18711;,
 -15.04364;7.50902;2.18711;,
 -15.04364;10.92085;0.32870;,
 -15.04364;8.27740;0.32870;,
 -15.04364;13.56432;5.21300;,
 -15.04364;13.56432;2.18711;,
 -15.04364;13.56432;0.32870;,
 -12.39278;10.95917;0.06502;,
 -14.97711;10.95917;0.06502;,
 13.54211;8.05204;0.06502;,
 10.95777;8.05204;0.06502;,
 10.95777;10.95917;0.06502;,
 13.54211;10.95917;0.06502;,
 10.95777;13.86631;0.06502;,
 13.54211;13.86631;0.06502;,
 10.95777;13.86631;2.10880;,
 13.54211;13.86631;2.10880;,
 10.95777;13.86631;5.43652;,
 13.54211;13.86631;5.43652;,
 10.95777;10.95917;5.87931;,
 13.54211;10.95917;5.87931;,
 10.95777;8.05204;5.87931;,
 13.54211;8.05204;5.87931;,
 10.95777;7.20699;2.10880;,
 13.54211;7.20699;2.10880;,
 10.89124;7.50902;2.18711;,
 10.89124;8.27740;5.61563;,
 10.89124;10.92085;5.61563;,
 10.89124;10.92085;2.18711;,
 10.89124;8.27740;0.32870;,
 10.89124;10.92085;0.32870;,
 10.89124;13.56432;5.21300;,
 10.89124;13.56432;2.18711;,
 10.89124;13.56432;0.32870;,
 13.60864;8.27740;5.61563;,
 13.60864;7.50902;2.18711;,
 13.60864;10.92085;2.18711;,
 13.60864;10.92085;5.61563;,
 13.60864;8.27740;0.32870;,
 13.60864;10.92085;0.32870;,
 13.60864;13.56432;2.18711;,
 13.60864;13.56432;5.21300;,
 13.60864;13.56432;0.32870;,
 -0.71750;20.92321;-9.04813;,
 8.82752;20.92321;-3.25944;,
 8.82752;15.73723;-3.25944;,
 -0.71750;15.73723;-9.04813;,
 -0.71750;20.92321;9.35528;,
 8.82752;20.92321;9.35528;,
 -0.71750;15.73723;9.35528;,
 8.82752;15.73723;9.35528;,
 -10.26252;15.73723;9.35528;,
 -10.26252;20.92321;9.35528;,
 -10.26252;20.92321;-3.25944;,
 -10.26252;15.73723;-3.25944;;
 
 212;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;3,2,7,6;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;2,16,17,7;,
 4;7,17,18,5;,
 4;5,18,19,1;,
 4;1,19,16,2;,
 4;20,21,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,21,20;,
 4;16,8,11,17;,
 4;17,11,10,18;,
 4;18,10,9,19;,
 4;19,9,8,16;,
 4;21,12,15,22;,
 4;22,15,14,24;,
 4;24,14,13,26;,
 4;26,13,12,21;,
 4;20,23,3,6;,
 4;27,20,6,4;,
 4;25,27,4,0;,
 4;23,25,0,3;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,38,37,45;,
 4;46,47,48,49;,
 4;50,51,43,42;,
 4;47,46,36,39;,
 4;52,53,32,35;,
 4;54,55,28,31;,
 4;56,57,58,59;,
 4;41,37,36,42;,
 4;45,37,41,40;,
 4;33,38,44,34;,
 4;29,60,61,30;,
 4;50,46,49,51;,
 4;54,62,63,55;,
 4;48,47,53,52;,
 4;64,65,57,56;,
 4;42,36,46,50;,
 4;55,52,35,28;,
 4;34,29,28,35;,
 4;44,60,29,34;,
 4;61,60,44,45;,
 4;30,61,45,40;,
 4;31,30,40,43;,
 4;51,54,31,43;,
 4;49,62,54,51;,
 4;48,63,62,49;,
 4;55,63,48,52;,
 4;32,56,59,33;,
 4;33,59,58,38;,
 4;38,58,57,39;,
 4;53,64,56,32;,
 4;39,57,65,47;,
 4;47,65,64,53;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;68,67,76,75;,
 4;82,83,84,85;,
 4;86,87,78,81;,
 4;83,82,74,77;,
 4;88,89,70,73;,
 4;85,84,66,69;,
 4;70,77,76,71;,
 4;80,75,74,81;,
 4;90,91,92,93;,
 4;71,76,67,72;,
 4;72,67,68,79;,
 4;94,95,96,97;,
 4;87,85,84,88;,
 4;88,84,83,89;,
 4;89,83,77,70;,
 4;81,74,82,86;,
 4;78,69,68,79;,
 4;79,68,67,72;,
 4;72,67,66,73;,
 4;87,85,69,78;,
 4;73,66,84,88;,
 4;88,84,85,87;,
 4;79,90,93,80;,
 4;80,93,92,75;,
 4;75,92,91,68;,
 4;68,91,90,79;,
 4;86,94,97,87;,
 4;87,97,96,85;,
 4;85,96,95,82;,
 4;82,95,94,86;,
 4;98,99,100,101;,
 4;102,103,99,98;,
 4;104,105,103,102;,
 4;106,107,108,109;,
 4;100,99,103,105;,
 4;110,111,112,113;,
 4;101,100,107,106;,
 4;107,100,105,108;,
 4;109,108,105,104;,
 4;114,110,113,115;,
 4;114,115,106,109;,
 4;110,114,109,104;,
 4;111,110,104,102;,
 4;112,111,102,98;,
 4;113,112,98,101;,
 4;115,113,101,106;,
 4;116,117,118,119;,
 4;120,121,117,116;,
 4;122,123,121,120;,
 4;119,118,123,122;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;118,132,133,123;,
 4;123,133,134,121;,
 4;121,134,135,117;,
 4;117,135,132,118;,
 4;136,137,138,139;,
 4;139,138,140,141;,
 4;141,140,142,143;,
 4;143,142,137,136;,
 4;132,124,127,133;,
 4;133,127,126,134;,
 4;134,126,125,135;,
 4;135,125,124,132;,
 4;137,128,131,138;,
 4;138,131,130,140;,
 4;140,130,129,142;,
 4;142,129,128,137;,
 4;136,139,119,122;,
 4;143,136,122,120;,
 4;141,143,120,116;,
 4;139,141,116,119;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;158,159,160,161;,
 4;162,163,159,158;,
 4;159,164,165,160;,
 4;163,166,164,159;,
 4;167,168,169,170;,
 4;170,169,171,172;,
 4;168,173,174,169;,
 4;169,174,175,171;,
 4;155,158,161,153;,
 4;153,161,160,151;,
 4;157,162,158,155;,
 4;176,163,162,157;,
 4;151,160,165,149;,
 4;149,165,164,146;,
 4;146,164,166,147;,
 4;147,166,163,176;,
 4;152,167,170,154;,
 4;150,168,167,152;,
 4;154,170,172,156;,
 4;156,172,171,177;,
 4;145,174,173,148;,
 4;148,173,168,150;,
 4;177,171,175,144;,
 4;144,175,174,145;,
 4;177,176,157,156;,
 4;177,144,147,176;,
 4;178,179,180,181;,
 4;181,180,182,183;,
 4;183,182,184,185;,
 4;185,184,186,187;,
 4;187,186,188,189;,
 4;189,188,190,191;,
 4;191,190,192,193;,
 4;193,192,179,178;,
 4;194,195,196,197;,
 4;198,194,197,199;,
 4;197,196,200,201;,
 4;199,197,201,202;,
 4;203,204,205,206;,
 4;204,207,208,205;,
 4;206,205,209,210;,
 4;205,208,211,209;,
 4;192,190,195,194;,
 4;190,188,196,195;,
 4;179,192,194,198;,
 4;180,179,198,199;,
 4;188,186,200,196;,
 4;186,184,201,200;,
 4;184,182,202,201;,
 4;182,180,199,202;,
 4;191,193,204,203;,
 4;189,191,203,206;,
 4;193,178,207,204;,
 4;178,181,208,207;,
 4;185,187,210,209;,
 4;187,189,206,210;,
 4;181,183,211,208;,
 4;183,185,209,211;,
 4;212,213,214,215;,
 4;216,217,213,212;,
 4;218,219,217,216;,
 4;215,214,219,218;,
 4;214,213,217,219;,
 4;220,221,222,223;,
 4;220,223,215,218;,
 4;221,220,218,216;,
 4;222,221,216,212;,
 4;223,222,212,215;;
 
 MeshMaterialList {
  1;
  212;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "union_ArmToArm.png";
   }
  }
 }
 MeshNormals {
  262;
  -0.044102;-0.974741;0.218939;,
  0.267751;-0.211151;-0.940066;,
  -0.287876;-0.133416;-0.948329;,
  0.040059;0.974907;-0.218977;,
  -0.048491;0.974543;-0.218894;,
  -0.267751;0.211147;0.940067;,
  0.322342;-0.923613;0.207447;,
  -0.708847;0.154579;0.688216;,
  -0.322330;0.923615;-0.207458;,
  -0.414384;-0.887978;0.199450;,
  -0.714637;-0.118351;-0.689411;,
  0.417301;0.886677;-0.199158;,
  0.914190;-0.395436;0.088811;,
  0.942875;-0.309893;-0.122285;,
  1.000000;0.000000;0.000000;,
  0.965407;-0.057144;-0.254410;,
  -0.951157;-0.301204;0.067653;,
  -0.960148;-0.246165;-0.132356;,
  -0.964542;-0.057839;-0.257515;,
  -1.000000;0.000000;0.000000;,
  -0.009807;-0.179485;-0.983712;,
  0.009807;0.179482;0.983712;,
  -0.007251;0.975665;-0.219148;,
  -0.316273;0.191712;-0.929095;,
  0.316273;0.191712;-0.929095;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.600077;0.161656;-0.783438;,
  0.000000;0.114448;0.993429;,
  0.000000;0.018233;0.999834;,
  0.563076;0.005857;0.826384;,
  0.305149;0.108990;0.946047;,
  0.000000;0.202085;-0.979368;,
  -0.993165;0.078750;0.086148;,
  0.000000;0.202085;-0.979368;,
  -0.984493;0.029733;0.172886;,
  0.995125;0.047603;0.086373;,
  -0.995125;0.047603;0.086374;,
  -0.139566;-0.969009;-0.203819;,
  0.139566;-0.969009;-0.203819;,
  -0.357537;0.913367;-0.194753;,
  0.357537;0.913366;-0.194753;,
  -0.310413;0.911594;0.269519;,
  0.310413;0.911594;0.269519;,
  -0.077388;-0.975540;0.205749;,
  0.077388;-0.975540;0.205749;,
  0.000000;-0.978587;-0.205834;,
  0.000000;-0.978474;0.206368;,
  -0.000000;0.925313;0.379203;,
  0.000000;0.954432;-0.298429;,
  0.000000;0.002306;0.999997;,
  0.000000;0.392333;0.919823;,
  0.240574;0.380810;0.892809;,
  0.237962;0.015072;0.971157;,
  0.477894;0.206793;-0.853730;,
  0.410930;0.521752;-0.747604;,
  -0.998987;-0.004482;0.044767;,
  -0.963145;0.019072;0.268305;,
  -0.748673;0.633330;-0.195916;,
  -0.882870;0.469128;0.021426;,
  0.000000;0.572305;-0.820041;,
  0.000000;0.235415;-0.971895;,
  0.123364;-0.991439;0.042786;,
  -0.123364;-0.991439;0.042786;,
  -0.985892;-0.167385;0.000001;,
  -0.984293;0.176540;0.000007;,
  0.000001;0.266096;-0.963946;,
  0.000010;1.000000;-0.000000;,
  -0.999989;0.004647;0.000004;,
  0.130073;-0.110694;-0.985306;,
  0.000001;0.522042;0.852920;,
  0.000001;0.522042;0.852920;,
  0.000008;1.000000;-0.000000;,
  0.000001;0.266096;-0.963947;,
  0.000001;-0.111643;-0.993748;,
  -0.044103;-0.974742;0.218937;,
  0.267751;-0.211148;-0.940067;,
  -0.287877;-0.133413;-0.948329;,
  0.040058;0.974907;-0.218977;,
  -0.048490;0.974543;-0.218894;,
  -0.267751;0.211148;0.940067;,
  -0.079720;-0.972585;0.218455;,
  -0.872568;0.267449;0.408773;,
  0.079718;0.972586;-0.218454;,
  0.088479;-0.971864;0.218291;,
  -0.721181;-0.116786;-0.682832;,
  -0.082089;0.972397;-0.218414;,
  0.971899;-0.229676;0.051588;,
  0.979380;-0.182303;-0.087067;,
  0.983103;-0.040116;-0.178601;,
  -0.983299;-0.177575;0.039885;,
  -0.977206;-0.159355;-0.140262;,
  -0.966981;-0.055849;-0.248653;,
  -0.009807;-0.179482;-0.983712;,
  0.009807;0.179485;0.983712;,
  -0.007251;0.975665;-0.219147;,
  0.000000;-0.924121;-0.382100;,
  -0.969611;0.000000;-0.244651;,
  0.969605;0.000000;-0.244677;,
  0.000000;0.075503;0.997146;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.996322;-0.085690;,
  0.992057;-0.076701;0.099695;,
  0.994315;-0.106224;-0.007413;,
  0.992490;0.009190;0.121978;,
  0.991839;-0.065465;-0.109410;,
  0.992372;0.000000;-0.123279;,
  0.993121;0.084813;0.080725;,
  0.994127;0.108222;0.000000;,
  0.993940;0.072592;-0.082546;,
  -0.992059;-0.076692;0.099684;,
  -0.994316;-0.106213;-0.007413;,
  -1.000000;0.000000;-0.000001;,
  -0.992492;0.009190;0.121965;,
  -0.991840;-0.065458;-0.109399;,
  -0.992374;0.000000;-0.123267;,
  -0.994128;0.108211;-0.000000;,
  -0.993123;0.084804;0.080717;,
  -0.993941;0.072584;-0.082537;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.075503;0.997146;,
  0.000000;-0.996322;-0.085690;,
  -0.992059;-0.076691;0.099683;,
  -0.994316;-0.106211;-0.007413;,
  -0.992492;0.009189;0.121963;,
  -0.991841;-0.065457;-0.109397;,
  -0.992374;0.000000;-0.123264;,
  -0.993123;0.084802;0.080715;,
  -0.994128;0.108209;0.000000;,
  -0.993941;0.072583;-0.082536;,
  0.992059;-0.076692;0.099684;,
  0.994316;-0.106212;-0.007413;,
  0.992492;0.009189;0.121964;,
  0.991840;-0.065457;-0.109398;,
  0.992374;0.000000;-0.123266;,
  0.994128;0.108210;0.000000;,
  0.993123;0.084803;0.080716;,
  0.993941;0.072584;-0.082537;,
  -0.871365;0.000000;-0.490636;,
  0.871365;0.000000;-0.490636;,
  0.518553;0.000000;-0.855046;,
  0.000000;-0.975691;0.219153;,
  0.048492;-0.974543;0.218896;,
  0.708847;-0.154583;-0.688215;,
  0.287877;0.133415;0.948329;,
  0.714637;0.118351;0.689410;,
  -0.864020;0.110333;0.491220;,
  -0.863735;0.468776;0.184962;,
  -0.671462;0.723023;-0.162408;,
  0.809399;0.572984;-0.128698;,
  0.906627;0.371624;0.199811;,
  0.860682;0.111578;0.496766;,
  0.993165;0.078751;0.086148;,
  -0.260488;0.017603;0.965316;,
  -0.305149;0.108990;0.946047;,
  -0.600077;0.161656;-0.783438;,
  0.000000;0.000000;0.000000;,
  0.996115;0.016410;0.086514;,
  -0.996115;0.016410;0.086515;,
  -0.000000;0.075708;-0.997130;,
  0.000000;0.075708;-0.997130;,
  0.965973;-0.019581;0.257900;,
  0.213036;-0.073971;0.974240;,
  0.000000;-0.075709;0.997130;,
  -0.000000;0.075709;-0.997130;,
  -0.213036;-0.073972;0.974240;,
  -0.965974;-0.019581;0.257895;,
  0.963145;0.019072;0.268304;,
  0.897595;0.353554;0.263291;,
  0.882871;0.469127;0.021425;,
  0.998987;-0.004482;0.044766;,
  -0.240574;0.380810;0.892809;,
  -0.237962;0.015072;0.971157;,
  -0.477893;0.206793;-0.853730;,
  0.150991;-0.903356;0.401433;,
  0.000000;-0.913834;0.406088;,
  -0.742112;-0.062556;-0.667350;,
  -0.616114;-0.079238;-0.783661;,
  -0.782643;0.023608;-0.622023;,
  0.782642;0.023608;-0.622024;,
  0.616113;-0.079238;-0.783662;,
  0.742112;-0.062556;-0.667351;,
  -0.150990;-0.903357;0.401432;,
  0.000000;-0.911951;-0.410300;,
  0.270481;-0.877958;-0.395006;,
  0.742112;0.062556;0.667350;,
  -0.270481;-0.877958;-0.395006;,
  -0.742112;0.062556;0.667351;,
  -0.801560;0.071797;-0.593588;,
  -0.957972;0.221638;-0.182115;,
  0.173632;0.027877;0.984416;,
  0.983395;-0.167850;0.068994;,
  -0.471828;-0.093569;-0.876712;,
  0.957972;0.221638;-0.182115;,
  0.801560;0.071797;-0.593589;,
  0.471828;-0.093569;-0.876712;,
  -0.983395;-0.167851;0.068994;,
  -0.173632;0.027877;0.984416;,
  0.000001;0.279641;0.960105;,
  0.000001;0.279640;0.960105;,
  0.999989;0.004646;-0.000005;,
  0.984294;0.176539;-0.000010;,
  0.239419;-0.469846;-0.849661;,
  0.000000;-0.483920;-0.875112;,
  0.985891;-0.167386;-0.000001;,
  0.000000;0.727772;0.685819;,
  0.000000;0.522042;0.852920;,
  0.000000;0.727772;0.685819;,
  0.000001;0.279640;0.960105;,
  0.000005;1.000000;-0.000000;,
  -0.130072;-0.110694;-0.985306;,
  0.000001;0.266096;-0.963947;,
  -0.239419;-0.469846;-0.849661;,
  0.000000;-0.975691;0.219151;,
  0.048493;-0.974543;0.218894;,
  -0.762760;0.141720;0.630961;,
  0.762760;-0.141721;-0.630961;,
  0.287876;0.133416;0.948329;,
  0.721181;0.116788;0.682831;,
  0.889176;-0.446443;0.100276;,
  -0.932985;0.078876;0.351167;,
  -0.952566;0.274620;0.131157;,
  -0.889175;0.446444;-0.100277;,
  -0.933752;-0.349219;0.078438;,
  0.933752;0.349220;-0.078440;,
  0.947442;0.240152;0.211376;,
  0.870106;0.108011;0.480884;,
  0.000000;0.150575;0.988599;,
  0.000000;-0.975793;0.218696;,
  0.977271;-0.211481;-0.014759;,
  0.982048;-0.115023;0.149506;,
  0.970069;0.018244;0.242143;,
  0.981593;-0.098061;-0.163888;,
  0.984446;0.127257;0.121124;,
  0.976576;0.215173;0.000000;,
  0.986273;0.109044;-0.123996;,
  -0.982052;-0.115010;0.149489;,
  -0.977276;-0.211458;-0.014758;,
  -0.970075;0.018242;0.242117;,
  -0.981597;-0.098050;-0.163870;,
  -0.976581;0.215150;0.000000;,
  -0.984450;0.127243;0.121110;,
  -0.986276;0.109032;-0.123982;,
  0.000000;0.150575;0.988599;,
  0.000000;-0.924121;-0.382100;,
  -0.977276;-0.211455;-0.014758;,
  -0.982052;-0.115009;0.149488;,
  -0.970076;0.018242;0.242115;,
  -0.981597;-0.098049;-0.163868;,
  -0.969612;0.000000;-0.244648;,
  -0.984450;0.127241;0.121109;,
  -0.976582;0.215147;0.000000;,
  -0.986276;0.109031;-0.123981;,
  0.982052;-0.115010;0.149489;,
  0.977276;-0.211458;-0.014758;,
  0.970075;0.018242;0.242117;,
  0.981597;-0.098050;-0.163870;,
  0.969611;0.000000;-0.244651;,
  0.976581;0.215150;0.000000;,
  0.984450;0.127243;0.121110;,
  0.986276;0.109032;-0.123982;,
  -0.518553;0.000000;-0.855046;;
  212;
  4;20,1,1,20;,
  4;22,4,4,22;,
  4;21,5,5,21;,
  4;141,142,142,141;,
  4;13,15,14,12;,
  4;16,19,18,17;,
  4;142,6,6,142;,
  4;5,7,7,5;,
  4;4,8,8,4;,
  4;1,143,143,1;,
  4;0,9,9,0;,
  4;2,10,10,2;,
  4;3,11,11,3;,
  4;144,145,145,144;,
  4;6,13,12,6;,
  4;7,146,147,7;,
  4;8,147,148,8;,
  4;143,15,13,143;,
  4;9,16,17,9;,
  4;10,17,18,10;,
  4;11,149,150,11;,
  4;145,150,151,145;,
  4;0,0,141,141;,
  4;144,144,21,21;,
  4;3,3,22,22;,
  4;2,2,20,20;,
  4;27,24,24,27;,
  4;25,25,25,25;,
  4;28,31,30,29;,
  4;26,26,26,26;,
  4;36,152,152,36;,
  4;33,35,37,37;,
  4;26,26,26,26;,
  4;153,154,28,29;,
  4;25,25,25,25;,
  4;23,23,155,155;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;24,32,32,24;,
  4;26,26,26,26;,
  4;23,34,34,23;,
  4;156,156,156,156;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;157,157,36,36;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;37,158,158,37;,
  4;25,25,25,25;,
  4;159,159,160,160;,
  4;161,161,161,30;,
  4;30,162,163,29;,
  4;164,164,159,159;,
  4;29,163,165,153;,
  4;35,166,166,166;,
  4;60,55,54,61;,
  4;48,43,41,49;,
  4;50,53,52,51;,
  4;46,39,45,47;,
  4;167,168,169,170;,
  4;56,59,58,57;,
  4;44,38,46,47;,
  4;171,172,50,51;,
  4;40,42,48,49;,
  4;173,173,60,61;,
  4;48,51,52,43;,
  4;45,174,175,47;,
  4;62,62,62,62;,
  4;43,169,168,41;,
  4;176,176,177,178;,
  4;63,63,63,63;,
  4;179,180,181,181;,
  4;40,58,59,42;,
  4;42,171,51,48;,
  4;47,175,182,44;,
  4;46,183,184,39;,
  4;185,167,168,185;,
  4;41,55,60,49;,
  4;38,186,183,46;,
  4;49,60,58,40;,
  4;187,187,57,187;,
  4;178,188,189,189;,
  4;190,190,190,53;,
  4;170,191,191,167;,
  4;177,192,188,178;,
  4;193,193,194,179;,
  4;179,194,195,180;,
  4;57,196,196,56;,
  4;172,197,197,197;,
  4;73,66,69,74;,
  4;72,67,67,72;,
  4;71,70,198,199;,
  4;26,26,26,26;,
  4;200,201,201,200;,
  4;68,65,65,68;,
  4;74,69,202,203;,
  4;204,200,200,204;,
  4;205,205,70,71;,
  4;64,68,68,64;,
  4;26,26,26,26;,
  4;206,207,205,71;,
  4;208,206,71,199;,
  4;209,209,72,72;,
  4;210,211,73,74;,
  4;212,210,74,203;,
  4;93,76,76,93;,
  4;95,79,79,95;,
  4;94,80,80,94;,
  4;213,214,214,213;,
  4;88,89,14,87;,
  4;90,19,92,91;,
  4;214,81,81,214;,
  4;80,215,82,80;,
  4;79,83,83,79;,
  4;76,216,216,76;,
  4;75,84,84,75;,
  4;77,85,85,77;,
  4;78,86,86,78;,
  4;217,218,218,217;,
  4;219,88,87,219;,
  4;215,220,221,82;,
  4;82,221,222,222;,
  4;216,89,88,216;,
  4;223,90,91,223;,
  4;85,91,92,85;,
  4;224,224,225,224;,
  4;218,225,226,218;,
  4;75,75,213,213;,
  4;217,217,94,94;,
  4;78,78,95,95;,
  4;77,77,93,93;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;227,99,99,227;,
  4;99,100,100,99;,
  4;228,101,101,228;,
  4;101,96,96,101;,
  4;103,14,104,102;,
  4;105,106,14,103;,
  4;14,108,107,104;,
  4;106,109,108,14;,
  4;110,113,112,111;,
  4;111,112,115,114;,
  4;113,117,116,112;,
  4;112,116,118,115;,
  4;229,103,102,230;,
  4;230,102,104,231;,
  4;232,105,103,229;,
  4;98,106,105,232;,
  4;231,104,107,233;,
  4;233,107,108,234;,
  4;234,108,109,235;,
  4;235,109,106,98;,
  4;236,110,111,237;,
  4;238,113,110,236;,
  4;237,111,114,239;,
  4;239,114,115,97;,
  4;240,116,117,241;,
  4;241,117,113,238;,
  4;97,115,118,242;,
  4;242,118,116,240;,
  4;119,119,119,119;,
  4;119,119,119,119;,
  4;119,119,119,119;,
  4;119,119,119,119;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;243,243,120,120;,
  4;120,120,100,100;,
  4;228,228,121,121;,
  4;121,121,244,244;,
  4;123,122,124,19;,
  4;125,123,19,126;,
  4;19,124,127,128;,
  4;126,19,128,129;,
  4;130,131,14,132;,
  4;131,133,134,14;,
  4;132,14,135,136;,
  4;14,134,137,135;,
  4;245,246,122,123;,
  4;246,247,124,122;,
  4;248,245,123,125;,
  4;249,248,125,126;,
  4;247,250,127,124;,
  4;250,251,128,127;,
  4;251,252,129,128;,
  4;252,249,126,129;,
  4;253,254,131,130;,
  4;255,253,130,132;,
  4;254,256,133,131;,
  4;256,257,134,133;,
  4;258,259,136,135;,
  4;259,255,132,136;,
  4;257,260,137,134;,
  4;260,258,135,137;,
  4;140,139,139,140;,
  4;25,25,25,25;,
  4;100,100,100,100;,
  4;26,26,26,26;,
  4;139,139,14,14;,
  4;19,19,138,138;,
  4;26,26,26,26;,
  4;100,100,100,100;,
  4;25,25,25,25;,
  4;138,138,261,261;;
 }
 MeshTextureCoords {
  224;
  0.835135;0.504619;,
  0.859734;0.495974;,
  0.859734;0.516123;,
  0.835135;0.524768;,
  0.835135;0.503246;,
  0.859734;0.494602;,
  0.835135;0.523396;,
  0.859734;0.514751;,
  0.989411;0.327968;,
  0.989411;0.307819;,
  0.989411;0.306447;,
  0.989411;0.326596;,
  0.699406;0.323502;,
  0.699406;0.303352;,
  0.699406;0.304725;,
  0.699406;0.324874;,
  0.916754;0.510318;,
  0.916754;0.508946;,
  0.916754;0.488797;,
  0.916754;0.490169;,
  0.810534;0.514751;,
  0.753694;0.508946;,
  0.753694;0.510318;,
  0.810534;0.516123;,
  0.753694;0.490169;,
  0.810534;0.495974;,
  0.753694;0.488797;,
  0.810534;0.494602;,
  0.817244;0.079911;,
  0.903317;0.079911;,
  0.903317;0.208912;,
  0.817244;0.208912;,
  0.817244;0.079911;,
  0.903317;0.079911;,
  0.903317;0.079911;,
  0.817244;0.079911;,
  0.817244;0.208912;,
  0.912478;0.208912;,
  0.898569;0.079911;,
  0.817244;0.079911;,
  0.910271;0.208912;,
  0.900613;0.208912;,
  0.817244;0.208912;,
  0.817244;0.208912;,
  0.907461;0.079911;,
  0.914415;0.208912;,
  0.722011;0.208912;,
  0.735919;0.079911;,
  0.727028;0.079911;,
  0.720073;0.208912;,
  0.729883;0.208912;,
  0.724217;0.208912;,
  0.731172;0.079911;,
  0.731172;0.079911;,
  0.731172;0.208912;,
  0.731172;0.079911;,
  0.817244;0.033090;,
  0.817244;0.033090;,
  0.898569;0.033090;,
  0.903317;0.033090;,
  0.916352;0.079911;,
  0.916352;0.208912;,
  0.718136;0.208912;,
  0.718136;0.079911;,
  0.731172;0.033090;,
  0.735919;0.033090;,
  0.813267;0.039469;,
  0.906050;0.032488;,
  0.919219;0.111655;,
  0.813267;0.119704;,
  0.813267;0.007646;,
  0.875182;0.007646;,
  0.875182;0.007646;,
  0.813267;0.007646;,
  0.813267;0.124734;,
  0.914283;0.118654;,
  0.904682;0.038418;,
  0.813267;0.044499;,
  0.813267;0.124734;,
  0.910844;0.124734;,
  0.899332;0.124734;,
  0.813267;0.124734;,
  0.712252;0.118654;,
  0.721853;0.038418;,
  0.720485;0.032488;,
  0.707315;0.111655;,
  0.727203;0.124734;,
  0.715691;0.124734;,
  0.751353;0.007646;,
  0.751353;0.007646;,
  0.910844;0.124734;,
  0.919219;0.111655;,
  0.914283;0.118654;,
  0.899332;0.124734;,
  0.727203;0.124734;,
  0.712252;0.118654;,
  0.707315;0.111655;,
  0.715691;0.124734;,
  0.149022;0.018421;,
  0.168454;0.018421;,
  0.193571;0.158461;,
  0.149022;0.158461;,
  0.149022;0.018421;,
  0.168454;0.018421;,
  0.149022;0.158461;,
  0.193571;0.158461;,
  0.149022;0.271603;,
  0.174362;0.271603;,
  0.174362;0.271603;,
  0.149022;0.271603;,
  0.104473;0.158461;,
  0.129590;0.018421;,
  0.129590;0.018421;,
  0.104473;0.158461;,
  0.123682;0.271603;,
  0.123682;0.271603;,
  0.835135;0.469561;,
  0.859734;0.460916;,
  0.859734;0.481065;,
  0.835135;0.489710;,
  0.835135;0.468188;,
  0.859734;0.459544;,
  0.835135;0.488338;,
  0.859734;0.479693;,
  0.955711;0.284083;,
  0.955711;0.263934;,
  0.955711;0.262562;,
  0.955711;0.282711;,
  0.720515;0.280126;,
  0.720515;0.259977;,
  0.720515;0.261349;,
  0.720515;0.281498;,
  0.916754;0.475260;,
  0.916754;0.473888;,
  0.916754;0.453739;,
  0.916754;0.455111;,
  0.810534;0.479693;,
  0.753694;0.473888;,
  0.753694;0.475260;,
  0.810534;0.481065;,
  0.753694;0.455111;,
  0.810534;0.460916;,
  0.753694;0.453739;,
  0.810534;0.459544;,
  0.026621;0.040533;,
  0.112869;0.040533;,
  0.112869;0.040533;,
  0.026621;0.040533;,
  0.253301;0.040533;,
  0.253301;0.040533;,
  0.271987;0.127499;,
  0.271987;0.127499;,
  0.271987;0.214464;,
  0.271987;0.214464;,
  0.112869;0.239743;,
  0.112869;0.239743;,
  0.026621;0.214464;,
  0.026621;0.214464;,
  0.116174;0.230709;,
  0.116174;0.128645;,
  0.260859;0.128645;,
  0.260859;0.207723;,
  0.037748;0.207723;,
  0.037748;0.128645;,
  0.116174;0.049567;,
  0.243868;0.049567;,
  0.037748;0.049567;,
  0.260859;0.207723;,
  0.260859;0.128645;,
  0.116174;0.128645;,
  0.116174;0.230709;,
  0.037748;0.128645;,
  0.037748;0.207723;,
  0.243868;0.049567;,
  0.116174;0.049567;,
  0.037748;0.049567;,
  0.026621;0.127499;,
  0.026621;0.127499;,
  0.026621;0.214464;,
  0.026621;0.214464;,
  0.026621;0.127499;,
  0.026621;0.127499;,
  0.026621;0.040533;,
  0.026621;0.040533;,
  0.112869;0.040533;,
  0.112869;0.040533;,
  0.253301;0.040533;,
  0.253301;0.040533;,
  0.271987;0.127499;,
  0.271987;0.127499;,
  0.271987;0.214464;,
  0.271987;0.214464;,
  0.112869;0.239743;,
  0.112869;0.239743;,
  0.116174;0.230709;,
  0.260859;0.207723;,
  0.260859;0.128645;,
  0.116174;0.128645;,
  0.037748;0.207723;,
  0.037748;0.128645;,
  0.243868;0.049567;,
  0.116174;0.049567;,
  0.037748;0.049567;,
  0.260859;0.207723;,
  0.116174;0.230709;,
  0.116174;0.128645;,
  0.260859;0.128645;,
  0.037748;0.207723;,
  0.037748;0.128645;,
  0.116174;0.049567;,
  0.243868;0.049567;,
  0.037748;0.049567;,
  0.809781;0.591946;,
  0.931134;0.591946;,
  0.931134;0.675070;,
  0.809781;0.675070;,
  0.809781;0.591946;,
  0.931134;0.591946;,
  0.809781;0.675070;,
  0.931134;0.675070;,
  0.688429;0.675070;,
  0.688429;0.591946;,
  0.688429;0.591946;,
  0.688429;0.675070;;
 }
}
