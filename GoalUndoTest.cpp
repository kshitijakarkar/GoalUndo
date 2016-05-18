/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
 
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(GoalUndoTest, AddGoalandOperation)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   ASSERT_EQ("Square",gu.getGoal());
}

TEST(GoalUndoTest, AddOperationtoExistingGoal)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Perimeter");
   gu.addOperation("Same Length Property");
   ASSERT_EQ("Area Perimeter Same Length Property",gu.getOperations());
}


TEST(GoalUndoTest, AddEmptyGoal)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("","Radius");
   ASSERT_EQ("Square",gu.getGoal());
}

TEST(GoalUndoTest, AddEmptyOperationtoGoal)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","");
   ASSERT_EQ("Square",gu.getGoal());
}

TEST(GoalUndoTest, AddGoals)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   ASSERT_EQ("Sphere",gu.getGoal());
}

TEST(GoalUndoTest, GetOperations)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   ASSERT_EQ("Volume Radius",gu.getOperations());
}

TEST(GoalUndoTest, AddEmptyOperation)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("");
   ASSERT_EQ("Square",gu.getGoal());
}

TEST(GoalUndoTest, AddOperationtoEmptyList)
{
   GoalUndo gu;
   gu.addOperation("Circle");
   ASSERT_EQ("Circle",gu.getGoal());
}

TEST(GoalUndoTest, CheckOperationtoEmptyList)
{
   GoalUndo gu;
   gu.addOperation("Circle");
   ASSERT_EQ("Circle",gu.getOperations());
}

TEST(GoalUndoTest, AddEmptyOperationtoEmptyList)
{
   GoalUndo gu;
   gu.addOperation("");
   ASSERT_EQ("",gu.getOperations());
}

TEST(GoalUndoTest, GetEmptyGoal)
{
   GoalUndo gu;
   ASSERT_EQ("",gu.getGoal());
}

TEST(GoalUndoTest, GetEmptyOperation)
{
   GoalUndo gu;
   ASSERT_EQ("",gu.getOperations());
}

TEST(GoalUndoTest, UndoLatestGoalOperation)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   gu.addOperation("pi*r^3");
   
   gu.undoOperation("Radius");
   ASSERT_EQ("Volume pi*r^3",gu.getOperations());
}


TEST(GoalUndoTest, UndoLatestGoalMultipleSameOperation)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   gu.addOperation("pi*r^3");
   gu.addOperation("Radius");

   gu.undoOperation("Radius");
   ASSERT_EQ("Volume Radius pi*r^3",gu.getOperations());
}

TEST(GoalUndoTest, UndoNoMatchOperation)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.undoOperation("Radius");
   ASSERT_EQ("Area",gu.getOperations());
}

TEST(GoalUndoTest, UndoInvalidOperation)
{
   GoalUndo gu;
   gu.undoOperation("Radius");
   ASSERT_EQ("",gu.getOperations());
}

TEST(GoalUndoTest, UndoOperation)
{
   bool set = false;   
   GoalUndo gu;
   gu.addOperation("Square","Area");
   try
   {
      gu.undoOperation("Area");
     
   }
   catch(...)
   {
      set = true;
      ASSERT_EQ("Square",gu.getGoal());
   }
   if(set == false)
   {
      ASSERT_EQ("",gu.getGoal());
   }
}

TEST(GoalUndoTest, UndoEmptyOperation)
{
   GoalUndo gu;
   gu.undoOperation();
   ASSERT_EQ("",gu.getOperations());
}


TEST(GoalUndoTest, UndoOneOperation)
{
   bool set;
   GoalUndo gu;
   gu.addOperation("Square","Area");
   try{
      set = false;
      gu.undoOperation();
   }
   catch(...)
   {
      set = true;
      ASSERT_EQ("Square",gu.getGoal());
   }
   if(set == false)
   {
      ASSERT_EQ("",gu.getGoal());
   }
}

TEST(GoalUndoTest, UndoLatestOperation)
{
   bool set = false;
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   gu.addOperation("pi*r^3");
   try
   {
      gu.undoOperation();
   }
   catch(...)
   {
      set = true;
      ASSERT_EQ("Volume Radius pi*r^3",gu.getOperations());
   }
   if(set == false)
   {
      ASSERT_EQ("Volume Radius",gu.getOperations());
   }
}


TEST(GoalUndoTest, UndoOneGoal)
{
   bool set;
   GoalUndo gu;
   gu.addOperation("Square","Area");
   try
   {
      set = false;
      gu.undoGoal();
   }
   catch(...)
   {
      set = true;
      ASSERT_EQ("Square",gu.getGoal());
   }
   if(set == false)
   {
      ASSERT_EQ("",gu.getGoal());
   }
}

TEST(GoalUndoTest, UndoEmptyGoal)
{
   GoalUndo gu;
   gu.undoGoal();
   ASSERT_EQ("",gu.getGoal());
}

TEST(GoalUndoTest, UndoLatestGoal)
{
   GoalUndo gu;
   gu.addOperation("Square","Area");
   gu.addOperation("Circle","Circumference");
   gu.addOperation("Sphere","Volume");
   gu.addOperation("Radius");
   gu.addOperation("pi*r^3");
   
   gu.undoGoal();
   ASSERT_EQ("Circle",gu.getGoal());
}

