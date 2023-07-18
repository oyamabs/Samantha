#include "pch.h"
#include "hook.h"

int windowHeight, windowWidth;

BOOL CALLBACK enumWind(HWND handle, LPARAM lp) {
    DWORD pId;
    GetWindowThreadProcessId(handle, &pId);

    if (GetCurrentProcessId() != pId)
        return TRUE;

    window = handle;
    return FALSE;
}

HWND GetProcessWindow() {
    window = NULL;

    EnumWindows(enumWind, NULL);

    RECT size;
    GetWindowRect(window, &size);
    windowWidth = size.right - size.left;
    windowHeight = size.bottom - size.top;

    windowHeight -= 29;
    windowWidth -= 5;

    return window;
}

bool GetD3D9Device(void** device, size_t deviceSize) {
    if (!device)
        return false;

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D)
        return false;

    IDirect3DDevice9* pDummyDevice = nullptr;

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();

    HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

    if (dummyDeviceCreated != S_OK) {
        d3dpp.Windowed = false;

        HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
    
        if (dummyDeviceCreated != S_OK) {
            pD3D->Release();
            return false;
        }
    }

    memcpy(device, *(void***)pDummyDevice, deviceSize);
    pDummyDevice->Release();
    pD3D->Release();
    return true;
}