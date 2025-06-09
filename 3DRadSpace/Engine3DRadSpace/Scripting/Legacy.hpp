#pragma once

#include "../3DRadSpace.hpp"

/*
	Set of legacy functions from the old engine. Source: https://3drad.boards.net/page/script-reference
*/



namespace Engine3DRadSpace::Legacy
{
	//
	//Global state functions. As a end-user, ignore these two.
	//

	//Sets the global state, since a list of objects is required.
	void E3DRSP_SCRIPTING_EXPORT SetObjectList(Engine3DRadSpace::ObjectList* list);
	//Sets project file path used when resetting objects.
	void E3DRSP_SCRIPTING_EXPORT SetProjectPath(const std::filesystem::path &path);
}

extern "C"
{
	//
	//	Object functions.
	//

	void E3DRSP_SCRIPTING_EXPORT iObjectStart(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectStop(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectSwitch(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectShow(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectHide(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectShowHideSwitch(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectReset(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientation(unsigned obj_x, Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientationSet(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientationReset(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocation(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocationSet(unsigned obj_x,const Engine3DRadSpace::Math::Vector3 &v);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocationReset(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectPositionReset(
		unsigned OBJ_X,
		Engine3DRadSpace::Math::Quaternion& outRotation,
		Engine3DRadSpace::Math::Vector3& outLocation
	);
	void E3DRSP_SCRIPTING_EXPORT iObjectScaleSet(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectScale(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	float E3DRSP_SCRIPTING_EXPORT iObjectKmh(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectVelocity(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectVelocitySet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectSpin(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectSpinSet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectTorqueApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectAngularAccelerationApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectForceApply(unsigned ojb_x, Engine3DRadSpace::Math::Vector3 f, Engine3DRadSpace::Math::Vector3 *p);
	void E3DRSP_SCRIPTING_EXPORT iObjectAccelerationApply(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& acc);
	void E3DRSP_SCRIPTING_EXPORT iObjectDampingApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v, bool is_rotation, bool local_axis);
	//float iObjectPicked(OBJ_X, Vector3)
	int E3DRSP_SCRIPTING_EXPORT iObjectScan(
		unsigned obj_x,
		const Engine3DRadSpace::Math::Vector3 &origin,
		const Engine3DRadSpace::Math::Vector3 &direction,
		float radius,
		Engine3DRadSpace::Math::Vector3& contactPoint,
		Engine3DRadSpace::Math::Vector3& contactNormal
	);
	void E3DRSP_SCRIPTING_EXPORT iObjectTextSet(
		unsigned obj_x,
		const std::string& str
	);
	//iObjectParamSet(OBJ_X,int,float)
	void E3DRSP_SCRIPTING_EXPORT iObjectRefresh(unsigned obj_x, const std::string& path);
	//int iObjectBonesCount(OBJ_X)
	//void iObjectBoneOrientation(OBJ_X,int,Quaternion,int)
	//iObjectBoneLocation(OBJ_X,int,Vector3,int)
	//void iObjectBoneOrientationSet(OBJ_X,int,Quaternion,int)\
	//iObjectBoneLocationSet(OBJ_X,int,Vector3)
	//iObjectBoneScaleSet(OBJ_X,int,Vector3)
	//iObjectEnvMapFocusSet(OBJ_X,Vector3)
	//iObjectImpostersCreate(OBJ_X,int)
	//iObjectImpostersDestroy(OBJ_X)
	//iObjectImposterSet(OBJ_X,int,Quaternion,Vector3)
	//iObjectImposterGet(OBJ_X,int,Quaternion,Vector3)
	//iObjectImposterScaleSet(OBJ_X,int,Vector3)
	//iObjectImposterHide(OBJ_X,int)
	//iObjectImposterShow(OBJ_X,int)
	//iObjectImposterShadowEnable(OBJ_X, int, bool)
	//iObjectImposterTorqueApply(OBJ_X,int,Vector3)
	//iObjectImposterAngularAccelerationApply(OBJ_X,int,Vector3)
	//iObjectImposterForceApply(OBJ_X,int,Vector3,Vector3)
	//iObjectImposterAccelerationApply(OBJ_X,int,Vector3) 
	//iObjectImposterVelocitySet(OBJ_X,int,Vector3)
	//iObjectChildTransform(OBJ_X, OBJ_Y, Vector3, Vector3)

	//void DLLEXPORT iShaderSet(int obj_x, const std::string& path);
	//iShaderStack(OBJ_X,string,float)
	//iShaderFloatSet(OBJ_X, string, float)
	//iShaderFloat2Set(OBJ_X,string,float,float)
	//iShaderFloat3Set(OBJ_X,string,float,float,float)
	//iShaderFloat4Set(OBJ_X,string,float,float,float,float)
	//iShaderFloat4x3Set(OBJ_X,string,float,float,float,float,float,float,float,float,float,float,float,float)
	//iShaderFloat4x4Set(OBJ_X,string,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)
	//iShaderViewMatrixSet(OBJ_X, string, OBJ_Y)
	//iShaderProjectionMatrixSet(OBJ_X,string,OBJ_Y)
	//int iShaderTextureCreate(string)
	//iShaderTextureDestroy(int)
	//iShaderTextureSet(OBJ_X,string,int)

	int E3DRSP_SCRIPTING_EXPORT iStringLen(const std::string &str);
	void E3DRSP_SCRIPTING_EXPORT iStringUCase(const std::string &in, std::string &out);
	void E3DRSP_SCRIPTING_EXPORT iStringLCase(const std::string &in, std::string &out);
}