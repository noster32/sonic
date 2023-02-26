#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
    //! Do Nothing
    return S_OK;
}

void ImageManager::release(void)
{
    this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    //������ �̹��� ����
    img = new GImage;
    if (FAILED(img->init(width, height)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;

}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    //������ �̹��� ����
    img = new GImage;
    if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    //������ �̹��� ����
    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    //������ �̹��� ����
    img = new GImage;
    if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    //������ �̹��� ����
    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addRotateImage(string strKey, const char* fileName, float x, float y, int width, int height, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, _anchorX, _anchorY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addRotateFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, float _anchorX, float _anchorY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, _anchorX, _anchorY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::findImage(string strKey)
{
    auto key = _mImageList.find(strKey);

    if (key != _mImageList.end())
    {
        return key->second;
    }

    return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
    auto key = _mImageList.find(strKey);
    if (key != _mImageList.end())
    {
        key->second->release();
        SAFE_DELETE(key->second);
        _mImageList.erase(key);

        return true;
    }

    return false;
}

bool ImageManager::deleteAll()
{
    auto iter = _mImageList.begin();

    for (; iter != _mImageList.end();)
    {
        if (iter->second != nullptr)
        {
            iter->second->release();
            SAFE_DELETE(iter->second);
            iter = _mImageList.erase(iter);
        }
        else //����� ���� �Ǽ��� �����ϱ� ���� �������� �Ʒ��� �����д�.
        {
            ++iter;
        }
    }

    _mImageList.clear();
    
    return true;
}

void ImageManager::rotateUpdate(string strKey, float _dt, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->rotateUpdate(_dt, destX, destY);
}

void ImageManager::rotateFrameUpdate(string strKey, float _dt, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->rotateFrameUpdate(_dt, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
    GImage* img = findImage(strKey);
    if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
    GImage* img = findImage(strKey);
    if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    GImage* img = findImage(strKey);
    if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    GImage* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
    GImage* img = findImage(strKey);
    if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
    GImage* img = findImage(strKey);
    if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void ImageManager::rotateRender(string strKey, HDC hdc, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->rotateRender(hdc, destX, destY);
}

void ImageManager::rotateFrameRender(string strKey, HDC hdc)
{
    GImage* img = findImage(strKey);
    if (img) img->rotateFrameRender(hdc);
}
