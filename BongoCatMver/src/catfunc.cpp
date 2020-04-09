#pragma once

#include "catfunc.h"
using namespace std;



//����һ������ΪN����Ƶѭ������
pSoundqueue creatSoundQueue(int n)
{
	//������һ���ڵ�
	pSoundqueue queuesoundplay = new soundqueue;
	queuesoundplay->index = 0;
	//�����һ���ڵ�
	pSoundqueue first = queuesoundplay;
	for (int i = 1; i < n; i++)
	{
		queuesoundplay->next = new soundqueue;
		queuesoundplay = queuesoundplay->next;
		queuesoundplay->index = i;
	}
	//�����һ���ڵ㲢���ӵ����п�ʼ
	queuesoundplay->next = first;
	//����ͷ�ڵ�
	return first;
}

//������Ϊindex�İ������ж�ȡ
pkeyList read_key_from_cfg(string index)
{
	pkeyList pkeylistcurrent = NULL;
	pkeyList key_list = NULL;
	if (!data::cfg[index][0].isNull())
	{
		pkeylistcurrent = new keyList;
		key_list = pkeylistcurrent;

		for (int i = 0; !data::cfg[index][i].isNull(); i++)
		{
			pkeylistcurrent->index = i;
			pkeylistcurrent->notelist = NULL;

			//������ϼ�����
			if (!data::cfg[index][i][0].isNull())
			{
				//������һ�������ڵ�
				pkeylistcurrent->notelist = new keyNote;
				pkeylistcurrent->notelist->key = data::cfg[index][i][0].asInt();
				pkeylistcurrent->notelist->next = NULL;

				//����һ������ϼ�������д����õ���ʱָ��
				pkeyNote current_note = pkeylistcurrent->notelist;
				for (int j = 1; !data::cfg[index][i][j].isNull(); j++)
				{
					current_note->next = new keyNote;
					current_note = current_note->next;
					current_note->key = data::cfg[index][i][j].asInt();
				}
				current_note->next = NULL;
			}
			if (!data::cfg[index][i + 1].isNull())
			{
				pkeylistcurrent->next = new keyList;
				pkeylistcurrent = pkeylistcurrent->next;
			}
		}
		if (pkeylistcurrent)
			pkeylistcurrent->next = NULL;
	}
	return key_list;
}
//������Ϊindex,index2�İ������ж�ȡ
pkeyList read_key_from_cfg(string index, string index2)
{
	pkeyList pkeylistcurrent = NULL;
	pkeyList key_list = NULL;
	if (!data::cfg[index][index2][0].isNull())
	{
		pkeylistcurrent = new keyList;
		key_list = pkeylistcurrent;

		for (int i = 0; !data::cfg[index][index2][i].isNull(); i++)
		{
			pkeylistcurrent->index = i;
			pkeylistcurrent->notelist = NULL;
			//������ϼ�����
			if (!data::cfg[index][index2][i][0].isNull())
			{
				//������һ�������ڵ�
				pkeylistcurrent->notelist = new keyNote;
				pkeylistcurrent->notelist->key = data::cfg[index][index2][i][0].asInt();
				pkeylistcurrent->notelist->next = NULL;

				//����һ������ϼ�������д����õ���ʱָ��
				pkeyNote current_note = pkeylistcurrent->notelist;
				for (int j = 1; !data::cfg[index][index2][i][j].isNull(); j++)
				{
					current_note->next = new keyNote;
					current_note = current_note->next;
					current_note->key = data::cfg[index][index2][i][j].asInt();
				}
				current_note->next = NULL;
			}
			if (!data::cfg[index][index2][i + 1].isNull())
			{
				pkeylistcurrent->next = new keyList;
				pkeylistcurrent = pkeylistcurrent->next;
			}
		}
		if (pkeylistcurrent)
			pkeylistcurrent->next = NULL;
	}
	return key_list;
}
//������Ϊindex,index2�Ľ�����ͼƬ��ȡ
pspriteList read_img(string index, string index2)
{
	pspriteList pspritelistcurrent = NULL;
	pspriteList sprite_list = NULL;


	if (!data::cfg[index][index2][0].isNull())
	{
		pspritelistcurrent = new spriteList;
		pspritelistcurrent->index = 0;

		pspritelistcurrent->sprite.setTexture(data::load_texture2("img/" + index + "/" + index2 + "/0.png"));
		pspritelistcurrent->next = NULL;
		sprite_list = pspritelistcurrent;
	}
	else return NULL;
	for (int i = 1; !data::cfg[index][index2][i].isNull(); i++)
	{
		pspritelistcurrent->next = new spriteList;
		pspritelistcurrent = pspritelistcurrent->next;
		pspritelistcurrent->index = i;

		pspritelistcurrent->sprite.setTexture(data::load_texture2("img/" + index + "/" + index2 + "/" + std::to_string(i) + ".png"));
	}
	pspritelistcurrent->next = NULL;
	return sprite_list;
}

