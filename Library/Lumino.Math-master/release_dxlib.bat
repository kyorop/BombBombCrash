mkdir "LuminoMath_x.x.x_DxLib_VC"
mkdir "LuminoMath_x.x.x_DxLib_VC\�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p"
mkdir "LuminoMath_x.x.x_DxLib_VC\help"
mkdir "LuminoMath_x.x.x_DxLib_VC\sample"

xcopy "lib\*.lib" "LuminoMath_x.x.x_DxLib_VC\�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p" /s /i /y
xcopy "lib\*.dll" "LuminoMath_x.x.x_DxLib_VC\�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p" /s /i /y
xcopy "include\*" "LuminoMath_x.x.x_DxLib_VC\�v���W�F�N�g�ɒǉ����ׂ��t�@�C��_VC�p" /s /i /y

xcopy "doc\html"                 "LuminoMath_x.x.x_DxLib_VC\help" /s /i /y
copy  "doc\src\ReadMe_DxLib.txt" "LuminoMath_x.x.x_DxLib_VC"

copy  "sample\Common.h"			"LuminoMath_x.x.x_DxLib_VC\sample\Common.h"
xcopy "sample\DxLibFlightSim"	"LuminoMath_x.x.x_DxLib_VC\sample\DxLibFlightSim" /s /i /y
xcopy "sample\DxLibModelViewer"	"LuminoMath_x.x.x_DxLib_VC\sample\DxLibModelViewer" /s /i /y

pause
