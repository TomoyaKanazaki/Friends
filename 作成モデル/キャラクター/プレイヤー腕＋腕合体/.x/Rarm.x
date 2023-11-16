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
 298;
 -45.75410;-26.48270;31.34830;,
 -27.38180;-25.57770;35.04060;,
 -25.75640;24.36810;39.99750;,
 -44.12840;23.46280;36.30520;,
 -9.00960;-24.67260;38.73300;,
 -8.19670;0.30040;41.21140;,
 -7.38370;25.27320;43.68980;,
 0.00000;0.00000;0.00000;,
 0.82020;25.19380;2.50030;,
 -0.90180;-1.02200;-17.18740;,
 -0.08890;23.95090;-14.70890;,
 -16.68390;23.02910;-27.32510;,
 -1.71480;-25.99480;-19.66580;,
 -18.30950;-26.91690;-32.28200;,
 -36.68170;-27.82210;-35.97420;,
 -35.05600;22.12370;-31.01740;,
 -42.89070;-26.82520;-10.91430;,
 -41.26490;23.12090;-5.95750;,
 -45.75410;-26.48270;31.34830;,
 -44.12840;23.46280;36.30520;,
 -39.00060;24.49760;-7.02440;,
 -17.43860;25.55990;-2.69120;,
 -17.94230;24.31290;-21.93200;,
 -34.64830;23.49020;-25.28960;,
 -41.60370;24.80860;31.40510;,
 -24.89780;25.63170;34.76240;,
 -0.73240;26.38310;0.66620;,
 -2.85270;25.15170;-10.46020;,
 -8.19200;26.45490;38.11980;,
 -36.35790;-29.02740;-30.50170;,
 -19.65200;-28.20430;-27.14420;,
 -19.14780;-26.95790;-7.90330;,
 -40.70950;-28.01940;-12.23660;,
 -26.60760;-26.88590;29.55020;,
 -43.31320;-27.70880;26.19290;,
 -4.56220;-27.36580;-15.67220;,
 -2.44210;-26.13440;-4.54580;,
 -9.90150;-26.06270;32.90770;,
 -41.26490;23.12090;-5.95750;,
 -35.05600;22.12370;-31.01740;,
 -16.68390;23.02910;-27.32510;,
 -0.08890;23.95090;-14.70890;,
 0.82020;25.19380;2.50030;,
 -36.68170;-27.82210;-35.97420;,
 -42.89070;-26.82520;-10.91430;,
 -18.30950;-26.91690;-32.28200;,
 -0.80580;-24.75190;-2.45650;,
 -1.71480;-25.99480;-19.66580;,
 -44.00270;-64.85880;34.55360;,
 -35.94850;-61.01940;-12.73220;,
 -36.50230;64.81630;-2.50670;,
 -44.55650;60.97690;44.77940;,
 -27.89450;-57.18030;-60.01840;,
 -28.44820;68.65570;-49.79280;,
 -64.92440;-56.72250;-61.68070;,
 -65.47820;69.11350;-51.45500;,
 -115.79170;-58.81540;-64.51350;,
 -116.34541;67.02040;-54.28850;,
 -131.86830;-62.55580;-17.58730;,
 -132.42230;63.28010;-7.36200;,
 -116.34560;67.02060;-54.28850;,
 -139.92250;-66.39490;29.69820;,
 -140.47659;59.44120;39.92390;,
 -83.37370;-65.51680;46.63640;,
 -83.92750;60.31910;56.86190;,
 -44.00270;-64.85880;34.55360;,
 -44.55650;60.97690;44.77940;,
 -84.52440;63.97550;52.14930;,
 -75.07170;68.48100;-3.34650;,
 -127.76530;66.41040;-6.26120;,
 -135.08890;62.91940;36.73620;,
 -48.72390;64.57360;41.16290;,
 -41.40010;68.06430;-1.83460;,
 -67.74810;71.97200;-46.34330;,
 -113.14670;69.81130;-48.93110;,
 -34.07690;71.55550;-44.83200;,
 -134.50691;-69.39580;25.98420;,
 -127.18330;-65.90480;-17.01320;,
 -74.48920;-63.83460;-14.09790;,
 -83.94150;-68.33970;41.39750;,
 -40.81800;-64.25050;-12.58660;,
 -48.14160;-67.74140;30.41090;,
 -112.56430;-62.50420;-59.68270;,
 -67.16550;-60.34320;-57.09530;,
 -33.49420;-60.75940;-55.58400;,
 -83.92750;60.31910;56.86190;,
 -140.47659;59.44120;39.92390;,
 -132.42230;63.28010;-7.36200;,
 -116.34541;67.02040;-54.28850;,
 -65.47820;69.11350;-51.45500;,
 -139.92250;-66.39490;29.69820;,
 -83.37370;-65.51680;46.63640;,
 -131.86830;-62.55580;-17.58730;,
 -64.92440;-56.72250;-61.68070;,
 -115.79170;-58.81540;-64.51350;,
 -274.55688;-30.47610;28.08300;,
 -241.22470;-30.90240;20.57380;,
 -236.89101;18.76480;26.98690;,
 -270.22290;19.19180;34.49610;,
 -207.89240;-31.32940;13.06470;,
 -203.55849;18.33800;19.47770;,
 -207.14340;-29.84320;-30.59590;,
 -202.80931;19.82470;-24.18280;,
 -208.24881;-30.66360;-48.81980;,
 -203.91499;19.00380;-42.40660;,
 -241.41859;-29.91440;-50.76980;,
 -237.08501;19.75290;-44.35660;,
 -274.75079;-29.48750;-43.26060;,
 -270.41742;20.18000;-36.84750;,
 -283.49658;-28.86510;-13.39480;,
 -279.16309;20.80230;-6.98160;,
 -274.55688;-30.47610;28.08300;,
 -270.22290;19.19180;34.49610;,
 -275.55991;22.09390;-9.26950;,
 -236.44112;21.59270;-18.08240;,
 -237.50929;20.84570;-38.45970;,
 -267.81851;21.23380;-31.63180;,
 -267.43091;20.62910;28.44630;,
 -237.12221;20.24070;21.61810;,
 -206.13220;21.20440;-24.91050;,
 -207.34770;20.16410;-36.68660;,
 -206.81319;19.85240;14.79000;,
 -272.37540;-30.99090;-38.37510;,
 -242.06641;-31.37920;-45.20310;,
 -240.99811;-30.63210;-24.82570;,
 -280.11679;-30.13110;-16.01290;,
 -241.67900;-31.98370;14.87470;,
 -271.98788;-31.59550;21.70280;,
 -211.90520;-32.06010;-43.42980;,
 -210.68881;-31.02060;-31.65380;,
 -211.36990;-32.37190;8.04670;,
 -279.16309;20.80230;-6.98160;,
 -270.41742;20.18000;-36.84750;,
 -237.08501;19.75290;-44.35660;,
 -203.91499;19.00380;-42.40660;,
 -202.80931;19.82470;-24.18280;,
 -274.75079;-29.48750;-43.26060;,
 -283.49658;-28.86510;-13.39480;,
 -241.41859;-29.91440;-50.76980;,
 -207.14340;-29.84320;-30.59590;,
 -208.24881;-30.66360;-48.81980;,
 -199.78070;-28.63790;14.51740;,
 -165.72690;-28.33610;17.32290;,
 -164.37959;21.66070;22.35130;,
 -198.43311;21.35830;19.54580;,
 -131.67360;-28.03370;20.12850;,
 -130.32620;21.96290;25.15680;,
 -117.91310;-28.29270;-21.33940;,
 -116.56539;21.70410;-16.31110;,
 -113.49670;-29.88380;-39.00220;,
 -112.14920;20.11290;-33.97370;,
 -144.56909;-30.24200;-50.79180;,
 -143.22150;19.75490;-45.76340;,
 -178.62219;-30.54410;-53.59730;,
 -177.27501;19.45260;-48.56890;,
 -195.91870;-28.98450;-27.76590;,
 -194.57111;21.01170;-22.73750;,
 -199.78070;-28.63790;14.51740;,
 -198.43311;21.35830;19.54580;,
 -190.47200;22.32060;-23.90540;,
 -150.50591;22.67490;-20.61290;,
 -145.41130;21.07140;-40.32090;,
 -176.37599;20.79630;-42.87210;,
 -193.98360;22.63590;14.54280;,
 -163.01849;22.91030;17.09380;,
 -119.54121;22.95010;-18.06190;,
 -117.15700;21.39660;-29.60060;,
 -132.05389;23.18520;19.64480;,
 -177.79271;-31.77460;-48.15940;,
 -146.82761;-31.49970;-45.60830;,
 -151.92241;-29.89570;-25.90030;,
 -191.88840;-30.25000;-29.19280;,
 -164.43520;-29.66020;11.80650;,
 -195.40021;-29.93500;9.25540;,
 -118.57380;-31.17400;-34.88780;,
 -120.95799;-29.62110;-23.34920;,
 -133.47040;-29.38580;14.35760;,
 -194.57111;21.01170;-22.73750;,
 -177.27501;19.45260;-48.56890;,
 -143.22150;19.75490;-45.76340;,
 -112.14920;20.11290;-33.97370;,
 -116.56539;21.70410;-16.31110;,
 -178.62219;-30.54410;-53.59730;,
 -195.91870;-28.98450;-27.76590;,
 -144.56909;-30.24200;-50.79180;,
 -117.91310;-28.29270;-21.33940;,
 -113.49670;-29.88380;-39.00220;,
 -192.95250;-21.30970;9.25340;,
 -192.51610;-6.60260;14.58670;,
 -207.70190;-5.80370;13.62630;,
 -208.13861;-20.51080;8.29300;,
 -191.35410;7.53570;7.97720;,
 -206.53989;8.33460;7.01680;,
 -190.14760;12.82320;-6.70320;,
 -205.33350;13.62230;-7.66360;,
 -189.60291;6.16280;-20.85490;,
 -204.78880;6.96210;-21.81530;,
 -190.03931;-8.54420;-26.18820;,
 -205.22530;-7.74520;-27.14850;,
 -191.20131;-22.68250;-19.57870;,
 -206.38730;-21.88340;-20.53910;,
 -192.40800;-27.97010;-4.89830;,
 -207.59399;-27.17130;-5.85870;,
 -192.95250;-21.30970;9.25340;,
 -208.13861;-20.51080;8.29300;,
 -192.51610;-6.60260;14.58670;,
 -192.95250;-21.30970;9.25340;,
 -191.27750;-7.57340;-5.80080;,
 -191.35410;7.53570;7.97720;,
 -190.14760;12.82320;-6.70320;,
 -189.60291;6.16280;-20.85490;,
 -190.03931;-8.54420;-26.18820;,
 -191.20131;-22.68250;-19.57870;,
 -192.40800;-27.97010;-4.89830;,
 -208.13861;-20.51080;8.29300;,
 -207.70190;-5.80370;13.62630;,
 -206.46341;-6.77460;-6.76110;,
 -206.53989;8.33460;7.01680;,
 -205.33350;13.62230;-7.66360;,
 -204.78880;6.96210;-21.81530;,
 -205.22530;-7.74520;-27.14850;,
 -206.38730;-21.88340;-20.53910;,
 -207.59399;-27.17130;-5.85870;,
 -304.74380;5.04400;13.13680;,
 -290.10400;2.90670;18.24910;,
 -287.80130;19.64330;19.08980;,
 -302.44110;21.78110;13.97750;,
 -276.12070;1.29780;11.40720;,
 -273.81799;18.03430;12.24790;,
 -270.98471;1.16020;-3.38100;,
 -268.68201;17.89710;-2.54030;,
 -277.70502;2.57390;-17.45280;,
 -275.40240;19.31080;-16.61210;,
 -292.34430;4.71130;-22.56510;,
 -290.04150;21.44820;-21.72440;,
 -306.32788;6.32010;-15.72320;,
 -304.02542;23.05670;-14.88250;,
 -311.46368;6.45800;-0.93500;,
 -309.16101;23.19480;-0.09430;,
 -304.74380;5.04400;13.13680;,
 -302.44110;21.78110;13.97750;,
 -290.10400;2.90670;18.24910;,
 -304.74380;5.04400;13.13680;,
 -291.22418;3.80900;-2.15800;,
 -276.12070;1.29780;11.40720;,
 -270.98471;1.16020;-3.38100;,
 -277.70502;2.57390;-17.45280;,
 -292.34430;4.71130;-22.56510;,
 -306.32788;6.32010;-15.72320;,
 -311.46368;6.45800;-0.93500;,
 -302.44110;21.78110;13.97750;,
 -287.80130;19.64330;19.08980;,
 -288.92151;20.54590;-1.31730;,
 -273.81799;18.03430;12.24790;,
 -268.68201;17.89710;-2.54030;,
 -275.40240;19.31080;-16.61210;,
 -290.04150;21.44820;-21.72440;,
 -304.02542;23.05670;-14.88250;,
 -309.16101;23.19480;-0.09430;,
 -308.41898;-24.48140;9.89610;,
 -293.77982;-26.61900;15.00840;,
 -291.47672;-9.88210;15.84910;,
 -306.11661;-7.74470;10.73670;,
 -279.79559;-28.22790;8.16650;,
 -277.49341;-11.49080;9.00720;,
 -274.66022;-28.36540;-6.62170;,
 -272.35760;-11.62860;-5.78110;,
 -281.38040;-26.95170;-20.69350;,
 -279.07770;-10.21480;-19.85280;,
 -296.02002;-24.81400;-25.80580;,
 -293.71710;-8.07740;-24.96520;,
 -310.00339;-23.20510;-18.96400;,
 -307.70041;-6.46890;-18.12330;,
 -315.13910;-23.06750;-4.17570;,
 -312.83652;-6.33050;-3.33500;,
 -308.41898;-24.48140;9.89610;,
 -306.11661;-7.74470;10.73670;,
 -293.77982;-26.61900;15.00840;,
 -308.41898;-24.48140;9.89610;,
 -294.89981;-25.71660;-5.39870;,
 -279.79559;-28.22790;8.16650;,
 -274.66022;-28.36540;-6.62170;,
 -281.38040;-26.95170;-20.69350;,
 -296.02002;-24.81400;-25.80580;,
 -310.00339;-23.20510;-18.96400;,
 -315.13910;-23.06750;-4.17570;,
 -306.11661;-7.74470;10.73670;,
 -291.47672;-9.88210;15.84910;,
 -292.59711;-8.97980;-4.55810;,
 -277.49341;-11.49080;9.00720;,
 -272.35760;-11.62860;-5.78110;,
 -279.07770;-10.21480;-19.85280;,
 -293.71710;-8.07740;-24.96520;,
 -307.70041;-6.46890;-18.12330;,
 -312.83652;-6.33050;-3.33500;,
 -0.80580;-24.75190;-2.45650;,
 -116.34541;67.02040;-54.28850;,
 -116.34541;67.02040;-54.28850;;
 
 208;
 4;0,1,2,3;,
 3;1,4,2;,
 3;2,5,6;,
 3;5,2,4;,
 4;7,8,6,5;,
 4;9,10,8,7;,
 3;10,9,11;,
 3;9,12,11;,
 3;11,12,13;,
 4;13,14,15,11;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;20,21,22,23;,
 4;24,25,21,20;,
 4;21,26,27,22;,
 4;25,28,26,21;,
 4;29,30,31,32;,
 4;32,31,33,34;,
 4;30,35,36,31;,
 4;31,36,37,33;,
 4;38,20,23,39;,
 4;39,23,22,40;,
 4;3,24,20,38;,
 4;2,25,24,3;,
 4;40,22,27,41;,
 4;41,27,26,42;,
 4;42,26,28,6;,
 4;6,28,25,2;,
 4;43,29,32,44;,
 4;45,30,29,43;,
 4;44,32,34,0;,
 4;0,34,33,1;,
 4;46,36,35,47;,
 4;47,35,30,45;,
 4;1,33,37,4;,
 4;4,37,36,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,60;,
 4;58,61,62,59;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;67,68,69,70;,
 4;71,72,68,67;,
 4;68,73,74,69;,
 4;72,75,73,68;,
 4;76,77,78,79;,
 4;79,78,80,81;,
 4;77,82,83,78;,
 4;78,83,84,80;,
 4;85,67,70,86;,
 4;86,70,69,87;,
 4;51,71,67,85;,
 4;50,72,71,51;,
 4;87,69,74,88;,
 4;88,74,73,89;,
 4;89,73,75,53;,
 4;53,75,72,50;,
 4;90,76,79,91;,
 4;92,77,76,90;,
 4;91,79,81,48;,
 4;48,81,80,49;,
 4;93,83,82,94;,
 4;94,82,77,92;,
 4;49,80,84,52;,
 4;52,84,83,93;,
 4;95,96,97,98;,
 4;96,99,100,97;,
 4;99,101,102,100;,
 4;101,103,104,102;,
 4;103,105,106,104;,
 4;105,107,108,106;,
 4;107,109,110,108;,
 4;109,111,112,110;,
 4;113,114,115,116;,
 4;117,118,114,113;,
 4;114,119,120,115;,
 4;118,121,119,114;,
 4;122,123,124,125;,
 4;125,124,126,127;,
 4;123,128,129,124;,
 4;124,129,130,126;,
 4;131,113,116,132;,
 4;132,116,115,133;,
 4;98,117,113,131;,
 4;97,118,117,98;,
 4;133,115,120,134;,
 4;134,120,119,135;,
 4;135,119,121,100;,
 4;100,121,118,97;,
 4;136,122,125,137;,
 4;138,123,122,136;,
 4;137,125,127,95;,
 4;95,127,126,96;,
 4;139,129,128,140;,
 4;140,128,123,138;,
 4;96,126,130,99;,
 4;99,130,129,139;,
 4;141,142,143,144;,
 4;142,145,146,143;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;159,160,161,162;,
 4;163,164,160,159;,
 4;160,165,166,161;,
 4;164,167,165,160;,
 4;168,169,170,171;,
 4;171,170,172,173;,
 4;169,174,175,170;,
 4;170,175,176,172;,
 4;177,159,162,178;,
 4;178,162,161,179;,
 4;144,163,159,177;,
 4;143,164,163,144;,
 4;179,161,166,180;,
 4;180,166,165,181;,
 4;181,165,167,146;,
 4;146,167,164,143;,
 4;182,168,171,183;,
 4;184,169,168,182;,
 4;183,171,173,141;,
 4;141,173,172,142;,
 4;185,175,174,186;,
 4;186,174,169,184;,
 4;142,172,176,145;,
 4;145,176,175,185;,
 4;187,188,189,190;,
 4;188,191,192,189;,
 4;191,193,194,192;,
 4;193,195,196,194;,
 4;195,197,198,196;,
 4;197,199,200,198;,
 4;199,201,202,200;,
 4;201,203,204,202;,
 3;205,206,207;,
 3;208,205,207;,
 3;209,208,207;,
 3;210,209,207;,
 3;211,210,207;,
 3;212,211,207;,
 3;213,212,207;,
 3;206,213,207;,
 3;214,215,216;,
 3;215,217,216;,
 3;217,218,216;,
 3;218,219,216;,
 3;219,220,216;,
 3;220,221,216;,
 3;221,222,216;,
 3;222,214,216;,
 4;223,224,225,226;,
 4;224,227,228,225;,
 4;227,229,230,228;,
 4;229,231,232,230;,
 4;231,233,234,232;,
 4;233,235,236,234;,
 4;235,237,238,236;,
 4;237,239,240,238;,
 3;241,242,243;,
 3;244,241,243;,
 3;245,244,243;,
 3;246,245,243;,
 3;247,246,243;,
 3;248,247,243;,
 3;249,248,243;,
 3;242,249,243;,
 3;250,251,252;,
 3;251,253,252;,
 3;253,254,252;,
 3;254,255,252;,
 3;255,256,252;,
 3;256,257,252;,
 3;257,258,252;,
 3;258,250,252;,
 4;259,260,261,262;,
 4;260,263,264,261;,
 4;263,265,266,264;,
 4;265,267,268,266;,
 4;267,269,270,268;,
 4;269,271,272,270;,
 4;271,273,274,272;,
 4;273,275,276,274;,
 3;277,278,279;,
 3;280,277,279;,
 3;281,280,279;,
 3;282,281,279;,
 3;283,282,279;,
 3;284,283,279;,
 3;285,284,279;,
 3;278,285,279;,
 3;286,287,288;,
 3;287,289,288;,
 3;289,290,288;,
 3;290,291,288;,
 3;291,292,288;,
 3;292,293,288;,
 3;293,294,288;,
 3;294,286,288;,
 4;295,12,9,7;,
 4;4,295,7,5;,
 3;59,296,60;,
 3;297,56,60;;
 
 MeshMaterialList {
  1;
  208;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  267;
  -0.191921;-0.090737;0.977207;,
  -0.191924;-0.090737;0.977206;,
  -0.191920;-0.090736;0.977207;,
  -0.191921;-0.090736;0.977207;,
  -0.191916;-0.090734;0.977208;,
  0.867104;-0.492062;0.077492;,
  0.996560;-0.039665;0.072773;,
  0.801051;0.033239;-0.597673;,
  0.883709;0.017651;-0.467705;,
  0.407399;0.077052;-0.909994;,
  0.509244;0.068565;-0.857887;,
  0.191918;0.090736;-0.977207;,
  -0.879509;-0.458614;-0.127034;,
  -0.856567;0.494501;-0.147519;,
  -0.202453;0.965839;-0.161763;,
  -0.302221;0.950270;-0.075166;,
  0.012257;0.988980;-0.147542;,
  -0.036877;0.998406;-0.042732;,
  -0.232037;0.971038;0.056965;,
  -0.069940;0.992032;0.104794;,
  0.182853;0.972995;-0.140877;,
  0.237480;0.970937;-0.029728;,
  0.135184;0.984823;0.108851;,
  -0.159660;-0.982940;-0.091316;,
  -0.259755;-0.965571;-0.014113;,
  0.036875;-0.998406;0.042728;,
  0.086809;-0.994040;-0.065945;,
  -0.154016;-0.985202;0.075200;,
  0.024281;-0.992184;0.122396;,
  0.301524;-0.951645;0.058785;,
  0.260718;-0.964954;-0.029834;,
  0.208988;-0.970125;0.123211;,
  0.872033;-0.476970;0.109806;,
  0.872171;0.452744;0.185315;,
  0.872035;-0.476967;0.109806;,
  0.872165;0.452755;0.185314;,
  0.872037;-0.476964;0.109806;,
  0.872159;0.452767;0.185313;,
  0.052583;-0.401058;-0.914542;,
  0.033508;0.546274;-0.836936;,
  -0.104983;-0.444394;-0.889658;,
  0.046371;0.389251;-0.919964;,
  -0.857511;-0.447111;-0.254491;,
  -0.857200;0.482651;-0.179600;,
  -0.872167;-0.452751;-0.185316;,
  -0.872048;0.476942;-0.109815;,
  0.009161;-0.553179;0.833012;,
  -0.004782;0.416519;0.909115;,
  -0.281850;0.931952;0.228091;,
  -0.015659;0.936005;0.351638;,
  -0.306341;0.951922;-0.000318;,
  -0.018281;0.996885;0.076716;,
  0.260941;0.919070;0.295329;,
  0.297812;0.946067;0.127537;,
  -0.210265;0.959985;-0.184978;,
  -0.004821;0.977959;-0.208742;,
  0.217698;0.972366;-0.084327;,
  -0.235255;-0.967582;0.091867;,
  0.014991;-0.978302;0.206642;,
  0.018288;-0.996885;-0.076715;,
  -0.267490;-0.952422;-0.146089;,
  0.247634;-0.958443;0.141651;,
  0.285245;-0.958010;-0.029196;,
  0.032891;-0.932144;-0.360592;,
  -0.153219;-0.929430;-0.335685;,
  0.203762;-0.948456;-0.242720;,
  -0.946330;0.022036;-0.322450;,
  0.215752;-0.143536;0.965841;,
  0.215750;-0.143535;0.965842;,
  0.215747;-0.143535;0.965842;,
  0.996222;-0.084170;-0.021377;,
  0.995215;-0.079508;-0.056794;,
  -0.078134;0.134370;-0.987846;,
  -0.215747;0.143535;-0.965842;,
  -0.995178;0.091419;-0.035533;,
  -0.110202;0.987155;-0.115672;,
  -0.141595;0.989901;-0.006850;,
  0.004344;0.993222;-0.116150;,
  0.013648;0.999877;-0.007694;,
  -0.063933;0.988997;0.133410;,
  0.046221;0.987757;0.148997;,
  0.121667;0.986213;-0.112168;,
  0.184175;0.982681;-0.020453;,
  0.158912;0.980758;0.113402;,
  -0.162489;-0.980454;-0.110940;,
  -0.191688;-0.981321;-0.016288;,
  -0.013646;-0.999877;0.007691;,
  -0.023174;-0.994134;-0.105642;,
  -0.108183;-0.992180;0.062249;,
  0.004200;-0.997150;0.075331;,
  0.161018;-0.986906;0.009500;,
  0.111058;-0.992370;-0.053560;,
  0.112083;-0.992823;0.041724;,
  -0.080855;-0.097585;0.991937;,
  -0.080856;-0.097584;0.991937;,
  -0.080856;-0.097584;0.991937;,
  0.958230;-0.054073;0.280840;,
  0.967789;-0.050884;0.246565;,
  0.218882;0.091802;-0.971423;,
  0.080855;0.097585;-0.991937;,
  -0.940322;0.059049;-0.335124;,
  -0.087729;0.977782;-0.190384;,
  -0.150323;0.983949;-0.096165;,
  0.021574;0.987370;-0.156954;,
  -0.002133;0.998689;-0.051139;,
  -0.118224;0.991126;0.060767;,
  -0.017762;0.993932;0.108550;,
  0.132448;0.984161;-0.117833;,
  0.164708;0.986274;-0.011597;,
  0.100559;0.988989;0.108577;,
  -0.104687;-0.988701;-0.107288;,
  -0.160878;-0.986639;-0.025725;,
  0.002128;-0.998689;0.051140;,
  0.026876;-0.997835;-0.060025;,
  -0.104544;-0.991721;0.074567;,
  -0.001148;-0.992677;0.120795;,
  0.167998;-0.980248;0.104354;,
  0.139315;-0.989806;0.029597;,
  0.111767;-0.986373;0.120731;,
  -0.081899;-0.671771;0.736217;,
  -0.060558;0.047470;0.997035;,
  -0.003737;0.738906;0.673798;,
  0.055280;0.997495;-0.044134;,
  0.081912;0.671773;-0.736215;,
  0.060555;-0.047471;-0.997035;,
  0.003735;-0.738903;-0.673802;,
  -0.055267;-0.997496;0.044135;,
  0.996633;-0.052437;0.063033;,
  -0.996633;0.052441;-0.063030;,
  -0.662261;0.053575;0.747356;,
  0.052771;-0.057339;0.996959;,
  0.736974;-0.134668;0.662370;,
  0.989277;-0.133085;-0.060165;,
  0.662256;-0.053573;-0.747360;,
  -0.052760;0.057336;-0.996960;,
  -0.736975;0.134662;-0.662370;,
  -0.989278;0.133082;0.060158;,
  -0.131858;-0.990594;-0.036562;,
  0.131859;0.990594;0.036565;,
  -0.662261;0.053572;0.747356;,
  0.052762;-0.057334;0.996960;,
  0.736979;-0.134655;0.662367;,
  0.989278;-0.133074;-0.060170;,
  0.662258;-0.053577;-0.747358;,
  -0.052766;0.057338;-0.996959;,
  -0.736973;0.134673;-0.662370;,
  -0.989277;0.133083;0.060157;,
  -0.131865;-0.990593;-0.036568;,
  0.131858;0.990594;0.036560;,
  0.883708;0.017650;-0.467705;,
  0.996559;-0.039665;0.072773;,
  -0.191916;-0.090734;0.977208;,
  0.979428;-0.051256;0.195176;,
  0.979428;-0.051255;0.195175;,
  -0.881757;-0.428944;-0.196244;,
  -0.612612;0.746131;-0.260758;,
  -0.996925;0.039185;-0.067863;,
  -0.657728;0.751970;0.043991;,
  0.051243;0.974154;-0.219997;,
  -0.091946;0.971297;0.219382;,
  0.281549;0.944879;-0.167134;,
  0.491118;0.871045;-0.009140;,
  0.228722;0.958505;0.170160;,
  0.144916;-0.968038;-0.204701;,
  0.091942;-0.971302;-0.219363;,
  -0.256059;-0.960698;0.107209;,
  0.001306;-0.972727;0.231948;,
  0.377891;-0.921705;-0.087515;,
  0.290415;-0.939857;0.179801;,
  0.036093;-0.402215;-0.914833;,
  0.044316;0.545397;-0.837006;,
  -0.235046;-0.530857;0.814214;,
  -0.270760;0.398345;0.876362;,
  0.254856;-0.541801;0.800937;,
  0.262116;0.404582;0.876133;,
  -0.534922;0.836822;-0.116565;,
  0.995957;-0.088724;0.014067;,
  0.061003;0.122584;-0.990582;,
  -0.952159;0.119399;-0.281312;,
  -0.975460;0.057677;0.212487;,
  -0.293153;0.955986;-0.012316;,
  -0.167315;0.973704;-0.154614;,
  0.001943;0.983287;-0.182051;,
  -0.106572;0.977317;0.183011;,
  0.071251;0.962559;0.261539;,
  0.177972;0.974512;-0.136571;,
  0.348446;0.936963;-0.026176;,
  0.227809;0.961686;0.152526;,
  -0.239941;-0.953163;-0.184141;,
  -0.364981;-0.930418;-0.033334;,
  -0.039064;-0.965219;-0.258509;,
  -0.152146;-0.982095;0.111089;,
  0.028889;-0.982487;0.184076;,
  0.331686;-0.943379;0.004574;,
  0.171471;-0.978731;-0.112619;,
  0.178511;-0.980677;0.080038;,
  0.947448;-0.057192;0.314757;,
  0.352639;0.084228;-0.931961;,
  -0.826180;0.078379;-0.557928;,
  -0.995183;0.035996;-0.091191;,
  -0.292695;0.945153;-0.144964;,
  -0.130320;0.961007;-0.243891;,
  0.039184;0.974715;-0.219987;,
  -0.173565;0.980142;0.095898;,
  -0.027141;0.974089;0.224530;,
  0.193681;0.973231;-0.123727;,
  0.323974;0.945449;0.034156;,
  0.154926;0.973648;0.167354;,
  -0.157136;-0.966804;-0.201491;,
  -0.321992;-0.941851;-0.096110;,
  0.056988;-0.975629;-0.211899;,
  -0.161291;-0.981031;0.107529;,
  -0.010412;-0.972869;0.231123;,
  0.331540;-0.931682;0.148490;,
  0.214401;-0.976701;-0.009341;,
  0.163459;-0.970635;0.176488;,
  0.996632;-0.052437;0.063045;,
  0.996632;-0.052443;0.063038;,
  0.996633;-0.052430;0.063036;,
  0.996634;-0.052421;0.063029;,
  0.996634;-0.052425;0.063028;,
  0.996633;-0.052438;0.063026;,
  0.996633;-0.052449;0.063028;,
  0.996632;-0.052450;0.063030;,
  -0.996632;0.052454;-0.063042;,
  -0.996632;0.052448;-0.063041;,
  -0.996633;0.052432;-0.063030;,
  -0.996634;0.052421;-0.063025;,
  -0.996634;0.052426;-0.063026;,
  -0.996634;0.052441;-0.063022;,
  -0.996633;0.052452;-0.063024;,
  -0.996632;0.052454;-0.063034;,
  -0.131858;-0.990594;-0.036561;,
  -0.131857;-0.990594;-0.036566;,
  -0.131859;-0.990594;-0.036568;,
  -0.131851;-0.990595;-0.036563;,
  -0.131857;-0.990595;-0.036556;,
  -0.131860;-0.990594;-0.036562;,
  -0.131858;-0.990594;-0.036559;,
  -0.131861;-0.990594;-0.036563;,
  0.131868;0.990593;0.036563;,
  0.131880;0.990591;0.036574;,
  0.131866;0.990592;0.036589;,
  0.131852;0.990594;0.036576;,
  0.131858;0.990594;0.036556;,
  0.131849;0.990595;0.036563;,
  0.131844;0.990596;0.036552;,
  0.131855;0.990595;0.036545;,
  -0.131868;-0.990593;-0.036567;,
  -0.131871;-0.990592;-0.036562;,
  -0.131856;-0.990594;-0.036572;,
  -0.131851;-0.990595;-0.036564;,
  -0.131863;-0.990593;-0.036563;,
  -0.131873;-0.990592;-0.036575;,
  -0.131870;-0.990592;-0.036577;,
  -0.131867;-0.990593;-0.036568;,
  0.131868;0.990593;0.036568;,
  0.131854;0.990595;0.036560;,
  0.131851;0.990595;0.036560;,
  0.131851;0.990595;0.036560;,
  0.131855;0.990595;0.036563;,
  0.131850;0.990595;0.036568;,
  0.131858;0.990595;0.036549;,
  0.131876;0.990592;0.036553;,
  0.979428;-0.051253;0.195175;,
  0.690014;0.663475;0.289279;,
  0.084313;0.081070;-0.993136;;
  208;
  4;0,1,2,0;,
  3;1,3,2;,
  3;2,151,4;,
  3;151,2,3;,
  4;150,6,152,153;,
  4;149,8,6,150;,
  3;8,149,10;,
  3;149,7,10;,
  3;10,7,9;,
  4;9,11,11,10;,
  4;154,12,13,155;,
  4;12,156,157,13;,
  4;15,17,16,14;,
  4;18,19,17,15;,
  4;17,21,20,16;,
  4;19,22,21,17;,
  4;23,26,25,24;,
  4;24,25,28,27;,
  4;26,30,29,25;,
  4;25,29,31,28;,
  4;13,15,14,155;,
  4;155,14,16,158;,
  4;157,18,15,13;,
  4;159,19,18,157;,
  4;158,16,20,160;,
  4;160,20,21,161;,
  4;161,21,22,162;,
  4;162,22,19,159;,
  4;154,23,24,12;,
  4;163,26,23,164;,
  4;12,24,27,165;,
  4;165,27,28,166;,
  4;5,29,30,167;,
  4;167,30,26,163;,
  4;166,28,31,168;,
  4;168,31,29,5;,
  4;32,34,35,33;,
  4;34,36,37,35;,
  4;169,38,39,170;,
  4;38,40,41,39;,
  4;66,42,43,66;,
  4;42,44,45,43;,
  4;171,46,47,172;,
  4;46,173,174,47;,
  4;49,51,50,48;,
  4;52,53,51,49;,
  4;51,55,54,50;,
  4;53,56,55,51;,
  4;57,60,59,58;,
  4;58,59,62,61;,
  4;60,64,63,59;,
  4;59,63,65,62;,
  4;47,49,48,172;,
  4;45,48,50,43;,
  4;174,52,49,47;,
  4;35,53,52,33;,
  4;43,50,54,175;,
  4;41,54,55,39;,
  4;39,55,56,170;,
  4;37,56,53,35;,
  4;171,57,58,46;,
  4;42,60,57,44;,
  4;46,58,61,173;,
  4;32,61,62,34;,
  4;38,63,64,40;,
  4;40,64,60,42;,
  4;34,62,65,36;,
  4;169,65,63,38;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;176,70,70,176;,
  4;70,71,71,70;,
  4;177,72,72,177;,
  4;72,73,73,72;,
  4;178,74,74,178;,
  4;74,179,179,74;,
  4;76,78,77,75;,
  4;79,80,78,76;,
  4;78,82,81,77;,
  4;80,83,82,78;,
  4;84,87,86,85;,
  4;85,86,89,88;,
  4;87,91,90,86;,
  4;86,90,92,89;,
  4;180,76,75,181;,
  4;181,75,77,182;,
  4;183,79,76,180;,
  4;184,80,79,183;,
  4;182,77,81,185;,
  4;185,81,82,186;,
  4;186,82,83,187;,
  4;187,83,80,184;,
  4;188,84,85,189;,
  4;190,87,84,188;,
  4;189,85,88,191;,
  4;191,88,89,192;,
  4;193,90,91,194;,
  4;194,91,87,190;,
  4;192,89,92,195;,
  4;195,92,90,193;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  4;196,96,96,196;,
  4;96,97,97,96;,
  4;197,98,98,197;,
  4;98,99,99,98;,
  4;198,100,100,198;,
  4;100,199,199,100;,
  4;102,104,103,101;,
  4;105,106,104,102;,
  4;104,108,107,103;,
  4;106,109,108,104;,
  4;110,113,112,111;,
  4;111,112,115,114;,
  4;113,117,116,112;,
  4;112,116,118,115;,
  4;200,102,101,201;,
  4;201,101,103,202;,
  4;203,105,102,200;,
  4;204,106,105,203;,
  4;202,103,107,205;,
  4;205,107,108,206;,
  4;206,108,109,207;,
  4;207,109,106,204;,
  4;208,110,111,209;,
  4;210,113,110,208;,
  4;209,111,114,211;,
  4;211,114,115,212;,
  4;213,116,117,214;,
  4;214,117,113,210;,
  4;212,115,118,215;,
  4;215,118,116,213;,
  4;119,120,120,119;,
  4;120,121,121,120;,
  4;121,122,122,121;,
  4;122,123,123,122;,
  4;123,124,124,123;,
  4;124,125,125,124;,
  4;125,126,126,125;,
  4;126,119,119,126;,
  3;216,217,127;,
  3;218,216,127;,
  3;219,218,127;,
  3;220,219,127;,
  3;221,220,127;,
  3;222,221,127;,
  3;223,222,127;,
  3;217,223,127;,
  3;224,225,128;,
  3;225,226,128;,
  3;226,227,128;,
  3;227,228,128;,
  3;228,229,128;,
  3;229,230,128;,
  3;230,231,128;,
  3;231,224,128;,
  4;129,130,130,129;,
  4;130,131,131,130;,
  4;131,132,132,131;,
  4;132,133,133,132;,
  4;133,134,134,133;,
  4;134,135,135,134;,
  4;135,136,136,135;,
  4;136,129,129,136;,
  3;232,233,137;,
  3;234,232,137;,
  3;235,234,137;,
  3;236,235,137;,
  3;237,236,137;,
  3;238,237,137;,
  3;239,238,137;,
  3;233,239,137;,
  3;240,241,138;,
  3;241,242,138;,
  3;242,243,138;,
  3;243,244,138;,
  3;244,245,138;,
  3;245,246,138;,
  3;246,247,138;,
  3;247,240,138;,
  4;139,140,140,139;,
  4;140,141,141,140;,
  4;141,142,142,141;,
  4;142,143,143,142;,
  4;143,144,144,143;,
  4;144,145,145,144;,
  4;145,146,146,145;,
  4;146,139,139,146;,
  3;248,249,147;,
  3;250,248,147;,
  3;251,250,147;,
  3;252,251,147;,
  3;253,252,147;,
  3;254,253,147;,
  3;255,254,147;,
  3;249,255,147;,
  3;256,257,148;,
  3;257,258,148;,
  3;258,259,148;,
  3;259,260,148;,
  3;260,261,148;,
  3;261,262,148;,
  3;262,263,148;,
  3;263,256,148;,
  4;5,7,149,150;,
  4;264,5,150,153;,
  3;265,265,265;,
  3;41,40,266;;
 }
 MeshTextureCoords {
  298;
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.498894;0.625000;,
  0.625000;0.625000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.375000;,
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
  0.625000;0.500000;,
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
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.687500;,
  0.437500;0.311560;,
  0.468750;0.687500;,
  0.468750;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.531250;0.687500;,
  0.531250;0.311560;,
  0.562500;0.687500;,
  0.562500;0.311560;,
  0.593750;0.687500;,
  0.593750;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610485;0.954235;,
  0.500000;0.850000;,
  0.389515;0.954235;,
  0.343750;0.843750;,
  0.389515;0.733265;,
  0.500000;0.687500;,
  0.610485;0.733265;,
  0.656250;0.843750;,
  0.610485;0.045765;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.500000;0.312500;,
  0.610485;0.266735;,
  0.656250;0.156250;,
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.687500;,
  0.437500;0.311560;,
  0.468750;0.687500;,
  0.468750;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.531250;0.687500;,
  0.531250;0.311560;,
  0.562500;0.687500;,
  0.562500;0.311560;,
  0.593750;0.687500;,
  0.593750;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610485;0.954235;,
  0.500000;0.850000;,
  0.389515;0.954235;,
  0.343750;0.843750;,
  0.389515;0.733265;,
  0.500000;0.687500;,
  0.610485;0.733265;,
  0.656250;0.843750;,
  0.610485;0.045765;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.500000;0.312500;,
  0.610485;0.266735;,
  0.656250;0.156250;,
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.687500;,
  0.437500;0.311560;,
  0.468750;0.687500;,
  0.468750;0.311560;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.531250;0.687500;,
  0.531250;0.311560;,
  0.562500;0.687500;,
  0.562500;0.311560;,
  0.593750;0.687500;,
  0.593750;0.311560;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610485;0.954235;,
  0.500000;0.850000;,
  0.389515;0.954235;,
  0.343750;0.843750;,
  0.389515;0.733265;,
  0.500000;0.687500;,
  0.610485;0.733265;,
  0.656250;0.843750;,
  0.610485;0.045765;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389515;0.045765;,
  0.343750;0.156250;,
  0.389515;0.266735;,
  0.500000;0.312500;,
  0.610485;0.266735;,
  0.656250;0.156250;,
  0.375000;0.625000;,
  0.625000;0.437500;,
  0.500000;0.500000;;
 }
}
