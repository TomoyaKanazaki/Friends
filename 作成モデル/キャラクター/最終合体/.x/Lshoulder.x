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
 144;
 11.71854;4.34174;-21.86040;,
 10.33518;5.98087;-22.87369;,
 21.35611;8.44627;-22.87369;,
 20.54508;7.90131;-21.24886;,
 49.10093;71.79070;3.53967;,
 35.81602;50.49541;-15.20855;,
 34.21555;50.76874;3.53967;,
 12.19248;5.70961;27.39580;,
 12.95162;3.48164;25.11703;,
 21.06615;7.21020;25.11703;,
 21.65974;9.81483;27.39580;,
 49.86010;67.80205;3.53967;,
 36.32891;45.58014;22.28789;,
 36.45205;46.04347;3.53967;,
 35.56974;49.56886;22.28789;,
 12.25094;19.10744;-15.28783;,
 12.64395;19.93240;21.57286;,
 12.74326;21.66054;-15.20855;,
 12.62018;23.75038;3.53967;,
 12.49704;21.39301;22.28789;,
 11.95406;18.69736;-18.62109;,
 22.92336;23.11836;-18.62109;,
 36.57518;46.50692;-15.20855;,
 22.27896;25.00229;-20.49553;,
 11.96594;19.64176;-20.49553;,
 12.48188;21.46828;25.10563;,
 23.40719;26.38260;25.82065;,
 23.45751;22.40620;24.57863;,
 12.31783;19.20616;24.54674;,
 -0.96977;0.27206;-28.19111;,
 -2.70060;2.32277;-29.45890;,
 11.08826;5.40733;-29.45890;,
 10.07357;4.72542;-27.42599;,
 34.57285;68.90984;3.58816;,
 25.78959;51.95080;-19.86866;,
 24.78838;52.12173;-8.14025;,
 23.78717;52.29271;3.58816;,
 -0.37685;1.98334;33.43574;,
 0.57302;-0.80410;30.58466;,
 10.72546;3.86078;30.58466;,
 11.46809;7.11967;33.43574;,
 35.52267;63.91953;3.58816;,
 26.43129;45.80116;27.04498;,
 26.58537;46.38088;3.58816;,
 25.48143;50.79147;27.04498;,
 -0.30363;18.74611;-19.96785;,
 0.18803;19.77814;26.15038;,
 0.31237;21.94054;-19.86866;,
 0.23531;23.24783;-8.14025;,
 0.15823;24.55513;3.58816;,
 0.08123;23.08044;15.31657;,
 0.00425;21.60576;27.04498;,
 -0.67511;18.23292;-24.13825;,
 13.04911;23.76457;-24.13825;,
 26.73941;46.96053;-19.86866;,
 12.24287;26.12122;-26.48347;,
 -0.66027;19.41460;-26.48347;,
 -0.01471;21.69983;30.57041;,
 13.65450;27.84843;31.46500;,
 13.71744;22.87331;29.91105;,
 -0.22001;18.86951;29.87113;,
 0.31237;21.94054;-19.86866;,
 0.23531;23.24783;-8.14025;,
 24.78838;52.12173;-8.14025;,
 25.78959;51.95080;-19.86866;,
 24.63430;51.54209;15.31657;,
 40.43039;16.49673;-15.84105;,
 53.60353;15.56553;-11.73510;,
 53.60353;3.57132;-11.73510;,
 41.11296;2.62451;-21.52359;,
 -7.94968;0.02972;3.64363;,
 -7.91018;10.51559;3.29966;,
 -7.91018;10.51559;-9.45781;,
 -7.94968;0.02972;-9.45781;,
 27.40938;-14.37031;27.17036;,
 40.05659;-11.49872;22.52126;,
 40.06147;2.20573;25.70219;,
 27.40942;0.98404;26.12274;,
 54.86311;-9.91081;16.34711;,
 54.86311;-9.91081;-10.54078;,
 54.86311;3.57132;16.34711;,
 54.86311;17.05345;16.34711;,
 54.86311;17.05345;-10.54078;,
 53.60353;18.25123;-9.05702;,
 27.40938;18.45238;-14.98761;,
 27.40938;18.45238;20.79392;,
 53.60353;18.25123;14.86335;,
 53.60353;-11.10847;14.86335;,
 27.40938;-17.05593;20.79392;,
 27.40938;-17.05593;-14.98761;,
 53.60353;-11.10847;-9.05702;,
 53.60353;-8.42285;-11.73510;,
 40.14120;17.52300;-14.99089;,
 25.41929;17.99255;-19.44100;,
 27.40938;17.41714;-19.89958;,
 27.40938;1.68427;-25.13634;,
 25.41929;1.46217;-24.60988;,
 40.49280;-11.39969;-17.81735;,
 40.14120;-13.25348;-16.98456;,
 25.41929;-16.59607;26.71179;,
 25.41929;0.69824;25.62735;,
 25.41929;17.99255;24.54293;,
 27.40938;17.41714;25.00149;,
 40.06765;16.52237;21.39643;,
 40.14120;17.52300;20.44501;,
 53.60353;3.51345;17.54142;,
 53.60353;-8.42285;17.54142;,
 40.14120;-13.25348;21.52945;,
 25.41929;-16.59607;-23.42834;,
 17.42094;17.22763;-19.44100;,
 17.39063;0.69782;-23.77888;,
 9.42259;16.46278;-19.44100;,
 9.42259;16.46278;24.54293;,
 9.29802;-16.59607;26.71179;,
 9.29802;-16.59607;-23.42834;,
 17.35867;-16.59607;-23.42834;,
 9.29802;-16.59607;-29.60425;,
 -0.12455;-16.52943;-29.60425;,
 0.00000;16.52943;-24.53489;,
 9.42259;16.46278;-24.53489;,
 0.00000;16.52943;23.01343;,
 0.00000;16.52943;2.90316;,
 0.00000;16.52943;-17.20711;,
 9.42259;16.46278;30.34122;,
 0.00000;16.52943;30.34122;,
 -0.12455;-16.52943;30.64706;,
 9.29802;-16.59607;30.64706;,
 -0.12455;-16.52943;-17.20711;,
 -0.12455;-16.52943;3.98760;,
 -0.12455;-16.52943;25.18230;,
 9.36033;-0.06664;-21.43467;,
 -0.06227;0.00000;-17.20711;,
 -0.06227;0.00000;24.09787;,
 27.40938;-14.37031;-23.88691;,
 53.60353;15.56553;17.54142;,
 -7.94968;0.02972;16.74506;,
 -7.91018;10.51559;16.05712;,
 -7.98918;-10.45616;3.98760;,
 -7.98918;-10.45616;17.43300;,
 -7.98918;-10.45616;-9.45781;,
 0.08123;23.08044;15.31657;,
 0.00425;21.60576;27.04498;,
 25.48143;50.79147;27.04498;,
 24.63430;51.54209;15.31657;;
 
 161;
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
 3;113,99,112;,
 3;112,99,101;,
 3;101,99,100;,
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
 3;118,127,122;,
 3;122,127,131;,
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
 4;131,73,72,122;,
 4;122,72,71,121;,
 4;121,71,136,120;,
 4;120,136,135,132;,
 4;132,135,138,129;,
 4;129,138,137,128;,
 4;127,139,73,131;,
 4;128,137,139,127;,
 4;48,49,36,35;,
 4;140,141,142,143;;
 
 MeshMaterialList {
  1;
  161;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\union\\SuperUnion\\Arm\\union_arm_UV_Yellow.jpg";
   }
  }
 }
 MeshNormals {
  180;
  -0.982156;0.183961;0.039083;,
  0.716634;-0.674164;0.178712;,
  -0.926983;0.358152;-0.111487;,
  -0.727548;0.646800;-0.228742;,
  -0.980710;0.195463;0.001344;,
  0.575585;0.017600;0.817552;,
  -0.999548;0.022577;-0.019859;,
  0.819026;-0.434568;0.374630;,
  0.264595;-0.506381;0.820712;,
  0.875379;-0.152970;-0.458597;,
  -0.944549;0.328141;-0.012271;,
  -0.322160;0.481934;0.814833;,
  0.401294;-0.102615;0.910183;,
  0.192093;-0.399104;-0.896558;,
  0.239230;-0.744127;-0.623734;,
  0.113794;-0.294795;0.948761;,
  0.290246;-0.650442;0.701914;,
  -0.816087;0.577861;0.008852;,
  0.906227;-0.341391;0.249407;,
  -0.798011;0.602602;0.006970;,
  0.802583;-0.596465;-0.009471;,
  -0.952560;0.304335;-0.003150;,
  -0.982156;0.183963;0.039087;,
  0.724733;-0.666672;0.174100;,
  -0.924121;0.366125;-0.109327;,
  -0.728247;0.647120;-0.225592;,
  -0.978555;0.205979;0.001933;,
  0.694150;0.037780;0.718838;,
  -0.999848;-0.004341;-0.016887;,
  0.851209;-0.418784;0.316327;,
  0.265350;-0.515120;0.815010;,
  0.885278;-0.144125;-0.442167;,
  -0.943195;0.332149;-0.007768;,
  -0.323302;0.489501;0.809855;,
  0.814608;-0.121041;0.567241;,
  0.192295;-0.405063;-0.893838;,
  0.239223;-0.744120;-0.623746;,
  0.113793;-0.294793;0.948761;,
  0.290244;-0.650438;0.701918;,
  -0.838774;0.544423;0.007884;,
  0.986965;-0.160930;0.001354;,
  -0.801279;0.598254;0.006685;,
  0.815168;-0.579156;-0.008959;,
  -0.947979;0.318318;-0.002966;,
  0.884631;-0.332148;-0.327271;,
  0.718448;0.361938;-0.593998;,
  0.137946;-0.960264;-0.242619;,
  -0.022882;0.483706;-0.874931;,
  0.031079;-0.074542;0.996733;,
  -0.028235;0.987302;0.156328;,
  0.744410;-0.474167;0.470126;,
  0.877110;0.312129;0.365039;,
  0.602715;-0.126347;-0.787890;,
  0.489652;0.255841;-0.833538;,
  0.097027;0.507633;-0.856092;,
  0.212910;-0.257407;-0.942556;,
  0.114540;-0.175862;0.977729;,
  0.048105;0.373562;0.926357;,
  0.464554;0.243912;0.851291;,
  0.522580;-0.172576;0.834942;,
  0.254267;0.940709;0.224534;,
  0.254707;0.943253;-0.213068;,
  -0.016149;0.992645;0.119984;,
  -0.019131;0.994383;-0.104098;,
  0.392222;-0.904824;0.165696;,
  0.395460;-0.907001;-0.144779;,
  0.133219;-0.988243;-0.075021;,
  0.137613;-0.985103;0.103123;,
  -0.005658;-0.999984;0.000000;,
  -0.027047;0.999634;0.000000;,
  -0.027047;0.999634;-0.000000;,
  0.000000;0.065465;0.997855;,
  -0.218605;-0.975814;0.000000;,
  -0.152057;0.988372;0.000000;,
  -0.206827;0.978378;0.000000;,
  -0.164529;-0.986372;0.000000;,
  0.001072;0.151568;-0.988446;,
  0.000065;0.009251;0.999957;,
  0.999993;-0.003767;-0.000005;,
  -0.134944;0.117991;-0.983803;,
  0.054969;0.108268;-0.992601;,
  0.598320;0.012289;-0.801163;,
  0.169507;0.861951;-0.477815;,
  0.310350;0.484690;-0.817777;,
  0.411153;0.057922;-0.909724;,
  0.454689;-0.291848;-0.841477;,
  0.386574;-0.784637;-0.484671;,
  -0.117311;0.231654;-0.965699;,
  -0.106815;0.118727;-0.987165;,
  0.000000;-1.000000;-0.000000;,
  -0.248720;0.063275;0.966506;,
  -0.037104;0.056220;0.997729;,
  0.562207;0.005732;0.826977;,
  0.918710;0.000000;0.394934;,
  0.162598;0.854911;0.492634;,
  0.262801;0.436218;0.860610;,
  0.301827;0.029160;0.952917;,
  0.365281;-0.270622;0.890693;,
  0.355998;-0.775394;0.521564;,
  -0.315974;0.948768;0.000000;,
  -0.326240;-0.945287;0.000000;,
  -0.916709;0.029595;0.398457;,
  0.000000;0.000000;1.000000;,
  -0.999993;0.003767;0.000000;,
  -0.922173;0.003474;-0.386761;,
  -0.906555;0.315468;-0.280425;,
  -0.895046;0.445974;0.000000;,
  -0.916709;0.029595;0.398457;,
  -0.897851;0.333957;0.286945;,
  -0.898381;-0.439217;0.000000;,
  -0.910955;-0.292991;0.290373;,
  -0.908906;-0.308628;-0.280425;,
  -0.786576;0.612677;-0.076972;,
  -0.942032;0.332814;-0.042541;,
  -0.782867;0.615703;0.089607;,
  -0.951863;0.304243;0.037323;,
  0.719135;0.136874;0.681257;,
  0.692243;-0.709369;0.132647;,
  0.644140;-0.007673;-0.764869;,
  -0.320036;0.464548;-0.825695;,
  -0.966101;0.080602;0.245259;,
  -0.488387;0.736260;0.468400;,
  -0.712476;0.665379;0.222820;,
  0.335891;-0.692464;-0.638492;,
  0.578502;-0.740939;-0.341092;,
  -0.997776;0.005466;-0.066439;,
  0.047110;-0.200685;0.978522;,
  0.993104;-0.114006;0.027341;,
  -0.057616;0.160968;-0.985276;,
  -0.912370;-0.020576;0.408849;,
  0.987705;-0.118107;0.102423;,
  0.014998;-0.036565;-0.999219;,
  -0.997566;-0.005411;-0.069525;,
  0.727112;0.138395;-0.672425;,
  0.982326;0.186972;0.008759;,
  0.668402;-0.732754;0.127710;,
  0.754998;0.013739;-0.655583;,
  -0.319499;0.471757;-0.821806;,
  -0.966099;0.080600;0.245269;,
  -0.487925;0.745997;0.453230;,
  -0.712784;0.666613;0.218096;,
  0.335300;-0.701326;-0.629059;,
  0.558893;-0.759095;-0.333787;,
  -0.997776;0.005474;-0.066436;,
  0.047110;-0.200685;0.978522;,
  0.993105;-0.114002;0.027333;,
  -0.057615;0.160968;-0.985276;,
  -0.912365;-0.020579;0.408861;,
  0.987703;-0.118109;0.102435;,
  0.014999;-0.036565;-0.999219;,
  -0.997566;-0.005410;-0.069520;,
  0.172882;0.832951;0.525646;,
  -0.083532;0.995480;-0.045186;,
  0.012299;-0.999034;0.042178;,
  -0.095196;0.995459;-0.000000;,
  -0.002992;0.064023;0.997944;,
  -0.118066;0.063482;0.990975;,
  1.000000;0.000000;-0.000000;,
  -0.003536;-0.999994;0.000000;,
  0.999993;-0.003767;-0.000000;,
  0.999993;-0.003768;-0.000003;,
  0.999993;-0.003768;-0.000005;,
  0.999993;-0.003768;-0.000000;,
  0.007073;0.999975;0.000000;,
  -0.999993;0.003767;0.000000;,
  -0.966840;0.003643;-0.255357;,
  -0.999993;0.003767;0.000000;,
  -0.922173;0.003474;-0.386761;,
  -0.007072;-0.999975;0.000000;,
  0.999993;-0.003768;-0.000000;,
  -0.916709;0.029595;0.398457;,
  -0.999993;0.003767;-0.000000;,
  -0.964602;0.020881;0.262882;,
  0.007073;0.999975;0.000000;,
  -0.125233;-0.056476;-0.990519;,
  -0.094891;0.004179;-0.995479;,
  -0.149927;0.119227;-0.981482;,
  -0.158146;0.186856;-0.969574;,
  -0.140991;0.051026;-0.988695;,
  -0.700827;0.002640;-0.713327;;
  161;
  4;14,14,14,14;,
  3;17,3,19;,
  4;15,16,16,15;,
  3;18,7,20;,
  4;116,5,7,18;,
  3;0,6,2;,
  3;2,6,21;,
  3;21,6,4;,
  4;117,8,8,1;,
  4;118,9,9,118;,
  4;3,119,10,2;,
  4;2,10,120,0;,
  4;121,11,11,122;,
  4;5,12,12,7;,
  4;123,13,13,124;,
  4;6,125,125,4;,
  4;8,126,126,8;,
  4;9,127,127,9;,
  4;119,128,128,128;,
  4;10,129,129,120;,
  4;11,15,15,11;,
  4;130,130,130,130;,
  4;13,131,131,13;,
  4;125,132,132,125;,
  4;118,118,133,133;,
  4;2,21,19,3;,
  3;124,117,7;,
  3;117,20,7;,
  3;20,117,1;,
  3;122,17,19;,
  3;1,18,20;,
  4;21,4,122,19;,
  4;36,36,36,36;,
  4;39,25,112,41;,
  4;37,38,38,37;,
  3;40,29,42;,
  4;134,27,29,40;,
  3;22,28,24;,
  3;24,28,113;,
  3;113,28,43;,
  3;43,28,115;,
  3;115,28,26;,
  4;135,30,30,23;,
  4;136,31,31,136;,
  4;25,137,32,24;,
  4;24,32,138,22;,
  4;139,33,33,140;,
  4;27,34,34,29;,
  4;141,35,35,142;,
  4;28,143,143,26;,
  4;30,144,144,30;,
  4;31,145,145,31;,
  4;137,146,146,146;,
  4;32,147,147,138;,
  4;33,37,37,33;,
  4;34,148,148,34;,
  4;35,149,149,35;,
  4;143,150,150,143;,
  4;136,136,134,40;,
  4;24,113,112,25;,
  3;142,135,29;,
  3;29,135,42;,
  3;42,135,23;,
  4;140,39,41,114;,
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
  3;60,94,151;,
  4;49,62,63,152;,
  3;152,63,82;,
  3;63,61,82;,
  3;82,61,45;,
  4;50,64,65,44;,
  3;46,86,66;,
  3;66,86,65;,
  3;65,86,44;,
  4;46,66,67,153;,
  3;153,67,98;,
  3;67,64,98;,
  3;98,64,50;,
  4;87,47,79,88;,
  3;69,70,154;,
  3;70,49,154;,
  3;154,49,152;,
  3;71,48,155;,
  3;155,48,156;,
  3;157,157,157;,
  3;68,89,158;,
  3;158,89,153;,
  3;153,89,46;,
  4;76,76,76,76;,
  3;74,70,99;,
  3;99,70,73;,
  3;73,70,69;,
  4;77,77,77,77;,
  3;72,68,100;,
  3;100,68,75;,
  3;75,68,158;,
  3;159,78,160;,
  3;78,161,160;,
  3;160,161,162;,
  4;69,163,163,73;,
  3;164,165,166;,
  3;166,165,167;,
  3;102,102,102;,
  4;72,168,168,68;,
  4;169,169,169,169;,
  4;158,168,168,75;,
  3;170,101,171;,
  3;101,172,171;,
  3;171,172,164;,
  4;74,173,173,70;,
  4;174,175,88,79;,
  4;80,55,174,79;,
  4;52,85,84,81;,
  4;83,54,47,82;,
  4;80,54,83,84;,
  4;85,55,80,84;,
  4;46,55,85,86;,
  4;176,177,87,88;,
  4;175,178,176,88;,
  4;91,57,156,90;,
  4;95,57,91,96;,
  4;51,58,92,93;,
  4;95,58,51,94;,
  4;92,58,95,96;,
  4;97,59,92,96;,
  4;50,59,97,98;,
  4;107,108,106,103;,
  4;109,110,107,103;,
  4;111,109,103,104;,
  4;179,104,105,167;,
  4;73,105,106,99;,
  4;99,106,108,74;,
  4;170,108,107,101;,
  4;101,107,110,172;,
  4;75,110,109,100;,
  4;165,111,104,179;,
  4;100,109,111,72;,
  4;113,43,41,112;,
  4;115,26,140,114;;
 }
 MeshTextureCoords {
  144;
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
  0.597553;0.948540;,
  0.596771;0.961198;,
  0.855583;0.710674;,
  0.846977;0.704231;;
 }
}
