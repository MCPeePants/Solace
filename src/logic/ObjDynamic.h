/// The ObjDynamic class is the base class for any object that is required to move
/// and generally be interactive in some way

#ifndef SLC_LOGIC_OBJDYNAMIC_H
#define SLC_LOGIC_OBJDYNAMIC_H

#include <SFML/Graphics.hpp>

class ObjDynamic
{
    private:
    int m_X, m_Y;             // X and Y position   Shouldn't these be floats?
    float m_Xvel, m_Yvel;     // X and Y velocity
    sf::Sprite m_Sprite;     // Object sprite
    sf::Image m_Image;       // Image that can be used for the sprite

    public:
    ObjDynamic(int X, int Y)
    {
        m_X = X;
        m_Y = Y;

        m_Xvel = 0.0f;
        m_Yvel = 0.0f;

        m_Sprite.SetPosition((float)m_X, (float)m_Y);
    }
    ObjDynamic(int X, int Y, float Vx, float Vy)
    {
        m_X = X;
        m_Y = Y;

        m_Xvel = Vx;
        m_Yvel = Vy;

        m_Sprite.SetPosition((float)m_X, (float)m_Y);
    }
    bool SetImage(char* Filepath)
    {
        if(m_Image.LoadFromFile(Filepath))
        {
            m_Sprite.SetImage(m_Image);
            return true;
        }
        else return false;
    }
    sf::Sprite GetDrawable()
    {
        return m_Sprite;
    }
    void SetPosition(int X, int Y)
    {
        m_X = X;
        m_Y = Y;

        m_Sprite.SetPosition((float)m_X, (float)m_Y);
    }
    void SetVelocity(float Vx, float Vy)
    {
        m_Xvel = Vx;
        m_Yvel = Vy;
    }
    int GetX()
    {
        return m_X;
    }
    int GetY()
    {
        return m_Y;
    }
    float GetVelocityX()
    {
        return m_Xvel;
    }
    float GetVelocityY()
    {
        return m_Yvel;
    }
};

#endif // SLC_LOGIC_OBJDYNAMIC_H