//������Ϊindex,index2�Ľ�������Ƶ��ȡ
psoundBufferList read_sound(string index, string index2)
{
	psoundBufferList psoundbufferlistcurrent = NULL;
	psoundBufferList soundbuffer_list = NULL;


	if (!data::cfg[index][index2][0].isNull())
	{
		psoundbufferlistcurrent = new soundBufferList;
		psoundbufferlistcurrent->index = 0;


		if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(0) + ".wav")))
			if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(0) + ".ogg")))
				if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(0) + ".flac")))
					;






		psoundbufferlistcurrent->next = NULL;
		soundbuffer_list = psoundbufferlistcurrent;
	}
	else return NULL;
	for (int i = 1; !data::cfg[index][index2][i].isNull(); i++)
	{
		psoundbufferlistcurrent->next = new soundBufferList;
		psoundbufferlistcurrent = psoundbufferlistcurrent->next;
		psoundbufferlistcurrent->index = i;

		if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(i) + ".wav")))
			if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(i) + ".ogg")))
				if (!psoundbufferlistcurrent->soundbuffer.loadFromFile(("img/" + index + "/" + index2 + "/" + std::to_string(i) + ".flac")))
					;
	}
	psoundbufferlistcurrent->next = NULL;
	return soundbuffer_list;
}



//������Ϊindex,index2�Ľ�㴴����ʱ����
ptimeList creat_timelist(string index, string index2)
{
	ptimeList ptimeListcurrent = NULL;
	ptimeList time_list = NULL;


	if (!data::cfg[index][index2][0].isNull())
	{
		ptimeListcurrent = new timeList;
		ptimeListcurrent->index = 0;
		ptimeListcurrent->time = sf::seconds(0);
		ptimeListcurrent->next = NULL;
		time_list = ptimeListcurrent;
	}
	else return NULL;

	for (int i = 1; !data::cfg[index][index2][i].isNull(); i++)
	{
		ptimeListcurrent->next = new timeList;
		ptimeListcurrent = ptimeListcurrent->next;
		ptimeListcurrent->index = i;
		ptimeListcurrent->time = sf::seconds(0);
	}
	ptimeListcurrent->next = NULL;
	return time_list;
}

//������Ϊindex,index2�Ľ�㴴��״̬����
pstateList creat_statelist(string index, string index2)
{
	pstateList pstateListcurrent = NULL;
	pstateList state_list = NULL;


	if (!data::cfg[index][index2][0].isNull())
	{
		pstateListcurrent = new stateList;
		pstateListcurrent->index = 0;
		pstateListcurrent->state = false;
		pstateListcurrent->next = NULL;
		state_list = pstateListcurrent;
	}
	else return NULL;

	for (int i = 1; !data::cfg[index][index2][i].isNull(); i++)
	{
		pstateListcurrent->next = new stateList;
		pstateListcurrent = pstateListcurrent->next;
		pstateListcurrent->index = i;
		pstateListcurrent->state = false;
	}
	pstateListcurrent->next = NULL;
	return state_list;
}

//��ȡʱ�������� ʱ��ֵ���Ľ������� ����ʾ���°��£�
int max_time(ptimeList timelist)
{
	sf::Time maxtime;
	int index = 0;
	if (timelist != NULL)
		maxtime = timelist->time;
	for (int i = 0; timelist != NULL; i++)
	{
		if (timelist->time > maxtime)
		{
			maxtime = timelist->time;
			index = i;
		};
		timelist = timelist->next;
	}
	return index;
}

