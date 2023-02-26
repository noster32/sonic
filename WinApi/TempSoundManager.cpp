#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
    return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();
    //mciSendString(): 장치에 특정 명령어를 전송하여 구동시킨다.
    //ㄴ 인자: 문자열 명령어, 반환값을 알려줄 문자열, 반환될 길이, 콜백(핸들)
    //mp3 타입의 파일을 연다 
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveaudio alias ";
    string finalQuery = first + fileName + end + key;
    
    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
    //PlaySound : 사운드재생함수. 빨라서 test에 많이 쓰인다.
    // 인자 (파일이름(파일경로), vs리소스를 사용하면 해당 인스턴스 핸들, fdwSound(옵션 | 옵션 | 옵션)
    /**옵션중요**
    *
    * SND_ASYNK : 비동기플래그. 재생하면서 다음코드 실행
    * SND_LOOP
    * SND_NODEFAULT : 지정경로에 파일 없을경우 나오는 경고음 재생X
    */

    //cout << "작동 : playEffectSoundWave" << endl;

    PlaySound(fileName, NULL, SND_ASYNC);
}

void TempSoundManager::playSoundWithKey(string key)
{
    string first = "play ";
    string finalQuery = first + key;

    const char* str = finalQuery.c_str();

    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
    string first = "play ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();

    mciSendString(str, NULL, 0, NULL);
}
