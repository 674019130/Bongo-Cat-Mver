#include "header.hpp"
#include <resource.h>
#include "../mydata.hpp"
#include"../catmain.h"
#include"../catfunc.h"
#include "../../../Windows Kits/10/Include/10.0.17763.0/um/WinUser.h"
#include "../resource.h"

using namespace std;
using namespace cat_main;

//ȫ�ֱ���
sf::RenderWindow window;            //������ʵ��
sf::Font catfont;                   //�洢ȫ������

HWND catHwnd;                       //�洢������
HWND uiHwnd=NULL;                   //�洢UI�߳̾��
HINSTANCE g_hInst;                  

int WIDTH;                          //�洢�Դ��ڽ��иı�ǰ�Ŀ��
int HEIGHT;                         //�洢�Դ��ڽ��иı�ǰ�ĸ߶�



HINSTANCE hInst;
int nCmdShow_pass;

bool is_reload = false;
bool is_reload_for_wmmsg = false;
bool loadflag = false;
bool is_load_success = false;
bool is_logo_end = false;
bool is_opengl_inited = false;
bool is_UIThread_on = false;
HANDLE logoAnime;
pSoundqueue soundplayqueue;

//��DInput COM����
LPDIRECTINPUT8 lpdi = NULL;
//�����豸
LPDIRECTINPUTDEVICE8 lpdimouse = NULL;
//��ȡ��������ݷ��ڴ˽ṹ��
DIMOUSESTATE mouse_state_d7;
//�������
POINT point;



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //��ʼ��json����ȡ����
    while (!data::init());

    //����һ����ʼ�Ĵ���,��ʼ��ȫ��WIDTH��HEIGHT����
    WIDTH = data::cfg["decoration"]["window_size"][0].asInt(); HEIGHT = data::cfg["decoration"]["window_size"][1].asInt();
    window.create(sf::VideoMode(WIDTH, HEIGHT), VERSION, sf::Style::Resize | sf::Style::Close); //sf::Style::None);
    //��ȡ���洢cat���ھ��
    catHwnd = window.getSystemHandle();

    //���ô���ͼ��
    HICON hIcon;
    hIcon = LoadIcon(hInstance, (LPCWSTR)IDI_ICON2);
    if (hIcon) {
        SendMessage(catHwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }

    //��ʼ�����
    hInst=GetModuleHandle(0);
    DInput_Init_Mouse();
    //������Ƶ����
    soundplayqueue = creatSoundQueue(50);

    //���̼߳��ظ����ļ�,����ȡ�߳̾��
    HANDLE handle_loadfile_thread = thread_loadfile(data::cfg["mode"].asInt());

    //��config���ô�����ʽ��
    setWindow();

    //������������
    StartLogoAnime();

    //�ȴ������ļ����߳̽���
    //WaitForSingleObject(handle_loadfile_thread, INFINITE);

    //��ʱ�򴰿ڷ�����Ϣ��ֹδ��Ӧ
    static sf::Clock msgtimer;//��ʱ��
    msgtimer.restart();//����ʱ��


    //����è��ѭ��
    while (window.isOpen())
    {
#ifdef MYDEBUG
        static sf::Clock FPStimeer;//����֡�ʼ�ʱ��
        FPStimeer.restart();//����ʱ��
        static double fps[5] = { 0 };//5֡��ȡƽ��ֵ
        static int i = 0;//֡������
#endif // MYDEBUG


        //���ܴ�����Ϣ
        MSG msg;
        //while(PeekMessage(&msg, nullptr, 0x0400+2, 0x0400+3, PM_REMOVE))
        //    switch (msg.message)
        //    {
        //    case UIWM_WRITECONFIG:
        //            //�ͷ��ڴ�
        //        clearmemory();
        //            while(!data::init());
        //            setWindow();
        //            switch (data::cfg["mode"].asInt())
        //            {
        //            case 1:
        //                standard::init();
        //                break;
        //            case 2:
        //                keyboard::init();
        //                break;
        //            case 98:
        //                live2d_98::init();
        //                break;
        //            default:
        //                break;
        //            } 
        //        is_reload_for_wmmsg = true;
        //        break;
        //    case UIWM_WRITECONFIG_AND_RELOAD_FILE:

        //        break;
        //    default:
        //        is_reload_for_wmmsg = false;
        //        break;
        //    }

        if(PeekMessage(&msg, catHwnd, 0x0400 + 2, 0x0400 + 4, PM_REMOVE))
            switch (msg.message)
            {
            case UIWM_WRITECONFIG:
                //�ͷ��ڴ�
                clearmemory();
                while (!data::init());
                setWindow();
                switch (data::cfg["mode"].asInt())
                {
                case 1:
                    standard::init();
                    break;
                case 2:
                    keyboard::init();
                    break;
                case 98:
                    live2d_98::init();
                    break;
                default:
                    break;
                }
                is_reload_for_wmmsg = true;
                break;
            case UIWM_WRITECONFIG_AND_RELOAD_FILE:

                break;
            
            default:
                is_reload_for_wmmsg = false;
                break;
            }
        if (msgtimer.getElapsedTime() > sf::seconds(2))
        {
            msgtimer.restart();
            PostMessage(catHwnd, CATWM_ACTIVE, 0, 0);
        }


        //�¼���Ӧ
        sf::Event event;
        while (window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                //�������ctrl+r�������¼���config���������ô���
                if (event.key.code == sf::Keyboard::R && event.key.control)
                {
                    if (!is_reload) {
                        clearmemory();
                        while (!data::init());
                        setWindow();
                        switch (data::cfg["mode"].asInt())
                        {
                        case 1:
                            standard::init();
                            break;
                        case 2:
                            keyboard::init();
                            break;
                        case 98:
                            live2d_98::init();
                            break;
                        default:
                            break;
                        }
                    }
                    is_reload = true;
                }
                //�������ctrl+shift+S�����UIҳ��
                else if (event.key.code == sf::Keyboard::S && event.key.control && event.key.shift && is_UIThread_on == false && is_reload == false)
                {
                    On_Start_UI();
                    is_reload = true;
                }
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
                is_reload = false;
            }





        //ͼ�λ���

        //���������ͼ��
        clearCatWindow();

        //����è��
        drawCat(data::cfg["mode"].asInt());

        //MYDEBUG�µ�֡�ʻ���
#ifdef MYDEBUG
        //д��������
        fps[i] = sf::seconds(1) / FPStimeer.getElapsedTime();
        i++;
        if (i > 4)i = 0;

        //����֡��
        window.draw(sf::Text("FPS:"+ std::to_string(
        
            min(min(min(
                min(fps[0], fps[1]),
                min(fps[1], fps[2]),
                ), fps[3]), fps[4])
        
        ), catfont));
#endif // MYDEBUG 

        //��ʾ��������
        window.display();

        //ѭ���ö�
        if (data::cfg["decoration"]["topWindow"].asBool()) SetWindowPos(catHwnd, HWND_TOP, 1, 1, 1, 1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOCOPYBITS| SWP_SHOWWINDOW);
        

    }

    return 0;
}






