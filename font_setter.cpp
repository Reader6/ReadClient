#include "font_setter.h"

font_setter::font_setter()
{
    m_fontSize=16;      //默认值
}


int font_setter::getFontSize()const
{
    return m_fontSize;
}
QString font_setter::getFontColor()const
{
        return m_fontColor;
}
void font_setter::setFontSize(int Size)
{
        m_fontSize=Size;
}
void font_setter::setFontColor(QString Color)
{
        m_fontColor=Color;

}

int font_setter::getAlignment() const
{
    return  m_alignment;
}

void font_setter::setAlignment(int Alignment)
{
    m_alignment=Alignment;
}

double font_setter::getWordSpcing() const
{
    return m_word_spacing;
}

void font_setter::setWordSpcing(double word_spcing)
{
       m_word_spacing=word_spcing;
}

