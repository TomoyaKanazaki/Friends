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
 2.37759;0.00000;0.00000;,
 3.00117;0.00000;0.00000;,
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
 -3.53279;0.00000;0.00000;,
 -2.90920;0.00000;0.00000;,
 5.25627;-6.38762;-5.65319;,
 -5.25627;-6.38762;-5.65319;,
 -5.25627;-4.82614;-5.65319;,
 5.25627;-4.82614;-5.65319;,
 5.25627;-4.82614;1.10933;,
 -5.25627;-4.82614;1.10933;,
 -5.25627;-4.82614;6.00633;,
 5.25627;-4.82614;6.00633;,
 -5.25627;-6.38762;6.00633;,
 5.25627;-6.38762;6.00633;,
 -5.25627;-4.82614;-0.98938;,
 5.25627;-4.82614;-0.98938;,
 5.25627;-0.97399;-1.71210;,
 0.00000;-0.97399;-1.71210;,
 0.00000;-0.97399;1.68552;,
 5.25627;-0.97399;1.68552;,
 -5.25627;-0.97399;-1.71210;,
 -5.25627;-0.97399;1.68552;;
 
 71;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;1,0,16;,
 3;4,1,16;,
 3;6,4,16;,
 3;8,6,16;,
 3;10,8,16;,
 3;12,10,16;,
 3;14,12,16;,
 3;0,14,16;,
 3;3,2,17;,
 3;2,5,17;,
 3;5,7,17;,
 3;7,9,17;,
 3;9,11,17;,
 3;11,13,17;,
 3;13,15,17;,
 3;15,3,17;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,18,21,33;,
 3;19,18,34;,
 3;22,19,34;,
 3;24,22,34;,
 3;26,24,34;,
 3;28,26,34;,
 3;30,28,34;,
 3;32,30,34;,
 3;18,32,34;,
 3;21,20,35;,
 3;20,23,35;,
 3;23,25,35;,
 3;25,27,35;,
 3;27,29,35;,
 3;29,31,35;,
 3;31,33,35;,
 3;33,21,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;43,42,44,45;,
 4;45,44,37,36;,
 3;37,44,38;,
 3;38,44,46;,
 3;46,44,41;,
 3;41,44,42;,
 3;45,36,43;,
 3;43,36,40;,
 3;40,36,47;,
 3;47,36,39;,
 4;39,38,46,47;,
 4;48,49,50,51;,
 3;52,49,46;,
 3;46,49,47;,
 3;47,49,48;,
 4;46,41,53,52;,
 3;41,40,53;,
 3;53,40,50;,
 3;50,40,51;,
 4;40,47,48,51;,
 4;49,52,53,50;;
 
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
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.184397;-0.982852;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.184397;-0.982852;,
  -0.000000;-0.147931;0.988998;;
  71;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
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
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
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
  4;14,14,14,14;,
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
  3;13,15,13;,
  3;13,15,13;,
  3;13,15,13;,
  4;8,8,8,8;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  4;9,9,9,9;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  54;
  0.112729;0.461275;,
  0.112729;0.500001;,
  0.222262;0.500001;,
  0.222262;0.461275;,
  0.112729;0.538726;,
  0.222262;0.538726;,
  0.112729;0.554767;,
  0.222262;0.554767;,
  0.112729;0.538726;,
  0.222262;0.538726;,
  0.112729;0.500001;,
  0.222262;0.500001;,
  0.112729;0.461275;,
  0.222262;0.461275;,
  0.112729;0.445235;,
  0.222262;0.445235;,
  0.112729;0.500001;,
  0.222262;0.500001;,
  0.133996;0.432229;,
  0.133996;0.500001;,
  0.325684;0.500001;,
  0.325684;0.432229;,
  0.133996;0.567773;,
  0.325684;0.567773;,
  0.133996;0.595845;,
  0.325684;0.595845;,
  0.133996;0.567773;,
  0.325684;0.567773;,
  0.133996;0.500001;,
  0.325684;0.500001;,
  0.133996;0.432229;,
  0.325684;0.432229;,
  0.133996;0.404157;,
  0.325684;0.404157;,
  0.133996;0.500001;,
  0.325684;0.500001;,
  0.901709;0.266718;,
  0.735591;0.266718;,
  0.735591;0.218804;,
  0.901709;0.218804;,
  0.901709;0.218804;,
  0.735591;0.218804;,
  0.735591;0.218804;,
  0.901709;0.218804;,
  0.735591;0.266718;,
  0.901709;0.266718;,
  0.735591;0.218804;,
  0.901709;0.218804;,
  0.901709;0.100600;,
  0.818650;0.100600;,
  0.818650;0.100600;,
  0.901709;0.100600;,
  0.735591;0.100600;,
  0.735591;0.100600;;
 }
}
