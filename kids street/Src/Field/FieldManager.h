//FieldManager.h
//�t�B�[���h�Ǘ�
//CField�ւ̃A�N�Z�X�͕K��CFieldManager���o�R

#pragma once

#include "Road/Road.h"
#include "FieldCommon.h"

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
	//�N���X�擾�֘A�֐�
	CRoad* GetRoad()		{ return &road_; }

private:
	static CFieldManager*	instance_;
	CRoad					road_;								//���N���X

};