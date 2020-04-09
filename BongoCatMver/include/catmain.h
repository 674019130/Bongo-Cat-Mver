#pragma once
#ifndef _CATMAIN_H
#define _CATMAIN_H


#include<header.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<CubismFramework.hpp>
#include"LAppAllocator.hpp"
#include "myUserModel.hpp"
#include"LAppPal.hpp"
#include <tchar.h>


using namespace Csm;

namespace cat_main
{
	bool config_init();//��ʼ��json����ȡconfig
	DWORD WINAPI loadfile(LPVOID lpParam);//��ȡ�ļ����߳����õĺ���
	void setWindow();//����config�ı䴰����ʽ
	HANDLE thread_loadfile(int mode);//������ȡ�ļ����߳�
	void StartLogoAnime();//������������
	void clearCatWindow();//����config��������������ͼ��
	void drawCat(int mode);//����ģʽֵ������è��
	void   PrintMessage(const  Csm::csmChar* message) { printf("%s", message); return; }//���ڳ�ʼ��csm�ĺ���֮һ
	void lockCat();//����ģʽ�����������è��
	void moveCatPosition();//�϶�����
	void moveCatSize();//�ı䴰�ڴ�С
	DWORD WINAPI UI_Start(LPVOID lpParam);//��������UI���ڲ��������ӵĺ���


	bool is_first_load_cat = true;	//�Ƿ�Ϊ������еĵ�һ�μ���è��
	static long windowlangdefault;	//Ĭ������µĴ���long
	static RECT rectdefault;		//Ĭ������µĴ���rect
	static long ret;				//�洢��ǰ����longֵ
	static bool is_UI_on = false;			//�洢UI����״̬

	LAppAllocator   _cubismAllocator;

	enum MODE
	{
		STANDARD = 1,
		KEYBOARD = 2,
		LIVE2D = 98
	};

	//��ʼ��json����ȡconfig
	bool config_init()
	{
		return true;
	}

