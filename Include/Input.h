#ifndef _INPUT_H
#define _INPUT_H

#include "SGUtil.h"

namespace SGEngine
{
class Input
{
  public:
    static Input& instance();
    ~Input();

    // Call each frame............
    void ClearLastFrameKey();

    // Handled by Windows Message
    void SetKeyDown(SG_UINT virtualKeyCode);
    void SetKeyUp(SG_UINT virtualKeyCode);
    //True during the frame user pressed the key
    bool GetKeyDown(SG_UINT keyCode);
    //True each frame the key is pressed
    bool GetKey(SG_UINT keyCode);
    bool GetKeyUp(SG_UINT keyCode);

  private:
    Input();

    bool keyState[256];
    //Exist for 1 Frame only
    unsigned int m_lastFrameKey;
    unsigned int m_lastFrameReleasedKey;
};

} // namespace SGEngine

#endif