//�����ֲ�ͼƬ��ͬʱ����ʱֻ������󴥷��Ķ���
void drawhand(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent, ptimeList ptimeListcurrent, sf::Clock clock, sf::Time init_time, sf::Sprite up)
{
	int hand_state = -1;
	ptimeList ptime = ptimeListcurrent; //��¼ָ���ʼ��ֵ
	//�ж����ֵ�ǰ״̬
	for (int i = 0; pkeylistcurrent != NULL; i++)
	{
		//����һ��������ʱ������ָ��
		pkeyNote pkeynotecurrent = pkeylistcurrent->notelist;
		//����һ�����ڴ洢�жϽ����boolֵ
		bool bpress = true;
		while (pkeynotecurrent != NULL && bpress)
		{
			bpress = GetKeyState(pkeynotecurrent->key) & 0x8000;//todo:�����ֵʱ���ʳ�ͻ��bug
			pkeynotecurrent = pkeynotecurrent->next;
		}
		//���һ����ϼ������£���ôbpress=true;
		if (bpress) {
			hand_state = i;
			pkeylistcurrent->state = true;
			//���һ�������°��µģ��ͱ���������İ���ʱ��
			if (pkeylistcurrent->last_state == false)
				ptimeListcurrent->time = clock.getElapsedTime();
		}
		else
			//������ʱ����Ϊ��ʼ��ʱ��ʱ��
			ptimeListcurrent->time = init_time;
		pkeylistcurrent->last_state = pkeylistcurrent->state;
		pkeylistcurrent->state = false;
		//ָ�����
		pkeylistcurrent = pkeylistcurrent->next;
		ptimeListcurrent = ptimeListcurrent->next;
	}
	if (hand_state != -1) {
		for (int i = 0; i < max_time(ptime); i++)
			pspriteListcurrent = pspriteListcurrent->next;
		window.draw(pspriteListcurrent->sprite);
	}
	else
		window.draw(up);
}
//���Ƽ�����Ч��ͬʱ����ʱ����ͼƬ������
void drawkeyboard(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent)
{
	//�жϼ��̵�ǰ״̬
	for (int i = 0; pkeylistcurrent != NULL; i++)
	{
		//����һ��������ʱ������ָ��
		pkeyNote pkeynotecurrent = pkeylistcurrent->notelist;
		//����һ�����ڴ洢�жϽ����boolֵ
		bool bpress = true;
		while (pkeynotecurrent != NULL && bpress)
		{
			bpress = GetKeyState(pkeynotecurrent->key) & 0x8000;//todo:�����ֵʱ���ʳ�ͻ��bug
			pkeynotecurrent = pkeynotecurrent->next;
		}
		//���һ����ϼ������£���ôbpress=true;
		if (bpress) {
			;
			pkeylistcurrent->state = true;
			window.draw(pspriteListcurrent->sprite);
		}
		pkeylistcurrent->last_state = pkeylistcurrent->state;
		pkeylistcurrent->state = false;
		//ָ�����
		pkeylistcurrent = pkeylistcurrent->next;
		pspriteListcurrent = pspriteListcurrent->next;
	}
}