	//����config�ı䴰����ʽ
	void setWindow()
	{
		//sfwindow�Ŀ������߿��windows��ߵĲ�ֵ
		static int offsetX, offsetY;
		static bool lastmode_ispet=false;

		//MoveWindow(catHwnd, window.getPosition().x, window.getPosition().y, data::cfg["decoration"]["window_size"][0].asInt(), data::cfg["decoration"]["window_size"][1].asInt(), TRUE);
		if (is_first_load_cat) {
			windowlangdefault = GetWindowLong(catHwnd, GWL_STYLE);
			GetWindowRect(catHwnd, &rectdefault);
			is_first_load_cat = false;
			offsetX = rectdefault.right - rectdefault.left - WIDTH;
			offsetY = rectdefault.bottom - rectdefault.top - HEIGHT;
		}
		//���ʹ�����裬������͸�������ޱ߿�
		if (data::cfg["decoration"]["desktop_pet"].asBool())
		{
			//���ô����ޱ߿�

			SetWindowLong(catHwnd, GWL_STYLE, windowlangdefault & (~(WS_CAPTION | WS_THICKFRAME)));
			//��������ǰ��ģʽ�������Ƿ�΢������λ��
			RECT catwndrect;
			GetClientRect(catHwnd,&catwndrect);
			if(lastmode_ispet)
				MoveWindow(catHwnd, window.getPosition().x, window.getPosition().y, WIDTH, HEIGHT, TRUE);
			else
				MoveWindow(catHwnd, window.getPosition().x+offsetX/2, window.getPosition().y + offsetY-offsetX/2, WIDTH, HEIGHT, TRUE);
			lastmode_ispet = true;
			//���ô���͸��
			DWM_BLURBEHIND bb = { 0 };
			HRGN hRgn = CreateRectRgn(0, 0, -1, -1); //Ӧ��ë�����ľ��η�Χ������(0,0,-1,-1)�������������ڿͻ������͸���ģ�������ǿ��Բ���͸��������
			bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
			bb.hRgnBlur = hRgn;
			bb.fEnable = TRUE;
			DwmEnableBlurBehindWindow(catHwnd, &bb);
		}

		//���δʹ�����裬�����ô����б߿�
		else
		{
			//���ô��ڱ߿���
			SetWindowLong(catHwnd, GWL_STYLE, windowlangdefault);

			//��������ǰ��ģʽ�������Ƿ�΢������λ��
			if(lastmode_ispet)
				MoveWindow(catHwnd, window.getPosition().x-offsetX/2, window.getPosition().y- offsetY+ offsetX / 2, \
					offsetX + WIDTH, offsetY + HEIGHT,
					TRUE);
			else
			MoveWindow(catHwnd, window.getPosition().x, window.getPosition().y, \
				offsetX + WIDTH , offsetY+HEIGHT,
				TRUE);
			lastmode_ispet = false;
			//���ô��ڲ�͸��
			DWM_BLURBEHIND bb = { 0 };
			HRGN hRgn = CreateRectRgn(0, 0, -1, -1); //Ӧ��ë�����ľ��η�Χ������(0,0,-1,-1)�������������ڿͻ������͸���ģ�������ǿ��Բ���͸��������
			bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
			bb.hRgnBlur = NULL;
			bb.fEnable = FALSE;
			DwmEnableBlurBehindWindow(catHwnd, &bb);
		}

		//�����ö�
		if (data::cfg["decoration"]["topWindow"].asBool())
			SetWindowPos(catHwnd, HWND_TOPMOST, 1, 1, 1, 1, SWP_NOMOVE | SWP_NOSIZE);
		else
			SetWindowPos(catHwnd, HWND_NOTOPMOST, 1, 1, 1, 1, SWP_NOMOVE | SWP_NOSIZE);

		//�����ģʽ98�����ʼ��openGL
		if (data::cfg["mode"].asInt() == LIVE2D) {
			if (glfwInit() == GL_FALSE)
			{
				data::error_msg("glfw��ʼ��ʧ���ˡ�", "һ���������������");
			}
			if (glewInit() != GLEW_OK) {
				glfwTerminate();
				data::error_msg("glew��ʼ��ʧ���ˡ�", "һ���������������");
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			CubismFramework::Option   _cubismOption;
			// �������Υ�٥���O����LogLevel_Verbose�Έ��Ϥ�Ԕ��������������롣
			_cubismOption.LoggingLevel = CubismFramework::Option::LogLevel_Verbose;
			_cubismOption.LogFunction = PrintMessage;

			// CubismNativeFramework�γ��ڻ��˱�Ҫ�ʥѥ��`�����O�����롣
			CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);

			// CubismFramework����ڻ����롣
			CubismFramework::Initialize();


			live2d_98::myModel = new myUserModel();

			// Read moc3 file.
			//��Щ����Ҳ���������߳���������Ȼè���������ɺ�ɫ
			std::string modelPath = "Resources/cat/";
			std::string modelJsonName = "cat.model3.json";
			live2d_98::myModel->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
			LAppPal::UpdateTime();
			is_opengl_inited = true;//��֪l2d��ʼ���߳�opengl�ĳ�ʼ�����

		}

		//���浱ǰlongֵ���ṩ������ģʽ������������
		static long ret = ::GetWindowLong(catHwnd, GWL_EXSTYLE);

		//����ˢ����fps
		window.setFramerateLimit(data::cfg["decoration"]["framerateLimit"].asInt());
	}


