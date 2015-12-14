//=============================================================================
// DX ���C�u�������g�p�������f���r���[�A�̃T���v��
//-----------------------------------------------------------------------------
//=============================================================================

#include <DxLib.h>
#include <LuminoMathDxLib.h>
#include "../Common.h"
using namespace Lumino;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	
		return -1;

	SetCameraNearFar(1.0f, 150.0f);

	int model = MV1LoadModel(LOCAL_RESOURCE("model.x"));

	Quaternion modelRot;	// ���f���̉�]�p��
	int lastMouseX = -1;	// �}�E�X�h���b�O�ʂ𒲂ׂ邽�߂̕ϐ� (�O��̃N���b�N�ʒu)
	int lastMouseY = -1;	// �}�E�X�h���b�O�ʂ𒲂ׂ邽�߂̕ϐ� (�O��̃N���b�N�ʒu)
	float cameraZ = -5.0f;	// �J�����̑O��ʒu

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//-----------------------------------------------------
		// �}�E�X�ړ��ʂ����]�p�����X�V

		int mouseState = GetMouseInput();
		if (mouseState & MOUSE_INPUT_LEFT)
		{
			int mouseX, mouseY;
			GetMousePoint(&mouseX, &mouseY);

			if (lastMouseX >= 0)
			{
				// �O��̃}�E�XX���W�Ƃ̍������p�x�Ƃ��āA���݂̎p����Y������ŉ�]����
				modelRot.RotateY(0.01f * (lastMouseX - mouseX));
			}
			
			if (lastMouseY >= 0)
			{
				// �O��̃}�E�XY���W�Ƃ̍������p�x�Ƃ��āA���݂̎p����X������ŉ�]����
				modelRot.RotateX(0.01f * (lastMouseY - mouseY));
			}
			
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}
		else
		{
			// �}�E�X�h���b�O����
			lastMouseX = -1;
			lastMouseY = -1;
		}

		// �J�����ʒu�̓}�E�X�z�C�[���̈ړ��ʂ���K���ɐݒ�
		cameraZ += GetMouseWheelRotVol();


		//-----------------------------------------------------
		// �`�揈��

		ClearDrawScreen();

		// �J�����ʒu�̐ݒ�
		SetCameraPositionAndTargetAndUpVec(
			VGet(0, 0, cameraZ),
			VGet(0, 0, 0),
			VGet(0, 1, 0));

		// �N�H�[�^�j�I��(��]�p��)���s��ɕϊ����ă��f���ɐݒ�A�`�悷��
		Matrix modelMat = Matrix::RotationQuaternion(modelRot);
		MV1SetMatrix(model, modelMat);
		MV1DrawModel(model);

		// info
		DrawString(0, 0, "�}�E�X���h���b�O�Ń��f������]���܂��B", GetColor(255, 255, 255));
		DrawString(0, 16, "�}�E�X�z�C�[���ŃJ������O��Ɉړ����܂��B", GetColor(255, 255, 255));

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}