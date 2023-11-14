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
 101;
 -16.10469;1.02051;1.25921;,
 -16.10469;0.00000;1.78081;,
 -24.58879;0.00000;2.30237;,
 -24.58879;1.73668;1.62803;,
 -16.10469;1.44113;0.00000;,
 -24.58879;2.28052;0.00000;,
 -16.10469;1.02051;-1.25921;,
 -24.58879;1.73668;-1.62803;,
 -16.10469;0.00000;-1.78081;,
 -24.58879;0.00000;-2.30237;,
 -27.69157;-0.01164;0.00000;,
 -29.79239;-0.00699;0.00000;,
 -29.20637;0.00000;2.53897;,
 -29.20637;1.50208;1.88595;,
 -29.20637;2.61990;0.00000;,
 -29.20637;1.50208;-1.88595;,
 -29.20637;0.00000;-2.53897;,
 -24.58879;3.17279;3.40882;,
 -24.58879;0.00000;4.82080;,
 -16.10469;0.00000;5.34238;,
 -16.10469;3.05143;3.77764;,
 -24.58879;4.31146;0.00000;,
 -16.10469;4.31330;0.00000;,
 -24.58879;3.17279;-3.40882;,
 -16.10469;3.05143;-3.77764;,
 -24.58879;0.00000;-4.82080;,
 -16.10469;0.00000;-5.34238;,
 -9.46546;3.39325;3.41630;,
 -9.46546;0.00000;4.83136;,
 -3.91358;0.00000;4.00176;,
 -3.91358;3.54438;2.82967;,
 -9.46546;4.53438;0.00000;,
 -3.91358;4.48956;0.00000;,
 -9.46546;3.39325;-3.41630;,
 -3.91358;3.54438;-2.82967;,
 -9.46546;0.00000;-4.83136;,
 -3.91358;0.00000;-4.00176;,
 0.00000;0.00000;4.19438;,
 0.00000;3.81825;2.96588;,
 0.00000;4.80896;0.00000;,
 0.00000;3.81825;-2.96588;,
 0.00000;0.00000;-4.19438;,
 0.00000;0.00000;0.00000;,
 -3.91358;0.00000;1.91122;,
 -3.91358;1.38531;1.35144;,
 -3.91358;2.80368;0.00000;,
 -3.91358;1.38531;-1.35144;,
 -3.91358;0.00000;-1.91122;,
 -9.46546;0.00000;1.94105;,
 -9.46546;1.19135;1.37253;,
 -9.46546;2.20357;0.00000;,
 -9.46546;1.19135;-1.37253;,
 -9.46546;0.08451;-1.94105;,
 -27.69157;0.00000;4.23758;,
 -27.69157;0.00000;-4.23758;,
 -16.10469;-1.02047;1.25921;,
 -24.58879;-1.73668;1.62803;,
 -16.10469;-1.44113;0.00000;,
 -24.58879;-2.28051;0.00000;,
 -16.10469;-1.02047;-1.25921;,
 -24.58879;-1.73668;-1.62803;,
 -29.20637;-1.52957;1.89108;,
 -29.20637;-2.61389;0.00000;,
 -29.20637;-1.52957;-1.89108;,
 -24.58879;-3.17279;3.40882;,
 -16.10469;-3.05143;3.77764;,
 -24.58879;-4.31144;0.00000;,
 -16.10469;-4.31326;0.00000;,
 -24.58879;-3.17279;-3.40882;,
 -16.10469;-3.05143;-3.77764;,
 -9.46546;-3.39323;3.41630;,
 -3.91358;-3.54434;2.82967;,
 -9.46546;-4.53438;0.00000;,
 -3.91358;-4.48957;0.00000;,
 -9.46546;-3.39323;-3.41630;,
 -3.91358;-3.54434;-2.82967;,
 0.00000;-3.81824;2.96588;,
 0.00000;-4.80896;-0.00000;,
 0.00000;-3.81824;-2.96588;,
 -3.91358;-1.38533;1.35144;,
 -3.91358;-2.80366;0.00000;,
 -3.91358;-1.38533;-1.35144;,
 -9.46546;-1.19133;1.37253;,
 -9.46546;-2.20354;0.00000;,
 -9.46546;-1.19133;-1.37253;,
 -9.46546;-0.08447;-1.94105;,
 1.94377;2.77087;2.15230;,
 1.94377;0.00000;3.04383;,
 3.70605;0.00000;0.00000;,
 1.94377;3.48982;0.00000;,
 1.94377;2.77087;-2.15230;,
 1.94377;0.00000;-3.04383;,
 1.94377;-2.77087;-2.15230;,
 1.94377;-3.48981;-0.00000;,
 1.94377;-2.77087;2.15230;,
 -27.69157;2.50701;3.14773;,
 -27.69157;4.37270;0.00000;,
 -27.69157;2.50701;-3.14773;,
 -27.69157;-2.55284;-3.15626;,
 -27.69157;-4.36264;0.00000;,
 -27.69157;-2.55284;3.15626;;
 
 140;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;8,6,7,9;,
 3;3,2,10;,
 3;5,3,10;,
 3;7,5,10;,
 3;9,7,10;,
 3;11,12,13;,
 3;11,13,14;,
 3;11,14,15;,
 3;11,15,16;,
 4;17,18,19,20;,
 4;21,17,20,22;,
 4;23,21,22,24;,
 4;25,23,24,26;,
 4;27,28,29,30;,
 4;31,27,30,32;,
 4;33,31,32,34;,
 4;35,33,34,36;,
 4;30,29,37,38;,
 4;32,30,38,39;,
 4;34,32,39,40;,
 4;36,34,40,41;,
 3;42,43,44;,
 3;42,44,45;,
 3;42,45,46;,
 3;42,46,47;,
 4;44,43,48,49;,
 4;45,44,49,50;,
 4;46,45,50,51;,
 4;47,46,51,52;,
 4;2,18,53,10;,
 4;52,35,36,47;,
 4;28,48,43,29;,
 4;29,43,42,37;,
 4;2,1,19,18;,
 4;9,25,26,8;,
 4;47,36,41,42;,
 4;9,10,54,25;,
 4;19,1,48,28;,
 4;49,48,1,0;,
 4;50,49,0,4;,
 4;51,50,4,6;,
 4;52,51,6,8;,
 4;8,26,35,52;,
 4;26,24,33,35;,
 4;24,22,31,33;,
 4;22,20,27,31;,
 4;20,19,28,27;,
 4;55,56,2,1;,
 4;57,58,56,55;,
 4;59,60,58,57;,
 4;8,9,60,59;,
 3;56,10,2;,
 3;58,10,56;,
 3;60,10,58;,
 3;9,10,60;,
 3;11,61,12;,
 3;11,62,61;,
 3;11,63,62;,
 3;11,16,63;,
 4;64,65,19,18;,
 4;66,67,65,64;,
 4;68,69,67,66;,
 4;25,26,69,68;,
 4;70,71,29,28;,
 4;72,73,71,70;,
 4;74,75,73,72;,
 4;35,36,75,74;,
 4;71,76,37,29;,
 4;73,77,76,71;,
 4;75,78,77,73;,
 4;36,41,78,75;,
 3;42,79,43;,
 3;42,80,79;,
 3;42,81,80;,
 3;42,47,81;,
 4;79,82,48,43;,
 4;80,83,82,79;,
 4;81,84,83,80;,
 4;47,85,84,81;,
 4;2,10,53,18;,
 4;85,47,36,35;,
 4;28,29,43,48;,
 4;29,37,42,43;,
 4;2,18,19,1;,
 4;9,8,26,25;,
 4;47,42,41,36;,
 4;9,25,54,10;,
 4;19,28,48,1;,
 4;82,55,1,48;,
 4;83,57,55,82;,
 4;84,59,57,83;,
 4;85,8,59,84;,
 4;8,85,35,26;,
 4;26,35,74,69;,
 4;69,74,72,67;,
 4;67,72,70,65;,
 4;65,70,28,19;,
 3;86,87,88;,
 3;89,86,88;,
 3;90,89,88;,
 3;91,90,88;,
 3;92,91,88;,
 3;93,92,88;,
 3;94,93,88;,
 3;87,94,88;,
 4;38,37,87,86;,
 4;37,42,88,87;,
 4;39,38,86,89;,
 4;40,39,89,90;,
 4;41,40,90,91;,
 4;42,41,91,88;,
 4;78,41,91,92;,
 4;41,42,88,91;,
 4;77,78,92,93;,
 4;76,77,93,94;,
 4;37,76,94,87;,
 4;42,37,87,88;,
 4;95,53,18,17;,
 4;96,95,17,21;,
 4;97,96,21,23;,
 4;54,97,23,25;,
 4;98,54,25,68;,
 4;99,98,68,66;,
 4;100,99,66,64;,
 4;53,100,64,18;,
 4;10,53,12,11;,
 4;53,95,13,12;,
 4;95,96,14,13;,
 4;96,97,15,14;,
 4;97,54,16,15;,
 4;54,10,11,16;,
 4;100,53,12,61;,
 4;53,10,11,12;,
 4;99,100,61,62;,
 4;98,99,62,63;,
 4;10,54,16,11;,
 4;54,98,63,16;;
 
 MeshMaterialList {
  1;
  140;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\tyuuni\\tyuuni_suit.png";
   }
  }
 }
 MeshNormals {
  131;
  -0.021511;0.000004;-0.999769;,
  -0.018965;-0.720186;-0.693522;,
  -0.017334;-0.999850;0.000000;,
  -0.018105;-0.722764;0.690857;,
  -0.019864;0.000003;0.999803;,
  0.288823;0.000110;-0.957383;,
  0.285753;-0.702492;-0.651805;,
  0.268851;-0.963182;-0.000000;,
  0.285753;-0.702492;0.651805;,
  0.288823;0.000110;0.957383;,
  0.278892;-0.952194;-0.124686;,
  -0.114642;0.001099;0.993406;,
  -0.084617;0.724402;0.684165;,
  -0.055524;0.998457;0.000000;,
  -0.084617;0.724402;-0.684165;,
  -0.114642;0.001099;-0.993406;,
  0.002845;-0.000000;0.999996;,
  -0.007246;0.747662;0.664040;,
  -0.016753;0.999860;0.000000;,
  -0.007246;0.747662;-0.664040;,
  0.002845;-0.000000;-0.999996;,
  0.033770;-0.000001;0.999430;,
  -0.001671;0.712420;0.701751;,
  -0.036677;0.999327;0.000000;,
  -0.001671;0.712420;-0.701751;,
  0.033770;-0.000001;-0.999430;,
  -0.497010;0.000001;-0.867745;,
  -0.226954;-0.000001;-0.973906;,
  -0.210655;-0.554122;-0.805340;,
  -0.203092;-0.707281;-0.677132;,
  -0.211375;-0.557137;0.803068;,
  -0.229500;-0.000003;0.973309;,
  0.088680;-0.000001;0.996060;,
  0.014541;0.000002;-0.999894;,
  0.036001;-0.645572;-0.762850;,
  0.056422;-0.823715;-0.564189;,
  0.035847;-0.651167;0.758088;,
  0.013013;-0.436166;0.899772;,
  0.088680;-0.000001;-0.996060;,
  0.038400;0.732745;-0.679419;,
  -0.012609;0.999920;0.000000;,
  0.038400;0.732745;0.679419;,
  -0.018965;0.720186;-0.693522;,
  -0.017335;0.999850;0.000000;,
  -0.018109;0.722762;0.690859;,
  0.284034;0.702999;-0.652010;,
  0.266435;0.963853;0.000000;,
  0.284034;0.702999;0.652010;,
  -0.082319;-0.724955;0.683859;,
  -0.052713;-0.998610;0.000000;,
  -0.082319;-0.724955;-0.683859;,
  -0.007246;-0.747664;0.664038;,
  -0.016753;-0.999860;0.000000;,
  -0.007246;-0.747664;-0.664038;,
  -0.001672;-0.712417;0.701754;,
  -0.036678;-0.999327;0.000000;,
  -0.001672;-0.712417;-0.701754;,
  -0.210656;0.554126;-0.805337;,
  -0.203092;0.707290;-0.677122;,
  -0.211375;0.557140;0.803066;,
  0.036003;0.645575;-0.762848;,
  0.056424;0.823716;-0.564189;,
  0.035844;0.651167;0.758088;,
  0.013007;0.436165;0.899773;,
  0.038400;-0.732744;-0.679420;,
  -0.012608;-0.999920;0.000000;,
  0.038400;-0.732744;0.679420;,
  0.240285;-0.000001;0.970702;,
  0.263572;0.676053;0.688100;,
  0.257263;0.966342;0.000000;,
  0.263572;0.676053;-0.688100;,
  0.240285;-0.000001;-0.970702;,
  0.263570;-0.676052;-0.688102;,
  0.257261;-0.966342;-0.000000;,
  0.263570;-0.676052;0.688102;,
  0.712724;-0.000000;0.701445;,
  0.754240;0.454651;0.473724;,
  1.000000;-0.000000;-0.000000;,
  0.753276;0.657704;0.000000;,
  0.754240;0.454651;-0.473724;,
  0.712724;-0.000000;-0.701445;,
  0.754240;-0.454651;-0.473724;,
  0.753276;-0.657704;-0.000000;,
  0.754240;-0.454651;0.473724;,
  -0.000895;-0.999997;0.002189;,
  -0.468728;0.606948;0.641801;,
  -0.470771;0.882255;0.000000;,
  -0.468728;0.606948;-0.641801;,
  -0.000895;-0.999997;-0.002189;,
  -0.468932;-0.607998;-0.640657;,
  -0.467860;-0.883803;0.000000;,
  -0.468932;-0.607998;0.640657;,
  -1.000000;0.000154;-0.000000;,
  -0.890149;0.002338;0.455663;,
  -0.880569;0.314671;0.354375;,
  -0.896794;0.442449;0.000000;,
  -0.880569;0.314671;-0.354375;,
  -0.890149;0.002338;-0.455663;,
  -0.881990;-0.313807;0.351594;,
  -0.895972;-0.444111;0.000000;,
  -0.881990;-0.313807;-0.351594;,
  0.595897;0.000198;0.803061;,
  -0.464310;-0.226456;0.856233;,
  -0.203092;-0.707281;0.677132;,
  0.056422;-0.823715;0.564189;,
  0.000428;-1.000000;0.000687;,
  -0.001540;-0.999892;0.014615;,
  -0.004898;-0.999961;0.007308;,
  0.000000;-1.000000;-0.000000;,
  0.000428;-1.000000;-0.000687;,
  0.003357;-0.999968;0.007307;,
  0.278315;0.952355;-0.124746;,
  -0.094570;0.985831;0.138542;,
  -0.203092;0.707290;0.677122;,
  0.056424;0.823716;0.564189;,
  -0.000428;1.000000;-0.000687;,
  0.000895;0.999997;-0.002189;,
  -0.001539;0.999892;0.014608;,
  -0.004895;0.999961;0.007305;,
  0.000000;1.000000;0.000000;,
  -0.000428;1.000000;0.000687;,
  0.003356;0.999968;0.007304;,
  0.000895;0.999997;0.002189;,
  -0.495911;0.002980;0.868368;,
  -0.495911;0.002980;-0.868368;,
  -0.002647;-0.999992;0.003005;,
  -0.002647;-0.999997;0.000000;,
  -0.002647;-0.999992;-0.003005;,
  0.002647;0.999997;0.000000;,
  0.002647;0.999992;-0.003005;,
  0.002647;0.999992;0.003005;;
  140;
  4;1,0,5,6;,
  4;2,1,6,7;,
  4;3,2,7,8;,
  4;4,3,8,9;,
  3;6,5,10;,
  3;7,6,10;,
  3;8,7,10;,
  3;9,8,101;,
  3;92,93,94;,
  3;92,94,95;,
  3;92,95,96;,
  3;92,96,97;,
  4;12,11,16,17;,
  4;13,12,17,18;,
  4;14,13,18,19;,
  4;15,14,19,20;,
  4;41,32,21,22;,
  4;40,41,22,23;,
  4;39,40,23,24;,
  4;38,39,24,25;,
  4;22,21,67,68;,
  4;23,22,68,69;,
  4;24,23,69,70;,
  4;25,24,70,71;,
  3;26,27,28;,
  3;26,28,29;,
  3;102,103,30;,
  3;102,30,31;,
  4;28,27,33,34;,
  4;29,28,34,35;,
  4;30,103,104,36;,
  4;31,30,36,37;,
  4;105,105,84,10;,
  4;106,106,107,107;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;105,108,108,105;,
  4;109,109,110,110;,
  4;107,107,108,108;,
  4;109,10,88,109;,
  4;108,108,108,108;,
  4;34,33,0,1;,
  4;35,34,1,2;,
  4;36,104,2,3;,
  4;37,36,3,4;,
  4;110,110,106,106;,
  4;20,19,39,38;,
  4;19,18,40,39;,
  4;18,17,41,40;,
  4;17,16,32,41;,
  4;42,45,5,0;,
  4;43,46,45,42;,
  4;44,47,46,43;,
  4;4,9,47,44;,
  3;45,111,5;,
  3;46,111,45;,
  3;47,111,46;,
  3;9,101,47;,
  3;92,98,93;,
  3;92,99,98;,
  3;92,100,99;,
  3;92,97,100;,
  4;48,51,16,11;,
  4;49,52,51,48;,
  4;50,53,52,49;,
  4;15,20,53,50;,
  4;66,54,21,32;,
  4;65,55,54,66;,
  4;64,56,55,65;,
  4;38,25,56,64;,
  4;54,74,67,21;,
  4;55,73,74,54;,
  4;56,72,73,55;,
  4;25,71,72,56;,
  3;26,57,27;,
  3;26,58,57;,
  3;112,59,113;,
  3;102,31,59;,
  4;57,60,33,27;,
  4;58,61,60,57;,
  4;59,62,114,113;,
  4;31,63,62,59;,
  4;115,111,116,115;,
  4;117,118,118,117;,
  4;119,119,119,119;,
  4;119,119,112,119;,
  4;115,115,119,119;,
  4;120,121,121,120;,
  4;118,112,119,118;,
  4;120,120,122,111;,
  4;119,119,119,119;,
  4;60,42,0,33;,
  4;61,43,42,60;,
  4;62,44,43,114;,
  4;63,4,44,62;,
  4;121,117,117,121;,
  4;20,38,64,53;,
  4;53,64,65,52;,
  4;52,65,66,51;,
  4;51,66,32,16;,
  3;76,75,77;,
  3;78,76,77;,
  3;79,78,77;,
  3;80,79,77;,
  3;81,80,77;,
  3;82,81,77;,
  3;83,82,77;,
  3;75,83,77;,
  4;68,67,75,76;,
  4;108,108,108,108;,
  4;69,68,76,78;,
  4;70,69,78,79;,
  4;71,70,79,80;,
  4;108,108,108,108;,
  4;72,71,80,81;,
  4;119,112,119,119;,
  4;73,72,81,82;,
  4;74,73,82,83;,
  4;67,74,83,75;,
  4;112,119,119,119;,
  4;85,123,11,12;,
  4;86,85,12,13;,
  4;87,86,13,14;,
  4;124,87,14,15;,
  4;89,124,15,50;,
  4;90,89,50,49;,
  4;91,90,49,48;,
  4;123,91,48,11;,
  4;10,84,125,126;,
  4;123,85,94,93;,
  4;85,86,95,94;,
  4;86,87,96,95;,
  4;87,124,97,96;,
  4;88,10,126,127;,
  4;91,123,93,98;,
  4;116,111,128,129;,
  4;90,91,98,99;,
  4;89,90,99,100;,
  4;111,122,130,128;,
  4;124,89,100,97;;
 }
 MeshTextureCoords {
  101;
  0.565330;0.473860;,
  0.565330;0.500000;,
  0.786140;0.500000;,
  0.786140;0.455520;,
  0.565330;0.463090;,
  0.786140;0.441590;,
  0.565330;0.473860;,
  0.786140;0.455520;,
  0.565330;0.500000;,
  0.786140;0.500000;,
  0.873930;0.500300;,
  0.918370;0.500180;,
  0.905970;0.500000;,
  0.905970;0.461530;,
  0.905970;0.432900;,
  0.905970;0.461530;,
  0.905970;0.500000;,
  0.786140;0.418740;,
  0.786140;0.500000;,
  0.565330;0.500000;,
  0.565330;0.421840;,
  0.786140;0.389570;,
  0.565330;0.389520;,
  0.786140;0.418740;,
  0.565330;0.421840;,
  0.786140;0.500000;,
  0.565330;0.500000;,
  0.397830;0.413090;,
  0.397830;0.500000;,
  0.263000;0.500000;,
  0.263000;0.409220;,
  0.397830;0.383860;,
  0.263000;0.385010;,
  0.397830;0.413090;,
  0.263000;0.409220;,
  0.397830;0.500000;,
  0.263000;0.500000;,
  0.160020;0.500000;,
  0.160020;0.402200;,
  0.160020;0.376830;,
  0.160020;0.402200;,
  0.160020;0.500000;,
  0.160020;0.500000;,
  0.263000;0.500000;,
  0.263000;0.464520;,
  0.263000;0.428190;,
  0.263000;0.464520;,
  0.263000;0.500000;,
  0.397830;0.500000;,
  0.397830;0.469490;,
  0.397830;0.443560;,
  0.397830;0.469490;,
  0.397830;0.497840;,
  0.873930;0.500000;,
  0.873930;0.500000;,
  0.565330;0.526140;,
  0.786140;0.544480;,
  0.565330;0.536910;,
  0.786140;0.558410;,
  0.565330;0.526140;,
  0.786140;0.544480;,
  0.905970;0.539180;,
  0.905970;0.566950;,
  0.905970;0.539180;,
  0.786140;0.581260;,
  0.565330;0.578160;,
  0.786140;0.610430;,
  0.565330;0.610480;,
  0.786140;0.581260;,
  0.565330;0.578160;,
  0.397830;0.586910;,
  0.263000;0.590780;,
  0.397830;0.616140;,
  0.263000;0.614990;,
  0.397830;0.586910;,
  0.263000;0.590780;,
  0.160020;0.597800;,
  0.160020;0.623170;,
  0.160020;0.597800;,
  0.263000;0.535480;,
  0.263000;0.571810;,
  0.263000;0.535480;,
  0.397830;0.530510;,
  0.397830;0.556440;,
  0.397830;0.530510;,
  0.397830;0.502160;,
  0.118910;0.429030;,
  0.118910;0.500000;,
  0.081630;0.500000;,
  0.118910;0.410620;,
  0.118910;0.429030;,
  0.118910;0.500000;,
  0.118910;0.570970;,
  0.118910;0.589390;,
  0.118910;0.570970;,
  0.873930;0.435790;,
  0.873930;0.388000;,
  0.873930;0.435790;,
  0.873930;0.565390;,
  0.873930;0.611740;,
  0.873930;0.565390;;
 }
}
