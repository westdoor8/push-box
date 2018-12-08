#include"function.h"

void init() {

	//�öδ��빦�������ع�꣬������win32��̽ӿڣ�����Ҫ����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���ھ��
	CONSOLE_CURSOR_INFO cci;//ʵ�л�һ������̨�����Ϣ��
	GetConsoleCursorInfo(hOut, &cci);//��ȡ�����Ϣ
	cci.bVisible = FALSE;//���ع��
	SetConsoleCursorInfo(hOut, &cci);//���ù����Ϣ

	system("title ������1.0");//�趨��������
	system("mode con cols=120 lines=30");//�趨���ڴ�С
}

void mainloop() {
	int level;//��ǰ�ؿ�
	int level_option;//ѡ��Ĺؿ�
	int scenes;//����
	char option;//����ָ��
	int isEnd;//�Ƿ����

	//��ʼ������
	level = 0;//��ʼ����ǰ�ؿ�Ϊ��һ�أ���0���𣬷�ΧΪ0-maps_num��
	level_option = 1;//��ʼ��ѡ��ؿ�Ϊ��һ�أ���1����
	scenes = 0;//��ʼ������Ϊ������
	isEnd = 0;//��ʼ�������жϱ���Ϊ0��false��

	//���ƽ���
	//������
	char *main_interface[] = {//���ֶ��巽ʽ��ʡ�ڴ�
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ��ʼ(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   �˳�(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	//���˵�2
	char *menu2[] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   ��ͷ��ʼ(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ѡ��(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ����(R)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|"
	};


	//��ʼ��Ϣѭ��
	while (1) {//������ԶΪ�棬����ѭ��

		//�����ӡ
		system("cls");//�����Ļ
		switch (scenes) {
		case 0:
			//��ӡ������
			for (int i = 0; i < 11; i++)
				puts(main_interface[i]);
			break;
		case 1:
			//��ӡ���˵�2
			for (int i = 0; i < 11; i++)
				puts(menu2[i]);
			break;
		case 2:
			//��ӡ�ؿ�ѡ�����
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("��ѡ��ؿ�(1-%d):%d", maps_num, level_option);
			break;
		default:
			break;
		}

		//��������
		if (scenes < 3) {
			option = getch();//��ȡ��������
			option = tolower(option);//�����������ĸ���ΪСд
		}

		//�¼��ж�
		switch (scenes) {
		case 0://�������¼��ж�
			if (option == 's')//�������Ϊ's',��������˵�2
				scenes = 1;
			else if (option == 27) {//�������Ϊesc��27�������˳���Ϸ
				isEnd = 1;
			}
			break;
		case 1://���˵�2�¼��ж�
			if (option == 'r' || option == 27)//�����ϼ��˵�
				scenes = 0;
			else if (option == 'a') {//�ӵ�һ�ؿ�ʼ��Ϸ
				scenes = 3;
			}
			else if (option == 'x') {//����ؿ�ѡ�����
				scenes = 2;
			}
			break;
		case 2://�ؿ�ѡ������¼��ж�
			   //���level_option����1���С1�����level_optionС��maps_num������1��������ж��Է�ֹԽ��
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 13 || option == 32)) {//�������Ϊ�ո�32����س���13�������ѡ��Ĺؿ�
				level = level_option - 1;//����ǰ�ؿ�����Ϊѡ��Ĺؿ������Ӧ��ϵΪ level = level_option - 1
				scenes = 4;
			}
			else if (option == 27)
				scenes = 1;
			break;
		case 3://��ͷ��ʼ
			level = 0;
			scenes = gameloop(level);//������Ϸ
			break;
		case 4://��ʼ��ǰ�ؿ�
			scenes = gameloop(level);
			break;
		case 5://������һ��
			level++;
			scenes = 4;
			break;
		case 6://ͨ����������
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}

		if (isEnd)//��������жϱ���Ϊ1��true��������ѭ�������˳���Ϸ
			break;
	}
}

int gameloop(int level)
{
	//��������

	int x, y;//x ������, y ������
	int wide;//��ͼ���
	char option;//��Ϸ�����ж�ȡ������Ϣ
	int scenes;//��ǰ����
	int isEnd;//�����жϱ���
	int reValue;//����ֵ�������泡��

	//������Ϸ��ͼ
	char map[50][50] = { 0 };

	//���������飬��¼�յ�����
	int aim_x[50] = { 0 }, aim_y[50] = { 0 }, xnum, ynum;

	int restep_num;//��¼ʣ�೷������
	int step_num;//��¼�����ܲ���
	int isUndo;//��¼�Ƿ�����
	int lastStep_num;//��¼��һ��������ǰ���ߵĲ���
	int box_x, box_y;//��¼��һ��������ǰ�������
	int box_nx, box_ny;//��¼��һ�������Ӻ��������
	int last_x, last_y;//��¼��һ��������ǰ��ɫ������

	//��Ϸ��ʼ��

	//��ʼ������
	wide = 0;
	step_num = 0;
	restep_num = 3;
	option = NULL;
	xnum = ynum = 0;
	isUndo = 0;
	scenes = 0;
	reValue = 0;
	isEnd = 0;

	//��ȡ��ͼ
	LoadMap(level, map);

	//�����ͼ���
	wide = strlen(map[0]);

	//��ʼ����ʼλ��
	for (int i = 0; i < 20; i++) 
	{
		for (int t = 0; map[i][t] != '\0'; t++)
			if (map[i][t] == '@')
			{
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	//Ѱ���յ�����
	for (int i = 2; i < 20; i++) 
	{
		for (int t = 2; map[i][t] != '\0'; t++)
		{
			if (map[i][t] == 'X' || map[i][t] == 'Q')
			{
				aim_x[xnum] = i;
				aim_y[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map[i][1] == '|') 
			{
				i = 99;
				break;
			}
		}
	}

	//��Ϸ��ѭ��
	while (1) {

		//�����ӡ
		system("cls");//�����Ļ
		switch (scenes) 
		{
		case 0:
			//��Ϸ����
			printf("\n\n\n\n\t\t\t\t\t\t         ��%d��", level + 1);
			printf("\n\n");
			for (int i = 0; i <= 17; i++)
			{
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map[i]);
			}
			printf("\t\t\t\t\t\t������%d  ʣ�೷��������%d", step_num, restep_num);
			printf("\n\n\t\t\t\t\t      ���汾��(Q) ����(U) �˵�(ESC)");
			break;
		case 1:
			//��ͣ����
			printf("\n\n\n\n\n\t\t\t\t\t\t        ����(R)\n");
			if (level == maps_num - 1)//�����ǰ�ؿ�Ϊ���һ�أ�����ʾ"��һ��(N)"
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(Q)  ���˵�(M)  \n");
			else
				printf("\n\n\t\t\t\t         ѡ��(X)  ����(Q)  ��һ��(N)  ���˵�(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      ����˵��");
			printf("\n\n\t\t\t\t\t        W:��  S:��  A:��  D:��");
			printf("\n\n\t\t\t\t\t         @:��  O:����  X:�յ� ");
			break;
		case 2:
			//���ؽ���
			if (level == maps_num - 1)//�����ǰ�ؿ�Ϊ���һ��
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t���Ѿ������һ���ˣ�");
			else
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  ����!");
			printf("\n\n\t\t\t\t\t\t    �����ܼƲ�����%d", step_num);
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t\t  ѡ��(X)  ����(Q)  ���˵�(M)  \n");
			else
				printf("\n\n\t\t\t\t\t  ѡ��(X)  ����(Q)  ��һ��(N)  ���˵�(M)  \n");
			break;
		default:
			break;
		}

		//��������
		option = getch();//��ȡ��������
		option = tolower(option);//�����������ĸ���ΪСд

		//�¼��ж�
		switch (scenes)
		{
		case 0:
			if (option == 's') {//�����ƶ�
				//��ǰ���ǿյػ��߿�Ŀ�ĵ�ʱ�����ƶ���ȥ
				if (map[x + 1][y] == ' ' || map[x + 1][y] == 'X') {
					map[x][y] = ' ';//����ɫ��ǰλ�ø���Ϊ�յأ������λ��Ӧ��ΪĿ�ĵ����ǽ��ں���������д���
					x++;//���½�ɫλ��
					map[x][y] = '@';//���µ�λ�ø���Ϊ��ɫ
					step_num++;//�ƶ�������1
				}
				//���ǰ����������������ͬ�������һλ�ò�Ϊǽ��������ʱ�����Խ���ǰ�����ƶ���ȥ
				else if ((map[x + 1][y] == 'O' || map[x + 1][y] == 'Q') && map[x + 2][y] != 'O' && map[x + 2][y] != 'Q' && map[x + 2][y] != '#') {
					map[x][y] = ' ';

					//��¼�ƶ�����ǰ��ɫ������
					last_x = x;
					last_y = y;

					x++;

					//��¼�ƶ�����ǰ���ӵ�����
					box_nx = x;
					box_ny = y;

					map[x][y] = '@';
					map[x + 1][y] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
					isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

					//��¼���һ�α��ƶ����ӵ�����
					box_x = x + 1;
					box_y = y;

					lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
					step_num++;
				}
			}
			else if (option == 'w') 
			{//�����ƶ�
				if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X')
				{
					map[x][y] = ' ';
					x--;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x - 1][y] == 'O' || map[x - 1][y] == 'Q') && map[x - 2][y] != 'O' && map[x - 2][y] != 'Q' && map[x - 2][y] != '#') {
					map[x][y] = ' ';

					//��¼�ƶ�����ǰ��ɫ������
					last_x = x;
					last_y = y;

					x--;

					//��¼�ƶ�����ǰ���ӵ�����
					box_nx = x;
					box_ny = y;

					map[x][y] = '@';
					map[x - 1][y] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
					isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

					//��¼���һ�α��ƶ����ӵ�����
					box_x = x - 1;
					box_y = y;

					lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
					step_num++;
				}
			}
			else if (option == 'a')
			{//�����ƶ�
				if (map[x][y - 1] == ' ' || map[x][y - 1] == 'X') 
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x][y - 1] == 'O' || map[x][y - 1] == 'Q') && map[x][y - 2] != 'O' && map[x][y - 2] != 'Q' && map[x][y - 2] != '#')
				{
					map[x][y] = ' ';

					//��¼�ƶ�����ǰ��ɫ������
					last_x = x;
					last_y = y;

					y--;

					//��¼�ƶ�����ǰ���ӵ�����
					box_nx = x;
					box_ny = y;

					map[x][y] = '@';
					map[x][y - 1] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
					isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

					//��¼���һ�α��ƶ����ӵ�����
					box_x = x;
					box_y = y - 1;

					lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
					step_num++;
				}
				break;
			}
			else if (option == 'd')
			{//�����ƶ�
				if (map[x][y + 1] == ' ' || map[x][y + 1] == 'X') 
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x][y + 1] == 'O' || map[x][y + 1] == 'Q') && map[x][y + 2] != 'O' && map[x][y + 2] != 'Q'&&map[x][y + 2] != '#')
				{
					map[x][y] = ' ';

					//��¼�ƶ�����ǰ��ɫ������
					last_x = x;
					last_y = y;

					y++;

					//��¼�ƶ�����ǰ���ӵ�����
					box_nx = x;
					box_ny = y;

					map[x][y] = '@';
					map[x][y + 1] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
					isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

					//��¼���һ�α��ƶ����ӵ�����
					box_x = x;
					box_y = y + 1;

					lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
					step_num++;
				}
			}
			else if (option == 'u')
			{
				//����һ��
				if (isUndo && restep_num > 0) 
				{

					map[x][y] = ' ';//����ɫ��ǰλ�ø���Ϊ�յأ������λ��Ӧ��ΪĿ�ĵ����ǽ��ں���������д���
					//����ɫλ�ø���Ϊ֮ǰ�洢��λ��
					x = last_x;
					y = last_y;
					map[x][y] = '@';//����ɫ��ԭ����λ�ø���Ϊ@

					//ͬ��������ӵ�λ��
					map[box_x][box_y] = ' ';
					map[box_nx][box_ny] = 'O';

					step_num = lastStep_num;//��ԭ֮ǰ���ߵĲ���

					isUndo = 0;//�������жϱ�������Ϊ0��false����ʾ��ǰ����λ��Ϊ�������λ�ã���ֹ�ٴγ���
					restep_num--;//ʣ��ɳ���������1
				}
			}
			else if (option == 'q') 
			{//���ñ�����Ϸ
				reValue = 4;
				isEnd = 1;
			}
			else if (option == 27)
			{//����ͣ�˵�
				scenes = 1;
			}
			break;
		case 1:
			if (option == 'r' || option == 27) 
			{//������Ϸ
				scenes = 0;
			}
			else if (option == 'x') 
			{//���뵽�ؿ�ѡ����棬����;�Ƴ��ؿ�ѡ��Ļ����������ǰ��Ϸ����ص����˵�
				reValue = 2;
				isEnd = 1;
			}
			else if (option == 'q') {
				reValue = 4;
				isEnd = 1;
			}
			else if (option == 'n' && level != maps_num - 1) {//�����ǰ�������һ�أ��������һ��
				reValue = 5;
				isEnd = 1;
			}
			else if (option == 'm') {//�������˵�
				reValue = 1;
				isEnd = 1;
			}
			break;
		case 2:
			if (option == 'x')
			{
				reValue = 2;
				isEnd = 1;
			}
			else if (option == 'q') 
			{
				reValue = 4;
				isEnd = 1;
			}
			else if (option == 'n'&&level != maps_num - 1)
			{
				reValue = 5;
				isEnd = 1;
			}
			else if (option == 'm')
			{
				reValue = 1;
				isEnd = 1;
			}
			break;
		default:
			break;
		}

		//�߼�����

		//��ԭ�յ���,����֮ǰû�д��������,�û���һ��Ҫ��ͨ�������ж�֮ǰ���в�����ȷ�ж��Ƿ����
		for (int i = 0; aim_x[i] != 0; i++) {//���μ���յ�����
			if (map[aim_x[i]][aim_y[i]] == ' ')//���Ϊ' '�����Ϊ'X'
				map[aim_x[i]][aim_y[i]] = 'X';
			if (map[aim_x[i]][aim_y[i]] == 'O')//���Ϊ'O'�����Ϊ'Q'
				map[aim_x[i]][aim_y[i]] = 'Q';
		}

		//ͨ�������ж�
		int count = 0;//��¼��ǰ�ж��ٸ����ӵ����յ�����
		for (int i = 0; aim_x[i] != 0; i++) 
		{//���μ���յ�����
			if (map[aim_x[i]][aim_y[i]] == 'Q')//�����λ��Ϊ����
				count++;//��������1
		}
		if (count == xnum) 
		{//���count�����յ�������Ŀ�����ʾͨ��
			scenes = 2;
		}

		if (isEnd)
			break;
	}

	return reValue;//����reValue
}

void LoadMap(int level, char(*map)[50])
{
	char buffer[256];//�ַ��������������ڴ�Źؿ��ļ�·��
	FILE *fp;//���ڴ򿪹ؿ��ļ����ļ�ָ��
	sprintf(buffer, "Debug\\Map\\%d.txt", level + 1);//ͨ��sprintf������ʽ���ļ�·��Ϊ����Ҫ��ȡ���ļ�
	fp = fopen(buffer, "r");//��ֻ������ʽ���ļ�
	for (int i = 0;; i++) 
	{//ѭ����ȡ�ļ����ݣ�ֱ���ﵽ�˳�����
		fgets(map[i], 256, fp);//��ȡһ���ַ���
		map[i][strlen(map[i]) - 1] = '\0';//���ַ���ĩβ�ֶ����Ͻ�����'\0'
		if (map[i][1] == '|')
		{//���ַ����ڶ�λ����'|'ʱ��ʾ����Ϊ���һ�У��ļ���ȡ����
			map[i][1] = '=';//����λ�ַ�����Ϊ'='
			break;//����ѭ��
		}
	}
	fclose(fp);//�ر��ļ�ָ��
}
