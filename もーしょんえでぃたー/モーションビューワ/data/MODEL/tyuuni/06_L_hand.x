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
 291;
 3.44196;-0.07049;0.96195;,
 1.29443;-0.07049;1.24371;,
 1.29443;0.80895;0.87942;,
 3.44196;0.60971;0.68020;,
 3.44196;-0.75069;0.68020;,
 1.29443;-0.94991;0.87942;,
 3.44196;-1.03245;-0.00000;,
 1.29443;-1.31419;-0.00000;,
 3.44196;-0.75069;-0.68020;,
 1.29443;-0.94991;-0.87942;,
 3.44196;-0.07049;-0.96195;,
 1.29443;-0.07049;-1.24371;,
 3.44196;0.60971;-0.68020;,
 1.29443;0.80895;-0.87942;,
 3.44196;0.89147;0.00000;,
 1.29443;1.17322;0.00000;,
 0.00000;-0.07049;-0.00000;,
 0.00000;-0.07049;2.03028;,
 1.29443;-0.07049;2.60411;,
 1.29443;1.77089;1.84138;,
 0.00000;1.36514;1.43562;,
 0.00000;-1.50612;1.43562;,
 1.29443;-1.91187;1.84138;,
 0.00000;-2.10076;-0.00000;,
 1.29443;-2.67461;-0.00000;,
 0.00000;-1.50612;-1.43562;,
 1.29443;-1.91187;-1.84138;,
 0.00000;-0.07049;-2.03028;,
 1.29443;-0.07049;-2.60411;,
 0.00000;1.36514;-1.43562;,
 1.29443;1.77089;-1.84138;,
 0.00000;1.95980;0.00000;,
 1.29443;2.53363;0.00000;,
 3.44196;-0.07049;2.88586;,
 3.44196;1.97012;2.04062;,
 3.44196;-2.11110;2.04062;,
 3.44196;-2.95635;-0.00000;,
 3.44196;-2.11110;-2.04062;,
 3.44196;-0.07049;-2.88586;,
 3.44196;1.97012;-2.04062;,
 3.44196;2.81538;0.00000;,
 5.87707;-0.07049;2.60411;,
 5.87707;1.77089;1.84138;,
 5.87707;-1.91187;1.84138;,
 5.87707;-2.67461;-0.00000;,
 5.87707;-1.91187;-1.84138;,
 5.87707;-0.07049;-2.60411;,
 5.87707;1.77089;-1.84138;,
 5.87707;2.53363;0.00000;,
 7.41145;-0.07049;1.92389;,
 7.41145;1.28993;1.36042;,
 7.41145;-1.43090;1.36042;,
 7.41145;-1.99439;-0.00000;,
 7.41145;-1.43090;-1.36042;,
 7.41145;-0.07049;-1.92389;,
 7.41145;1.28993;-1.36042;,
 7.41145;1.85341;0.00000;,
 5.87707;-0.07049;1.24371;,
 5.87707;0.80895;0.87942;,
 5.87707;-0.94991;0.87942;,
 5.87707;-1.31419;-0.00000;,
 5.87707;-0.94991;-0.87942;,
 5.87707;-0.07049;-1.24371;,
 5.87707;0.80895;-0.87942;,
 5.87707;1.17322;0.00000;,
 -0.94361;-0.07049;0.00000;,
 -0.44398;0.85479;0.92527;,
 -0.44398;1.23806;0.00000;,
 -0.44398;0.85479;-0.92527;,
 -0.44398;-0.07049;-1.30852;,
 -0.44398;-0.99576;-0.92527;,
 -0.44398;-1.37900;0.00000;,
 -0.44398;-0.99576;0.92527;,
 -0.44398;-0.07049;1.30852;,
 10.03091;3.49912;-0.73330;,
 10.82299;3.49459;-1.28523;,
 10.42948;3.23281;-2.65571;,
 8.90737;3.35229;-1.60477;,
 11.78385;3.48713;-1.20591;,
 15.23072;3.09307;-3.49046;,
 12.55986;3.47141;-0.55462;,
 15.60735;3.06520;-1.42911;,
 12.83317;3.45389;0.31219;,
 15.54673;2.80964;0.41285;,
 12.48880;3.45177;1.15362;,
 15.45379;3.02278;2.26231;,
 11.66137;3.45333;1.73852;,
 14.90726;3.00366;4.28548;,
 10.69720;3.45983;1.73805;,
 10.19168;3.16706;3.06055;,
 9.95372;3.47774;1.12266;,
 8.76193;3.31209;1.89175;,
 9.69425;3.49372;0.18237;,
 8.25788;3.33659;0.11957;,
 10.07026;2.81689;-3.88606;,
 7.88459;2.85246;-2.39858;,
 16.34520;2.68703;-3.52969;,
 16.69520;2.83299;-1.43669;,
 16.57072;2.62616;0.45188;,
 16.53765;2.78951;2.35122;,
 16.01526;2.59588;4.40152;,
 9.73214;2.72347;4.24035;,
 7.67756;2.79521;2.57850;,
 6.96735;2.82832;0.05619;,
 9.84778;1.64074;-4.65315;,
 7.23822;1.66655;-2.91678;,
 17.09897;1.44794;-3.66515;,
 17.35859;1.54667;-1.52249;,
 17.34187;1.56362;0.46389;,
 17.19360;1.50107;2.44331;,
 16.75712;1.35347;4.55236;,
 9.44865;1.53047;4.94167;,
 6.99224;1.59857;2.99633;,
 6.15455;1.64231;0.00000;,
 9.76265;0.39698;-4.91843;,
 7.01615;0.39784;-3.10148;,
 17.78008;0.22902;-3.66267;,
 17.98244;0.30865;-1.51623;,
 18.02062;0.34507;0.46911;,
 17.81782;0.26322;2.44198;,
 17.43683;0.13527;4.56195;,
 9.34703;0.26819;5.15278;,
 13.14832;0.20684;4.96885;,
 6.75759;0.32637;3.11409;,
 5.87707;0.37241;-0.03551;,
 9.77827;-0.98084;-4.62840;,
 7.21398;-0.90385;-2.96943;,
 16.34056;-1.64143;-3.34276;,
 16.62136;-1.56719;-1.57621;,
 16.78045;-1.63057;0.36500;,
 16.45528;-1.62380;2.28713;,
 16.04491;-1.59193;4.42631;,
 13.27880;0.07580;4.82470;,
 6.95184;-0.94652;2.94662;,
 9.45164;-1.02451;4.88132;,
 6.11417;-0.90275;-0.04969;,
 10.02940;-1.30068;-3.71866;,
 7.87226;-2.09536;-2.54907;,
 14.78365;-1.21312;-3.39305;,
 16.13398;-1.35362;-3.47036;,
 16.15688;-1.35969;-1.55866;,
 14.27960;-1.68799;-1.55567;,
 14.80829;-0.82877;-3.46235;,
 16.31378;-1.42843;0.34962;,
 14.35772;-1.79536;0.25649;,
 15.99335;-1.41572;2.23930;,
 14.12394;-1.74130;2.05911;,
 15.80621;-1.46590;4.14088;,
 13.79931;-1.66595;3.99701;,
 13.19171;0.20857;4.34720;,
 13.21362;0.18551;3.98257;,
 7.55628;-2.09652;2.51010;,
 9.74866;-2.16207;4.15595;,
 6.84301;-2.05929;-0.04120;,
 10.46544;-1.35381;-2.76374;,
 8.94716;-3.04092;-1.77095;,
 15.03380;-0.93974;-3.54787;,
 13.65086;-0.85444;-1.58460;,
 15.10018;-0.93786;-3.45623;,
 13.60213;-0.93182;0.24455;,
 13.49334;-0.90842;2.07359;,
 13.24674;-0.53555;4.01864;,
 13.21070;0.09916;3.67085;,
 8.68994;-3.08785;1.73853;,
 10.23344;-3.10935;2.85367;,
 8.18809;-3.06021;-0.00405;,
 14.21185;-0.93190;-1.03123;,
 13.58125;-0.90792;-0.63110;,
 14.89259;-0.91114;-0.91784;,
 13.53026;-0.44888;-1.59872;,
 15.26506;-0.52973;-0.31742;,
 13.49271;-0.52312;0.24908;,
 15.48371;-0.55609;0.37260;,
 13.34728;-0.51883;1.97886;,
 15.22824;-0.55654;0.99509;,
 13.25793;-0.52110;4.05000;,
 14.66759;-0.79366;1.40126;,
 14.18333;-0.95285;1.71614;,
 13.43783;-0.19714;3.96059;,
 13.49882;-0.91523;0.99674;,
 13.27621;-0.91363;0.27116;,
 10.83841;3.08561;-1.17708;,
 10.08194;3.08695;-0.67402;,
 11.23940;3.10968;0.23942;,
 11.74601;3.07638;-1.13951;,
 12.45811;3.06281;-0.57562;,
 12.70265;3.05001;0.29914;,
 12.38632;3.04297;1.15069;,
 11.62981;3.04432;1.65375;,
 10.72218;3.05350;1.61617;,
 10.01012;3.06709;1.05230;,
 9.76557;3.07989;0.17753;,
 14.55861;-0.76145;0.32758;,
 13.41563;-0.05366;4.36788;,
 10.83841;3.08561;-1.17708;,
 10.08194;3.08695;-0.67402;,
 11.74601;3.07638;-1.13951;,
 12.45811;3.06281;-0.57562;,
 12.70265;3.05001;0.29914;,
 12.38632;3.04297;1.15069;,
 11.62981;3.04432;1.65375;,
 10.72218;3.05350;1.61617;,
 10.01012;3.06709;1.05230;,
 9.76557;3.07989;0.17753;,
 16.13398;-1.35362;-3.47036;,
 16.15688;-1.35969;-1.55866;,
 16.31378;-1.42843;0.34962;,
 15.99335;-1.41572;2.23930;,
 15.80621;-1.46590;4.14088;,
 13.19171;0.20857;4.34720;,
 14.80829;-0.82877;-3.46235;,
 15.10018;-0.93786;-3.45623;,
 13.65086;-0.85444;-1.58460;,
 13.60213;-0.93182;0.24455;,
 13.49271;-0.52312;0.24908;,
 13.53026;-0.44888;-1.59872;,
 13.65086;-0.85444;-1.58460;,
 13.49334;-0.90842;2.07359;,
 13.34728;-0.51883;1.97886;,
 13.24674;-0.53555;4.01864;,
 13.49334;-0.90842;2.07359;,
 13.21070;0.09916;3.67085;,
 13.21362;0.18551;3.98257;,
 9.24640;0.63630;-3.13849;,
 8.88050;-0.20713;-3.21460;,
 10.35193;-0.64406;-2.39276;,
 10.82833;0.28280;-2.64895;,
 8.58518;-0.45744;-3.72020;,
 11.12209;-1.68935;-3.39946;,
 8.61836;-0.95867;-3.93390;,
 10.93471;-2.00506;-4.45086;,
 8.61110;-0.37072;-4.12666;,
 11.14180;-1.52953;-5.44924;,
 8.96769;-0.01716;-4.22901;,
 11.51013;-0.68192;-5.72243;,
 9.23950;0.65209;-3.85957;,
 11.86079;0.11961;-5.31755;,
 9.69707;1.07329;-3.44416;,
 12.06803;0.49174;-4.32483;,
 12.41662;-1.11563;-2.89737;,
 12.85882;-0.16767;-3.24203;,
 12.06074;-1.94312;-3.36476;,
 11.98087;-2.29030;-4.40277;,
 12.24592;-1.87147;-5.38048;,
 12.65204;-1.00348;-5.69069;,
 12.99899;-0.15298;-5.25290;,
 13.09660;0.21836;-4.25948;,
 16.05490;-2.16400;-1.63023;,
 16.19996;-0.99458;-1.84664;,
 15.95978;-3.02197;-2.09356;,
 16.39294;-3.49912;-3.12824;,
 17.13203;-3.24249;-4.11260;,
 17.73490;-2.43682;-4.44827;,
 17.87779;-1.54501;-3.98615;,
 17.47480;-1.05434;-3.00706;,
 16.22228;-1.22533;-2.16675;,
 16.24212;-2.14403;-2.11766;,
 16.18228;-2.22120;0.39455;,
 16.63702;-1.66094;0.41420;,
 16.17700;-2.79539;-2.43176;,
 16.10405;-2.88002;0.32429;,
 16.55314;-3.14807;-3.09977;,
 16.44827;-3.25064;0.24458;,
 17.14995;-2.99615;-3.73065;,
 17.01308;-3.11660;0.20212;,
 17.61801;-2.42791;-3.95472;,
 17.46794;-2.55582;0.22178;,
 17.68291;-1.77705;-3.64075;,
 17.54602;-1.89751;0.29201;,
 17.30683;-1.42417;-2.97260;,
 16.55485;-1.37291;0.95276;,
 16.22228;-1.22533;-2.16675;,
 16.63702;-1.66094;0.41420;,
 8.86777;-0.00207;-3.89782;,
 16.63702;-1.66094;0.41420;,
 16.18228;-2.22120;0.39455;,
 16.79373;-2.40619;0.88753;,
 16.10405;-2.88002;0.32429;,
 16.44827;-3.25064;0.24458;,
 17.01308;-3.11660;0.20212;,
 17.46794;-2.55582;0.22178;,
 17.54602;-1.89751;0.29201;,
 16.55485;-1.37291;0.95276;,
 16.22228;-1.22533;-2.16675;,
 16.24212;-2.14403;-2.11766;,
 16.17700;-2.79539;-2.43176;,
 16.55314;-3.14807;-3.09977;,
 17.14995;-2.99615;-3.73065;,
 17.61801;-2.42791;-3.95472;,
 17.68291;-1.77705;-3.64075;,
 17.30683;-1.42417;-2.97260;;
 
 267;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;8,9,7,6;,
 4;10,11,9,8;,
 4;12,13,11,10;,
 4;14,15,13,12;,
 4;3,2,15,14;,
 3;1,16,2;,
 3;5,16,1;,
 3;7,16,5;,
 3;9,16,7;,
 3;11,16,9;,
 3;13,16,11;,
 3;15,16,13;,
 3;2,16,15;,
 4;17,18,19,20;,
 4;21,22,18,17;,
 4;23,24,22,21;,
 4;25,26,24,23;,
 4;27,28,26,25;,
 4;29,30,28,27;,
 4;31,32,30,29;,
 4;20,19,32,31;,
 4;18,33,34,19;,
 4;22,35,33,18;,
 4;24,36,35,22;,
 4;26,37,36,24;,
 4;28,38,37,26;,
 4;30,39,38,28;,
 4;32,40,39,30;,
 4;19,34,40,32;,
 4;33,41,42,34;,
 4;35,43,41,33;,
 4;36,44,43,35;,
 4;37,45,44,36;,
 4;38,46,45,37;,
 4;39,47,46,38;,
 4;40,48,47,39;,
 4;34,42,48,40;,
 4;41,49,50,42;,
 4;43,51,49,41;,
 4;44,52,51,43;,
 4;45,53,52,44;,
 4;46,54,53,45;,
 4;47,55,54,46;,
 4;48,56,55,47;,
 4;42,50,56,48;,
 4;49,57,58,50;,
 4;51,59,57,49;,
 4;52,60,59,51;,
 4;53,61,60,52;,
 4;54,62,61,53;,
 4;55,63,62,54;,
 4;56,64,63,55;,
 4;50,58,64,56;,
 4;57,0,3,58;,
 4;59,4,0,57;,
 4;60,6,4,59;,
 4;61,8,6,60;,
 4;62,10,8,61;,
 4;63,12,10,62;,
 4;64,14,12,63;,
 4;58,3,14,64;,
 3;65,66,67;,
 3;65,67,68;,
 3;65,68,69;,
 3;65,69,70;,
 3;65,70,71;,
 3;65,71,72;,
 3;65,72,73;,
 3;65,73,66;,
 4;31,67,66,20;,
 4;29,68,67,31;,
 4;27,69,68,29;,
 4;25,70,69,27;,
 4;23,71,70,25;,
 4;21,72,71,23;,
 4;17,73,72,21;,
 4;20,66,73,17;,
 4;74,75,76,77;,
 4;75,78,79,76;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,74,77,93;,
 4;77,76,94,95;,
 4;76,79,96,94;,
 4;79,81,97,96;,
 4;81,83,98,97;,
 4;83,85,99,98;,
 4;85,87,100,99;,
 4;87,89,101,100;,
 4;89,91,102,101;,
 4;91,93,103,102;,
 4;93,77,95,103;,
 4;95,94,104,105;,
 4;94,96,106,104;,
 4;96,97,107,106;,
 4;97,98,108,107;,
 4;98,99,109,108;,
 4;99,100,110,109;,
 4;100,101,111,110;,
 4;101,102,112,111;,
 4;102,103,113,112;,
 4;103,95,105,113;,
 4;105,104,114,115;,
 4;104,106,116,114;,
 4;106,107,117,116;,
 4;107,108,118,117;,
 4;108,109,119,118;,
 4;109,110,120,119;,
 3;121,122,111;,
 3;111,122,110;,
 3;110,122,120;,
 4;111,112,123,121;,
 4;112,113,124,123;,
 4;113,105,115,124;,
 4;115,114,125,126;,
 4;114,116,127,125;,
 4;116,117,128,127;,
 4;117,118,129,128;,
 4;118,119,130,129;,
 4;119,120,131,130;,
 4;120,122,132,131;,
 4;121,123,133,134;,
 4;123,124,135,133;,
 4;124,115,126,135;,
 4;126,125,136,137;,
 4;125,127,138,136;,
 4;139,140,141,142;,
 4;140,143,144,141;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;134,133,151,152;,
 4;133,135,153,151;,
 4;135,126,137,153;,
 4;137,136,154,155;,
 4;136,138,156,154;,
 4;142,141,157,158;,
 4;141,144,159,157;,
 4;144,146,160,159;,
 4;146,148,161,160;,
 4;148,150,162,161;,
 4;152,151,163,164;,
 4;151,153,165,163;,
 4;153,137,155,165;,
 4;155,154,166,167;,
 4;154,156,168,166;,
 4;156,169,170,168;,
 4;169,171,172,170;,
 4;171,173,174,172;,
 4;173,175,176,174;,
 3;164,177,178;,
 3;176,175,177;,
 3;177,175,178;,
 4;164,163,179,177;,
 4;163,165,180,179;,
 4;165,155,167,180;,
 3;181,182,183;,
 3;184,181,183;,
 3;185,184,183;,
 3;186,185,183;,
 3;187,186,183;,
 3;188,187,183;,
 3;189,188,183;,
 3;190,189,183;,
 3;191,190,183;,
 3;182,191,183;,
 3;167,166,192;,
 3;166,168,192;,
 3;168,170,192;,
 3;170,172,192;,
 3;172,174,192;,
 3;174,176,192;,
 3;176,177,192;,
 3;177,179,192;,
 3;179,180,192;,
 3;180,167,192;,
 4;132,122,121,134;,
 4;193,132,134,152;,
 4;178,193,152,164;,
 4;194,75,74,195;,
 4;196,78,75,194;,
 4;197,80,78,196;,
 4;198,82,80,197;,
 4;199,84,82,198;,
 4;200,86,84,199;,
 4;201,88,86,200;,
 4;202,90,88,201;,
 4;203,92,90,202;,
 4;195,74,92,203;,
 4;204,127,128,205;,
 4;205,128,129,206;,
 4;206,129,130,207;,
 4;207,130,131,208;,
 4;208,131,132,209;,
 4;210,138,127,204;,
 4;211,156,138,210;,
 4;212,169,156,211;,
 4;213,214,215,216;,
 4;217,218,214,213;,
 4;219,175,173,220;,
 4;221,178,175,219;,
 4;209,132,193,222;,
 4;222,193,178,221;,
 4;223,224,225,226;,
 4;224,227,228,225;,
 4;227,229,230,228;,
 4;229,231,232,230;,
 4;231,233,234,232;,
 4;233,235,236,234;,
 4;235,237,238,236;,
 4;237,223,226,238;,
 4;226,225,239,240;,
 4;225,228,241,239;,
 4;228,230,242,241;,
 4;230,232,243,242;,
 4;232,234,244,243;,
 4;234,236,245,244;,
 4;236,238,246,245;,
 4;238,226,240,246;,
 4;240,239,247,248;,
 4;239,241,249,247;,
 4;241,242,250,249;,
 4;242,243,251,250;,
 4;243,244,252,251;,
 4;244,245,253,252;,
 4;245,246,254,253;,
 4;246,240,248,254;,
 4;255,256,257,258;,
 4;256,259,260,257;,
 4;259,261,262,260;,
 4;261,263,264,262;,
 4;263,265,266,264;,
 4;265,267,268,266;,
 4;267,269,270,268;,
 4;269,271,272,270;,
 3;224,223,273;,
 3;227,224,273;,
 3;229,227,273;,
 3;231,229,273;,
 3;233,231,273;,
 3;235,233,273;,
 3;237,235,273;,
 3;223,237,273;,
 3;274,275,276;,
 3;275,277,276;,
 3;277,278,276;,
 3;278,279,276;,
 3;279,280,276;,
 3;280,281,276;,
 3;281,282,276;,
 3;282,274,276;,
 4;283,248,247,284;,
 4;284,247,249,285;,
 4;285,249,250,286;,
 4;286,250,251,287;,
 4;287,251,252,288;,
 4;288,252,253,289;,
 4;289,253,254,290;,
 4;290,254,248,283;;
 
 MeshMaterialList {
  1;
  267;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "tyuuni_suit.png";
   }
  }
 }
 MeshNormals {
  318;
  -0.007647;-0.707087;-0.707085;,
  -0.007647;0.000001;-0.999971;,
  -0.007647;0.707085;-0.707087;,
  -0.007647;0.999971;0.000000;,
  -0.007647;0.707085;0.707087;,
  -0.007647;0.000001;0.999971;,
  -0.007647;-0.707087;0.707085;,
  -0.007647;-0.999971;0.000000;,
  0.320196;-0.669881;-0.669876;,
  0.320198;0.000002;-0.947351;,
  0.320196;0.669879;-0.669878;,
  0.320200;0.947350;0.000000;,
  0.320196;0.669879;0.669878;,
  0.320198;0.000002;0.947351;,
  0.320196;-0.669881;0.669876;,
  0.320198;-0.947351;-0.000000;,
  0.740867;0.257030;-0.620525;,
  -0.271212;0.680603;0.680605;,
  -0.271213;0.000001;0.962520;,
  -0.271213;-0.680604;0.680604;,
  -0.271214;-0.962519;0.000000;,
  -0.271213;-0.680604;-0.680604;,
  -0.271213;0.000001;-0.962520;,
  -0.271212;0.680603;-0.680605;,
  -0.271213;0.962519;0.000000;,
  -0.007647;0.707085;0.707088;,
  -0.007647;0.000001;0.999971;,
  -0.007647;-0.707085;0.707087;,
  -0.007647;-0.999971;0.000000;,
  -0.007647;-0.707085;-0.707087;,
  -0.007647;0.000001;-0.999971;,
  -0.007647;0.707085;-0.707088;,
  -0.007648;0.999971;0.000000;,
  0.263923;0.682034;0.682037;,
  0.263922;0.000000;0.964544;,
  0.263922;-0.682034;0.682037;,
  0.263922;-0.964544;-0.000000;,
  0.263922;-0.682034;-0.682037;,
  0.263922;0.000000;-0.964544;,
  0.263923;0.682034;-0.682037;,
  0.263923;0.964544;0.000000;,
  0.405272;0.646432;0.646436;,
  0.405270;0.000000;0.914197;,
  0.405270;-0.646433;0.646437;,
  0.405271;-0.914197;-0.000000;,
  0.405270;-0.646433;-0.646437;,
  0.405270;0.000000;-0.914197;,
  0.405272;0.646432;-0.646436;,
  0.405273;0.914196;0.000000;,
  0.263921;-0.682037;-0.682035;,
  0.263922;0.000001;-0.964544;,
  0.263921;0.682035;-0.682037;,
  0.263923;0.964544;0.000000;,
  0.263921;0.682035;0.682037;,
  0.263922;0.000001;0.964544;,
  0.263921;-0.682037;0.682035;,
  0.263922;-0.964544;-0.000000;,
  -0.663223;0.529213;0.529214;,
  -0.663223;0.748422;0.000000;,
  -0.663223;0.529213;-0.529214;,
  -0.663226;0.000001;-0.748420;,
  -0.663227;-0.529213;-0.529210;,
  -0.663226;-0.748419;0.000000;,
  -0.663227;-0.529213;0.529210;,
  -0.663225;0.000001;0.748420;,
  -1.000000;-0.000002;-0.000000;,
  -0.897143;0.441741;0.000000;,
  -0.897143;0.312357;0.312360;,
  -0.897143;0.312357;-0.312360;,
  -0.897143;0.000000;-0.441741;,
  -0.897144;-0.312357;-0.312355;,
  -0.897142;-0.441741;0.000000;,
  -0.897144;-0.312357;0.312355;,
  -0.897143;0.000000;0.441741;,
  -0.389429;-0.918253;-0.071804;,
  -0.255548;-0.965441;-0.051172;,
  -0.117387;-0.992891;-0.019672;,
  -0.129344;-0.991477;-0.015610;,
  -0.337152;-0.925971;0.170020;,
  -0.110138;-0.974829;-0.193850;,
  -0.261859;-0.959559;-0.103327;,
  0.177081;-0.984172;-0.006916;,
  0.154301;-0.987453;0.033589;,
  -0.458209;-0.849179;0.262562;,
  -0.379073;0.644110;-0.664399;,
  -0.653977;0.645649;-0.394274;,
  -0.881575;-0.469689;-0.047085;,
  -0.938146;-0.340331;-0.063695;,
  -0.980325;-0.187191;-0.062630;,
  -0.514013;-0.780446;0.355942;,
  -0.558230;-0.304422;0.771820;,
  -0.642178;0.008851;0.766505;,
  -0.014132;0.999876;-0.006976;,
  0.001490;0.999847;-0.017410;,
  0.020280;0.999655;-0.016690;,
  0.035086;0.999372;-0.005004;,
  0.040205;0.999105;0.013158;,
  0.033621;0.998959;0.030818;,
  0.017866;0.998990;0.041236;,
  -0.000951;0.999182;0.040418;,
  -0.015628;0.999465;0.028736;,
  -0.020654;0.999730;0.010643;,
  0.009723;0.999882;0.011898;,
  -0.079029;0.993398;-0.083150;,
  -0.173615;0.972851;-0.153032;,
  -0.049998;0.934373;-0.352772;,
  -0.019998;0.987157;-0.158497;,
  0.107114;0.956898;-0.269950;,
  0.056293;0.992333;-0.110028;,
  0.185991;0.982351;0.019841;,
  0.138687;0.990259;0.012340;,
  0.186070;0.982351;0.019100;,
  0.177737;0.983899;0.018759;,
  0.186030;0.982373;0.018338;,
  0.138237;0.990154;0.022021;,
  0.083511;0.949720;0.301758;,
  0.046032;0.989447;0.137388;,
  -0.080455;0.925112;0.371072;,
  -0.034129;0.983192;0.179354;,
  -0.187055;0.969088;0.160867;,
  -0.086384;0.991314;0.099167;,
  -0.238195;0.971216;0.001306;,
  -0.108009;0.994126;0.006856;,
  -0.475048;0.793203;-0.380997;,
  -0.138349;0.684050;-0.716195;,
  0.370365;0.743647;-0.556613;,
  0.593206;0.804967;-0.011662;,
  0.572541;0.819200;0.033282;,
  0.589872;0.803569;0.079548;,
  0.323291;0.726122;0.606819;,
  -0.199390;0.661691;0.722779;,
  -0.507965;0.782466;0.360163;,
  -0.618216;0.785836;-0.016448;,
  -0.717323;0.404229;-0.567491;,
  -0.202679;0.342203;-0.917507;,
  0.124386;0.257889;-0.958134;,
  0.870538;0.488940;-0.055693;,
  0.867907;0.494966;0.041780;,
  0.863051;0.485577;0.139136;,
  0.853861;0.473659;0.215796;,
  -0.213410;0.295909;0.931071;,
  -0.764510;0.384914;0.517074;,
  -0.916320;0.399058;-0.033317;,
  -0.782446;0.020866;-0.622368;,
  -0.212446;-0.015327;-0.977053;,
  0.154356;-0.048718;-0.986813;,
  0.881720;0.467607;-0.062557;,
  0.882671;0.468105;0.042063;,
  0.873672;0.463970;0.146386;,
  0.865644;0.460160;0.197264;,
  0.080963;-0.099729;0.991715;,
  -0.289704;-0.081382;0.953650;,
  -0.831667;-0.000510;0.555274;,
  -0.999011;0.015453;-0.041699;,
  -0.691312;-0.444613;-0.569568;,
  -0.238447;-0.425715;-0.872875;,
  0.156149;-0.237264;-0.958813;,
  0.812203;-0.580156;-0.061192;,
  0.827361;-0.560994;0.027571;,
  0.802806;-0.584714;0.116669;,
  0.782922;-0.607899;0.132256;,
  0.171874;-0.535701;0.826731;,
  -0.191381;-0.523762;0.830088;,
  -0.770709;-0.383152;0.509118;,
  -0.927608;-0.370875;-0.044669;,
  -0.391842;-0.796113;-0.461154;,
  -0.064899;-0.939209;-0.337157;,
  0.019530;-0.830139;0.557214;,
  -0.036352;-0.779249;0.625660;,
  -0.600931;-0.695431;0.394029;,
  -0.723665;-0.688846;-0.042418;,
  0.082272;-0.968566;-0.234759;,
  0.183307;-0.950861;-0.249523;,
  0.111274;-0.877718;0.466078;,
  0.270923;-0.921015;0.279880;,
  -0.213732;-0.958223;0.190071;,
  -0.108466;-0.993929;-0.018451;,
  0.207440;-0.978053;0.019521;,
  0.098042;-0.995101;0.012688;,
  0.192385;-0.972720;0.129629;,
  0.247949;0.953836;-0.169462;,
  0.016712;0.999657;0.020145;,
  0.207924;0.943681;0.257360;,
  0.376400;0.789520;0.484748;,
  0.363097;-0.930992;0.037601;,
  0.479029;-0.751529;0.453580;,
  0.233588;-0.955925;-0.177889;,
  0.256546;-0.966530;0.002105;,
  0.193188;-0.980941;0.020831;,
  0.377564;-0.733096;0.565699;,
  -0.795648;0.605572;0.015086;,
  -0.974124;0.223814;0.031473;,
  -0.949335;-0.312316;-0.034961;,
  -0.730061;-0.682089;-0.042025;,
  0.678487;-0.708466;0.194247;,
  0.904688;-0.398932;0.149644;,
  0.965362;0.055350;0.254975;,
  0.624305;0.778293;0.067107;,
  -0.891446;0.390418;0.229994;,
  -0.861558;0.230191;0.452472;,
  -0.822522;-0.324027;0.467402;,
  -0.340798;-0.722888;0.601074;,
  0.500239;-0.770838;0.394424;,
  0.833119;-0.384136;0.397935;,
  0.856985;0.175018;0.484712;,
  0.102369;-0.237542;0.965968;,
  -0.109895;0.561433;0.820193;,
  0.097006;0.593673;0.798838;,
  -0.041679;-0.062460;0.997177;,
  -0.767038;0.447274;0.459998;,
  -0.286686;-0.751061;0.594743;,
  -0.392221;-0.713860;0.580143;,
  -0.311889;-0.929721;0.195815;,
  -0.645831;-0.289372;0.706517;,
  -0.348438;-0.461205;-0.816015;,
  -0.518030;-0.261358;-0.814455;,
  -0.187604;0.189321;-0.963827;,
  -0.641476;0.477175;-0.600677;,
  0.008225;0.728818;-0.684658;,
  -0.437317;0.698695;-0.566197;,
  0.167577;0.968668;-0.183306;,
  -0.429048;0.827303;-0.362611;,
  0.125049;0.676414;0.725828;,
  -0.119758;-0.126270;0.984740;,
  -0.282802;-0.736242;0.614793;,
  -0.261214;-0.963507;-0.058486;,
  -0.083581;-0.676734;-0.731468;,
  0.144366;0.012481;-0.989446;,
  0.285458;0.684848;-0.670445;,
  0.265317;0.964034;-0.015690;,
  -0.064889;0.727186;0.683367;,
  -0.347693;-0.022692;0.937334;,
  -0.392366;-0.680521;0.618822;,
  -0.257832;-0.964906;-0.049801;,
  -0.018049;-0.714848;-0.699047;,
  0.237031;-0.028923;-0.971071;,
  0.359313;0.669221;-0.650413;,
  0.260400;0.965179;-0.024927;,
  -0.871337;0.490669;0.003986;,
  0.740868;0.257030;0.620525;,
  0.692835;-0.721096;-0.000000;,
  0.405269;0.000001;-0.914197;,
  0.405270;-0.646436;-0.646434;,
  0.405272;0.646433;-0.646435;,
  0.405276;0.914194;0.000000;,
  0.405272;0.646433;0.646435;,
  0.405269;0.000001;0.914197;,
  0.405270;-0.646436;0.646434;,
  0.405270;-0.914197;-0.000000;,
  0.867291;0.479715;-0.132964;,
  0.058625;0.193663;0.979315;,
  0.877628;0.465630;-0.113836;,
  0.081835;-0.199408;0.976493;,
  0.795113;-0.601634;-0.076370;,
  0.062793;-0.446192;0.892732;,
  -0.100345;-0.969335;0.224320;,
  -0.382866;-0.911987;0.147289;,
  0.136582;-0.570934;0.809555;,
  -0.774737;-0.630842;-0.042670;,
  -0.804835;-0.581231;-0.120045;,
  -0.814023;-0.577238;-0.064523;,
  0.219735;0.733116;-0.643628;,
  0.455860;0.814334;-0.359238;,
  0.380578;-0.921658;0.075550;,
  0.486484;-0.804119;0.341652;,
  -0.843480;0.357811;-0.400640;,
  -0.935032;0.270631;-0.229073;,
  0.333184;-0.846789;-0.414653;,
  0.363447;-0.929401;0.064190;,
  0.217171;-0.976079;-0.010357;,
  0.282144;-0.959304;0.011441;,
  0.259404;0.220825;0.940184;,
  0.773782;0.192915;0.603362;,
  -0.357577;0.189222;0.914513;,
  -0.809822;0.210767;0.547509;,
  -0.961447;0.272538;-0.036652;,
  -0.760393;0.232145;-0.606557;,
  -0.280012;0.223510;-0.933615;,
  0.335370;0.254937;-0.906937;,
  0.819794;0.213961;-0.531186;,
  0.983923;0.173328;0.043044;,
  -0.521948;-0.852461;0.029669;,
  -0.401428;-0.915376;-0.030710;,
  -0.402197;-0.913348;-0.063502;,
  -0.467789;-0.882238;-0.053197;,
  -0.528577;-0.847838;-0.042145;,
  0.087366;0.320752;0.943125;,
  -0.047861;0.546895;-0.835832;,
  -0.816596;-0.551895;-0.169062;,
  -0.575382;-0.766836;-0.284427;,
  -0.955450;-0.290931;-0.049740;,
  -0.995757;-0.071364;-0.058091;,
  0.903701;0.114718;-0.412509;,
  0.748350;-0.303529;-0.589782;,
  0.759356;0.650246;0.023632;,
  0.810735;0.582465;-0.058674;,
  -0.443617;-0.734870;0.513001;,
  -0.689906;-0.177225;-0.701870;,
  -0.519073;-0.543568;-0.659618;,
  0.132963;0.791016;0.597172;,
  0.521427;-0.814587;0.254090;,
  0.226969;-0.973646;-0.022337;,
  -0.569430;0.820179;-0.055280;,
  -0.849006;0.527984;-0.020530;,
  -0.863590;0.439631;-0.246855;,
  -0.857556;0.475977;0.195047;,
  -0.790889;0.423605;0.441648;,
  0.583052;0.083777;0.808104;,
  -0.974289;-0.223404;-0.029174;,
  0.813286;-0.266887;0.517046;,
  0.938721;-0.154377;0.308172;,
  0.851080;-0.277757;0.445549;,
  0.766148;-0.392088;0.509200;,
  0.803050;-0.276190;0.528044;,
  0.768561;-0.520682;0.371757;,
  0.874730;-0.400745;0.272491;,
  0.886010;-0.235326;0.399511;,
  0.703376;-0.343598;0.622257;;
  267;
  4;1,9,8,0;,
  4;2,10,9,1;,
  4;3,11,10,2;,
  4;4,12,11,3;,
  4;5,13,12,4;,
  4;6,14,13,5;,
  4;7,15,14,6;,
  4;0,8,15,7;,
  3;9,16,8;,
  3;10,16,9;,
  3;11,16,10;,
  3;12,239,11;,
  3;13,239,12;,
  3;14,239,13;,
  3;15,240,14;,
  3;8,240,15;,
  4;64,18,17,57;,
  4;63,19,18,64;,
  4;62,20,19,63;,
  4;61,21,20,62;,
  4;60,22,21,61;,
  4;59,23,22,60;,
  4;58,24,23,59;,
  4;57,17,24,58;,
  4;18,26,25,17;,
  4;19,27,26,18;,
  4;20,28,27,19;,
  4;21,29,28,20;,
  4;22,30,29,21;,
  4;23,31,30,22;,
  4;24,32,31,23;,
  4;17,25,32,24;,
  4;26,34,33,25;,
  4;27,35,34,26;,
  4;28,36,35,27;,
  4;29,37,36,28;,
  4;30,38,37,29;,
  4;31,39,38,30;,
  4;32,40,39,31;,
  4;25,33,40,32;,
  4;34,42,41,33;,
  4;35,43,42,34;,
  4;36,44,43,35;,
  4;37,45,44,36;,
  4;38,46,45,37;,
  4;39,47,46,38;,
  4;40,48,47,39;,
  4;33,41,48,40;,
  4;241,50,49,242;,
  4;243,51,50,241;,
  4;244,52,51,243;,
  4;245,53,52,244;,
  4;246,54,53,245;,
  4;247,55,54,246;,
  4;248,56,55,247;,
  4;242,49,56,248;,
  4;50,1,0,49;,
  4;51,2,1,50;,
  4;52,3,2,51;,
  4;53,4,3,52;,
  4;54,5,4,53;,
  4;55,6,5,54;,
  4;56,7,6,55;,
  4;49,0,7,56;,
  3;65,67,66;,
  3;65,66,68;,
  3;65,68,69;,
  3;65,69,70;,
  3;65,70,71;,
  3;65,71,72;,
  3;65,72,73;,
  3;65,73,67;,
  4;58,66,67,57;,
  4;59,68,66,58;,
  4;60,69,68,59;,
  4;61,70,69,60;,
  4;62,71,70,61;,
  4;63,72,71,62;,
  4;64,73,72,63;,
  4;57,67,73,64;,
  4;103,106,105,104;,
  4;106,108,107,105;,
  4;108,110,109,107;,
  4;110,112,111,109;,
  4;112,114,113,111;,
  4;114,116,115,113;,
  4;116,118,117,115;,
  4;118,120,119,117;,
  4;120,122,121,119;,
  4;122,103,104,121;,
  4;104,105,124,123;,
  4;105,107,125,124;,
  4;107,109,126,125;,
  4;109,111,127,126;,
  4;111,113,128,127;,
  4;113,115,129,128;,
  4;115,117,130,129;,
  4;117,119,131,130;,
  4;119,121,132,131;,
  4;121,104,123,132;,
  4;123,124,134,133;,
  4;124,125,135,134;,
  4;125,126,136,249;,
  4;126,127,137,136;,
  4;127,128,138,137;,
  4;128,129,139,138;,
  4;129,130,140,250;,
  4;130,131,141,140;,
  4;131,132,142,141;,
  4;132,123,133,142;,
  4;133,134,144,143;,
  4;134,135,145,144;,
  4;249,136,146,251;,
  4;136,137,147,146;,
  4;137,138,148,147;,
  4;138,139,149,148;,
  3;151,150,140;,
  3;140,150,250;,
  3;250,150,252;,
  4;140,141,152,151;,
  4;141,142,153,152;,
  4;142,133,143,153;,
  4;143,144,155,154;,
  4;144,145,156,155;,
  4;253,157,157,253;,
  4;157,158,158,157;,
  4;158,159,159,158;,
  4;159,160,160,159;,
  4;252,150,161,254;,
  4;151,152,163,162;,
  4;152,153,164,163;,
  4;153,143,154,164;,
  4;154,155,166,165;,
  4;255,256,167,166;,
  4;74,75,80,79;,
  4;75,76,81,80;,
  4;76,77,82,81;,
  4;77,78,83,82;,
  4;78,89,90,83;,
  4;162,163,169,168;,
  4;163,164,170,169;,
  4;164,154,165,170;,
  4;165,166,172,171;,
  4;257,167,173,257;,
  4;84,85,85,84;,
  4;80,258,86,259;,
  4;258,260,87,86;,
  4;260,83,88,87;,
  4;91,90,91,91;,
  4;168,169,175,174;,
  4;169,170,176,175;,
  4;170,165,171,176;,
  4;171,172,178,177;,
  4;172,173,179,178;,
  4;261,180,180,262;,
  4;180,181,181,180;,
  4;181,182,182,181;,
  4;182,183,183,182;,
  3;174,184,185;,
  3;263,264,184;,
  3;265,266,265;,
  4;174,267,186,184;,
  4;175,176,187,186;,
  4;176,171,177,187;,
  3;93,92,102;,
  3;94,93,102;,
  3;95,94,102;,
  3;96,95,102;,
  3;97,96,102;,
  3;98,97,102;,
  3;99,98,102;,
  3;100,99,102;,
  3;101,100,102;,
  3;92,101,102;,
  3;177,178,188;,
  3;178,179,188;,
  3;179,268,188;,
  3;268,269,188;,
  3;269,270,188;,
  3;270,263,188;,
  3;263,184,188;,
  3;184,186,188;,
  3;186,187,188;,
  3;187,177,188;,
  4;161,150,151,162;,
  4;189,161,162,168;,
  4;185,189,168,174;,
  4;271,271,272,272;,
  4;273,273,271,271;,
  4;274,274,273,273;,
  4;275,275,274,274;,
  4;276,276,275,275;,
  4;277,277,276,276;,
  4;278,278,277,277;,
  4;279,279,278,278;,
  4;280,280,279,279;,
  4;272,272,280,280;,
  4;74,256,281,75;,
  4;75,281,282,76;,
  4;76,282,283,77;,
  4;77,283,284,78;,
  4;78,284,285,89;,
  4;286,286,286,286;,
  4;84,261,287,84;,
  4;259,288,289,289;,
  4;86,290,288,259;,
  4;87,291,290,86;,
  4;88,266,291,87;,
  4;292,292,293,293;,
  4;294,294,295,295;,
  4;295,295,292,292;,
  4;206,209,208,207;,
  4;296,211,210,296;,
  4;211,213,212,210;,
  4;297,215,214,298;,
  4;215,217,216,214;,
  4;217,219,218,216;,
  4;219,221,220,218;,
  4;299,206,207,299;,
  4;207,208,223,222;,
  4;208,210,224,223;,
  4;210,212,225,224;,
  4;212,214,226,225;,
  4;214,216,227,226;,
  4;216,218,228,227;,
  4;218,220,229,228;,
  4;220,207,222,229;,
  4;222,223,231,230;,
  4;223,224,232,231;,
  4;224,225,233,232;,
  4;225,226,234,233;,
  4;226,227,235,234;,
  4;227,228,236,235;,
  4;228,229,237,236;,
  4;229,222,230,237;,
  4;190,191,199,198;,
  4;191,192,200,199;,
  4;192,193,201,200;,
  4;300,194,202,301;,
  4;194,195,203,202;,
  4;195,196,204,203;,
  4;196,197,197,204;,
  4;302,190,198,302;,
  3;209,303,238;,
  3;304,209,238;,
  3;297,304,238;,
  3;305,213,238;,
  3;217,305,238;,
  3;219,217,238;,
  3;306,306,238;,
  3;303,221,238;,
  3;198,199,205;,
  3;199,200,205;,
  3;200,201,205;,
  3;201,202,205;,
  3;202,203,205;,
  3;203,204,205;,
  3;204,307,205;,
  3;308,198,308;,
  4;309,309,310,310;,
  4;310,310,311,311;,
  4;311,311,312,313;,
  4;300,312,314,194;,
  4;194,314,315,195;,
  4;195,315,316,196;,
  4;196,316,317,317;,
  4;317,317,309,309;;
 }
 MeshTextureCoords {
  291;
  0.908400;0.074570;,
  0.870520;0.074570;,
  0.870520;0.059060;,
  0.908400;0.062570;,
  0.908400;0.086570;,
  0.870520;0.090090;,
  0.908400;0.091540;,
  0.870520;0.096510;,
  0.908400;0.086570;,
  0.870520;0.090090;,
  0.908400;0.074570;,
  0.870520;0.074570;,
  0.908400;0.062570;,
  0.870520;0.059060;,
  0.908400;0.057600;,
  0.870520;0.052630;,
  0.847680;0.074570;,
  0.847680;0.074570;,
  0.870520;0.074570;,
  0.870520;0.042090;,
  0.847680;0.049240;,
  0.847680;0.099900;,
  0.870520;0.107060;,
  0.847680;0.110390;,
  0.870520;0.120510;,
  0.847680;0.099900;,
  0.870520;0.107060;,
  0.847680;0.074570;,
  0.870520;0.074570;,
  0.847680;0.049240;,
  0.870520;0.042090;,
  0.847680;0.038750;,
  0.870520;0.028630;,
  0.908400;0.074570;,
  0.908400;0.038570;,
  0.908400;0.110570;,
  0.908400;0.125480;,
  0.908400;0.110570;,
  0.908400;0.074570;,
  0.908400;0.038570;,
  0.908400;0.023660;,
  0.951360;0.074570;,
  0.951360;0.042090;,
  0.951360;0.107060;,
  0.951360;0.120510;,
  0.951360;0.107060;,
  0.951360;0.074570;,
  0.951360;0.042090;,
  0.951360;0.028630;,
  0.978430;0.074570;,
  0.978430;0.050570;,
  0.978430;0.098570;,
  0.978430;0.108510;,
  0.978430;0.098570;,
  0.978430;0.074570;,
  0.978430;0.050570;,
  0.978430;0.040630;,
  0.951360;0.074570;,
  0.951360;0.059060;,
  0.951360;0.090090;,
  0.951360;0.096510;,
  0.951360;0.090090;,
  0.951360;0.074570;,
  0.951360;0.059060;,
  0.951360;0.052630;,
  0.831040;0.074570;,
  0.839850;0.058250;,
  0.839850;0.051490;,
  0.839850;0.058250;,
  0.839850;0.074570;,
  0.839850;0.090890;,
  0.839850;0.097650;,
  0.839850;0.090890;,
  0.839850;0.074570;,
  0.353880;0.564800;,
  0.414220;0.606840;,
  0.384240;0.711250;,
  0.268280;0.631190;,
  0.487430;0.600800;,
  0.750030;0.774850;,
  0.546550;0.551180;,
  0.778730;0.617810;,
  0.567370;0.485140;,
  0.774110;0.477470;,
  0.541140;0.421040;,
  0.767030;0.336570;,
  0.478100;0.376480;,
  0.725390;0.182430;,
  0.404640;0.376510;,
  0.366130;0.275750;,
  0.348000;0.423400;,
  0.257200;0.364800;,
  0.328230;0.495030;,
  0.218800;0.499820;,
  0.356880;0.804990;,
  0.190360;0.691670;,
  0.834940;0.777840;,
  0.861610;0.618380;,
  0.852120;0.474500;,
  0.849600;0.329800;,
  0.809800;0.173590;,
  0.331120;0.185870;,
  0.174590;0.312480;,
  0.120480;0.504650;,
  0.339930;0.863430;,
  0.141110;0.731150;,
  0.892370;0.788160;,
  0.912150;0.624920;,
  0.910870;0.473590;,
  0.899580;0.322780;,
  0.866320;0.162100;,
  0.309520;0.132440;,
  0.122370;0.280650;,
  0.058550;0.508930;,
  0.333440;0.883640;,
  0.124200;0.745220;,
  0.944260;0.787970;,
  0.959680;0.624440;,
  0.962580;0.473190;,
  0.947130;0.322880;,
  0.918110;0.161370;,
  0.301780;0.116360;,
  0.591380;0.130370;,
  0.104500;0.271680;,
  0.037420;0.511630;,
  0.334630;0.861550;,
  0.139270;0.735160;,
  0.834590;0.763600;,
  0.855980;0.629010;,
  0.868100;0.481120;,
  0.843330;0.334680;,
  0.812060;0.171700;,
  0.601320;0.141350;,
  0.119300;0.284430;,
  0.309750;0.137040;,
  0.055480;0.512710;,
  0.353760;0.792240;,
  0.189420;0.703130;,
  0.715970;0.767430;,
  0.969610;0.099090;,
  0.970770;0.099400;,
  0.875600;0.116040;,
  0.902400;0.072480;,
  0.978730;0.102880;,
  0.879560;0.121490;,
  0.962480;0.102240;,
  0.867710;0.118750;,
  0.952990;0.104790;,
  0.851250;0.114930;,
  0.820450;0.019900;,
  0.821560;0.021060;,
  0.165350;0.317690;,
  0.332380;0.192300;,
  0.111010;0.512070;,
  0.386980;0.719490;,
  0.271310;0.643850;,
  0.735030;0.779220;,
  0.843730;0.073790;,
  0.917200;0.078020;,
  0.841260;0.077710;,
  0.835740;0.076520;,
  0.823240;0.057620;,
  0.821410;0.025440;,
  0.251720;0.376470;,
  0.369310;0.291520;,
  0.213480;0.509240;,
  0.672410;0.587490;,
  0.624370;0.557010;,
  0.724270;0.578850;,
  0.620480;0.630730;,
  0.752650;0.533110;,
  0.617620;0.489950;,
  0.769310;0.480540;,
  0.606540;0.358160;,
  0.749840;0.433120;,
  0.599730;0.200370;,
  0.707130;0.402170;,
  0.670240;0.378180;,
  0.613440;0.207190;,
  0.618090;0.432990;,
  0.601130;0.488270;,
  0.866340;0.056060;,
  0.815550;0.055970;,
  0.893260;0.054440;,
  0.927270;0.056680;,
  0.975080;0.057590;,
  0.991500;0.058450;,
  0.970260;0.058920;,
  0.919470;0.058830;,
  0.858530;0.058210;,
  0.810730;0.057300;,
  0.794310;0.056440;,
  0.698830;0.483970;,
  0.611750;0.176160;,
  0.415400;0.598600;,
  0.357770;0.560280;,
  0.484550;0.595740;,
  0.538800;0.552780;,
  0.557430;0.486140;,
  0.533330;0.421260;,
  0.475690;0.382930;,
  0.406550;0.385800;,
  0.352300;0.428760;,
  0.333670;0.495400;,
  0.818850;0.773320;,
  0.820590;0.627680;,
  0.832550;0.482290;,
  0.808130;0.338320;,
  0.793880;0.193450;,
  0.594690;0.177730;,
  0.717850;0.772710;,
  0.740090;0.772240;,
  0.629670;0.629650;,
  0.805680;0.093870;,
  0.798330;0.066430;,
  0.800850;0.061440;,
  0.808950;0.088670;,
  0.798380;0.092300;,
  0.788570;0.066140;,
  0.598880;0.202760;,
  0.617670;0.350950;,
  0.596140;0.229260;,
  0.596360;0.205510;,
  0.100330;0.290190;,
  0.063630;0.297820;,
  0.211200;0.215400;,
  0.258980;0.241090;,
  0.034010;0.348530;,
  0.288450;0.316360;,
  0.037340;0.369970;,
  0.269650;0.421810;,
  0.036610;0.389300;,
  0.290420;0.521940;,
  0.072380;0.399560;,
  0.327360;0.549340;,
  0.099640;0.362510;,
  0.362530;0.508730;,
  0.145530;0.320850;,
  0.383310;0.409170;,
  0.418270;0.266010;,
  0.462620;0.300580;,
  0.382580;0.312880;,
  0.374570;0.416990;,
  0.401150;0.515040;,
  0.441890;0.546160;,
  0.476680;0.502250;,
  0.486470;0.402620;,
  0.783170;0.138930;,
  0.797710;0.160630;,
  0.773630;0.185390;,
  0.817070;0.289160;,
  0.891190;0.387890;,
  0.951650;0.421550;,
  0.965990;0.375200;,
  0.925570;0.277010;,
  0.929680;0.105470;,
  0.933830;0.105470;,
  0.933830;0.092980;,
  0.929680;0.092980;,
  0.937980;0.105470;,
  0.937980;0.092980;,
  0.942140;0.105470;,
  0.942140;0.092980;,
  0.946290;0.105470;,
  0.946290;0.092980;,
  0.950440;0.105470;,
  0.950440;0.092980;,
  0.954600;0.105470;,
  0.954600;0.092980;,
  0.958750;0.105470;,
  0.958750;0.092980;,
  0.962910;0.105470;,
  0.962910;0.092980;,
  0.062350;0.366340;,
  0.960980;0.057650;,
  0.946290;0.051560;,
  0.946290;0.073160;,
  0.931600;0.057650;,
  0.925520;0.072330;,
  0.931600;0.087020;,
  0.946290;0.093100;,
  0.960980;0.087020;,
  0.967060;0.072330;,
  0.799950;0.192740;,
  0.801940;0.187810;,
  0.795410;0.219310;,
  0.833130;0.286310;,
  0.892990;0.349580;,
  0.939930;0.372050;,
  0.946440;0.340560;,
  0.908720;0.273550;;
 }
}
