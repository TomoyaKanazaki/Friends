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
 368;
 100.00000;0.00000;-120.00000;,
 -100.00000;0.00000;-120.00000;,
 -100.00000;500.00000;-120.00000;,
 100.00000;500.00000;-120.00000;,
 100.00000;0.00000;120.00000;,
 100.00000;500.00000;120.00000;,
 -100.00000;500.00000;120.00000;,
 -100.00000;0.00000;120.00000;,
 -100.00000;500.00000;-60.00000;,
 -100.00000;500.00000;60.00000;,
 100.00000;500.00000;60.00000;,
 100.00000;500.00000;-60.00000;,
 -100.00000;0.00000;-60.00000;,
 100.00000;0.00000;-60.00000;,
 100.00000;0.00000;60.00000;,
 -100.00000;0.00000;60.00000;,
 -160.00000;500.00000;-60.00000;,
 -160.00000;0.00000;-60.00000;,
 -160.00000;0.00000;60.00000;,
 -160.00000;500.00000;60.00000;,
 160.00000;500.00000;-60.00000;,
 160.00000;500.00000;60.00000;,
 160.00000;0.00000;60.00000;,
 160.00000;0.00000;-60.00000;,
 120.00000;500.00000;-60.00000;,
 120.00000;500.00000;60.00000;,
 160.00000;500.00000;60.00000;,
 160.00000;500.00000;-60.00000;,
 120.00000;500.00000;-60.00000;,
 160.00000;500.00000;-60.00000;,
 160.00000;0.00000;-60.00000;,
 120.00000;0.00000;-60.00000;,
 100.00000;0.00000;-60.00000;,
 100.00000;500.00000;-60.00000;,
 120.00000;500.00000;60.00000;,
 100.00000;500.00000;60.00000;,
 100.00000;0.00000;60.00000;,
 120.00000;0.00000;60.00000;,
 160.00000;0.00000;60.00000;,
 160.00000;500.00000;60.00000;,
 120.00000;0.00000;-60.00000;,
 160.00000;0.00000;-60.00000;,
 160.00000;0.00000;60.00000;,
 120.00000;0.00000;60.00000;,
 -120.00000;500.00000;-60.00000;,
 -160.00000;500.00000;-60.00000;,
 -160.00000;500.00000;60.00000;,
 -120.00000;500.00000;60.00000;,
 -120.00000;500.00000;-60.00000;,
 -100.00000;500.00000;-60.00000;,
 -100.00000;0.00000;-60.00000;,
 -120.00000;0.00000;-60.00000;,
 -160.00000;0.00000;-60.00000;,
 -160.00000;500.00000;-60.00000;,
 -120.00000;500.00000;60.00000;,
 -160.00000;500.00000;60.00000;,
 -160.00000;0.00000;60.00000;,
 -120.00000;0.00000;60.00000;,
 -100.00000;0.00000;60.00000;,
 -100.00000;500.00000;60.00000;,
 -120.00000;0.00000;-60.00000;,
 -120.00000;0.00000;60.00000;,
 -160.00000;0.00000;60.00000;,
 -160.00000;0.00000;-60.00000;,
 -100.00000;500.00000;80.00000;,
 -100.00000;500.00000;120.00000;,
 100.00000;500.00000;120.00000;,
 100.00000;500.00000;80.00000;,
 -100.00000;500.00000;80.00000;,
 -100.00000;0.00000;80.00000;,
 -100.00000;500.00000;80.00000;,
 -100.00000;0.00000;80.00000;,
 -100.00000;0.00000;120.00000;,
 -100.00000;500.00000;120.00000;,
 100.00000;500.00000;80.00000;,
 100.00000;500.00000;120.00000;,
 100.00000;0.00000;120.00000;,
 100.00000;0.00000;80.00000;,
 100.00000;500.00000;80.00000;,
 100.00000;0.00000;80.00000;,
 -100.00000;0.00000;80.00000;,
 100.00000;0.00000;80.00000;,
 100.00000;0.00000;120.00000;,
 -100.00000;0.00000;120.00000;,
 -100.00000;500.00000;-80.00000;,
 100.00000;500.00000;-80.00000;,
 100.00000;500.00000;-120.00000;,
 -100.00000;500.00000;-120.00000;,
 -100.00000;500.00000;-80.00000;,
 -100.00000;500.00000;-120.00000;,
 -100.00000;0.00000;-120.00000;,
 -100.00000;0.00000;-80.00000;,
 -100.00000;500.00000;-80.00000;,
 -100.00000;0.00000;-80.00000;,
 100.00000;500.00000;-80.00000;,
 100.00000;0.00000;-80.00000;,
 100.00000;500.00000;-80.00000;,
 100.00000;0.00000;-80.00000;,
 100.00000;0.00000;-120.00000;,
 100.00000;500.00000;-120.00000;,
 -100.00000;0.00000;-80.00000;,
 -100.00000;0.00000;-120.00000;,
 100.00000;0.00000;-120.00000;,
 100.00000;0.00000;-80.00000;,
 -120.00000;500.00000;-80.00000;,
 -120.00000;0.00000;-80.00000;,
 -120.00000;500.00000;-60.00000;,
 -120.00000;500.00000;-80.00000;,
 -120.00000;0.00000;-80.00000;,
 -120.00000;0.00000;-60.00000;,
 120.00000;500.00000;-80.00000;,
 120.00000;0.00000;-80.00000;,
 120.00000;500.00000;-80.00000;,
 120.00000;500.00000;-60.00000;,
 120.00000;0.00000;-60.00000;,
 120.00000;0.00000;-80.00000;,
 120.00000;500.00000;80.00000;,
 120.00000;0.00000;80.00000;,
 120.00000;500.00000;60.00000;,
 120.00000;500.00000;80.00000;,
 120.00000;0.00000;80.00000;,
 120.00000;0.00000;60.00000;,
 -120.00000;0.00000;80.00000;,
 -120.00000;500.00000;80.00000;,
 -120.00000;500.00000;80.00000;,
 -120.00000;500.00000;60.00000;,
 -120.00000;0.00000;60.00000;,
 -120.00000;0.00000;80.00000;,
 -100.00000;515.00000;-50.00000;,
 -35.87050;515.00000;-50.00000;,
 -35.87050;500.00000;-50.00000;,
 -100.00000;500.00000;-50.00000;,
 -35.87050;515.00000;-50.00000;,
 -35.87050;515.00000;-16.08120;,
 -35.87050;500.00000;-16.08120;,
 -35.87050;500.00000;-50.00000;,
 -35.87050;515.00000;-16.08120;,
 -100.00000;515.00000;-16.08120;,
 -100.00000;500.00000;-16.08120;,
 -35.87050;500.00000;-16.08120;,
 -100.00000;515.00000;-16.08120;,
 -100.00000;515.00000;-50.00000;,
 -100.00000;500.00000;-50.00000;,
 -100.00000;500.00000;-16.08120;,
 -100.00000;500.00000;-50.00000;,
 -35.87050;500.00000;-50.00000;,
 -35.87050;500.00000;-16.08120;,
 -100.00000;500.00000;-16.08120;,
 -100.11410;515.00000;19.96460;,
 -35.98460;515.00000;19.96460;,
 -35.87050;500.00000;20.08660;,
 -100.00000;500.00000;20.08660;,
 -35.98460;515.00000;19.96460;,
 -35.98460;515.00000;53.88340;,
 -35.87050;500.00000;54.00530;,
 -35.87050;500.00000;20.08660;,
 -35.98460;515.00000;53.88340;,
 -100.11410;515.00000;53.88340;,
 -100.00000;500.00000;54.00530;,
 -35.87050;500.00000;54.00530;,
 -100.11410;515.00000;53.88340;,
 -100.11410;515.00000;19.96460;,
 -100.00000;500.00000;20.08660;,
 -100.00000;500.00000;54.00530;,
 -100.00000;500.00000;20.08660;,
 -35.87050;500.00000;20.08660;,
 -35.87050;500.00000;54.00530;,
 -100.00000;500.00000;54.00530;,
 -56.29150;518.05640;-24.70010;,
 -56.29150;518.05640;-41.38110;,
 -56.29150;514.35748;-41.38110;,
 -56.29150;514.35748;-24.70010;,
 -56.29150;518.05640;-41.38110;,
 -47.46880;518.05640;-41.38110;,
 -47.46880;514.35748;-41.38110;,
 -56.29150;514.35748;-41.38110;,
 -47.46880;518.05640;-41.38110;,
 -47.46880;518.05640;-24.70010;,
 -47.46880;514.35748;-24.70010;,
 -47.46880;514.35748;-41.38110;,
 -47.46880;518.05640;-24.70010;,
 -56.29150;518.05640;-24.70010;,
 -56.29150;514.35748;-24.70010;,
 -47.46880;514.35748;-24.70010;,
 -56.29150;514.35748;-24.70010;,
 -56.29150;514.35748;-41.38110;,
 -47.46880;514.35748;-41.38110;,
 -47.46880;514.35748;-24.70010;,
 -88.96060;518.05640;-24.70010;,
 -88.96060;518.05640;-41.38110;,
 -88.96060;514.35748;-41.38110;,
 -88.96060;514.35748;-24.70010;,
 -88.96060;518.05640;-41.38110;,
 -80.13770;518.05640;-41.38110;,
 -80.13770;514.35748;-41.38110;,
 -88.96060;514.35748;-41.38110;,
 -80.13770;518.05640;-41.38110;,
 -80.13770;518.05640;-24.70010;,
 -80.13770;514.35748;-24.70010;,
 -80.13770;514.35748;-41.38110;,
 -80.13770;518.05640;-24.70010;,
 -88.96060;518.05640;-24.70010;,
 -88.96060;514.35748;-24.70010;,
 -80.13770;514.35748;-24.70010;,
 -88.96060;514.35748;-24.70010;,
 -88.96060;514.35748;-41.38110;,
 -80.13770;514.35748;-41.38110;,
 -80.13770;514.35748;-24.70010;,
 -56.29150;518.05640;45.02490;,
 -56.29150;518.05640;28.34390;,
 -56.29150;514.35748;28.34390;,
 -56.29150;514.35748;45.02490;,
 -56.29150;518.05640;28.34390;,
 -47.46880;518.05640;28.34390;,
 -47.46880;514.35748;28.34390;,
 -56.29150;514.35748;28.34390;,
 -47.46880;518.05640;28.34390;,
 -47.46880;518.05640;45.02490;,
 -47.46880;514.35748;45.02490;,
 -47.46880;514.35748;28.34390;,
 -47.46880;518.05640;45.02490;,
 -56.29150;518.05640;45.02490;,
 -56.29150;514.35748;45.02490;,
 -47.46880;514.35748;45.02490;,
 -56.29150;514.35748;45.02490;,
 -56.29150;514.35748;28.34390;,
 -47.46880;514.35748;28.34390;,
 -47.46880;514.35748;45.02490;,
 -88.62690;518.05640;45.02490;,
 -88.62690;518.05640;28.34390;,
 -88.62690;514.35748;28.34390;,
 -88.62690;514.35748;45.02490;,
 -88.62690;518.05640;28.34390;,
 -79.80420;518.05640;28.34390;,
 -79.80420;514.35748;28.34390;,
 -88.62690;514.35748;28.34390;,
 -79.80420;518.05640;28.34390;,
 -79.80420;518.05640;45.02490;,
 -79.80420;514.35748;45.02490;,
 -79.80420;514.35748;28.34390;,
 -79.80420;518.05640;45.02490;,
 -88.62690;518.05640;45.02490;,
 -88.62690;514.35748;45.02490;,
 -79.80420;514.35748;45.02490;,
 -88.62690;514.35748;45.02490;,
 -88.62690;514.35748;28.34390;,
 -79.80420;514.35748;28.34390;,
 -79.80420;514.35748;45.02490;,
 35.00000;515.00000;-50.00000;,
 99.12950;515.00000;-50.00000;,
 99.12950;500.00000;-50.00000;,
 35.00000;500.00000;-50.00000;,
 99.12950;515.00000;-50.00000;,
 99.12950;515.00000;-16.08120;,
 99.12950;500.00000;-16.08120;,
 99.12950;500.00000;-50.00000;,
 99.12950;515.00000;-16.08120;,
 35.00000;515.00000;-16.08120;,
 35.00000;500.00000;-16.08120;,
 99.12950;500.00000;-16.08120;,
 35.00000;515.00000;-16.08120;,
 35.00000;515.00000;-50.00000;,
 35.00000;500.00000;-50.00000;,
 35.00000;500.00000;-16.08120;,
 35.00000;500.00000;-50.00000;,
 99.12950;500.00000;-50.00000;,
 99.12950;500.00000;-16.08120;,
 35.00000;500.00000;-16.08120;,
 34.88590;515.00000;19.96460;,
 99.01540;515.00000;19.96460;,
 99.12950;500.00000;20.08660;,
 35.00000;500.00000;20.08660;,
 99.01540;515.00000;19.96460;,
 99.01540;515.00000;53.88340;,
 99.12950;500.00000;54.00530;,
 99.12950;500.00000;20.08660;,
 99.01540;515.00000;53.88340;,
 34.88590;515.00000;53.88340;,
 35.00000;500.00000;54.00530;,
 99.12950;500.00000;54.00530;,
 34.88590;515.00000;53.88340;,
 34.88590;515.00000;19.96460;,
 35.00000;500.00000;20.08660;,
 35.00000;500.00000;54.00530;,
 35.00000;500.00000;20.08660;,
 99.12950;500.00000;20.08660;,
 99.12950;500.00000;54.00530;,
 35.00000;500.00000;54.00530;,
 78.70850;518.05640;-24.70010;,
 78.70850;518.05640;-41.38110;,
 78.70850;514.35748;-41.38110;,
 78.70850;514.35748;-24.70010;,
 78.70850;518.05640;-41.38110;,
 87.53120;518.05640;-41.38110;,
 87.53120;514.35748;-41.38110;,
 78.70850;514.35748;-41.38110;,
 87.53120;518.05640;-41.38110;,
 87.53120;518.05640;-24.70010;,
 87.53120;514.35748;-24.70010;,
 87.53120;514.35748;-41.38110;,
 87.53120;518.05640;-24.70010;,
 78.70850;518.05640;-24.70010;,
 78.70850;514.35748;-24.70010;,
 87.53120;514.35748;-24.70010;,
 78.70850;514.35748;-24.70010;,
 78.70850;514.35748;-41.38110;,
 87.53120;514.35748;-41.38110;,
 87.53120;514.35748;-24.70010;,
 46.03940;518.05640;-24.70010;,
 46.03940;518.05640;-41.38110;,
 46.03940;514.35748;-41.38110;,
 46.03940;514.35748;-24.70010;,
 46.03940;518.05640;-41.38110;,
 54.86230;518.05640;-41.38110;,
 54.86230;514.35748;-41.38110;,
 46.03940;514.35748;-41.38110;,
 54.86230;518.05640;-41.38110;,
 54.86230;518.05640;-24.70010;,
 54.86230;514.35748;-24.70010;,
 54.86230;514.35748;-41.38110;,
 54.86230;518.05640;-24.70010;,
 46.03940;518.05640;-24.70010;,
 46.03940;514.35748;-24.70010;,
 54.86230;514.35748;-24.70010;,
 46.03940;514.35748;-24.70010;,
 46.03940;514.35748;-41.38110;,
 54.86230;514.35748;-41.38110;,
 54.86230;514.35748;-24.70010;,
 78.70850;518.05640;45.02490;,
 78.70850;518.05640;28.34390;,
 78.70850;514.35748;28.34390;,
 78.70850;514.35748;45.02490;,
 78.70850;518.05640;28.34390;,
 87.53120;518.05640;28.34390;,
 87.53120;514.35748;28.34390;,
 78.70850;514.35748;28.34390;,
 87.53120;518.05640;28.34390;,
 87.53120;518.05640;45.02490;,
 87.53120;514.35748;45.02490;,
 87.53120;514.35748;28.34390;,
 87.53120;518.05640;45.02490;,
 78.70850;518.05640;45.02490;,
 78.70850;514.35748;45.02490;,
 87.53120;514.35748;45.02490;,
 78.70850;514.35748;45.02490;,
 78.70850;514.35748;28.34390;,
 87.53120;514.35748;28.34390;,
 87.53120;514.35748;45.02490;,
 46.37310;518.05640;45.02490;,
 46.37310;518.05640;28.34390;,
 46.37310;514.35748;28.34390;,
 46.37310;514.35748;45.02490;,
 46.37310;518.05640;28.34390;,
 55.19580;518.05640;28.34390;,
 55.19580;514.35748;28.34390;,
 46.37310;514.35748;28.34390;,
 55.19580;518.05640;28.34390;,
 55.19580;518.05640;45.02490;,
 55.19580;514.35748;45.02490;,
 55.19580;514.35748;28.34390;,
 55.19580;518.05640;45.02490;,
 46.37310;518.05640;45.02490;,
 46.37310;514.35748;45.02490;,
 55.19580;514.35748;45.02490;,
 46.37310;514.35748;45.02490;,
 46.37310;514.35748;28.34390;,
 55.19580;514.35748;28.34390;,
 55.19580;514.35748;45.02490;;
 
 126;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,11,10,25;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;28,31,32,33;,
 4;34,35,36,37;,
 4;34,37,38,39;,
 4;40,41,42,43;,
 4;40,43,14,13;,
 4;44,45,46,47;,
 4;44,47,9,8;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 4;54,55,56,57;,
 4;54,57,58,59;,
 4;60,12,15,61;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;64,67,10,9;,
 4;68,59,58,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,36,35;,
 4;80,15,14,81;,
 4;80,81,82,83;,
 4;84,8,11,85;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,50,49;,
 4;94,33,32,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;100,103,13,12;,
 4;84,104,44,8;,
 4;105,100,12,60;,
 4;106,107,108,109;,
 4;100,105,104,84;,
 4;24,110,85,11;,
 4;111,40,13,103;,
 4;85,110,111,103;,
 4;112,113,114,115;,
 4;67,116,25,10;,
 4;117,81,14,43;,
 4;118,119,120,121;,
 4;116,67,81,117;,
 4;122,61,15,80;,
 4;47,123,64,9;,
 4;64,123,122,80;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;161,157,156,152;,
 4;133,129,128,137;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;173,169,168,177;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;193,189,188,197;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;213,209,208,217;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;233,229,228,237;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;281,277,276,272;,
 4;253,249,248,257;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;293,289,288,297;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;316,317,318,319;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;313,309,308,317;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;336,337,338,339;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;333,329,328,337;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;353,349,348,357;;
 
 MeshMaterialList {
  5;
  126;
  1,
  1,
  0,
  3,
  2,
  2,
  0,
  0,
  1,
  1,
  1,
  1,
  3,
  3,
  0,
  0,
  1,
  1,
  1,
  1,
  3,
  3,
  0,
  0,
  1,
  2,
  2,
  1,
  3,
  3,
  0,
  0,
  2,
  1,
  1,
  2,
  3,
  3,
  0,
  3,
  4,
  3,
  0,
  3,
  3,
  4,
  0,
  3,
  4,
  3,
  3,
  0,
  3,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.524000;0.524000;0.524000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\glass001.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\glass001.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\concrete001.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\concrete001.jpg";
   }
  }
 }
 MeshNormals {
  19;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.008133;-0.999967;,
  0.999971;0.007607;0.000000;,
  0.000000;0.008126;0.999967;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.008133;-0.999967;,
  0.999971;0.007606;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999971;-0.007606;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.999971;-0.007607;0.000000;;
  126;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;16,16,16,16;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;11,11,11,11;,
  4;18,18,18,18;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  368;
  1.000000;2.013925;,
  0.000000;2.013925;,
  0.000000;-0.486075;,
  1.000000;-0.486075;,
  1.000000;2.013925;,
  1.000000;-0.486075;,
  0.000000;-0.486075;,
  0.000000;2.013925;,
  -1.991405;0.060322;,
  -1.991405;0.060322;,
  2.991405;0.060322;,
  2.991405;0.060322;,
  -1.991405;0.973161;,
  2.991405;0.973161;,
  2.991405;0.973161;,
  -1.991405;0.973161;,
  0.200000;-0.486000;,
  0.200000;2.014000;,
  0.800000;2.014000;,
  0.800000;-0.486000;,
  0.200000;-0.486000;,
  0.800000;-0.486000;,
  0.800000;2.014000;,
  0.200000;2.014000;,
  3.489686;0.060322;,
  3.489686;0.060322;,
  4.486248;0.060322;,
  4.486248;0.060322;,
  1.100000;-0.486075;,
  1.300000;-0.486075;,
  1.300000;2.013925;,
  1.100000;2.013925;,
  1.000000;2.013925;,
  1.000000;-0.486075;,
  1.100000;-0.486075;,
  1.000000;-0.486075;,
  1.000000;2.013925;,
  1.100000;2.013925;,
  1.300000;2.013925;,
  1.300000;-0.486075;,
  3.489686;0.973161;,
  4.486248;0.973161;,
  4.486248;0.973161;,
  3.489686;0.973161;,
  -2.489686;0.060322;,
  -3.486248;0.060322;,
  -3.486248;0.060322;,
  -2.489686;0.060322;,
  -0.100000;-0.486075;,
  0.000000;-0.486075;,
  0.000000;2.013925;,
  -0.100000;2.013925;,
  -0.300000;2.013925;,
  -0.300000;-0.486075;,
  -0.100000;-0.486075;,
  -0.300000;-0.486075;,
  -0.300000;2.013925;,
  -0.100000;2.013925;,
  0.000000;2.013925;,
  0.000000;-0.486075;,
  -2.489686;0.973161;,
  -2.489686;0.973161;,
  -3.486248;0.973161;,
  -3.486248;0.973161;,
  -1.991405;0.060322;,
  -1.991405;0.060322;,
  2.991405;0.060322;,
  2.991405;0.060322;,
  0.000000;-0.486075;,
  0.000000;2.013925;,
  0.900000;-0.486000;,
  0.900000;2.014000;,
  1.100000;2.014000;,
  1.100000;-0.486000;,
  0.900000;-0.486000;,
  1.100000;-0.486000;,
  1.100000;2.014000;,
  0.900000;2.014000;,
  1.000000;-0.486075;,
  1.000000;2.013925;,
  -1.991405;0.973161;,
  2.991405;0.973161;,
  2.991405;0.973161;,
  -1.991405;0.973161;,
  -1.991405;0.060322;,
  2.991405;0.060322;,
  2.991405;0.060322;,
  -1.991405;0.060322;,
  0.100000;-0.486000;,
  -0.100000;-0.486000;,
  -0.100000;2.014000;,
  0.100000;2.014000;,
  0.000000;-0.486075;,
  0.000000;2.013925;,
  1.000000;-0.486075;,
  1.000000;2.013925;,
  0.100000;-0.486000;,
  0.100000;2.014000;,
  -0.100000;2.014000;,
  -0.100000;-0.486000;,
  -1.991405;0.973161;,
  -1.991405;0.973161;,
  2.991405;0.973161;,
  2.991405;0.973161;,
  -2.489686;0.060322;,
  -2.489686;0.973161;,
  -0.992537;0.060424;,
  -1.490050;0.060424;,
  -1.490050;0.973165;,
  -0.992537;0.973165;,
  3.489686;0.060322;,
  3.489686;0.973161;,
  -1.490050;0.060424;,
  -0.992537;0.060424;,
  -0.992537;0.973165;,
  -1.490050;0.973165;,
  3.489686;0.060322;,
  3.489686;0.973161;,
  1.992537;0.060424;,
  2.490050;0.060424;,
  2.490050;0.973165;,
  1.992537;0.973165;,
  -2.489686;0.973161;,
  -2.489686;0.060322;,
  2.490050;0.060424;,
  1.992537;0.060424;,
  1.992537;0.973165;,
  2.490050;0.973165;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;,
  -0.000000;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  -0.000000;1.000000;,
  -1.974990;-0.000010;,
  -0.988440;-0.000010;,
  -0.988440;1.000050;,
  -1.974990;1.000050;,
  1.000000;-0.000000;,
  -0.000000;-0.000000;,
  -0.000000;1.000000;,
  1.000000;1.000000;,
  -1.004720;-0.000010;,
  -1.991260;-0.000010;,
  -1.991260;1.000050;,
  -1.004720;1.000050;,
  0.082550;0.001720;,
  0.301290;0.001720;,
  0.301290;0.001720;,
  0.082550;0.001720;;
 }
}
