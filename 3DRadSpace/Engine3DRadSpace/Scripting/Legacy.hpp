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
	void DLLEXPORT SetObjectList(Engine3DRadSpace::ObjectList* list);
	//Sets project file path used when resetting objects.
	void DLLEXPORT SetProjectPath(const std::filesystem::path &path);
}

extern "C"
{
	//
	//	Object functions.
	//

	void DLLEXPORT iObjectStart(unsigned obj_x);
	void DLLEXPORT iObjectStop(unsigned obj_x);
	void DLLEXPORT iObjectSwitch(unsigned obj_x);
	void DLLEXPORT iObjectShow(unsigned obj_x);
	void DLLEXPORT iObjectHide(unsigned obj_x);
	void DLLEXPORT iObjectShowHideSwitch(unsigned obj_x);
	void DLLEXPORT iObjectReset(unsigned obj_x);
	void DLLEXPORT iObjectOrientation(unsigned obj_x, Engine3DRadSpace::Math::Quaternion& q);
	void DLLEXPORT iObjectOrientationSet(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void DLLEXPORT iObjectOrientationReset(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void DLLEXPORT iObjectLocation(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectLocationSet(unsigned obj_x,const Engine3DRadSpace::Math::Vector3 &v);
	void DLLEXPORT iObjectLocationReset(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectPositionReset(
		unsigned OBJ_X,
		Engine3DRadSpace::Math::Quaternion& outRotation,
		Engine3DRadSpace::Math::Vector3& outLocation
	);
	void DLLEXPORT iObjectScaleSet(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectScale(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	float DLLEXPORT iObjectKmh(unsigned obj_x);
	void DLLEXPORT iObjectVelocity(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectVelocitySet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectSpin(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectSpinSet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectTorqueApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectAngularAccelerationApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void DLLEXPORT iObjectForceApply(unsigned ojb_x, Engine3DRadSpace::Math::Vector3 f, Engine3DRadSpace::Math::Vector3 *p);
	void DLLEXPORT iObjectAccelerationApply(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& acc);
	void DLLEXPORT iObjectDampingApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v, bool is_rotation, bool local_axis);
	//float iObjectPicked(OBJ_X, Vector3)
	int DLLEXPORT iObjectScan(
		unsigned obj_x,
		const Engine3DRadSpace::Math::Vector3 &origin,
		const Engine3DRadSpace::Math::Vector3 &direction,
		float radius,
		Engine3DRadSpace::Math::Vector3& contactPoint,
		Engine3DRadSpace::Math::Vector3& contactNormal
	);
	void DLLEXPORT iObjectTextSet(
		unsigned obj_x,
		const std::string& str
	);
	//iObjectParamSet(OBJ_X,int,float)
	void DLLEXPORT iObjectRefresh(unsigned obj_x, const std::string& path);
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

	int DLLEXPORT iStringLen(const std::string &str);
	void DLLEXPORT iStringUCase(const std::string &in, std::string &out);
	void DLLEXPORT iStringLCase(const std::string &in, std::string &out);
}