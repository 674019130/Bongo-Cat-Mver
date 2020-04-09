#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <dinput.h>

#include <time.h>
#include <windows.h>
#include <math.h>
#include <string.h>

#include "../myUserModel.hpp"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "json/json.h"
//#include<atlimage.h>
//#include <assert.h>
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")


//����ȫ�ֺ�
#define MAX_KEYS_NUM 50
#define VERSION "Bongo Cat Mver v0.1.4"

//������Ϣ
#define UIWM_WRITECONFIG 0x0400+2                   //дconfig�ļ���֪ͨcat���ڶ�ȡ
#define UIWM_WRITECONFIG_AND_RELOAD_FILE 0x0400+3   //дconfig�ļ���֪ͨcat�������¶�ȡ�ز��ļ�
#define CATWM_ACTIVE	0x0400+4					//���Լ�������Ϣ�Ա��ּ���״̬





//���õ�ȫ�ֱ���
extern HWND catHwnd;			//è�䴰�ھ��
extern HWND uiHwnd;				//UI���ھ��
extern HINSTANCE hInst;			//è�䴰��ʵ��


extern sf::RenderWindow window;	//è�䴰�ڶ���
extern sf::Font catfont;		//ȫ�ֵ��������

extern int WIDTH;				//è�䴰�ڵĿ��
extern int HEIGHT;				//è�䴰�ڵĸ߶�

extern bool is_load_success;	//todo������	
extern bool is_opengl_inited;	//��֪opengl��ʼ�����
extern bool is_UIThread_on;		//һ�����ڿ���ͬʱֻ������һ�����ô��ڵ�boolֵ



//�������ڴ��һ����ϼ��ĵ����Ľṹ���������������һ����ʾһ����ϼ�����������Ӧ���Ϊֻ��һ��������ϼ�
typedef struct keyNote {
	int key;
	keyNote* next;
}*pkeyNote;
//�������ڴ��һ����ϼ��Ľṹ���������������һ����ʾһ����ϼ�������
typedef struct keyList{
	int index;
	keyNote* notelist;
	keyList* next;
	bool state;	//��ʶ�ü���ǰ�ĵ��״̬
	bool last_state;	//��ʶ�ü���һ֡�ĵ��״̬
}*pkeyList;
//�������ڴ��һ��ͼƬ�������㡣
typedef struct spriteList {
	int index;
	sf::Sprite sprite;
	spriteList* next;
}*pspriteList;
//�������ڴ��һ���ʱ���ݵ������㡣
typedef struct timeList {
	int index;
	sf::Time time;
	timeList* next;
}*ptimeList;
//�������ڴ�Ų���״̬�������㡣
typedef struct stateList {
	int index;
	bool state;
	stateList* next;
}*pstateList;
//�������ڴ����Ƶ�����������
typedef struct soundBufferList {
	int index;
	sf::SoundBuffer soundbuffer;
	soundBufferList* next;
}*psoundBufferList;
typedef struct soundList {
	int index;
	sf::Sound sound;
	soundList* next;
}*psoundList;
//�������ڲ�����Ƶ��ѭ������
typedef struct soundqueue {
	sf::Sound sound;
	int index;
	soundqueue* next;
}*pSoundqueue;




extern pSoundqueue soundplayqueue;//һ��ȫ�ֵ���Ƶ����

//��DInput COM����
extern LPDIRECTINPUT8 lpdi ;
//�����豸
extern LPDIRECTINPUTDEVICE8 lpdimouse;
//��ȡ��������ݷ��ڴ˽ṹ��
extern DIMOUSESTATE mouse_state_d7;
//�������
extern POINT point;









namespace data
{
extern Json::Value cfg;

void error_msg(std::string error, std::string title);

bool init();

sf::Texture &load_texture(std::string path);
sf::Texture &load_texture2(std::string path);
}; // namespace data


namespace standard
{
	bool init();

	void draw();

	//��¶����release��ָ��
	extern pkeyList keyboard_key_list;			//������Ч����ϼ�����
	extern pspriteList keyboard_sprite_list;	//������Ч��ͼƬ����

	extern pkeyList hand_key_list;			//�ֵ���ϼ�����
	extern pspriteList hand_sprite_list;	//��sprite������
	extern ptimeList hand_time_list;		//�ֵļ�ʱ������

	extern pkeyList face_key_list;				//�������ϼ�����
	extern pspriteList face_sprite_list;		//����sprite������
	extern pstateList face_state_list;			//��¼����״̬������

	extern pkeyList sound_key_list;				//��Ƶ����ϼ�����
	extern psoundBufferList sound_buffer_list;	//��Ƶ�Ļ�������
	extern psoundList sound_list;				//��Ƶ���������	�������²�����Ƶ
}; // namespace standard


namespace keyboard
{
	bool init();

	void draw();

	extern sf::SoundBuffer soundBuffer[50];

	//��¶����release��ָ��
	extern pkeyList keyboard_key_list;			//������Ч����ϼ�����
	extern pspriteList keyboard_sprite_list;	//������Ч��ͼƬ����

	extern pkeyList righthand_key_list;			//���ֵ���ϼ�����
	extern pspriteList righthand_sprite_list;	//����sprite������
	extern ptimeList righthand_time_list;		//���ֵļ�ʱ������

	extern pkeyList  lefthand_key_list;			//���ֵ���ϼ�����
	extern pspriteList lefthand_sprite_list;	//����sprite������
	extern ptimeList lefthand_time_list;		//���ֵļ�ʱ������

	extern pkeyList face_key_list;				//�������ϼ�����
	extern pspriteList face_sprite_list;		//����sprite������
	extern pstateList face_state_list;			//��¼����״̬������

	extern pkeyList sound_key_list;				//��Ƶ����ϼ�����
	extern psoundBufferList sound_buffer_list;	//��Ƶ�Ļ�������
	extern psoundList sound_list;				//��Ƶ���������	�������²�����Ƶ

}; // namespace keyboard


namespace live2d_98
{
	bool init();

	void draw();

	extern myUserModel* myModel;

	//��¶����release��ָ��
	extern pkeyList keyboard_key_list;			//������Ч����ϼ�����
	extern pspriteList keyboard_sprite_list;	//������Ч��ͼƬ����

	extern pkeyList hand_key_list;			//�ֵ���ϼ�����
	extern pspriteList hand_sprite_list;	//��sprite������
	extern ptimeList hand_time_list;		//�ֵļ�ʱ������

	extern pkeyList face_key_list;				//�������ϼ�����
	extern pspriteList face_sprite_list;		//����sprite������
	extern pstateList face_state_list;			//��¼����״̬������

	extern pkeyList sound_key_list;				//��Ƶ����ϼ�����
	extern psoundBufferList sound_buffer_list;	//��Ƶ�Ļ�������
	extern psoundList sound_list;				//��Ƶ���������	�������²�����Ƶ
}; // namespace live2d_standard



























//��Ϊlive2d��logo���ʺϽ����û���������Ӧ������Դ�ļ�
//һ�����ڴ���Դ�м���png�ļ��ĺ���
/*CImage* LoadCImage(UINT nID, LPCTSTR lpszType, HINSTANCE hInstance)
{
	CImage* pImage = NULL;
	// ����bmp�ļ���
	if (RT_BITMAP == lpszType)
	{
		pImage = new CImage();
		pImage->LoadFromResource(hInstance, nID);
		if (!pImage->IsNull())
		{
			return pImage;
		}
		else
		{
			delete pImage;
			pImage = NULL;
			return pImage;
		}
	}
	CString strLog;
	HRSRC hRsrc = ::FindResource(hInstance, MAKEINTRESOURCE(nID), lpszType);
	assert(hRsrc != NULL);
	if (NULL == hRsrc)
	{
		return NULL;
	}
	DWORD dwSize = ::SizeofResource(hInstance, hRsrc);
	LPBYTE lpRsrc = (LPBYTE)::LoadResource(hInstance, hRsrc);
	assert(lpRsrc != NULL);
	if (NULL == hRsrc)
	{
		return NULL;
	}
	// ������������صķ�ʽʹ�õ���CreateStreamOnHGlobal������Ҫʹ��HGLOBAL�ڴ�
	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	if (NULL == hMem)
	{
		::FreeResource(lpRsrc);
		return NULL;
	}
	LPBYTE pMem = (LPBYTE)::GlobalLock(hMem);
	if (NULL == pMem)
	{
		::GlobalUnlock(hMem);
		::GlobalFree(hMem);
		::FreeResource(lpRsrc);
		return NULL;
	}
	memcpy(pMem, lpRsrc, dwSize);
	IStream* pStream = NULL;
	HRESULT hr = ::CreateStreamOnHGlobal(hMem, FALSE, &pStream);
	if (pStream != NULL && hr == S_OK)
	{
		pImage = new CImage();
		HRESULT hrs = pImage->Load(pStream);
		pStream->Release();
		// �ͷ���Դ
		::GlobalUnlock(hMem);
		::GlobalFree(hMem);
		::FreeResource(lpRsrc);
		if (hrs == S_OK)
		{
			// ����ͼƬ�е�͸��Ч��
			if (pImage->GetBPP() == 32)
			{
				for (int i = 0; i < pImage->GetWidth(); i++)
				{
					for (int j = 0; j < pImage->GetHeight(); j++)
					{
						unsigned char* pucColor = reinterpret_cast<unsigned char*>(pImage->GetPixelAddress(i, j));
						pucColor[0] = pucColor[0] * pucColor[3] / 255;
						pucColor[1] = pucColor[1] * pucColor[3] / 255;
						pucColor[2] = pucColor[2] * pucColor[3] / 255;
					}
				}
			}
			return pImage;
		}
		else
		{
			delete pImage;
			pImage = NULL;
			return pImage;
		}
	}
	else
	{   // �ͷ���Դ
		::GlobalUnlock(hMem);
		::GlobalFree(hMem);
		::FreeResource(lpRsrc);
		return NULL;
	}
}
*/