#pragma once

#include <cstdint>
#include <memory>
#include <string>

// Я все опять переиначил
// Делаем проще но с фабрикой))
// Это просто информация о шейпах - Pod'ы
// Однако есть две идеи:
// 1) Можно сделать шейпы сериалайзэбл, но тут возникают странности
// сериализует она сама себя а вот десериализует ее что-то другое
// 2) делаем сериалайзер который понимает что это за тип данных
// и соответственно десериалайзер
//
// сейчас мне больше нравится второй подход
//
// к тому же я подумал и понял: нельзя просто так взять и сделать отмену действий
//
// ну тоесть можно, но это немного сложнее, и не за 5 минут
//
// просто добавлю ластик и все...

namespace wboard
{

enum class ShapeType
{
	Line,
	Circle,
	Rect,
	Text
};
	
struct Color
{
	uint16_t	B{ 0 };
	uint16_t	G{ 0 };
	uint16_t	R{ 0 };
};

struct Point
{
	int		X{ 0 };
	int		Y{ 0 };
};
	
struct ShapeBase
{
	ShapeType	Type;
	Color		ShapeColor;

	Point		P1;
	Point		P2;

	int			Thickness { 2 };
};

	// Добавил чисто для стиралки
struct Circle : ShapeBase
{
	Circle()
	{
		Type = ShapeType::Circle;
	}
};
	
struct Line : ShapeBase
{
	Line()
	{
		Type = ShapeType::Line;
	}
};

struct Rect : ShapeBase
{
	Rect()
	{
		Type = ShapeType::Rect;
	}
};

// Это пакет, просто сырые данные которые надо скопировать
// Добавлю их в пул наверное...
// точно так же выглядят штуки в сфмл

using Data = std::unique_ptr<uint8_t>;
constexpr size_t MAX_PCG_SIZE{ 512 };
	
struct Package final
{
	size_t	Emount;
	uint8_t	RowData[MAX_PCG_SIZE];
};

using Shape = std::shared_ptr<ShapeBase>;
	
}
