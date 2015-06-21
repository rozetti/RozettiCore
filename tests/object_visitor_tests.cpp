#include "tests.h"

#include "detail/objects.h"
#include "detail/object_impl.h"

#include <iostream>

#if 0
namespace Test
{
	class ObjectVisitorTests : public ::testing::Test
	{
	protected:
		ObjectVisitorTests() :
		state(nullptr)
		{
		}
		
		virtual void SetUp()
		{
			state = luaL_newstate();
			script_state.set_lua_state(state);
			
			ASSERT_NE(nullptr, state);
			
			luaL_openlibs(state);
			
			m_pos = new ObjectWithPositionImpl(4.2, 1.729);
			m_size = new ObjectWithSizeImpl(0.618, 1.618);
			rz::bounding_box _box(rz::vector2(1.0, 2.0), rz::vector2(3.0, 4.0));
			m_box = new ObjectWithBoundingBoxImpl(_box);
			
			objects.clear();
			objects.push_back(m_pos);
			objects.push_back(m_size);
			objects.push_back(m_box);
			
			rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_construct_policy> construct(&script_state);
			
			m_pos->accept(construct);
			m_size->accept(construct);
			m_box->accept(construct);
		}
		
		virtual void TearDown()
		{
			delete m_pos;
			delete m_size;
			delete m_box;
		}
		
	protected:
		lua_State *state;
		rz::lua_scriptable_object_operation_state script_state;
		
		std::vector<ObjectBaseImpl *> objects;
		
		ObjectWithPositionImpl *m_pos;
		ObjectWithSizeImpl *m_size;
		ObjectWithBoundingBoxImpl *m_box;
	};
	
	TEST_F(ObjectVisitorTests, ObjectsCollectionIsOK)
	{
		ASSERT_NE(nullptr, m_pos);
		ASSERT_STREQ("ObjectWithPositionImpl", m_pos->get_name().c_str());
		
		ASSERT_NE(nullptr, m_size);
		ASSERT_STREQ("ObjectWithSizeImpl", m_size->get_name().c_str());

		ASSERT_NE(nullptr, m_box);
		ASSERT_STREQ("ObjectWithBoundingBoxImpl", m_box->get_name().c_str());
	}
	
	TEST_F(ObjectVisitorTests, ObjectTablesCreatedOK)
	{
		lua_getglobal(state, "ObjectWithPositionImpl");
		ASSERT_TRUE(lua_istable(state, -1));
		lua_pop(state, 1);
		
		lua_getglobal(state, "ObjectWithSizeImpl");
		ASSERT_TRUE(lua_istable(state, -1));
		lua_pop(state, 1);
		
		lua_getglobal(state, "ObjectWithBoundingBoxImpl");
		ASSERT_TRUE(lua_istable(state, -1));
		lua_pop(state, 1);

		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy> print(&script_state);
		
		for (auto p : objects) { p->accept(print); }
	}
	
