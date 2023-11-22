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
 315;
 -12.28669;-12.84733;22.38382;,
 -11.66401;-12.58926;22.36391;,
 -11.97027;-12.58926;12.78387;,
 -12.59295;-12.84733;12.80378;,
 -11.04133;-12.84733;22.34401;,
 -11.34759;-12.84733;12.76397;,
 -10.78341;-13.47032;22.33576;,
 -11.08967;-13.47032;12.75572;,
 -11.04133;-14.09332;22.34401;,
 -11.34759;-14.09332;12.76397;,
 -11.66401;-14.35137;22.36391;,
 -11.97027;-14.35137;12.78387;,
 -12.28669;-14.09332;22.38382;,
 -12.59295;-14.09332;12.80378;,
 -12.54461;-13.47032;22.39207;,
 -12.85087;-13.47032;12.81203;,
 -12.28669;-12.84733;22.38382;,
 -12.59295;-12.84733;12.80378;,
 -11.41090;-5.08569;32.17044;,
 -12.03358;-5.34374;32.19035;,
 -11.45462;-7.09711;30.80287;,
 -10.78822;-5.34374;32.15054;,
 -10.53030;-5.96673;32.14229;,
 -10.78822;-6.58973;32.15054;,
 -11.41091;-6.84779;32.17044;,
 -12.03358;-6.58973;32.19035;,
 -12.29151;-5.96673;32.19859;,
 -12.59295;-12.84733;12.80378;,
 -11.97027;-12.58926;12.78387;,
 -11.97027;-13.47032;12.78387;,
 -11.34759;-12.84733;12.76397;,
 -11.08967;-13.47032;12.75572;,
 -11.34759;-14.09332;12.76397;,
 -11.97027;-14.35137;12.78387;,
 -12.59295;-14.09332;12.80378;,
 -12.85087;-13.47032;12.81203;,
 -11.66401;-12.58926;22.36391;,
 -12.28669;-12.84733;22.38382;,
 -12.21001;-11.69066;24.78223;,
 -11.58733;-11.43260;24.76232;,
 -11.04133;-12.84733;22.34401;,
 -10.96465;-11.69066;24.74241;,
 -10.78341;-13.47032;22.33576;,
 -10.70673;-12.31365;24.73417;,
 -11.04133;-14.09332;22.34401;,
 -10.96466;-12.93664;24.74241;,
 -11.66401;-14.35137;22.36391;,
 -11.58734;-13.19470;24.76232;,
 -12.28669;-14.09332;22.38382;,
 -12.21001;-12.93664;24.78223;,
 -12.54461;-13.47032;22.39207;,
 -12.46794;-12.31365;24.79047;,
 2.82826;-5.29747;-8.64515;,
 -8.92197;-3.57648;-8.64515;,
 -8.15873;-1.80735;-6.48149;,
 4.77472;-4.08786;-6.48149;,
 0.00000;0.00000;6.33699;,
 6.72897;-1.78882;6.33699;,
 6.72897;-1.78882;-0.00000;,
 0.00000;0.00000;0.00000;,
 4.77472;-4.08786;6.48149;,
 -8.15873;-1.80735;6.48149;,
 -8.92196;-1.85976;16.35316;,
 2.82826;-3.58074;16.35316;,
 1.48742;-15.85713;44.80176;,
 -11.47364;-13.92264;44.80176;,
 -12.39474;-17.44606;40.94655;,
 0.44507;-19.38053;40.94655;,
 -9.18849;-3.38380;-0.12425;,
 -10.01469;-1.66708;15.50926;,
 -8.57993;-1.73307;5.63760;,
 -8.57993;-1.73307;-5.63760;,
 3.92100;-3.77342;15.50926;,
 5.21226;-5.49013;-0.12425;,
 5.86746;-4.28054;-5.63760;,
 5.52070;-4.28054;5.63760;,
 -0.47826;-19.39417;1.93610;,
 -13.43932;-17.45970;1.93610;,
 -8.27760;-1.11261;-6.33699;,
 5.79556;-3.59407;-6.33699;,
 5.79556;-3.59407;6.33699;,
 -8.27760;-1.11261;6.33699;,
 -9.60031;-2.16661;15.97682;,
 3.36075;-4.10110;15.97682;,
 -9.60031;-2.16661;15.97682;,
 -8.27760;-1.11261;6.33699;,
 3.36075;-4.10110;15.97682;,
 5.79556;-3.59407;6.33699;,
 -6.72897;1.78883;-6.33699;,
 0.00000;0.00000;-6.33699;,
 6.72897;-1.78882;-6.33699;,
 -6.72897;1.78883;0.00000;,
 -6.72897;1.78883;6.33699;,
 -10.08316;-4.27369;22.44330;,
 2.87791;-5.05151;23.22604;,
 -13.43932;-17.45970;1.93610;,
 -12.45334;-16.02399;15.72893;,
 -0.47826;-19.39417;1.93610;,
 1.83556;-17.95848;15.72893;,
 -10.61510;-8.61211;46.31082;,
 2.34596;-10.54660;46.31082;,
 -11.53621;-18.69578;33.63177;,
 1.30360;-20.63027;33.63177;,
 -12.28809;-9.90617;21.00650;,
 -11.45238;-9.56000;21.00650;,
 -11.45238;-9.56000;8.14900;,
 -12.28809;-9.90617;8.14900;,
 -10.61668;-9.90617;21.00650;,
 -10.61668;-9.90617;8.14900;,
 -10.27052;-10.74187;21.00650;,
 -10.27052;-10.74187;8.14900;,
 -10.61668;-11.57758;21.00650;,
 -10.61668;-11.57758;8.14900;,
 -11.45238;-11.92374;21.00650;,
 -11.45238;-11.92374;8.14900;,
 -12.28809;-11.57758;21.00650;,
 -12.28809;-11.57758;8.14900;,
 -12.63425;-10.74187;21.00650;,
 -12.63425;-10.74187;8.14900;,
 -12.28809;-9.90617;21.00650;,
 -12.28809;-9.90617;8.14900;,
 -11.45238;-9.56000;21.00650;,
 -12.28809;-9.90617;21.00650;,
 -11.45238;-10.74187;21.00650;,
 -10.61668;-9.90617;21.00650;,
 -10.27052;-10.74187;21.00650;,
 -10.61668;-11.57758;21.00650;,
 -11.45238;-11.92374;21.00650;,
 -12.28809;-11.57758;21.00650;,
 -12.63425;-10.74187;21.00650;,
 -12.28809;-9.90617;8.14900;,
 -11.45238;-9.56000;8.14900;,
 -11.45238;-10.74187;8.14900;,
 -10.61668;-9.90617;8.14900;,
 -10.27052;-10.74187;8.14900;,
 -10.61668;-11.57758;8.14900;,
 -11.45238;-11.92374;8.14900;,
 -12.28809;-11.57758;8.14900;,
 -12.63425;-10.74187;8.14900;,
 -11.74688;-6.51345;21.00650;,
 -10.91117;-6.16728;21.00650;,
 -10.91117;-6.16728;8.14900;,
 -11.74688;-6.51345;8.14900;,
 -10.07547;-6.51345;21.00650;,
 -10.07547;-6.51345;8.14900;,
 -9.72931;-7.34915;21.00650;,
 -9.72931;-7.34915;8.14900;,
 -10.07547;-8.18486;21.00650;,
 -10.07547;-8.18486;8.14900;,
 -10.91117;-8.53102;21.00650;,
 -10.91117;-8.53102;8.14900;,
 -11.74688;-8.18486;21.00650;,
 -11.74688;-8.18486;8.14900;,
 -12.09304;-7.34915;21.00650;,
 -12.09304;-7.34915;8.14900;,
 -11.74688;-6.51345;21.00650;,
 -11.74688;-6.51345;8.14900;,
 -10.91117;-6.16728;21.00650;,
 -11.74688;-6.51345;21.00650;,
 -10.91117;-7.34915;21.00650;,
 -10.07547;-6.51345;21.00650;,
 -9.72931;-7.34915;21.00650;,
 -10.07547;-8.18486;21.00650;,
 -10.91117;-8.53102;21.00650;,
 -11.74688;-8.18486;21.00650;,
 -12.09304;-7.34915;21.00650;,
 -11.74688;-6.51345;8.14900;,
 -10.91117;-6.16728;8.14900;,
 -10.91117;-7.34915;8.14900;,
 -10.07547;-6.51345;8.14900;,
 -9.72931;-7.34915;8.14900;,
 -10.07547;-8.18486;8.14900;,
 -10.91117;-8.53102;8.14900;,
 -11.74688;-8.18486;8.14900;,
 -12.09304;-7.34915;8.14900;,
 -12.54272;-12.63462;21.03229;,
 -11.70744;-12.28846;21.00559;,
 -12.11827;-12.28846;8.15465;,
 -12.95355;-12.63462;8.18135;,
 -10.87216;-12.63462;20.97889;,
 -11.28299;-12.63462;8.12794;,
 -10.52617;-13.47033;20.96783;,
 -10.93700;-13.47033;8.11689;,
 -10.87216;-14.30603;20.97889;,
 -11.28299;-14.30603;8.12794;,
 -11.70744;-14.65219;21.00559;,
 -12.11827;-14.65219;8.15465;,
 -12.54272;-14.30603;21.03229;,
 -12.95355;-14.30603;8.18135;,
 -12.88870;-13.47033;21.04335;,
 -13.29953;-13.47033;8.19241;,
 -12.54272;-12.63462;21.03229;,
 -12.95355;-12.63462;8.18135;,
 -11.70744;-12.28846;21.00559;,
 -12.54272;-12.63462;21.03229;,
 -11.70744;-13.47033;21.00559;,
 -10.87216;-12.63462;20.97889;,
 -10.52617;-13.47033;20.96783;,
 -10.87216;-14.30603;20.97889;,
 -11.70744;-14.65219;21.00559;,
 -12.54272;-14.30603;21.03229;,
 -12.88870;-13.47033;21.04335;,
 -12.95355;-12.63462;8.18135;,
 -12.11827;-12.28846;8.15465;,
 -12.11827;-13.47033;8.15465;,
 -11.28299;-12.63462;8.12794;,
 -10.93700;-13.47033;8.11689;,
 -11.28299;-14.30603;8.12794;,
 -12.11827;-14.65219;8.15465;,
 -12.95355;-14.30603;8.18135;,
 -13.29953;-13.47033;8.19241;,
 -11.53417;-6.72616;22.36552;,
 -10.91117;-6.46810;22.36552;,
 -10.91117;-6.46810;12.78058;,
 -11.53417;-6.72616;12.78058;,
 -10.28818;-6.72616;22.36552;,
 -10.28818;-6.72616;12.78058;,
 -10.03012;-7.34915;22.36552;,
 -10.03012;-7.34915;12.78058;,
 -10.28818;-7.97215;22.36552;,
 -10.28818;-7.97215;12.78058;,
 -10.91117;-8.23020;22.36552;,
 -10.91117;-8.23020;12.78058;,
 -11.53417;-7.97215;22.36552;,
 -11.53417;-7.97215;12.78058;,
 -11.79223;-7.34915;22.36552;,
 -11.79223;-7.34915;12.78058;,
 -11.53417;-6.72616;22.36552;,
 -11.53417;-6.72616;12.78058;,
 -10.91117;-2.67319;27.95302;,
 -11.53417;-2.93124;27.95302;,
 -10.91117;-4.28595;26.96934;,
 -10.28817;-2.93124;27.95302;,
 -10.03011;-3.55424;27.95302;,
 -10.28817;-4.17723;27.95302;,
 -10.91117;-4.43529;27.95302;,
 -11.53417;-4.17723;27.95302;,
 -11.79223;-3.55424;27.95302;,
 -11.53417;-6.72616;12.78058;,
 -10.91117;-6.46810;12.78058;,
 -10.91117;-7.34915;12.78058;,
 -10.28818;-6.72616;12.78058;,
 -10.03012;-7.34915;12.78058;,
 -10.28818;-7.97215;12.78058;,
 -10.91117;-8.23020;12.78058;,
 -11.53417;-7.97215;12.78058;,
 -11.79223;-7.34915;12.78058;,
 -10.91117;-6.46810;22.36552;,
 -11.53417;-6.72616;22.36552;,
 -11.53417;-5.56949;24.76516;,
 -10.91117;-5.31143;24.76516;,
 -10.28818;-6.72616;22.36552;,
 -10.28817;-5.56949;24.76516;,
 -10.03012;-7.34915;22.36552;,
 -10.03012;-6.19248;24.76516;,
 -10.28818;-7.97215;22.36552;,
 -10.28818;-6.81548;24.76516;,
 -10.91117;-8.23020;22.36552;,
 -10.91117;-7.07354;24.76516;,
 -11.53417;-7.97215;22.36552;,
 -11.53417;-6.81548;24.76516;,
 -11.79223;-7.34915;22.36552;,
 -11.79223;-6.19248;24.76516;,
 -12.07538;-10.11888;22.36552;,
 -11.45238;-9.86082;22.36552;,
 -11.45238;-9.86082;12.78058;,
 -12.07538;-10.11888;12.78058;,
 -10.82939;-10.11888;22.36552;,
 -10.82939;-10.11888;12.78058;,
 -10.57133;-10.74187;22.36552;,
 -10.57133;-10.74187;12.78058;,
 -10.82939;-11.36487;22.36552;,
 -10.82939;-11.36487;12.78058;,
 -11.45238;-11.62292;22.36552;,
 -11.45238;-11.62292;12.78058;,
 -12.07538;-11.36487;22.36552;,
 -12.07538;-11.36487;12.78058;,
 -12.33344;-10.74187;22.36552;,
 -12.33344;-10.74187;12.78058;,
 -12.07538;-10.11888;22.36552;,
 -12.07538;-10.11888;12.78058;,
 -11.45238;-3.73538;30.28679;,
 -12.07538;-3.99343;30.28679;,
 -11.45238;-5.74680;28.91852;,
 -10.82938;-3.99343;30.28679;,
 -10.57132;-4.61643;30.28679;,
 -10.82938;-5.23942;30.28679;,
 -11.45238;-5.49748;30.28679;,
 -12.07538;-5.23942;30.28679;,
 -12.33344;-4.61643;30.28679;,
 -12.07538;-10.11888;12.78058;,
 -11.45238;-9.86082;12.78058;,
 -11.45238;-10.74187;12.78058;,
 -10.82939;-10.11888;12.78058;,
 -10.57133;-10.74187;12.78058;,
 -10.82939;-11.36487;12.78058;,
 -11.45238;-11.62292;12.78058;,
 -12.07538;-11.36487;12.78058;,
 -12.33344;-10.74187;12.78058;,
 -11.45238;-9.86082;22.36552;,
 -12.07538;-10.11888;22.36552;,
 -12.07538;-8.96221;24.76516;,
 -11.45238;-8.70415;24.76516;,
 -10.82939;-10.11888;22.36552;,
 -10.82938;-8.96221;24.76516;,
 -10.57133;-10.74187;22.36552;,
 -10.57133;-9.58520;24.76516;,
 -10.82939;-11.36487;22.36552;,
 -10.82939;-10.20819;24.76516;,
 -11.45238;-11.62292;22.36552;,
 -11.45238;-10.46626;24.76516;,
 -12.07538;-11.36487;22.36552;,
 -12.07538;-10.20819;24.76516;,
 -12.33344;-10.74187;22.36552;,
 -12.33344;-9.58520;24.76516;;
 
 241;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,18,20;,
 3;22,21,20;,
 3;23,22,20;,
 3;24,23,20;,
 3;25,24,20;,
 3;26,25,20;,
 3;19,26,20;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;31,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;34,35,29;,
 3;35,27,29;,
 4;36,37,38,39;,
 4;40,36,39,41;,
 4;42,40,41,43;,
 4;44,42,43,45;,
 4;46,44,45,47;,
 4;48,46,47,49;,
 4;50,48,49,51;,
 4;37,50,51,38;,
 4;39,38,19,18;,
 4;41,39,18,21;,
 4;43,41,21,22;,
 4;45,43,22,23;,
 4;47,45,23,24;,
 4;49,47,24,25;,
 4;51,49,25,26;,
 4;38,51,26,19;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,53,52;,
 4;77,78,54,53;,
 4;78,79,55,54;,
 4;79,76,52,55;,
 4;80,81,61,60;,
 4;81,82,62,61;,
 4;82,83,63,62;,
 4;83,80,60,63;,
 4;77,84,69,68;,
 4;84,85,70,69;,
 4;85,78,71,70;,
 4;78,77,68,71;,
 4;86,76,73,72;,
 4;76,79,74,73;,
 4;79,87,75,74;,
 4;87,86,72,75;,
 3;78,88,79;,
 3;88,89,79;,
 3;79,89,90;,
 3;78,81,88;,
 3;88,81,91;,
 3;91,81,92;,
 3;81,80,92;,
 3;92,80,56;,
 3;56,80,57;,
 3;80,79,57;,
 3;57,79,58;,
 3;58,79,90;,
 4;83,82,93,94;,
 4;82,95,96,93;,
 4;95,97,98,96;,
 4;97,83,94,98;,
 4;94,93,99,100;,
 4;93,96,101,99;,
 4;96,98,102,101;,
 4;98,94,100,102;,
 4;100,99,65,64;,
 4;99,101,66,65;,
 4;101,102,67,66;,
 4;102,100,64,67;,
 4;103,104,105,106;,
 4;104,107,108,105;,
 4;107,109,110,108;,
 4;109,111,112,110;,
 4;111,113,114,112;,
 4;113,115,116,114;,
 4;115,117,118,116;,
 4;117,119,120,118;,
 3;121,122,123;,
 3;124,121,123;,
 3;125,124,123;,
 3;126,125,123;,
 3;127,126,123;,
 3;128,127,123;,
 3;129,128,123;,
 3;122,129,123;,
 3;130,131,132;,
 3;131,133,132;,
 3;133,134,132;,
 3;134,135,132;,
 3;135,136,132;,
 3;136,137,132;,
 3;137,138,132;,
 3;138,130,132;,
 4;139,140,141,142;,
 4;140,143,144,141;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 3;157,158,159;,
 3;160,157,159;,
 3;161,160,159;,
 3;162,161,159;,
 3;163,162,159;,
 3;164,163,159;,
 3;165,164,159;,
 3;158,165,159;,
 3;166,167,168;,
 3;167,169,168;,
 3;169,170,168;,
 3;170,171,168;,
 3;171,172,168;,
 3;172,173,168;,
 3;173,174,168;,
 3;174,166,168;,
 4;175,176,177,178;,
 4;176,179,180,177;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,185,186,184;,
 4;185,187,188,186;,
 4;187,189,190,188;,
 4;189,191,192,190;,
 3;193,194,195;,
 3;196,193,195;,
 3;197,196,195;,
 3;198,197,195;,
 3;199,198,195;,
 3;200,199,195;,
 3;201,200,195;,
 3;194,201,195;,
 3;202,203,204;,
 3;203,205,204;,
 3;205,206,204;,
 3;206,207,204;,
 3;207,208,204;,
 3;208,209,204;,
 3;209,210,204;,
 3;210,202,204;,
 4;211,212,213,214;,
 4;212,215,216,213;,
 4;215,217,218,216;,
 4;217,219,220,218;,
 4;219,221,222,220;,
 4;221,223,224,222;,
 4;223,225,226,224;,
 4;225,227,228,226;,
 3;229,230,231;,
 3;232,229,231;,
 3;233,232,231;,
 3;234,233,231;,
 3;235,234,231;,
 3;236,235,231;,
 3;237,236,231;,
 3;230,237,231;,
 3;238,239,240;,
 3;239,241,240;,
 3;241,242,240;,
 3;242,243,240;,
 3;243,244,240;,
 3;244,245,240;,
 3;245,246,240;,
 3;246,238,240;,
 4;247,248,249,250;,
 4;251,247,250,252;,
 4;253,251,252,254;,
 4;255,253,254,256;,
 4;257,255,256,258;,
 4;259,257,258,260;,
 4;261,259,260,262;,
 4;248,261,262,249;,
 4;250,249,230,229;,
 4;252,250,229,232;,
 4;254,252,232,233;,
 4;256,254,233,234;,
 4;258,256,234,235;,
 4;260,258,235,236;,
 4;262,260,236,237;,
 4;249,262,237,230;,
 4;263,264,265,266;,
 4;264,267,268,265;,
 4;267,269,270,268;,
 4;269,271,272,270;,
 4;271,273,274,272;,
 4;273,275,276,274;,
 4;275,277,278,276;,
 4;277,279,280,278;,
 3;281,282,283;,
 3;284,281,283;,
 3;285,284,283;,
 3;286,285,283;,
 3;287,286,283;,
 3;288,287,283;,
 3;289,288,283;,
 3;282,289,283;,
 3;290,291,292;,
 3;291,293,292;,
 3;293,294,292;,
 3;294,295,292;,
 3;295,296,292;,
 3;296,297,292;,
 3;297,298,292;,
 3;298,290,292;,
 4;299,300,301,302;,
 4;303,299,302,304;,
 4;305,303,304,306;,
 4;307,305,306,308;,
 4;309,307,308,310;,
 4;311,309,310,312;,
 4;313,311,312,314;,
 4;300,313,314,301;,
 4;302,301,282,281;,
 4;304,302,281,284;,
 4;306,304,284,285;,
 4;308,306,285,286;,
 4;310,308,286,287;,
 4;312,310,287,288;,
 4;314,312,288,289;,
 4;301,314,289,282;,
 4;90,89,59,58;,
 4;91,92,56,59;,
 4;89,88,91,59;;
 
 MeshMaterialList {
  1;
  241;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  225;
  -0.707818;0.692646;-0.138690;,
  -0.007166;0.974530;-0.224140;,
  0.697515;0.692645;-0.183618;,
  0.999489;0.000000;-0.031952;,
  0.707812;-0.692652;0.138693;,
  0.007165;-0.974530;0.224142;,
  -0.697508;-0.692651;0.183619;,
  -0.999489;0.000002;0.031952;,
  -0.706753;0.707100;0.022594;,
  0.000000;1.000000;-0.000000;,
  0.706753;0.707100;-0.022594;,
  0.999489;0.000003;-0.031952;,
  0.706745;-0.707107;-0.022594;,
  0.000000;-1.000000;-0.000000;,
  -0.706745;-0.707107;0.022594;,
  -0.999489;0.000003;0.031952;,
  -0.031953;0.000000;-0.999489;,
  -0.673374;0.625943;-0.393399;,
  -0.017266;0.836524;-0.547658;,
  0.648496;0.627144;-0.431443;,
  0.999598;0.000451;-0.028338;,
  0.673374;-0.625943;0.393400;,
  0.017264;-0.836523;0.547659;,
  -0.648492;-0.627147;0.431445;,
  -0.999598;-0.000451;0.028337;,
  0.497021;-0.431589;0.752795;,
  0.026418;-0.562452;0.826408;,
  0.027854;-0.489764;0.871410;,
  -0.447932;-0.431585;0.783002;,
  -0.840142;0.046713;0.540351;,
  -0.700355;0.709382;0.079241;,
  -0.005722;0.983801;-0.179173;,
  0.703986;0.709383;0.034345;,
  0.872938;0.046715;0.485589;,
  0.682776;-0.509889;-0.523288;,
  -0.086562;-0.585438;-0.806083;,
  0.009277;0.052614;-0.998572;,
  -0.937144;0.332429;-0.106076;,
  0.009277;0.052614;0.998572;,
  0.018581;0.105380;0.994258;,
  -0.097594;-0.659912;0.744977;,
  0.145469;0.981322;0.125881;,
  0.125986;0.778102;-0.615373;,
  0.086624;0.525081;-0.846632;,
  0.171157;0.985140;0.014336;,
  0.309751;0.949406;0.051789;,
  -0.956195;0.279862;0.085844;,
  -0.964489;0.264015;0.007534;,
  -0.694484;0.719469;-0.007516;,
  -0.914987;0.397846;-0.067204;,
  0.815764;-0.548001;0.184998;,
  0.838094;-0.545107;0.021354;,
  0.897695;-0.434851;-0.071057;,
  0.918150;-0.392830;0.051823;,
  0.000000;0.000000;-1.000000;,
  -0.882202;0.470871;0.000000;,
  0.256915;0.966434;0.000000;,
  0.094331;0.971748;0.216352;,
  -0.986049;0.164126;0.027768;,
  -0.141220;-0.989890;-0.013230;,
  0.095995;0.973768;0.206303;,
  -0.974963;0.217640;-0.045597;,
  -0.145275;-0.989388;0.002421;,
  -0.076722;-0.512272;0.855389;,
  -0.133707;-0.889222;0.437500;,
  -0.707109;0.707105;0.000000;,
  0.000002;1.000000;0.000000;,
  0.707110;0.707103;0.000000;,
  1.000000;0.000002;0.000000;,
  0.707108;-0.707106;-0.000000;,
  0.000002;-1.000000;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -1.000000;0.000002;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.707109;0.707104;0.000000;,
  0.000002;1.000000;0.000000;,
  0.707108;-0.707105;-0.000000;,
  0.000002;-1.000000;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -1.000000;0.000002;0.000000;,
  -0.706748;0.707105;0.022594;,
  0.000000;1.000000;0.000000;,
  0.706744;0.707109;-0.022594;,
  0.999489;-0.000002;-0.031953;,
  0.706742;-0.707110;-0.022594;,
  0.000000;-1.000000;0.000000;,
  -0.706746;-0.707106;0.022594;,
  -0.999489;-0.000002;0.031953;,
  0.031950;0.000000;0.999490;,
  -0.031952;0.000000;-0.999489;,
  -0.703018;0.692653;-0.161237;,
  0.000002;0.974530;-0.224255;,
  0.703021;0.692650;-0.161237;,
  1.000000;0.000001;-0.000000;,
  0.703018;-0.692653;0.161237;,
  0.000003;-0.974531;0.224254;,
  -0.703016;-0.692655;0.161237;,
  -1.000000;0.000003;-0.000001;,
  -0.707105;0.707109;0.000000;,
  0.000003;1.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  1.000000;0.000003;0.000000;,
  0.707104;-0.707109;-0.000000;,
  0.000003;-1.000000;-0.000000;,
  -0.707102;-0.707112;0.000000;,
  -1.000000;0.000003;0.000000;,
  -0.662704;0.629115;-0.406249;,
  0.000000;0.841218;-0.540697;,
  0.662707;0.629112;-0.406249;,
  1.000000;-0.000002;-0.000000;,
  0.662707;-0.629113;0.406247;,
  0.000002;-0.841218;0.540696;,
  -0.662705;-0.629114;0.406249;,
  -1.000000;0.000001;-0.000001;,
  0.427176;-0.394351;0.813639;,
  0.000000;-0.520720;0.853728;,
  -0.000000;-0.436148;0.899875;,
  -0.427176;-0.394351;0.813639;,
  -0.759812;0.042763;0.648735;,
  -0.649382;0.682271;0.335870;,
  0.000000;0.988671;0.150097;,
  0.649383;0.682271;0.335869;,
  0.759812;0.042763;0.648735;,
  -0.703018;0.692653;-0.161237;,
  0.000002;0.974530;-0.224255;,
  0.703021;0.692650;-0.161237;,
  1.000000;0.000000;0.000000;,
  0.703019;-0.692652;0.161237;,
  0.000003;-0.974531;0.224254;,
  -0.703017;-0.692654;0.161238;,
  -1.000000;0.000002;-0.000000;,
  -0.707105;0.707109;0.000000;,
  -0.707102;-0.707111;0.000000;,
  -1.000000;0.000003;0.000000;,
  -0.658957;0.622734;-0.421874;,
  0.000000;0.829619;-0.558331;,
  0.658960;0.622732;-0.421873;,
  1.000000;-0.000003;0.000001;,
  0.658961;-0.622732;0.421872;,
  0.000002;-0.829619;0.558330;,
  -0.658959;-0.622733;0.421873;,
  -1.000000;0.000000;0.000000;,
  0.472717;-0.431585;0.768293;,
  0.000000;-0.562451;0.826830;,
  0.000000;-0.489761;0.871857;,
  -0.472717;-0.431585;0.768293;,
  -0.856978;0.046721;0.513231;,
  -0.702527;0.709385;0.056821;,
  0.000000;0.983801;-0.179264;,
  0.702527;0.709385;0.056821;,
  0.856978;0.046721;0.513231;,
  0.256916;0.966434;0.000000;,
  -0.031960;-0.000002;-0.999489;,
  -0.031950;0.000000;-0.999489;,
  -0.031946;0.000004;-0.999490;,
  -0.031951;0.000000;-0.999490;,
  -0.031946;-0.000004;-0.999490;,
  -0.031950;0.000000;-0.999490;,
  -0.031960;0.000002;-0.999489;,
  -0.031962;-0.000000;-0.999489;,
  -0.649189;0.585193;-0.485904;,
  -0.020310;0.759486;-0.650207;,
  0.620607;0.588101;-0.518636;,
  0.999697;0.000920;-0.024598;,
  0.649194;-0.585191;0.485901;,
  0.020307;-0.759486;0.650206;,
  -0.620606;-0.588102;0.518637;,
  -0.999697;-0.000919;0.024596;,
  0.268069;-0.598848;-0.754665;,
  -0.986276;0.158913;-0.044786;,
  -0.946032;0.171175;-0.275176;,
  0.018581;0.105380;-0.994258;,
  0.881245;-0.446048;-0.156361;,
  0.588230;-0.535254;-0.606208;,
  0.036949;0.209549;0.977100;,
  0.172341;0.982354;0.072659;,
  0.326438;0.934668;0.140834;,
  0.439956;0.893210;0.092815;,
  -0.986136;0.112213;0.122246;,
  -0.122451;0.991793;0.036764;,
  -0.886504;0.462721;0.000000;,
  0.945098;-0.304233;0.119302;,
  0.831471;-0.478889;0.281641;,
  0.950962;-0.309219;0.007392;,
  0.662562;0.733883;0.149759;,
  0.888286;-0.459291;-0.000000;,
  0.888286;-0.459291;-0.000000;,
  -0.139900;-0.983021;0.118731;,
  0.994541;-0.102013;-0.021943;,
  0.975700;-0.209303;0.064826;,
  -0.039874;-0.267154;0.962829;,
  -0.944006;0.305267;-0.125158;,
  0.939803;-0.319546;0.121082;,
  0.031950;0.000000;0.999489;,
  0.031950;-0.000000;0.999490;,
  0.031949;0.000000;0.999490;,
  0.031949;-0.000000;0.999490;,
  0.031949;-0.000000;0.999490;,
  0.031950;0.000000;0.999489;,
  0.031950;0.000000;0.999489;,
  0.031950;0.000000;0.999490;,
  -0.031949;-0.000000;-0.999490;,
  -0.031955;0.000000;-0.999489;,
  -0.031955;-0.000006;-0.999489;,
  -0.031949;0.000000;-0.999489;,
  -0.031955;0.000006;-0.999489;,
  -0.031949;0.000000;-0.999489;,
  -0.031950;0.000000;-0.999490;,
  -0.638984;0.592601;-0.490432;,
  -0.000000;0.770393;-0.637570;,
  0.638987;0.592599;-0.490430;,
  1.000000;-0.000003;0.000000;,
  0.638988;-0.592600;0.490429;,
  0.000001;-0.770392;0.637570;,
  -0.638986;-0.592600;0.490431;,
  -1.000000;0.000000;0.000000;,
  -0.629219;0.577745;-0.519898;,
  -0.000000;0.743340;-0.668913;,
  0.629222;0.577743;-0.519897;,
  1.000000;-0.000004;0.000002;,
  0.629223;-0.577743;0.519895;,
  0.000001;-0.743340;0.668913;,
  -0.629222;-0.577743;0.519896;,
  -1.000000;-0.000001;0.000001;,
  0.256917;0.966434;0.000000;;
  241;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  3;26,25,27;,
  3;28,26,27;,
  3;29,28,27;,
  3;30,29,30;,
  3;31,30,30;,
  3;32,31,32;,
  3;33,32,32;,
  3;25,33,27;,
  3;152,153,16;,
  3;153,154,16;,
  3;154,155,16;,
  3;155,156,16;,
  3;156,157,16;,
  3;157,158,16;,
  3;158,159,16;,
  3;159,152,16;,
  4;1,0,17,18;,
  4;2,1,18,19;,
  4;3,2,19,20;,
  4;4,3,20,21;,
  4;5,4,21,22;,
  4;6,5,22,23;,
  4;7,6,23,24;,
  4;0,7,24,17;,
  4;18,17,160,161;,
  4;19,18,161,162;,
  4;20,19,162,163;,
  4;21,20,163,164;,
  4;22,21,164,165;,
  4;23,22,165,166;,
  4;24,23,166,167;,
  4;17,24,167,160;,
  4;42,42,43,43;,
  4;151,56,56,151;,
  4;44,45,45,44;,
  4;63,63,64,64;,
  4;47,46,48,49;,
  4;50,51,52,53;,
  4;34,35,35,168;,
  4;169,37,170,170;,
  4;171,36,43,43;,
  4;172,34,168,173;,
  4;38,39,174,174;,
  4;175,41,45,45;,
  4;40,40,40,40;,
  4;176,177,44,44;,
  4;169,178,46,47;,
  4;41,175,48,179;,
  4;180,37,49,48;,
  4;37,169,47,49;,
  4;181,182,51,50;,
  4;34,172,52,51;,
  4;172,183,53,52;,
  4;177,176,184,184;,
  3;171,54,36;,
  3;54,54,36;,
  3;36,54,54;,
  3;37,180,55;,
  3;55,180,55;,
  3;55,180,55;,
  3;39,38,73;,
  3;73,38,73;,
  3;73,38,73;,
  3;183,172,185;,
  3;185,172,185;,
  3;185,172,186;,
  4;176,41,57,57;,
  4;178,169,58,58;,
  4;187,187,59,59;,
  4;34,181,188,188;,
  4;57,57,60,60;,
  4;58,58,61,61;,
  4;59,59,62,62;,
  4;188,188,189,189;,
  4;190,190,63,63;,
  4;61,61,191,191;,
  4;62,62,64,64;,
  4;189,189,192,192;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,65,65,72;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  4;74,75,75,74;,
  4;75,67,67,75;,
  4;67,68,68,67;,
  4;68,76,76,68;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,74,74,79;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,80,80,87;,
  3;193,194,88;,
  3;195,193,88;,
  3;196,195,88;,
  3;197,196,88;,
  3;198,197,88;,
  3;199,198,88;,
  3;200,199,88;,
  3;194,200,88;,
  3;201,202,89;,
  3;202,203,89;,
  3;203,204,89;,
  3;204,205,89;,
  3;205,202,89;,
  3;202,206,89;,
  3;206,207,89;,
  3;207,201,89;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  3;115,114,116;,
  3;117,115,116;,
  3;118,117,116;,
  3;119,118,119;,
  3;120,119,119;,
  3;121,120,121;,
  3;122,121,121;,
  3;114,122,116;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  4;91,90,106,107;,
  4;92,91,107,108;,
  4;93,92,108,109;,
  4;94,93,109,110;,
  4;95,94,110,111;,
  4;96,95,111,112;,
  4;97,96,112,113;,
  4;90,97,113,106;,
  4;107,106,208,209;,
  4;108,107,209,210;,
  4;109,108,210,211;,
  4;110,109,211,212;,
  4;111,110,212,213;,
  4;112,111,213,214;,
  4;113,112,214,215;,
  4;106,113,215,208;,
  4;123,124,99,131;,
  4;124,125,100,99;,
  4;125,126,101,100;,
  4;126,127,102,101;,
  4;127,128,103,102;,
  4;128,129,132,103;,
  4;129,130,133,132;,
  4;130,123,131,133;,
  3;143,142,144;,
  3;145,143,144;,
  3;146,145,144;,
  3;147,146,147;,
  3;148,147,147;,
  3;149,148,149;,
  3;150,149,149;,
  3;142,150,144;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  3;54,54,54;,
  4;124,123,134,135;,
  4;125,124,135,136;,
  4;126,125,136,137;,
  4;127,126,137,138;,
  4;128,127,138,139;,
  4;129,128,139,140;,
  4;130,129,140,141;,
  4;123,130,141,134;,
  4;135,134,216,217;,
  4;136,135,217,218;,
  4;137,136,218,219;,
  4;138,137,219,220;,
  4;139,138,220,221;,
  4;140,139,221,222;,
  4;141,140,222,223;,
  4;134,141,223,216;,
  4;56,151,151,56;,
  4;224,224,151,151;,
  4;151,224,224,151;;
 }
 MeshTextureCoords {
  315;
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;,
  0.500000;1.000000;,
  0.610490;0.954240;,
  0.610490;0.954240;,
  0.500000;1.000000;,
  0.389520;0.954240;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.656250;0.843750;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.625000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;,
  0.500000;1.000000;,
  0.610490;0.954240;,
  0.610490;0.954240;,
  0.500000;1.000000;,
  0.389520;0.954240;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.656250;0.843750;,
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
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;,
  0.500000;1.000000;,
  0.610490;0.954240;,
  0.610490;0.954240;,
  0.500000;1.000000;,
  0.389520;0.954240;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.656250;0.843750;;
 }
}