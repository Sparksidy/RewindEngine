/******************************************************************************/
/*!
\file  GameClock.h
\project  CS562 - //Code borrowed from my own graphics framework
\author Esteban Enrique Maldonado Cabán

Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#pragma once

class GameClock
{
public:
	//CONSTRUCTORS
	GameClock(void);
	~GameClock(void);

	//GETTERS
	float GetTotalTime(void) const;
	float GetDeltaTime(void) const;

	//UTILITY
	void ResetClock(void);
	void StartClock(void);
	void StopClock(void);
	void Tick(void);

private:
	double m_SecondsPerCount;
	double m_Dt;

	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StoppedTime;
	__int64 m_PreviousTime;
	__int64 m_CurrentTime;

	bool m_IsStopped;

};