#pragma once
#include "../Reflection/Reflection.hpp"
#include "../Game.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Engine3DRadSpace::Reflection
{
	void to_json(json& j, const UUID& uuid);
	void from_json(const json& j, UUID& uuid);
}

namespace Engine3DRadSpace::Projects
{
	class Serializer
	{
	public:
		static json SerializeObject(Engine3DRadSpace::IObject* obj);
		static [[nodiscard]] Engine3DRadSpace::IObject* DeserializeObject(const json& j);

		static bool LoadProject(
			Engine3DRadSpace::ObjectList* lst,
			Engine3DRadSpace::Content::ContentManager* content,
			const std::filesystem::path& projectPath
		);

		static bool SaveProject(Engine3DRadSpace::ObjectList* lst, Engine3DRadSpace::Content::ContentManager* content, const std::filesystem::path& projectPath);
	};
}