//���ƿɳ����ı��飬�������ȡ����ʽ
void drawface(pkeyList pkeylistcurrent, pspriteList pspriteListcurrent, pstateList pstateListcurrent)
{
	int index = -1;
	pstateList statelist = pstateListcurrent;	//��¼ָ���ʼֵ
	pspriteList   spriteList = pspriteListcurrent;
	//�жϰ�����ǰ״̬
	for (int i = 0; pkeylistcurrent != NULL; i++)
	{
		//����һ��������ʱ������ָ��
		pkeyNote pkeynotecurrent = pkeylistcurrent->notelist;
		//����һ�����ڴ洢�жϽ����boolֵ
		bool bpress = true;
		while (pkeynotecurrent != NULL && bpress)
		{
			bpress = GetKeyState(pkeynotecurrent->key) & 0x8000;//todo:�����ֵʱ���ʳ�ͻ��bug
			pkeynotecurrent = pkeynotecurrent->next;
		}
		//���һ����ϼ������£���ôbpress=true;
		if (bpress) {
			;
			pkeylistcurrent->state = true;
			if (pkeylistcurrent->last_state == false)
				//��һ�����鰴��ʱ��¼��ǰ����
				index = i;
		}
		pkeylistcurrent->last_state = pkeylistcurrent->state;
		pkeylistcurrent->state = false;
		//ָ�����
		pkeylistcurrent = pkeylistcurrent->next;
		pspriteListcurrent = pspriteListcurrent->next;
		pstateListcurrent = pstateListcurrent->next;
	}
	//������������״̬
	pstateListcurrent = statelist;
	if (index != -1)
	{
		for (int i = 0; i < index; i++)
		{
			pstateListcurrent->state = false;
			pstateListcurrent = pstateListcurrent->next;
		}
		if (pstateListcurrent->state == false)
			pstateListcurrent->state = true;
		else
			pstateListcurrent->state = false;
		pstateListcurrent = pstateListcurrent->next;
		while (pstateListcurrent != NULL)
		{
			pstateListcurrent->state = false;
			pstateListcurrent = pstateListcurrent->next;
		}
	}
	//����״ֵ̬���ű���
	while (statelist != NULL && statelist->state == false)
	{
		statelist = statelist->next;
		spriteList = spriteList->next;
	}
	if (statelist != NULL)
	{
		window.draw(spriteList->sprite);
	}
}

//���ſɵ���ͬʱ���ŵ���Ƶ
void playsound(pkeyList pkeylistcurrent, psoundBufferList psoundBufferListcurrent, pSoundqueue psoundqueuecurrent)
{
	psoundBufferList psoundbuffer = psoundBufferListcurrent; //��¼ָ���ʼ��ֵ
	//�ж���Ƶ������ǰ״̬
	for (int i = 0; pkeylistcurrent != NULL; i++)
	{
		//����һ��������ʱ������ָ��
		pkeyNote pkeynotecurrent = pkeylistcurrent->notelist;
		//����һ�����ڴ洢�жϽ����boolֵ
		bool bpress = true;
		while (pkeynotecurrent != NULL && bpress)
		{
			bpress = GetKeyState(pkeynotecurrent->key) & 0x8000;//todo:�����ֵʱ���ʳ�ͻ��bug
			pkeynotecurrent = pkeynotecurrent->next;
		}
		//���һ����ϼ������£���ôbpress=true;
		if (bpress) {
			pkeylistcurrent->state = true;
			//���һ�������°��µģ��Ͳ��������Ƶ

			if (pkeylistcurrent->last_state == false)
				//todo
			{

				//����ѯ100λ��Ƶ״̬����ѯ�������˳�

				for (int counter = 0; psoundqueuecurrent->sound.getStatus() == sf::Sound::Playing && counter < 100; counter++)
					psoundqueuecurrent = psoundqueuecurrent->next;

				psoundqueuecurrent->sound.setBuffer(psoundBufferListcurrent->soundbuffer);
				psoundqueuecurrent->sound.play();
				psoundqueuecurrent = psoundqueuecurrent->next;
			}
		}
		pkeylistcurrent->last_state = pkeylistcurrent->state;
		pkeylistcurrent->state = false;
		//ָ�����
		pkeylistcurrent = pkeylistcurrent->next;
		psoundBufferListcurrent = psoundBufferListcurrent->next;
	}
}

//�԰���ͬһ����λ��ʱ���жϵ�ǰ��λ��Ƶ�ķ�ʽ���в���
void playsound(pkeyList pkeylistcurrent, psoundList psoundcurrent)
{
	//�ж���Ƶ������ǰ״̬
	for (int i = 0; pkeylistcurrent != NULL; i++)
	{
		//����һ��������ʱ������ָ��
		pkeyNote pkeynotecurrent = pkeylistcurrent->notelist;
		//����һ�����ڴ洢�жϽ����boolֵ
		bool bpress = true;
		while (pkeynotecurrent != NULL && bpress)
		{
			bpress = GetKeyState(pkeynotecurrent->key) & 0x8000;//todo:�����ֵʱ���ʳ�ͻ��bug
			pkeynotecurrent = pkeynotecurrent->next;
		}
		//���һ����ϼ������£���ôbpress=true;
		if (bpress) {
			pkeylistcurrent->state = true;
			//���һ�������°��µģ��Ͳ��������Ƶ
			if (pkeylistcurrent->last_state == false)
			{
				psoundcurrent->sound.play();
			}
		}
		pkeylistcurrent->last_state = pkeylistcurrent->state;
		pkeylistcurrent->state = false;
		//ָ�����
		pkeylistcurrent = pkeylistcurrent->next;
		psoundcurrent = psoundcurrent->next;
	}
}


