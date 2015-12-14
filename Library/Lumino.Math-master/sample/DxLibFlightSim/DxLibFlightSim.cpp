//=============================================================================
// DX ���C�u�������g�p�����t���C�g�V�~�����[�^�̃T���v��
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

	int playerModel = MV1LoadModel(LOCAL_RESOURCE("Plane1.x"));
	int skyModel = MV1LoadModel(LOCAL_RESOURCE("BG_Sky1.x"));
	int groundModel = MV1LoadModel(LOCAL_RESOURCE("Ground1.x"));

	SetCameraNearFar(1.0f, 10000.0f);
	SetupCamera_Perspective(Math::PI / 2);

	Quaternion playerRot;			// ���@�̉�]���
	Vector3 playerPos;				// ���@�̈ʒu
	float velocity = 5.0f;			// ���@�̑��x
	float rotVelocity = 0.02f;		// ���@�̉�]���x

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//-----------------------------------------------------
		// ���@�̎p���X�V

		// �� �L�[
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			// �s�b�`�͎��@�����_�ɂ���Ƃ���ƁAX������A�܂�E����������Ƃ�����]�ƍl���邱�Ƃ��ł���B
			// X ����\���x�N�g���� (1, 0, 0) �ŁAVector3::UnitX �萔�������\���B
			// ���̃x�N�g�������@�̌��݂̉�]�p�� (playerRot) �ō��W�ϊ�����ƁA
			// ���݂̎p�����猩���E��������킩��B����� axis �Ƃ���B
			Vector3 axis = Vector3::Transform(Vector3::UnitX, playerRot);

			// ����ꂽ�E����������Ƃ��āA-rotVelocity (���W�A���P��) ���A
			// ���݂̉�]�p��������ɉ�]������B
			playerRot.RotateAxis(axis, -rotVelocity);
		}
		// �� �L�[
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			Vector3 axis = Vector3::Transform(Vector3::UnitX, playerRot);
			playerRot.RotateAxis(axis, rotVelocity);
		}
		// �� �L�[
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			// ���[���͎��@�����_�ɂ���Ƃ���ƁAZ������̉�]�ƂȂ�B
			// Z����\���x�N�g���� (0, 0, 1) �ŁAVector3::UnitZ �萔�������\���B
			// ��̓s�b�`�̎��Ɠ����B
			Vector3 axis = Vector3::Transform(Vector3::UnitZ, playerRot);
			playerRot.RotateAxis(axis, rotVelocity);
		}
		// �� �L�[
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			Vector3 axis = Vector3::Transform(Vector3::UnitZ, playerRot);
			playerRot.RotateAxis(axis, -rotVelocity);
		}

		// ���@��O�i������B
		// �܂����[���Ɠ������@�Ő��ʕ��������߂�B
		// ����͒P�ʃx�N�g���ŁA���x���|���邱�ƂŎ��@�̈ʒu���ǂꂾ���i�߂�΂悢�����킩��B
		Vector3 front = Vector3::Transform(Vector3::UnitZ, playerRot);
		playerPos += front * velocity;


		//-----------------------------------------------------
		// �J�����̎p���X�V
		
		// �J�����̈ʒu�͎��@���� 5.0 �������ɗ��ꂽ�Ƃ���ɂ������B
		// ���@�̃��[���Ɠ������@�ŁA�w�� -5.0 �̈ʒu�����߂Ă���B
		Vector3 back = Vector3::Transform(Vector3(0, 0, -5.0f), playerRot);
		Vector3 cameraPos = playerPos + back;

		// �����������܂łƓ��������W�ϊ��ŋ��߂�B
		// ���̕����� (0, 1, 0) �ŁAVector3::UnitY �萔�������\���B
		Vector3 cameraUp = Vector3::Transform(Vector3::UnitY, playerRot);

		// �K�v�ȏ�񂪑������B�J�����̎p����ݒ肷��
		SetCameraPositionAndTargetAndUpVec(cameraPos, playerPos, cameraUp);
		

		//-----------------------------------------------------
		// �`�揈��

		ClearDrawScreen();

		// �w�i���́A�n�`���߂荞��Ō����Ȃ��悤�� ZWrite �𖳌��ɂ��ĕ`�悷��
		MV1SetPosition(skyModel, playerPos);
		MV1SetWriteZBuffer(skyModel, FALSE);
		MV1DrawModel(skyModel);

		// �n�ʂ̕`�� (������)
		MV1SetWireFrameDrawFlag(groundModel, FALSE);
		MV1SetOpacityRate(groundModel, 0.2f);
		MV1DrawModel(groundModel);

		// �n�ʂ̕`�� (���C���[�t���[��)
		MV1SetWireFrameDrawFlag(groundModel, TRUE);
		MV1SetOpacityRate(groundModel, 1.0f);
		MV1DrawModel(groundModel);

		// �N�H�[�^�j�I���ƈʒu�x�N�g�����烏�[���h���W�ϊ��s������߁A���@�̎p���Ƃ��Đݒ肷��
		Matrix mat = Matrix::AffineTransformation(
			Vector3::One,	// �g�嗦�� (1, 1, 1)
			Vector3::Zero,	// ��]�̌��_�̓��f���̌��_
			playerRot,		// ��]���
			playerPos);		// �ʒu
		MV1SetMatrix(playerModel, mat);
		MV1DrawModel(playerModel);

		// [���܂�] �����̕������������Ƃ��ɉ�ʂ̋P�x���グ��B
		// �����̌����Ǝ��@�̌����œ��ς����ƁA�݂��Ɋ��S�Ɍ��������Ƃ��� -1.0 ���A�����ł���� 0.0 ���Ԃ�B
		// �����ł� -0.5 �` -1.0 �̊Ԃŏ��X�ɖ��邭���Ă���B
		Vector3 ligntDir(1, -1, -1);
		ligntDir.Normalize();
		float dot = Vector3::Dot(ligntDir, mat.GetFront());
		if (dot < -0.5f)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (-(dot + 0.5f))));
			DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);
		}

		// info
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawString(0, 0, "�� �� �L�[�Ń��[��", GetColor(100, 100, 100));
		DrawString(0, 16, "�� �� �L�[�Ńs�b�`", GetColor(100, 100, 100));

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}