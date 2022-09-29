#include <iostream>
#include <fstream>
using namespace std;
#define buffersize 2000                                     //���� ����� ����� ����

int main()
{
    char buffer[buffersize];
    ifstream file;
    file.open("test.flac", ios::binary);                    //��������
    ofstream afterfile;
    afterfile.open("aftertest.flac", ios::binary);          //��������
    if (file.fail()) 
    {
        cout << "������ ���� �� �����߽��ϴ�." << endl;
        return 1;
    }                                                       //���� ���⿡ �����ϸ� ���α׷��� ����

    file.seekg(0, ios::end);                                //���� ũ�� Ȯ���� ���� Ʈ���Ÿ� ���� ������ �̵�
    float filesize = file.tellg();                          //���� ũ�� Ȯ��
    int originalfilesize = filesize;                        //������ ������ �����ߴ��� Ȯ���ϱ� ���� ���� ����� ����
    file.seekg(0, ios::beg);                                //���� ũ�� Ȯ���� ���� ������ �Ű�� Ʈ���Ÿ� �ٽ� ������ �̵�

    int count = 0;                                          //�ݺ����� �� �۵��ߴ��� Ȯ���ϱ� ���� ī���͸� ����

    while (filesize > 0)
    {
        file.read(buffer, buffersize);                      //������ ���� �����ŭ �о��
        for (int i = 0; i < buffersize; i++)
        {
            buffer[i] = buffer[i] ^ buffer[i];              //xor������ ���� ������ �����͸� ����
        }
        afterfile.write(buffer, buffersize);                //������ ���۸� ���Ͽ� �Է�
        filesize = filesize - buffersize;                   //���� ũ�⸸ŭ ���ѹݺ� file.tellg()���� ������ �߻��� �̷��� �ذ�
        buffer[0] = '\n';                                   //���� ����ֱ�
        count++;                                            //�ݺ� Ƚ�� ī��Ʈ
    }
    file.close();                                           //�������ϴݱ�
    afterfile.close();                                      //�������ϴݱ�

    cout << "���� ���� ������� " << originalfilesize << "��Ʈ�̸� ���ۻ������ " << buffersize << "�Դϴ�." << endl;
    cout << "�ݺ� Ƚ���� " << count << "���Դϴ�." << endl;
    if (count * buffersize >= originalfilesize)
    {
        cout << "���ۻ����� * �ݺ�Ƚ�� : " << count * buffersize << endl;
        cout << "�۾��� ���������� �Ϸ�Ǿ����ϴ�." << endl;
    }
    else
    {
        cout << "���ۻ����� * �ݺ�Ƚ�� : " << count * buffersize << endl;
        cout << "������ �߻��߽��ϴ� �ٽ� �õ����ּ���." << endl;
    }                                                       //�۾� �Ϸ� ���� ���� �� ���
    return 0;
}