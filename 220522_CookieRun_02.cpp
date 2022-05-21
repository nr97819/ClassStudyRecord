#include <iostream>
#include <vector>

/*enum class ANIM_TYPE
{
    ENVIRONMENT,
    PLAYER,
    
    LAST_INDEX
}*/

enum class ANIM_STATE
{
    RUN,
    
    JUMP_START,
    
    JUMP2_START,
    JUMP2_SPIN_FALL,
    
    JUMP_FALL,
    JUMP_END,
    
    SLIDE
    
    LAST_INDEX
}

class CApp
{
private:
    /*std::vector<CAnimation*> pArrVectorAnims[ANIM_TYPE::LAST_INDEX];*/
    CPlayer* player;
    //D2D1Bitmap* pBitmap_midnight;
    D2D1Bitmap* pBitmap_cookie;
    
public:
    void Init()
    {
        /* ------------------------ */
        /*      핵심 추가 코드      */
        /* ------------------------ */
        UINT TILE_SIZE_X = 96;
        UINT TILE_SIZE_Y = 98;
        UINT PADDING_SIZE = 2;
        
        // 자동화 코드(내가 만든 생성자의 반복문)를 활용한 모습
        CAnimation* anim_run = new CAnimation(0.1, 8, pBitmap_cookie, 0, 100, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::RUN, anim_run);
        
        CAnimation* anim_jump_start = new CAnimation(0.1, 4, pBitmap_cookie, 0, 200, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::JUMP_START, anim_jump_start);
        
        CAnimation* anim_jump2_start = new CAnimation(0.1, 6, pBitmap_cookie, 0, 600, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::JUMP2_START, anim_jump2_start);
        
        CAnimation* anim_jump2_spinFall = new CAnimation(0.1, 8, pBitmap_cookie, 0, 400, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::JUMP2_SPIN_FALL, anim_jump2_spinFall);
        
        CAnimation* anim_jump_fall = new CAnimation(0.1, 4, pBitmap_cookie, 0, 300, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::JUMP_FALL, anim_jump_fall);
        
        CAnimation* anim_jump_end = new CAnimation(0.1, 4, pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::JUMP_END, anim_jump_end);
        
        CAnimation* anim_slide = new CAnimation(0.1);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        anim_slide->AddSprite(pBitmap_cookie, 0, 700, TILE_SIZE_X, TILE_SIZE_Y, PADDING_SIZE);
        SetAnimation(ANIM_STATE::SLIDE, anim_slide);
        // 강사님 말대로 하면 어떻게 되는지 보여드리기 위함...
        
public:
    void Update(){}
    void Render(){}
    void Release(){}
}

class CPlayer
{
private:
    /* ------------------------ */
    /*      핵심 추가 코드      */
    /* ------------------------ */
    
    // CAnimation은 array로 구현하도록 수정하고,
    // CSprite만 vector로 구현한 점
    CAnimation* pArrAnims[ANIM_STATE::LAST_INDEX];
    Vec2 vPos;
    
public:
    CPlayer(){}
    ~CPlayer()
    {
        for(UINT i = 0; i < ANIM_STATE::LAST_INDEX; ++i)
        {
            if(nullptr != pArrAnims[i])
            {
                delete pArrAnims[i];
                pArrAnims[i] = nullptr;
            }
        }
    }
    
public:
    void Render()
    {
        for(std::vector<CAnimation*>::iterator it = pArrAnims.Begin(); it != pArrAnims.End(); ++it)
        {
            if(nullptr != it.ptr)
            {
                it.ptr->Render(vPos.x, vPos.y);
            }
        }
    }
    
/* ------------------------ */
/*      핵심 추가 코드      */
/* ------------------------ */
public:
    void SetAnimation(UINT _iAnimState, CAnimation* _pAnimation)
    {
        pArrAnims[_iAnimState] = _pAnimation;
    }
};

class CAnimation
{
private:
    std::vector<CSprite*> pVecSprites;
    double dInterval;
    double dAccValue;
    
public:
    CAnimation()
        : dInterval(0.1)
        , dAccValue(0.)
    {
        
    }
    
    CAnimation(_dInterval, _iCount, _pBitmap, _iStartX, _iStartY, _iSizeX, _iSizeY, iPadding)
        : dInterval(0.1)
        , dAccValue(0.)
    {
        /* ------------------------ */
        /*      핵심 추가 코드      */
        /* ------------------------ */
        // 이전에 왜 CAnimation 초기화 할 때, 이러한 내용들을 받았었는지 기억났다... 받는 것이 편하다...
        for(UINT i=0; i<_iCount; ++i)
        {
           AddSprite(new CSprite(_pBitmap, 
                _iStartX + (i * _iSizeX + iPadding), 
                _iStartY + (i * _iSizeY + iPadding), 
                _iSizeX + (i * _iSizeX + iPadding), 
                _iSizeY + (i * _iSizeY + iPadding)));
        }
    }
    CAnimation(double _dInterval)
        : dInterval(_dInterval)
        , ...
    {
        ...
    }
    ~CAnimation()
    {
        for(std::vector<CSprite*>::iterator it = pVecSprites.Begin(); it != pVecSprites.End(); ++it)
        {
            if(nullptr != it.ptr)
            {
                delete it.ptr;
                it.ptr = nullptr;
            }
        }
    }
    
public:
    void AddSprite(CSprite* _sprite)
    {
        pVecSprites.push_back(_sprite);
    }
    
public:
    void Render(int _startX, int _startY)
    {
        for(std::vector<CSprite*>::iterator it = pArrSprites.Begin(); it != pArrSprites.End(); ++it)
        {
            if(dAccValue >= dInterval)
            {
                if(nullptr != it.ptr)
                {
                    it.ptr->Render();
                }
            }
        }
    }
};

class CSprite
{
private:
    D2D1Bitmap      pBitmap;
    Vec2            vStartPos;
    Vec2            vEndPos;
    
/* ------------------------ */
/*      핵심 추가 코드      */
/* ------------------------ */
public:
    CSprite(D2D1Bitmap* _pBitmap, Vec2 _vStartPos, Vec2 _vEndPos)
        : bitmap(_pBitmap)
        , vStartPos(_vStartPos)
        , vEndPos(_vEndPos)
    {}
    
public:
    void Render(int _startX, int _startY)
    {
        D2D1::DrawScreen(D2D1Core::GetInst()->GetRT()
                            , _startX
                            , _startY,
                            ...
                            )
    }
};

int main()
{
    CApp app;
    app.Init();
    while(true)
    {
        app.Update();
        app.Render();
    }
    app.Release();
    
    return 0;
}