	TEST_F(ObjectVisitorTests, UploadToLua)
	{
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy> print(&script_state);
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_upload_policy> upload(&script_state);

		auto f = "ObjectWithPositionImpl.x = 0; "
		"ObjectWithPositionImpl.y = 0; "
		"ObjectWithSizeImpl.w = 0; "
		"ObjectWithSizeImpl.h = 0; "
		"ObjectWithBoundingBoxImpl.bounding_box.min.x = 0; "
		"ObjectWithBoundingBoxImpl.bounding_box.min.y = 0; "
		"ObjectWithBoundingBoxImpl.bounding_box.max.x = 0; "
		"ObjectWithBoundingBoxImpl.bounding_box.max.y = 0;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		f = "return ObjectWithPositionImpl.x, ObjectWithPositionImpl.y, "
			"ObjectWithSizeImpl.w, ObjectWithSizeImpl.h, "
			"ObjectWithBoundingBoxImpl.bounding_box.min.x, "
			"ObjectWithBoundingBoxImpl.bounding_box.min.y,"
			"ObjectWithBoundingBoxImpl.bounding_box.max.x, "
			"ObjectWithBoundingBoxImpl.bounding_box.max.y;";
		
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		lua_setglobal(state, "f");
		
		lua_getglobal(state, "f");
		ASSERT_TRUE(lua_isfunction(state, -1));
		ASSERT_EQ(0, lua_pcall(state, 0, 8, 0)) << lua_tostring(state, -1);
		
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -8));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -7));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -6));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -5));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -4));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -3));
		EXPECT_DOUBLE_EQ(0, lua_tonumber(state, -2));
		ASSERT_DOUBLE_EQ(0, lua_tonumber(state, -1));

		std::cout << "should be all zeros:" << std::endl;
		for (auto p : objects) { p->accept(print); }
		
		for(auto p : objects) {	p->accept(upload); }
		
		lua_getglobal(state, "f");
		ASSERT_TRUE(lua_isfunction(state, -1));
		ASSERT_EQ(0, lua_pcall(state, 0, 8, 0)) << lua_tostring(state, -1);
		
		EXPECT_DOUBLE_EQ(m_pos->get_x(), lua_tonumber(state, -8));
		EXPECT_DOUBLE_EQ(m_pos->get_y(), lua_tonumber(state, -7));
		EXPECT_DOUBLE_EQ(m_size->get_w(), lua_tonumber(state, -6));
		EXPECT_DOUBLE_EQ(m_size->get_h(), lua_tonumber(state, -5));
		EXPECT_DOUBLE_EQ(m_box->get_bounding_box().Min.X, lua_tonumber(state, -4));
		EXPECT_DOUBLE_EQ(m_box->get_bounding_box().Min.Y, lua_tonumber(state, -3));
		EXPECT_DOUBLE_EQ(m_box->get_bounding_box().Max.X, lua_tonumber(state, -2));
		EXPECT_DOUBLE_EQ(m_box->get_bounding_box().Max.Y, lua_tonumber(state, -1));

		std::cout << "should be back to proper values now:" << std::endl;
		for (auto p : objects) { p->accept(print); }
	}
	
	TEST_F(ObjectVisitorTests, DownloadFromLua)
	{
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy> print(&script_state);
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_download_policy> download(&script_state);

		auto x = m_pos->get_x();
		auto y = m_pos->get_y();
		auto w = m_size->get_w();
		auto h = m_size->get_h();
		
		m_pos->set_x(0.0);
		m_pos->set_y(0.0);
		m_size->set_w(0.0);
		m_size->set_h(0.0);

		std::cout << "should not be all zeros:" << std::endl;
		for (auto p : objects) { p->accept(print); }

		for(auto p : objects) {	p->accept(download); }
		
		EXPECT_DOUBLE_EQ(x, m_pos->get_x());
		EXPECT_DOUBLE_EQ(y, m_pos->get_y());
		EXPECT_DOUBLE_EQ(w, m_size->get_w());
		EXPECT_DOUBLE_EQ(h, m_size->get_h());
	}

	TEST_F(ObjectVisitorTests, CallObjectFunction)
	{
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy> print(&script_state);

		m_pos->accept(print);
		ASSERT_FLOAT_EQ(4.2, m_pos->get_x());
		ASSERT_FLOAT_EQ(1.729, m_pos->get_y());

		auto f = "ObjectWithPositionImpl:move(3.14, 1729);";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		m_pos->accept(print);
		EXPECT_FLOAT_EQ(3.14, m_pos->get_x());
		EXPECT_FLOAT_EQ(1729, m_pos->get_y());

		m_size->accept(print);
		ASSERT_FLOAT_EQ(0.618, m_size->get_w());
		ASSERT_FLOAT_EQ(1.618, m_size->get_h());
		
		f = "ObjectWithSizeImpl:resize(1.23, 3.21);";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		m_size->accept(print);
		EXPECT_FLOAT_EQ(1.23, m_size->get_w());
		EXPECT_FLOAT_EQ(3.21, m_size->get_h());
	}
	
	TEST_F(ObjectVisitorTests, UploadDownloadAndPrintVisitors)
	{
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy> print(&script_state);
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_upload_policy> upload(&script_state);
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_download_policy> download(&script_state);
		
		auto f = "ObjectWithPositionImpl.x=0; ObjectWithPositionImpl.y=0; " \
		"ObjectWithSizeImpl.w=0; ObjectWithSizeImpl.h=0;" \
		"ObjectWithBoundingBoxImpl.bounding_box.min.x=0; " \
		"ObjectWithBoundingBoxImpl.bounding_box.min.y=0; " \
		"ObjectWithBoundingBoxImpl.bounding_box.max.x=0; " \
		"ObjectWithBoundingBoxImpl.bounding_box.max.y=0;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);

		for(auto p : objects) {	p->accept(print); }

		for(auto p : objects) {	p->accept(upload); }
		for(auto p : objects) {	p->accept(print); }
		
		f = "ObjectWithPositionImpl.x=1.1; ObjectWithPositionImpl.y=2.2; " \
			"ObjectWithSizeImpl.w=3.3; ObjectWithSizeImpl.h=4.4;" \
			"ObjectWithBoundingBoxImpl.bounding_box.min.x=5.5; " \
			"ObjectWithBoundingBoxImpl.bounding_box.min.y=6.6; " \
			"ObjectWithBoundingBoxImpl.bounding_box.max.x=7.7; " \
			"ObjectWithBoundingBoxImpl.bounding_box.max.y=8.8;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		for(auto p : objects) {	p->accept(print); }
		for(auto p : objects) {	p->accept(download); }
		
		EXPECT_DOUBLE_EQ(1.1, m_pos->get_x());
		EXPECT_DOUBLE_EQ(2.2, m_pos->get_y());
		EXPECT_DOUBLE_EQ(3.3, m_size->get_w());
		EXPECT_DOUBLE_EQ(4.4, m_size->get_h());
		EXPECT_FLOAT_EQ(5.5, m_box->get_bounding_box().Min.X);
		EXPECT_FLOAT_EQ(6.6, m_box->get_bounding_box().Min.Y);
		EXPECT_FLOAT_EQ(7.7, m_box->get_bounding_box().Max.X);
		EXPECT_FLOAT_EQ(8.8, m_box->get_bounding_box().Max.Y);
		
		for(auto p : objects) {	p->accept(upload); }
		for(auto p : objects) {	p->accept(print); }
		for(auto p : objects) {	p->accept(download); }
		
		EXPECT_DOUBLE_EQ(1.1, m_pos->get_x());
		EXPECT_DOUBLE_EQ(2.2, m_pos->get_y());
		EXPECT_DOUBLE_EQ(3.3, m_size->get_w());
		EXPECT_DOUBLE_EQ(4.4, m_size->get_h());
		EXPECT_FLOAT_EQ(5.5, m_box->get_bounding_box().Min.X);
		EXPECT_FLOAT_EQ(6.6, m_box->get_bounding_box().Min.Y);
		EXPECT_FLOAT_EQ(7.7, m_box->get_bounding_box().Max.X);
		EXPECT_FLOAT_EQ(8.8, m_box->get_bounding_box().Max.Y);
	}
	
	TEST_F(ObjectVisitorTests, DestroyObjects)
	{
		rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_destruct_policy> destroy(&script_state);
		
		for(auto p : objects) {	p->accept(destroy); }
		
		for(auto p : objects)
		{
			lua_getglobal(state, p->get_name().c_str());
			
			ASSERT_FALSE(lua_istable(state, -1));
		}
	}
}
#endif