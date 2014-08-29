#include "stdafx.h"
#include "myString.h"
#include "Optional.h"

using namespace Base;

static cString longString() { return "abcdefghijklmnopqrstuvwxyz0123456789"; }

class StringTest : public ::testing::Test
{
protected:
  cString str;
  cString str1;

  void SetUp()
  {
    str1 = cString(" Ankur is the best the ");
  }

  void TearDown()
  {

  }
};

TEST_F(StringTest, Constructors)
{
  cString s;
  EXPECT_EQ(s, "");

  cString s1("abc");
  EXPECT_EQ(s1, "abc");

  cString s11(cString("abc"));
  EXPECT_EQ(s11, "abc");

  cString s2(longString().GetData());
  EXPECT_EQ(s2, longString());

  cString s22(longString());
  EXPECT_EQ(s22, longString().GetData());

  cString s3(std::string("abc"));
  EXPECT_EQ(s3, "abc");
}

TEST_F(StringTest, MakeFormatted)
{
  cString s = cString::MakeFormatted("abc %d %c", 5, 'a');
  EXPECT_EQ(s, "abc 5 a");
  
  cString s1 = cString::MakeFormatted("abc");
  EXPECT_EQ(s1, "abc");

  cString s2 = cString::MakeFormatted("");
  EXPECT_EQ(s2, "");
}

TEST_F(StringTest, GetData)
{
  EXPECT_STREQ(str.GetData(), "");
  EXPECT_STREQ(str1.GetData()," Ankur is the best the ");
}

TEST_F(StringTest, IsEmpty)
{
  EXPECT_EQ(str.IsEmpty(), true);
  EXPECT_EQ(str1.IsEmpty(), false);
}

TEST_F(StringTest, GetLength)
{
  cString str2 = longString();
  cString str3 = " is the best";
  cString str4 = cString::MakeFormatted("%d %s %c", 5, "ankur", 'c');

  EXPECT_EQ(str.GetLength(), 0);
  EXPECT_EQ(str1.GetLength(), 23);
  EXPECT_EQ(str2.GetLength(), 36);
  EXPECT_EQ(str3.GetLength(), 12);
  EXPECT_EQ(str4.GetLength(), 9);
}

TEST_F(StringTest, GetSubString)
{
  EXPECT_STREQ(str.GetSubString(-1, 0).GetData(), "");
  EXPECT_STREQ(str.GetSubString(0, 1).GetData(), "");
  
  EXPECT_STREQ(str1.GetSubString(0,36).GetData(), "");
  EXPECT_STREQ(str1.GetSubString(0,5).GetData(), " Ankur");
  EXPECT_STREQ(str1.GetSubString(0,2).GetData(), " An");
  EXPECT_STREQ(str1.GetSubString(0,str1.GetLength()).GetData(), " Ankur is the best the ");

  EXPECT_STREQ(str1.GetSubString(10,15).GetData(), "the be");
  EXPECT_STREQ(str1.GetSubString(9,str1.GetLength()).GetData(), " the best the ");
}

TEST_F(StringTest, FindIndex)
{
  tOptional<int> val;
  val = str.FindIndex('a', 0);
  EXPECT_FALSE(val.IsValid());

  val = str1.FindIndex('e', 0);
  EXPECT_EQ(*val, 12);
  val = str1.FindIndex('e', 13);
  EXPECT_EQ(*val, 15);
  val = str1.FindIndex('e', 25);
  EXPECT_TRUE(val.IsInvalid());
  val = str1.FindIndex('q', 0);
  EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindFirstOfAny)
{
  tOptional<int> val;
  val = str.FindFirstOfAny("a", 0);
  EXPECT_FALSE(val.IsValid());

  val = str1.FindFirstOfAny("teb", 0);
  EXPECT_EQ(*val, 10);
  val = str1.FindFirstOfAny("bq", 11);
  EXPECT_EQ(*val, 14);
  val = str1.FindFirstOfAny("lzq", 0);
  EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindFirstNotOfAny)
{
  tOptional<int> val;
  val = str.FindFirstNotOfAny("a", 0);
  EXPECT_FALSE(val.IsValid());

  val = str1.FindFirstNotOfAny(" An", 0);
  EXPECT_EQ(*val, 3);
  val = str1.FindFirstNotOfAny("be", 14);
  EXPECT_EQ(*val, 16);
  val = str1.FindFirstNotOfAny("Ankur istheb", 0);
  EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindLastOfAny)
{
  tOptional<int> val;
  val = str.FindLastOfAny("a", str.GetLength());
  EXPECT_FALSE(val.IsValid());

  val = str1.FindLastOfAny("teb", str1.GetLength());
  EXPECT_EQ(*val, 21);
  val = str1.FindLastOfAny("At", 13);
  EXPECT_EQ(*val, 10);
  val = str1.FindLastOfAny("lzq", str1.GetLength());
  EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindLastNotOfAny)
{
  tOptional<int> val;
  val = str.FindLastNotOfAny("a", str.GetLength());
  EXPECT_FALSE(val.IsValid());

  val = str1.FindLastNotOfAny(" besth", str1.GetLength());
  EXPECT_EQ(*val, 7);
  val = str1.FindLastNotOfAny(" besth", 12);
  EXPECT_EQ(*val, 7);
  val = str1.FindLastNotOfAny("Ankur istheb", str1.GetLength());
  EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, CompareInsensitive)
{
  EXPECT_TRUE(str.CompareInsensitive(""));
  EXPECT_FALSE(str.CompareInsensitive("a"));
  
  cString str2("Ankur");
  EXPECT_TRUE(str2.CompareInsensitive("Ankur"));
  EXPECT_TRUE(str2.CompareInsensitive("anKUr"));
  EXPECT_FALSE(str2.CompareInsensitive(" Ankur"));
  
  cString str3("Ankur 5");
  EXPECT_TRUE(str3.CompareInsensitive("Ankur 5"));
  EXPECT_TRUE(str3.CompareInsensitive("anKUr 5"));
  EXPECT_FALSE(str3.CompareInsensitive(" Ankur 5"));
}

TEST_F(StringTest, TrimLeft)
{
  str.TrimLeft();
  EXPECT_STREQ(str.GetData(), "");
  
  str1.TrimLeft();
  EXPECT_STREQ(str1.GetData(), "Ankur is the best the ");

  cString str2("    Ankur   ");
  str2.TrimLeft();
  EXPECT_STREQ(str2.GetData(), "Ankur   ");
}

TEST_F(StringTest, TrimRight)
{
  str.TrimRight();
  EXPECT_STREQ(str.GetData(), "");
  
  str1.TrimRight();
  EXPECT_STREQ(str1.GetData(), " Ankur is the best the");
  
  cString str2(" Ankur      \n");
  str2.TrimRight();
  EXPECT_STREQ(str2.GetData(), " Ankur");
}

TEST_F(StringTest, TrimBoth)
{
  str.TrimBoth();
  EXPECT_STREQ(str.GetData(), "");

  str1.TrimBoth();
  EXPECT_STREQ(str1.GetData(), "Ankur is the best the");
}
