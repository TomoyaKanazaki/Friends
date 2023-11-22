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
 100;
 5.25627;-6.38762;-5.65319;,
 -5.25627;-6.38762;-5.65319;,
 -5.25627;-4.82613;-5.65319;,
 5.25627;-4.82613;-5.65319;,
 5.25627;-4.82613;1.10933;,
 -5.25627;-4.82613;1.10933;,
 -5.25627;-4.82613;6.00633;,
 5.25627;-4.82613;6.00633;,
 -5.25627;-6.38762;6.00633;,
 5.25627;-6.38762;6.00633;,
 -5.25627;-6.38762;-5.65319;,
 5.25627;-6.38762;-5.65319;,
 -5.25627;-6.38762;6.00633;,
 -5.25627;-4.82613;-0.98938;,
 -5.25627;-4.82613;1.10933;,
 -5.25627;-4.82613;6.00633;,
 5.25627;-6.38762;6.00633;,
 5.25627;-4.82613;6.00633;,
 5.25627;-4.82613;1.10933;,
 5.25627;-4.82613;-0.98938;,
 -5.25627;-4.82613;-0.98938;,
 5.25627;-4.82613;-0.98938;,
 5.25627;-0.97399;-1.71210;,
 0.00000;-0.97399;-1.71210;,
 0.00000;-0.97399;1.68552;,
 5.25627;-0.97399;1.68552;,
 -5.25627;-0.97399;-1.71210;,
 -5.25627;-0.97399;1.68552;,
 2.37759;0.91324;0.91324;,
 2.37759;0.00000;1.29152;,
 3.00117;0.00000;1.29152;,
 3.00117;0.91324;0.91324;,
 2.37759;-0.91324;0.91324;,
 3.00117;-0.91324;0.91324;,
 2.37759;-1.29152;-0.00000;,
 3.00117;-1.29152;-0.00000;,
 2.37759;-0.91324;-0.91324;,
 3.00117;-0.91324;-0.91324;,
 2.37759;0.00000;-1.29152;,
 3.00117;0.00000;-1.29152;,
 2.37759;0.91324;-0.91324;,
 3.00117;0.91324;-0.91324;,
 2.37759;1.29152;0.00000;,
 3.00117;1.29152;0.00000;,
 2.37759;0.91324;0.91324;,
 3.00117;0.91324;0.91324;,
 2.37759;0.00000;1.29152;,
 2.37759;0.91324;0.91324;,
 2.37759;0.00000;0.00000;,
 2.37759;-0.91324;0.91324;,
 2.37759;-1.29152;-0.00000;,
 2.37759;-0.91324;-0.91324;,
 2.37759;0.00000;-1.29152;,
 2.37759;0.91324;-0.91324;,
 2.37759;1.29152;0.00000;,
 3.00117;0.91324;0.91324;,
 3.00117;0.00000;1.29152;,
 3.00117;0.00000;0.00000;,
 3.00117;-0.91324;0.91324;,
 3.00117;-1.29152;-0.00000;,
 3.00117;-0.91324;-0.91324;,
 3.00117;0.00000;-1.29152;,
 3.00117;0.91324;-0.91324;,
 3.00117;1.29152;0.00000;,
 -3.53279;0.91324;0.91324;,
 -3.53279;0.00000;1.29152;,
 -2.90920;0.00000;1.29152;,
 -2.90920;0.91324;0.91324;,
 -3.53279;-0.91324;0.91324;,
 -2.90920;-0.91324;0.91324;,
 -3.53279;-1.29152;0.00000;,
 -2.90920;-1.29152;0.00000;,
 -3.53279;-0.91324;-0.91324;,
 -2.90920;-0.91324;-0.91324;,
 -3.53279;0.00000;-1.29152;,
 -2.90920;0.00000;-1.29152;,
 -3.53279;0.91324;-0.91324;,
 -2.90920;0.91324;-0.91324;,
 -3.53279;1.29152;0.00000;,
 -2.90920;1.29152;0.00000;,
 -3.53279;0.91324;0.91324;,
 -2.90920;0.91324;0.91324;,
 -3.53279;0.00000;1.29152;,
 -3.53279;0.91324;0.91324;,
 -3.53279;0.00000;0.00000;,
 -3.53279;-0.91324;0.91324;,
 -3.53279;-1.29152;0.00000;,
 -3.53279;-0.91324;-0.91324;,
 -3.53279;0.00000;-1.29152;,
 -3.53279;0.91324;-0.91324;,
 -3.53279;1.29152;0.00000;,
 -2.90920;0.91324;0.91324;,
 -2.90920;0.00000;1.29152;,
 -2.90920;0.00000;0.00000;,
 -2.90920;-0.91324;0.91324;,
 -2.90920;-1.29152;0.00000;,
 -2.90920;-0.91324;-0.91324;,
 -2.90920;0.00000;-1.29152;,
 -2.90920;0.91324;-0.91324;,
 -2.90920;1.29152;0.00000;;
 
 71;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 3;1,12,2;,
 3;2,12,13;,
 3;13,12,14;,
 3;14,12,15;,
 3;16,0,17;,
 3;17,0,18;,
 3;18,0,19;,
 3;19,0,3;,
 4;3,2,20,21;,
 4;22,23,24,25;,
 3;26,23,20;,
 3;20,23,21;,
 3;21,23,22;,
 4;20,5,27,26;,
 3;5,4,27;,
 3;27,4,24;,
 3;24,4,25;,
 4;4,21,22,25;,
 4;28,29,30,31;,
 4;29,32,33,30;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 3;46,47,48;,
 3;49,46,48;,
 3;50,49,48;,
 3;51,50,48;,
 3;52,51,48;,
 3;53,52,48;,
 3;54,53,48;,
 3;47,54,48;,
 3;55,56,57;,
 3;56,58,57;,
 3;58,59,57;,
 3;59,60,57;,
 3;60,61,57;,
 3;61,62,57;,
 3;62,63,57;,
 3;63,55,57;,
 4;64,65,66,67;,
 4;65,68,69,66;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 3;82,83,84;,
 3;85,82,84;,
 3;86,85,84;,
 3;87,86,84;,
 3;88,87,84;,
 3;89,88,84;,
 3;90,89,84;,
 3;83,90,84;,
 3;91,92,93;,
 3;92,94,93;,
 3;94,95,93;,
 3;95,96,93;,
 3;96,97,93;,
 3;97,98,93;,
 3;98,99,93;,
 3;99,91,93;,
 4;23,26,27,24;;
 
 MeshMaterialList {
  1;
  71;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  15;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.184398;-0.982852;,
  0.000000;0.707107;0.707107;,
  0.000000;-0.707107;0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.707107;-0.707107;,
  0.000000;0.707107;-0.707107;,
  0.000000;-0.184398;-0.982852;,
  0.000000;-0.184398;-0.982852;,
  -0.000000;-0.147931;0.988998;,
  0.000000;-0.147931;0.988998;;
  71;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;8,8,8,8;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;5,11,12;,
  3;12,11,12;,
  3;12,11,5;,
  4;4,4,4,4;,
  3;13,14,14;,
  3;14,14,14;,
  3;14,14,13;,
  4;3,3,3,3;,
  4;6,2,2,6;,
  4;2,7,7,2;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,0,0,9;,
  4;0,10,10,0;,
  4;10,1,1,10;,
  4;1,6,6,1;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;6,2,2,6;,
  4;2,7,7,2;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,0,0,9;,
  4;0,10,10,0;,
  4;10,1,1,10;,
  4;1,6,6,1;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;1,1,1,1;;
 }
 MeshTextureCoords {
  100;
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.605000;,
  0.625000;0.605000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.875000;1.000000;,
  0.725000;0.750000;,
  0.770000;0.750000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.230000;0.750000;,
  0.275000;0.750000;,
  0.625000;0.650000;,
  0.375000;0.650000;,
  0.375000;0.650000;,
  0.500000;0.650000;,
  0.500000;0.605000;,
  0.375000;0.605000;,
  0.625000;0.650000;,
  0.625000;0.605000;,
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
  0.656250;0.156250;;
 }
}