#pragma once
#include "../IObject.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Counter object to be used together with other event objects (EoL, EoV, et cetera...)
	/// To be maninly used (eventually) as compatibility with 3DRad v722.
	/// </summary>
	/// 
	/// <remarks>
	/// Notes:
	///  -When toggling Enabled to true, the counter will increment by the Increment value, then Enabled will become false. 
	/// This behiavor is defined in ::Update().\
	/// </remarks>
	class DLLEXPORT Counter: public IObject
	{
	public:
		Counter();
		Counter(const std::string& name, double vaulue, double increment);

		double Value;
		double Increment;

		bool LoadFromFile = false;
		std::string FilePath;

		void Initialize() override;
		void EditorInitialize() override;

		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void EditorLoad() override;

		void Update() override;

		void Save();

		Reflection::UUID GetUUID() const noexcept override;

		~Counter() override;
	};
}

REFL_FWD(Counter)