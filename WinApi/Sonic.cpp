#include "Stdafx.h"
#include "Sonic.h"

HRESULT Sonic::init(void)
{
    IMAGEMANAGER->addImage("Score", "Resources/Images/UI/score.bmp", 41, 14, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("Time", "Resources/Images/UI/time.bmp", 33, 14, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("Ring", "Resources/Images/UI/RING.bmp", 33, 14, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("tuiNumber", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("tuiNumber2", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("tuiNumber3", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("tuiNumber4", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("tuiNumber5", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("tuiNumber6", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("suiNumber", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("suiNumber2", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("suiNumber3", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("suiNumber4", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("suiNumber5", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("suiNumber6", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("cuiNumber", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("cuiNumber2", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("cuiNumber3", "Resources/Images/UI/uiNumber.bmp", 90, 14, 10, 1, true, RGB(255, 0, 255));



    _sonicImg = IMAGEMANAGER->addRotateFrameImage("Sonic", "Resources/Images/Motion/sonic.bmp", 0, 0, 1152, 1296, 24, 27, .5f, .5f, true, RGB(255, 0, 255));


    position.x = 140;
    position.y = 940;
    velocity = Vector2D();

    //4초 간격마다 idle
    _count = 0;
   
    _idleFrame = _moveFrame = _jumpFrame = _skidFrame = _lookUpFrame = 0;
    _repeatIdle1 = _repeatIdle2 = _repeatIdle3 = _delayIdle = _delayLookUp = 0;

    _fallSpeed = 1;

    _sSonic.isNotControl = false;
    _sSonic.isMove = false;
    _sSonic.isMoveF = false;
    _sSonic.isMoveVF = false;
    _sSonic.isLeft = false;
    _sSonic.isJump = false;
    _sSonic.isSkid = false;
    _sSonic.isAir = true;
    _sSonic.isLookUp = false;
    _sSonic.isLookUpAnimLeft = false;
    _sSonic.isMoveAnimLeft = false;
    _sSonic.isCrouchAnimLeft = false;
    _sSonic.isCrouch = false;
    _sSonic.isBallMode = false;
    _sSonic.isSpinDash = false;
    _sSonic.isSpinDashRemain = false;
    _sSonic.isDropDash = false;
    _sSonic.accel = 0;
    _sSonic.hSpeed = 0;

    c1 = 0;
    c2 = 0;
    c3 = 0;

    hitboxX = 20;
    hitboxY = 33;
    
    ww = 16384;
    wh = 2048;


    return S_OK;
}

void Sonic::release(void)
{
    SAFE_DELETE(_sonicImg)
}

void Sonic::update(void)
{


    //100fps
    _count++;             
    _sSonic.isMove = false;
    _sSonic.isMoveF = false;
    _sSonic.isMoveVF = false;
    
    if (onPixelLeft || onPixelRight)
    {
        onPixel = true;
    }
    else
    {
        onPixel = false;
    }

    if (is360) {
        force360rolling();
        UpdateCamera();
        sonicAnim();
        IMAGEMANAGER->findImage("Sonic")->rotateFrameUpdate(-_sonicRotate, position.x - cameraX, position.y - cameraY);
        _sSonic.HitBox = RectMakeCenter(position.x, position.y + 4, hitboxX, hitboxY);
        return;
    }

    UpdateCamera();


    if (_sonicDraw.left < 0)
    {
        position.x = 24;
    }
    //LeftMove & RightMove
    sonicKeybind();

    

    if (_sSonic.isSpinDashRemain)
        _sSonic.isBallMode = true;
    if (_sSonic.speed == 0)
    {
        _sSonic.isBallMode = false;
        _sSonic.isSpinDashRemain = false;
    }

    //Sonic Move Anim Change
    if ((_sSonic.speed >= 8 || _sSonic.speed <= -8))
    {
        _sSonic.isMoveVF = true;
    }
    else if (((_sSonic.speed < 8 && _sSonic.speed > 4) || (_sSonic.speed > -8 && _sSonic.speed < -4)))
    {
        _sSonic.isMoveF = true;
    }

    //Gravity
    gravity();
    

    //pixel Collision
    _underLeftX = position.x - 9;
    _underRightX = position.x + 9;
    _reverseUpY = position.y - 9;
    _reverseDownY = position.y + 9;
    //sonicImg.bottom
    _probeY = position.y + 24;
    _probeX = position.x + 24;
    _probeXL = position.x - 24;
    
        
    sonicCollision();
    if (is360) return;
    sonicRotateCal();

    

    //afk or Not
    if (!_sSonic.isNotControl && !_sSonic.isMove && !_sSonic.isJump && !_sSonic.isLookUp && !_sSonic.isBallMode && !_sSonic.isCrouch && !_sSonic.isLookUpAnimLeft && !_sSonic.isMoveAnimLeft)
    {
        _afkCount++;
        if (_afkCount > 400)
        {
            _sSonic.isNotControl = true;
            _afkCount = 0;
        }
    }
    else _afkCount = 0;

    //Anim
    sonicAnim();
    
    //Sonic Move
    if (_sSonic.isSpinDash) {}
    else
        position.x += _sSonic.speed;
       
    position.y -= _sSonic.hSpeed;

    

    if (_count % 1 == 0)
    {
        milliSec2++;
        if (milliSec2 > 9) milliSec2 = 0;
    }
    if (_count % 10 == 0)
    {
        milliSec1++;
        if (milliSec1 > 9) milliSec1 = 0;
    }
    if (_count % 100 == 0)
    {
        sec2++;
        if (sec2 > 9) sec2 = 0;
    }
    if (_count % 1000 == 0)
    {
        sec1++;
        if (sec1 > 9) sec1 = 0;
    }
    if (_count % 10000 == 0)
    {
        min2++;
        if (min2 > 9) min2 = 0;
    }
    if (_count % 10000 == 0)
    {
        min1++;
        if (min1 > 9) min1 = 0;
    }


     c1 = _eatRing % 10;

     c2 = (_eatRing %  100) / 10;

     c3 = (_eatRing % 1000) / 100;


    IMAGEMANAGER->findImage("tuiNumber")->setFrameX(min1);
    IMAGEMANAGER->findImage("tuiNumber2")->setFrameX(min2);
    IMAGEMANAGER->findImage("tuiNumber3")->setFrameX(sec1);
    IMAGEMANAGER->findImage("tuiNumber4")->setFrameX(sec2);
    IMAGEMANAGER->findImage("tuiNumber5")->setFrameX(milliSec1);
    IMAGEMANAGER->findImage("tuiNumber6")->setFrameX(milliSec2);

    IMAGEMANAGER->findImage("cuiNumber")->setFrameX(c3);
    IMAGEMANAGER->findImage("cuiNumber2")->setFrameX(c2);
    IMAGEMANAGER->findImage("cuiNumber3")->setFrameX(c1);
    

    _sSonic.HitBox = RectMakeCenter(position.x, position.y + 4, hitboxX, hitboxY);
    IMAGEMANAGER->findImage("Sonic")->rotateFrameUpdate(_sonicRotate, position.x - cameraX, position.y - cameraY);


}

void Sonic::render(void)
{
    IMAGEMANAGER->render("Score", getMemDC(), 50, 80);
    IMAGEMANAGER->render("Time", getMemDC(), 50, 100);
    IMAGEMANAGER->render("Ring", getMemDC(), 50, 120);

    IMAGEMANAGER->frameRender("tuiNumber", getMemDC(), 90, 100);
    IMAGEMANAGER->frameRender("tuiNumber2", getMemDC(), 99, 100);
    IMAGEMANAGER->frameRender("tuiNumber3", getMemDC(), 110, 100);
    IMAGEMANAGER->frameRender("tuiNumber4", getMemDC(), 119, 100);
    IMAGEMANAGER->frameRender("tuiNumber5", getMemDC(), 130, 100);
    IMAGEMANAGER->frameRender("tuiNumber6", getMemDC(), 139, 100);

    IMAGEMANAGER->frameRender("cuiNumber", getMemDC(), 90, 120);
    IMAGEMANAGER->frameRender("cuiNumber2", getMemDC(), 99, 120);
    IMAGEMANAGER->frameRender("cuiNumber3", getMemDC(), 110, 120);

    IMAGEMANAGER->rotateFrameRender("Sonic", getMemDC());

    if (KEYMANAGER->isToggleKey(VK_F1))
    { 
        RectMake(_sSonic.HitBox.left - cameraX, _sSonic.HitBox.top - cameraY, hitboxX, hitboxY);
        LineMake(getMemDC(), position.x - cameraX, position.y - cameraY, (position.x + _sSonic.speed) - cameraX, position.y - cameraY);
        LineMake(getMemDC(), _underLeftX - cameraX, position.y - cameraY, _underLeftX - cameraX, _probeY - cameraY);
        LineMake(getMemDC(), _underRightX - cameraX, position.y - cameraY, _underRightX - cameraX, _probeY - cameraY);
    }
    Rectangle(getMemDC(), 600, 1400, 700, 1500);
    if (KEYMANAGER->isToggleKey(VK_F2))
    {
        debugLog();
    }
    
}

void Sonic::sonicKeybind(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_sSonic.isCrouch && !_sSonic.isLookUp && !_sSonic.isBallMode)
    {
        if (_sSonic.speed < 0)
        {
            if (!_sSonic.isSkid) TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/Skidding.wav");
            _sSonic.isSkid = true;
            _sSonic.accel = .9f;
            _sSonic.speed *= _sSonic.accel;
            if (_sSonic.speed > -.5f)
                _sSonic.speed = 0; 
        }
        else
        {
            _sSonic.isSkid = false;
            _sSonic.isMove = true;

            _sSonic.accel = 1.06f;
            if (_sSonic.speed == 0) _sSonic.speed = 0.1f;
            else if (_sSonic.isDropDash) _sSonic.speed *= 1.0f;
            else _sSonic.speed *= _sSonic.accel;
            if (_sSonic.speed >= 8 && !_sSonic.isDropDash)
                _sSonic.speed = 8;
            _sSonic.isLeft = false;
        }

        _sSonic.isNotControl = false;

    }
    else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_sSonic.isCrouch && !_sSonic.isLookUp && !_sSonic.isBallMode)
    {
        
        if (_sSonic.speed > 0)
        {
            if (!_sSonic.isSkid) TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/Skidding.wav");
            _sSonic.isSkid = true;
            _sSonic.accel = .9f;
            _sSonic.speed *= _sSonic.accel;
            if (_sSonic.speed < .5f)
                _sSonic.speed = 0;
            
        }
        else
        {
            _sSonic.isSkid = false;
            _sSonic.isMove = true;

            _sSonic.accel = 1.06f;
            if (_sSonic.speed == 0) _sSonic.speed = -0.1f;
            else if (_sSonic.isDropDash) _sSonic.speed *= 1.0f;
            else _sSonic.speed *= _sSonic.accel;
            if (_sSonic.speed <= -8 && !_sSonic.isDropDash)
                _sSonic.speed = -8;
            _sSonic.isLeft = true;
        }

        _sSonic.isNotControl = false;
    }
    else
    {
        _sSonic.isSkid = false;
        if (_sSonic.isBallMode)
        {
            _sSonic.speed *= 0.98f;
        }
        else if (_sSonic.isSpinDash)
        {
            _sSonic.speed *= 1.0f;
        }
        else
        {
            _sSonic.speed *= 0.93f;
        }
            

        if ((_sSonic.speed > 0 && _sSonic.speed < 1) || (_sSonic.speed > -1 && _sSonic.speed < 0))
            _sSonic.speed = 0;
    }

    if (KEYMANAGER->isStayKeyDown('S') && !_sSonic.isJump && !_sSonic.isCrouch && !_sSonic.isSpinDash && !_sSonic.isSpinDashRemain)
    {
        _sSonic.isNotControl = false;
        jump();
        TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/Jump.wav");
    }

    if (KEYMANAGER->isOnceKeyDown('A') && _sSonic.isJump)
    {
        _sSonic.isDropDash = true;
        
        if (!_sSonic.isLeft) _sSonic.speed = 15;
        else if (_sSonic.isLeft) _sSonic.speed = -15;
    }

    if (KEYMANAGER->isStayKeyDown(VK_UP) && !_sSonic.isNotControl && !_sSonic.isMove && !_sSonic.isJump)
    {
        _sSonic.isLookUp = true;
    }
    if (KEYMANAGER->isOnceKeyUp(VK_UP))
    {
        _sSonic.isLookUp = false;
    }

    if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_sSonic.isJump)
    {
        _sSonic.isCrouch = true;

        if ((_sSonic.speed > 0 || _sSonic.speed < 0) && !_sSonic.isSpinDash) _sSonic.isBallMode = true;
    }


    if (KEYMANAGER->isStayKeyDown('S') && _sSonic.speed == 0 && _sSonic.isCrouch)
    {
        _sSonic.isSpinDash = true;
        
        if (!_sSonic.isLeft) _sSonic.speed = 15;
        else if (_sSonic.isLeft) _sSonic.speed = -15;
    }


    if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
    {
        _sSonic.isCrouch = false;
        _sSonic.isSpinDash = false;
        _sSonic.isSpinDashRemain = true;
    }

}

void Sonic::sonicAnim(void)
{
    //AFK
    if (_sSonic.isNotControl)
    {
        if (_repeatIdle1 < 11 && !_sSonic.isLeft)
        {
            IMAGEMANAGER->findImage("Sonic")->setFrameY(0);
        }
        else if (_repeatIdle1 < 11 && _sSonic.isLeft)
        {
            IMAGEMANAGER->findImage("Sonic")->setFrameY(1);
        }
        else if (_repeatIdle1 > 10 && !_sSonic.isLeft)
        {
            IMAGEMANAGER->findImage("Sonic")->setFrameY(2);
        }
        else
        {
            IMAGEMANAGER->findImage("Sonic")->setFrameY(3);
        }

        if (_count % 8 == 0)
        {
            _idleFrame++;
            //8~14
            if (_idleFrame > 5 && _repeatIdle1 < 11)
            {
                if (_idleFrame > 10)
                {
                    _idleFrame = 6;
                    _repeatIdle1++;
                    if (_repeatIdle1 > 10) _idleFrame = 0;
                }
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_idleFrame);
            }
            else if (_idleFrame > 7 && _repeatIdle1 > 10)
            {
                if (_idleFrame > 13 && _repeatIdle2 < 4)
                {
                    _idleFrame = 8;
                    _repeatIdle2++;
                }
                else if (_repeatIdle2 > 3 && _repeatIdle3 == 0)
                {
                    if (_delayIdle > 3)
                    {
                        if (_delayIdle == 4)
                        {
                            _delayIdle++;
                            _idleFrame = 8;
                        }
                        _repeatIdle3 = 1;
                        _repeatIdle2 = 1;
                    }
                    else
                    {
                        _delayIdle++;
                    }

                }
                else
                {
                    if (_idleFrame > 17)
                    {
                        _repeatIdle1 = _repeatIdle2 = _repeatIdle3 = _delayIdle = 0;
                        _sSonic.isNotControl = false;
                    }
                }

                if (_repeatIdle2 > 3 && _repeatIdle3 == 0)
                {
                    if (_delayIdle > 3)
                    {
                        if (_delayIdle == 4)
                        {
                            IMAGEMANAGER->findImage("Sonic")->setFrameX(7);
                        }
                        else
                            IMAGEMANAGER->findImage("Sonic")->setFrameX(_idleFrame);
                    }
                    else
                    {
                        if (_delayIdle == 0)
                            IMAGEMANAGER->findImage("Sonic")->setFrameX(15);
                        else
                            IMAGEMANAGER->findImage("Sonic")->setFrameX(6);
                    }
                }
                else
                    IMAGEMANAGER->findImage("Sonic")->setFrameX(_idleFrame);
            }
            else if (_idleFrame < 8 && _repeatIdle1 > 10)
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_idleFrame);
            }
            else
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_idleFrame);
            }
        }
    }
    else if (!_sSonic.isNotControl)
    {
        _idleFrame = 0;
    }

    //IDLE
    if (!_sSonic.isNotControl && !_sSonic.isMove && !_sSonic.isJump && !_sSonic.isSkid && !_sSonic.isLookUp && !_sSonic.isLookUpAnimLeft && !_sSonic.isMoveAnimLeft && !_sSonic.isCrouch && !_sSonic.isBallMode && !_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
        {
            IMAGEMANAGER->findImage("Sonic")->setFrameY(0);
        }
        else
            IMAGEMANAGER->findImage("Sonic")->setFrameY(1);

        IMAGEMANAGER->findImage("Sonic")->setFrameX(0);
    }

    //MOVE
    if (_sSonic.isMove && !_sSonic.isJump && !_sSonic.isSkid && !_sSonic.isBallMode && !_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
        {
            if (_sSonic.isMoveVF)
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameY(8);
            }
            else if (_sSonic.isMoveF)
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameY(6);
            }
            else if (_sSonic.isMove && !_sSonic.isMoveF && !_sSonic.isMoveVF)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(4);
        }
        else if (_sSonic.isLeft)
        {
            if (_sSonic.isMoveVF)
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameY(9);
            }
            else if (_sSonic.isMoveF)
            {
                IMAGEMANAGER->findImage("Sonic")->setFrameY(7);
            }
            else if (_sSonic.isMove && !_sSonic.isMoveF && !_sSonic.isMoveVF)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(5);
        }

        if (_sSonic.isMoveVF)
        {
            if (_count % 2 == 0)
            {
                _moveFrame++;
                if (_moveFrame > 6)
                {
                    _moveFrame = 0;
                }
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
            }
        }
        else if (_sSonic.isMoveF)
        {
            if (_count % 4 == 0)
            {
                _moveFrame++;
                if (_moveFrame > 9)
                {
                    _moveFrame = 0;
                }
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
            }
        }
        else if (_sSonic.isMove && !_sSonic.isMoveF && !_sSonic.isMoveVF)
        {
            if (_count % 5 == 0)
            {
                _moveFrame++;
                if (_moveFrame > 11)
                {
                    _moveFrame = 0;
                }
                IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
            }
        }

    }
    if (!_sSonic.isMove)
    {
        if ((_sSonic.speed > 0 || _sSonic.speed < 0) && !_sSonic.isJump && !_sSonic.isSkid && !_sSonic.isBallMode && !_sSonic.isDamaged)
        {
            _sSonic.isMoveAnimLeft = true;

            if (!_sSonic.isLeft)
            {
                if (_sSonic.isMoveVF)
                {
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(8);
                }
                else if (_sSonic.isMoveF)
                {
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(6);
                }
                else if (_sSonic.isMoveAnimLeft && !_sSonic.isMoveF && !_sSonic.isMoveVF)
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(4);
            }
            else if (_sSonic.isLeft)
            {
                if (_sSonic.isMoveVF)
                {
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(9);
                }
                else if (_sSonic.isMoveF)
                {
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(7);
                }
                else if (_sSonic.isMoveAnimLeft && !_sSonic.isMoveF && !_sSonic.isMoveVF)
                {
                    IMAGEMANAGER->findImage("Sonic")->setFrameY(5);
                }
                    
            }

            if (_sSonic.isMoveVF)
            {
                if (_count % 2 == 0)
                {
                    _moveFrame++;
                    if (_moveFrame > 6)
                    {
                        _moveFrame = 0;
                    }
                    IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
                }
            }
            else if (_sSonic.isMoveF)
            {
                if (_count % 4 == 0)
                {
                    _moveFrame++;
                    if (_moveFrame > 9)
                    {
                        _moveFrame = 0;
                    }
                    IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
                }
            }
            else if (_sSonic.isMoveAnimLeft && !_sSonic.isMoveF && !_sSonic.isMoveVF)
            {
                if (_count % 5 == 0)
                {
                    _moveFrame++;
                    if (_moveFrame > 11)
                    {
                        _moveFrame = 0;
                    }
                    IMAGEMANAGER->findImage("Sonic")->setFrameX(_moveFrame);
                }
            }

        }
        else
        {
            _sSonic.isMoveAnimLeft = false;
            _moveFrame = 0;
        }
            
    }

    //JUMP
    if (_sSonic.isJump && !_sSonic.isDropDash && !_sSonic.isDamaged)
    {
        hitboxY = 25;
        if (_count % 3 == 0)
        {
            if (!_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(10);
            else if (_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(11);

            _jumpFrame++;
            if (_jumpFrame > 15)
            {
                _jumpFrame = 0;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_jumpFrame);
        }
    }
    else if (!_sSonic.isJump)
    {
        _jumpFrame = 0;
        hitboxY = 33;
    }

    //SKID
    if (_sSonic.isSkid && !_sSonic.isJump && !_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(12);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(13);

        if (_count % 2 == 0)
        {
            _skidFrame++;
            if (_skidFrame > 11)
            {
                _skidFrame = 11;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_skidFrame);
        }
    }
    else if (!_sSonic.isSkid)
    {
        _skidFrame = 0;
    }

    //LOOKUP
    if (_sSonic.isLookUp && !_sSonic.isJump && !_sSonic.isCrouch && !_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(14);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(15);

        if (_count % 5 == 0)
        {

            if (_lookUpFrame == 2 && _delayLookUp < 20)
            {
                _delayLookUp++;
                _lookUpFrame = 2;
            }
            else
            {
                _lookUpFrame++;
                if (_delayLookUp >= 20) _delayLookUp = 0;
            }
            if (_lookUpFrame > 3)
            {
                _lookUpFrame = 2;
            }

            IMAGEMANAGER->findImage("Sonic")->setFrameX(_lookUpFrame);
        }
    }
    else if (!_sSonic.isLookUp)
    {
        if (_lookUpFrame > 0)
        {
            if (_lookUpFrame < 4 && _lookUpFrame > 0) _lookUpFrame = 5;

            if (!_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(14);
            else if (_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(15);

            _sSonic.isLookUpAnimLeft = true;
            if (_count % 5 == 0)
            {
                _lookUpFrame++;
                if (_lookUpFrame > 5)
                {
                    _lookUpFrame = 0;
                    _sSonic.isLookUpAnimLeft = false;
                }

                IMAGEMANAGER->findImage("Sonic")->setFrameX(_lookUpFrame);
                    
            }
        }
        else
            _lookUpFrame = 0;
    }

    //CROUCH
    if (_sSonic.isCrouch && !_sSonic.isBallMode && !_sSonic.isJump && !_sSonic.isLookUp && !_sSonic.isSpinDash && !_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(16);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(17);
        
        if (_count % 6 == 0)
        {
            
            if (_crouchFrame > 2)
            {
                _crouchFrame = 3;
            }
            else
                _crouchFrame++;

            IMAGEMANAGER->findImage("Sonic")->setFrameX(_crouchFrame);
        }
    }
    else if (!_sSonic.isCrouch)
    {
        if (_crouchFrame > 0)
        {
            if (_crouchFrame < 4) _crouchFrame = 4;

            if (!_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(16);
            else if (_sSonic.isLeft)
                IMAGEMANAGER->findImage("Sonic")->setFrameY(17);

            _sSonic.isCrouchAnimLeft = true;
            if (_count % 5 == 0)
            {
                _crouchFrame++;
                if (_crouchFrame > 3)
                {
                    _crouchFrame = 0;
                    _sSonic.isCrouchAnimLeft = false;
                }

                IMAGEMANAGER->findImage("Sonic")->setFrameX(_crouchFrame);

            }
        }
        else
            _crouchFrame = 0;
    }

    //ROLL
    if (_sSonic.isBallMode)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(10);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(11);

        if (_count % 2 == 0)
        {
            _ballModeFrame++;
            if (_ballModeFrame > 11)
            {
                _ballModeFrame = 0;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_ballModeFrame);
        }

    }
    else if (!_sSonic.isBallMode)
    {
        _ballModeFrame = 0;
    }

    //SPINDASH
    if (_sSonic.isSpinDash)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(18);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(19);

        if (_count % 2 == 0)
        {
            _spinDashFrame++;
            if (_spinDashFrame > 15)
            {
                _spinDashFrame = 0;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_spinDashFrame);
        }
    }
    else if (!_sSonic.isSpinDash)
    {
        _spinDashFrame = 0;
    }

    //DROPDASH
    if (_sSonic.isDropDash)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(20);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(21);

        if (_count % 2 == 0)
        {
            _dropDashFrame++;
            if (_dropDashFrame > 15)
            {
                _dropDashFrame = 0;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_dropDashFrame);
        }
    }
    else if (!_sSonic.isDropDash)
    {
        _dropDashFrame = 0;
    }
    
    //DAMGED
    if (_sSonic.isDamaged)
    {
        if (!_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(25);
        else if (_sSonic.isLeft)
            IMAGEMANAGER->findImage("Sonic")->setFrameY(26);

        if (_count % 2 == 0)
        {
            _damagedFrame++;
            if (_damagedFrame > 3)
            {
                _damagedFrame = 4;
            }
            IMAGEMANAGER->findImage("Sonic")->setFrameX(_damagedFrame);
        }
    }
}

void Sonic::sonicCollision(void)
{
    bool isAir = true;

    for (int i = _probeY - 5; i < _probeY + 5; i++)
    {
        
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _underLeftX, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (r == 0 && g == 0 && b == 255)
        {
            _sSonic.isDamaged = true;
            _sSonic.hSpeed = 5;
        }

        if (!(r == 255 && g == 0 && b == 255))
        { 
            isAir = false;
            onPixelLeft = true;
            if (r == 0 && g == 255 && b == 255)
            {
                _sSonic.onEdge = true;

            }
            else
            {
                _sSonic.onEdge = false;
            }

            if (position.y >= i - 24 && onPixel)
            {
                position.y = i - 24;
                _sSonic.isAir = false;
                
                if (_sSonic.isJump) _sSonic.isJump = false;
                if (_sSonic.onEdgeAfter) _sSonic.onEdgeAfter = false;
                if (_sSonic.isDropDash)
                {
                    _sSonic.isBallMode = true;
                    _sSonic.isDropDash = false;
                }

                if (!(r == 0 && g == 0 && b == 255))
                {
                    _sSonic.isDamaged = false;
                }
            }
            if (_sSonic.onEdge)
            {
                _sSonic.jHeight = _sSonic.speed / 1.5f;
                position.y -= _sSonic.jHeight;
            }
        }
        else
        {
            onPixelLeft = false;
        }
        
    }

    for (int j = _probeY - 5; j < _probeY + 5; j++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _underRightX, j);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (r == 0 && g == 0 && b == 255)
        {
            _sSonic.isDamaged = true;
            _sSonic.hSpeed = 5;
        }

        if (!(r == 255 && g == 0 && b == 255))
        {
            isAir = false;
            onPixelRight = true;
            if (r == 0 && g == 255 && b == 255)
            {
                _sSonic.onEdge = true;
            }
            else
            {
                _sSonic.onEdge = false;
            } 
            
            

            if (position.y >= j - 24 && onPixel)
            {
                position.y = j - 24;
                _sSonic.isAir = false;
                if (_sSonic.isJump) _sSonic.isJump = false;
                if (_sSonic.onEdgeAfter) _sSonic.onEdgeAfter = false;
                if (_sSonic.isDropDash)
                {
                    _sSonic.isBallMode = true;
                    _sSonic.isDropDash = false;
                }

                if (!(r == 0 && g == 0 && b == 255))
                {
                    _sSonic.isDamaged = false;
                }
            }
        }
        else
        {
            onPixelRight = false;
        }
        if (_sSonic.onEdge)
        {
            _sSonic.hSpeed = _sSonic.speed / 1.5f;
        }
    }

    COLORREF xLeft = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _probeXL, position.y);
    COLORREF xRight = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _probeX, position.y);

    if (xLeft == RGB(255, 0, 0) && _sSonic.speed < 0)
    {
        _sSonic.speed = 0;
    }
    else if (xRight == RGB(255, 0, 0) && _sSonic.speed > 0)
    {
        _sSonic.speed = 0;
    }

    if (xLeft == RGB(0, 0, 255))
    {
        _sSonic.isDamaged = true;
    }
    else if (xRight == RGB(0, 0, 255))
    {
        _sSonic.isDamaged = true;
    }

    if (xRight == RGB(255, 255, 0) && _sSonic.speed > 4)
    {
        is360 = true;
        _sonicRotate = 90;
        centerX = position.x - 50;
        centerY = position.y - 20;
        return;
    }

    if (_sSonic.isDamaged)
    {
        if (_sSonic.isLeft) _sSonic.speed = 5;
        else _sSonic.speed = -5;
    }

    if (isAir)
    {
        if (_sSonic.onEdge) _sSonic.onEdgeAfter = true;
        _sSonic.isAir = true;
        _sSonic.onEdge = false;
    }


}

void Sonic::sonicRotateCal(void)
{
    
    if (_sSonic.isAir)
    {
        if (_sonicRotate > 1)
            _sonicRotate -= .5f;
        else if (_sonicRotate < -1)
            _sonicRotate += .5f;
        else
            _sonicRotate = 0;
    }
    else
    {
        int left = 0;
        int right = 0;
       
        while (true)
        {
            COLORREF color = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _underLeftX, _probeY + left);

            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);


            if (!(r == 255 && g == 0 && b == 255))
            {
                break;
            }
            else
                left++;
        }
        while (true)
        {
            COLORREF color = GetPixel(IMAGEMANAGER->findImage("debugMap")->getMemDC(), _underRightX, _probeY + right);

            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);

            if (!(r == 255 && g == 0 && b == 255))
            {
                break;
            }
            else
                right++;
        }
        if (abs(right - left) > 48)
        {
            _sonicRotate = 0;
            return;
        }
        float angle = (right - left) * 1.4f;
        _sonicRotate = (atan((angle) / 48.0f) * 180.0f / M_PI);
    }
}

void Sonic::debugLog(void)
{
    char strScore2[100];
    sprintf_s(strScore2, "position: (%f, %f)", position.x, position.y);
    TextOutA(getMemDC(), 10, 10, strScore2, strlen(strScore2));
    wsprintf(strScore2, "idle: %d", _idleFrame);
    TextOut(getMemDC(), 10, 30, strScore2, strlen(strScore2));
    wsprintf(strScore2, "move: %d", _moveFrame);
    TextOut(getMemDC(), 10, 50, strScore2, strlen(strScore2));
    wsprintf(strScore2, "jump: %d", _jumpFrame);
    TextOut(getMemDC(), 10, 70, strScore2, strlen(strScore2));
    wsprintf(strScore2, "skid: %d", _skidFrame);
    TextOut(getMemDC(), 10, 90, strScore2, strlen(strScore2));
    wsprintf(strScore2, "LookUp: %d", _lookUpFrame);
    TextOut(getMemDC(), 10, 110, strScore2, strlen(strScore2));
    wsprintf(strScore2, "Crouch: %d", _crouchFrame);
    TextOut(getMemDC(), 10, 130, strScore2, strlen(strScore2));
    wsprintf(strScore2, "BallMode: %d", _ballModeFrame);
    TextOut(getMemDC(), 10, 150, strScore2, strlen(strScore2));
    wsprintf(strScore2, "afkCount: %d", _afkCount);
    TextOut(getMemDC(), 10, 170, strScore2, strlen(strScore2));
    sprintf_s(strScore2, "speed: %f", _sSonic.speed);
    TextOutA(getMemDC(), 10, 190, strScore2, strlen(strScore2));
    sprintf_s(strScore2, "jHeight: %f", _sSonic.jHeight);
    TextOutA(getMemDC(), 10, 210, strScore2, strlen(strScore2));
    sprintf_s(strScore2, "fallSpeed: %f", _fallSpeed);
    TextOutA(getMemDC(), 10, 230, strScore2, strlen(strScore2));

    wsprintf(strScore2, "isJump: %s", _sSonic.isJump ? "true" : "false");
    TextOut(getMemDC(), 150, 30, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isSkid: %s", _sSonic.isSkid ? "true" : "false");
    TextOut(getMemDC(), 150, 50, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isLookUp: %s", _sSonic.isLookUp ? "true" : "false");
    TextOut(getMemDC(), 150, 70, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isCrouch: %s", _sSonic.isCrouch ? "true" : "false");
    TextOut(getMemDC(), 150, 90, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isAnimLeft: %s", _sSonic.isLookUpAnimLeft ? "true" : "false");
    TextOut(getMemDC(), 150, 110, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isBallMode: %s", _sSonic.isBallMode ? "true" : "false");
    TextOut(getMemDC(), 150, 130, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isAir: %s", _sSonic.isAir ? "true" : "false");
    TextOut(getMemDC(), 150, 150, strScore2, strlen(strScore2));
    wsprintf(strScore2, "onEdge: %s", _sSonic.onEdge ? "true" : "false");
    TextOut(getMemDC(), 150, 170, strScore2, strlen(strScore2));
    wsprintf(strScore2, "onEdgeAfter: %s", _sSonic.onEdgeAfter ? "true" : "false");
    TextOut(getMemDC(), 150, 190, strScore2, strlen(strScore2));


    wsprintf(strScore2, "isMove: %s", _sSonic.isMove ? "true" : "false");
    TextOut(getMemDC(), 300, 30, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isMoveF: %s", _sSonic.isMoveF ? "true" : "false");
    TextOut(getMemDC(), 300, 50, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isMoveVF: %s", _sSonic.isMoveVF ? "true" : "false");
    TextOut(getMemDC(), 300, 70, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isNotControl: %s", _sSonic.isNotControl ? "true" : "false");
    TextOut(getMemDC(), 300, 90, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isSpinDash: %s", _sSonic.isSpinDash ? "true" : "false");
    TextOut(getMemDC(), 300, 110, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isDropDash: %s", _sSonic.isDropDash ? "true" : "false");
    TextOut(getMemDC(), 300, 130, strScore2, strlen(strScore2));
    wsprintf(strScore2, "pixelTest: %s", onPixel ? "true" : "false");
    TextOut(getMemDC(), 300, 150, strScore2, strlen(strScore2));
    wsprintf(strScore2, "isDamaged: %s", _sSonic.isDamaged ? "true" : "false");
    TextOut(getMemDC(), 300, 150, strScore2, strlen(strScore2));
}

void Sonic::gravity(void)
{
    if (_sSonic.isJump)
    {
        _gravity = 0.9f;
        _sSonic.jHeight *= _gravity;
        position.y -= _sSonic.jHeight;
    }
    
    if (_sSonic.onEdgeAfter)
    {
        _gravity = .9f;
        _sSonic.jHeight *= _gravity;
        position.y -= _sSonic.jHeight;
    }

    if (_sSonic.isDamaged)
    {
        position.y -= _sSonic.hSpeed;
    }

    if (!_sSonic.isAir && !_sSonic.onEdge && !_sSonic.isJump)
    {
        _sSonic.jHeight = 1;
    }

    if (_sSonic.isAir && _sSonic.jHeight <= 1)
    {
        _gravity = 1.1f;
        _fallSpeed *= _gravity;
        if (_fallSpeed >= 10) _fallSpeed = 10;
        position.y += _fallSpeed;
        _sSonic.onEdge = false;
    }
    else
        _fallSpeed = 1;

    if (_sSonic.hSpeed > .3f)
    {
        _sSonic.hSpeed *= 0.9f;
    }
    else
        _sSonic.hSpeed = 0;
}

void Sonic::jump(void)
{
    _sSonic.jHeight = 15.0f;
    _sSonic.isJump = true;
}


void Sonic::UpdateCamera()
{
    cameraX = position.x - WINSIZE_X / 2;
    cameraY = position.y - WINSIZE_Y / 2;

    if (cameraX < 0)
        cameraX = 0;
    else if (cameraX >= ww - WINSIZE_X)
        cameraX = ww - WINSIZE_X;

    if (cameraY < 0)
        cameraY = 0;
    else if (cameraY >= wh - WINSIZE_Y)
        cameraY = wh - WINSIZE_Y;
}


void Sonic::force360rolling()
{
    HDC world = IMAGEMANAGER->findImage("debugMap")->getMemDC();

    int x = (int)centerX;
    int y = (int)centerY;

    position.x = x + 70 * sin(_sonicRotate * M_PI / 180.0f);
    position.y = y + 70 * cos(_sonicRotate * M_PI / 180.0f);

    _sonicRotate += _sSonic.speed;

    if (is360 && _sonicRotate > 400)
        is360 = false;
}