	//������ȡ�ļ����߳�
	HANDLE thread_loadfile(int mode)
	{
		HANDLE thread_handle;
		thread_handle = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)loadfile,
			&mode,
			0,
			NULL
		);

		if (!thread_handle)
			data::error_msg("���������ļ����߳�����ʧ����", "һ���������������");
		return thread_handle;
	}

	//��ȡ�ļ����߳����õĺ���
	DWORD WINAPI loadfile(LPVOID lpParam)
	{
		bool flag = false;

		while (flag == false) {
			//��ȡ��������Ҫ�������ļ�
			if (!catfont.loadFromFile("Resources/cat.ttf")) {
				data::error_msg("����û���غã��ǲ������cat.ttfŪ���ˣ���", "�����ļ�������");
				flag = false;
				continue;
			}
			//��ģʽ�����ļ�
			switch (data::cfg["mode"].asInt())
			{
			case STANDARD:
				flag = standard::init();
				if (flag == false)data::error_msg("��׼ģʽ��ʼ���������ˡ�", "һ���������������");
				break;
			case KEYBOARD:
				flag = keyboard::init();
				if (flag == false)data::error_msg("������ģʽ��ʼ���������ˡ�", "һ���������������");
				break;
			case LIVE2D:
				flag = live2d_98::init();
				if (flag == false)data::error_msg("live2dģʽ�������ˡ�", "һ���������������");
				break;
			default:
				data::error_msg("�ֵ�����ģʽ������û���ö�ͷ����", "�����ô���");
				flag = false;
			}
		}
		is_load_success = true;
		return 0;
	}

	//������������
	void StartLogoAnime()
	{
		//todo�ж��Ƿ�Ϊ��һ������

		//������������ʱ��
		sf::Clock textTimer;
		textTimer.restart();
		//����logoͼƬ
		sf::Sprite L2dlogo;
		L2dlogo.setTexture(data::load_texture("Resources/l2dlogo.png"), true);
		//��logoͼƬ����������
		L2dlogo.setPosition((WIDTH- L2dlogo.getTextureRect().width)/2,(HEIGHT- L2dlogo.getTextureRect().height)/2);
		//���������Ķ���ѭ��
		while (window.isOpen() && ((textTimer.getElapsedTime() < sf::seconds(2)) || is_load_success == false))
		{
			//������Ϣѭ��
			sf::Event event;
			while (window.pollEvent(event))
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					//������ģʽ��������������ʽ�̶����ڱ���
					if (!data::cfg["decoration"]["desktop_pet"].asBool())
					{
						if (event.size.width != WIDTH)
							window.setSize(sf::Vector2u(event.size.width, event.size.width * data::cfg["decoration"]["window_size"][1].asInt() / data::cfg["decoration"]["window_size"][0].asInt()));
						else if (event.size.height != HEIGHT)
							window.setSize(sf::Vector2u(event.size.height * data::cfg["decoration"]["window_size"][0].asInt() / data::cfg["decoration"]["window_size"][1].asInt(), event.size.height));
						//�洢�µĿ��ֵ
						WIDTH = window.getSize().x;
						HEIGHT = window.getSize().y;
					}
					break;
				default:
					break;
				}
			window.clear(sf::Color::White);
			window.draw(L2dlogo);
			window.display();
		}



	}

	//����config��������������ͼ��
	void clearCatWindow()
	{
		//������������裬��Ѵ��ڲ���ȫ͸��
		if (data::cfg["decoration"]["desktop_pet"].asBool())
			window.clear(sf::Color(0, 0, 0, 0));
		//���δ�������裬��Ѵ��ڲ���rgb���õ�ɫֵ
		else
			window.clear(
				sf::Color(
					data::cfg["decoration"]["rgb"][0].asInt(),
					data::cfg["decoration"]["rgb"][1].asInt(),
					data::cfg["decoration"]["rgb"][2].asInt()
				)
			);
	}


	//����ģʽֵ������è��
	void drawCat(int mode)
	{

		switch (mode)
		{
		case STANDARD:
			standard::draw();
			break;
		case KEYBOARD:
			keyboard::draw();
			break;
		case LIVE2D:
			live2d_98::draw();
			break;
		default:
			return;
		}
		//����ģʽ�¸���������������è��
		lockCat();

		//����ģʽ�¶�è������ƶ��ʹ�С�ĸı�
		if (data::cfg["decoration"]["desktop_pet"].asBool())
		{
			moveCatPosition();
			moveCatSize();
		}

	};

	//����ģʽ�����������è��
	void lockCat()
	{
		static bool T_keystate = false;			//T��״ֵ̬����괩͸״ֵ̬
		static bool is_mouse_through = false;		//��괩͸״ֵ̬
		static  sf::Clock textTimer;			//�ı���ʾ��ʱ��
		static bool text_drawing = false;		//�Ƿ���ʾ�ı�����Ҫ���ڷ�ֹ�ڳ�������ʱ����ʾ�ı�

		//�ж��Ƿ�������ϼ�ctrl:17 shift:16 T:84   ���ж��Ƿ�Ϊ����״̬��  ʹ��GetKeyState()������Ϊ���ڴ�͸״̬��Ҳ�ܽ����ȼ�
		if ((GetKeyState(17) & 0x8000) && (GetKeyState(16) & 0x8000) && (GetKeyState(84) & 0x8000) && data::cfg["decoration"]["desktop_pet"].asBool())
		{
			//�ж��Ƿ�հ���T
			if (T_keystate == false)
			{
				//�����Ƿ���괩͸���������ı���ʾ�ļ�ʱ��
				if (is_mouse_through) {
					SetWindowLong(catHwnd, GWL_EXSTYLE, ret);
					is_mouse_through = false;
					textTimer.restart();
				}
				else
				{
					SetWindowLong(catHwnd, GWL_EXSTYLE, ret | WS_EX_LAYERED | WS_EX_TRANSPARENT);
					is_mouse_through = true;
					textTimer.restart();
				}
			}
			//����T��״̬�� �ڵ�һ�ΰ�����ϼ�ʱ�ſ����ı���ʾ
			T_keystate = true;
			text_drawing = true;
		}
		//�ɿ����̺����T��״̬
		else
			T_keystate = false;

		//���ݼ�ʱ�����ı���ʾ״ֵ̬���жϵ�ǰ֡�Ƿ���ʾ�ı�
		if (textTimer.getElapsedTime() < sf::seconds(2) && text_drawing)
		{
			//����һ��������ʾ���ı�
			sf::Text textForLock;
			textForLock.setFont(catfont);
			textForLock.setFillColor(sf::Color(255, 126, 126));
			textForLock.setCharacterSize(50);
			if (is_mouse_through)
				textForLock.setString(L"������������괩͸�ѿ���");
			else
				textForLock.setString(L"���ڽ�������괩͸�ѹر�");
			window.draw(textForLock);
		}
		//���Ƶ�������
		else if (sf::seconds(2) < textTimer.getElapsedTime() && textTimer.getElapsedTime() < sf::milliseconds(2500) && text_drawing)
		{
			sf::Text textForLock;
			textForLock.setFont(catfont);
			textForLock.setFillColor(sf::Color(255, 126, 126, 255 * ((sf::milliseconds(2500) - textTimer.getElapsedTime()) / sf::milliseconds(500))));
			textForLock.setCharacterSize(50);
			if (is_mouse_through)
				textForLock.setString(L"������������괩͸�ѿ���");
			else
				textForLock.setString(L"���ڽ�������괩͸�ѹر�");
			window.draw(textForLock);
		}
	}

	//�϶�����
	void moveCatPosition()
	{
		static bool bFirstCLK = false;
		static POINT OldPos, NewPos;
		static int  xOffset, yOffset;
		static RECT subrect;

		//���������£���è������ƶ�
		if ((GetKeyState(1) & 0x8000) && (window.hasFocus()))
		{
			if (bFirstCLK == false) {
				GetCursorPos(&OldPos);
				GetWindowRect(catHwnd, &subrect);
				bFirstCLK = true;
			}
			else {

				GetCursorPos(&NewPos);
				xOffset = NewPos.x - OldPos.x;
				yOffset = NewPos.y - OldPos.y;
				//����ƫ�����ı䴰��λ��
				MoveWindow(catHwnd, subrect.left + xOffset, subrect.top + yOffset, subrect.right - subrect.left, subrect.bottom - subrect.top, TRUE);
				UpdateWindow(catHwnd);
			}
		}
		else
			bFirstCLK = false;
	}

	//�ı䴰�ڴ�С
	void moveCatSize()
	{
		static bool rbFirstCLK = false;
		static POINT OldPos, NewPos;
		static int  xOffset, yOffset;
		static RECT subrect;

		//����Ҽ����£���è���������
		if ((GetKeyState(2) & 0x8000) && (window.hasFocus()))
		{
			if (rbFirstCLK == false) {
				GetCursorPos(&OldPos);
				rbFirstCLK = true;
			}
			else {
				GetCursorPos(&NewPos);
				xOffset = NewPos.x - OldPos.x;
				yOffset = NewPos.y - OldPos.y;
				GetWindowRect(catHwnd, &subrect);
				//����һ��ƫ�����ƶ�����������ı�è�䴰��
				if (xOffset * xOffset > yOffset* yOffset)
					MoveWindow(catHwnd, subrect.left, subrect.top,
						subrect.right + xOffset - subrect.left,
						(subrect.right + xOffset - subrect.left) * data::cfg["decoration"]["window_size"][1].asInt() / data::cfg["decoration"]["window_size"][0].asInt(),
						false);
				else
					MoveWindow(catHwnd, subrect.left, subrect.top,
						 (subrect.bottom + yOffset - subrect.top) * data::cfg["decoration"]["window_size"][0].asInt() / data::cfg["decoration"]["window_size"][1].asInt(),
						subrect.bottom + yOffset - subrect.top,
						false);
				OldPos.x= NewPos.x;
				OldPos.y = NewPos.y;
				UpdateWindow(catHwnd);
			}
		}
		else
			rbFirstCLK = false;
	}


	//����������UI����ʱ
	void On_Start_UI()
	{
		//���UI�����Ѿ������������������������Ӵ˴�����
		if (is_UI_on == false) {
			WCHAR text[32] = { 0 };
			GetWindowText(uiHwnd, text, 32);
			//��ʶ���Ѿ���UI����ʱ����UI�����Ƶ�����
			if (wcscmp(text, L"Bongo Cat Mver setting") == 0)
				SetWindowPos(uiHwnd, HWND_NOTOPMOST,1,1,1,1, SWP_NOMOVE| SWP_NOSIZE| SWP_SHOWWINDOW);
			//δʶ��UI����ʱ��������UI���ڵ��߳�
			else
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UI_Start, NULL, 0, NULL);
		}
	}

	//����UI
	DWORD WINAPI UI_Start(LPVOID lpParam)
	{
		//����UI״̬
		is_UI_on = true;

		//�����ܵ�ͨ����Ҫ�ľ���������ð�ȫ����
		//HANDLE hpipe2UIRd, hpipe2UIWt;
		HANDLE hpipe2CATRd=NULL, hpipe2CATWt=NULL;
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = NULL;
		//����һ������ܵ�
		if (!CreatePipe(&hpipe2CATRd, &hpipe2CATWt, &sa, 0))
		{
			data::error_msg("��UI����ͨ�Źܵ�ʧ��","һ���������������");
			is_UI_on = false;
			return 1;
		}
		if (!SetHandleInformation(hpipe2CATRd, HANDLE_FLAG_INHERIT, 0))
		{
			data::error_msg("��UI����ͨ�Źܵ�ʧ��", "һ���������������");
			is_UI_on = false;
			return 1;
		}
	
		//����UI���̲�����cat���ھ��
		PROCESS_INFORMATION pi;//pi ��ȡ�ӽ��̵���Ϣ
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.hStdOutput = hpipe2CATWt; //����ɱ�׼��� -> ������ܵ� 
		si.hStdError = hpipe2CATWt;
		si.dwFlags |= STARTF_USESTDHANDLES;

		TCHAR szAppPath[MAX_PATH] = { 0 };//���ڴ���cat���ھ��
		wsprintfW(szAppPath,L"%p", catHwnd);
		if (!CreateProcess(L"BongoCatUI.exe", szAppPath, NULL, NULL, true, NULL, NULL, NULL, &si, &pi))
		{
			data::error_msg("����UI���̵�ʱ����������", "һ���������������");
			is_UI_on = false;
			return 1;
		};
		CloseHandle(hpipe2CATWt);

		//�����̴�pipeout�Ķ��˶�ȡ����
		char buffer[128] = { 0 };
		DWORD readBytes, dwWritten;
		memset(buffer, 0, sizeof(buffer));
		HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		bool bSuccess = ReadFile(hpipe2CATRd, buffer, 128, &readBytes, NULL);
		if (!bSuccess || readBytes == 0) data::error_msg(buffer, "��UI���̻�ȡ��Ϣʧ��");

		//��ȡ�ɹ�����UI���̵Ĵ��ھ���ַ���תΪHWND��ʽ
		else
			uiHwnd=(HWND)strtoull(buffer,NULL,16);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		is_UI_on = false;
		return 0;
	}

	//�ͷ���Դ��ģ�庯��
	template <typename T>
	void release(T list)
	{
		T currentlist;
		while (list != NULL)
		{
			currentlist = list;
			list = list->next;
			delete currentlist;
		}
	}
	template <>   // ��pkeyList��������
	void release(pkeyList list)
	{
		pkeyList currentlist;
		while (list != NULL)
		{
			currentlist = list;
			release(list->notelist);
			list = list->next;
			delete currentlist;
		}
	}


	//����ģʽ�����ڴ�
	void clearmemory()
	{
		switch (data::cfg["mode"].asInt())
		{
		case STANDARD:
			release(standard::keyboard_key_list);
			release(standard::keyboard_sprite_list);

			release(standard::hand_key_list);
			release(standard::hand_sprite_list);
			release(standard::hand_time_list);

			release(standard::face_key_list);
			release(standard::face_sprite_list);
			release(standard::face_state_list);

			release(standard::sound_key_list);
			release(standard::sound_buffer_list);
			release(standard::sound_list);
			break;
		case KEYBOARD:
			
			release(keyboard::keyboard_key_list);
			release(keyboard::keyboard_sprite_list);

			release(keyboard::righthand_key_list);
			release(keyboard::righthand_sprite_list);
			release(keyboard::righthand_time_list);

			release(keyboard::lefthand_key_list);
			release(keyboard::lefthand_sprite_list);
			release(keyboard::lefthand_time_list);

			release(keyboard::face_key_list);
			release(keyboard::face_sprite_list);
			release(keyboard::face_state_list);

			release(keyboard::sound_key_list);
			release(keyboard::sound_buffer_list);
			release(keyboard::sound_list);
			

			break;
		case LIVE2D:
			release(live2d_98::keyboard_key_list);
			release(live2d_98::keyboard_sprite_list);

			release(live2d_98::hand_key_list);
			release(live2d_98::hand_sprite_list);
			release(live2d_98::hand_time_list);

			release(live2d_98::face_key_list);
			release(live2d_98::face_sprite_list);
			release(live2d_98::face_state_list);

			release(live2d_98::sound_key_list);
			release(live2d_98::sound_buffer_list);
			release(live2d_98::sound_list);
			break;
		default:
			break;
		}
	}

}//namespace cat_main



#endif // !_CATMAIN_H


