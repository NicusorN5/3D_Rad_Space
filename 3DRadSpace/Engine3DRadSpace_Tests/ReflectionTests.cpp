#include "pch.h"
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/IObject3D.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Content;

class TestObject : public IObject3D
{
public:
	TestObject() : IObject3D("Test object"), 
		Integer(5),
		Float(1.0f), 
		TestKey(Key::Space)
	{
	}

	// Inherited via IObject
	void Initialize() override
	{
	}

	void Load() override
	{
	}

	void Load(const std::filesystem::path &dummy) override
	{
	}

	void Update() override
	{
	}

	void Draw3D() override
	{
	}

	void EditorInitialize() override
	{
	}

	void EditorDraw3D(bool selected) override
	{
	}

	void EditorUpdate() override
	{
	}
	
	Reflection::UUID GetUUID() const noexcept override
	{
		// {017161C9-9EB7-4C10-AEEE-24347466586D}
		return {0x17161c9, 0x9eb7, 0x4c10, { 0xae, 0xee, 0x24, 0x34, 0x74, 0x66, 0x58, 0x6d }};
	}
	void EditorLoad() override
	{
	}
	std::optional<float> Intersects(const Ray&r) override
	{
		return std::nullopt;
	}

	int Integer;
	float Float;
	Color Colour;
	Math::Rectangle Rectangle1;
	RectangleF Rectangle2;

	Vector4 Vector;
	Key TestKey;
};

REFL_BEGIN(TestObject, "Test Object", "Tests", "Dummy test object")
	REFL_FIELD(TestObject, std::string, Name, "Name", "Test object", "Name of the object")
	REFL_FIELD(TestObject, bool, Enabled, "Enabled", true, "Is the object enabled?")
	REFL_FIELD(TestObject, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(TestObject, Vector3, Position, "Position", Vector3::Zero(), "Object position in world")
	REFL_FIELD(TestObject, Vector3, RotationCenter, "Rotation center", Vector3::Zero(), "Rotation pivot point")
	REFL_FIELD(TestObject, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation")
	REFL_FIELD(TestObject, Vector3, Scale, "Scale", Vector3::One(), "Object scale")
	REFL_FIELD(TestObject, int, Integer, "Test Integer", 5, "int32_t value used for testing")
	REFL_FIELD(TestObject, float, Float, "Test float", 1.0f, "test float value")
	REFL_FIELD(TestObject, Color, Colour, "Test color", Colors::White, "test color")
	REFL_FIELD(TestObject, Math::Rectangle, Rectangle1, "Test rectangle 1", Math::Rectangle(1, 2, 3, 4), "integer rectangle")
	REFL_FIELD(TestObject, RectangleF, Rectangle2, "Test rectangle 2", RectangleF(5, 4, 3, 2), "float rectangle")
	REFL_FIELD(TestObject, Vector4, Vector, "Vector4", Vector4(0, 0, 0, 1), "Test vector4")
	REFL_FIELD(TestObject, Key, TestKey, "Test key", Key::ESC, "Dummy test key")
REFL_END

TEST(ReflectionTests, VisibleStrings)
{
	EXPECT_EQ(TestObjectReflInstance[0]->FieldName(), std::string("Name")); //visible name
	EXPECT_EQ(TestObjectReflInstance[0]->FieldDesc(), std::string("Name of the object")); //description
	
	//default value
	std::string v = *static_cast<const std::string*>(TestObjectReflInstance[0]->DefaultValue());
	EXPECT_EQ(v, "Test object");
}

TEST(ReflectionTests, SizeTests)
{
	EXPECT_EQ(TestObjectReflInstance[0]->TypeSize(), sizeof(std::string)); //test sizeof(T)
	EXPECT_EQ(TestObjectReflInstance[0]->TypeHash(), typeid(std::string).hash_code()); //object hash code
	EXPECT_EQ(TestObjectReflInstance["Test float"]->FieldOffset(), offsetof(TestObject, Float)); //test the offset.
}

#define TestFieldRW(id, fieldName, type, value) \
TEST(ReflectionTests, fieldName##RW ) \
{ \
	TestObject test; \
	type temp = value; \
	TestObjectReflInstance[id]->Set(&test, &temp); \
	EXPECT_EQ(temp, test. fieldName); \
	EXPECT_EQ(*static_cast<const type *>(TestObjectReflInstance[id]->Get(&test)), temp); \
}

TestFieldRW(0, Name, std::string, "Test name")
TestFieldRW(1, Enabled, bool, true)
TestFieldRW(2, Visible, bool, true)
TestFieldRW(3, Position, Vector3, Vector3(1,2,3))
TestFieldRW(4, RotationCenter, Vector3, Vector3(5,5,5))
TestFieldRW(5, Rotation, Quaternion, Quaternion(1,2,3,4))
TestFieldRW(6, Scale, Vector3, Vector3(3,3,3))
TestFieldRW(7, Integer, int, 34)
TestFieldRW(8, Float, float, 3.141f)
TestFieldRW(9, Colour, Color, Colors::Red)
TestFieldRW(10, Rectangle1, Math::Rectangle, Math::Rectangle(1,2,3,4))
TestFieldRW(11, Rectangle2, Math::RectangleF, Math::RectangleF(1.1f ,2.2f ,3.3f ,4.4f))
TestFieldRW(12, Vector, Vector4, Vector4(4,3,2,1))
TestFieldRW(13, TestKey, Key, Key::Enter)

TEST(ReflectionTests, UUIDTest)
{
	TestObject o;
	TestObjectReflInstance.ObjectUUID == o.GetUUID();
}