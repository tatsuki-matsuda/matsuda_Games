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
 232;
 137.35201;0.00000;0.00000;,
 142.40376;6.97622;0.00000;,
 123.32528;6.97622;-71.20188;,
 118.95033;0.00000;-68.67600;,
 154.59987;9.86586;0.00000;,
 133.88737;9.86586;-77.29993;,
 166.79591;6.97622;0.00000;,
 144.44948;6.97622;-83.39796;,
 171.84769;-0.00000;-0.00000;,
 148.82442;-0.00000;-85.92384;,
 166.79591;-6.97622;-0.00000;,
 144.44948;-6.97622;-83.39796;,
 154.59987;-9.86586;-0.00000;,
 133.88737;-9.86586;-77.29993;,
 142.40376;-6.97622;-0.00000;,
 123.32528;-6.97622;-71.20188;,
 137.35201;0.00000;0.00000;,
 118.95033;0.00000;-68.67600;,
 71.20187;6.97622;-123.32528;,
 68.67600;0.00000;-118.95033;,
 77.29993;9.86586;-133.88737;,
 83.39794;6.97622;-144.44948;,
 85.92384;-0.00000;-148.82442;,
 83.39794;-6.97622;-144.44948;,
 77.29993;-9.86586;-133.88737;,
 71.20187;-6.97622;-123.32528;,
 68.67600;0.00000;-118.95033;,
 -0.00001;6.97622;-142.40376;,
 -0.00001;0.00000;-137.35201;,
 -0.00001;9.86586;-154.59987;,
 -0.00001;6.97622;-166.79591;,
 -0.00001;-0.00000;-171.84769;,
 -0.00001;-6.97622;-166.79591;,
 -0.00001;-9.86586;-154.59987;,
 -0.00001;-6.97622;-142.40376;,
 -0.00001;0.00000;-137.35201;,
 -71.20189;6.97622;-123.32526;,
 -68.67601;0.00000;-118.95030;,
 -77.29994;9.86586;-133.88736;,
 -83.39796;6.97622;-144.44946;,
 -85.92385;-0.00000;-148.82440;,
 -83.39796;-6.97622;-144.44946;,
 -77.29994;-9.86586;-133.88736;,
 -71.20189;-6.97622;-123.32526;,
 -68.67601;0.00000;-118.95030;,
 -123.32526;6.97622;-71.20189;,
 -118.95030;0.00000;-68.67601;,
 -133.88736;9.86586;-77.29994;,
 -144.44948;6.97622;-83.39796;,
 -148.82440;-0.00000;-85.92385;,
 -144.44948;-6.97622;-83.39796;,
 -133.88736;-9.86586;-77.29994;,
 -123.32526;-6.97622;-71.20189;,
 -118.95030;0.00000;-68.67601;,
 -142.40376;6.97622;-0.00002;,
 -137.35201;0.00000;-0.00002;,
 -154.59987;9.86586;-0.00002;,
 -166.79591;6.97622;-0.00003;,
 -171.84769;-0.00000;-0.00003;,
 -166.79591;-6.97622;-0.00003;,
 -154.59987;-9.86586;-0.00002;,
 -142.40376;-6.97622;-0.00002;,
 -137.35201;0.00000;-0.00002;,
 -123.32529;6.97622;71.20185;,
 -118.95033;0.00000;68.67597;,
 -133.88742;9.86586;77.29989;,
 -144.44952;6.97622;83.39793;,
 -148.82445;-0.00000;85.92382;,
 -144.44952;-6.97622;83.39793;,
 -133.88742;-9.86586;77.29989;,
 -123.32529;-6.97622;71.20185;,
 -118.95033;0.00000;68.67597;,
 -71.20194;6.97622;123.32526;,
 -68.67607;0.00000;118.95029;,
 -77.29998;9.86586;133.88736;,
 -83.39800;6.97622;144.44946;,
 -85.92388;-0.00000;148.82437;,
 -83.39800;-6.97622;144.44946;,
 -77.29998;-9.86586;133.88736;,
 -71.20194;-6.97622;123.32526;,
 -68.67607;0.00000;118.95029;,
 -0.00007;6.97622;142.40376;,
 -0.00006;0.00000;137.35201;,
 -0.00007;9.86586;154.59987;,
 -0.00008;6.97622;166.79591;,
 -0.00008;-0.00000;171.84769;,
 -0.00008;-6.97622;166.79591;,
 -0.00007;-9.86586;154.59987;,
 -0.00007;-6.97622;142.40376;,
 -0.00006;0.00000;137.35201;,
 71.20182;6.97622;123.32531;,
 68.67594;0.00000;118.95038;,
 77.29984;9.86586;133.88745;,
 83.39784;6.97622;144.44954;,
 85.92376;-0.00000;148.82448;,
 83.39784;-6.97622;144.44954;,
 77.29984;-9.86586;133.88745;,
 71.20182;-6.97622;123.32531;,
 68.67594;0.00000;118.95038;,
 123.32524;6.97622;71.20198;,
 118.95027;0.00000;68.67610;,
 133.88734;9.86586;77.30002;,
 144.44945;6.97622;83.39803;,
 148.82436;-0.00000;85.92391;,
 144.44945;-6.97622;83.39803;,
 133.88734;-9.86586;77.30002;,
 123.32524;-6.97622;71.20198;,
 118.95027;0.00000;68.67610;,
 142.40376;6.97622;0.00000;,
 137.35201;0.00000;0.00000;,
 154.59987;9.86586;0.00000;,
 166.79591;6.97622;0.00000;,
 171.84769;-0.00000;-0.00000;,
 166.79591;-6.97622;-0.00000;,
 154.59987;-9.86586;-0.00000;,
 142.40376;-6.97622;-0.00000;,
 137.35201;0.00000;0.00000;,
 0.00000;50.00000;0.00000;,
 9.56709;46.19397;-16.57068;,
 0.00000;46.19397;-19.13417;,
 0.00000;50.00000;0.00000;,
 16.57068;46.19397;-9.56709;,
 0.00000;50.00000;0.00000;,
 19.13417;46.19397;0.00000;,
 0.00000;50.00000;0.00000;,
 16.57068;46.19397;9.56709;,
 0.00000;50.00000;0.00000;,
 9.56709;46.19397;16.57068;,
 0.00000;50.00000;0.00000;,
 0.00000;46.19397;19.13417;,
 0.00000;50.00000;0.00000;,
 -9.56708;46.19397;16.57068;,
 0.00000;50.00000;0.00000;,
 -16.57068;46.19397;9.56709;,
 0.00000;50.00000;0.00000;,
 -19.13417;46.19397;0.00001;,
 0.00000;50.00000;0.00000;,
 -16.57069;46.19397;-9.56708;,
 0.00000;50.00000;0.00000;,
 -9.56710;46.19397;-16.57067;,
 0.00000;50.00000;0.00000;,
 0.00000;46.19397;-19.13417;,
 17.67767;35.35534;-30.61862;,
 0.00000;35.35534;-35.35534;,
 30.61862;35.35534;-17.67767;,
 35.35534;35.35534;0.00000;,
 30.61862;35.35534;17.67767;,
 17.67767;35.35534;30.61862;,
 0.00001;35.35534;35.35534;,
 -17.67766;35.35534;30.61863;,
 -30.61861;35.35534;17.67768;,
 -35.35534;35.35534;0.00002;,
 -30.61863;35.35534;-17.67765;,
 -17.67769;35.35534;-30.61861;,
 0.00000;35.35534;-35.35534;,
 23.09699;19.13417;-40.00516;,
 0.00000;19.13417;-46.19397;,
 40.00516;19.13417;-23.09699;,
 46.19397;19.13417;0.00000;,
 40.00515;19.13417;23.09699;,
 23.09699;19.13417;40.00516;,
 0.00001;19.13417;46.19397;,
 -23.09698;19.13417;40.00516;,
 -40.00515;19.13417;23.09700;,
 -46.19397;19.13417;0.00002;,
 -40.00517;19.13417;-23.09697;,
 -23.09702;19.13417;-40.00514;,
 0.00000;19.13417;-46.19397;,
 25.00000;-0.00000;-43.30127;,
 0.00000;-0.00000;-50.00000;,
 43.30127;-0.00000;-25.00000;,
 50.00000;-0.00000;0.00000;,
 43.30127;-0.00000;25.00000;,
 25.00000;-0.00000;43.30127;,
 0.00001;-0.00000;50.00000;,
 -24.99999;-0.00000;43.30128;,
 -43.30126;-0.00000;25.00002;,
 -50.00000;-0.00000;0.00002;,
 -43.30128;-0.00000;-24.99998;,
 -25.00003;-0.00000;-43.30125;,
 0.00000;-0.00000;-50.00000;,
 23.09699;-19.13418;-40.00516;,
 0.00000;-19.13418;-46.19397;,
 40.00516;-19.13418;-23.09699;,
 46.19397;-19.13418;0.00000;,
 40.00515;-19.13418;23.09699;,
 23.09699;-19.13418;40.00516;,
 0.00001;-19.13418;46.19397;,
 -23.09698;-19.13418;40.00516;,
 -40.00515;-19.13418;23.09700;,
 -46.19397;-19.13418;0.00002;,
 -40.00517;-19.13418;-23.09697;,
 -23.09702;-19.13418;-40.00514;,
 0.00000;-19.13418;-46.19397;,
 17.67767;-35.35534;-30.61862;,
 0.00000;-35.35534;-35.35534;,
 30.61862;-35.35534;-17.67767;,
 35.35534;-35.35534;0.00000;,
 30.61862;-35.35534;17.67767;,
 17.67767;-35.35534;30.61862;,
 0.00001;-35.35534;35.35534;,
 -17.67766;-35.35534;30.61863;,
 -30.61861;-35.35534;17.67768;,
 -35.35534;-35.35534;0.00002;,
 -30.61863;-35.35534;-17.67765;,
 -17.67769;-35.35534;-30.61861;,
 0.00000;-35.35534;-35.35534;,
 9.56709;-46.19397;-16.57068;,
 0.00000;-46.19397;-19.13417;,
 16.57068;-46.19397;-9.56709;,
 19.13417;-46.19397;0.00000;,
 16.57068;-46.19397;9.56709;,
 9.56709;-46.19397;16.57068;,
 0.00000;-46.19397;19.13417;,
 -9.56708;-46.19397;16.57068;,
 -16.57068;-46.19397;9.56709;,
 -19.13417;-46.19397;0.00001;,
 -16.57069;-46.19397;-9.56708;,
 -9.56710;-46.19397;-16.57067;,
 0.00000;-46.19397;-19.13417;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;,
 0.00000;-50.00000;-0.00000;;
 
 192;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;55,54,63,64;,
 4;54,56,65,63;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;64,63,72,73;,
 4;63,65,74,72;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;73,72,81,82;,
 4;72,74,83,81;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;79,80,89,88;,
 4;82,81,90,91;,
 4;81,83,92,90;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;88,89,98,97;,
 4;91,90,99,100;,
 4;90,92,101,99;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;100,99,108,109;,
 4;99,101,110,108;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 3;117,118,119;,
 3;120,121,118;,
 3;122,123,121;,
 3;124,125,123;,
 3;126,127,125;,
 3;128,129,127;,
 3;130,131,129;,
 3;132,133,131;,
 3;134,135,133;,
 3;136,137,135;,
 3;138,139,137;,
 3;140,141,139;,
 4;119,118,142,143;,
 4;118,121,144,142;,
 4;121,123,145,144;,
 4;123,125,146,145;,
 4;125,127,147,146;,
 4;127,129,148,147;,
 4;129,131,149,148;,
 4;131,133,150,149;,
 4;133,135,151,150;,
 4;135,137,152,151;,
 4;137,139,153,152;,
 4;139,141,154,153;,
 4;143,142,155,156;,
 4;142,144,157,155;,
 4;144,145,158,157;,
 4;145,146,159,158;,
 4;146,147,160,159;,
 4;147,148,161,160;,
 4;148,149,162,161;,
 4;149,150,163,162;,
 4;150,151,164,163;,
 4;151,152,165,164;,
 4;152,153,166,165;,
 4;153,154,167,166;,
 4;156,155,168,169;,
 4;155,157,170,168;,
 4;157,158,171,170;,
 4;158,159,172,171;,
 4;159,160,173,172;,
 4;160,161,174,173;,
 4;161,162,175,174;,
 4;162,163,176,175;,
 4;163,164,177,176;,
 4;164,165,178,177;,
 4;165,166,179,178;,
 4;166,167,180,179;,
 4;169,168,181,182;,
 4;168,170,183,181;,
 4;170,171,184,183;,
 4;171,172,185,184;,
 4;172,173,186,185;,
 4;173,174,187,186;,
 4;174,175,188,187;,
 4;175,176,189,188;,
 4;176,177,190,189;,
 4;177,178,191,190;,
 4;178,179,192,191;,
 4;179,180,193,192;,
 4;182,181,194,195;,
 4;181,183,196,194;,
 4;183,184,197,196;,
 4;184,185,198,197;,
 4;185,186,199,198;,
 4;186,187,200,199;,
 4;187,188,201,200;,
 4;188,189,202,201;,
 4;189,190,203,202;,
 4;190,191,204,203;,
 4;191,192,205,204;,
 4;192,193,206,205;,
 4;195,194,207,208;,
 4;194,196,209,207;,
 4;196,197,210,209;,
 4;197,198,211,210;,
 4;198,199,212,211;,
 4;199,200,213,212;,
 4;200,201,214,213;,
 4;201,202,215,214;,
 4;202,203,216,215;,
 4;203,204,217,216;,
 4;204,205,218,217;,
 4;205,206,219,218;,
 3;208,207,220;,
 3;207,209,221;,
 3;209,210,222;,
 3;210,211,223;,
 3;211,212,224;,
 3;212,213,225;,
 3;213,214,226;,
 3;214,215,227;,
 3;215,216,228;,
 3;216,217,229;,
 3;217,218,230;,
 3;218,219,231;;
 
 MeshMaterialList {
  2;
  192;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.720000;0.694588;0.705882;1.000000;;
   5.000000;
   0.420000;0.420000;0.420000;;
   0.230000;0.221882;0.225490;;
  }
  Material {
   0.081569;0.266667;0.338824;1.000000;;
   17.000000;
   0.600000;0.600000;0.600000;;
   0.014275;0.046667;0.059294;;
  }
 }
 MeshNormals {
  206;
  -0.809941;0.586511;-0.000000;,
  -0.551721;0.834029;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.551722;0.834028;0.000000;,
  0.809942;0.586511;0.000000;,
  0.551722;-0.834028;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.551721;-0.834029;-0.000000;,
  -0.701430;0.586511;0.404971;,
  -0.477805;0.834029;0.275861;,
  0.000000;1.000000;-0.000000;,
  0.477805;0.834028;-0.275861;,
  0.701429;0.586511;-0.404971;,
  0.477805;-0.834029;-0.275861;,
  0.000000;-1.000000;-0.000000;,
  -0.477805;-0.834029;0.275861;,
  -0.404971;0.586511;0.701430;,
  -0.275861;0.834029;0.477805;,
  0.000000;1.000000;-0.000000;,
  0.275861;0.834029;-0.477805;,
  0.404971;0.586511;-0.701429;,
  0.275861;-0.834029;-0.477805;,
  0.000000;-1.000000;-0.000000;,
  -0.275861;-0.834029;0.477805;,
  0.000000;0.586511;0.809941;,
  0.000000;0.834029;0.551721;,
  0.000000;1.000000;-0.000000;,
  -0.000000;0.834029;-0.551721;,
  -0.000000;0.586511;-0.809941;,
  -0.000000;-0.834029;-0.551721;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.834029;0.551721;,
  0.404970;0.586511;0.701429;,
  0.275861;0.834029;0.477804;,
  -0.000000;1.000000;-0.000000;,
  -0.275861;0.834028;-0.477805;,
  -0.404971;0.586511;-0.701430;,
  -0.275861;-0.834028;-0.477805;,
  -0.000000;-1.000000;-0.000000;,
  0.275861;-0.834029;0.477804;,
  0.701429;0.586511;0.404970;,
  0.477804;0.834029;0.275861;,
  -0.000000;1.000000;-0.000000;,
  -0.477805;0.834028;-0.275861;,
  -0.701430;0.586510;-0.404971;,
  -0.477805;-0.834028;-0.275861;,
  -0.000000;-1.000000;-0.000000;,
  0.477804;-0.834029;0.275861;,
  0.809941;0.586511;0.000000;,
  0.551721;0.834029;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.551722;0.834028;-0.000000;,
  -0.809941;0.586511;-0.000000;,
  -0.551722;-0.834028;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.551721;-0.834029;0.000000;,
  0.701430;0.586511;-0.404970;,
  0.477804;0.834029;-0.275860;,
  -0.000000;1.000000;0.000000;,
  -0.477805;0.834028;0.275861;,
  -0.701430;0.586510;0.404971;,
  -0.477805;-0.834028;0.275861;,
  -0.000000;-1.000000;0.000000;,
  0.477804;-0.834029;-0.275860;,
  0.404971;0.586511;-0.701429;,
  0.275861;0.834029;-0.477804;,
  -0.000000;1.000000;0.000000;,
  -0.275861;0.834028;0.477805;,
  -0.404971;0.586510;0.701430;,
  -0.275861;-0.834028;0.477805;,
  -0.000000;-1.000000;0.000000;,
  0.275861;-0.834029;-0.477804;,
  0.000000;0.586511;-0.809941;,
  0.000000;0.834029;-0.551721;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.834028;0.551722;,
  -0.000001;0.586511;0.809941;,
  -0.000000;-0.834028;0.551722;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.834029;-0.551721;,
  -0.404970;0.586511;-0.701430;,
  -0.275860;0.834028;-0.477805;,
  0.000000;1.000000;0.000000;,
  0.275861;0.834028;0.477805;,
  0.404970;0.586511;0.701430;,
  0.275861;-0.834028;0.477805;,
  0.000000;-1.000000;0.000000;,
  -0.275860;-0.834029;-0.477805;,
  -0.701429;0.586511;-0.404971;,
  -0.477804;0.834029;-0.275861;,
  0.000000;1.000000;0.000000;,
  0.477805;0.834028;0.275861;,
  0.701430;0.586510;0.404971;,
  0.477805;-0.834028;0.275861;,
  0.000000;-1.000000;0.000000;,
  -0.477804;-0.834029;-0.275861;,
  0.809942;-0.586511;0.000000;,
  0.701429;-0.586511;-0.404971;,
  -0.809941;-0.586511;-0.000000;,
  -0.701430;-0.586511;0.404971;,
  0.404971;-0.586511;-0.701429;,
  -0.404971;-0.586511;0.701430;,
  -0.000000;-0.586511;-0.809941;,
  0.000000;-0.586511;0.809941;,
  -0.404971;-0.586511;-0.701430;,
  0.404970;-0.586511;0.701429;,
  -0.701430;-0.586510;-0.404971;,
  0.701429;-0.586511;0.404970;,
  -0.809942;-0.586511;-0.000000;,
  0.809941;-0.586511;0.000000;,
  -0.701430;-0.586510;0.404971;,
  0.701430;-0.586511;-0.404970;,
  -0.404971;-0.586510;0.701430;,
  0.404971;-0.586511;-0.701429;,
  -0.000001;-0.586511;0.809941;,
  0.000000;-0.586511;-0.809941;,
  0.404970;-0.586511;0.701430;,
  -0.404970;-0.586511;-0.701430;,
  0.701430;-0.586510;0.404971;,
  -0.701429;-0.586511;-0.404971;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.924244;-0.381802;,
  0.190901;0.924244;-0.330650;,
  0.330650;0.924244;-0.190901;,
  0.381802;0.924244;0.000000;,
  0.330650;0.924244;0.190901;,
  0.190901;0.924244;0.330650;,
  0.000000;0.924244;0.381802;,
  -0.190901;0.924244;0.330650;,
  -0.330650;0.924244;0.190901;,
  -0.381802;0.924244;0.000000;,
  -0.330650;0.924244;-0.190901;,
  -0.190901;0.924244;-0.330650;,
  -0.000000;0.708039;-0.706173;,
  0.353087;0.708039;-0.611564;,
  0.611564;0.708039;-0.353087;,
  0.706174;0.708039;0.000000;,
  0.611564;0.708039;0.353087;,
  0.353087;0.708039;0.611564;,
  0.000000;0.708039;0.706174;,
  -0.353087;0.708039;0.611564;,
  -0.611564;0.708039;0.353087;,
  -0.706174;0.708039;0.000000;,
  -0.611564;0.708039;-0.353086;,
  -0.353087;0.708039;-0.611564;,
  -0.000000;0.383526;-0.923530;,
  0.461765;0.383526;-0.799801;,
  0.799801;0.383526;-0.461765;,
  0.923530;0.383526;0.000000;,
  0.799801;0.383526;0.461765;,
  0.461765;0.383526;0.799801;,
  0.000000;0.383526;0.923530;,
  -0.461765;0.383526;0.799801;,
  -0.799800;0.383526;0.461765;,
  -0.923530;0.383526;0.000000;,
  -0.799801;0.383526;-0.461765;,
  -0.461765;0.383526;-0.799800;,
  -0.000000;0.000000;-1.000000;,
  0.500000;0.000000;-0.866025;,
  0.866025;0.000000;-0.500000;,
  1.000000;0.000000;0.000000;,
  0.866025;0.000000;0.500000;,
  0.500000;0.000000;0.866025;,
  0.000000;0.000000;1.000000;,
  -0.500000;0.000000;0.866025;,
  -0.866025;0.000000;0.500000;,
  -1.000000;0.000000;0.000000;,
  -0.866026;0.000000;-0.499999;,
  -0.500000;0.000000;-0.866025;,
  -0.000000;-0.383526;-0.923530;,
  0.461765;-0.383526;-0.799801;,
  0.799801;-0.383526;-0.461765;,
  0.923530;-0.383526;0.000000;,
  0.799801;-0.383526;0.461765;,
  0.461765;-0.383526;0.799801;,
  0.000000;-0.383526;0.923530;,
  -0.461765;-0.383526;0.799801;,
  -0.799800;-0.383526;0.461765;,
  -0.923530;-0.383526;0.000000;,
  -0.799801;-0.383526;-0.461765;,
  -0.461765;-0.383526;-0.799800;,
  -0.000000;-0.708039;-0.706173;,
  0.353087;-0.708039;-0.611564;,
  0.611564;-0.708039;-0.353087;,
  0.706173;-0.708039;0.000000;,
  0.611564;-0.708039;0.353087;,
  0.353087;-0.708039;0.611564;,
  0.000000;-0.708039;0.706173;,
  -0.353087;-0.708039;0.611564;,
  -0.611564;-0.708039;0.353087;,
  -0.706173;-0.708039;0.000000;,
  -0.611564;-0.708039;-0.353086;,
  -0.353087;-0.708039;-0.611564;,
  -0.000000;-0.924244;-0.381802;,
  0.190901;-0.924244;-0.330650;,
  0.330650;-0.924244;-0.190901;,
  0.381802;-0.924244;0.000000;,
  0.330650;-0.924244;0.190901;,
  0.190901;-0.924244;0.330650;,
  0.000000;-0.924244;0.381802;,
  -0.190901;-0.924244;0.330650;,
  -0.330650;-0.924244;0.190901;,
  -0.381802;-0.924244;0.000000;,
  -0.330650;-0.924244;-0.190901;,
  -0.190901;-0.924244;-0.330650;,
  -0.000000;-1.000000;0.000000;;
  192;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;96,5,13,97;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,98,99,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;97,13,21,100;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,99,101,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;100,21,29,102;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,101,103,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;102,29,37,104;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,103,105,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;104,37,45,106;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,105,107,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;106,45,53,108;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,107,109,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;108,53,61,110;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,109,111,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;110,61,69,112;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,111,113,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;112,69,77,114;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,113,115,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;114,77,85,116;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,115,117,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;116,85,93,118;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,117,119,95;,
  4;88,89,1,0;,
  4;89,90,2,1;,
  4;90,91,3,2;,
  4;91,92,4,3;,
  4;118,93,5,96;,
  4;93,94,6,5;,
  4;94,95,7,6;,
  4;95,119,98,7;,
  3;120,122,121;,
  3;120,123,122;,
  3;120,124,123;,
  3;120,125,124;,
  3;120,126,125;,
  3;120,127,126;,
  3;120,128,127;,
  3;120,129,128;,
  3;120,130,129;,
  3;120,131,130;,
  3;120,132,131;,
  3;120,121,132;,
  4;121,122,134,133;,
  4;122,123,135,134;,
  4;123,124,136,135;,
  4;124,125,137,136;,
  4;125,126,138,137;,
  4;126,127,139,138;,
  4;127,128,140,139;,
  4;128,129,141,140;,
  4;129,130,142,141;,
  4;130,131,143,142;,
  4;131,132,144,143;,
  4;132,121,133,144;,
  4;133,134,146,145;,
  4;134,135,147,146;,
  4;135,136,148,147;,
  4;136,137,149,148;,
  4;137,138,150,149;,
  4;138,139,151,150;,
  4;139,140,152,151;,
  4;140,141,153,152;,
  4;141,142,154,153;,
  4;142,143,155,154;,
  4;143,144,156,155;,
  4;144,133,145,156;,
  4;145,146,158,157;,
  4;146,147,159,158;,
  4;147,148,160,159;,
  4;148,149,161,160;,
  4;149,150,162,161;,
  4;150,151,163,162;,
  4;151,152,164,163;,
  4;152,153,165,164;,
  4;153,154,166,165;,
  4;154,155,167,166;,
  4;155,156,168,167;,
  4;156,145,157,168;,
  4;157,158,170,169;,
  4;158,159,171,170;,
  4;159,160,172,171;,
  4;160,161,173,172;,
  4;161,162,174,173;,
  4;162,163,175,174;,
  4;163,164,176,175;,
  4;164,165,177,176;,
  4;165,166,178,177;,
  4;166,167,179,178;,
  4;167,168,180,179;,
  4;168,157,169,180;,
  4;169,170,182,181;,
  4;170,171,183,182;,
  4;171,172,184,183;,
  4;172,173,185,184;,
  4;173,174,186,185;,
  4;174,175,187,186;,
  4;175,176,188,187;,
  4;176,177,189,188;,
  4;177,178,190,189;,
  4;178,179,191,190;,
  4;179,180,192,191;,
  4;180,169,181,192;,
  4;181,182,194,193;,
  4;182,183,195,194;,
  4;183,184,196,195;,
  4;184,185,197,196;,
  4;185,186,198,197;,
  4;186,187,199,198;,
  4;187,188,200,199;,
  4;188,189,201,200;,
  4;189,190,202,201;,
  4;190,191,203,202;,
  4;191,192,204,203;,
  4;192,181,193,204;,
  3;193,194,205;,
  3;194,195,205;,
  3;195,196,205;,
  3;196,197,205;,
  3;197,198,205;,
  3;198,199,205;,
  3;199,200,205;,
  3;200,201,205;,
  3;201,202,205;,
  3;202,203,205;,
  3;203,204,205;,
  3;204,193,205;;
 }
 MeshTextureCoords {
  232;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.083333;0.125000;,
  0.083333;0.000000;,
  0.000000;0.250000;,
  0.083333;0.250000;,
  0.000000;0.375000;,
  0.083333;0.375000;,
  0.000000;0.500000;,
  0.083333;0.500000;,
  0.000000;0.625000;,
  0.083333;0.625000;,
  0.000000;0.750000;,
  0.083333;0.750000;,
  0.000000;0.875000;,
  0.083333;0.875000;,
  0.000000;1.000000;,
  0.083333;1.000000;,
  0.166667;0.125000;,
  0.166667;0.000000;,
  0.166667;0.250000;,
  0.166667;0.375000;,
  0.166667;0.500000;,
  0.166667;0.625000;,
  0.166667;0.750000;,
  0.166667;0.875000;,
  0.166667;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.333333;0.125000;,
  0.333333;0.000000;,
  0.333333;0.250000;,
  0.333333;0.375000;,
  0.333333;0.500000;,
  0.333333;0.625000;,
  0.333333;0.750000;,
  0.333333;0.875000;,
  0.333333;1.000000;,
  0.416667;0.125000;,
  0.416667;0.000000;,
  0.416667;0.250000;,
  0.416667;0.375000;,
  0.416667;0.500000;,
  0.416667;0.625000;,
  0.416667;0.750000;,
  0.416667;0.875000;,
  0.416667;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.583333;0.125000;,
  0.583333;0.000000;,
  0.583333;0.250000;,
  0.583333;0.375000;,
  0.583333;0.500000;,
  0.583333;0.625000;,
  0.583333;0.750000;,
  0.583333;0.875000;,
  0.583333;1.000000;,
  0.666667;0.125000;,
  0.666667;0.000000;,
  0.666667;0.250000;,
  0.666667;0.375000;,
  0.666667;0.500000;,
  0.666667;0.625000;,
  0.666667;0.750000;,
  0.666667;0.875000;,
  0.666667;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.833333;0.125000;,
  0.833333;0.000000;,
  0.833333;0.250000;,
  0.833333;0.375000;,
  0.833333;0.500000;,
  0.833333;0.625000;,
  0.833333;0.750000;,
  0.833333;0.875000;,
  0.833333;1.000000;,
  0.916667;0.125000;,
  0.916667;0.000000;,
  0.916667;0.250000;,
  0.916667;0.375000;,
  0.916667;0.500000;,
  0.916667;0.625000;,
  0.916667;0.750000;,
  0.916667;0.875000;,
  0.916667;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.041667;0.000000;,
  0.083333;0.125000;,
  0.000000;0.125000;,
  0.125000;0.000000;,
  0.166667;0.125000;,
  0.208333;0.000000;,
  0.250000;0.125000;,
  0.291667;0.000000;,
  0.333333;0.125000;,
  0.375000;0.000000;,
  0.416667;0.125000;,
  0.458333;0.000000;,
  0.500000;0.125000;,
  0.541667;0.000000;,
  0.583333;0.125000;,
  0.625000;0.000000;,
  0.666667;0.125000;,
  0.708333;0.000000;,
  0.750000;0.125000;,
  0.791667;0.000000;,
  0.833333;0.125000;,
  0.875000;0.000000;,
  0.916667;0.125000;,
  0.958333;0.000000;,
  1.000000;0.125000;,
  0.083333;0.250000;,
  0.000000;0.250000;,
  0.166667;0.250000;,
  0.250000;0.250000;,
  0.333333;0.250000;,
  0.416667;0.250000;,
  0.500000;0.250000;,
  0.583333;0.250000;,
  0.666667;0.250000;,
  0.750000;0.250000;,
  0.833333;0.250000;,
  0.916667;0.250000;,
  1.000000;0.250000;,
  0.083333;0.375000;,
  0.000000;0.375000;,
  0.166667;0.375000;,
  0.250000;0.375000;,
  0.333333;0.375000;,
  0.416667;0.375000;,
  0.500000;0.375000;,
  0.583333;0.375000;,
  0.666667;0.375000;,
  0.750000;0.375000;,
  0.833333;0.375000;,
  0.916667;0.375000;,
  1.000000;0.375000;,
  0.083333;0.500000;,
  0.000000;0.500000;,
  0.166667;0.500000;,
  0.250000;0.500000;,
  0.333333;0.500000;,
  0.416667;0.500000;,
  0.500000;0.500000;,
  0.583333;0.500000;,
  0.666667;0.500000;,
  0.750000;0.500000;,
  0.833333;0.500000;,
  0.916667;0.500000;,
  1.000000;0.500000;,
  0.083333;0.625000;,
  0.000000;0.625000;,
  0.166667;0.625000;,
  0.250000;0.625000;,
  0.333333;0.625000;,
  0.416667;0.625000;,
  0.500000;0.625000;,
  0.583333;0.625000;,
  0.666667;0.625000;,
  0.750000;0.625000;,
  0.833333;0.625000;,
  0.916667;0.625000;,
  1.000000;0.625000;,
  0.083333;0.750000;,
  0.000000;0.750000;,
  0.166667;0.750000;,
  0.250000;0.750000;,
  0.333333;0.750000;,
  0.416667;0.750000;,
  0.500000;0.750000;,
  0.583333;0.750000;,
  0.666667;0.750000;,
  0.750000;0.750000;,
  0.833333;0.750000;,
  0.916667;0.750000;,
  1.000000;0.750000;,
  0.083333;0.875000;,
  0.000000;0.875000;,
  0.166667;0.875000;,
  0.250000;0.875000;,
  0.333333;0.875000;,
  0.416667;0.875000;,
  0.500000;0.875000;,
  0.583333;0.875000;,
  0.666667;0.875000;,
  0.750000;0.875000;,
  0.833333;0.875000;,
  0.916667;0.875000;,
  1.000000;0.875000;,
  0.041667;1.000000;,
  0.125000;1.000000;,
  0.208333;1.000000;,
  0.291667;1.000000;,
  0.375000;1.000000;,
  0.458333;1.000000;,
  0.541667;1.000000;,
  0.625000;1.000000;,
  0.708333;1.000000;,
  0.791667;1.000000;,
  0.875000;1.000000;,
  0.958333;1.000000;;
 }
}