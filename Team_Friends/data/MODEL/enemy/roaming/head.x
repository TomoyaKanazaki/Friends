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
 20;
 20.00000;-0.94993;15.51655;,
 -20.00000;-0.94993;15.51655;,
 -20.00000;-0.94993;-16.48345;,
 20.00000;-0.94993;-16.48345;,
 13.79922;11.46591;-13.99314;,
 0.02300;56.05007;-8.46045;,
 13.78895;11.48646;-4.93814;,
 20.00000;-0.94993;15.51655;,
 20.00000;-0.94993;-16.48345;,
 -13.58586;11.86361;-5.16421;,
 0.02300;56.05007;-8.46045;,
 -13.59592;11.84351;-13.91740;,
 -20.00000;-0.94993;-16.48345;,
 -20.00000;-0.94993;15.51655;,
 13.78895;11.48646;-4.93814;,
 0.02300;56.05007;-8.46045;,
 -13.58586;11.86361;-5.16421;,
 -13.59592;11.84351;-13.91740;,
 0.02300;56.05007;-8.46045;,
 13.79922;11.46591;-13.99314;;
 
 9;
 4;0,1,2,3;,
 3;4,5,6;,
 4;4,6,7,8;,
 3;9,10,11;,
 4;9,11,12,13;,
 3;14,15,16;,
 4;14,16,13,7;,
 3;17,18,19;,
 4;17,19,8,12;;
 
 MeshMaterialList {
  1;
  9;
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
   0.718431;0.690196;0.241569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  13;
  0.955443;0.295175;0.000413;,
  0.000000;-1.000000;0.000000;,
  0.928140;0.372232;0.000207;,
  -0.928125;0.372269;0.000212;,
  0.894633;0.446802;0.000000;,
  -0.955691;0.294372;0.000422;,
  -0.894221;0.447625;-0.000000;,
  -0.001971;0.520987;0.853562;,
  -0.007179;0.076588;0.997037;,
  0.003667;0.851757;0.523924;,
  -0.000526;0.159857;-0.987140;,
  -0.001051;0.122831;-0.992427;,
  -0.000000;0.196658;-0.980472;;
  9;
  4;1,1,1,1;,
  3;2,0,2;,
  4;2,2,4,4;,
  3;3,5,3;,
  4;3,3,6,6;,
  3;7,8,7;,
  4;7,7,9,9;,
  3;10,11,10;,
  4;10,10,12,12;;
 }
 MeshTextureCoords {
  20;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.689604;0.844802;,
  0.000000;0.500000;,
  0.689090;0.155455;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.320339;0.160169;,
  1.000000;0.500000;,
  0.319836;0.840082;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.844545;0.310910;,
  0.500000;1.000000;,
  0.160169;0.320339;,
  0.159918;0.680164;,
  0.500000;0.000000;,
  0.844802;0.689604;;
 }
}
