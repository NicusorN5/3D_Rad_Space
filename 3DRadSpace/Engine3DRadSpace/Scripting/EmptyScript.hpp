#include "IScript.hpp"

using namespace Engine3DRadSpace::Scripting;

/// <summary>
/// Used as reference for source code generators. Not to be used in the game engine source code.
/// </summary>
class EmptyScript : public IScript
{
public:
	void Start() override;
	void Update() override;
	void End() override;

	~EmptyScript();
};