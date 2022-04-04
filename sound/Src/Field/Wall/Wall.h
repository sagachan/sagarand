

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Animation/Model/model.h"
#include "../../Scene/SceneManager.h"

class CWall : public CModel
{
public:

public:
	CWall();
	~CWall();

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
	void	CheckCollision();							//“–‚½‚è”»’èŒvŽZ

private:
	MapInfo					mapInfo_;
};