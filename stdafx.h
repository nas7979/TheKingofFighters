#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <io.h>
#include <dsound.h>
#include "SDKsound.h"
#include "SDKwavefile.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "dsound.lib")

#define g_Device DXUTGetD3D9Device()
#define AC(a) AddComponent<a>()
#define GC(a) GetComponent<a>()

using namespace std;

using Vec2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;

#include "cImageManager.h"
#include "cSystemManager.h"
#define DT SYSTEM->m_DT
#define NSDT SYSTEM->m_NSDT
#include "Math.h"
using namespace Math;
#include "cSoundManager.h"
#include "cObjectManager.h"
#include "cParticleManager.h"
#include "cInputManager.h"
#include "cCameraManager.h"
#include "cScheduleManager.h"
#include "cSceneManager.h"

#include "cRenderer.h"
#include "cAnimation.h"
#include "cCollider.h"
#include "cCharacter.h"
#include "cKyo.h"
#include "cKim.h"
#include "cHitBox.h"
#include "cMissile.h"