//������Ϊindex,index2�Ľ�㴴��״̬����
psoundList creat_soundlist(string index, string index2)
{
	psoundList psoundListcurrent = NULL;
	psoundList sound_list = NULL;


	if (!data::cfg[index][index2][0].isNull())
	{
		psoundListcurrent = new soundList;
		psoundListcurrent->index = 0;
		psoundListcurrent->next = NULL;
		sound_list = psoundListcurrent;
	}
	else return NULL;

	for (int i = 1; !data::cfg[index][index2][i].isNull(); i++)
	{
		psoundListcurrent->next = new soundList;
		psoundListcurrent = psoundListcurrent->next;
		psoundListcurrent->index = i;
	}
	psoundListcurrent->next = NULL;
	return sound_list;
}

std::tuple<double, double> bezier(double ratio, std::vector<double>& points, int length)
{
	double fact[22] = { 0.001, 0.001, 0.002, 0.006, 0.024, 0.12, 0.72, 5.04, 40.32, 362.88, 3628.8, 39916.8, 479001.6, 6227020.8, 87178291.2, 1307674368.0, 20922789888.0, 355687428096.0, 6402373705728.0, 121645100408832.0, 2432902008176640.0, 51090942171709440.0 };
	int nn = (length / 2) - 1;
	double xx = 0;
	double yy = 0;

	for (int point = 0; point <= nn; point++)
	{
		double tmp = fact[nn] / (fact[point] * fact[nn - point]) * pow(ratio, point) * pow(1 - ratio, nn - point);
		xx += points[2 * point] * tmp;
		yy += points[2 * point + 1] * tmp;
	}
	return std::make_tuple(xx / 1000, yy / 1000);
}

