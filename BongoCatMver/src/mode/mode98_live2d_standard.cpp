#include "header.hpp"
#include "SFML/Graphics/Texture.hpp"


#include<CubismFramework.hpp>
#include"LAppAllocator.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "myUserModel.hpp"
#include"LAppPal.hpp"
#include"../catfunc.h"




using namespace Csm;

extern void writeConfigFromUI();


namespace live2d_98
{
	//csm��ȫ�ֱ���
	CubismFramework::Option   _cubismOption;
	// allocator.
	LAppAllocator   _cubismAllocator;
	//live2d��Ϣ��� Message output function.
	static   void   PrintMessage(const   Csm::csmChar* message);

	bool is_l2d_horizontal_flip;
	//ģ��
	myUserModel* myModel;

	Json::Value mouse_leftkey_value, mouse_rightkey_value, mouse_sidekey_value, stopemoticon_value,stopsound_value;

	int offset_x, offset_y;				//ͼƬ�ļ�ƫ��ֵ
	int hand_offset_x, hand_offset_y;	//������ƫ��ֵ
	int horizontal, vertical;

	double scale;

	bool is_mouse, is_left_handed, is_emoticonkeep, is_workarea, is_mouse_force_move, is_soundkeep;

	sf::Sprite bg, device, mouse_left, mouse_right, mouse_side, up;
	sf::Texture atextex;				//��������

	int mouse_state = 0;				//���״̬

	//window
	double letter_x, letter_y, s_height, s_width;

	sf::Clock key_clock;
	sf::Time init_time;

	pkeyList keyboard_key_list;			//������Ч����ϼ�����
	pspriteList keyboard_sprite_list;	//������Ч��ͼƬ����

	pkeyList  hand_key_list;			//�ֵ���ϼ�����
	pspriteList hand_sprite_list;		//��sprite������
	ptimeList hand_time_list;			//�ֵļ�ʱ������

	pkeyList face_key_list;				//�������ϼ�����
	pspriteList face_sprite_list;		//����sprite������
	pstateList face_state_list;			//��¼����״̬������

	pkeyList sound_key_list;			//��Ƶ����ϼ�����
	psoundBufferList sound_buffer_list;	//��Ƶ�Ļ�������
	//pSoundqueue soundplayqueue;			//��Ƶ��ѭ������	ͬʱ���ŵ�����Ƶʱ��
	psoundList sound_list;				//��Ƶ���������	�������²�����Ƶ


	//arm lines color
	int red_value;
	int green_value;
	int blue_value;

	//workarea
	int top_left;
	int right_bottom;




