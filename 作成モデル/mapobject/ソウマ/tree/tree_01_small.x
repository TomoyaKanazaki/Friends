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
 263;
 0.22028;42.50294;2.82113;,
 -0.01053;47.64688;-0.00267;,
 -0.06634;47.64688;-0.01454;,
 -1.42333;41.14042;2.45945;,
 -0.11250;47.64688;-0.04808;,
 -1.86787;41.72927;1.27475;,
 -0.14103;47.64688;-0.09749;,
 -2.47691;41.15418;0.76265;,
 -0.14699;47.64688;-0.15423;,
 -3.12046;40.83874;-0.52266;,
 -0.12936;47.64688;-0.20849;,
 -2.62912;41.11892;-1.86510;,
 -0.09118;47.64688;-0.25090;,
 -1.60888;42.02980;-2.15281;,
 -0.03906;47.64688;-0.27410;,
 -0.66137;41.01141;-2.94563;,
 0.01800;47.64688;-0.27410;,
 0.56423;41.55569;-2.97839;,
 0.07012;47.64688;-0.25090;,
 1.95232;41.49777;-2.72383;,
 0.10830;47.64688;-0.20849;,
 2.76499;40.96181;-1.58118;,
 0.12593;47.64688;-0.15423;,
 3.18324;40.83912;-0.19366;,
 0.11997;47.64688;-0.09749;,
 2.82854;39.81330;0.52176;,
 0.09144;47.64688;-0.04808;,
 2.38350;41.12897;1.64262;,
 0.12593;47.64688;-0.15423;,
 0.10830;47.64688;-0.20849;,
 0.11997;47.64688;-0.09749;,
 0.09144;47.64688;-0.04808;,
 0.07012;47.64688;-0.25090;,
 0.04528;47.64688;-0.01454;,
 0.01800;47.64688;-0.27410;,
 -0.01053;47.64688;-0.00267;,
 -0.03906;47.64688;-0.27410;,
 -0.06634;47.64688;-0.01454;,
 -0.09118;47.64688;-0.25090;,
 -0.11250;47.64688;-0.04808;,
 -0.12936;47.64688;-0.20849;,
 -0.14103;47.64688;-0.09749;,
 -0.14699;47.64688;-0.15423;,
 0.04528;47.64688;-0.01454;,
 1.17835;42.23359;2.58701;,
 -0.01053;47.64688;-0.00267;,
 0.22028;42.50294;2.82113;,
 6.35555;10.53544;-0.80649;,
 6.13246;10.73722;1.84937;,
 5.57436;10.50380;-3.36567;,
 4.69214;10.69198;4.21281;,
 3.54600;10.59594;-5.38019;,
 2.49024;10.20281;5.81017;,
 1.36435;10.30053;-6.55690;,
 -0.09336;11.26742;6.48996;,
 -1.22403;10.58011;-6.51533;,
 -2.67484;10.03969;5.87623;,
 -3.85588;10.69625;-5.29461;,
 -4.71181;10.77407;4.05598;,
 -5.55902;10.35688;-3.34439;,
 -6.21889;10.61816;1.64884;,
 -6.38013;10.48433;-0.70695;,
 1.99882;17.29344;4.60835;,
 3.61049;15.84644;7.49040;,
 0.46755;18.04591;8.72278;,
 0.00986;16.01357;5.54879;,
 1.49317;22.91276;3.21331;,
 2.69329;22.83942;6.58568;,
 -0.19636;21.06625;6.98526;,
 -0.18690;22.27160;3.74567;,
 1.40377;29.61906;3.21341;,
 2.35201;28.48548;4.85417;,
 -0.22534;28.08855;5.53560;,
 -0.08735;29.35633;3.37408;,
 1.07283;36.18521;2.26549;,
 1.78401;34.89700;3.63565;,
 -0.06135;35.62532;3.99954;,
 0.04677;36.10140;2.33717;,
 0.63496;42.86762;1.20270;,
 -0.16400;43.04015;1.32436;,
 3.85542;16.74332;3.43499;,
 6.38211;15.50206;6.07256;,
 2.82840;23.71218;2.76120;,
 5.35186;22.19991;4.65469;,
 2.45705;29.78542;2.07517;,
 4.23112;28.23820;3.60544;,
 2.05135;36.99042;1.82074;,
 3.05798;35.80565;2.53671;,
 1.29154;42.41176;0.88297;,
 5.38691;15.77296;1.56845;,
 8.45415;12.93133;2.40848;,
 3.55370;24.11110;1.00164;,
 6.80068;21.85770;2.07253;,
 3.11048;29.52320;0.77130;,
 5.28318;28.95519;1.68508;,
 2.56955;35.73248;0.51317;,
 4.01410;35.64124;1.08663;,
 1.47893;42.63464;0.36395;,
 5.33375;17.44141;-0.57985;,
 9.20250;13.65173;-0.62176;,
 3.89418;22.86032;-0.45753;,
 6.91926;21.74906;-0.71186;,
 3.28345;29.25963;-0.55856;,
 5.57668;28.00575;-0.69091;,
 2.45978;35.85902;-0.67585;,
 3.99454;35.66889;-0.50759;,
 1.52488;42.65229;-0.38128;,
 4.64570;17.09905;-2.82380;,
 8.18613;14.88257;-4.79291;,
 3.47479;23.13718;-2.08887;,
 5.97877;22.44470;-3.56679;,
 2.79112;29.68727;-1.68924;,
 4.87867;28.13346;-2.99855;,
 2.05153;37.00240;-1.47494;,
 3.58982;35.06136;-2.60168;,
 1.27273;42.80422;-0.87165;,
 3.14400;17.09562;-4.47150;,
 5.27765;15.25005;-7.41831;,
 2.13335;22.99554;-3.16903;,
 4.09943;22.54809;-6.02303;,
 1.98055;29.67479;-2.92057;,
 3.34858;27.53481;-5.02905;,
 1.56179;36.24943;-2.11052;,
 2.52063;34.54500;-3.52345;,
 1.18730;42.70562;-1.42442;,
 1.06931;16.56892;-5.46111;,
 1.64726;15.74747;-8.56585;,
 0.81669;23.16473;-3.92998;,
 1.55480;22.36690;-7.11785;,
 0.60164;29.03033;-3.19974;,
 0.95718;28.80076;-5.92287;,
 0.64636;35.70973;-2.81661;,
 0.48710;36.15267;-4.17098;,
 0.49186;42.63313;-1.53557;,
 -1.15509;17.00985;-5.49501;,
 -1.86144;15.06745;-8.69387;,
 -0.62455;22.59977;-3.82624;,
 -1.43497;22.86165;-7.21262;,
 -0.94326;29.14494;-3.69145;,
 -1.11549;28.40842;-5.65610;,
 -0.56587;36.15405;-2.68012;,
 -0.67557;34.77717;-4.72075;,
 -0.74450;42.72938;-1.51686;,
 -3.23908;18.93586;-4.67898;,
 -5.38558;17.39764;-6.85570;,
 -2.32736;24.32685;-2.96374;,
 -4.17033;22.09169;-5.79661;,
 -2.07121;30.61868;-2.84149;,
 -3.47591;29.47537;-4.64068;,
 -1.58092;36.14224;-2.22726;,
 -2.17781;33.89714;-3.52083;,
 -0.85588;42.99594;-1.31081;,
 -4.90013;17.12298;-2.85181;,
 -7.77065;14.55974;-4.41501;,
 -3.37650;23.82295;-2.06926;,
 -6.30743;22.90019;-3.83459;,
 -3.32435;30.05150;-1.80848;,
 -5.08289;27.98960;-3.19119;,
 -2.39241;35.98759;-1.48840;,
 -3.47324;36.28131;-2.51038;,
 -1.52844;42.60262;-0.87191;,
 -5.14954;16.49917;-0.84185;,
 -9.18402;14.93147;-1.11561;,
 -3.82604;23.09955;-0.41190;,
 -7.19348;22.80096;-0.79554;,
 -3.44048;28.71596;-0.63328;,
 -5.57374;28.56270;-0.90808;,
 -2.76548;36.87327;-0.64083;,
 -4.32644;34.44329;-0.66165;,
 -1.55900;42.72007;-0.42096;,
 -5.27764;16.01583;1.68999;,
 -7.35117;15.85200;2.17357;,
 -3.55087;23.27347;0.90269;,
 -6.55288;21.74187;2.05385;,
 -3.25126;29.71985;0.91564;,
 -5.41488;28.40617;1.58640;,
 -2.43653;35.87017;0.60352;,
 -3.70590;34.52557;1.41371;,
 -1.37931;42.66380;0.24308;,
 -4.00979;17.05152;3.46699;,
 -6.30813;15.50027;5.34656;,
 -2.73894;22.92666;2.40497;,
 -5.37903;21.60149;4.65739;,
 -2.41028;29.38907;2.46251;,
 -4.08922;27.91452;3.74593;,
 -1.77702;35.98929;1.71188;,
 -3.36750;35.71546;2.68706;,
 -1.18276;42.38883;1.09302;,
 -2.10359;16.18236;4.47387;,
 -4.01833;16.31797;7.34203;,
 -1.60395;23.19764;3.33265;,
 -2.91881;21.31147;6.64903;,
 -1.13746;29.16236;2.95184;,
 -2.65633;28.33509;5.08077;,
 -1.08320;35.87361;2.24080;,
 -1.77039;35.14346;3.57333;,
 -0.58601;42.58446;1.33052;,
 0.00986;16.01357;5.54879;,
 0.46755;18.04591;8.72278;,
 -0.18690;22.27160;3.74567;,
 -0.19636;21.06625;6.98526;,
 -0.08735;29.35633;3.37408;,
 -0.22534;28.08855;5.53560;,
 0.04677;36.10140;2.33717;,
 -0.06135;35.62532;3.99954;,
 -0.16400;43.04015;1.32436;,
 0.42604;12.25294;10.33908;,
 -4.64841;8.43252;9.14987;,
 -7.15114;10.00081;6.08762;,
 -9.10776;9.34260;2.51212;,
 -10.52086;8.03962;-1.20212;,
 -9.10671;7.91035;-5.21266;,
 -6.39021;10.21261;-7.96975;,
 -1.98162;8.98009;-10.10418;,
 2.10181;9.36426;-10.15714;,
 5.86437;9.13999;-8.65007;,
 9.24271;8.53450;-5.31176;,
 10.52687;8.27645;-0.70603;,
 10.12815;6.78635;2.91495;,
 7.37525;9.47514;6.75764;,
 3.99303;9.85148;9.16583;,
 0.42604;12.25294;10.33908;,
 0.42604;12.25294;10.33908;,
 -4.64841;8.43252;9.14987;,
 -7.15114;10.00081;6.08762;,
 -9.10776;9.34260;2.51212;,
 -10.52086;8.03962;-1.20212;,
 -9.10671;7.91035;-5.21266;,
 -6.39021;10.21261;-7.96975;,
 -1.98162;8.98009;-10.10418;,
 2.10181;9.36426;-10.15714;,
 5.86437;9.13999;-8.65007;,
 9.24271;8.53450;-5.31176;,
 10.52687;8.27645;-0.70603;,
 10.12815;6.78635;2.91495;,
 7.37525;9.47514;6.75764;,
 3.99303;9.85148;9.16583;,
 -0.01053;-0.17693;1.67053;,
 -1.52100;10.13325;0.35089;,
 -1.73235;-0.17693;0.41956;,
 -1.07467;-0.17693;-1.60456;,
 1.05362;-0.17693;-1.60456;,
 -0.01053;-0.17693;-1.60456;,
 0.51555;42.29314;-0.86397;,
 -0.53661;42.29314;-0.86397;,
 0.84069;42.29314;0.13669;,
 0.51555;42.29314;-0.86397;,
 -0.01053;42.29314;0.75513;,
 -0.53661;42.29314;-0.86397;,
 -0.86174;42.29314;0.13669;,
 0.84069;42.29314;0.13669;,
 1.71129;-0.17693;0.41956;,
 -0.01053;42.29314;0.75513;,
 -0.01053;-0.17693;1.67053;,
 -0.01053;-0.17693;1.67053;,
 -1.73235;-0.17693;0.41956;,
 -0.01053;-0.17693;-0.29452;,
 -0.01053;-0.17693;-1.60456;,
 -1.07467;-0.17693;-1.60456;,
 -0.01053;42.29314;0.75513;,
 -0.86174;42.29314;0.13669;,
 1.71129;-0.17693;0.41956;,
 1.05362;-0.17693;-1.60456;;
 
 224;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 3;28,29,30;,
 3;30,29,31;,
 3;29,32,31;,
 3;31,32,33;,
 3;32,34,33;,
 3;33,34,35;,
 3;34,36,35;,
 3;35,36,37;,
 3;36,38,37;,
 3;37,38,39;,
 3;38,40,39;,
 3;39,40,41;,
 3;40,42,41;,
 4;27,26,43,44;,
 4;44,43,45,46;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;50,52,51;,
 3;51,52,53;,
 3;52,54,53;,
 3;53,54,55;,
 3;54,56,55;,
 3;55,56,57;,
 3;56,58,57;,
 3;57,58,59;,
 3;58,60,59;,
 3;60,61,59;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,44,46,79;,
 4;80,81,63,62;,
 4;82,83,67,66;,
 4;84,85,71,70;,
 4;86,87,75,74;,
 4;88,27,44,78;,
 4;89,90,81,80;,
 4;91,92,83,82;,
 4;93,94,85,84;,
 4;95,96,87,86;,
 4;97,25,27,88;,
 4;98,99,90,89;,
 4;100,101,92,91;,
 4;102,103,94,93;,
 4;104,105,96,95;,
 4;106,23,25,97;,
 4;107,108,99,98;,
 4;109,110,101,100;,
 4;111,112,103,102;,
 4;113,114,105,104;,
 4;115,21,23,106;,
 4;116,117,108,107;,
 4;118,119,110,109;,
 4;120,121,112,111;,
 4;122,123,114,113;,
 4;124,19,21,115;,
 4;125,126,117,116;,
 4;127,128,119,118;,
 4;129,130,121,120;,
 4;131,132,123,122;,
 4;133,17,19,124;,
 4;134,135,126,125;,
 4;136,137,128,127;,
 4;138,139,130,129;,
 4;140,141,132,131;,
 4;142,15,17,133;,
 4;143,144,135,134;,
 4;145,146,137,136;,
 4;147,148,139,138;,
 4;149,150,141,140;,
 4;151,13,15,142;,
 4;152,153,144,143;,
 4;154,155,146,145;,
 4;156,157,148,147;,
 4;158,159,150,149;,
 4;160,11,13,151;,
 4;161,162,153,152;,
 4;163,164,155,154;,
 4;165,166,157,156;,
 4;167,168,159,158;,
 4;169,9,11,160;,
 4;170,171,162,161;,
 4;172,173,164,163;,
 4;174,175,166,165;,
 4;176,177,168,167;,
 4;178,7,9,169;,
 4;179,180,171,170;,
 4;181,182,173,172;,
 4;183,184,175,174;,
 4;185,186,177,176;,
 4;187,5,7,178;,
 4;188,189,180,179;,
 4;190,191,182,181;,
 4;192,193,184,183;,
 4;194,195,186,185;,
 4;196,3,5,187;,
 4;197,198,189,188;,
 4;199,200,191,190;,
 4;201,202,193,192;,
 4;203,204,195,194;,
 4;205,0,3,196;,
 4;206,197,188,207;,
 4;207,188,179,208;,
 4;208,179,170,209;,
 4;209,170,161,210;,
 4;210,161,152,211;,
 4;211,152,143,212;,
 4;212,143,134,213;,
 4;213,134,125,214;,
 4;214,125,116,215;,
 4;215,116,107,216;,
 4;216,107,98,217;,
 4;217,98,89,218;,
 4;218,89,80,219;,
 4;219,80,62,220;,
 4;220,62,65,221;,
 4;198,199,190,189;,
 4;189,190,181,180;,
 4;180,181,172,171;,
 4;171,172,163,162;,
 4;162,163,154,153;,
 4;153,154,145,144;,
 4;144,145,136,135;,
 4;135,136,127,126;,
 4;126,127,118,117;,
 4;117,118,109,108;,
 4;108,109,100,99;,
 4;99,100,91,90;,
 4;90,91,82,81;,
 4;81,82,66,63;,
 4;63,66,69,64;,
 4;200,201,192,191;,
 4;191,192,183,182;,
 4;182,183,174,173;,
 4;173,174,165,164;,
 4;164,165,156,155;,
 4;155,156,147,146;,
 4;146,147,138,137;,
 4;137,138,129,128;,
 4;128,129,120,119;,
 4;119,120,111,110;,
 4;110,111,102,101;,
 4;101,102,93,92;,
 4;92,93,84,83;,
 4;83,84,70,67;,
 4;67,70,73,68;,
 4;202,203,194,193;,
 4;193,194,185,184;,
 4;184,185,176,175;,
 4;175,176,167,166;,
 4;166,167,158,157;,
 4;157,158,149,148;,
 4;148,149,140,139;,
 4;139,140,131,130;,
 4;130,131,122,121;,
 4;121,122,113,112;,
 4;112,113,104,103;,
 4;103,104,95,94;,
 4;94,95,86,85;,
 4;85,86,74,71;,
 4;71,74,77,72;,
 4;204,205,196,195;,
 4;195,196,187,186;,
 4;186,187,178,177;,
 4;177,178,169,168;,
 4;168,169,160,159;,
 4;159,160,151,150;,
 4;150,151,142,141;,
 4;141,142,133,132;,
 4;132,133,124,123;,
 4;123,124,115,114;,
 4;114,115,106,105;,
 4;105,106,97,96;,
 4;96,97,88,87;,
 4;87,88,78,75;,
 4;75,78,79,76;,
 4;56,54,222,223;,
 4;58,56,223,224;,
 4;60,58,224,225;,
 4;61,60,225,226;,
 4;59,61,226,227;,
 4;57,59,227,228;,
 4;55,57,228,229;,
 4;53,55,229,230;,
 4;51,53,230,231;,
 4;49,51,231,232;,
 4;47,49,232,233;,
 4;48,47,233,234;,
 4;50,48,234,235;,
 4;52,50,235,236;,
 4;54,52,236,222;,
 3;237,238,239;,
 3;239,238,240;,
 3;241,242,243;,
 3;243,242,244;,
 3;242,240,244;,
 3;245,246,247;,
 3;246,248,247;,
 3;248,249,247;,
 4;241,243,250,251;,
 4;251,250,252,253;,
 3;254,255,256;,
 3;257,256,258;,
 3;256,255,258;,
 4;237,259,260,238;,
 4;240,238,260,244;,
 3;261,254,262;,
 3;262,254,256;,
 3;256,257,262;;
 
 MeshMaterialList {
  2;
  224;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0;;
  Material {
   0.053600;0.408000;0.053600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326400;0.200800;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  209;
  0.005911;-0.997063;0.076364;,
  -0.046462;0.478006;0.877127;,
  0.113342;-0.990013;-0.083826;,
  -0.530910;0.401786;0.746126;,
  0.046944;-0.995234;-0.085473;,
  -0.745961;0.349145;0.567133;,
  0.206048;-0.978116;0.028865;,
  -0.859918;0.356203;0.365596;,
  0.328145;-0.938299;0.109161;,
  -0.920838;0.389443;-0.019807;,
  0.235816;-0.969992;0.059209;,
  -0.774560;0.409930;-0.481678;,
  0.051411;-0.997311;0.052225;,
  -0.492485;0.395782;-0.775123;,
  0.053883;-0.987780;0.146242;,
  -0.224081;0.392772;-0.891918;,
  -0.090955;-0.985167;0.145508;,
  0.091886;0.410937;-0.907021;,
  -0.028767;-0.994391;0.101777;,
  0.539149;0.440963;-0.717544;,
  -0.183849;-0.978751;0.090813;,
  0.822765;0.420041;-0.382913;,
  -0.396187;-0.918170;0.000472;,
  0.907903;0.408707;0.093119;,
  -0.294333;-0.954687;-0.044045;,
  0.866120;0.371546;0.334350;,
  -0.076912;-0.995494;-0.055458;,
  0.796722;0.415088;0.439244;,
  -0.114645;-0.993360;-0.009633;,
  0.000000;1.000000;0.000000;,
  0.000257;-0.990933;0.134357;,
  0.107781;-0.925897;-0.362075;,
  0.099191;-0.865218;-0.491486;,
  0.048251;-0.933103;-0.356356;,
  0.153725;-0.922623;-0.353745;,
  0.205308;-0.899978;-0.384562;,
  0.050674;-0.920974;-0.386313;,
  0.058915;-0.997380;0.041979;,
  0.298295;-0.945301;-0.132011;,
  0.320838;-0.869382;-0.375817;,
  0.298175;-0.912285;-0.280763;,
  0.203293;-0.972519;-0.113483;,
  0.642798;-0.758798;-0.105056;,
  0.384504;-0.915283;-0.120060;,
  0.305787;-0.923766;-0.230543;,
  0.267465;-0.962198;-0.051351;,
  0.692513;-0.705007;-0.152938;,
  0.437975;-0.897918;0.043826;,
  0.253432;-0.951811;-0.172708;,
  0.377073;-0.926182;-0.001812;,
  0.283910;-0.922609;0.261127;,
  0.573998;-0.818693;0.016393;,
  0.272145;-0.957851;0.091967;,
  0.615700;-0.787144;-0.036310;,
  0.217766;-0.813902;0.538648;,
  -0.302125;-0.792109;0.530362;,
  0.137062;-0.928395;0.345394;,
  -0.271710;-0.718806;0.639915;,
  0.365825;-0.850209;0.378573;,
  -0.124785;-0.916595;0.379846;,
  0.022836;-0.982717;0.183700;,
  -0.138368;-0.829457;0.541161;,
  -0.140185;-0.966336;0.215739;,
  -0.010505;-0.966990;0.254599;,
  0.001651;-0.996422;0.084496;,
  -0.057757;-0.915944;0.397128;,
  -0.318943;-0.777619;0.541835;,
  -0.255346;-0.895394;0.364785;,
  -0.101048;-0.985457;0.136617;,
  -0.239878;-0.908819;0.341329;,
  -0.417821;-0.808342;0.414739;,
  -0.492009;-0.840758;0.225950;,
  -0.222155;-0.974856;0.017397;,
  -0.503974;-0.838165;0.208541;,
  -0.334593;-0.942094;-0.022512;,
  -0.465982;-0.875988;0.124518;,
  -0.420127;-0.904659;0.071316;,
  -0.642068;-0.751470;-0.151793;,
  -0.297025;-0.953641;0.048419;,
  -0.349835;-0.936811;-0.001243;,
  -0.484185;-0.874936;-0.007207;,
  -0.621187;-0.766552;-0.162862;,
  -0.014309;-0.629804;-0.776622;,
  -0.330269;-0.889489;-0.315803;,
  -0.206149;-0.947807;-0.243239;,
  -0.467154;-0.881271;-0.071613;,
  0.467103;0.465543;0.751721;,
  -0.098972;-0.786682;-0.609374;,
  -0.161605;-0.855678;-0.491628;,
  0.223879;-0.948299;-0.224960;,
  -0.185187;-0.976071;-0.113977;,
  0.213196;-0.898416;-0.383923;,
  0.572034;-0.672367;-0.469786;,
  0.588503;-0.689907;-0.421536;,
  0.714561;-0.647585;-0.264643;,
  0.764391;-0.643940;-0.032348;,
  0.701181;-0.675891;0.226972;,
  0.330178;-0.743959;0.580955;,
  0.032689;-0.680051;0.732435;,
  0.020369;-0.756987;0.653112;,
  -0.429495;-0.784805;0.446783;,
  -0.724759;-0.662108;0.190621;,
  -0.762312;-0.631207;-0.143032;,
  -0.803659;-0.529520;-0.271551;,
  -0.773153;-0.624862;-0.108544;,
  -0.486533;-0.849136;-0.205557;,
  -0.067089;0.672585;0.736972;,
  -0.421069;0.553812;0.718327;,
  -0.621443;0.524573;0.581921;,
  -0.836439;0.505927;0.210730;,
  -0.866801;0.497996;-0.025614;,
  -0.848239;0.463305;-0.256591;,
  -0.531835;0.487636;-0.692360;,
  -0.061431;0.477526;-0.876467;,
  0.163182;0.529066;-0.832743;,
  0.479513;0.535240;-0.695403;,
  0.747517;0.511069;-0.424297;,
  0.864635;0.501760;0.025364;,
  0.814678;0.489474;0.310989;,
  0.688473;0.538352;0.485986;,
  0.446279;0.591117;0.671875;,
  -0.587695;0.017435;0.808895;,
  -0.587695;0.017435;0.808895;,
  -0.950912;0.017435;-0.308970;,
  0.000000;0.017435;-0.999848;,
  0.950912;0.017435;-0.308969;,
  0.000000;-1.000000;-0.000000;,
  -0.492497;-0.857312;0.149876;,
  0.680825;-0.720459;-0.131969;,
  0.620033;-0.774651;0.124401;,
  0.088087;0.635214;0.767296;,
  -0.427193;0.585773;0.688749;,
  -0.703761;0.516302;0.488010;,
  -0.811829;0.490886;0.316172;,
  -0.864467;0.502682;-0.002796;,
  -0.806308;0.508946;-0.301397;,
  -0.435883;0.577920;-0.689938;,
  -0.091048;0.520301;-0.849115;,
  0.123083;0.549559;-0.826338;,
  0.473981;0.543022;-0.693159;,
  0.734899;0.559408;-0.383389;,
  0.878326;0.478053;0.002928;,
  0.875300;0.438392;0.204116;,
  0.602612;0.503309;0.619305;,
  0.313968;0.559191;0.767287;,
  -0.146757;0.419007;0.896044;,
  -0.326036;0.412975;0.850384;,
  -0.624578;0.425324;0.654982;,
  -0.854238;0.431676;0.289713;,
  -0.895602;0.439086;0.071413;,
  -0.814821;0.454725;-0.359572;,
  -0.488876;0.415297;-0.767157;,
  -0.080878;0.469441;-0.879252;,
  0.181873;0.474314;-0.861365;,
  0.471435;0.485830;-0.736015;,
  0.816774;0.449520;-0.361678;,
  0.894330;0.438751;-0.087581;,
  0.872970;0.446380;0.196646;,
  0.725704;0.454073;0.516887;,
  0.297150;0.466970;0.832851;,
  -0.015112;0.360452;0.932655;,
  -0.391785;0.381241;0.837353;,
  -0.706879;0.365799;0.605404;,
  -0.852992;0.349577;0.387556;,
  -0.931294;0.350511;-0.099161;,
  -0.780697;0.358807;-0.511634;,
  -0.531323;0.404733;-0.744236;,
  -0.193411;0.385267;-0.902309;,
  0.195514;0.389598;-0.899993;,
  0.543062;0.352743;-0.762008;,
  0.819366;0.352343;-0.452210;,
  0.931195;0.352283;-0.093657;,
  0.919635;0.359684;0.157793;,
  0.678397;0.342538;0.649958;,
  0.256812;0.326322;0.909704;,
  -0.033077;0.336608;0.941064;,
  -0.362337;0.322059;0.874637;,
  -0.751673;0.354090;0.556425;,
  -0.930573;0.303969;0.204051;,
  -0.946505;0.315107;0.069544;,
  -0.759374;0.341715;-0.553698;,
  -0.554706;0.282610;-0.782581;,
  -0.360169;0.344261;-0.867043;,
  0.157932;0.361796;-0.918783;,
  0.570664;0.349718;-0.742994;,
  0.843675;0.332544;-0.421459;,
  0.930082;0.339312;-0.140769;,
  0.901740;0.348103;0.256300;,
  0.686926;0.339931;0.642324;,
  0.396959;0.328089;0.857194;,
  0.045596;-0.988833;0.141882;,
  0.262734;-0.948707;-0.175857;,
  0.156400;-0.957347;-0.242954;,
  0.386238;-0.922397;0.001756;,
  0.469136;-0.873186;0.132129;,
  0.446796;-0.891401;0.076003;,
  0.212600;-0.965098;0.152925;,
  0.003446;-0.939412;0.342772;,
  -0.053620;-0.945540;0.321059;,
  -0.215916;-0.941603;0.258388;,
  -0.383684;-0.908454;0.165827;,
  -0.505682;-0.862186;-0.030336;,
  -0.528143;-0.838724;-0.132694;,
  -0.309055;-0.938119;-0.156261;,
  -0.271782;-0.962169;-0.019117;,
  -0.950912;0.017435;-0.308969;,
  0.587696;0.017435;0.808894;,
  -0.587695;0.017435;0.808895;,
  -0.950912;0.017435;-0.308971;;
  224;
  4;1,1,3,3;,
  4;3,3,5,5;,
  4;5,5,7,7;,
  4;7,7,9,9;,
  4;9,9,11,11;,
  4;11,11,13,13;,
  4;13,13,15,15;,
  4;15,15,17,17;,
  4;17,17,19,19;,
  4;19,19,21,21;,
  4;21,21,23,23;,
  4;23,23,25,25;,
  4;25,25,27,27;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  4;27,27,86,86;,
  4;86,86,1,1;,
  3;22,24,20;,
  3;24,26,20;,
  3;20,26,18;,
  3;26,28,18;,
  3;18,28,16;,
  3;28,0,16;,
  3;16,0,14;,
  3;0,2,14;,
  3;14,2,12;,
  3;2,4,12;,
  3;12,4,10;,
  3;4,6,10;,
  3;6,8,10;,
  4;90,90,30,30;,
  4;89,89,31,31;,
  4;88,88,32,32;,
  4;87,87,33,33;,
  4;105,105,91,91;,
  4;85,85,90,90;,
  4;84,84,89,89;,
  4;83,83,88,88;,
  4;82,82,87,87;,
  4;104,104,105,105;,
  4;81,81,85,85;,
  4;80,80,84,84;,
  4;79,79,83,83;,
  4;78,78,127,127;,
  4;103,103,104,104;,
  4;77,77,81,81;,
  4;76,76,80,80;,
  4;75,75,79,79;,
  4;74,74,78,78;,
  4;102,102,103,103;,
  4;73,73,77,77;,
  4;72,72,76,76;,
  4;71,71,75,75;,
  4;70,70,74,74;,
  4;101,101,102,102;,
  4;69,69,73,73;,
  4;68,68,72,72;,
  4;67,67,71,71;,
  4;66,66,70,70;,
  4;100,100,101,101;,
  4;65,65,69,69;,
  4;64,64,68,68;,
  4;63,63,67,67;,
  4;62,62,66,66;,
  4;99,99,100,100;,
  4;61,61,65,65;,
  4;60,60,64,64;,
  4;59,59,63,63;,
  4;58,58,62,62;,
  4;98,98,99,99;,
  4;57,57,61,61;,
  4;56,56,60,60;,
  4;55,55,59,59;,
  4;54,54,58,58;,
  4;97,97,98,98;,
  4;53,53,128,128;,
  4;52,52,56,56;,
  4;51,51,129,129;,
  4;50,50,54,54;,
  4;96,96,97,97;,
  4;49,49,53,53;,
  4;48,48,52,52;,
  4;47,47,51,51;,
  4;46,46,50,50;,
  4;95,95,96,96;,
  4;45,45,49,49;,
  4;44,44,48,48;,
  4;43,43,47,47;,
  4;42,42,46,46;,
  4;94,94,95,95;,
  4;41,41,45,45;,
  4;40,40,44,44;,
  4;39,39,43,43;,
  4;38,38,42,42;,
  4;93,93,94,94;,
  4;37,37,41,41;,
  4;36,36,40,40;,
  4;35,35,39,39;,
  4;34,34,38,38;,
  4;92,92,93,93;,
  4;30,30,37,37;,
  4;31,31,36,36;,
  4;32,32,35,35;,
  4;33,33,34,34;,
  4;91,91,92,92;,
  4;106,106,107,107;,
  4;107,107,108,108;,
  4;108,108,109,109;,
  4;109,109,110,110;,
  4;110,110,111,111;,
  4;111,111,112,112;,
  4;112,112,113,113;,
  4;113,113,114,114;,
  4;114,114,115,115;,
  4;115,115,116,116;,
  4;116,116,117,117;,
  4;117,117,118,118;,
  4;118,118,119,119;,
  4;119,119,120,120;,
  4;120,120,106,106;,
  4;130,130,131,131;,
  4;131,131,132,132;,
  4;132,132,133,133;,
  4;133,133,134,134;,
  4;134,134,135,135;,
  4;135,135,136,136;,
  4;136,136,137,137;,
  4;137,137,138,138;,
  4;138,138,139,139;,
  4;139,139,140,140;,
  4;140,140,141,141;,
  4;141,141,142,142;,
  4;142,142,143,143;,
  4;143,143,144,144;,
  4;144,144,130,130;,
  4;145,145,146,146;,
  4;146,146,147,147;,
  4;147,147,148,148;,
  4;148,148,149,149;,
  4;149,149,150,150;,
  4;150,150,151,151;,
  4;151,151,152,152;,
  4;152,152,153,153;,
  4;153,153,154,154;,
  4;154,154,155,155;,
  4;155,155,156,156;,
  4;156,156,157,157;,
  4;157,157,158,158;,
  4;158,158,159,159;,
  4;159,159,145,145;,
  4;160,160,161,161;,
  4;161,161,162,162;,
  4;162,162,163,163;,
  4;163,163,164,164;,
  4;164,164,165,165;,
  4;165,165,166,166;,
  4;166,166,167,167;,
  4;167,167,168,168;,
  4;168,168,169,169;,
  4;169,169,170,170;,
  4;170,170,171,171;,
  4;171,171,172,172;,
  4;172,172,173,173;,
  4;173,173,174,174;,
  4;174,174,160,160;,
  4;175,175,176,176;,
  4;176,176,177,177;,
  4;177,177,178,178;,
  4;178,178,179,179;,
  4;179,179,180,180;,
  4;180,180,181,181;,
  4;181,181,182,182;,
  4;182,182,183,183;,
  4;183,183,184,184;,
  4;184,184,185,185;,
  4;185,185,186,186;,
  4;186,186,187,187;,
  4;187,187,188,188;,
  4;188,188,189,189;,
  4;189,189,175,175;,
  4;2,0,190,191;,
  4;4,2,191,192;,
  4;6,4,192,193;,
  4;8,6,193,194;,
  4;10,8,194,195;,
  4;12,10,195,196;,
  4;14,12,196,197;,
  4;16,14,197,198;,
  4;18,16,198,199;,
  4;20,18,199,200;,
  4;22,20,200,201;,
  4;24,22,201,202;,
  4;26,24,202,203;,
  4;28,26,203,204;,
  4;0,28,204,190;,
  3;121,121,122;,
  3;205,123,123;,
  3;124,124,124;,
  3;124,124,124;,
  3;124,124,124;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  4;125,125,125,125;,
  4;206,206,206,206;,
  3;126,126,126;,
  3;126,126,126;,
  3;126,126,126;,
  4;121,207,207,121;,
  4;123,123,208,208;,
  3;126,126,126;,
  3;126,126,126;,
  3;126,126,126;;
 }
 MeshTextureCoords {
  263;
  1.000000;0.083330;,
  1.000000;0.000000;,
  0.933330;0.000000;,
  0.933330;0.083330;,
  0.866670;0.000000;,
  0.866670;0.083330;,
  0.800000;0.000000;,
  0.800000;0.083330;,
  0.733330;0.000000;,
  0.733330;0.083330;,
  0.666670;0.000000;,
  0.666670;0.083330;,
  0.600000;0.000000;,
  0.600000;0.083330;,
  0.533330;0.000000;,
  0.533330;0.083330;,
  0.466670;0.000000;,
  0.466670;0.083330;,
  0.400000;0.000000;,
  0.400000;0.083330;,
  0.333330;0.000000;,
  0.333330;0.083330;,
  0.266670;0.000000;,
  0.266670;0.083330;,
  0.200000;0.000000;,
  0.200000;0.083330;,
  0.133330;0.000000;,
  0.133330;0.083330;,
  0.011320;0.775090;,
  0.042150;0.870000;,
  0.021750;0.675840;,
  0.071640;0.589410;,
  0.108930;0.944160;,
  0.152380;0.530750;,
  0.200100;0.984750;,
  0.250000;0.510000;,
  0.299900;0.984750;,
  0.347620;0.530750;,
  0.391070;0.944160;,
  0.428360;0.589410;,
  0.457850;0.870000;,
  0.478250;0.675840;,
  0.488690;0.775090;,
  0.066670;0.000000;,
  0.066670;0.083330;,
  0.000000;0.000000;,
  0.000000;0.083330;,
  0.547990;0.771070;,
  0.555690;0.687490;,
  0.572600;0.851250;,
  0.599240;0.613830;,
  0.633800;0.914610;,
  0.668430;0.564080;,
  0.707250;0.950080;,
  0.750340;0.544940;,
  0.790120;0.949730;,
  0.831780;0.562290;,
  0.870450;0.913800;,
  0.898800;0.614600;,
  0.925370;0.852200;,
  0.944650;0.689800;,
  0.951470;0.768780;,
  0.066670;0.416670;,
  0.066670;0.416670;,
  0.000000;0.416670;,
  0.000000;0.416670;,
  0.066670;0.333330;,
  0.066670;0.333330;,
  0.000000;0.333330;,
  0.000000;0.333330;,
  0.066670;0.250000;,
  0.066670;0.250000;,
  0.000000;0.250000;,
  0.000000;0.250000;,
  0.066670;0.166670;,
  0.066670;0.166670;,
  0.000000;0.166670;,
  0.000000;0.166670;,
  0.066670;0.083330;,
  0.000000;0.083330;,
  0.133330;0.416670;,
  0.133330;0.416670;,
  0.133330;0.333330;,
  0.133330;0.333330;,
  0.133330;0.250000;,
  0.133330;0.250000;,
  0.133330;0.166670;,
  0.133330;0.166670;,
  0.133330;0.083330;,
  0.200000;0.416670;,
  0.200000;0.416670;,
  0.200000;0.333330;,
  0.200000;0.333330;,
  0.200000;0.250000;,
  0.200000;0.250000;,
  0.200000;0.166670;,
  0.200000;0.166670;,
  0.200000;0.083330;,
  0.266670;0.416670;,
  0.266670;0.416670;,
  0.266670;0.333330;,
  0.266670;0.333330;,
  0.266670;0.250000;,
  0.266670;0.250000;,
  0.266670;0.166670;,
  0.266670;0.166670;,
  0.266670;0.083330;,
  0.333330;0.416670;,
  0.333330;0.416670;,
  0.333330;0.333330;,
  0.333330;0.333330;,
  0.333330;0.250000;,
  0.333330;0.250000;,
  0.333330;0.166670;,
  0.333330;0.166670;,
  0.333330;0.083330;,
  0.400000;0.416670;,
  0.400000;0.416670;,
  0.400000;0.333330;,
  0.400000;0.333330;,
  0.400000;0.250000;,
  0.400000;0.250000;,
  0.400000;0.166670;,
  0.400000;0.166670;,
  0.400000;0.083330;,
  0.466670;0.416670;,
  0.466670;0.416670;,
  0.466670;0.333330;,
  0.466670;0.333330;,
  0.466670;0.250000;,
  0.466670;0.250000;,
  0.466670;0.166670;,
  0.466670;0.166670;,
  0.466670;0.083330;,
  0.533330;0.416670;,
  0.533330;0.416670;,
  0.533330;0.333330;,
  0.533330;0.333330;,
  0.533330;0.250000;,
  0.533330;0.250000;,
  0.533330;0.166670;,
  0.533330;0.166670;,
  0.533330;0.083330;,
  0.600000;0.416670;,
  0.600000;0.416670;,
  0.600000;0.333330;,
  0.600000;0.333330;,
  0.600000;0.250000;,
  0.600000;0.250000;,
  0.600000;0.166670;,
  0.600000;0.166670;,
  0.600000;0.083330;,
  0.666670;0.416670;,
  0.666670;0.416670;,
  0.666670;0.333330;,
  0.666670;0.333330;,
  0.666670;0.250000;,
  0.666670;0.250000;,
  0.666670;0.166670;,
  0.666670;0.166670;,
  0.666670;0.083330;,
  0.733330;0.416670;,
  0.733330;0.416670;,
  0.733330;0.333330;,
  0.733330;0.333330;,
  0.733330;0.250000;,
  0.733330;0.250000;,
  0.733330;0.166670;,
  0.733330;0.166670;,
  0.733330;0.083330;,
  0.800000;0.416670;,
  0.800000;0.416670;,
  0.800000;0.333330;,
  0.800000;0.333330;,
  0.800000;0.250000;,
  0.800000;0.250000;,
  0.800000;0.166670;,
  0.800000;0.166670;,
  0.800000;0.083330;,
  0.866670;0.416670;,
  0.866670;0.416670;,
  0.866670;0.333330;,
  0.866670;0.333330;,
  0.866670;0.250000;,
  0.866670;0.250000;,
  0.866670;0.166670;,
  0.866670;0.166670;,
  0.866670;0.083330;,
  0.933330;0.416670;,
  0.933330;0.416670;,
  0.933330;0.333330;,
  0.933330;0.333330;,
  0.933330;0.250000;,
  0.933330;0.250000;,
  0.933330;0.166670;,
  0.933330;0.166670;,
  0.933330;0.083330;,
  1.000000;0.416670;,
  1.000000;0.416670;,
  1.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.166670;,
  1.000000;0.166670;,
  1.000000;0.083330;,
  1.000000;0.500000;,
  0.933330;0.500000;,
  0.866670;0.500000;,
  0.800000;0.500000;,
  0.733330;0.500000;,
  0.666670;0.500000;,
  0.600000;0.500000;,
  0.533330;0.500000;,
  0.466670;0.500000;,
  0.400000;0.500000;,
  0.333330;0.500000;,
  0.266670;0.500000;,
  0.200000;0.500000;,
  0.133330;0.500000;,
  0.066670;0.500000;,
  0.000000;0.500000;,
  0.750000;0.510000;,
  0.847620;0.530750;,
  0.928350;0.589410;,
  0.978250;0.675840;,
  0.988690;0.775090;,
  0.957850;0.870000;,
  0.891070;0.944160;,
  0.799900;0.984750;,
  0.700100;0.984750;,
  0.608930;0.944160;,
  0.542150;0.870000;,
  0.511310;0.775090;,
  0.521750;0.675840;,
  0.571650;0.589410;,
  0.652380;0.530750;,
  1.000000;0.500000;,
  0.800000;0.378620;,
  0.800000;0.500000;,
  0.600000;0.500000;,
  0.400000;0.500000;,
  0.500000;0.500000;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.021750;0.675840;,
  0.108930;0.944160;,
  0.250000;0.510000;,
  0.391070;0.944160;,
  0.478250;0.675840;,
  0.200000;0.000000;,
  0.200000;0.500000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.750000;0.510000;,
  0.978250;0.675840;,
  0.750000;0.770500;,
  0.750000;0.944160;,
  0.891070;0.944160;,
  1.000000;0.000000;,
  0.800000;0.000000;,
  0.521750;0.675840;,
  0.608930;0.944160;;
 }
}
