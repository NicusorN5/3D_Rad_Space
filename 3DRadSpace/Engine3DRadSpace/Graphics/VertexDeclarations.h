#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"

typedef struct E3DRSP_VertexPosition
{
	E3DRSP_Vector3 Position;
} E3DRSP_VertexPosition;

typedef struct E3DRSP_VertexPositionColor
{
	E3DRSP_Vector3 Position;
	E3DRSP_Color Color;
} E3DRSP_VertexPositionColor;

typedef struct E3DRSP_VertexPositionUV
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector2 UV;
} E3DRSP_VertexPositionUV;
	
typedef struct E3DRSP_VertexPointUV
{
	E3DRSP_Vector2 Position;
	E3DRSP_Vector2 UV;
} E3DRSP_VertexPointUV;

typedef struct E3DRSP_VertexPositionNormalColor
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Color Color;
} E3DRSP_VertexPositionNormalColor;

typedef struct E3DRSP_VertexPositionNormalUV
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector2 UV;
} E3DRSP_VertexPositionNormalUV;

typedef struct E3DRSP_VertexPositionNormalUVColor
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector2 UV;
	E3DRSP_Color Color;
} E3DRSP_VertexPositionNormalUVColor;

typedef struct E3DRSP_VertexPositionNormalBitangent
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector3 Tangent;
	E3DRSP_Vector3 Bitangent;
} E3DRSP_VertexPositionNormalBitangent;

typedef struct E3DRSP_VertexPositionNormalBitangentColor
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector3 Tangent;
	E3DRSP_Vector3 Bitangent;
	E3DRSP_Color Color;
} E3DRSP_VertexPositionNormalBitangentColor;

typedef struct E3DRSP_VertexPositionNormalBitangentUVColor
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector3 Tangent;
	E3DRSP_Vector3 Bitangent;
	E3DRSP_Vector2 UV;
	E3DRSP_Color Color;
} E3DRSP_VertexPositionNormalBitangentUVColor;

typedef struct E3DRSP_VertexPositionNormalBitangentUV
{
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Normal;
	E3DRSP_Vector3 Tangent;
	E3DRSP_Vector3 Bitangent;
	E3DRSP_Vector2 UV;
} E3DRSP_VertexPositionNormalBitangentUV;

typedef struct E3DRSP_VertexPointUVColor
{
	E3DRSP_Vector2 Position;
	E3DRSP_Vector2 UV;
	E3DRSP_Color Color;
} E3DRSP_VertexPointUVColor;