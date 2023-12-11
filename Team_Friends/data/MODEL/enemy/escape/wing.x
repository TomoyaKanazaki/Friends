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
 60;
 -2.47785;2.70720;-32.04584;,
 -1.72431;2.65959;-30.38433;,
 5.77878;-1.95566;-30.34622;,
 6.17330;-2.61423;-32.00188;,
 -5.96978;0.97382;-6.01717;,
 -3.64486;0.97382;5.86900;,
 5.84395;0.97382;5.91718;,
 3.92794;0.97382;-5.96690;,
 -5.83387;-1.92711;30.24659;,
 -6.39180;-2.45702;31.90143;,
 2.52342;0.08893;31.94670;,
 1.78537;0.24872;30.28527;,
 -3.64486;-0.99723;5.86900;,
 -5.96978;-0.99723;-6.01717;,
 3.92794;-0.99723;-5.96690;,
 5.84395;-0.99723;5.91718;,
 4.60350;-0.01171;-6.28802;,
 6.51623;-0.01171;6.24514;,
 -4.32041;-0.01171;6.19011;,
 -6.64205;-0.01171;-6.34513;,
 -5.51567;2.49292;-12.64059;,
 -5.65972;2.21472;-17.97021;,
 4.05057;-3.74673;-21.59116;,
 -0.64237;-0.50470;-12.61584;,
 4.61671;-2.82632;-21.58830;,
 0.12885;0.74912;-12.61191;,
 0.32076;-0.23088;-13.29765;,
 4.91262;-3.63962;-22.56479;,
 -5.09360;3.13513;-17.96734;,
 -4.74444;3.74673;-12.63667;,
 -5.94570;3.02802;-18.94967;,
 -5.70058;3.47291;-13.32824;,
 -2.70881;0.39505;21.97428;,
 -4.89636;-1.23046;27.76490;,
 2.82229;0.97405;28.00672;,
 5.24175;2.66650;22.69012;,
 3.57596;0.76186;29.54339;,
 6.03181;2.33202;23.93569;,
 5.53845;1.62745;22.69163;,
 3.04918;0.17954;28.00788;,
 -4.66946;-2.02497;27.76606;,
 -2.41209;-0.64399;21.97580;,
 -3.21477;-0.30952;23.21326;,
 -5.43870;-1.81278;29.29499;,
 -2.10012;2.04865;-30.38623;,
 5.40298;-2.56661;-30.34814;,
 -5.63689;-2.61682;30.24758;,
 1.98233;-0.44098;30.28629;,
 1.05761;1.09746;17.33999;,
 5.36556;2.32769;17.36186;,
 6.21084;1.80502;18.31641;,
 5.76977;0.91225;17.36391;,
 1.46181;-0.31797;17.34203;,
 0.60687;0.20469;18.28795;,
 5.13250;-2.80263;-28.59673;,
 5.92116;-2.81930;-30.11447;,
 -2.81203;2.08186;-27.90302;,
 -3.17141;2.77136;-29.42659;,
 -2.39818;2.75470;-27.90092;,
 5.54635;-2.12980;-28.59463;;
 
 58;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,7,6,17;,
 4;18,5,4,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;25,24,28,29;,
 4;29,28,30,31;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;38,39,40,41;,
 4;33,32,42,43;,
 4;21,20,31,30;,
 4;44,0,3,45;,
 4;23,22,27,26;,
 4;14,16,17,15;,
 4;39,38,37,36;,
 4;9,46,47,10;,
 4;41,40,43,42;,
 4;12,18,19,13;,
 4;13,20,23,14;,
 4;14,23,26,16;,
 4;25,7,16,26;,
 4;7,25,29,4;,
 4;4,29,31,19;,
 4;20,13,19,31;,
 4;48,32,35,49;,
 4;49,35,37,50;,
 4;38,51,50,37;,
 4;51,38,41,52;,
 4;52,41,42,53;,
 4;32,48,53,42;,
 4;22,54,55,27;,
 4;21,56,54,22;,
 4;56,21,30,57;,
 4;28,58,57,30;,
 4;24,59,58,28;,
 4;59,24,27,55;,
 4;5,48,49,6;,
 4;6,49,50,17;,
 4;51,15,17,50;,
 4;15,51,52,12;,
 4;12,52,53,18;,
 4;48,5,18,53;,
 4;54,45,3,55;,
 4;56,44,45,54;,
 4;0,44,56,57;,
 4;58,1,0,57;,
 4;59,2,1,58;,
 4;3,2,59,55;,
 4;40,46,9,43;,
 4;39,47,46,40;,
 4;10,47,39,36;,
 4;34,11,10,36;,
 4;33,8,11,34;,
 4;9,8,33,43;;
 
 MeshMaterialList {
  1;
  58;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "box_UV_.jpg";
   }
  }
 }
 MeshNormals {
  91;
  -0.524693;-0.841582;-0.128210;,
  0.286806;-0.937164;-0.198660;,
  -0.356486;0.919793;0.164006;,
  0.503628;0.857679;-0.103655;,
  -0.464814;0.879332;0.103556;,
  0.398767;0.913983;-0.074966;,
  -0.345516;-0.926485;0.149148;,
  0.498248;-0.866716;0.023498;,
  -0.561947;-0.806848;-0.182240;,
  -0.469212;-0.864090;-0.182178;,
  0.730011;0.682925;0.026411;,
  0.381650;0.923781;-0.031180;,
  -0.271563;0.943506;0.189870;,
  -0.245105;0.949889;0.193996;,
  0.397993;-0.915901;0.052215;,
  0.274928;-0.960446;0.044247;,
  -0.751770;0.632751;0.185653;,
  0.300871;0.946733;-0.114772;,
  0.820017;0.571402;-0.032742;,
  0.778209;0.557519;-0.289073;,
  0.775959;0.623021;-0.098652;,
  -0.230736;0.950934;0.206118;,
  -0.269452;0.939817;0.210092;,
  -0.772812;0.594605;0.221823;,
  -0.705975;-0.693873;-0.141911;,
  -0.117600;-0.973646;-0.195405;,
  0.715080;-0.642471;0.275484;,
  0.823424;-0.255489;0.506654;,
  -0.011871;0.998052;0.061255;,
  -0.427780;0.901377;0.067256;,
  -0.277497;0.959498;0.048576;,
  -0.034607;0.996404;0.077339;,
  0.224756;0.968996;0.102621;,
  0.524711;-0.849370;0.056998;,
  0.274866;-0.961421;0.010828;,
  -0.842535;-0.174255;-0.509676;,
  0.871158;-0.240449;0.428098;,
  -0.417105;-0.904472;-0.089184;,
  -0.738401;-0.670677;-0.070404;,
  -0.065375;0.995996;-0.060975;,
  0.241872;0.969948;-0.026455;,
  0.938708;-0.036186;0.342810;,
  -0.401828;0.914194;0.052768;,
  0.233063;0.969771;-0.072295;,
  0.628657;0.775254;-0.061417;,
  0.542586;-0.831089;0.122029;,
  -0.057248;-0.980306;0.189006;,
  -0.759677;-0.166212;-0.628701;,
  -0.269630;-0.950579;-0.153949;,
  -0.405058;-0.899654;-0.162944;,
  -0.619006;-0.765584;-0.175252;,
  -0.699569;-0.691541;-0.179930;,
  0.291900;0.954728;0.057346;,
  0.814744;0.559122;0.153539;,
  -0.894432;-0.220257;-0.389203;,
  0.277086;-0.952763;-0.124361;,
  0.473576;-0.880485;-0.021719;,
  -0.144033;0.963835;0.224226;,
  -0.211081;0.957500;0.196567;,
  -0.276920;0.946110;0.167905;,
  0.529341;0.838884;-0.126774;,
  0.527473;0.849502;0.010843;,
  -0.917677;-0.132022;-0.374752;,
  -0.846224;-0.209217;-0.490034;,
  -0.917768;-0.367331;-0.150898;,
  -0.894418;-0.440848;-0.075300;,
  -0.582060;-0.790599;-0.190158;,
  -0.442764;-0.876273;-0.190015;,
  0.608784;-0.594179;0.525675;,
  0.653896;-0.722247;-0.225342;,
  0.827873;-0.560753;-0.013523;,
  0.733195;-0.672834;0.098584;,
  0.644421;-0.760243;0.082173;,
  0.267305;-0.939816;0.212824;,
  0.453662;-0.879768;0.142126;,
  -0.837520;-0.139259;-0.528363;,
  -0.863867;-0.305836;-0.400246;,
  -0.699570;-0.681235;0.215686;,
  -0.833240;-0.544557;-0.095760;,
  0.716243;0.540187;-0.441808;,
  0.809573;-0.578527;0.099487;,
  -0.780768;0.091654;-0.618062;,
  -0.687647;-0.412933;-0.597183;,
  -0.164707;-0.976147;-0.141454;,
  0.030229;0.999270;-0.023365;,
  0.969772;0.193066;0.149221;,
  -0.560568;-0.783150;0.269145;,
  -0.723889;0.627508;0.286737;,
  -0.884410;-0.249382;-0.394497;,
  -0.880617;-0.260718;-0.395651;,
  -0.876698;-0.272016;-0.396748;;
  58;
  4;17,11,10,18;,
  4;2,4,5,3;,
  4;12,22,21,13;,
  4;6,0,1,7;,
  4;19,3,5,20;,
  4;23,4,2,16;,
  4;24,38,37,25;,
  4;41,27,26,36;,
  4;60,61,40,28;,
  4;28,40,39,29;,
  4;30,59,58,31;,
  4;31,58,57,32;,
  4;33,56,55,34;,
  4;62,63,35,54;,
  4;38,24,64,65;,
  4;8,66,67,9;,
  4;68,68,36,26;,
  4;1,69,70,7;,
  4;56,33,71,72;,
  4;73,15,14,74;,
  4;75,76,54,35;,
  4;6,77,78,0;,
  4;0,24,25,1;,
  4;1,25,26,69;,
  4;60,3,19,79;,
  4;3,60,28,2;,
  4;2,28,29,16;,
  4;24,0,78,64;,
  4;42,30,31,43;,
  4;43,31,32,44;,
  4;33,45,80,71;,
  4;45,33,34,46;,
  4;81,75,35,47;,
  4;63,82,47,35;,
  4;37,49,48,83;,
  4;38,50,49,37;,
  4;50,38,65,51;,
  4;40,52,84,39;,
  4;61,53,52,40;,
  4;53,41,36,85;,
  4;4,42,43,5;,
  4;5,43,44,20;,
  4;45,7,70,80;,
  4;7,45,46,6;,
  4;6,46,86,77;,
  4;42,4,23,87;,
  4;49,9,67,48;,
  4;50,8,9,49;,
  4;66,8,50,51;,
  4;52,11,17,84;,
  4;53,10,11,52;,
  4;18,10,53,85;,
  4;76,88,89,54;,
  4;56,14,15,55;,
  4;74,14,56,72;,
  4;58,13,21,57;,
  4;59,12,13,58;,
  4;89,90,62,54;;
 }
 MeshTextureCoords {
  60;
  0.595382;0.065207;,
  0.608145;0.067047;,
  0.671402;0.245363;,
  0.668319;0.270808;,
  0.666661;0.132179;,
  0.732179;0.132179;,
  0.812178;0.132179;,
  0.750107;0.132179;,
  0.808033;0.244260;,
  0.809739;0.264734;,
  0.884902;0.166368;,
  0.872270;0.160194;,
  0.732179;0.208333;,
  0.666661;0.208333;,
  0.750107;0.208333;,
  0.812178;0.208333;,
  0.754548;0.170256;,
  0.819101;0.170256;,
  0.727739;0.170256;,
  0.659738;0.170256;,
  0.644868;0.073486;,
  0.623048;0.084235;,
  0.690721;0.314564;,
  0.685954;0.189303;,
  0.695494;0.279003;,
  0.692457;0.140861;,
  0.691419;0.178724;,
  0.694207;0.310425;,
  0.627820;0.048674;,
  0.651370;0.025043;,
  0.616855;0.052812;,
  0.640654;0.035623;,
  0.802330;0.154540;,
  0.806322;0.217344;,
  0.872180;0.132170;,
  0.871972;0.066780;,
  0.884462;0.140368;,
  0.883434;0.079703;,
  0.874474;0.106925;,
  0.874093;0.162867;,
  0.808235;0.248041;,
  0.804832;0.194685;,
  0.802866;0.181762;,
  0.807677;0.239843;,
  0.604976;0.090651;,
  0.668234;0.268968;,
  0.809694;0.270908;,
  0.873930;0.186842;,
  0.816090;0.127402;,
  0.852410;0.079870;,
  0.863211;0.100064;,
  0.855817;0.134558;,
  0.819498;0.182089;,
  0.815964;0.161895;,
  0.672732;0.278087;,
  0.673496;0.278731;,
  0.608591;0.089368;,
  0.599676;0.062728;,
  0.612080;0.063372;,
  0.676221;0.252091;;
 }
}
