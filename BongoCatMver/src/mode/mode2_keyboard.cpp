#include "header.hpp"
#include "../catfunc.h"
#include "SFML/Graphics/Texture.hpp"

namespace keyboard
{
	Json::Value stopemoticon_value,stopsound_value;

	bool is_emoticonkeep,is_soundkeep;
	sf::Sprite bg, left_up,right_up;

	sf::Clock key_clock;				//�����жϰ����Ⱥ�ļ�ʱ��
	sf::Time init_time;

	pkeyList keyboard_key_list;			//������Ч����ϼ�����
	pspriteList keyboard_sprite_list;	//������Ч��ͼƬ����

	pkeyList righthand_key_list;		//���ֵ���ϼ�����
	pspriteList righthand_sprite_list;	//����sprite������
	ptimeList righthand_time_list;		//���ֵļ�ʱ������

	pkeyList  lefthand_key_list;		//���ֵ���ϼ�����
	pspriteList lefthand_sprite_list;	//����sprite������
	ptimeList lefthand_time_list;		//���ֵļ�ʱ������

	pkeyList face_key_list;				//�������ϼ�����
	pspriteList face_sprite_list;		//����sprite������
	pstateList face_state_list;			//��¼����״̬������

	pkeyList sound_key_list;			//��Ƶ����ϼ�����
	psoundBufferList sound_buffer_list;	//��Ƶ�Ļ�������
	//pSoundqueue soundplayqueue;			//��Ƶ��ѭ������	ͬʱ���ŵ�����Ƶʱ��
	psoundList sound_list;				//��Ƶ���������	�������²�����Ƶ


	bool init()
	{
		sound_list = NULL;

		key_clock.restart();	//��ʼ��ʱ��
		init_time = key_clock.getElapsedTime();

		is_emoticonkeep = data::cfg["decoration"]["emoticonKeep"].asBool();
		is_soundkeep = data::cfg["decoration"]["soundKeep"].asBool();
		stopemoticon_value = data::cfg["decoration"]["emoticonClear"];
		stopsound_value=data::cfg["decoration"]["soundClear"];


		//��ȡ���̰���
		keyboard_key_list = read_key_from_cfg("keyboard", "keyboard");
		//��ȡ����ͼƬ
		keyboard_sprite_list= read_img("keyboard", "keyboard");

		//��ȡ���ְ���
		righthand_key_list=read_key_from_cfg("keyboard", "righthand");
		//��ȡ����ͼƬ
		righthand_sprite_list = read_img("keyboard", "righthand");
		//�������ּ�ʱ������
		righthand_time_list = creat_timelist("keyboard", "righthand");

		//��ȡ���ְ���
		lefthand_key_list = read_key_from_cfg("keyboard", "lefthand");
		//��ȡ����ͼƬ
		lefthand_sprite_list = read_img("keyboard", "lefthand");
		//�������ּ�ʱ������
		lefthand_time_list = creat_timelist("keyboard", "lefthand");

		//��ȡ���鰴��
		face_key_list= read_key_from_cfg("keyboard", "face");
		//��ȡ����ͼƬ
		face_sprite_list= read_img("keyboard", "face");
		//��������״̬����
		face_state_list = creat_statelist("keyboard", "face");

		//��ȡ��Ƶ����
		sound_key_list= read_key_from_cfg("keyboard", "sounds");
		//��ȡ��Ƶ�ļ�
		sound_buffer_list = read_sound("keyboard", "sounds");
		if(!is_soundkeep)
		{
			sound_list = creat_soundlist("keyboard", "sounds");
			psoundBufferList psoundBuffer = sound_buffer_list;
			psoundList psound = sound_list;
			while(psound !=NULL)
			{
				psound->sound.setBuffer(psoundBuffer->soundbuffer);
				psound = psound->next;
				psoundBuffer = psoundBuffer->next;
			}
		}



		//���������־�ֹ����
		left_up.setTexture(data::load_texture("img/keyboard/lefthand/leftup.png"));
		right_up.setTexture(data::load_texture("img/keyboard/righthand/rightup.png"));

		bg.setTexture(data::load_texture("img/keyboard/bg.png"));

		return true;
	}

	void draw()
	{
		window.draw(bg);

		//������Ƶ����ģʽ��������Ƶ
		if (is_soundkeep)
			playsound(sound_key_list,sound_buffer_list, soundplayqueue);
		else
			playsound(sound_key_list, sound_list);
		//���������ȡ����Ƶ����ֹͣ������Ƶ
		bool stop=true;
		for (Json::Value& v : stopsound_value)
			stop = stop&&(GetKeyState(v.asInt()) & 0x8000);
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
		//��Ⲣ��������
		drawhand(righthand_key_list, righthand_sprite_list, righthand_time_list, key_clock, init_time, right_up);
		//��Ⲣ��������
		drawhand(lefthand_key_list, lefthand_sprite_list, lefthand_time_list, key_clock, init_time, left_up);



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
	}
}; // namespace keyboard