//���ݲ����õ�һ���ֵ�����
void setrighthand(double x, double y, double* pmpos0, double* pmpos1, std::vector<double>* ppss2, double dx, double dy)
{
	// initializing pss and pss2 (kuvster's magic)
	int oof = 6;
	std::vector<double> pss = { 211.0, 159.0 };
	double dist = hypot(211 - x, 159 - y);
	double centreleft0 = 211 - 0.7237 * dist / 2;
	double centreleft1 = 159 + 0.69 * dist / 2;
	for (double i = 1; i < oof; i++)
	{
		double p0;
		double p1;
		std::vector<double> bez = { 211, 159, centreleft0, centreleft1, x, y };
		std::tie(p0, p1) = bezier(i / oof, bez, 6);
		pss.push_back(p0);
		pss.push_back(p1);
	}
	pss.push_back(x);
	pss.push_back(y);
	double a = y - centreleft1;
	double b = centreleft0 - x;
	double le = hypot(a, b);
	a = x + a / le * 60;
	b = y + b / le * 60;
	int a1 = 258;
	int a2 = 228;
	dist = hypot(a1 - a, a2 - b);
	double centreright0 = a1 - 0.6 * dist / 2;
	double centreright1 = a2 + 0.8 * dist / 2;
	int push = 20;
	double s = x - centreleft0;
	double t = y - centreleft1;
	le = hypot(s, t);
	s *= push / le;
	t *= push / le;
	double s2 = a - centreright0;
	double t2 = b - centreright1;
	le = hypot(s2, t2);
	s2 *= push / le;
	t2 *= push / le;
	for (double i = 1; i < oof; i++)
	{
		double p0;
		double p1;
		std::vector<double> bez = { x, y, x + s, y + t, a + s2, b + t2, a, b };
		std::tie(p0, p1) = bezier(i / oof, bez, 8);
		pss.push_back(p0);
		pss.push_back(p1);
	}
	pss.push_back(a);
	pss.push_back(b);
	for (double i = oof - 1; i > 0; i--)
	{
		double p0;
		double p1;
		std::vector<double> bez = { 1.0 * a1, 1.0 * a2, centreright0, centreright1, a, b };
		std::tie(p0, p1) = bezier(i / oof, bez, 6);
		pss.push_back(p0);
		pss.push_back(p1);
	}
	pss.push_back(a1);
	pss.push_back(a2);
	*pmpos0 = (a + x) / 2 - 52 - 15;
	*pmpos1 = (b + y) / 2 - 34 + 5;


	const int iter = 25;

	*ppss2 = { pss[0] + dx, pss[1] + dy };
	for (double i = 1; i < iter; i++)
	{
		double p0;
		double p1;
		std::tie(p0, p1) = bezier(i / iter, pss, 38);
		ppss2->push_back(p0 + dx);
		ppss2->push_back(p1 + dy);
	}
	ppss2->push_back(pss[36] + dx);
	ppss2->push_back(pss[37] + dy);
}
//���������������
void drawline(std::vector<double> pss2, int red_value, int green_value, int blue_value)
{

	// drawing first arm arc
	int shad = 77;
	sf::VertexArray edge(sf::TriangleStrip, 52);
	double width = 7;
	sf::CircleShape circ(width / 2);
	circ.setFillColor(sf::Color(red_value, green_value, blue_value, shad));
	circ.setPosition(pss2[0] - width / 2, pss2[1] - width / 2);

	window.draw(circ);
	for (int i = 0; i < 50; i += 2)
	{
		double vec0 = pss2[i] - pss2[i + 2];
		double vec1 = pss2[i + 1] - pss2[i + 3];
		double dist = hypot(vec0, vec1);
		edge[i].position = sf::Vector2f(pss2[i] + vec1 / dist * width / 2, pss2[i + 1] - vec0 / dist * width / 2);
		edge[i + 1].position = sf::Vector2f(pss2[i] - vec1 / dist * width / 2, pss2[i + 1] + vec0 / dist * width / 2);
		edge[i].color = sf::Color(0, 0, 0, shad);
		edge[i + 1].color = sf::Color(0, 0, 0, shad);
		width -= 0.08;
	}
	double vec0 = pss2[50] - pss2[48];
	double vec1 = pss2[51] - pss2[49];
	double dist = hypot(vec0, vec1);
	edge[51].position = sf::Vector2f(pss2[50] + vec1 / dist * width / 2, pss2[51] - vec0 / dist * width / 2);
	edge[50].position = sf::Vector2f(pss2[50] - vec1 / dist * width / 2, pss2[51] + vec0 / dist * width / 2);
	edge[50].color = sf::Color(red_value, green_value, blue_value, shad);
	edge[51].color = sf::Color(red_value, green_value, blue_value, shad);
	window.draw(edge);
	circ.setRadius(width / 2);
	circ.setPosition(pss2[50] - width / 2, pss2[51] - width / 2);
	window.draw(circ);

	// drawing second arm arc
	sf::VertexArray edge2(sf::TriangleStrip, 52);
	width = 6;
	sf::CircleShape circ2(width / 2);
	circ2.setFillColor(sf::Color(red_value, green_value, blue_value));
	circ2.setPosition(pss2[0] - width / 2, pss2[1] - width / 2);
	window.draw(circ2);
	for (int i = 0; i < 50; i += 2)
	{
		vec0 = pss2[i] - pss2[i + 2];
		vec1 = pss2[i + 1] - pss2[i + 3];
		double dist = hypot(vec0, vec1);
		edge2[i].position = sf::Vector2f(pss2[i] + vec1 / dist * width / 2, pss2[i + 1] - vec0 / dist * width / 2);
		edge2[i + 1].position = sf::Vector2f(pss2[i] - vec1 / dist * width / 2, pss2[i + 1] + vec0 / dist * width / 2);
		edge2[i].color = sf::Color(red_value, green_value, blue_value);
		edge2[i + 1].color = sf::Color(red_value, green_value, blue_value);
		width -= 0.08;
	}
	vec0 = pss2[50] - pss2[48];
	vec1 = pss2[51] - pss2[49];
	dist = hypot(vec0, vec1);
	edge2[51].position = sf::Vector2f(pss2[50] + vec1 / dist * width / 2, pss2[51] - vec0 / dist * width / 2);
	edge2[50].position = sf::Vector2f(pss2[50] - vec1 / dist * width / 2, pss2[51] + vec0 / dist * width / 2);
	edge2[50].color = sf::Color(red_value, green_value, blue_value);
	edge2[51].color = sf::Color(red_value, green_value, blue_value);
	window.draw(edge2);
	circ2.setRadius(width / 2);
	circ2.setPosition(pss2[50] - width / 2, pss2[51] - width / 2);
	window.draw(circ2);
}

