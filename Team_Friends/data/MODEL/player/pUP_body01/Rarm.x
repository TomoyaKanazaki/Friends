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
 29;
 -17.35187;-5.46473;-4.91185;,
 -17.35187;5.46473;-4.91185;,
 -0.76379;5.02650;-4.24398;,
 -0.76379;-5.02654;-4.24398;,
 -0.00001;5.65014;0.00000;,
 -0.00001;5.65014;4.14936;,
 -0.00001;0.00002;4.14936;,
 -0.00001;0.00002;0.00000;,
 -0.76379;-5.02654;4.24398;,
 -0.76379;5.02650;4.24398;,
 -17.35187;5.46473;4.91185;,
 -17.35187;-5.46473;4.91185;,
 -18.13802;-6.14266;4.51110;,
 -18.13802;6.14268;4.51110;,
 -18.13802;6.14268;-4.51110;,
 -18.13802;-6.14266;-4.51110;,
 -17.35187;6.68836;-4.01323;,
 -17.35187;6.68836;4.01323;,
 -0.76379;5.77893;3.69141;,
 -0.76379;5.77893;-3.69141;,
 -17.35187;-6.68838;4.01323;,
 -17.35187;-6.68838;-4.01323;,
 -0.76379;-5.77891;-3.69141;,
 -0.76379;-5.77891;3.69141;,
 -0.00001;5.65014;-4.14936;,
 -0.00001;0.00002;-4.14936;,
 -0.00001;-5.65009;-4.14936;,
 -0.00001;-5.65009;4.14936;,
 -0.00001;-5.65009;0.00000;;
 
 33;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;15,14,1,0;,
 4;14,24,2,1;,
 3;24,25,2;,
 3;26,3,25;,
 3;25,3,2;,
 4;26,15,0,3;,
 3;8,27,9;,
 3;9,6,5;,
 3;6,9,27;,
 4;5,13,10,9;,
 4;13,12,11,10;,
 4;12,27,8,11;,
 4;14,13,17,16;,
 4;13,5,18,17;,
 3;18,5,19;,
 3;5,4,19;,
 3;19,4,24;,
 4;24,14,16,19;,
 4;12,15,21,20;,
 4;15,26,22,21;,
 3;23,22,27;,
 3;27,22,28;,
 3;28,22,26;,
 4;27,12,20,23;,
 4;7,6,27,28;,
 4;25,24,4,7;,
 4;26,25,7,28;;
 
 MeshMaterialList {
  1;
  33;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "body_UV_Yellow.jpg";
   }
  }
 }
 MeshNormals {
  33;
  -0.886071;-0.463550;0.000000;,
  -0.886063;0.463565;0.000000;,
  0.073797;-0.436070;-0.896882;,
  0.073797;0.436078;-0.896878;,
  0.088713;-0.325937;0.941220;,
  1.000000;0.000000;0.000000;,
  -0.131306;-0.119945;-0.984059;,
  -0.131306;0.119940;-0.984060;,
  0.081685;0.087258;-0.992831;,
  0.081685;-0.087262;-0.992831;,
  0.067558;-0.116592;0.990880;,
  0.090087;0.069684;0.993493;,
  -0.131306;0.119940;0.984060;,
  -0.131306;-0.119945;0.984059;,
  -0.171233;0.966660;0.190390;,
  -0.171233;0.966660;-0.190390;,
  0.091072;0.979137;0.181649;,
  0.122375;0.986598;-0.107929;,
  -0.171244;-0.966654;0.190407;,
  -0.171244;-0.966654;-0.190407;,
  0.122399;-0.986594;-0.107938;,
  0.091087;-0.979133;0.181664;,
  0.122944;0.000000;-0.992414;,
  0.166312;-0.986073;-0.000000;,
  -0.140620;-0.447823;-0.882995;,
  -0.140621;0.447831;-0.882991;,
  0.122944;0.000000;0.992414;,
  0.073797;0.436078;0.896878;,
  -0.140621;0.447831;0.882991;,
  -0.140620;-0.447823;0.882995;,
  0.166275;0.986079;0.000000;,
  0.166275;0.986080;0.000000;,
  0.166275;0.986079;0.000000;;
  33;
  4;6,7,8,9;,
  4;5,5,5,5;,
  4;10,11,12,13;,
  4;0,1,1,0;,
  4;15,14,16,17;,
  4;18,19,20,21;,
  4;24,25,7,6;,
  4;25,3,8,7;,
  3;3,22,8;,
  3;2,9,22;,
  3;22,9,8;,
  4;2,24,6,9;,
  3;10,4,11;,
  3;11,26,27;,
  3;26,11,4;,
  4;27,28,12,11;,
  4;28,29,13,12;,
  4;29,4,10,13;,
  4;1,1,14,15;,
  4;28,27,16,14;,
  3;16,30,17;,
  3;30,31,17;,
  3;17,31,32;,
  4;3,25,15,17;,
  4;0,0,19,18;,
  4;24,2,20,19;,
  3;21,20,23;,
  3;23,20,23;,
  3;23,20,23;,
  4;4,29,18,21;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  29;
  0.191777;0.218127;,
  0.191777;0.082194;,
  0.343931;0.087645;,
  0.343931;0.212677;,
  0.350937;0.079889;,
  0.350937;0.079889;,
  0.350937;0.150161;,
  0.350937;0.150161;,
  0.343931;0.212677;,
  0.343931;0.087645;,
  0.191777;0.082194;,
  0.191777;0.218127;,
  0.184566;0.226559;,
  0.184566;0.073762;,
  0.184566;0.073762;,
  0.184566;0.226559;,
  0.191777;0.066976;,
  0.191777;0.066976;,
  0.343931;0.078287;,
  0.343931;0.078287;,
  0.191777;0.233346;,
  0.191777;0.233346;,
  0.343931;0.222035;,
  0.343931;0.222035;,
  0.350937;0.079889;,
  0.350937;0.150161;,
  0.350937;0.220433;,
  0.350937;0.220433;,
  0.350937;0.220433;;
 }
}
