#ifndef _CORE_H
#define _CORE_H

#include <External/GL/glew.h>
#include <External/GLFW/glfw3.h>
#include <SGUtil.h>

void ProcessInput(GLFWwindow *window, int key, int scancode, int action, int mods);

namespace SGEngine
{
class SGCore
{
  public:
    static SGCore &instance();
    
    int InitEngine();
    int run();
    int EngineDispose();

    //Abstract methods
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Start() = 0;
    virtual void ApplicationDispose() = 0;
    
    GLFWwindow &GetMainWindow()
    {
        return *mainWindow;
    }

    void HandleInput(GLFWwindow *wnd, int key, int action);
  protected:
    GLFWwindow *mainWindow;
    SGCore();
    virtual ~SGCore();
    static SGCore *_instance; // Not thread safe ?
};
} // namespace SGEngine

#endif