//��ʼ������豸
int DInput_Init_Mouse(void)
{
	HRESULT hr;
	if (FAILED(::DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpdi, NULL)))
	{
		return 0;
	}

	//��������豸
	if (lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL) != DI_OK)
		return(0);

	//�������Э���ȼ�������Ϊ��̨/�Ƕ�ռģʽ
	if (lpdimouse->SetCooperativeLevel(catHwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
		return(0);

	DIPROPDWORD     property;

	property.diph.dwSize = sizeof(DIPROPDWORD);
	property.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	property.diph.dwObj = 0;
	property.diph.dwHow = DIPH_DEVICE;
	property.dwData = 16;


	//�������ݸ�ʽ,����Ӧ�����ݸ�ʽΪc_dfDIMouse
	if (lpdimouse->SetDataFormat(&c_dfDIMouse) != DI_OK)
		return(0);

	hr = lpdimouse->SetProperty(DIPROP_BUFFERSIZE, &property.diph);

	if FAILED(hr)
	{
		// ʧ��
		return FALSE;
	}


	//��ȡ���
	if (lpdimouse->Acquire() != DI_OK)
		return(0);


}
//������ȡ����
int DInput_Read_Mouse(void)
{
	//��ȡ�������
	if (lpdimouse)
	{
		if (lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state_d7) != DI_OK)
			return(0);
	}
	else
	{
		//���û�в�����꣬��������ݽṹ��Ϊ0
		memset(&mouse_state_d7, 0, sizeof(mouse_state_d7));
		return(0);
	}
	return(1);
}

//�ͷ����
void DInput_Release_Mouse(void)
{
	if (lpdimouse)
	{
		lpdimouse->Unacquire();
		lpdimouse->Release();
	}
}
//�����������
HRESULT UpdateInputState(void)
{
	DWORD   i;

	if (lpdimouse != NULL)
	{
		DIDEVICEOBJECTDATA  didod;  // Receives buffered data
		DWORD               dwElements;
		HRESULT             hr;

		while (TRUE)
		{
			dwElements = 1;                     // ÿ�δӻ������ж�һ������
			hr = lpdimouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &didod, &dwElements, 0);

			if FAILED(hr)
			{
				// ������һ������
				if (hr == DIERR_INPUTLOST)
				{
					hr = lpdimouse->Acquire();    // ��ͼ����ȡ���豸
					if FAILED(hr)
					{
						return S_FALSE;         // ʧ��
					}
				}
			}
			else
				if (dwElements == 1)
				{
					switch (didod.dwOfs)
					{
					case DIMOFS_X:              // X ��ƫ����
						// didod.dwData ���Ǿ���ƫ�����ֵ����λΪ����
						point.x += didod.dwData;
						break;
					case DIMOFS_Y:              // Y ��ƫ����
						// didod.dwData ���Ǿ���ƫ�����ֵ����λΪ����
						point.y += didod.dwData;
						break;
					case DIMOFS_BUTTON0:        // 0 �ż��������״̬
						// didod.dwData ���Ǿ���״ֵ̬
						// ���ֽ����λΪ 1 ���ʾ����
						// ���ֽ����λΪ 0 ��ʾδ����
						break;
					case DIMOFS_BUTTON1:        // 1 �ż����Ҽ���״̬
						// ͬ��
						break;
					case DIMOFS_BUTTON2:        // 2 �ż����м���״̬
						// ͬ��
						break;
					case DIMOFS_BUTTON3:        // 3 �ż�״̬
						// ͬ��
						break;
					}
				}
				else if (dwElements == 0) break;      // ����������
		}
	}
	return S_OK;
}