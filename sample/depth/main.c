// Zbuffer use.
// Z range : nearest 0 - 65535 farest
// Objects are automatically sorted to have a proper rendering with blending.

#include <pspkernel.h>
#include "../../glib2d.h"

PSP_MODULE_INFO("App",0,1,1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Callbacks */
int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0; }
int CallbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0; }
int SetupCallbacks() {
  int thid = 0;
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0) sceKernelStartThread(thid, 0, 0);
  return thid; }

int main()
{
  SetupCallbacks();

  while (1)
  {
    g2dClear(BLACK); // Clears zbuffer since Z coordinate is used in the loop

    g2dBeginRects(NULL);

    g2dSetColor(AZURE);
    g2dSetAlpha(255);
    g2dSetScaleWH(50,50);
    g2dSetCoordXYZ(195,50,0);
    g2dAdd();

    g2dSetColor(CHARTREUSE);
    g2dSetAlpha(200);
    g2dSetScaleWH(200,100);
    g2dSetCoordXYZ(20,20,0);
    g2dAdd();

    g2dSetColor(0xFFDDEEFF);
    g2dSetAlpha(127);
    g2dSetScaleWH(100,67);
    g2dSetCoordXYZ(170,60,1);
    g2dAdd();

    g2dEnd();

    g2dFlip(G2D_VSYNC);
  }

  sceKernelExitGame();
  return 0;
}
