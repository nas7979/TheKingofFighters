#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
}

void cInputManager::Init()
{
	m_Keys[0][Key_Up] = 'W';
	m_Keys[0][Key_Down] = 'S';
	m_Keys[0][Key_Right] = 'D';
	m_Keys[0][Key_Left] = 'A';
	m_Keys[0][Key_WPunch] = 'H';
	m_Keys[0][Key_SPunch] = 'Y';
	m_Keys[0][Key_WKick] = 'J';
	m_Keys[0][Key_SKick] = 'U';
	m_Keys[0][Key_Run] = VK_SHIFT;
	m_Keys[0][Key_Jump] = VK_SPACE;

	m_Keys[1][Key_Up] = VK_UP;
	m_Keys[1][Key_Down] = VK_DOWN;
	m_Keys[1][Key_Right] = VK_RIGHT;
	m_Keys[1][Key_Left] = VK_LEFT;
	m_Keys[1][Key_WPunch] = VK_NUMPAD1;
	m_Keys[1][Key_SPunch] = VK_NUMPAD4;
	m_Keys[1][Key_WKick] = VK_NUMPAD2;
	m_Keys[1][Key_SKick] = VK_NUMPAD5;
	m_Keys[1][Key_Run] = VK_NUMPAD0;
	m_Keys[1][Key_Jump] = VK_NUMPAD3;
	
	m_Command[Key_Up] = '8';
	m_Command[Key_Down] = '2';
	m_Command[Key_Right] = '6';
	m_Command[Key_Left] = '4';
	m_Command[Key_WPunch] = 'p';
	m_Command[Key_SPunch] = 'P';
	m_Command[Key_WKick] = 'k';
	m_Command[Key_SKick] = 'K';

	//26 = 26
	//626 = 626
	//24 = 24
	//424 = 426
	//624 = 624
	//426 = 424
	//6246 = 6244
	//2624 = 2624
	//2426 = 2424
	//246 = 244
	//624624 = 624424
	//426426 = 424424

}

void cInputManager::Update()
{
	memcpy(m_Old, m_Cur, 128);
	memset(m_Cur, false, 128);
	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}

	for (int Side = 0; Side < 2; Side++)
	{
		m_InputBufferTimer[Side] -= DT;
		if (m_InputBufferTimer[Side] <= 0)
		{
			ClearInputBuffer(Side);
		}
	}
}

void cInputManager::Render()
{
}

void cInputManager::Release()
{
}

void cInputManager::AddToInputBuffer(int _Side, Keys _Key)
{
	if (m_InputBuffer[_Side].size() != 0)
	{
		if (_Key == Key_WPunch || _Key == Key_WKick || _Key == Key_SPunch || _Key == Key_SKick)
			if (m_Command[_Key] == m_InputBuffer[_Side].back())
				return;
	}
	else
		m_InputStartZ[_Side] = SYSTEM->m_Player[_Side]->m_Z;

	if (_Key == Key_Run || _Key == Key_Jump)
		return;
	m_InputBuffer[_Side].push_back(m_Command[_Key]);
	m_InputDirBuffer[_Side].push_back(SYSTEM->m_Player[_Side]->m_Scale.x);
	m_InputBufferTimer[_Side] = 0.2f;
}

void cInputManager::ClearInputBuffer(int _Side)
{
	m_InputBuffer[_Side].clear();
	m_InputDirBuffer[_Side].clear();
}

bool cInputManager::CheckCommand(Command _Stick, Keys _Button, int _Side)
{
	string Temp;
	int Dir = SYSTEM->m_Player[_Side]->m_Scale.x;
	cCharacter* Char = SYSTEM->m_Player[_Side]->GC(cCharacter);
	if ((_Stick == Cmd_2624 || _Stick == Cmd_24 || _Stick == Cmd_624) && (Char->m_SubState == State_Air || (Char->m_MainState != State_Idle && Char->m_MainState != State_Walk && Char->m_MainState != State_Run)))
	{
		Dir *= -1;
	}
	if (Dir == 1)
	{
		switch (_Stick)
		{
		case Cmd_26: Temp += "26"; break;
		case Cmd_626: Temp += "626"; break;
		case Cmd_624: Temp += "426"; break;
		case Cmd_426: Temp += "426"; break;
		case Cmd_2626: Temp += "2626"; break;
		case Cmd_22: Temp += "22"; break;
		case Cmd_24: Temp += "26"; break;
		case Cmd_2624: Temp += "2426"; break;
		case Cmd_66: Temp += "66"; break;
		case Cmd_88: Temp += "88"; break;
		case Cmd_26262626: Temp += "26262626"; break;
		}
	}
	else
	{
		switch (_Stick)
		{
		case Cmd_26: Temp += "24"; break;
		case Cmd_626: Temp += "424"; break;
		case Cmd_624: Temp += "624"; break;
		case Cmd_426: Temp += "624"; break;
		case Cmd_2626: Temp += "2424"; break;
		case Cmd_22: Temp += "22"; break;
		case Cmd_24: Temp += "24"; break;
		case Cmd_2624: Temp += "2624"; break;
		case Cmd_66: Temp += "44"; break;
		case Cmd_88: Temp += "88"; break;
		case Cmd_26262626: Temp += "24242424"; break;
		}
	}
	if (_Button != Key_End)
		Temp.push_back(m_Command[_Button]);

	int Size = Temp.size();
	int Pos = Clamp((int)m_InputBuffer[_Side].size() - Size, 0, 30);
	if (m_InputBuffer[_Side].compare(Pos, Size, Temp) == 0)
	{
		if (_Button != Key_End)
		{
			SYSTEM->m_Player[_Side]->m_Z = m_InputStartZ[_Side];
			m_InputBuffer[_Side].push_back('1');
			m_InputDirBuffer[_Side].push_back(1);
		}
		return true;
	}
	return false;
}
