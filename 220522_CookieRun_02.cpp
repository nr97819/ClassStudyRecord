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
    
public:
    void Init()
    {
        /* ------------------------ */
        /*      핵심 추가 코드      */
        /* ------------------------ */
        CAnimation* anim_run = new CAnimation(0.);
        CAnimation* anim_jump_start = new CAnimation(0.);
        CAnimation* anim_jump2_start = new CAnimation(0.);
        CAnimation* anim_jump2_spinFall = new CAnimation(0.);
        CAnimation* anim_jump_fall = new CAnimation(0.);
        CAnimation* anim_jump_end = new CAnimation(0.);
        CAnimation* anim_slide = new CAnimation(0.);
        
        SetAnimation(ANIM_STATE::RUN, anim_run);
        SetAnimation(ANIM_STATE::RUN, anim_jump_start);
        SetAnimation(ANIM_STATE::RUN, anim_jump2_start);
        SetAnimation(ANIM_STATE::RUN, anim_jump2_spinFall);
        SetAnimation(ANIM_STATE::RUN, anim_jump_fall);
        SetAnimation(ANIM_STATE::RUN, anim_jump_end);
        SetAnimation(ANIM_STATE::RUN, anim_slide);
    
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
    std::vector<CSprite*> pArrSprites;
    double dInterval;
    double dAccValue;
    
public:
    CAnimation()
        : dInterval(0.1)
        , dAccValue(0.)
    {
        
    }
    CAnimation(double _dInterval)
        : dInterval(_dInterval)
        , ...
    {
        ...
    }
    ~CAnimation()
    {
        for(std::vector<CSprite*>::iterator it = pArrSprites.Begin(); it != pArrSprites.End(); ++it)
        {
            if(nullptr != it.ptr)
            {
                delete it.ptr;
                it.ptr = nullptr;
            }
        }
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
    D2D1Bitmap      bitmap;
    Vec2            vStartPos;
    Vec2            vEndPos;
    
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
