#pragma once

class UILayer : public Layer
{
public:
<<<<<<< HEAD
	
	enum CONSTANT ///# ���̹� ����. �ʹ� �Ϲ����̰� �������� �̸�..
=======
	enum CONSTANT
>>>>>>> f193e0075ffbff1e9040a0434c3258fc5989f363
	{
		PAUSE_BUTTON_WIDTH = 40,
		PAUSE_BUTTON_HEIGHT = 40
	};

	CREATE_FUNC(UILayer);
	bool init();

	void MakeSuccessWidget(int m_stage);
	void MakeFailWidget(int m_stage);
	
private:

	enum ButtonSize
	{
		BUTTON_WIDTH = 40,
		BUTTON_HEIGHT = 40
	};

	void ChangeToStageScene(Ref* pSender);
	void GotoStage(Ref* pSender, int stageNum);
};