	bool init()
	{
		sound_list = NULL;
		while (!is_opengl_inited)
			Sleep(100);//�ȴ�openGL��ʼ�����


		key_clock.restart();//��ʼ��ʱ��
		init_time = key_clock.getElapsedTime();



		//��ֵ
		red_value = data::cfg["decoration"]["armLineColor"][0].asInt();
		green_value = data::cfg["decoration"]["armLineColor"][1].asInt();
		blue_value = data::cfg["decoration"]["armLineColor"][2].asInt();

		is_emoticonkeep = data::cfg["decoration"]["emoticonKeep"].asBool();
		is_soundkeep = data::cfg["decoration"]["soundKeep"].asBool();
		stopemoticon_value = data::cfg["decoration"]["emoticonClear"];
		stopsound_value = data::cfg["decoration"]["soundClear"];

		is_mouse = data::cfg["standard"]["mouse"].asBool();
		is_mouse_force_move = data::cfg["decoration"]["mouse_force_move"].asBool();
		is_left_handed = data::cfg["decoration"]["leftHanded"].asBool();

		mouse_leftkey_value = data::cfg["standard"]["mouse_left"];
		mouse_rightkey_value = data::cfg["standard"]["mouse_right"];
		mouse_sidekey_value = data::cfg["standard"]["mouse_side"];

		hand_offset_x= data::cfg["standard"]["hand_offset"][0].asInt();
		hand_offset_y=data::cfg["standard"]["hand_offset"][1].asInt();

		if (is_mouse)
		{
			offset_x = (data::cfg["decoration"]["offsetX"])[0].asInt();
			offset_y = (data::cfg["decoration"]["offsetY"])[0].asInt();
			scale = (data::cfg["decoration"]["scalar"])[0].asDouble();
		}
		else
		{
			offset_x = (data::cfg["decoration"]["offsetX"])[1].asInt();
			offset_y = (data::cfg["decoration"]["offsetY"])[1].asInt();
			scale = (data::cfg["decoration"]["scalar"])[1].asDouble();
		}

		//��ȡ�������
		RECT desktop;
		const HWND h_desktop = GetDesktopWindow();
		GetWindowRect(h_desktop, &desktop);
		horizontal = desktop.right;
		vertical = desktop.bottom;
		//����workarea�趨ָ������
		if (data::cfg["workarea"]["workarea"].asBool()) {
			letter_x = data::cfg["workarea"]["top_left"][0].asInt();
			letter_y = data::cfg["workarea"]["top_left"][1].asInt();
			s_width = data::cfg["workarea"]["right_bottom"][0].asInt() - letter_x;
			s_height = data::cfg["workarea"]["right_bottom"][1].asInt() - letter_y;

		}
		else
		{
			s_width = horizontal;
			s_height = vertical;
			letter_x = 0;
			letter_y = 0;
		}



		//����sprites
		if (!atextex.loadFromFile("img/standard/arm.png"))
		{
			data::error_msg("File not successfully loaded", "Error loading files");
		}
		up.setTexture(data::load_texture("img/standard/up.png"));
		if (is_mouse)
		{
			bg.setTexture(data::load_texture("img/standard/l2dmousebg.png"));
			device.setTexture(data::load_texture("img/standard/mouse.png"), true);
			mouse_left.setTexture(data::load_texture("img/standard/mouse_left.png"), true);
			mouse_right.setTexture(data::load_texture("img/standard/mouse_right.png"), true);
			mouse_side.setTexture(data::load_texture("img/standard/mouse_side.png"), true);
		}
		else
		{
			bg.setTexture(data::load_texture("img/standard/l2dtabletbg.png"));
			device.setTexture(data::load_texture("img/standard/tablet.png"), true);
			mouse_left.setTexture(data::load_texture("img/standard/tablet_left.png"), true);
			mouse_right.setTexture(data::load_texture("img/standard/tablet_right.png"), true);
		}
		//��ȡ���̰���
		keyboard_key_list = read_key_from_cfg("standard", "keyboard");
		//��ȡ����ͼƬ
		keyboard_sprite_list = read_img("standard", "keyboard");

		//��ȡ�ְ���
		hand_key_list = read_key_from_cfg("standard", "hand");
		//��ȡ��ͼƬ
		hand_sprite_list = read_img("standard", "hand");
		//�����ּ�ʱ������
		hand_time_list = creat_timelist("standard", "hand");

		//��ȡ���鰴��
		face_key_list = read_key_from_cfg("standard", "face");
		//��ȡ����ͼƬ
		face_sprite_list = read_img("standard", "face");
		//��������״̬����
		face_state_list = creat_statelist("standard", "face");

		//��ȡ��Ƶ����
		sound_key_list = read_key_from_cfg("standard", "sounds");
		//��ȡ��Ƶ�ļ�
		sound_buffer_list = read_sound("standard", "sounds");
		if (!is_soundkeep)
		{
			sound_list = creat_soundlist("standard", "sounds");
			psoundBufferList psoundBuffer = sound_buffer_list;
			psoundList psound = sound_list;
			while (psound != NULL)
			{
				psound->sound.setBuffer(psoundBuffer->soundbuffer);
				psound = psound->next;
				psoundBuffer = psoundBuffer->next;
			}
		}

		device.setScale(scale, scale);
		mouse_left.setScale(scale, scale);
		mouse_right.setScale(scale, scale);
		mouse_side.setScale(scale, scale);

		GetCursorPos(&point);//��ʼ���������


		return true;


	}




