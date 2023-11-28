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
 54;
 3.53279;0.91324;0.91324;,
 2.90920;0.91324;0.91324;,
 2.90920;0.00000;1.29152;,
 3.53279;0.00000;1.29152;,
 2.90920;-0.91324;0.91324;,
 3.53279;-0.91324;0.91324;,
 2.90920;-1.29152;-0.00000;,
 3.53279;-1.29152;-0.00000;,
 2.90920;-0.91324;-0.91324;,
 3.53279;-0.91324;-0.91324;,
 2.90920;0.00000;-1.29152;,
 3.53279;0.00000;-1.29152;,
 2.90920;0.91324;-0.91324;,
 3.53279;0.91324;-0.91324;,
 2.90920;1.29152;0.00000;,
 3.53279;1.29152;0.00000;,
 3.53279;0.00000;0.00000;,
 2.90920;0.00000;0.00000;,
 -5.25627;-6.38762;-5.65319;,
 -5.25627;-4.82614;-5.65319;,
 5.25627;-4.82614;-5.65319;,
 5.25627;-6.38762;-5.65319;,
 -5.25627;-4.82614;1.10933;,
 -5.25627;-4.82614;6.00633;,
 5.25627;-4.82614;6.00633;,
 5.25627;-4.82614;1.10933;,
 -5.25627;-6.38762;6.00633;,
 5.25627;-6.38762;6.00633;,
 5.25627;-4.82614;-0.98938;,
 -5.25627;-4.82614;-0.98938;,
 0.00000;-0.97399;1.68552;,
 5.25627;-0.97399;1.68552;,
 5.25627;-0.97399;-1.71210;,
 0.00000;-0.97399;-1.71210;,
 -5.25627;-0.97399;-1.71210;,
 -5.25627;-0.97399;1.68552;,
 -2.37759;0.91324;0.91324;,
 -3.00117;0.91324;0.91324;,
 -3.00117;0.00000;1.29152;,
 -2.37759;0.00000;1.29152;,
 -3.00117;-0.91324;0.91324;,
 -2.37759;-0.91324;0.91324;,
 -3.00117;-1.29152;0.00000;,
 -2.37759;-1.29152;0.00000;,
 -3.00117;-0.91324;-0.91324;,
 -2.37759;-0.91324;-0.91324;,
 -3.00117;0.00000;-1.29152;,
 -2.37759;0.00000;-1.29152;,
 -3.00117;0.91324;-0.91324;,
 -2.37759;0.91324;-0.91324;,
 -3.00117;1.29152;0.00000;,
 -2.37759;1.29152;0.00000;,
 -2.37759;0.00000;0.00000;,
 -3.00117;0.00000;0.00000;;
 
 71;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 3;3,16,0;,
 3;5,16,3;,
 3;7,16,5;,
 3;9,16,7;,
 3;11,16,9;,
 3;13,16,11;,
 3;15,16,13;,
 3;0,16,15;,
 3;1,17,2;,
 3;2,17,4;,
 3;4,17,6;,
 3;6,17,8;,
 3;8,17,10;,
 3;10,17,12;,
 3;12,17,14;,
 3;14,17,1;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;23,26,27,24;,
 4;26,18,21,27;,
 3;27,21,24;,
 3;24,21,25;,
 3;25,21,28;,
 3;28,21,20;,
 3;18,26,19;,
 3;19,26,29;,
 3;29,26,22;,
 3;22,26,23;,
 4;19,29,28,20;,
 4;30,31,32,33;,
 3;29,34,28;,
 3;34,33,28;,
 3;28,33,32;,
 4;28,32,31,25;,
 3;22,25,35;,
 3;35,25,30;,
 3;30,25,31;,
 4;22,35,34,29;,
 4;34,35,30,33;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;51,50,37,36;,
 3;39,52,36;,
 3;41,52,39;,
 3;43,52,41;,
 3;45,52,43;,
 3;47,52,45;,
 3;49,52,47;,
 3;51,52,49;,
 3;36,52,51;,
 3;37,53,38;,
 3;38,53,40;,
 3;40,53,42;,
 3;42,53,44;,
 3;44,53,46;,
 3;46,53,48;,
 3;48,53,50;,
 3;50,53,37;;
 
 MeshMaterialList {
  2;
  71;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "feet_UV_Green.jpg";
   }
  }
 }
 MeshNormals {
  17;
  0.000000;0.707107;0.707107;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.707107;0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.707107;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.707107;-0.707107;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.184397;-0.982852;,
  0.000000;-0.147931;0.988998;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.184397;-0.982852;;
  71;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  3;13,13,16;,
  3;13,13,16;,
  3;16,13,13;,
  4;8,8,8,8;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  4;9,9,9,9;,
  4;11,11,11,11;,
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  54;
  0.240971;0.454577;,
  0.112493;0.454577;,
  0.112493;0.500001;,
  0.240971;0.500001;,
  0.112493;0.545425;,
  0.240971;0.545425;,
  0.112493;0.564240;,
  0.240971;0.564240;,
  0.112493;0.545425;,
  0.240971;0.545425;,
  0.112493;0.500001;,
  0.240971;0.500001;,
  0.112493;0.454577;,
  0.240971;0.454577;,
  0.112493;0.435762;,
  0.240971;0.435762;,
  0.240971;0.500001;,
  0.112493;0.500001;,
  0.737892;0.259799;,
  0.737892;0.214544;,
  0.894790;0.214544;,
  0.894790;0.259799;,
  0.737892;0.214544;,
  0.737892;0.214544;,
  0.894790;0.214544;,
  0.894790;0.214544;,
  0.737892;0.259799;,
  0.894790;0.259799;,
  0.894790;0.214544;,
  0.737892;0.214544;,
  0.816341;0.102901;,
  0.894790;0.102901;,
  0.894790;0.102901;,
  0.816341;0.102901;,
  0.737892;0.102901;,
  0.737892;0.102901;,
  0.232090;0.444529;,
  0.075192;0.444529;,
  0.075192;0.500001;,
  0.232090;0.500001;,
  0.075192;0.555473;,
  0.232090;0.555473;,
  0.075192;0.578450;,
  0.232090;0.578450;,
  0.075192;0.555473;,
  0.232090;0.555473;,
  0.075192;0.500001;,
  0.232090;0.500001;,
  0.075192;0.444529;,
  0.232090;0.444529;,
  0.075192;0.421552;,
  0.232090;0.421552;,
  0.232090;0.500001;,
  0.075192;0.500001;;
 }
}
