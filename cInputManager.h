#pragma once
enum Keys
{
	Key_Up,
	Key_Down,
	Key_Right,
	Key_Left,
	Key_WPunch,
	Key_SPunch,
	Key_WKick,
	Key_SKick,
	Key_Run,
	Key_Jump,
	Key_End
};
enum Command
{
	Cmd_26,
	Cmd_626,
	Cmd_624,
	Cmd_426,
	Cmd_2626,
	Cmd_22,
	Cmd_66,
	Cmd_88,
	Cmd_24,
	Cmd_2624,
	Cmd_26262626
};

class cInputManager : public cSingleton<cInputManager>
{
public:
	cInputManager();
	~cInputManager();

	void Init();
	void Update();
	void Render();
	void Release();

	bool m_Cur[128];
	bool m_Old[128];
	int m_Keys[2][Key_End];
	int m_Command[Key_End];
	int m_InputStartZ[2];
	string m_InputBuffer[2];
	vector<int> m_InputDirBuffer[2];
	float m_InputBufferTimer[2];

	bool KeyDown(int _Key) { return m_Cur[_Key] && !m_Old[_Key]; }
	bool KeyPress(int _Key) { return m_Cur[_Key]; }
	bool KeyUp(int _Key) { return !m_Cur[_Key] && m_Old[_Key]; }
	void AddToInputBuffer(int _Side, Keys _Key);
	void ClearInputBuffer(int _Side);
	bool CheckCommand(Command _Stick, Keys _Button, int _Side);
};

#define INPUT cInputManager::GetInstance()