	void draw()
	{

		//����live2dģ��
		LAppPal::UpdateTime();
		CubismMatrix44 projection;
		int l2dwidth = data::cfg["decoration"]["window_size"][0].asInt(), l2dheight = data::cfg["decoration"]["window_size"][1].asInt();
		double modelscale = data::cfg["decoration"]["l2d_correct"].asDouble();

		projection.Scale(modelscale * 1.0f, modelscale * static_cast<float>(l2dwidth) / static_cast<float>(l2dheight));

		const CubismMatrix44    saveProjection = projection;
		myModel->Update();
		myModel->Draw(projection);



		//���Ʊ���
		window.draw(bg);

		double x, y;
		if (is_mouse_force_move)
		{
			DInput_Read_Mouse();
			point.x += mouse_state_d7.lX;
			point.y += mouse_state_d7.lY;
			//UpdateInputState();
			if (point.x < letter_x)point.x = letter_x;
			if (point.x > (s_width + letter_x))point.x = s_width + letter_x;
			if (point.y < letter_y)point.y = letter_y;
			if (point.y > (s_width + letter_x))point.y = s_height + letter_y;
			double fx = ((double)point.x - letter_x) / s_width;
			if (is_left_handed)
				fx = 1 - fx;
			double fy = ((double)point.y - letter_y) / s_height;
			fx = min(fx, 1.0);
			fx = max(fx, 0.0);
			fy = min(fy, 1.0);
			fy = max(fy, 0.0);
			x = -97 * fx + 44 * fy + 184;
			y = -76 * fx - 40 * fy + 324;
			if (is_l2d_horizontal_flip)
				myModel->SetDragging(1 - 2 * fx, 1 - 2 * fy);
			else
				myModel->SetDragging(1 - 2 * fx, 1 - 2 * fy);
		}
		else
			if (GetCursorPos(&point))
			{
				double fx = ((double)point.x - letter_x) / s_width;
				if (is_left_handed)
					fx = 1 - fx;
				double fy = ((double)point.y - letter_y) / s_height;
				fx = min(fx, 1.0);
				fx = max(fx, 0.0);
				fy = min(fy, 1.0);
				fy = max(fy, 0.0);
				x = -97 * fx + 44 * fy + 184;
				y = -76 * fx - 40 * fy + 324;
				if (is_l2d_horizontal_flip)
					myModel->SetDragging(1 - 2 * fx, 1 - 2 * fy);
				else
					myModel->SetDragging(1 - 2 * fx, 1 - 2 * fy);
			}
			else { x = y = 0; }

		double mpos0, mpos1;
		double dx = -38;
		double dy = -50;
		std::vector<double>pss2;
		//�������ֵı�������������
		setrighthand(x, y, &mpos0, &mpos1, &pss2, dx, dy);


		//�����ֽ���λ�ô���
		for (int i = 0; i < 26; i++)
		{
			pss2[i * 2] += hand_offset_x;
			pss2[i * 2 + 1] += hand_offset_y;
		}


		//��������
		device.setPosition(mpos0 + dx + offset_x+ hand_offset_x, mpos1 + dy + offset_y+ hand_offset_y);
		mouse_left.setPosition(mpos0 + dx + offset_x+ hand_offset_x, mpos1 + dy + offset_y+ hand_offset_y);
		mouse_right.setPosition(mpos0 + dx + offset_x+ hand_offset_x, mpos1 + dy + offset_y+ hand_offset_y);
		mouse_side.setPosition(mpos0 + dx + offset_x+ hand_offset_x, mpos1 + dy + offset_y+ hand_offset_y);

		// drawing mouse
		if (is_mouse) {
			window.draw(device);
			for (Json::Value& v : mouse_leftkey_value)
				if (GetKeyState(v.asInt()) & 0x8000)
				{
					window.draw(mouse_left);
					break;
				}
			for (Json::Value& v : mouse_rightkey_value)
				if (GetKeyState(v.asInt()) & 0x8000)
				{
					window.draw(mouse_right);
					break;
				}
			for (Json::Value& v : mouse_sidekey_value)
				if (GetKeyState(v.asInt()) & 0x8000)
				{
					window.draw(mouse_side);
					break;
				}


		}

		//����������״��������������
		sf::ConvexShape fill(26);
		for (int i = 0; i < 26; i++)
		{
			fill.setPoint(i, sf::Vector2f(pss2[i * 2], pss2[i * 2 + 1]));
		}
		fill.setTexture(&atextex);
		window.draw(fill);



		drawline(pss2, red_value, green_value, blue_value);



		//������Ƶ����ģʽ��������Ƶ
		if (is_soundkeep)
			playsound(sound_key_list, sound_buffer_list, soundplayqueue);
		else
			playsound(sound_key_list, sound_list);
		//���������ȡ����Ƶ����ֹͣ������Ƶ
		bool stop = true;
		for (Json::Value& v : stopsound_value)
			stop = stop && (GetKeyState(v.asInt()) & 0x8000);
		if (stop) {
			if (is_soundkeep)
				for (int i = 0; i < 50; i++)
				{
					soundplayqueue->sound.stop();
					soundplayqueue = soundplayqueue->next;
				}
			else
			{
				psoundList psound = sound_list;
				while (psound != NULL)
				{
					psound->sound.stop();
					psound = psound->next;
				}
			}
		}

		//��Ⲣ���Ƽ���
		drawkeyboard(keyboard_key_list, keyboard_sprite_list);
		//��Ⲣ������
		drawhand(hand_key_list, hand_sprite_list, hand_time_list, key_clock, init_time, up);

		if (is_emoticonkeep)
		{
			//����������������ļ������������״̬
			stop = true;
			for (Json::Value& v : stopemoticon_value)
				stop = stop && (GetKeyState(v.asInt()) & 0x8000);
			if (stop)
				{
					pstateList statelist = face_state_list;
					while (statelist != NULL)
					{
						statelist->state = false;
						statelist = statelist->next;
					}
				}
			//�԰���ȡ���ķ�ʽ���Ʊ���
			drawface(face_key_list, face_sprite_list, face_state_list);
		}
		else
			//�԰�����Чͬ���ķ�ʽ���Ʊ���
			drawkeyboard(face_key_list, face_sprite_list);



		//ʹ����λ��ʱ������λ��
		if (!is_mouse) {
			for (Json::Value& v : mouse_leftkey_value)
				if (GetKeyState(v.asInt()) & 0x8000)
				{
					mouse_state = 1;
					break;
				}
			for (Json::Value& v : mouse_rightkey_value)
				if (GetKeyState(v.asInt()) & 0x8000)
				{
					mouse_state = 2;
					break;
				}
			switch (mouse_state)
			{
			case 1:
				window.draw(mouse_left);
				break;
			case 2:
				window.draw(mouse_right);
				break;
			default:
				window.draw(device);
				break;
			}
			mouse_state = 0;
		}


	}



	void   PrintMessage(const   Csm::csmChar* message)
	{

		printf("%sʲô������û���׼��", message);
		return;
	}




}; // namespace live2d_98






