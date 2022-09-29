#include <iostream>
#include <fstream>
using namespace std;
#define buffersize 2000                                     //버퍼 사이즈를 상수로 선언

int main()
{
    char buffer[buffersize];
    ifstream file;
    file.open("test.flac", ios::binary);                    //원본파일
    ofstream afterfile;
    afterfile.open("aftertest.flac", ios::binary);          //변조파일
    if (file.fail()) 
    {
        cout << "파일을 여는 데 실패했습니다." << endl;
        return 1;
    }                                                       //파일 열기에 실패하면 프로그램을 종료

    file.seekg(0, ios::end);                                //파일 크기 확인을 위해 트리거를 파일 끝으로 이동
    float filesize = file.tellg();                          //파일 크기 확인
    int originalfilesize = filesize;                        //파일을 끝까지 복제했는지 확인하기 위해 파일 사이즈를 저장
    file.seekg(0, ios::beg);                                //파일 크기 확인을 위해 끝으로 옮겼던 트리거를 다시 앞으로 이동

    int count = 0;                                          //반복문이 잘 작동했는지 확인하기 위해 카운터를 선언

    while (filesize > 0)
    {
        file.read(buffer, buffersize);                      //파일을 버퍼 사이즈만큼 읽어옴
        for (int i = 0; i < buffersize; i++)
        {
            buffer[i] = buffer[i] ^ buffer[i];              //xor연산을 통해 버퍼의 데이터를 변조
        }
        afterfile.write(buffer, buffersize);                //변조된 버퍼를 파일에 입력
        filesize = filesize - buffersize;                   //파일 크기만큼 무한반복 file.tellg()사용시 오류가 발생해 이렇게 해결
        buffer[0] = '\n';                                   //버퍼 비워주기
        count++;                                            //반복 횟수 카운트
    }
    file.close();                                           //원본파일닫기
    afterfile.close();                                      //변조파일닫기

    cout << "원본 파일 사이즈는 " << originalfilesize << "비트이며 버퍼사이즈는 " << buffersize << "입니다." << endl;
    cout << "반복 횟수는 " << count << "번입니다." << endl;
    if (count * buffersize >= originalfilesize)
    {
        cout << "버퍼사이즈 * 반복횟수 : " << count * buffersize << endl;
        cout << "작업이 성공적으로 완료되었습니다." << endl;
    }
    else
    {
        cout << "버퍼사이즈 * 반복횟수 : " << count * buffersize << endl;
        cout << "문제가 발생했습니다 다시 시도해주세요." << endl;
    }                                                       //작업 완료 내역 검증 및 출력
    return 0;
}