#pragma once
class Samantha
{
private:
	static void MsgBox(const wchar_t* msg);
	static void DisplayHelp();
	static void SetNoclip(bool bNoclip);
	static void SetGodMode(bool bGodMode);
	static void SetUnlimitedAmmos(bool bUnlimitedAmmos);
	static void SetInfinitePoints(bool bInifinitePoints);
	static void QuitTrainer();
	static void ExecServer();
public:
	static void ExecTrainer(HMODULE hMod);
};

