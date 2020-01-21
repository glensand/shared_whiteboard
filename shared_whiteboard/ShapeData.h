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

struct Color
{
	uint16_t	B;
	uint16_t	G;
	uint16_t	R;
};
	
struct ShapeBase
{
	// Так я надеюсь никто до этого не доебется
	// сейчас мне так удобнее всего сделать определение типа
	virtual ~ShapeBase() = default;
	
	Color ShapeColor;
};
	
struct Point : ShapeBase
{
	virtual ~Point() = default;
	
	size_t	X;
	size_t	Y;
};

	// Добавил чисто для стиралки
struct Circle : ShapeBase
{
	virtual  ~Circle() = default;

	Point	Center;
	size_t	Rad;
};
	
struct Line : ShapeBase
{
	virtual ~Line() = default;
	
	Point	P1;
	Point	P2;

	size_t	Thickness;
};

struct Rect : ShapeBase
{
	virtual ~Rect() = default;
	
	Point	P1;
	Point	P2;

	size_t	BorderThickness;
};

struct Text : ShapeBase
{
	virtual ~Text() = default;

	Point		P;
	std::string Data;
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

using Shape = std::unique_ptr<ShapeBase>;
	
}
