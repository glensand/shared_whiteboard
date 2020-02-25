//#include <gtest/gtest.h>
//#include <iostream>
//
//class Foo
//{
//public:
//	Foo()
//		: i(0)
//	{
//		std::cout << "CONSTRUCTED" << std::endl;
//	}
//	~Foo()
//	{
//		std::cout << "DESTRUCTED" << std::endl;
//	}
//	int i;
//};
//
//class TestFoo : public ::testing::Test
//{
//protected:
//	void SetUp()
//	{
//		foo = new Foo;
//		foo->i = 5;
//	}
//	void TearDown()
//	{
//		delete foo;
//	}
//	Foo* foo;
//};
//
//TEST_F(TestFoo, test2)
//{
//	ASSERT_EQ(1, 5);
//}

#include <iostream>

#include <sharedWhiteboard/serializer/SimpleShapeSeializer.h>

#include <sstream>

int main(int argc, char* argv[])
{
	auto shape = std::make_shared<wboard::SimpleShape>();
	shape->Type = wboard::ShapeType::Curve;

	std::stringstream stream;
	const wboard::SimpleShapeSeializer ser;

	ser.Serialize(stream, shape);

	std::cout << stream.tellp() << std::endl;
	stream.seekg(stream.tellp());
	std::cout << stream.tellg() << std::endl;
	
	const auto deserializedShape = ser.Deserialize(stream);

	std::cout << int(deserializedShape->Type) << std::endl;
}
