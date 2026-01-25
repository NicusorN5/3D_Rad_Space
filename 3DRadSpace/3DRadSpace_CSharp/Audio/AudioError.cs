namespace Engine3DRadSpace.Audio;

public enum AudioError : int
{
	None = 0,
	BadID,
	InvalidEnum,
	InvalidValue,
	InvalidOperation,
	OutOfMemory,
	Unspecified = 0x7FFFFFFF,
};
