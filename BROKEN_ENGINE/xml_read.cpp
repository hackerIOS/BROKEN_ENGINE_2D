//XML Read

#include <iostream>
using namespace std;
#include "IRapidXml/rapidxml.hpp"
#include "IRapidXml/rapidxml_print.hpp"
#include "IRapidXml/rapidxml_utils.hpp"
#include <vector>

using namespace rapidxml;
int main(){
	file<>Filedoc("xmlout.xml");
	xml_document<>doc;
	cout<<Filedoc.data()<<endl;
	doc.parse<0>(Filedoc.data());
	xml_node<>*node1=doc.first_node();
	
}
/*<XML name="123">

<Node_Start linkNode="DebugMessage" outpoint="out" linkpoint="show" Pos=100,20 t_id=0 l_id=1>//Add a this id and a link id

//
<Node_DebugMessage_DW inpoint="Msg" linkinpoint="String" t_id=1 l_id=2/>

<Node_String Str="123" outpoint="outstr" linkNode="DebugMessage" linkpoint="Msg" Pos=0,0 t_id=2 l_id=1/>


<Node_DebugMessage outpoint="Done" Msg="123" s_pos=10,10 linkNode="Sleep" linkpoint="Enable" Pos =100,40 t_id=1 l_id=3/>

//
<Node_Sleep outpoint="SleepEnd" SleepTime=1000 linkNode="DebugMessage" linkpoint="show" Pos=120,20 t_id=3 l_id=4/>


//<Node_Loop id=1/>//数据循环了

<Node_DebugMessage outpoint="" Msg="456" s_pos=10,10 linkNode="" linkpoint="" Pos=100,40 t_id=4 l_id=/>



<Node_Start/>

<update>

<update/>

<XML/>*/