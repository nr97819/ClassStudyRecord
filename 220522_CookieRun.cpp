#include <iostream>
using namespace std;

double dGravity = -9.8;

#define BOTTOM_Y_POSITION 0

struct Vec2
{
    float x;
    float y;
    
    Vec2()
    {
        x = 50.f;
        y = 0.f;
    }
}

enum class ePlayerState
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

class CPlayer
{
private:
    Vec2 vPos;
    double dStartSpeed;
    UINT iActiveMotion;
    UINT iExistJumpCnt;
    double dJumpTime;
    
public:
    CPlayer()
        : vPos{0.f, 0.f}
        , dStartSpeed(10.)
        , iActiveMotion(ePlayerState::RUN)
        , iExistJumpCnt(2)
        , dJumpTime(0.)
    {}
    ~CPlayer()
    {}
    
public:
    Vec2 GetPos(){ return vPos; }
    void SetPos(Vec2 _vPos) { vPos = _vPos; }
    
    UINT GetActiveMotion() { return iActiveMotion; }
    void SetActiveMotion(UINT iNumber) { iActiveMotion = iNumber; }
    
    void GetJumpCnt() {return iExistJumpCnt;}
    void ReduceJumpCnt() { iExistJumpCnt--; };
    
    void Update()
    {
        std::cout << "CurPos : " << GetPos().x << ", " << GetPos().y << endl;
        
        // 점프 후, 지면 도달 시 호출
        if(GetPos().y <= BOTTOM_Y_POSITION)
        {
            if(player.GetActiveMotion() == RUN)
                return;
                
            if(player.GetActiveMotion() == JUMP_END)
                return;
                
            if(player.GetActiveMotion() == SLIDE)
                return;
                
            SetActiveMotion(ePlayerState::JUMP_END)
        }
        
        // 꼭 0으로 초기화 해주기
        dJumpTime = 0.;
    }
    
    void Jump()
    {
        Vec2 vPos = GetPos();
        double fDelta = (dStartSpeed + dGravity * dJumpTime * fDT);
        
        vPos.y += vDelta;
        SetPos(vPos);
        
        if(player.GetActiveMotion() == JUMP_FALL)
            return;
        
        if(fDelta < 0.)
        {
            if(player.GetActiveMotion() == JUMP_START)
            {
                player.SetActiveMotion((UINT)ePlayerState::JUMP_FALL)
            }
            else if(player.GetActiveMotion() == JUMP2_START)
            {
                player.SetActiveMotion((UINT)ePlayerState::JUMP2_SPIN_FALL)
            }
        }
    }
}

int main()
{
    CPlayer player;
    
    while(true)
    {
        player.Update();
        
        if(KEY_STATE(KEY::SPACE) == DOWN)
        {
            if(GetJumpCnt() >= 0)
            {
                if(player.GetActiveMotion() == RUN)
                { 
                    // Falst Jump Start
                    player.SetActiveMotion((UINT)ePlayerState::JUMP_START);
                }
                else if(player.GetActiveMotion() == JUMP_START)
                { 
                    // Second Jump Start
                    player.SetActiveMotion((UINT)ePlayerState::JUMP2_START);
                }
                else if((player.GetActiveMotion() == JUMP_FALL)
                        && (player.GetJumpCnt() >= 0))
                {
                    // Second Jump Start (예외처리)
                    player.SetActiveMotion((UINT)ePlayerState::JUMP2_START);
                }
                player.ReduceJumpCnt(); // -1
            }
        }
        
        // 무시
        if(isJumpStarted())
        {
            Jump();
        }
    }
    
    return 0;
}
