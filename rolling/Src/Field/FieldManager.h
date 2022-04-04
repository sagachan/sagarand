//FieldManager.h
//フィールド管理
//CFieldへのアクセスは必ずCFieldManagerを経由

#pragma once

#include "Road/Road.h"
#include "FieldCommon.h"
#include "Wall/Wall.h"
#include "Sky/Sky.h"

class CFieldManager
{
public:
	CFieldManager();
	~CFieldManager();
	
public:
	static void CreateInstance() { if (!instance_)instance_ = new CFieldManager; }
	static CFieldManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	void Init();
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();
	
	
public:
	//クラス取得関連関数
	CRoad* GetRoad()		{ return &road_; }
	CWall* GetWall()		{ return &wall_; }
	CSky* GetSky()			{ return &sky_; }


private:
	static CFieldManager*	instance_;
	CRoad					road_;								//道クラス
	CWall					wall_;								//壁クラス
	CSky					sky_;								//空クラス
};