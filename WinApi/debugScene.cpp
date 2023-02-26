#include "Stdafx.h"
#include "debugScene.h"



HRESULT debugScene::init(void)
{
    ww = 7992;
    wh = 2048;

   TEMPSOUNDMANAGER->addMp3FileWithKey("GHZBGM", "Resources/Sound/GHZbgm.mp3");

    

    IMAGEMANAGER->addImage("debugMap", "Resources/Images/BackGround/GHZc1.bmp", ww, wh);
    IMAGEMANAGER->addImage("sky1", "Resources/Images/BackGround/sky1.bmp", ww, 32, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("sky2", "Resources/Images/BackGround/sky2.bmp", ww, 32, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("bg1", "Resources/Images/BackGround/bg3.bmp", ww, 48, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("bg2", "Resources/Images/BackGround/bg4.bmp", ww, 900, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("GHZup", "Resources/Images/BackGround/GHZup.bmp", ww, wh, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("GHZunder", "Resources/Images/BackGround/GHZunder.bmp", ww, wh, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("Coin", "Resources/Images/Object/coin.bmp", 256, 16, 16, 1, true, RGB(255, 0, 255));



    _sonic = new Sonic;
    
    _sonic->init();

    _world = IMAGEMANAGER->findImage("debugMap");
    _worldDown = IMAGEMANAGER->findImage("GHZunder");
    _coin = IMAGEMANAGER->findImage("Coin");

    eatRing = 0;


    createCoin();
    return S_OK;
}

void debugScene::release(void)
{
    SAFE_DELETE(_sonic)
}

void debugScene::update(void)
{

    //TEMPSOUNDMANAGER->playSoundWithKey("GHZBGM");
    _count++;
    if (_count % 12300 == 0)
    {
        TEMPSOUNDMANAGER->stopMp3WithKey("GHZBGM");
        TEMPSOUNDMANAGER->playSoundWithKey("GHZBGM");
    }

    _sonic->update();

    cx = _sonic->getCameraX();
    cy = _sonic->getCameraY();

    loopSpeed1 += 1.8f;
    loopSpeed2 += .6f;

    _coin->setFrameY(0);
    _coin->setFrameX((_count % 32) / 2);
    
    vector<Coin>::iterator iter(coins.begin());

    for (; iter != coins.end();) {
        iter->update();
        RECT tempRect;
        RECT rect;
        rect.left = iter->getX();
        rect.right = rect.left + 16;
        rect.top = iter->getY();
        rect.bottom = rect.top + 16;

        if(!_sonic->getIsHit() && IntersectRect(&tempRect, &rect, &_sonic->getHitbox()))
        {
            iter = coins.erase(iter);
            eatRing++;
            _sonic->setEatCoin(eatRing);
            TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/LoseRings");
        }
        else if (iter->isRemove())
        {
            iter = coins.erase(iter);
        }  
        else
            iter++;
    }


    if (_sonic->getIsHit() && _sonic->getEatCoin() > 0)
    {
        eatRing = 0;
        coinSpread();
        _sonic->setEatCoin(0);
        TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/LoseRings");
    }




  

};


void debugScene::render(void)
{


    IMAGEMANAGER->loopRender("sky1", getMemDC(), &RectMake(0, 0, WINSIZE_X,32), loopSpeed1, 0);
    IMAGEMANAGER->loopRender("sky2", getMemDC(), &RectMake(0, 32, WINSIZE_X, 32), loopSpeed2, 0);
    IMAGEMANAGER->findImage("bg1")->scaleRender(getMemDC(), 0, 64, WINSIZE_X, WINSIZE_Y / 4, cx * .08, 0, WINSIZE_X / 3.75, 48);
    IMAGEMANAGER->findImage("bg2")->scaleRender(getMemDC(), 0, 244,WINSIZE_X, 476, cx * .23, 0, WINSIZE_X / 2, 238);
    IMAGEMANAGER->findImage("GHZunder")->render(getMemDC(), _world->getX() - cx, _world->getY() - cy);
    IMAGEMANAGER->findImage("GHZup")->render(getMemDC(), _world->getX() - cx, _world->getY() - cy);
    if (KEYMANAGER->isToggleKey(VK_F3))
    {
        IMAGEMANAGER->findImage("debugMap")->render(getMemDC(), _world->getX() - cx, _world->getY() - cy);
    }
    _sonic->render();

    

    for (Coin& c : coins)
    {
        _coin->frameRender(getMemDC(), c.getX() - cx, c.getY() - cy);
    }
}

void debugScene::coinSpread(void)
{
    float unit = 180.0f / _sonic->getEatCoin();


    for (int i = 0; i < _sonic->getEatCoin(); i++)
    {
        Coin coin(_sonic->getSonicX(), _sonic->getSonicY());

        coin.setV(8 * cos(i * unit * M_PI / 180.0f), 16 * sin(i * unit * M_PI / 180.0f));
        coin.setLost();
        coins.push_back(coin);
       
    }

}

void debugScene::createCoin(void)
{
    coins.push_back(Coin(325, 850));
    coins.push_back(Coin(350, 850));
    coins.push_back(Coin(375, 850));
    coins.push_back(Coin(1130, 825));
    coins.push_back(Coin(1155, 825));
    coins.push_back(Coin(1180, 825));
    coins.push_back(Coin(1205, 825));
    coins.push_back(Coin(1230 ,825));
    coins.push_back(Coin(1650, 896));
    coins.push_back(Coin(1730, 940));
    coins.push_back(Coin(1805, 950));
    coins.push_back(Coin(1848, 942));
    coins.push_back(Coin(1880, 915));
    coins.push_back(Coin(2504, 705));
    coins.push_back(Coin(2530, 705));
    coins.push_back(Coin(2940, 715));
    coins.push_back(Coin(2965, 715));
    coins.push_back(Coin(3400, 696));
    coins.push_back(Coin(3471, 658));
    coins.push_back(Coin(3540, 631));
    coins.push_back(Coin(3852, 504));
    coins.push_back(Coin(3896, 516));
    coins.push_back(Coin(4445, 833));
    coins.push_back(Coin(4470, 833));
    coins.push_back(Coin(4660, 833));
    coins.push_back(Coin(4685, 833));
    coins.push_back(Coin(4690, 573));
    coins.push_back(Coin(4782, 611));
    coins.push_back(Coin(4839, 629));
    coins.push_back(Coin(5567, 607));
    coins.push_back(Coin(5505, 546));
    coins.push_back(Coin(5440, 608));
    coins.push_back(Coin(5405, 855));
    coins.push_back(Coin(5407, 906));
}