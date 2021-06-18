#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <mysql.h>

#include "cgicc/Cgicc.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTTPContentHeader.h"

using namespace std;
using namespace cgicc;

char sql[512];
char cgiOut[512];

int main()
{
	
	try{
		
		Cgicc cgi;

      		// Send HTTP header
      		cout << HTTPContentHeader("text/html; charset=utf-8");
      		//cout << HTTPHTMLHeader() << endl;

      		// Set up the HTML document
      		cout << html() << head(title("Cgicc Login")) << endl;
      		cout << "<body background=\"../2.jpeg\">" << endl;

      		// Print out the submitted element
      		form_iterator name = cgi.getElement("name");
      		if(name != cgi.getElements().end()) {
      			cout << "Your name: " << **name << "<br>";
      		}
      		form_iterator student_id = cgi.getElement("student_id");
      		if(student_id != cgi.getElements().end()) {
      			cout << "Your student_id: " << **student_id << "<br>";
      		}
      		form_iterator sex = cgi.getElement("sex");
      		if(sex != cgi.getElements().end()) {
      			cout << "Your sex: " << **sex << "<br>";
      		}
      		form_iterator year = cgi.getElement("year");
      		if(year != cgi.getElements().end()) {
      			cout << "Your year: " << **year << "<br>";
      		}
      		form_iterator dept_name = cgi.getElement("dept_name");
      		if(dept_name != cgi.getElements().end()) {
      			cout << "Your dept_name: " << **dept_name << "<br>";
      		}
      		form_iterator class0 = cgi.getElement("class0");
      		if(class0 != cgi.getElements().end()) {
      			cout << "Your class: " << **class0 << "<br>";
      		}
      		form_iterator chinese = cgi.getElement("chinese");
      		if(chinese != cgi.getElements().end()) {
      			cout << "Your chinese: " << **chinese << "<br>";
      		}
      		form_iterator math = cgi.getElement("math");
      		if(math != cgi.getElements().end()) {
      			cout << "Your math: " << **math << "<br>";
      		}
      		form_iterator english = cgi.getElement("english");
      		if(english != cgi.getElements().end()) {
      			cout << "Your english: " << **english << "<br>";
      		}
      		
      		string name1((name)->getValue());
      		const char *name2 = name1.c_str();
      		string class1((class0)->getValue());
      		const char *class2 = class1.c_str();
      		string sex1((sex)->getValue());
      		const char *sex2 = sex1.c_str();
      		string dept_name1((dept_name)->getValue());
      		const char *dept_name2 = dept_name1.c_str();
      		string chinese1((chinese)->getValue());
      		const char *chinese2 = chinese1.c_str();
      		string math1((math)->getValue());
      		const char *math2 = math1.c_str();
      		string english1((english)->getValue());
      		const char *english2 = english1.c_str();
      		string student_id1((student_id)->getValue());
      		const char *student_id2 = student_id1.c_str();
      		string year1((year)->getValue());
      		const char *year2 = year1.c_str();
      		
      		MYSQL mysql;
      		int res;
      		mysql_init(&mysql);
      		if(MYSQL *conn=mysql_real_connect(&mysql, "127.0.0.1","root","123456","Cgicc_StudentScoreSystem_Project",0,NULL,CLIENT_FOUND_ROWS)){
      			cout << "[+] Connection Success!\n" << "<br>";
      			
      			string a="300",b="100",c="1";
      			const char *a1=a.c_str(),*b1=b.c_str(),*c1=c.c_str();
      			
      			int cn=stoi(chinese1),mh=stoi(math1),en=stoi(english1);
      			int sum=cn+mh+en;
      			float cd=sum/3;
      			
      			sprintf(sql,"insert into Infomation values('%s',%s,'%s',%s,'%s','%s',%s,%s,%s,%d,%f,%s);",name2,student_id2,sex2,year2,class2,dept_name2,chinese2,math2,english2,sum,cd,c1);
      			//sprintf(sql,"select * from Infomation where student_id='%s'",student_id2);
      			cout<<sql<<"<br>";
      			res=mysql_query(conn,sql);
      			
      		        if(res){
      		           	cout<<"[-] Query Input Error!"<< "<br>";
      		        }
      			else{
				cout<<"[+] Query Input Success!"<< "<br>";
			}
      			
      			sprintf(sql,"select * from Infomation");
      			res=mysql_query(conn,sql);
      			if(!res)cout<<"[+] Query Input2 Success!"<< "<br>";
      			MYSQL_ROW row;
      			auto rsl= mysql_store_result(conn);
      			unsigned int row_max_num = mysql_num_fields(rsl);
      			
      			cout<<"<table border=\"1\" cellpadding=\"10\">";
      			cout<<"<tr>";
      			cout<<"<th>Name</th><th>Student ID</th><th>Sex</th><th>Years</th><th>Class</th><th>Dept Name</th>";
      			cout<<"<th>Chinese</th><th>Math</th><th>English</th><th>Score</th><th>Credit</th><th>Ranking</th>";
      			cout<<"</tr>";
      			
      			
      			while ((row = mysql_fetch_row(rsl)))
      			{	
      				cout<<"<tr>";
				for(int i = 0; i < row_max_num; i++){
					cout<<"<td>"<<row[i]<<"</td>"<<"<br>";	
				}
				cout<<"</tr>";
			}
			cout<< "</table>"<<"<br>";
			
      			mysql_close(conn);
			mysql_close(&mysql);
			
		}
		else{
			cout << "connect failed" << endl;
		}
		
		
		// Close the HTML document
      		cout << body() << html();
      		

	}
	catch(exception& e) {
      	// handle any errors - omitted for brevity
   	}
}
