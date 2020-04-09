#pragma once

#include <header.hpp>

using namespace std;



//����һ������ΪN����Ƶѭ������
pSoundqueue creatSoundQueue(int n);
//������Ϊindex�İ������ж�ȡ
pkeyList read_key_from_cfg(string index);
//������Ϊindex,index2�İ������ж�ȡ
pkeyList read_key_from_cfg(string index, string index2);
//������Ϊindex,index2�Ľ�����ͼƬ��ȡ
pspriteList read_img(string index, string index2);
//������Ϊindex,index2�Ľ�������Ƶ��ȡ
psoundBufferList read_sound(string index, string index2);
//������Ϊindex,index2�Ľ�㴴����ʱ����
ptimeList creat_timelist(string index, string index2);
//������Ϊindex,index2�Ľ�㴴��״̬����
pstateList creat_statelist(string index, string index2);
//������Ϊindex,index2�Ľ�㴴��״̬����
psoundList creat_soundlist(string index, string index2);

//��ȡʱ�������� ʱ��ֵ���Ľ������� ����ʾ���°��£�
int max_time(ptimeList timelist);

//�����ֲ�ͼƬ��ͬʱ����ʱֻ������󴥷��Ķ���
void drawhand(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent, ptimeList ptimeListcurrent, sf::Clock clock, sf::Time init_time, sf::Sprite up);

//���Ƽ�����Ч��ͬʱ����ʱ����ͼƬ������
void drawkeyboard(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent);

//���ƿɳ����ı��飬�������ȡ����ʽ
void drawface(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent, pstateList pstateListcurrent);

//���ſɵ���ͬʱ���ŵ���Ƶ
void playsound(pkeyList pkeylistcurrent, psoundBufferList psoundBufferListcurrent, pSoundqueue psoundqueuecurrent);
//�԰���ͬһ����λ��ʱ���жϵ�ǰ��λ��Ƶ�ķ�ʽ���в���
void playsound(pkeyList pkeylistcurrent, psoundList psoundcurrent);



std::tuple<double, double> bezier(double ratio, std::vector<double>& points, int length);

//���ݲ����õ�һ���ֵ�����
void setrighthand(double x, double y, double* pmpos0, double* pmpos1, std::vector<double>* ppss2, double dx, double dy);
//���������������
void drawline(std::vector<double> pss2, int red_value, int green_value, int blue_value);

//���ȡ����йصĺ���
int DInput_Init_Mouse(void);
int DInput_Read_Mouse(void);
void DInput_Release_Mouse(void);
HRESULT UpdateInputState(void);